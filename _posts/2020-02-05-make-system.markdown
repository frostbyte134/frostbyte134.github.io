---
layout: post
title:  "Make 정리"
date:   2020-02-09 09:00:05 +0800
categories: coding
use_math: true
tags: coding C
---


1. KLDP https://wiki.kldp.org/KoreanDoc/html/gcc_and_make/gcc_and_make-3.html

목표:  목표를 만드는데 필요한 구성요소들...  
    목표를 달성하기 위한 명령 1  
    목표를 달성하기 위한 명령 2  
    ...  

target (=label)... : dependency(=prerequisites) ...
                command(=recipe)
                ...
                ...

 %.o: %.c  
    gcc -c -o $@ ${CFLAGS} $<  

$<     입력 화일을 의미합니다. 콜론의 오른쪽에 오는 패턴을 치환합니다.  
$@     출력 화일을 의미합니다 (current target). 콜론의 왼쪽에 오는 패턴을 치환합니다.  
$*     입력 화일에서 꼬리말(.c, .s 등)을 떼넨 화일명을 나타냅니다.  

- https://www.gnu.org/software/make/manual/html_node/Automatic-Variables.html#Automatic-Variables

 target:
        cd obj
        HOST_DIR=/home/e 
        mv *.o $HOST_DIR

하나의 목표에 대하여 여러 명령을 쓰면 예기치 않은 일이 벌어집니다. 기술적으로 말하자면 rkrrkrdml 명령은 각자의 서브쉘에서 실행되므로 전혀 연관이 없습니다.


이렇게 적어주셔야 합니다. 세미콜론으로 각 명령을 구분하지요. 처음 두 줄의 마지막에 쓰인 역슬래쉬(\) 문자는 한 줄에 쓸 것을 여러 줄로 나누어 쓴다는 것을 나타내고 있습니다.

확장자 규칙 (Suffix rule)

확장자 규칙이란 간단히 말해서 파일의 확장자를 보고, 그에 따라 적절한 연산을 수행시키는 규칙

.SUFFIXES : .c .o

위의 표현은 '.c' 와 '.o' 확장자를 가진 파일들을 확장자 규칙에 의거해서 처리될 수 있도록 해준다. .SUFFIXES 매크로를 이용한 예제를 살펴보자.



### Recursive MAKE
.SUFFIXES : .c .o
CC = gcc
CFLAGS = -O2 -g

all : DataBase Test <- 요기에 집중.

DataBase:
                cd db ; $(MAKE) <- db 로 이동해서 make 실행

Test: 
                cd test ; $(Make) <- db 로 이동해서 make 실행



### http://developinghappiness.com/
SRCS = MySocket.c MyClient.c  
OBJS = $(SRCS:%.c=%.o)  

경험적으로 봤을 때도, 소스 코드 사이의 의존성 부분은 Makefile에서 빼는 게 좋더라는 겁니다  
-include $(DEPEND_FILE)

이거 왜 이러세요, __코드 중복보다 더 무서운게 소스 파일의 중복__이란 것쯤은 다 아시잖아요…그 보다는 MyClient로부터 각 테스트에 공통으로 사용되는 부분을 분리해서 하나의 라이브러리로 만들면 어떨까요? 





$(TARGET_NAMES): $@.o
	$(CC) -o $@ $@.o $(LIB_DIRS) $(LIBS)

make의 $@ 같은 자동 변수는, 레시피에서만 값을 가지기 때문입니다. 따라서 선행조건에서는 빈 문자열을 나타내고, 결과적으로 gcc는 입력 파일을 주지 않은 채, .o 라는 이름으로 컴파일하라는 명령만 받은 셈


선행조건에 $@ 에 해당하는 것만 표현할 수 있으면 하나의 규칙으로 정리가 가능하다는 것 - Secondary expansion

Second Expansion을 알기 위해서는 먼저 make가 Makefile을 어떻게 읽어들이는 지에 대한 좀더 구체적인 이해가 필요합니다.

make는 크게 2개의 단계로 Makefile을 읽어 들입니다. 첫 번째 단계는 read-in phase로서, make는 입력으로 지정된 Makefile의 모든 내용을, include된 다른 파일들까지 포함해서 모두 읽어 들인 후, 모든 변수들과 규칙들을 정의하고, 규칙들의 타겟들과 선행조건들의 의존성 그래프를 구조화합니다. 그리고 두 번째 단계, target update phase에서, make는 이러한 내부 구조들을 사용해서 어떤 타겟이 다시 만들어져야 하는지, 그리고 어떤 규칙들이 실행되어야 하는 지를 결정합니다.

