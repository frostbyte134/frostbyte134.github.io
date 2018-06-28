---
layout: post
title:  "Precision, Recall and MAP"
date:   2018-06-28 08:00:05 +0800
categories: information_theory
use_math: true
tags: map mean_average_precision precision recall information_theory
---

Suppose we are solving a binary classification problem.

### (True/False)(Positive/Negative)

|                     |true|false|
|---------------------|-----------------------------|--------|
|positive |true positives(tp) |false positives(fp)|
|negative  |false negatives(fn)|true negatives(tn)|

(positive: reported true by the binary classifier)

### Precision, Recall, Accuracy
* `Precision`: fraction of positive data were true \\[P=tp/(tp+fp)\\]  
* `Recall`: fraction of true data that is reported positive \\[R=tp/(tp+fn)\\]  
* `Accuracy`: \\((\textrm\{tp\}+\textrm\{tn\})/(\textrm\{tp\}+\textrm\{tn\}+\textrm\{fp\}+\textrm\{fn\})\\)

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

<img src="{{ site.url }}/images/deeplearning/pr_curve.png" class="center"/>  
(image from [1])  

If we consider the top k most confident data, then
1. \\(k=0\\): return false(negative) strat. We report nothing as positive so \\(P=0\\) by the convention, and \\(R=0\\) (Among the true data, we were failed to report any of them as positive).
\\[\vdots\\]
2. Suppose \\(k=i\\).  
* If \\(i+1\\)th confident data (which we well gonna report as positive) is false, then  
\\(R\\) remains the same, but \\(P\\) decreases
* If \\(i+1\\)th confident data is positive, then  
Both \\(R\\) and \\(P\\) increases (\\(tp\\) increases by 1 \\(\rightarrow\\) fraction become closes to 1), and the curve jags up to right.

### AP and mAP
<img src="{{ site.url }}/images/deeplearning/20171123_195812.png" class="center"/>  
`AP`: average of maximum recall over all distinct recall values.
`mAP`: average of AP over all queries

Links:  
<a href="https://nlp.stanford.edu/IR-book/pdf/08eval.pdf" target="_blank">https://nlp.stanford.edu/IR-book/pdf/08eval.pdf</a>  
<a href="https://arxiv.org/ftp/arxiv/papers/1503/1503.06410.pdf" target="_blank">https://arxiv.org/ftp/arxiv/papers/1503/1503.06410.pdf</a>  
<a href="https://datascience.stackexchange.com/questions/25119/how-to-calculate-map-for-detection-task-for-the-pascal-voc-challenge" target="_blank">https://datascience.stackexchange.com/questions/25119/how-to-calculate-map-for-detection-task-for-the-pascal-voc-challenge</a>  
<a href="https://github.com/rafaelpadilla/Object-Detection-Metrics" target="_blank">https://github.com/rafaelpadilla/Object-Detection-Metrics</a>