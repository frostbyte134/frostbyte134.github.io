
### 선형대수 - Ax=b의 해결 (pseudoInverse까지)




### 선형대수 - 좌표변환


### 선형대수 - 조던분해 (왜 썼어?????)
- algebraic multiplicity of an eval: 같은 eval의 갯수 
- geometric multiplicity of an eval: 연관된 eigenspace (A-eI의 nullspace!!!)의 dimension
- n x n square matrix A가 서로 다른 고유값 \lambda_1,...,\lambda_n 을 지니면, 대응하는 고유벡터를 나열한 행렬 \\(P\\)는 정칙이고, P^-1AP=diag\(\lambda\_1,...,\lambda\_n\)로 대각화할 수 있다.

- 서로 다른 고유값n개는
  - singularity하고 관련이 전혀 없음.
    - 서로 다른 고유값n개를 가지는 경우에도 singular인 행렬
    - 서로 다른 고유값 n개가 없어도 non-singular한 행렬 다 가능
  - 



### 선형대수 - SVD, Spectral decomposition



### (랩스 - 목욜) 칼만 필터 기본만 
* https://medium.com/@celinachild/kalman-filter-%EC%86%8C%EA%B0%9C-395c2016b4d6
* 모션 모델과 측정 모델이 linear할 경우
* 모션 모델과 측정 모델이 Gaussian 분포를 따를 경우
* Using a Kalman filter assumes that the errors are Gaussian.[3]

### (랩스 - 목욜) 파티클 필터 기본만 - SLAM과 연동?

### (퀄컴) 해석학 - open/closed. 기본만 보자 


### optimization
- convex, grad descent, etc


- 헤시안이 positive definite하다 - 모든 eigenvalue들이 양수이다 - convex하다 (taylor approx으로 보일 수 있음)

