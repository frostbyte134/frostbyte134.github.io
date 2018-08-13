---
layout: post
title:  "A Bayesian Perspective on Generalization and Stochastic Gradient Descent"
date:   2018-08-12 08:00:05 +0800
categories: deep_learning
use_math: true
tags: deep_learning SGD bayesian
---

<a href="https://arxiv.org/pdf/1804.06516.pdf" target="_blank">https://arxiv.org/pdf/1804.06516.pdf</a>  


### Bayesian Model Comparison
Let 
* \\(M\\): classification model
* \\(w\\): weight of \\(M\\)
* \\((x,y)\\): input / output

Then,
\\[\text\{Posterior over \}w\\>\propto\text\{ likelihood \}\times\text\{ prior\}\\]
\\[P(w|y,x;M)=\frac\{
P(y|w,x;M)\times P(w;M)
\}
\{
P(y|x;M)
\}
\\]

With the i.i.d assumption of inputs, the __likelihood__ becomes
\\[P(y|w,x;M)=\prod\_iP(y\_i|w,x\_i;M)\\]
\\[=\prod\_i\exp\\{\ln\{P(y\_i|w,x\_i;M)\}\\}\\]
\\[\exp\\{\sum\_i\{\ln\{P(y\_i|w,x\_i;M)\}\}\\}\\]
and we let
\\[P(y|w,x;M)=\text\{Likelihood of w\}=e^\{-H(w;M)\}, \text\{ where \}H(w;M):=-\sum\_i\{\ln\{P(y\_i|w,x\_i;M)\}\}\\]

Right term is a __Gaissian prior__ (\\(\lambda\\) is a precision (=inverse of variance))
\\[P(w;M)=\sqrt\{\frac\{\lambda\}\{2\pi\}\}e^\{-\lambda\frac\{w^2\}\{2\}\}\\]

Then the __posterior__ is proportional to
\\[P(w|y,x;M)\propto\{e^\{-H(w;M)\}\times \}\sqrt\{\frac\{\lambda\}\{2\pi\}\}e^\{-\lambda\frac\{w^2\}\{2\}\}\\]
\\[=\sqrt\{\frac\{\lambda\}\{2\pi\}\}e^\{-(H(w;M)+\lambda\frac\{w^2\}\{2\})\}\\]
By defining \\(C(w;M):=H(w;M)+\lambda\frac\{w^2\}\{2\}\\) (__L2 regularized cross entropy__ (cost function)), we obtain
\\[P(w|y,x;M)=\frac\{\sqrt\{\frac\{\lambda\}\{2\pi\}\}e^\{-C(w;M)\}\}\{P(y|x;M)\}\\]

We also define 
* \\(w_0 :=\\) __optimal weight__ which maximizes the cost function (equivalent to maximizing the posterior)

To predict an unknown label \\(y_t\\) given \\(x_t\\) and training data / model,
\\[P(y_t|x_t,y,x;M)=\int\{P(y_t,w|x_t,y,x;M)dw\}\\]
Note that, with the (somewhat) strong independent assumption between \\(w, (x,y), (x_t,y_t)\\), the inner term becomes
\\[P(y_t,w|x_t,y,x;M)=\frac\{P(y_t,x_t,w,y,x;M)\}\{P(x_t,y,x;M)\}\\]
\\[=\frac\{P(y_t,w,x_t;M)P(y,x;M)\}\{P(x_t,y,x;M)\}\\]
\\[=\frac\{P(y_t,w,x_t;M)P(y,x;M)P(w,x_t;M)\}\{P(w,x_t;M)P(x_t,y,x;M)\}\\]
\\[=\frac\{P(y_t,w,x_t;M)P(w,y,x;M)\}\{P(w,x_t;M)P(y,x;M)\}\\]
\\[=P(y_t|w,x_t;M)P(w|y,x;M)\\]