이 과정에서 변수의 값이 결정되는 것을 expansion이라고 하는데, 보통의 경우는 대부분 read-in phase에서 expansion이 일어납니다. 하지만 make는 특정 규칙들에 대한 선행조건 목록에 한해서, expansion을 나중으로 미룰 수 있는 기능을 제공하는데요, 이를 secondary expansion이라 합니다.


@echo "================================================"


MKDIR = mkdir
...
$(OBJS_DIR)/%.o : %.c
	@echo "============================================================"
	@echo "= Compiling $@ "
	@echo "============================================================"
	@`[ -d $(OBJS_DIR) ] || $(MKDIR) $(OBJS_DIR)`
	$(CC) $(CFLAGS) -c $< -o $@

why we add `$(OBJS_DIR)/%.o : %.c` -  In default, Makefile can only handle `$(name).o : $(name).c`, not `src/$(name).o : $(name).c`


```make
# Makefile template
 
include $(PROJ_ROOT)/IncludePre.mk
 
# 서브 디렉토리 목록입니다. 
SUB_DIRS = # 
 
# 링킹할 때 사용되는 링커 이름입니다.
LIB_NAME = # Example
 
# 공유 라이브러리 여부를 나타냅니다. (IS_SHARED = 1 이면 공유 라이브러리)
IS_SHARED = # 1
# 공유 라이브러리 버전입니다. \
	soname은 lib$(LIB_NAME).so.$(MAJOR_VERSION) 으로 지정됩니다. \
	실제이름은 lib$(LIB_NAME).so.$(MAJOR_VERSION).$(MINOR_VERSION) 으로 지정됩니다.
MAJOR_VERSION = # 1
MINOR_VERSION = # 0
 
# 라이브러리 소스 파일들의 목록입니다.
LIB_SRCS = # LibSource1.c LibSource2.c ...
 
# 라이브러리를 사용하는 실행 파일들의 소스 파일 목록입니다.
TARGET_SRCS = # TargetBin1.c TargetBin2.c ...
 
# 의존성 규칙에 포함시킬 라이브러리 목록입니다.
DEPEND_LIBS = # -lLibrary1 -lLibrary2
 
# 외부 시스템 라이브러리 목록입니다.
LIBS += # -lExtLibrary1 -lExtLibrary2
 
include $(PROJ_ROOT)/IncludePost.mk
```

```make
# IncludePre.mk
 
CC = gcc
AR = ar
RANLIB = ranlib
RM = rm
MV = mv
MKDIR = mkdir
MAKE = make
LN = ln
STRIP = strip
 
ROOT_SRC_DIR = $(PROJ_ROOT)/Source
ROOT_OUT_DIR = $(PROJ_ROOT)/Out
ROOT_LIB_DIR = $(ROOT_OUT_DIR)/Library
 
INC_DIRS = -I$(PROJ_ROOT)/Include
 
ifeq ($(RELEASE), 1)
OBJS_DIR = Release
DBG_FLAGS = -O2 -DNDEBUG
else
OBJS_DIR = Debug
DBG_FLAGS = -g -O0 -DDEBUG
endif
 
DEPEND_FILE = $(OBJS_DIR)/depend_file
 
LIB_DIRS = -L$(ROOT_LIB_DIR)/$(OBJS_DIR)
```

