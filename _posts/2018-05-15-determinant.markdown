---
layout: post
title:  "Determinant(definition, properties)"
date:   2018-05-15 13:31:00 +0900
categories: linear_algebra
use_math: true
tags: linear_algebra
---
Determinant provides
{:.acounter}
1. Test for invertivility
2. Volume of a box (with rows)
3. In \\(Ax=b\\), how \\(x=A^\{-1\}b\\) changes wrt \\(b\\).

### Basic 3 properties (definition)
1. det⁡I=1
2. When rows are exchanged, the sign of determinant changes  
(Remember that, cross product changes sign__(link)__ when order is changed)
3. The determinant depends linearly on the 1st row (indeed, a volume with rows)
\\[
\begin{vmatrix}{}
	t(a+a' ) && t(b+b' ) \cr
	c && d \cr
\end{vmatrix}
=t
\begin{vmatrix}{}
	a && b \cr
	c && d \cr
\end{vmatrix}
=t
\begin{vmatrix}{}
	a' && b' \cr
	c && d \cr
\end{vmatrix}
\\]
### Additional properties
4. If two rows of \\(A\\) are equal, \\(\textrm\{det\}⁡A=0\\)
\\[-x=x\quad\rightarrow\quad 0\\]
(Follows by `b`. By exchanging two equivalent rows the sign of determinant must be inverted, but it must not change at the same time)
5. Subtracting (adding) multiples of one row from the other row leaves the same determinant
\\[
\begin{vmatrix}{}
	a-tc && b-td \cr
	c && d \cr
\end{vmatrix}
=
\begin{vmatrix}{}
	a && b \cr
	c && d \cr
\end{vmatrix}
-t
\begin{vmatrix}{}
	c && d \cr
	c && d \cr
\end{vmatrix}
=
\begin{vmatrix}{}
	a && b \cr
	c && d \cr
\end{vmatrix}
\\]
(By applying rule `(b)` and `(c)`)
6. If A has rows of 0, then \\(\textrm\{det\}⁡A=0\\)  
(we can add some nonzero row to zero row, unchanging the determinant, and apply `d.` <br/>
7. If A is triangular, then det⁡A is the product of diagonal entries
\\[
\begin{vmatrix}{}
	a && 0 \cr
	c && d \cr
\end{vmatrix}
=a
\begin{vmatrix}{}
	1 && 0 \cr
	c && d \cr
\end{vmatrix}
=ad
\begin{vmatrix}{}
	1 && 0 \cr
	c && 1 \cr
\end{vmatrix}
=ad
\begin{vmatrix}{}
	1 && 0 \cr
	0 && 1 \cr
\end{vmatrix}
\\]
(Applying `(b)`, `(e)`, and `(a)`) <br/>
8. If \\(A\\) is singular, then \\(\textrm\{det\}⁡A=0\\)  
Colloary: `(d)`+`(e)` → if two rows are linearly dependent, then \\(\textrm\{det\}⁡A=0\\).
9. \\(\textrm\{det\}⁡AB=\textrm\{det\}⁡A\textrm\{det\}⁡B\\)  <br/>
Singular case: trivial. \\(\textrm\{det\}⁡AB=0=\textrm\{det\}⁡A\textrm\{det\}⁡B\\)  
(1st equality : linear transformation perspective)  
Nonsingular case: For any nonsingular matrix \\(A,\\>A→U→D\\) only requires proper row operations, thus 
\\[\textrm\{det\}⁡A=(+\textrm\{or\}-)\textrm\{det\}⁡D.\\]
Same operations have exactly effect on
\\[AB→UB→DB\\]
so that, \\(\textrm\{det\}⁡AB=(\textrm\{same +or\}-)\textrm\{det\}⁡DB\\).
Now we have,
\\[\textrm\{det⁡\}AB=(+\textrm\{or\}-) \textrm\{det\}⁡DB=(+\textrm\{or\}-) \textrm\{det⁡\}D  \textrm\{det⁡\}B=\textrm\{det\}⁡A  \textrm\{det\}⁡B\\]
where the 2nd equality follows from `(c)`, and 3rd equality follows from the properties of determinant.
10. \\(\textrm\{det\}⁡A^T=\textrm\{det\}⁡A\\)  
	Singular : trivial  
	Nonsingular : \\(PA=LDU\\). Applying `i` gives
\\[\textrm\{det\}⁡PA=\textrm\{det\}⁡P \textrm\{det\}⁡A=\textrm\{det\}⁡L \textrm\{det\}⁡D \textrm\{det\}⁡U\\]
Similarly,
\\[\textrm\{det\}⁡A^TP^T=\textrm\{det\}⁡A^T \textrm\{det\}P^T=\textrm\{det\}⁡U^T \textrm\{det\}⁡D^T \textrm\{det\}⁡L^T\\]
\\(L,U,L^T,U^T\\) are triangular with unit diagonal, and for any diagonal matrix \\(D=D^T\\) holds. We only have to show \\(\textrm\{det\}P^T=\textrm\{det\}P\\).  
Certainly \\(\textrm\{det\}⁡P=1\\) or\\(-1\\), because \\(P\\) comes from \\(I\\) by row exchanges. Observe also that \\(PP^T=I\\) (by reverse row exchanges), therefore \\(\textrm\{det⁡\}PP^T=1=\textrm\{det\}⁡P \textrm\{det\}P^T\\), and \\(P\\) and \\(P^T\\) must have same determinant: both 1 or both -1.   
We conclude that the above two products are same. This fact practically doubles our list of properties, since every rule that applied to the rows can now be applied to columns.
{:.acounter}