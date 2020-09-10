---
layout: post
title:  "shell script"
date:   2020-09-09 09:00:05 +0800
categories: coding
use_math: true
tags: os need_review coding
---

예전에 이 주제로 글 쓴적 있지 않나...?

<a href="https://mug896.github.io/bash-shell/basics.html" target="_blank">https://mug896.github.io/bash-shell/basics.html</a>

### 2 basics
- `$?` : 이전 실행결과를 저장하는 특수변수
- Shell 에서 $ 문자를 이용하는 확장
  - Shell 에서는 `$` 문자를 이용하는 확장이 3 가지 종류가 있습니다.
  - `${ }` 를 사용하는 매개변수 확장 : `$AA, ${AA}, ${AA:-5}, ${AA%.*}` ...
  - `$(( ))` 를 사용하는 산술 확장 : `$(( 1 + 2 ))` ...
  - `$( )` 를 사용하는 명령 치환 : `$( echo "1.3 + 2.5" | bc )` ...
- `$1, $2, $3`... : 입력인자용 특수변수 

#### 2.1 Quotes
- shell 에서 quotes 은 숫자나 스트링 값을 구분하기 위한 용도로 사용하지 않습니다. 123, "123", '123' 은 모두 같고 abc, "abc", 'abc' 들은 차이가 없으며 모두 다 shell 에서는 스트링입니다
- shell 에서 quotes 은 다음과 같은 용도로 사용됩니다.
  - 공백으로 분리되는 여러 개의 스트링을 하나의 인수로 만들 때  
    ( sed, awk 스크립트를 quotes 을 이용해 작성하는 이유가 하나의 인수로 만들기 위해서입니다. )
  - 라인 개행이나 둘 이상의 공백문자를 유지하기 위해
  - 단어분리, globbing 발생을 금지하기 위해
  - shell 키워드, 메타문자, alias 와 같이 shell 에서 특수기능을 하는 문자, 단어를 단순히 명령문의 스트링으로 만들기위해
  - 문자 그대로 스트링을 강조하기 위해
  - 최종적으로 명령이 실행될 때는 사용된 quotes 이 제거된 후에 인수가 전달됩니다.
- No quotes 상태에서는 기본적으로 모든 문자가 escape 됩니다.

Double quotes `""`
  - Double quotes 안에서는 $ ` ! 특수기능을 하는 문자들이 해석되어 실행되고 공백과 개행이 유지됩니다. 변수 사용 시에도 동일하게 적용되므로 quote 을 하지 않으면 공백과 개행이 유지되지 않습니다.

#### 2.2 Variables
- 생성한 변수는 subshell 이나 source 한 스크립트 내에서는 별다른 설정 없이 사용할 수 있으나 child process 에서도 사용하려면 `export` 해야 합니다.
  - `export ORIGINAL_FILE=myfile`

#### 2.3 Functionss, 2.4 Exit Status
- shell 에서는 return 명령이 함수에서 연산한 결과를 반환하는데 사용되는 것이 아니고 exit 명령과 같이 함수가 정상적으로 종료됐는지 아니면 오류가 발생했는지를 나타내는 종료 상태 값을 지정하는 용도로 사용됩니다.
- 스크립트 파일이나 subshell 은 프로세스가 새로 생성되는 것이므로 종료 상태 값을 지정할때 exit 명령으로 합니다. function 이나 source 명령으로 읽어들이는 경우에는 return 명령으로 합니다. 종료 상태 값을 지정하지 않으면 마지막으로 실행된 명령의 종료 상태 값이 사용됩니다. 따라서 스크립트 작성시 직접 $? 변수를 사용해야 되는 경우는 많지 않습니다.