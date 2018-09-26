---
layout: post
title:  "Xception (pytorch 0.4.1)"
date:   2018-09-26 8:00:05 +0800
categories: deep_learning
use_math: true
tags: deep_learning xception bottleneck basenet
---

`Not tested yet`

```python

import numpy as np
import torch
import torch.nn as nn

def sameConv(in_c, out_c, k_size=3, stride=1, group=1,where=None): #where = w or h if Asym conv
  pad_w = pad_h = 0
  if(where is None):
    pad_total = k_size-1 # Refer to the formula in the blog
    
    # https://nailbrainz.github.io/deep_learning/2018/07/11/conv-size.html
    pad_w = pad_h = pad_total // 2 # if not divisible by 2, can't handle
    
    # Note that, the (a, b) padding of nn.Conv2d adds 
    # (2*a) on width, and (2*b) on height (on each side)
  else:
    if(where == 'w'):
      pad_total = k_size[0] - 1
      pad_w = pad_total // 2
    else:
      pad_total = k_size[1] - 1
      pad_h = pad_total // 2
  
  return nn.Conv2d(in_c, out_c, k_size, stride=stride, 
                   padding=(pad_w, pad_h),groups=group, bias=False)

def getDim(k_size):
  if(type(k_size) != type(())): return None
  if k_size[0] > k_size[1]: return 'w'
  elif k_size[0] < k_size[1]: return 'h'
  else : return None

bnMomentum = 0.1
  
class SeparableConv(nn.Module):
  def __init__(self, in_c, out_c, k_size, stride=1, isSame=True):
    super(SeparableConv, self).__init__()
    if isSame:
      self.conv1 = sameConv(in_c, in_c, k_size, 
                           stride=stride, group=in_c, where=getDim(k_size))
    else:
      self.conv1 = nn.Conv2d(in_c, in_c, k_size, stride=stride, bias=False)
      
    self.conv2 = sameConv(in_c, out_c, 1)
    
    
  def forward(self, x):
    x = self.conv1(x)
    x = self.conv2(x)
    return x

class XcepionModule(nn.Module):
  def __init__(self, in_c, out_c):
    super(XcepionModule, self).__init__()
    modules = []
    for i in range(3):
      modules += [SeparableConv(in_c, out_c, 3, 1, True), 
                  nn.BatchNorm2d(out_c, momentum=bnMomentum),
                  nn.ReLU()]
    self.module = nn.Sequential(*modules)
    
  def forward(self, x):
    residual = x
    x = self.module(x)
    x = residual + x
    return x

class XceptionReduc(nn.Module):
  def __init__(self, in_c, out_c, initRelu=True):
    super(XceptionReduc, self).__init__()
    #in = 384 X 35 X 35
    self.initRelu = None
    if initRelu :
      self.initRelu = nn.ReLU()
    
    self.residConv = nn.Sequential(
        sameConv(in_c, out_c, 1, stride=2),
        nn.BatchNorm2d(out_c, momentum=bnMomentum))
    
    self.conv1 = SeparableConv(in_c, out_c, 3, 1, True)
    self.bn1 = nn.BatchNorm2d(out_c, momentum=bnMomentum)
    
    self.relu2 = nn.ReLU()
    self.conv2 = SeparableConv(out_c, out_c, 3, 1, True)
    self.bn2 = nn.BatchNorm2d(out_c, momentum=bnMomentum)
    
    self.mp = nn.MaxPool2d(3, padding=1, stride=2)
    
  def forward(self, x):
    residual = self.residConv(x)
    print('resid size = ', residual.size())
    if self.initRelu is not None:
      x = self.initRelu(x)
    x = self.conv1(x)
    x = self.bn1(x)
    
    x = self.relu2(x)
    x = self.conv2(x)
    x = self.bn2(x)
    
    x = self.mp(x)
    print('x size = ', x.size())
    
    x = x + residual
    return x

class Xception(nn.Module):
  n_class = 1000
  def __init__(self):
    super(Xception, self).__init__()

    self.reduc = nn.Sequential(
        nn.Conv2d(3, 32, 3, stride=2, padding=1, bias=False),
        nn.BatchNorm2d(32, momentum=bnMomentum),
        nn.ReLU(),
        
        sameConv(32, 64, 3),
        nn.BatchNorm2d(64, momentum=bnMomentum),
        nn.ReLU(),
        
        XceptionReduc(64, 128, initRelu=False),
        XceptionReduc(128, 256, initRelu=True),
        XceptionReduc(256, 728, initRelu=True),
        )
    self.layers = nn.Sequential(
        
        *[XcepionModule(728, 728) for i in range(8)],
        )
    
    self.module1 = nn.Sequential(
      nn.ReLU(inplace=True),
      SeparableConv(728, 728, 3, 1, True),
      nn.BatchNorm2d(728, momentum=bnMomentum),
        
      nn.ReLU(inplace=True),
      SeparableConv(728, 1024, 3, 1, True),
      nn.BatchNorm2d(1024, momentum=bnMomentum),
      nn.MaxPool2d(3, stride=2, padding=1))
    
    self.residModule = nn.Sequential(
      sameConv(728, 1024, 1, stride=2),
      nn.BatchNorm2d(1024, momentum=bnMomentum))
    
    self.module2 = nn.Sequential(SeparableConv(1024, 1536, 3, 1, True),
                                nn.BatchNorm2d(1536, momentum=bnMomentum),
                                nn.ReLU(inplace=True),
                                SeparableConv(1536, 2048, 3, 1, True),
                                nn.BatchNorm2d(2048, momentum=bnMomentum),
                                nn.ReLU(inplace=True))
  
    
    self.linear = nn.Linear(2048, self.n_class)
    self.bn = nn.BatchNorm2d(2048, momentum=bnMomentum)
    for m in self.modules():
      if isinstance(m, nn.Conv2d):
        nn.init.kaiming_normal_(m.weight, mode='fan_out', nonlinearity='relu')
      elif isinstance(m, nn.BatchNorm2d):
        nn.init.constant_(m.weight, 1)
        nn.init.constant_(m.bias, 0)

  def forward(self, x):
    x = self.reduc(x)
    print("after reduc = ", x.size())
    x = self.layers(x)
    print("after layers = ", x.size())
    residual = self.residModule(x)
    x = self.module1(x)
    x = residual + x
    x = self.module2(x)
    print("final layers = ", x.size())
    x = x.mean(dim=2, keepdim=True)     
    x = x.mean(dim=3, keepdim=True)
    
    x = self.linear(x.view(x.size(0), -1))
    return x

if __name__=='__main__':
  model = Xception()
  y = model(torch.randn(1, 3, 299, 299))
  print(y.size())

print('done')
```
