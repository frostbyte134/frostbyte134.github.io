---
layout: post
title:  "Non-singular matrix preserves rank"
date:   2018-05-08 16:06:00 +0900
categories: linear_algebra
use_math: true
tags: linear_algebra
---

For non-singular matrix \\(P, Q\\), 
#### \\((i)\\>\\>\textrm\{rank\}(AQ)=\textrm\{rank\}(A)\\)
\\(\textrm\{rank\}A\equiv\textrm\{dim\}(\textrm\{Im\}(A))\\) holds, so we will show that
\\[\textrm\{Im\}(AQ)\equiv\textrm\{Im\}(A).\\]
1. If \\(y\in\textrm\{Im\}(AQ)\\), then there must be \\(x\\) such that \\(y\=AQx'\\).  
By substituting \\(Qx'\\) as \\(x\\), it holds that \\(y=Ax\\), which implies \\(y\in\textrm\{Im\}A\\)  
2. If \\(y\in\textrm\{Im\}A\\), then \\(\exists\\>x\\) s.t. \\(y=Ax\\),  
and since \\(Q\\) is non-singular, there must be \\(x'\\) s.t. \\(x=Qx'\\>\rightarrow y=AQx'\\)  
which implies \\(y\in\textrm\{Im\}(AQ)\\).
  
  
#### \\((ii)\\>\\>\textrm\{rank\}(PA)=\textrm\{rank\}(A)\\)
Let \\(\{u_1,...,u_r\}\\) be a basis of \\(\textrm\{Im\}A\\). Then, 
\\[(u'_1,...,u'_r):=(Pu_1,...,Pu_r)\in\textrm\{Im\}PA.\\]
We will showt that \\((u'_1,..,u'_r)\\) is a basis of \\(\textrm\{Im\}PA\\).
1. For an arbitrary \\(y'\in\textrm\{Im\}PA\\), \\(y'=c'_1u'_1+...+c'_ru'_r\\) holds.  
proof: Since \\(y'\in\textrm\{Im\}PA,\\) there must be \\(y\in\textrm\{Im\}A\\) such that \\(y'=Py\\) holds.  
Since \\((u_1,...,u_r)\\) is a basis of \\(\textrm\{Im\}A, y=c_1u_1+...+c_ru_r\\), so that
\\[y'=Py=P(c_1u_1+...+c_ru_r)=c_1u'_1+...+c_ru'_r\\]
2. Such \\((c_1',...,c'_r)\\) is unique.  
Suppose not. Then it holds that \\[y'=c'_1u'_1+...+c'_ru'_r=d'_1u'_1+...+d'_ru'_r.\\]
Using the fact that \\(\\{u_i\\>\|\\>u_i=P^\{-1\}u'_i\\>\forall i=1,...,r\\}\\) is a basis of \\(\textrm\{Im\}A\\), \\[P^\{-1\}y'=c'_1u_1+...+c'_ru_r=d'_1u_1+...+d'_ru_r\\]which is a contradiction.