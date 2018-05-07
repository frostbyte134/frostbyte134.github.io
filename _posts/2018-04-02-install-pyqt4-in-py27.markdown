---
layout: post
title:  "가상환경 python2.7에서 PyQt4설치"
date:   2018-04-02 13:46:00
categories: python
use_math: true
tags: python coding
kramdown:
  input: GFM
  hard_wrap: false
---

1. sudo apt-get install qt4-qmake libqt4-dev
2. sip최신버전을 받아 설치. (python configure.py, sudo make, sudo make install)
3. sudo apt-get install python-qt4
4. /usr/lib/python2.7/dist-packages 에 있는 sip, pyqt관련파일들을 전부 가상환경의 lib/python2.7/site-packages에 복사
