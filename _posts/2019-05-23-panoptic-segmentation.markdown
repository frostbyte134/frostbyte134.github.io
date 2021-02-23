---
layout: post
title:  "Panoptic Segmentation"
date:   2019-05-23 09:10:05 +0800
categories: deep_learning
use_math: true
tags: deep_learning panoptic_segmentation 
---

<a href="https://arxiv.org/abs/1801.00868" target="_blank">https://arxiv.org/abs/1801.00868</a>

\\[\text\{PQ\} = \frac\{\sum \_\{(p,q)\in TP\} \text\{IoU\}(p,q)\}\{\|TP\| + \frac\{1\}\{2\}\|FP\| + \frac\{1\}\{2\}\|FN\|\}\\]
`Cityscapes`, `ADE20k`, `Mapillary Vistas`

### Abstract
`Panoptic segmentation` unifies the typical distinct tasks of
* `semantic segmentation`: stuff
    * amorphous (having no definite form / distinct shape) regions of similar texture or material such as grass, sky , road
    * FCN, with dilated conv
* `instance segmentation`: things
    * countable objects such as ppl, animal, tools
    * object proposals, region-based.

Propose a novel __panoptic quality__ (`PQ`) metric that captures performance for all classes (stuff and things) in an interpretable and unified manner.

### Intro
`stuff` / `things` dichonomy (schism)

`Panoptic quality` (PQ) is _simple_ and _informative_
* unlike semantic segmentation, it requires __differentiating individual obj instances__, which poses a challenge over FCN
* Unlike instance segmentation, object segments must be __non-overlapping__

Baseline model
* we define a simple and likely sub-optimal heuristic that combines the output of two independent systems for semantic and instance segmentation via a series of (heurestic) post-processing steps that merges their outputs (in essence, _a sophisticated form of NMS_)

### Format
* \\(\mathcal\{L\}=\\{0,...,L-1\\}\\) : predetermined set of \\(L\\) __semantic classes__
* __panoptic segmentation algorithm__ : maps each pixel \\(i\\) of an image to a pair \\(l\_i,z\_i\in \mathcal\{L\}\times\mathcal\{N\}\\)
* \\(l\_i\\) semantic class of pixel \\(i\\)
* \\(z\_i\\) its instance id

Ambiguous / out-of-cls pixels can be assigned a special void label; i.e., not all pixels must have a semantic label.

#### Stuff and thing labels
The semantic label set \\(\mathcal\{L\}\\) consists of __M.E.C.E__ subsets
* \\(\mathcal\{L\}^\{St\}\\) : stuff. When a pixel is labeled with \\(l\_i\in \mathcal\{L\}^\{St\}\\), its instance id \\(z\_i\\) is irrelevant.
* \\(\mathcal\{L\}^\{Th\}\\) : Things. All pixels belonging to the same isntance must have the same \\((l\_i, z\_i)\\).

Relationship (in terms of format) with other tasks
* semantic segmentation : the `PS` is a strict generalization fo the format for semantic segmentation
* instance segmentation : it allows overlapping segments, whereas the PS task permits only one semantic label and on inst id to be assigned to each pixel.
* confidence score: PS requires no confidence score, but it could be useful to some tasks

### PS metric
1. Segment matching  
We specify that a predicted segment and a GT segment can match only if their IoU is strictly greater than 0.5
    1. there can be only one predicted segment with each ground truth segment (Theorem 1)  
    For \\(\text\{IoU\}\geq 0.5\\), any matching (including greedy one) will find the only one unique and valid matching.
    2. After the matching, each blobs (predicted and GT) are divided into 3 sets 
        * `TP` : matched ones, with IoU >= 0.5.
        * `FP` : prediction - gt matched with Iou >= 0.5, but the semantic label is not true
        * `FN` : no valid matching prediction of GT
2. PQ computation
\\[\text\{PQ\} = \frac\{\sum \_\{(p,q)\in TP\} \text\{IoU\}(p,q)\}\{\|TP\| + \frac\{1\}\{2\}\|FP\| + \frac\{1\}\{2\}\|FN\|\}\\]
Note that,
    1. \\(\frac\{1\}\{\|TP\|\}\sum \_\{(p,q)\in TP\} \text\{IoU\}(p,q)\\) is the average IoU of matched segments (not the MIoU!)
    2. \\(\frac\{1\}\{2\}\|FP\| + \frac\{1\}\{2\}\|FN\|\\) is added to the denominaator to penalize segments without matches. Note that __all segments recive equal imortance regardless of their area__
    3. PQ can be divided into
    \\[\text\{PQ=SQ(segmentaion quality\}\times\text\{RQ(recognition quality)\}\\]
    \\[PQ=\frac\{\sum \_\{(p,q)\in TP\} \text\{IoU\}(p,q)\}\{\|TP\| \}\times\frac\{\|TP\|\}\{\frac\{1\}\{2\}\|FP\| + \frac\{1\}\{2\}\|FN\|\}\\]
    Written this way, \\(RQ\\) i the familiar \\(F\_1\\) score, \\(SQ\\) is the average IoU of matched segment (since it only counts the matched segment, is not eqivalent to the MIoU)
4. Void Labels  
    = out of class pixels / ambiguous or unknown pixels. As often we cannot differentiate these two cases, wo don't evaluate prediction for void pixels. Namely,
    1. during matching, all pixles in a predicted segment that are labeled as void in the GT are removed from the prediction, and do not affect IoU computation
    2. after matching, unmatched predicted segments that contain a fraction of void pixels over the matching threshold are removed, and do not count as FP.
    3. outputs (of prediction?) may also contain void pixels; these do not affect eval.
4. Group labels  
    not considered

* PQ treats all classes (stuff and things) in a uniform way
* PQ is not a combination of semantic / inst segmentation metrics
* Rather, SQ and RQ are computed for every cls (stuff and things), and measure segmentation and recogition quality, respectively. __PQ thus unifies evaluation over all classes__

### Human perception
- For Cityscapes and ADE20k human consistency for stuff and things are close, on Vistas the gap is a bit larget. Overall, this implies stuff and things have similar difficulty (in terms of SQ, RQ)

IOU theshold : if below 0.5, `bipartite matching` can return a matching which maximizes the sum of IoUs

### Baseline MOdel
- Mask R-CNN +  PSPNet (on Cityscapes)

To integrate two models, we develop a simple non-maximum suppression (NMS)-like procedure. (Heuristic combination) (matching instance box - class segmentation)
1. sort the predicted segments by their confidence scores
2. remove instances with low scores.
3. iterate over sorted instances, starting from the most confident.
4. for each instance, we first remove pixels which have been assigned to prev segments.
5. Then, if a sufficient fraction of the segment remains, accept the non-overlaping portion, otherwise we discard the entire segment.

All thresholds are selected by grid search to optimize PQ.