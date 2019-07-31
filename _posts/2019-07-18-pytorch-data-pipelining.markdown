---
layout: post
title:  "Bottlenecks in Pytorch training"
date:   2019-07-18 09:00:05 +0800
categories: deep_learning
use_math: true
tags: deep_learning pytorch
---

https://discuss.pytorch.org/t/how-to-prefetch-data-when-processing-with-gpu/548/19

### toTensor() bug
toTensor seems too slow
* <a href="https://github.com/pytorch/vision/blob/master/torchvision/transforms/functional.py" target="_blank">https://github.com/pytorch/vision/blob/master/torchvision/transforms/functional.py</a>
```python
# yikes, this transpose takes 80% of the loading time/CPU
img = img.transpose(0, 1).transpose(0, 2).contiguous()
```
Seems like, aligning Pytorch tensors with its stride (`.contiguous()`) seems too slow.

<a href="https://github.com/NVIDIA/apex/blob/master/examples/imagenet/main_amp.py" target="_blank">Fast_collate</a> in `Apex` (Nvidia) bypassess this problem by using Numpy.
```python
def fast_collate(batch):
    imgs = [img[0] for img in batch]
    targets = torch.tensor([target[1] for target in batch], dtype=torch.int64)
    w = imgs[0].size[0]
    h = imgs[0].size[1]
    tensor = torch.zeros( (len(imgs), 3, h, w), dtype=torch.uint8 )
    for i, img in enumerate(imgs):
        nump_array = np.asarray(img, dtype=np.uint8)
        if(nump_array.ndim < 3):
            nump_array = np.expand_dims(nump_array, axis=-1)
        nump_array = np.rollaxis(nump_array, 2)

        tensor[i] += torch.from_numpy(nump_array)
        
    return tensor, targets
```

### GIL
- due to this, cannot use lightweighted thread synchronization. Must be dependent on multiproc sync.
- Use `native code`s as much as possible (`Numpy`!)

### io waiting
- iostat (nfsiostat)
- NVME SSD > SATA SSD
- h5py / tfrecord chunking seems not so effective, since we must perform shuffle during training
- excessive workers may result in too frequent context switch, more IO wait (meh), ...

### Pinned memory
1. Note: `pinned memory` is not in the GPU. Rather, it is in the __host memory__
2. Then why pinned memory?  
   if not pinned, due to the demaning paging, the content of memory for specific physical memory constantly changes  
   \\(\rightarrow\\) cannot use Direct Memory Access (like mmap)
3. If the system has not enough memory (especially 32bit), pinning large portion of memory could bring more deadlocks


### Profiling?
- iostats, vmstats, ...whatever