We have calculated the right term \\(P(w|y,x;M)=\frac\{\sqrt\{\frac\{\lambda\}\{2\pi\}\}e^\{-C(w;M)\}\}\{P(y|x;M)\}\\) above. To deal with the normalization term \\(P(y|x;M)\\), using the above results and marginalization,
\\[\int{P(w|y,x;M)}dw=1\\]
\\[\int{P(w|y,x;M)}dw=1\\]
\\[\int{\frac\{\sqrt\{\frac\{\lambda\}\{2\pi\}\}e^\{-C(w;M)\}\}\{P(y|x;M)\}}dw=1\\]
\\[\frac\{1\}\{P(y|x;M)\}\int{\sqrt\{\frac\{\lambda\}\{2\pi\}\}e^\{-C(w;M)\}}dw=1\\]
\\[P(y|x;M)=\sqrt\{\frac\{\lambda\}\{2\pi\}\}\int{e^\{-C(w;M)\}}dw\\]
Therefore the prediction becomes
\\[P(y_t|w,x_t,y,x;M)=\int\{P(y_t|x_t;M)P(w|y,x;M)dw\}\\]
\\[=\int\{P(y_t|w,x_t;M)\frac\{\sqrt\{\frac\{\lambda\}\{2\pi\}\}e^\{-C(w;M)\}\}\{P(y|x;M)\}dw\}\\]
\\[=\frac\{\sqrt\{\frac\{\lambda\}\{2\pi\}\}\}\{P(y|x;M)\}\int\{P(y_t|w,x_t;M)e^\{-C(w;M)\}dw\}\\]
\\[=\frac\{\sqrt\{\frac\{\lambda\}\{2\pi\}\}\}\{\sqrt\{\frac\{\lambda\}\{2\pi\}\}\int{e^\{-C(w;M)\}}dw\}\int\{P(y_t|w,x_t;M)e^\{-C(w;M)\}dw\}\\]
\\[=\frac\{\int\{P(y_t|w,x_t;M)e^\{-C(w;M)\}dw\}\}\{\int{e^\{-C(w;M)\}}dw\}\tag\{3\}\\]
However, 
* these integrals are dominated by the (maximum) regin near \\(w_0\\) (isn't it too rough?), and since \\(P(y_t\|w,x_t;M)\\) is smooth (at least in deep learning, we never use models with discontinuity), we usually approximate so we approximate \\[\frac\{\int\{P(y_t\|w,x_t;M)e^\{-C(w;M)\}dw\}\}\{\int{e^\{-C(w;M)\}}dw\}=\frac\{P(y_t\|w_0,x_t;M)e^\{-C(w_0;M)\}\}\{e^\{-C(w_0;M)\}}=P(y_t\|w_0,x_t;M)\\]

Notice that the evidence

### Abstract

* To handle the variability in real-world data, the system relies upon the technique of `domain randomization`, in which the parameters of the simulator - such as lighting, pose, object textures, etc. - are randomized in non-realistic ways to force the network to learn the essential features of the object of interest.
* With additional fine-tuning on real data, the network yields better performance than using real data alone.
* ...evaluated on bnding box detection of cars on the KITTI dataset.


### (1) Introduction

* In particular, the expense required to generate photo-realistic quality negates the primary selling point of synthetic data, namely, that arbitrarily large amounts of labeled data are available essentially for free.
* To solve this problem, `domain randomization` [32] is a recently proposed inexpensive approach that intentionally abnandons photorealism by randomly perturbing the environment in non-photorealistic ways (e.g., by adding random textures) __to force network to learn to focus on the seesntial features of the image__.

... `DR` has been successful in 
* determining the control commands of an indoor quadcopter [28]
* detecting the 3D coordinates of homogeneously colored cubes on a table [32]
* optical flow [4] and scene flow [18]

Our `DR`-based car detector achieves better results on the KITTI dataset than the same architecture trained on virtual KITTI [7], even though the latter dataset is highly correlated with the test set.

Furthermore, augmenting synthetic `DR` data by fine-tuing on real data yields better results than training on real KITTI data alone.


### (2) Previous Works

Hinterstoisser _et al._ [11] used synthetic data generated by adding Gaussian noise to the object of interest and Guassian blurring the object edges before composing over a black-ground image. The resulting synthetic data are used to train the later layers of a neural network while freezing the early layers pretrained on real data (e.g., ImageNet). In constract, we found this approach of __freezing the weights to be harmful rather than helpful, as shown later.__ (think freezing weight was effective in [11] since it didn't used `DR`. Networks trained with DR need to _narrow its scope_(?) considerably to adjust on real test data)

The work of Johnson-Robertson _et al._ [15] used __photorealistic synthetic data to train a car detector that was tested on the KITTI dataset.__ This work is colsely related to ours, with the __primary difference__ being our use of DR rather than photorealistic images. 
* Our experimental results reveal a similar conclusion, namely, __that synthetic data can rival, and in some cases beat, real data for training nueral networks__.
* Moreover, we show clear benefit from __fine-tuning on real data after training on synthetic data.__

### (3) Domain Randomization

Fig.1 - processes
1. Begin with 3D models of object of interest
2. A random # of these ojects are placed in a 3D scene at random positions and orientations
3. To better enable the network to learn to ignore objects in the scene that are not of interest, a random number of gemoetric shapes are added to the scene. We call these __flying distractors__
4. Random textures are than applied to both the objects of interest and the flying distractors.
5. A random number of lights of different types are inserted at random locations, and the scene is rendered from a random camera viewpoint, after  which the result is composed over a random bg image.
6. The resulting image with automatically generated GT label is used for training.

Details of above is in the paper. Used an internally created plugin to the `Unreal Engine 4`, outputing 1200 X 400 images with annotations at 30Hz.

Although our crude (and amlost cartoonish) images are not as aesthetically pleasing (compared to VKITTI), this apparent limiation is arguably an asset:
* our images are order of magnitude faster to created (with less expertise)
* include variations that force the ddep neural network to focus on the important structure of the problem at hand, rather than details that may or may not be present in real images at test time.


### (4) Evaluation - no real images during training
1. Training: `VKITTI` vs `DR`, on (`Faster-RCNN`, `R-FCN`, `SSD`)  
(All 3 detector used <a href="{{site.url}}/deep_learning/2018/06/23/inceptionv4-resnet-residualconn.html" target="_blank">Inception-Resnet V2</a>, imagenet pretrained)  
For all architectures, training was stopped when performance on the test set saturated to __avoid overfitting.__
2. Testing: 500 images from `KITTI` dataset, __IOU 0.5__
	* `DR` dataset: 100K images, no more than __14 cars__ in a frame __(36 models)__, 8k random textures
	* `VKITTI` dataset: 2.5k images, Unity 3D. High correlation with `KITTI` dataset (need speciality / care)

__Data Augmentation:__
	- random (brightness / contrast / Gaussin noise)  
	- `classical augmentations`: random (flips / resizing), box jitter and random crop.


__Minimum bnding box:__
	- considered __bnding boxes with height greater than 40 pixels__, and __truncation lower than 0.15__, as in [8] (KITTI, "easy difficulty" setting, http://www.cvlibs.net/datasets/kitti/eval_object.php ).  


__Machine__:
	- DGX, batch 4

__Results:__

|Architecture|VKITTI  |DR      |
|------------|--------|--------|
|Faster-RCNN |__79.7__|78.1    |
|R-FCN       |64.6    |__71.5__|
|SSD         |36.1    |__46.3__|

Although `DR` images are easy to generate, obtained somewhat competitive results
	\\(\rightarrow\\) simple technique of `DR` bridged the reality gap (Remember that, DR trained model never seen a real car image, beside the imagenet pretraining)

__PR Curve__:

<img src="{{ site.url }}/images/deeplearning/ssg/dr-pr.png" class="center" style="width:500px"/>
	- For high recall, VKITTI is better.
> We hypothesize that our simplified DR procedure prevents some variations observed in the test set from being genrerated. For example, image context is ignored by our procedure, so that the structure inherent in parked cars is not taken into account. (thus problematic in high recall?)


### (4) Evaluation - fine tuning with real images
* lr: 1/10 decreased while keeping the rest of the hyperparameters unchanged, 
* gradient was allowed to fully flow from end-to-end
* Faster R-CNN network trained until convergence. 

<img src="{{ site.url }}/images/deeplearning/ssg/finetune-pr.png" class="center" style="width:500px"/>

Fig. 6. (For comparison, the figure also shows results after
training only on real images at the original learning rate of
0.0003.) 


> Note that DR surpasses VKITTI as the number of real images increases, likely due to the fact that the advantage
of the latter becomes less important as real images that resemble the synthetic images are added. With fine-tuning
on all 6000 real images, our DR-based approach achieves an AP score of 98.5, which is better than VKITTI by 1.6%
and better than using only real data by 2.1%.

### (4)-2. Ablation
Faster-RCNN with Resnet V1, 50K `DR` images, lr 0.3, momentum 0.0003, testing with AP@0.5 on `KITTI`.

AP - 73.64
* no light augmentation: 67.6 (????)
* No random texture: 69.0  
	half (4K) textures: 71.500
* Data augmentation: 72.0
	- random contrast, brighness, crop, flip, resizing, additive Guassian noise
* Flying distractor: 72.5

### (4)-3 Pretraining
* Faster-RCNN + Resnet V2
* COCO pretraining 

|COCO|COCO+VKITTI|COCO+DR |
|-----------|--------|--------|
|56.7|79.7\\(\rightarrow\\)79.7|78.1\\(\rightarrow\\)83.7|

* Although COCO includes car images, not that good with COCO only.  
\\(\rightarrow\\) networks today often fail to transfer from one dataset to another.  
> Synthetic data, and in particular DR, has the potential to overcome this problem, by enabling the network to learn features that are invariant to the specific dataset (????). 

### (4)-3 Freezing Weights
In main experiment, freezed imagenet trained feature extractor, and trained left part of `Faster R-CNN` or `R-FCN` (__no__ `SSD`)  
\\(\rightarrow\\) Degraded AP by 13.50  
\\(\rightarrow\\) With the variarity of DR images (obtained by randomization), the target domain of input image is large (but low avg accuracy). It has to be fine-tuned in comparably large scale, compared to the imagenet pretrained networks.

### (4)-3 Dataset Size
Contrary to [20] (Pretraining is useless when we have masssive synthetic images), Pretraining was helpful even up to 1M images.

> This result can be explained by the fact that our training images are not photo-realistic.



Links:  
<a href="https://arxiv.org/abs/1710.10710" target="_blank">[11] (Freezing Weights) On pre-trained image features and synthetic images for deep learning</a>  
<a href="http://vladlen.info/papers/playing-for-data.pdf" target="_blank">[26] (GTA5) Playing for data: Ground truth from computer games, in ECCV, 2016</a>  
<a href="https://arxiv.org/abs/1605.06457" target="_blank">[7] (VKITTI) Virtual Worlds as Proxy for Multi-Object Tracking Analysis, In CVPR, 2016</a>  