```make
# IncludePost.mk
 
ifeq ($(IS_SHARED),1)
SHARED_FLAGS = -fPIC
SHARED_SO_NAME = lib$(LIB_NAME).so.$(MAJOR_VERSION)
SHARED_REAL_NAME = $(SHARED_SO_NAME).$(MINOR_VERSION)
LIB_FULL_NAME = $(ROOT_LIB_DIR)/$(OBJS_DIR)/$(SHARED_REAL_NAME)
else
LIB_FULL_NAME = $(ROOT_LIB_DIR)/$(OBJS_DIR)/lib$(LIB_NAME).a
endif
 
LIB_OBJS = $(LIB_SRCS:%.c=$(OBJS_DIR)/%.o)
 
ALL_LIBS = -l$(LIB_NAME) $(DEPEND_LIBS) $(LIBS)
 
TARGET_OBJS = $(TARGET_SRCS:%.c=$(OBJS_DIR)/%.o)
TARGET_NAMES = $(TARGET_SRCS:%.c=$(OBJS_DIR)/%)
 
.SUFFIXES : .c .o
 
all : lib subdirs targets
 
subdirs : 
	@for dir in $(SUB_DIRS); do \
		$(MAKE) -C $$dir all; \
		if [ $$? != 0 ]; then exit 1; fi; \
	done
 
lib : $(LIB_FULL_NAME)
 
liball : $(LIB_FULL_NAME) 
	@for dir in $(SUB_DIRS); do \
		$(MAKE) -C $$dir liball; \
		if [ $$? != 0 ]; then exit 1; fi; \
	done
 
targets : $(TARGET_NAMES)
 
$(LIB_FULL_NAME) : $(LIB_OBJS)
	@`[ -d $(ROOT_LIB_DIR)/$(OBJS_DIR) ] || $(MKDIR) -p $(ROOT_LIB_DIR)/$(OBJS_DIR)`
ifeq ($(IS_SHARED),1)
	$(CC) -shared -Wl,-soname,$(SHARED_SO_NAME) -o $@ $(LIB_OBJS)
	$(LN) -fs $(SHARED_REAL_NAME) $(SHARED_SO_NAME)
	$(LN) -fs $(SHARED_SO_NAME) lib$(LIB_NAME).so
	$(MV) $(SHARED_SO_NAME) lib$(LIB_NAME).so $(ROOT_LIB_DIR)/$(OBJS_DIR)/
else
	$(AR) rcv $@ $(LIB_OBJS)
	$(RANLIB) $@
endif
 
$(OBJS_DIR)/%.o : %.c
	@echo "==================================================="
	@echo "= Compiling $@"
	@echo "==================================================="
	@`[ -d $(OBJS_DIR) ] || $(MKDIR) -p $(OBJS_DIR)`
	$(if $(findstring $<, $(TARGET_SRCS)), \
		$(CC) $(CFLAGS) $(DBG_FLAGS) $(INC_DIRS) -c $< -o $@, \
		$(CC) $(CFLAGS) $(DBG_FLAGS) $(SHARED_FLAGS) $(INC_DIRS) -c $< -o $@)
 
.SECONDEXPANSION:
$(TARGET_NAMES): $$@.o
	@echo "==================================================="
	@echo "= Linking $@"
	@echo "==================================================="
ifeq ($(LIBS_CYCLING_DEPEND),1)
	$(CC) -o $@ $< $(LIB_DIRS) -Wl,-\( $(ALL_LIBS) -Wl,-\)
else
	$(CC) -o $@ $< $(LIB_DIRS) $(ALL_LIBS)
endif
 
depend :
	@`[ -d $(OBJS_DIR) ] || $(MKDIR) $(OBJS_DIR)`
	@$(RM) -f $(DEPEND_FILE)
	@for FILE in $(LIB_SRCS:%.c=%); do \
		$(CC) -MM -MT $(OBJS_DIR)/$$FILE.o $$FILE.c $(CFLAGS) $(DBG_FLAGS) $(SHARED_FLAGS) $(INC_DIRS) >> $(DEPEND_FILE); \
	done
	@for FILE in $(TARGET_SRCS:%.c=%); do \
		$(CC) -MM -MT $(OBJS_DIR)/$$FILE.o $$FILE.c $(CFLAGS) $(DBG_FLAGS) $(INC_DIRS) >> $(DEPEND_FILE); \
	done
 
dependall : depend
	@for dir in $(SUB_DIRS); do \
		$(MAKE) -C $$dir dependall; \
		if [ $$? != 0 ]; then exit 1; fi; \
	done
 
clean :
	$(RM) -fr $(OBJS_DIR) $(LIB_FULL_NAME)
ifeq ($(IS_SHARED),1)
	$(RM) -f $(ROOT_LIB_DIR)/$(OBJS_DIR)/lib$(LIB_NAME).so*
endif
 
cleanall : clean
	@for dir in $(SUB_DIRS); do \
		$(MAKE) -C $$dir cleanall; \
		if [ $$? != 0 ]; then exit 1; fi; \
	done
 
$(TARGET_NAMES) : $(LIB_FULL_NAME) \
	$(patsubst -l%, $(wildcard %.*), $(DEPEND_LIBS))
 
ifneq ($(MAKECMDGOALS), clean)
ifneq ($(MAKECMDGOALS), cleanall)
ifneq ($(MAKECMDGOALS), depend)
ifneq ($(MAKECMDGOALS), dependall)
ifneq ($(strip $(LIB_SRCS) $(TARGET_SRCS)),)
-include $(DEPEND_FILE)
endif
endif
endif
endif
endif
```c