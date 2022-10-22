---
layout: post
title:  "Resnet (pytorch 0.4.0)"
date:   2018-07-25 08:00:05 +0800
categories: deep_learning
use_math: true
tags: deep_learning resnet bottleneck basenet
---

### "SAME" convolution in tensorflow 
as for the padding size \\(k-1\\), refer to <a href="{{site.url}}/deep_learning/2018/07/11/conv-size.html" target="_blank">`here`</a>
Note that, the (a, b) padding of nn.Conv2d adds (2*a) on width, and (2*b) on height (on each side)

```python
def sameConv(in_c, out_c, k_size=3, stride=1):
  pad_total = k_size-1 # Refer to the formula in the blog
  # https://deep_learning/2018/07/11/conv-size.html
  
  pad = pad_total // 2 # if not divisible by 2, can't handle
  
  # Note that, the (a, b) padding of nn.Conv2d adds 
  # (2*a) on width, and (2*b) on height (on each side)
  return nn.Conv2d(in_c, out_c, k_size, stride=stride, 
                   padding=pad,bias=False)
```


### Block module (2 conv opers)
```python
class ResnetBlockModule(nn.Module):
  
  def __init__(self, cin_size, cout_size, k_size=3, stride=1, resMult=0.3):
    super(ResnetBlockModule).__init__()
    self.resMult = resMult
    
    self.conv1 = sameConv(cin_size, cout_size, k_size, stride)
    # 1by1 conv, (c_size//4 if first else c_size) to c_size//4
    self.bn1 = nn.BatchNorm2d(cout_size, momentum=0.01)
    
    self.conv2 = sameConv(cout_size, cout_size, k_size)
    # 1by1 conv, (c_size//4 if first else c_size) to c_size//4
    self.bn2 = nn.BatchNorm2d(cout_size, momentum=0.01)
    self.isDownSample = stride is not 1 or cin_size != cout_size
    
    if self.isDownSample:
      self.downSample = nn.Sequential(
        sameConv(cin_size, cout_size, 1, stride=stride),
        nn.BatchNorm2d(cout_size)
      )
    
  def forward(self, x):
    shortcut = x
    if self.isDownSample:
      '''
      Zero padding at paper.
      shortcut = torch.nn.functional.pad(x, (0, 0, 0, 0, 0, (self.c_size//4)*3))
      # (a, b, c, d, e, f) over (1, 2, 3, 4) 
      # applies paddinf (a, b), (c, d), (e, f) so that
      # (1, e+2+f, c+3+d, a+4+b)
      # Thus, above padding adds (self.c_size//4)*3) over the channel. 
      # -> Zero padding (C?) of the resnet paper
      
      # Consider replacing zero padding with 1x1 embedding to larger channel
      '''
      shortcut = self.downSample(x)
    
    x = self.conv1(x)
    x = self.bn1(x)
    x = F.relu(x)
    
    x = self.conv2(x)
    x = self.bn2(x)
    x = F.relu(x)
    x = x + self.resMult * shortcut
    return x
```

### Bottleneck Module (3 conv opers)
```python
class BottleneckModule(nn.Module):
  def __init__(self, cin_size, cout_size, k_size=3, stride=1, resMult=0.3):
    super(BottleneckModule, self).__init__()
    self.resMult = resMult
    
    self.conv1 = sameConv(cin_size, cout_size//4, 1, stride)
    self.bn1 = nn.BatchNorm2d(cout_size//4, momentum=0.01)
    
    self.conv2 = sameConv(cout_size//4, cout_size//4, k_size, stride=1)
    self.bn2 = nn.BatchNorm2d(cout_size//4, momentum=0.01)
    
    self.conv3 = sameConv(cout_size//4, cout_size, 1, stride=1)
    self.bn3 = nn.BatchNorm2d(cout_size, momentum=0.01)
    
    self.isDownSample = stride is not 1 or cin_size != cout_size
    
    if self.isDownSample:
      self.downSample = nn.Sequential(
        sameConv(cin_size, cout_size, 1, stride=stride),
        nn.BatchNorm2d(cout_size)
      )
    
  def forward(self, x):
    shortcut = x
    if self.isDownSample:
      '''
      Zero padding at paper.
      shortcut = torch.nn.functional.pad(x, (0, 0, 0, 0, 0, (self.c_size//4)*3))
      # (a, b, c, d, e, f) over (1, 2, 3, 4) 
      # applies paddinf (a, b), (c, d), (e, f) so that
      # (1, e+2+f, c+3+d, a+4+b)
      # Thus, above padding adds (self.c_size//4)*3) over the channel. 
      # -> Zero padding (C?) of the resnet paper
      
      # Consider replacing zero padding with 1x1 embedding to larger channel
      '''
      shortcut = self.downSample(x)
    x = self.conv1(x)
    x = self.bn1(x)
    x = F.relu(x)
    
    x = self.conv2(x)
    x = self.bn2(x)
    x = F.relu(x)
    
    x = self.conv3(x)
    x = self.bn3(x)
    return x + self.resMult * shortcut
```


### Main resnet
```python
class Resnet(nn.Module):
  n_class = 1000
  def __init__(self, block, bneckBlock, beg_ch, factor, numLayers):
    super(Resnet, self).__init__()
    
    self.conv1 = sameConv(3, beg_ch, k_size=3, stride=2)
    self.bn1 = nn.BatchNorm2d(beg_ch, momentum=0.01)
    self.mp1 = nn.MaxPool2d(kernel_size=3, stride=2, padding=0, ceil_mode=True)
    
    self.conv2 = nn.Sequential(*(
      [bneckBlock(beg_ch, beg_ch*4)] +
      [bneckBlock(beg_ch*4, beg_ch*4) for i in range(1, numLayers[0])]
    ))
    
    self.conv3 = nn.Sequential(*(
      [bneckBlock(beg_ch*4, beg_ch*8, stride=2)] +
      [bneckBlock(beg_ch*8, beg_ch*8) for i in range(1, numLayers[1])]
    ))
    
    self.conv4 = nn.Sequential(*(
      [bneckBlock(beg_ch*8, beg_ch*16, stride=2)] +
      [bneckBlock(beg_ch*16, beg_ch*16) for i in range(1, numLayers[2])]
    ))
    
    self.conv5 = nn.Sequential(*(
      [bneckBlock(beg_ch*16, beg_ch*32, stride=2)] +
      [bneckBlock(beg_ch*32, beg_ch*32) for i in range(1, numLayers[2])]
    ))
    
    self.linear1 = nn.Linear(beg_ch*32, self.n_class)
    
    for m in self.modules():
      if isinstance(m, nn.Conv2d):
        torch.nn.init.xavier_normal_(m.weight)
      elif isinstance(m, nn.BatchNorm2d):
        nn.init.constant_(m.weight, 0)
        nn.init.constant_(m.bias, 1)
    
  def forward(self, x):
    
    out = self.conv1(x)
    
    out = self.bn1(out)
    out = F.relu(out)
    out = self.mp1(out)
    out = self.conv2(out)
    out = self.conv3(out)
    out = self.conv4(out)
    out = self.conv5(out)
    
    out = out.mean(dim=2, keepdim=True)     
    out = out.mean(dim=3, keepdim=True)
      
    out = self.linear1(out.view(out.size(0), -1))
    return out
```


### Testing
```python
model = Resnet(ResnetBlockModule, BottleneckModule, 64, 2, [3, 4, 6, 3])
def testIndices():
  y = model(torch.randn(1, 3, 224, 224))
  print(y.size())

testIndices()
```