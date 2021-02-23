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

<a href="https://pytorch.org/docs/stable/distributed.html#basics" target="_blank">From the official pytorch documentation,</a>
> In the single-machine synchronous case, torch.distributed or the torch.nn.parallel.DistributedDataParallel() wrapper may still have advantages over other approaches to data-parallelism, including torch.nn.DataParallel():  
* Each process maintains its own optimizer and performs a complete optimization step with each iteration. While this may appear redundant, since the gradients have already been gathered together and averaged across processes and are thus the same for every process, this means that no parameter broadcast step is needed, reducing time spent transferring tensors between nodes.  
* Each process contains an independent Python interpreter, eliminating the extra interpreter overhead and “GIL-thrashing” that comes from driving several execution threads, model replicas, or GPUs from a single Python process. This is especially important for models that make heavy use of the Python runtime, including models with recurrent layers or many small components.  

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


### Graceful termination of child workers
The workers of `dataloader` are __daemonic__
* at the termination (of main process), all daemonic processes are terminated with SIGTERM
* however, it will happen only when the process exits gracefully -> this is where all the <defunts> generated  (Not 100% sure)


### Basics
1. 가장 비싼 장비 - GPU. 따라서 GPU Utilization을 올려야 함 (실제로 wall-clock time과도 비례)
2. filesystem
    * IO-scheduling
        - severe random access (from shuffling)때문에, 스케쥴링은 효과X
        - 그리고 대부분 NFS위인데, NFS에서는 스케쥴링도 없음
        - 쓴다해도 No-OP (contiguous한경우에 병합만 하고, 예측 등은 안함)이 젤 좋음
    * Chunks
        - dgx-1환경에서는 무쓸모. 실제로 대부분의 메모리가 page-cache로 활용되기 때문. 초반 로딩에는 의미가 좀 있을지도...
3. GIL
    * multi-process (distributed launch, 1 gpu - 1 python)
    * Torch script - JIT? <a href="https://github.com/pytorch/pytorch/issues/17614" trarget="_blank"> (YOU CAN TRAIN TORCH MODEL IN C++ WITH TORCH SCRIPT!) </a>
    * use
4. FP16
   1. loss scaling. add post
5. DMA (pin_memory): cat /proc/buddyinfo?