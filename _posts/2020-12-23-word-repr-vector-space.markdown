---
layout: post
title:  "Efficient Estimation of Word Representations in Vector Space"
date:   2020-12-23 08:00:05 +0800
categories: math deep_learning
use_math: true
tags: math need_review deep_learning recomm
---

- <a href="https://arxiv.org/abs/1301.3781" target="_blank">https://arxiv.org/abs/1301.3781</a>
- <a href="https://hong-yp-ml-records.tistory.com/56" target="_blank">https://hong-yp-ml-records.tistory.com/56</a>
- 



Next
- <a href="https://arxiv.org/abs/1810.04805" target="_blank">BERT (2018)</a>
- [20] words can have multiple degree of similarity <a href="https://www.aclweb.org/anthology/N13-1090/" target="_blank">Linguistic Regularities in Continuous Space Word Representations (2013)</a>
- Latent Dirichlet Allocation
- skip gram?
- hierarchical softmax

### Abstract, Intro

#### Efficient Training
- efficient training = able to work on large datasets (in 2013)
  - __simple model__ (N-gram) works on __trillions of words__
  - __complex model__ (DNN with distributed repr) are restricted to __few hundred of mills of words__, with `embed_dim` = 50~100
    - target = train complex model (using distributed repr) for __few bills of words,__ \\(\|V\|\\) = mils

#### Syntatic + Semantic
- words can have multiple degree of similarity [20]
  - "for example, nouns can have multiple word endings, and if we search for similar words in a subspace of the original vector space, it is possible to find words that have similar engings [13, 14]"
    - ex) big - bigger, big - biggest have different type of similarity
    - big - bigger, small - smaller have similar type of similarity
- `syntatic similarity` (regularity) = similar (inflectional) word endings, ...
- `semantic similarity` (regularity) = vector("King") - vector("Man") + vector("Woman") \\(\approx\\) vector("Queen")
  - some sort of linear regularities
- target = developing new architecture (?) that preserve the linear regularities among words
- new test for measuring both syntatic / semantic regularities
- shows relation between training time/acc \\(\leftrightarrow\\) embed_dim/amount of data


### Model Archs
- `LSA` : Latent Semantic Analysis
- `LDA` : Latent Dirichlet Allocation. distribution over distribution? 기억이 날듯 말듯...복습 함만 하자
  - computationally expensive


Let
\\[\text{computational complexity of a model  :=  # of params that need to be accessed during training}\\]
\\[\text{training complexity } O := E\\ \times\\ T\\ \times\\ Q \\]
where
- \\(E\\) : # of epochs
- \\(T\\) : # of words in a training set (corpus?)
- \\(Q\\) : model training complexity, defined further

#### NNLM

(refer to the `A Neural Models (in 2003)` part <a href="{{site.url}}/math/deep_learning/2020/12/21/nplm.html" target="_blank">in link here</a>)
\\[Q = N \times D + N \times D \times H + H \times V\\]
1. \\(N\times D\\) : project \\(N\\) words(one-hot) to embedding space \\(\Re^D\\)
2. \\((N \times D) \times H\\) hidden FC layer \\((N\times D)\mapsto H\\), where \\(N\times D \approx 500~2000,\quad H \approx 500~1000\\)
3. \\(H \times V\\) : hidden layer to logits. Here normally `hierarchical softmax` (with hierarchical word models) is used (balanced binary / huffman tree), so that \\(V\\) is reduced to \\(\log V\\).

In `LLML`, the computational bottlenect is the \\(N\times D\times H\\) term.

#### (CBOW) Continuous Bag-of-Words Model
- (nonlinear) hidden layer in `NNLM` was a bottleneck - remove them
- take average over \\(N\\) embeddings
\\[Q = N \times D + D \times \log\_2(V)\\]
- predict middle words (input : prev/after 4 words)


#### Continous Skip-gram Model
- If \\(C=5\\), randomly select \\(R\in \\{1, 2, 3, 4, 5\\}\\) and use \\(R\\) from history and \\(R\\) from future as label, input = current word
- in the experiment, \\(C=10\\)

\\[Q = C \times (D + D\times \log\_2(V))\\]

### Result
- as described in Abstract, words can have many different types of similarities
- we can ask : __What is the word that is similar to small in the same sense as biggest is similar to big?__
- can be used to answer __more subtle semantic rels between words__
  - e.g. Frans is to Paris as Germany is to Berlin (wtf)
  - \\(Paris - France + Italy = Rome\\)
- 5 semantic, 9 syntactic questions
- used `Google News corpus` for training the word vectors
  - too big : `proxy tasks`! (\\(\|V\| = 30k\\))
  - __adding more embed_dim solely, or adding more training data solely provides diminishing improvements__
    - they have to be increased at the same time! (2X data = 2X embed_dim)
    
#### Comparison of word archs
- `embed_dim`=640 during experiments
- training data = several `LDC corpora` (320M words, 82k vocabs)
- RNNLM, NNLM \\(<<<\\) CBOS, SKIP-GRAM
  - skip-gram had far-better semantic accuracy, but CBOS had silightly better semantic acc
- Adagrad, Distbelief, CPU


### Conclusion
- (using avged embedding) it is possible to compute very accurate high dimensional word vectors from a much larger data set