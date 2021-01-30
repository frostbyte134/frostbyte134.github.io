---
layout: post
title:  "Information Theory Intro"
date:   2021-01-30 09:00:05 +0800
categories: probability
use_math: true
tags: math probability bandit information_theory
---


- <a href="https://banditalgs.com/2016/09/22/optimality-concepts-and-information-theory/" target="_blank">https://banditalgs.com/2016/09/22/optimality-concepts-and-information-theory/</a>  
- 옛날에 책이 어디 있었는데...

### Entropy

For a discrete (wlog?) distribution induced by a discrete RV \\(X \in [N] \\),
\\[H(p) := \sum\_i p\_i\log\frac{1}{p\_i}\\]

1. can be thought of a __optimal average code length__ wrt `Huffman coding`
   1. If \\(p\_i\\) occurs frequently, its code length must be short
   2. For \\(i,j, \text{len}(p\_i) < \text{len}(p\_j)\\), \\(p\_i\\) must not be the prefix of \\(p\_j\\)
2. can be thought as a __average uncertainty (=suprise)__ of the distribution \\(P\_X\\)
   1. When \\(P(X=i)=1\\), there is no uncertainty here.
   2. When \\(X\\) is discrete uniform, we are equally suprised, and the uncertainty is maximized.
   3. Since \\(\lim\_{x\rightarrow 0}x\log x=0\\), we adopt the convention that \\(0\log\frac{1}{0}=0\\)

> Information = Optimal code length per symbol = Uncertainty

### Relative Entropy (aka KL-divergence)

\\[\begin{align\*} 
D(p, q) &:= \sum\_i p\_i\log\frac{1}{q\_i} - \sum\_i p\_i\log\frac{1}{p\_i} \cr
        &= \sum\_i p\_i\log\frac{p\_i}{q\_i}
\end{align\*} \\]

Two interpretations
- How surprised one should be on average, when observing a RV \\(X\\) whose distribution is \\(P\\), when one expected that \\(X \sim Q\\).
- information contained in observing \\(X \sim P\\), relative to one's apriori expect that \\(X\sim Q\\)
 
- \\(\sum\_i p\_i\log\frac{1}{q\_i}\\) : average code length of the distribution \\(Q\\), when we take average wrt \\(P\\)
  - we were expecting the distribution \\(Q\\), but observed \\(P\\) and took average on it


#### Continuous P, Q

In case of continuous distributions \\(P, Q\\),
\\[D(P, Q) := \sup\_{f}D(P_f, Q_f)\\]
where the superemum is over the "discretization" of \\(P, Q\\)


### Densities, Radon-Nykodim derivatives
Given distributions \\(P, Q\\), the `density` __of__ \\(P\\) __with respect to__ \\(Q\\) is defined as a \\(\mathcal{F/B}\\)-measurable mapping (same definition as the random variable!) \\(f : \Omega \mapsto [0, \infty)\\) such that for all \\(A\in \mathcal{F}\\),

\\[\int_A f(\omega) dQ(\omega) = P(A)\\]

Recalling that \\[P(A) = \int\_AdP(w)\\], we woud write above as \\[fdQ = dP\\] meaning that if we integrate tis equality over any set \\(A\\), we will get identity.

Based on the above shorthand notation, we write the `density` of \\(P\\) wrt \\(Q\\) as
\\[f=\frac{dP}{dQ}\\]

Few things to note
- generally, e.g. for standard normal RV, the density is
  \\[g(x)=\frac{1}{\sqrt{2\pi}}\exp(-x^2/2)\\]
  which is \\(\mathcal{F/B}\\)-measurable (\\(\mathcal{B}\\) : Borel measure over the real line)
- the `chain rule` also holds, if the absolute continuity condition holds


Based on the Radon-Nyukodim theorem (refer to the link), the KL-divergence is formally defined as
\\[
D(P, Q) =
\begin{cases} 
 \int \log \left(\frac{dP}{dQ}(\omega)\right) dP(\omega)\,, & \text{if } P \ll Q\,; \cr 
 +\infty\,, & \text{otherwise}\,. 
\end{cases}    
\\]

and using the chain rule and \\[p=\frac{dP}{d\lambda}, q=\frac{dQ}{d\lambda}\\] where \\(\lambda\\) is the legesgue measure, we obtain the usual (informal) definition of the KL-divergence

