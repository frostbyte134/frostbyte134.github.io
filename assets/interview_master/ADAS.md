


### Detection Decoder over Quantized network

__카운팅소트ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ__

입력: [8][각 레이어별 크기]
stride - 0:width, 1:height, 2:channel (stride 엄청 큼)

wwwwwwww
h  h  h
c        c

2번째 채널: ary[stride_channel * 1]

anchor1  anchor2
c1 c2 c3 c1 c2 c3


1. 우선 class점수를 bucket sorting함. bin[4][256]: bin[i][j]엔 i번째 레이어의 값 j의 갯수가 들어가게 
2. bin[i][j]를 전체(4개 레이어)에서 i번째 레이어의 값 j의 순위로 바꿈 (accumulating sum)
   1. raw값: j * quant_val[i]
   2. 매 iteration마다 레이어를 (i) 순회하며, raw값이 가장 큰 것을 찾음. 
   3. 마지막엔 각 레이어마다 최소 accept threshold를 알 수 있게 됨
   4. 각 레이어가 죽었는지 (127 -> -128 도달) 체크하면 좀 효율적?
3. 모든 anchor position을 돌며, 속한 각 레이어의 threshold를 넘을 시
   1. 체널이 stride가 가장 큼. 채널에서 앵커/클래스 위치를 찾은 후, 
      1. clsoutput[(numDetclass * anchor_ind + cls) * stride_channel_cls]
      2. locoutput[(numRegOutput * anchor_ind + cls) * stride_channel_loc]
      3. 부터 시작하는 decoding data들을 넘겨 줌

__view angle이 뭐지?__

### NMS

--선택된 애들 --||-> 선택안된애들 ---> 현재 인덱스 --> 체크안한 애들
체크안한 애들 선택할 땐 ||까지만 체크하면 됨



### ldc
- LUT테이블 기반. 원본 이미지를 normalized plane에 갖다놓고 다항식에 의한 distortion correction 후, undistorted image (openCV가 제공)하는 intrinsic matrix로 이미지를 원복시킴
- LUT엔 상대좌표를 32bit raw img에 16비트씩 넣어주면 됨.
- 크롭도 같이 함. 크롭할 부분의 lut만 이용
- 크롭 위치. 유럽연이 어떻게 extrinsic인 rotation을 ldc에 반영하나? - crop과 관련 있는 듯함. intrinsic이 crop을 반영하게 되어야 하는 듯.
- 1) How much "rotation compensation" shall be performed. I.e., where in the image should be the area of least distortion. Probably this should lie in the center of the region of interest. Also, should the camera roll and pitch at rest be compensated, or not?




### Egomotion
- optical flow는 TI꺼를 쓰고 나는 잘 모른다. sparse optical flow를 뽑아주는 부분도 내가 안하고 유럽연이 함
- 선택된 optical flow에서 답을 만드는 levelberg-marquart알고리즘을 담당함
- 카메라도 계속 바껴서요 optical flow가 제대로 된게 없슴다 - 난 천재야!!!!!!!!!!!!!!!

### epipolar geometry

현재 축에서 R, T에 있는 축으로 가고싶으면, 모든 포인트들에는 반대로 해 줘야 함


Choleskey decomposition: LL^T=A. postitive definite한 경우에만. A[0][0]부터 차례로 계산하면 됨

LL^Tx=b 에도 쓰임. Ly=b 먼저 계산하고 L^Tx=y를 계산하면 됨. 이거도 마찬가지로 차례대로

reprojection error: 실제 움직인 거리와 estimate의 차이 - sum of least squares. 근데 실제 움직인 거리를 어떻게 알지?