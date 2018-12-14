---
layout: post
title:  "국민대 프리스캔 교육"
date:   2018-12-14 09:00:05 +0800
categories: misc
use_math: true
tags: prescan synthetic 
---

* 클릭->ctrl+클릭으로 한번에 연결
* 우클릭 드래그 앤 드랍 – 복사
* 시그널 분기 – 우클릭 드래그
* 블록 때기 – 쉬프트 클릭
* Gain – 곱하기
* Scope – 시뮬레이션 후 값 display?
* 시그널 이름을 주면 스코프에서 확인가능 (설정→ display → show legend)
* 스위치의 u2 는 가운데 (파라미터)
* 매뉴얼 스위치 – 클릭으로 변경가능
* Step size에는 variable / fixed size가 있음
* Trigger = rising/down edge일 시 activation됨
* If-else – port & subsystems에 있음
* Satuation – [a, b]사이 있는 값만 출력
* Dead-zone – [-a, a] 값을 빼서 출력 (saturation + dead zone = 원래 신호 복원)
* User define function / fcn = 매틀랩 함수 / 함수 사용가능 

Carsim
* Carsim run = prescan experiment
* 도로 library 있음?
* Carsim s-function: 차량 동력학 정보 포함
* Fixate to build area: 안움직이게
* Bend road – relative heading으로 각도조정 (90도)
* 베지어 스플라인 – 컨트롤 키로 길이 조정
* Flexible road 끊기 + bend road 350도 -> 무한돌기 (randomization?)
* 램프의 각도조절: height
* 라인 마커: 패스를 따라 마커 지정가능
* Trajectory: path + speedprofile
* Path 위에 차량 올려놓으면 trajectory 생김
* Test automation : batch 돌리기

센서
* Federate: multi-core/machine
* GPS원점 calibration (중부원점, 서부원점 등을 prescan 좌표의 0,0에 맞춤) – general setting → Global placement
* Orm assignment?

* GPU 가속?? 매뉴얼 찾아 보자
* 렌즈 맵에서 빛방울 설정가능
* Remote viewer plugin – 가벼운 뷰어
* 다 지우고 regenerate – 초기화

stateflow
* Simulink-stateflow = if/else rule
* Default transition: 왼쪽 toolbar
* input-output = 오른클릭후 Explore, 변수추가 (위의 툴바) - input/output
