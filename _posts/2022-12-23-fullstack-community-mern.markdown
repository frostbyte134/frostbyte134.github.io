---
layout: post
title:  "인프런-풀스택-MERN-커뮤니티 만들기"
date:   2022-12-24 08:00:05 +0800
categories: coding
use_math: true
tags: coding
---


복지포인트가 남아서 ㅎㅎ 일단 지르고 봄. 첫 시작으로 리액트에 흥미를 붙이는 정도...? 백엔드는 fastapi로 바꾸고 헤로쿠 말고 AWS에 올리는 식으로 할듯

### lec 1
#### 대충 구조

<a href="https://github.com/frostbyte134/react-fastapi-blog" target="_blank">https://github.com/frostbyte134/react-fastapi-blog</a>
- 프론트+백을 한 레포에 몰아넣으면 좋은 게 있을까? 통테가 쉽나?
    - 없을 거 같음. 따로 만들자
- nodejs lts 18.12.1 설치
- ES7 React/Redux/GraphQL 어쩌고 vs extention설치 - 단축키용?


create app
- npm - 라이브러리 관리? poetry 같은거
- npx - 라이브러리를 한번만 사용하고 삭제?
- creat react app - 한번만 쓰면 됨
- `npx create-react-app client` 좀 걸리네..
- `npm start`

App.js의 내용이 어떻게 브라우져로 렌더링되는가?
- index.js를 보면, root객체를 만듬
- 이 root객체는 `public/index.html`의 body에 `<div id="root">`이걸 렌더링하는 데 쓰이는 듯

#### 컴포넌트
리액트의 뭔가 중요한 building block (재사용성!). 클래스형에서 함수형으로 넘어가는 추세
- 사용자 정의의 custom html tag = `컴포넌트`

컴포넌트 생성 - src/test.js 생성
- rfce = react Functional Export Component
- html을 반환하는 함수를 `App.js`에 임포트해서 `<함수명 />`으로 바디에 놓으면 렌더링됨 ㄷㄷ 

컴포넌트 생성규칙
- 이름 시작은 영어 대문자 (기존 html태그와 구분)
- 코딩이 끝나면 다른데서 사용할 수 있게 export 해 줘야 함 
- 컴포넌트가 다른컴포넌트를 사용하려면 임포트해야 함
- 함수의 이름으로서 컴포넌트를 정의
    - 파일명은 컴포넌트명과 달라도 됨
    - 단, 단일파일에서 단일컴포넌트만 export할 시에는 `export default 컴포넌트명`처럼 default가 붙는데, 이경우는 __통일시켜주는게 관례__

컴포넌트로 프로젝트를 구축할 시 장점 = 재사용성 증가
- 함수형 컴포넌트 - 리턴구문에는 단 하나의 태그만 리턴가능 (1개 태그 내에는 자유)
    - 보통 `<div>...</div>` 로 리턴하는 듯
- `react fragment` - div대체 (div 남발 방지)
    - `<>...</>`를 반환하면 됨


#### JSX
리턴에 html은 있는데, 자바스크립트/css는?


요약
1. 카멜케이스
2. js: `{}`
3. css: `{{}}`


1. jsx 문법
- 리엑트는 camelCase 
    - html 태그속성에 class, id를 지정해서 css/js의 타겟으로 삼는데 자바스크립트에서는 class라는 이름이 정의되어 있음 - __대신 className 사용__ `<h1 className="">` 
- js 사용시 중괄호로 감싸기 {}

```
const Temp 7
<>{Temp}</>
```

- 스타일 속성 (css): 중괄호 2개에 object형태로 (json?) 입력
- `<h1 className="" style={{ color: "red", fontSize: "3rem" }}>` 으로 `인라인 스타일`을 입힐 수 있음

외부 css를 import해올수도 있음
- `<h1 className="css name">`으로 하고, `.test`이걸 app.css에 정의하면 됨

리액트에서 많이 사용하는 자바스크립트 문법
```
if-else, switch, for
```

if-else 리턴구문에서 써보기
1. 함수로 뺴고 호출하기 (이걸 해야 하는 듯)
2. 자바스크립트 삼항연산자로 (좀 극혐. 안티패턴 아닌감 ㄷㄷ)

반복문 리턴구문에서 써보기 - map
```
let Arr = [1, 2, 3];
return (
    <>
        {
            Arr.map((elem, idx) => {
                return <p>{elem}</p>
            })
        }
    </>
);
```
이렇게 하면 컴포넌트 내에서 컴포넌트를 반환하는 함수를 쓰는 건가?

