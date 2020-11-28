---
layout: post
title:  "Independence"
date:   2020-11-28 09:00:05 +0800
categories: probability
use_math: true
tags: math probability 
---


- <a href="https://ocw.mit.edu/resources/res-6-012-introduction-to-probability-spring-2018/part-i-the-fundamentals/MITRES_6_012S18_L03.pdf" target="blank">https://ocw.mit.edu/resources/res-6-012-introduction-to-probability-spring-2018/part-i-the-fundamentals/MITRES_6_012S18_L03.pdf</a>
- <a href="https://vfu.bg/en/e-Learning/Math--Bertsekas_Tsitsiklis_Introduction_to_probability.pdf" target="_blank">https://vfu.bg/en/e-Learning/Math--Bertsekas_Tsitsiklis_Introduction_to_probability.pdf</a>

TODO: 책 읽고 내용 추가


### Independence - definition
1. Intuitive definition : \\(P(B\|A) = P(B)\\)
  - occurance of \\(A\\) provides no info about the occurance of \\(B\\)
2. Formal definition : \\(P(A\cap B) = P(A)\cdot P(B)\\)
   - symmetric
   - implies intuitive definition
   - applies even if \\(P(A)=0\\)


<img src="{{site.url}}/images/math/prob/prob_ind.jpg" width="600">  
- \\(P(A\cap B) = 0, P(A)>0, P(B)>0\\) : not independent!
- 아마...\\(P(B) : P(\Omega)\\)와 \\(P(A\cap B) : P(A)\\)의 비율이 우연히 같게 되면 되는 듯?

### Independence and complement
\\(A\\) and \\(B\\) are independent \\(\quad\rightarrow\quad\\) \\(A\\) and \\(B^c\\) are independent

__Proof__:  
\\[P(A) = P\left((A\cap B)\cup (A\cap B^c)\right)\\]
\\[ = P(A\cap B) + P(A\cap B^c) - P(A\cap B cap B^C)\\]
\\[ = P(A)P(B) + P(A\cap B^c)\\]
\\[P(A)(1-P(B)) = P(A\cap B^c)\\]
\\[P(A)P(B^c) = P(A\cap B^c)\\]


### Independence and Pairwise independence
1. Intuitive definition :
  - occurance of some events provides no info about the occurance of other events
2. Formal definition - Events \\(A\_1,...,A\_n) are `independent` if : \\[P(A\_1\cap A\_2) = P(A)\cdot P(B)\\]
   - symmetry holds
   - implies intuitive definition
   - applies even if \\(P(A)=0\\)
3. Independence implies pairwise independence
   - can be proven by exactly same techniques used in complement independence
4. pairwise independece __does not__ implies independence
  - <a href="https://math.stackexchange.com/questions/1938819/mutual-independence-implies-pairwise-independence-show-that-the-converse-is-not" target="_blank">easiest example</a> : Suppose three people are each tossing a fair coin. Consider the three events \\(A,B\\) match, \\(B,C\\) match, and \\(A,C\\) match.  
  these events are pairwise independence, but any two determine the third.

