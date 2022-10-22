
### 메모리 섹선
-링크


### data alignment
https://coding/2020/04/10/data-align.html

### restrict, volatile
`volatile`: 이 메모리 접근 부분을 생략하지 말아라  
`restrict`: 다른 포인터는 여기 접근할 일 없으니, 최적화해라


### 파이썬
파이썬은 CPU bound에만 느림. IO bound는 알아서 처리함 - https://stackoverflow.com/questions/29270818/why-is-a-python-i-o-bound-task-not-blocked-by-the-gil

`JIT`: 프로그램 실행 시점에야 기계어로 컴파일. 왜 빨라지나? - http://net-informations.com/faq/qk/jit.htm
- 타겟 머신을 대상으로만 실행파일이 만들어짐
- 실행 중 중요한 코드 / 데이터들을 식별하고, 이에 관한 최적화 가능 (실행안되는것 컴파일 X) 인터프리트 하면서 자주 쓰이는 코드를 캐싱하기 때문에 인터프리터의 느린 실행 속도를 개선할 수 있다
- 메모리 많이 필요하다 함?
- 파이썬의 Copy on read!
이는 파이썬 garbage collection에서 객체를 담은 링크드리스트를 순회하며 객체의 reference count를 업데이트할 때 링크드리스트 자체를 뒤섞기 때문에
쓰기 작업이 일어나, 읽기 전용 페이지에 page fault가 발생하여 copy-on-write도 같이 수행되기 때문이다. 어찌보면 이는 copy-on-read라고 할 수 있을 것이다.
- PyPy

https://cjh5414.github.io/about-python-and-how-python-works/
> CPython은 인터프리터 이면서 컴파일러 이다. 우리가 작성하는 Python 코드를 bytecode로 컴파일 하고 실행한다. 다시 말해, python 코드를 C언어로 바꾸는 것이 아니라 컴파일하여 bytecode로 바꾸고 그 다음에 interpreter(virtual machine)가 실행한다.

__Why python is so slow?__
https://jakevdp.github.io/blog/2014/05/09/why-python-is-slow/ 개굿 
1. Python is Dynamically Typed rather than Statically Typed
2. Python is interpreted rather than compiled.
3. Python's object model can lead to inefficient memory access (파이썬 리스트객체는 continuous한 point배열을 가짐. data가 continuous하게 있는 것이 아님)


https://tech.ssut.me/yes-python-is-slow-and-i-dont-care/

### 싸이썬
Python의 슈퍼셋인 Cython이라는 언어가 있습니다. Cython은 거의 Python과 C를 합쳐둔 형태이고 이를 단계적 타이핑 언어(progressively typed language or gradual typing)라고 부릅니다. 그리고 Python 코드는 Cython 코드로 옮겨도 유효한 코드이고 Cython은 이를 C 코드로 컴파일합니다. Cython을 이용하면 C 타입과 성능의 이점을 가진 채로 모듈 또는 메소드를 작성할 수 있게 됩니다. 물론 C 타입과 Python만의 타입을 합칠 수도 있습니다. Cython을 이용해 Python의 멋진 부분을 이용하면서도 병목만 최적화할 수 있는 셈입니다.


`제너레이터`: 제너레이터(generators)는 이터레이터(iterators)입니다. 하지만 제너레이터는 모든 값을 메모리에 담고 있지 않고 그때그때 값을 생성(generator)해서 반환하기 때문에 제너레이터를 사용할 때에는 한 번에 한 개의 값만 순환(iterate) 할 수 있습니다:


### 클로저, 데코레이터 (클로저를 이용, @)



### 파이썬 GC (퀄컴에서 이거안물어봐서 다행)
- https://gogyzzz.blogspot.com/2019/07/190719-python-garbage-collection.html
- https://dc7303.github.io/python/2019/08/06/python-memory/
- https://winterj.me/python-gc/ - 여기 레퍼런스도 지림 (바로밑)
- https://b.luavis.kr/python/dismissing-python-garbage-collection-at-instagram
- https://d2.naver.com/helloworld/1329
- https://llvllatrix.wordpress.com/2016/02/19/python-vs-copy-on-write/ ?????





### 팀 소트? ㄷㄷ
https://d2.naver.com/helloworld/0315536


### 코루틴
코루틴은 항상 반드시 하나의 코루틴만 실행되기 때문에, 여러 쓰레드들을 사용할 때처럼 락을 관리할 필요가 없다. 다른 코루틴으로 제어권을 넘겨주려면 await 문을 사용하여 언제든지 넘겨줄 수 있다. 그렇기 때문에 코루틴은 안전하게 취소할 수 있다. 코루틴이 멈춰있던 await 문에서 CancelledError 를 처리해서 마무리하면 된다.


http://judis.me/wordpress/x86-flags-register/