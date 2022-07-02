---
layout: post
title:  "Precision, Recall and MAP"
date:   2018-06-28 08:00:05 +0800
categories: information_theory
use_math: true
tags: map mean_average_precision precision recall information_theory detection deep_learning
---

- [참고](https://ctkim.tistory.com/79)

Suppose we are solving a detection problem.

### IOU

`IOU`: Intersection over union. IOU is calculated betweeen `ground truth` and `detection`.

<img src="{{ site.url }}/nailbrainz.github.io/images/deeplearning/map/iou.png" class="center" style="width:400px"/>


### (True/False)(Positive/Negative)


|                     |true|false|
|---------------------|-----------------------------|--------|
|positive |true positives(TP) |false positives(FP)|
|negative  |false negatives(FN)|true negatives(TN)|

<img src="{{ site.url }}/nailbrainz.github.io/images/deeplearning/map/samples_1_v2.png" class="center" style="width:700px"/>  
Percentage(%) refers to the confidence of model.

Assume that IOU threshold is 0.5. In above fig, we need to identify IOU with eyes.
* `True positive`: Correctly identified. Detection with \\(\textrm\{IOU\}\geq\textrm\{Threshold\}\\).  
EX) B of image 1
* `False positive`: Incorrectly detected. There might be some cases.
	1. Detection with  \\(\textrm\{IOU\}<\textrm\{Threshold\}\\). The box yielded by the algorithm does not match with GT.  
	EX) C of image 1
	2. Detection exceeds threshold, but  but there exists another detection with better IOU. In many cases (Including PASCAL VOC) this is considered as FN.  
	EX) D of image 2.
* `True negative`: Correctly rejected. The GT doesn't exists in some location, and the algorithm does not suggested a box near it.
* `False negative`: Incorrectly rejected. The GT exists, but a box was not suggested.  
EX) green box in image 2, upper right.


Note that,
1. \\(\textrm\{TP\}+\textrm\{FP\}=\textrm\{all detections\}\\)
2. \\(\textrm\{TP\}+\textrm\{FN\}=\textrm\{all GTs\}\\)

### Precision, Recall, Accuracy
* `Precision` \\(P\\): fraction of boxes(positives) that were true(IOU exceeds threshold) \\[P=\frac\{\textrm\{TP\}\}\{\textrm\{TP\}+\textrm\{FP\}\}=\frac\{\textrm\{TP\}\}\{\textrm\{all detections\}\}\\]  
* `Recall` \\(R\\): fraction of GT that a box(positive) is suggested \\[R=\frac\{\textrm\{TP\}\}\{\textrm\{TP\}+\textrm\{FN\}\}=\frac\{\textrm\{TP\}\}\{\textrm\{all GTs\}\}\\]  
* `Accuracy`: \\[\frac\{\textrm\{TP\}+\textrm\{TN\}\}\{\textrm\{TP\}+\textrm\{TN\}+\textrm\{FP\}+\textrm\{FN\}\}\\]

__When the accuracy is not a good measure?__  
Generally the fraction of true data are small (ex-web search engine). By assigning negative to all data, the model easily obtains high accuracy.

### Tradeoff between precision and recall
\\(P\\) and \\(R\\) clearly trade off againts one another.
* We always can get \\(R=1\\) by assigning true for all data  
__Recall is a non-decreasing function over the number of positive reports__
* However, as we reports many data as true, generally the precision goes down

> In general, we want to get some amout of recall while tolerating only a certain percentage of false positive (maintaining precision).


### F-score
\\[\textrm\{F-score\}:=\frac\{2pr\}\{p+r\}.\\]

* __Why the harmonic mean, not the arithmetic or geometric?__  
Ex) using 'return true` strategy with arithmetic mean (which gives \\(R=1,P\approx0\\)), we can always have the measure over 0.5.  
harmonic mean is always less than geometric/arithmetic mean, and close to the \\(\min(P,R)\\), which makes the return true strat ineffective.


### Precision-Recall Curve

<img src="{{ site.url }}/nailbrainz.github.io/images/deeplearning/map/pr_curve.png" class="center"/>  
(image from [1])  

If we consider the top k most confident data, then
1. \\(k=0\\): return false(negative) strat. We report nothing as positive so \\(P=1\\) by the convention (there is no wrong box), and \\(R=0\\) (Among the GT, we were failed to report any of them as positive).
\\[\vdots\\]
2. Suppose \\(k=i\\).  
* If \\(i+1\\)th confident data (which we well gonna report as positive) is false, then  
\\(R\\) remains the same, but \\(P\\) decreases
* If \\(i+1\\)th confident data is positive, then  
Both \\(R\\) and \\(P\\) increases (\\(tp\\) increases by 1 \\(\rightarrow\\) fraction become closes to 1), and the curve jags up to right.

### AP and mAP
<img src="{{ site.url }}/nailbrainz.github.io/images/deeplearning/map/20171123_195812.jpg" class="center" style="width:400px"/>  
(image from <a href="http://darkpgmr.tistory.com/162" target="_blank">http://darkpgmr.tistory.com/162</a>)

`AP`: average of maximum recall over all distinct recall values. (single category, in detection case)  
	 Note that, since the maxium of recall is 1, summing the area under PR-curve is equivalent to taking expectation. Thus the name __average__ precision.  
`mAP`: average of AP over all queries (AP averaged __for all categories__) 

Links:  
<a href="https://nlp.stanford.edu/IR-book/pdf/08eval.pdf" target="_blank">https://nlp.stanford.edu/IR-book/pdf/08eval.pdf</a>  
<a href="https://arxiv.org/ftp/arxiv/papers/1503/1503.06410.pdf" target="_blank">https://arxiv.org/ftp/arxiv/papers/1503/1503.06410.pdf</a>  
<a href="https://datascience.stackexchange.com/questions/25119/how-to-calculate-map-for-detection-task-for-the-pascal-voc-challenge" target="_blank">https://datascience.stackexchange.com/questions/25119/how-to-calculate-map-for-detection-task-for-the-pascal-voc-challenge</a>  
<a href="https://github.com/rafaelpadilla/Object-Detection-Metrics" target="_blank">https://github.com/rafaelpadilla/Object-Detection-Metrics</a>