크롬 콘솔창 열기 - ctrl + option + i
- each clild in a list should have a unique "key" prop. 이거때매 터지진 않았음. 
- __컴포넌트 내 컴포넌트 반복 리턴시 고유의 키값을 줘야 함 (인덱스로 보통 줌)__

여기까지 깃 커밋 - [링크](https://github.com/frostbyte134/react-fastapi-blog/commit/edb912f19739369ee4c910de8c3309b395f11e54)

### 리액트 스테이트
useState(1)

스테이트를 쓰기 위해선 useState 함수를 import해야 함

`const [state, setstate] = useState("")`
- 1st return: name of the state
- 2nd return: function to change the state (1st return var)
- parameter of useState = initial value of state

리엑트에서 js변수를 state로 사용할 수 있음


왜 쓰는가?
- 스테이트가 바뀌는 환경에 대해 알아야 함
- `<button onClick={() => setTemp(Temp + 1)}>증가</button>`
- 리액트 = 사용자 인터렉션을 최대화하기 위해 (?) 같은 환경을 구축하기 위한 웹 어플 라이브러리다
    - state로 관리하는 js 변수는 새로고침 안해도 새로운 화면을 보여줄 수 있음


state 사용 규칙
- 값 변경 시 항상 setstate 사용
- setstate를 html태그의 on 속성에서 호출하려고 할 땐 항상 함수로 감싸줘야 함 (기본  `funnction(){}`도 되고, 위처럼 arrow function도 됨)
- ex) `<button onClick={...}>` 내부
- 안그러면 무한 렌더링
- 값으로는 모든 js 변수를 넣을 수 있음
    - state가 list일 시 append를 하고 싶으면, setTemp함수에는 (기존 리스트의 값을 가져와서) 거기에 append한 것을 넘겨줘야 함 


<a href="https://developer.mozilla.org/en-US/docs/Web/JavaScript/Guide/Functions#arrow_functions" target="_blank">arrow functions</a>

```javascript
function Name() {
    return;
}
// Arrow function defition
const Name = () => {
    return;
}

() => someAlreadyDefinedFunc(param1)
```

<a href="https://studiomeal.com/archives/197" target="_blank">css flex</a>
<a href="https://github.com/frostbyte134/react-fastapi-blog/commit/179a35f7bf88ac113ed3eff9e525ac988d0629ab" target="_blank">setstate(2) codes</a>
#### setstate(3)와 input 태그

<a href="https://github.com/frostbyte134/react-fastapi-blog/commit/f5bb8cc784b76f885a86bb1f8e6b79ae0e7ded75" target="_blank">setstate(3) codes</a>

사용자는 form에 글 작성
- form에는 input태그를 통해 사용자가 작성한 글을 저장/보여줄 수 있게
- state를 통해 input 태그를 어떻게 관리하는가?


<a href="https://developer.mozilla.org/en-US/docs/Web/API/Event/currentTarget" target="_blank">event.currentTarget</a>: 이벤트가 발생한 현 타겟을 갖고옴. 이경유 type=text인 input태그
- input태그의 value (지금까지 해당 태그에 입력된 값)에 state를 할당할 수 있음 `value={content}`. 근데 할당만 한 거고, 자동적으로 input태그에 입력한 값이 content state로 들어가진 않음
- 이 때 `onChange`에 setState(event.currentTarget.value)를 걸어줘야 현재 인풋태그의 value가 제대로 disp되게 됨


### react-router-dom

<a href="https://github.com/frostbyte134/react-fastapi-blog/commit/76e656962850d206d87bb314eb73891b43bf3ea1" target="_blank">코드</a>

6버전 이후로 해야 함
라우팅을 백엔드말고 프론트에서

index.js로 라우팅 규칙 정의
- `<BrowserRouter><Routes>`로 일단 감싸고
- `<Route>`에서 각 라우터 규칙 정함. 여기 element 속성으로 컴포넌트 지정가능

react-router-dom에서 invalid hook call에러 발생 (일단 hook이 뭔지 잘모름 ㅋㅋ)
- 이 라이브러리 설치를 다른 터미널에서 해서 그런가? npm install을 -i -s로 해서 그런가. 


보통 index.js에서는 `<BrowserRouter><App /></BrowserRouter>`만 설정해 주고, 실제 router 설정은 App에서 리턴되는 html에 끼워넣는듯