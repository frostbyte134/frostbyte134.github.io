---
layout: post
title:  "Inception-V4 (pytorch 0.4.0)"
date:   2018-07-25 10:00:05 +0800
categories: deep_learning
use_math: true
tags: deep_learning resnet bottleneck
---

### Convolution
Need special care for asym conv

```python
def sameConv(in_c, out_c, k_size=3, stride=1, where=None): #where = w or h if Asym conv
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
                   padding=(pad_w, pad_h),bias=False)

def getDim(k_size):
  if(type(k_size) != type(())): return None
  if k_size[0] > k_size[1]: return 'w'
  elif k_size[0] < k_size[1]: return 'h'
  else : return None


class ConvModule(nn.Module):
  def __init__(self, in_c, out_c, k_size, stride=1, isSame=False):
    super(ConvModule, self).__init__()
    if isSame:
      self.conv = sameConv(in_c, out_c, k_size, 
                           stride=stride, where=getDim(k_size))
    else:
      self.conv = nn.Conv2d(in_c, out_c, k_size, stride=stride)
      
    self.bn = nn.BatchNorm2d(out_c, eps=0.001, momentum=0, affine=True)
    self.relu = nn.ReLU(inplace=True)
    
  def forward(self, x):
    x = self.conv(x)
    x = self.bn(x)
    x = self.relu(x)
    return x```


### Stem_v4
```python
# Assumes 299x299x3 input
class Stem_v4(nn.Module):
  def __init__(self):
    super(Stem_v4, self).__init__()
    self.conv1 = nn.Sequential(ConvModule(3, 32, 3, isSame=False),
                               ConvModule(32, 32, 3, isSame=False),
                               ConvModule(32, 64, 3, isSame=True))
    
    self.mp2 = nn.MaxPool2d(kernel_size=3, stride=2, ceil_mode=True)
    self.conv2 = ConvModule(64, 96, 3, stride=2, isSame=False)
    # need nn.cat here
    
    self.conv3_r=nn.Sequential(ConvModule(160, 64, 3, isSame=True),
                               ConvModule(64, 64, (7, 1), isSame=True),
                               ConvModule(64, 64, (1, 7), isSame=True),
                               nn.Conv2d(64, 96, 3)
                              )
    
    
    self.conv3_l = nn.Sequential(ConvModule(160, 64, 1, isSame=True),
                                ConvModule(64, 96, 3),
                                )
    
    #need nn.cat here
    
    self.mp4 = nn.MaxPool2d(kernel_size=3, stride=2, ceil_mode=True)
    self.conv4 = ConvModule(192, 192, 3, stride=2)
    
    #also need a concat here
  
  def forward(self, x):
    x = self.conv1(x)
    
    x1 = self.mp2(x)
    x2 = self.conv2(x)
    x = torch.cat((x1, x2), 1)
    
    x1 = self.conv3_r(x)
    x2 = self.conv3_l(x)
    x = torch.cat((x1, x2), 1)
    
    x1 = self.mp4(x)
    x2 = self.conv4(x)
    x = torch.cat((x1, x2), 1)
    return x
```

### Incep-v4
```python
class IncepA_v4(nn.Module):
  def __init__(self):
    super(IncepA_v4, self).__init__()
    #in = 384 X 35 X 35
    self.module1 = nn.Sequential(ConvModule(384, 64, 1, isSame=True),
                              ConvModule(64, 96, 3, isSame=True),
                              ConvModule(96, 96, 3, isSame=True)
                              )
    
    self.module2 = nn.Sequential(ConvModule(384, 64, 1, isSame=True),
                              ConvModule(64, 96, 3, isSame=True)
                              )
    
    self.module3 = nn.Sequential(ConvModule(384, 96, 1, isSame=True))
    
    self.module4 = nn.Sequential(nn.AvgPool2d(3, stride=1, padding=1, count_include_pad=False),
                              ConvModule(384, 96, 1, isSame=True))
    
  def forward(self, x):
    x1 = self.module1(x)
    x2 = self.module2(x)
    x3 = self.module3(x)
    x4 = self.module4(x)
    
    x = torch.cat([x1, x2, x3, x4], 1)
    return x
```


### ReductA-v4
```python
class ReductA_v4(nn.Module):
  def __init__(self):
    super(ReductA_v4, self).__init__()
    #in = 384 X 35 X 35
    self.module1 = nn.Sequential(ConvModule(384, 192, 1, isSame=True),
                              ConvModule(192, 224, 3, isSame=True),
                              ConvModule(224, 256, 3, stride=2)
                              )
    
    self.module2 = nn.Sequential(ConvModule(384, 384, 3, stride=2)
                              )
    
    self.module3 = nn.MaxPool2d(3, stride=2)
    
  def forward(self, x):
    x1 = self.module1(x)
    x2 = self.module2(x)
    x3 = self.module3(x)
    
    x = torch.cat([x1, x2, x3], 1)
    return x
```


