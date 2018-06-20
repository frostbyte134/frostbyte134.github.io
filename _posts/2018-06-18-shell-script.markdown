---
layout: post
title:  "Bash Shell Script"
date:   2018-06-18 19:34:00 +0900
categories: linux
use_math: true
tags: coding script linux bash need_revise
---

### Start of shell script

```shell
#! /bin/sh
```

Indicates that following scripts will be evaluated with the basic shell script of the OS.  
For older linux `bash shell` (<b>B</b>ourn <b>A</b>gain <b>SH</b>ell) is used, but recently Ubuntu/Debian made conversion to `dash shell`.

You can still use bash shell by the explicit designation.
```shell
#! /bin/bash
```

### Variable and comments
```shell
#!/bin/bash
# 이 프로그램은 1부터 10까지 카운트한다:
for i in 1 2 3 4 5 6 7 8 9 10; do
    echo $i
done
```
__Comment__ in Bash shell start with `#`.  
Note the `$` symbol, which is required to obtain the __value of a variable__.  
Definition of variable can be done as following.
```shell
#! /bin/bash
x=12
y="14"
echo "The value of var x is $x"
echo "The value of var x is $y"
```
Note that,
1. there is no differentiation between string/integer types.
2. No whitespaces between var="value"


### Global(environmental) variables
Environmental variabls are defined in `/etc/profile` and `~/.bash_profile`. They holds special values.
```shell
#! /bin/bash

echo $Shell
$ENV	 #.bashrc 파일에서 설정하며 함수와 별명 등을 설정하는 환경 파일의 이름을 설정
$EUID	 #Shell이 시작할 때 현재 사용자의 유효 ID를 확장한다.
$HISTFILE	 #명령어 히스토리를 저장할 파일이름. 기본값은 ~/.bash_history이다.
$HOME	 #사용자의 홈 디렉토리의 값을 가지고 있으며 특정 디렉토리를 지정하지 않고 cd 명령을 사용할 때 이용한다.
$LANG	 #LC_로 시작하는 변수들에 포함되지 않는 로케일을 설정
$PATH	 #명령어의 검색 경로, 콜론으로 구분한 디렉토리 목록
$PPID	 #부모프로세스의 PID
$PWD	 #현재 작업 디렉토리
$SHELL	 #현재 사용되어지고 있는 SHELL
$UID	 #현재 사용자의 UID
$OLDPWD	 #이전 작업 디렉토리 (이전 한개만 저장)
$SHLVL   #재귀적 쉘 호출의 스택 레벨 
$USER	 #사용자 이름
$TERM	 #터미널 타입

$$	#쉘의 프로세스 번호
$0	#쉘 스크립트 이름
$1 ~ $9	#명령줄 인수
$*	#모든 명령줄 인수 리스트
$#	#명령줄 인수의 개수
```

### Expressions
1. Comparison between nubmers
```shell
x -eq y   #x가 y와 같은지 체크
x -ne y   #x가 y와 같지 않은지 체크
x -gt y   #x가 y 보다 큰지 체크
x -lt y   #x가 y 보다 작은지 체크
```
2. Comparison between strings 
```shell
x = y   #문자열 x가 문자열 y와 같은지 체크
x != y  #문자열 x가 문자열 y와 다른지 체크
-n x   #문자열 x가 널 문자가 아니면 true로 간주함
-z x   #문자열 x가 널 문자이면 true로 간주함.
```
3. `test` command: checks the existence/permission/properties of files
```shell
-d #파일이 디렉토리인지 체크 
-e #파일이 존재하는지 체크 
-f #파일이 일반적인 파일인지 체크 
-g #파일이 SGID 퍼미션을 가졌는지 체크 
-r #파일이 읽기 가능인지 체크 
-s #파일의 크기가 0이 아닌지 체크 
-u #파일이 SUID 퍼미션을 가졌는지 체크 
-w #파일이 쓰기 가능인지 체크 
-x #파일이 실행 가능인지 체크
```

#### Usage of `test`
```shell
if test -f /etc/foo
then
```
Can be written as follows:
```shell
if [ -f /etc/foo ]; then
```


### Control statement in Bash
1. if-elif-else
```shell
if list then list fi
if list then list else list fi
if list then list elif list then list fi
if list then list elif list then list elif list then list fi
if list then list elif list then list else list fi
if list then list elif list then list elif list else list fi
```
`list` is one of the followings.
	1. simple __expressions__ or __commands__, such as `test`
	2. set of simple commands, connected with `|` (pipe)
	3. consecutive expressions, connected with `&`, `;`, `&&` or `||`.  

continued..

Links  
<a href="http://storycompiler.tistory.com/103" target="_blank">http://storycompiler.tistory.com/101</a>  
<a href="http://coffeenix.net/doc/shell/introbashscript.htm" target="_blank">http://coffeenix.net/doc/shell/introbashscript.htm</a>  
<a href="https://opentutorials.org/course/2598/14212" target="_blank">https://opentutorials.org/course/2598/14212</a>