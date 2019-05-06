---
layout: post
title:  "Smooth L1 Loss"
date:   2018-07-17 08:00:05 +0800
categories: optimization
use_math: true
tags: deep_learning detection optimization
---

<img src="{{ site.url }}/images/deeplearning/smooth_l1.png" class="center" style="width:500px"/>  
\\[
\text\{smooth\}\_\{L\_1\}=\begin\{cases\}
    0.5x^2, && \text\{if \} \|x\|<1 \\\
    \|x\|-0.5, && \text\{otherwise.\}
  \end\{cases\}
\\]

> Is a robust \\(L_1\\) loss that is less sensitive to outliers.

It is a compound loss of L1 and L2.
1. Between \\([-0.5,\\>0.5])\\), it behaves like L2 loss  
\\(\leadsto\\) Smooth than L1 in \\([-0.5,\\>0.5])\\) (Less panelizes close elements than L1)
1. Otherwise, it behaves like L1 loss  
\\(\leadsto\\) Smooth than L2 in other areas (Less panelizes elements with distance than L2)