### IncepB_v4
```python
class IncepB_v4(nn.Module):
  def __init__(self):
    super(IncepB_v4, self).__init__()
    #in = 1024 X 17 X 17
    self.module1 = nn.Sequential(ConvModule(1024, 192, 1, isSame=True),
                              ConvModule(192, 192, (1, 7), isSame=True),
                              ConvModule(192, 224, (7, 1), isSame=True),
                              ConvModule(224, 224, (1, 7), isSame=True),
                              ConvModule(224, 256, (1, 7), isSame=True),
                              )
    
    self.module2 = nn.Sequential(ConvModule(1024, 192, 1, isSame=True),
                              ConvModule(192, 224, (1, 7), isSame=True),
                              ConvModule(224, 256, (7, 1), isSame=True),
                              )
    
    self.module3 = nn.Sequential(ConvModule(1024, 384, 1, isSame=True))
    
    self.module4 = nn.Sequential(nn.AvgPool2d(3, stride=1, padding=1, count_include_pad=False),
                              ConvModule(1024, 128, 1, isSame=True))
    
  def forward(self, x):
    x1 = self.module1(x)
    x2 = self.module2(x)
    x3 = self.module3(x)
    x4 = self.module4(x)
    
    x = torch.cat([x1, x2, x3, x4], 1)
    return x
```


### ReductB_v4
```python
class ReductB_v4(nn.Module):
  def __init__(self):
    super(ReductB_v4, self).__init__()
    #in = 1024 X 17 X 17
    self.module1 = nn.Sequential(ConvModule(1024, 256, 1, isSame=True),
                              ConvModule(256, 256, (1,7), isSame=True),
                              ConvModule(256, 320, (7,1), isSame=True),
                              ConvModule(320, 320, 3, stride=2, isSame=False),
                              )
    
    self.module2 = nn.Sequential(ConvModule(1024, 192, 1, isSame=True),
                                 ConvModule(192, 192, 3, stride=2, isSame=False),
                              )
    
    self.module3 = nn.MaxPool2d(3, stride=2)
    
  def forward(self, x):
    x1 = self.module1(x)
    x2 = self.module2(x)
    x3 = self.module3(x)
    
    x = torch.cat([x1, x2, x3], 1)
    return x
```


### IncepC_v4
```python
class IncepC_v4(nn.Module):
  def __init__(self):
    super(IncepC_v4, self).__init__()
    #in = 1536 X 8 X 8
    self.module1 = nn.Sequential(ConvModule(1536, 384, 1, isSame=True),
                              ConvModule(384, 448, (1, 3), isSame=True),
                              ConvModule(448, 512, (3, 1), isSame=True),
                              )
    self.module1_1 = ConvModule(512, 256, (1,3), isSame=True)
    self.module1_2 = ConvModule(512, 256, (3,1), isSame=True)
    
    
    self.module2 = ConvModule(1536, 384, 1, isSame=True)
    self.module2_1 = ConvModule(384, 256, (1,3), isSame=True)
    self.module2_2 = ConvModule(384, 256, (3,1), isSame=True)
    
    self.module3 = ConvModule(1536, 256, 1, isSame=True)
    
    self.module4 = nn.Sequential(nn.AvgPool2d(3, stride=1, padding=1, count_include_pad=False),
                              ConvModule(1536, 256, 1, isSame=True))
    
  def forward(self, x):
    x1 = self.module1(x)
    x1_1 = self.module1_1(x1)
    x1_2 = self.module1_2(x1)
    x1 = torch.cat([x1_1, x1_2], 1)
    
    x2 = self.module2(x)
    x2_1 = self.module2_1(x2)
    x2_2 = self.module2_2(x2)
    x2 = torch.cat([x2_1, x2_2], 1)
    
    x3 = self.module3(x)
    
    x4 = self.module4(x)
    x = torch.cat([x1, x2, x3, x4], 1)
    return x
```

### InceptionV4
```python
class InceptionV4(nn.Module):
  n_class = 1000
  def __init__(self):
    super(InceptionV4, self).__init__()
    
    self.layers = nn.Sequential(
        Stem_v4(),
        IncepA_v4(),
        ReductA_v4(),
        IncepB_v4(),
        ReductB_v4(),
        IncepC_v4(),
    )
    
    self.dr = torch.nn.Dropout(p=0.8, inplace=False)
    self.linear = nn.Linear(1536, self.n_class)
    
  def forward(self, x):
    x = self.layers(x)
    
    x = x.mean(dim=2, keepdim=True)     
    x = x.mean(dim=3, keepdim=True)
    
    x = self.linear(x.view(x.size(0), -1))
    return x
```

### testing
```python
model = InceptionV4()
def testIndices():
  y = model(torch.randn(1, 3, 299, 299))
  print(y.size())

testIndices()
```
