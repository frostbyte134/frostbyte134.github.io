---
layout: post
title:  "(In / Sur / Bi)jective linear mapping"
date:   2018-05-09 13:42:00 +0900
categories: linear_algebra
use_math: true
tags: linear_algebra analysis
---
For \\(A\in R^\{m\times n\}\\),
<h3 id="injective_linear_mapping">(1) Injective linear mapping</h3>
= 단사  
`Definitions:`  
\\[\forall x,x'\in R^n,\\>Ax\neq Ax'\\]
\\[\Leftrightarrow \textrm\{ker\}A \textrm\{ is trivial\}\\]
\\[\Leftrightarrow \textrm\{rank\}A=n\\]
<br>
* If \\(m<n,\\>A\\) __cannot be injective__.  
proof: Thanks to the <a href="{{ site.url }}/linear_algebra/2018/05/09/rank.html#dimen_theorem" target="_blank">dimensionality theorem</a>,
\\[\textrm\{dim\}(\textrm\{ker\}A)+\textrm\{dim\}(\textrm\{Im\}A)=n\\]
but \\(\textrm\{dim\}(\textrm\{Im\}A)<n\\), so \\(\textrm\{ker\}A\\) is nontrivial.  
\\(\Rightarrow \\) for nonzero \\(x'\in \textrm\{ker\}A,\\>Ax=A(x+x')\\)

<h3 id="surjective_linear_mapping">(2) Surjective linear mapping</h3>
=전사
\\[\forall y \in R^m,\\>\exists\\>x \textrm\{ s.t. \}y=Ax\\]
\\[\Leftrightarrow \textrm\{dim\}\textrm\{Im\}A=m\\]
<br>
* If \\(m>n,\\>A\\) __cannot be surjective__.  
proof: Again, thanks to the <a href="{{ site.url }}/linear_algebra/2018/05/09/rank.html#dimen_theorem" target="_blank">dimensionality theorem</a>,
\\[\textrm\{dim\}(\textrm\{ker\}A)+\textrm\{dim\}(\textrm\{Im\}A)=n\\]
Then \\(\textrm\{dim\}(\textrm\{Im\}A)\leq n<m\\), which contradicts the definition of surjective mapping.

### (3) Bijective linear mapping
=전단사  
If a mapping \\(A\\) is both injective and surjective, then it is bijective.