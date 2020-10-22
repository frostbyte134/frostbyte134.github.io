---
layout: post
title:  "MLC"
date:   2020-09-01 09:10:05 +0800
categories: math
use_math: true
tags: math
---

keywords, TODO
- multi-label classification
  - K-NN, LDA, least-square, logistic
- Word embedding
  - sentence embedding





A/B 데이터에서, A/B를 어떻게 쪼갤 것인가?

### Glossary
- documents - sentence들이 있는 문서
- corpus - set of documents
- 

### Word embedding
- <a href="https://www.analyticsvidhya.com/blog/2017/06/word-embeddings-count-word2veec/" target="_blank">https://www.analyticsvidhya.com/blog/2017/06/word-embeddings-count-word2veec/</a>p

`Frequency based Embedding`
- Count Vector : construct a matrix (row = terms, col - documents)
- TF-IDF Vector
  - Ideally, what we would want is to down weight the common words occurring in almost all documents and give more importance to words that appear in a subset of documents.
  - TF = (Number of times term t appears in a document)/(Number of terms in the document)
    - eg: A document about Messi should contain the word ‘Messi’ in large number.
  - IDF = log(N/n), where, N is the number of documents and n is the number of documents a term t has appeared in.
    - so, the IDF of common words should be low
  - TF-IDF : TF X IDF
- Co-Occurrence Vector

- <a href="https://github.com/ratsgo/embedding" target="_blank">https://github.com/ratsgo/embedding</a>


- <a href="https://lovit.github.io/machine%20learning/2019/03/17/attention_in_nlp/" target="_blank">https://lovit.github.io/machine%20learning/2019/03/17/attention_in_nlp/</a>