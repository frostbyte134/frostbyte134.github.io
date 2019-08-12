---
layout: post
title:  "Mixed Precision"
date:   2019-08-12 09:00:05 +0800
categories: deep_learning
use_math: true
tags: deep_learning pytorch
---

## Training with Mixed Precision

benefits
1. require less memory
2. require less memory bandwidth
3. run much faster, especially with Tensor cores

identifies the steps that require full precision and using 32-bit floating point for only those steps while using 16-bit floating point everywhere else

1. half precision: 16bit
2. single precision: 32bit
3. double precision: 64bit

Tensor cores are in the `Volta` and `Turing`

Using mixed precision requires two steps:
1. Porting the model to use the FP16 data type where appropriate
2. Adding loss scaling to preserve small gradient values
    - values computed by large reductions should be left in FP32 (`bn` mean / variance)

