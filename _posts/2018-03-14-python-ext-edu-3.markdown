---
layout: post
title:  "파이썬 교육 3, 4일차"
date:   2018-03-14 09:04:00
categories: python
use_math: true
tags: python
---

os 라이브러리는 os라고 적어주면 안된다네?...  
파일 open write시 인자는 문자열 ('r', 'w')로 전달이 됨.

try except finally구문을 사용안하고, 에러가 발생하면 자동으로 파일을 닫는 구문  
with open('filename' 'mode') as f:

배포패키지 만들기: py2exe (linux: pyinstaller)  
외부패키지 설치방법: python setup.py install   
exe파일로 만들기: python setup.py py2exe  
배포판에 전달하고자 하는 파일은 폴더내에 유일하게 존재해야 함  
(setup.py에 설정한 파일이 없으면 안됨?? 멍게소리야)  
최신판은 cx_Freeze를 사용한다 함 (간단하니 함 찾아보면 될듯. 실습했지만 기억하고싶진 않음)  

SQLite: 타입이 서로 매칭되서 쓰기 편함 (매칭테이블은 교제에)  
PEP: 파이썬 공식 문서  
con.execute보단 cursor.execute를 더 추천한다. 일관성 관점에서?  

Python은 C++처럼 다중상속이 된다.

pandas의 고차원 배열: 계층적 색인 pandas의 기본연산은 열에 적용 ex) dataframe.apply(lambda x : max(x) - min(x)) : 각 열의 최대값-최소값을 가진 리스트가 나옴 axis=1을 주면 행에 대해서로 바뀜 applymap은 뭔함수여 계층적 색인은 요소의 개수가 짝이 맞아야 한다?