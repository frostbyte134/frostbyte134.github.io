---
layout: post
title:  "풀스택-커뮤니티-mern"
date:   2022-12-24 08:00:05 +0800
categories: coding
use_math: true
tags: coding
---


복지포인트가 남아서 ㅎㅎ 일단 지르고 봄. 첫 시작으로 리액트에 흥미를 붙이는 정도...? 백엔드는 fastapi로 바꾸고 헤로쿠 말고 AWS에 올리는 식으로 할듯


클래스형 -> 함수형 컴포넌트


### lec 1
#### 대충 구조

<a href="https://github.com/frostbyte134/react-fastapi-blog" target="_blank">https://github.com/frostbyte134/react-fastapi-blog</a>
- 프론트+백을 한 레포에 몰아넣으면 좋은 게 있을까? 통테가 쉽나? 
- nodejs lts 18.12.1 설치
- ES7 React/Redux/GraphQL 어쩌고 vs extention설치 - 단축키용?


create app
- npm - 라이브러리 관리? poetry
- npx - 라이브러리를 한번만 사용하고 삭제?
- creat react app - 한번만 쓰면 됨
- `npx create-react-app client` 좀 걸리네..
- `npm start`

App.js의 내용이 어떻게 브라우져로 렌더링되는가?
- index.js를 보면, root객체를 만듬
- 이 root객체는는 `public/index.html`의 body에 `<div id="root">`이걸 렌더링하는 데 쓰이는 듯
- 다른 것들과는 다르게, 사용자 임의의 커스텀 HTML을 만들어서 블록쌓듯이 
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
    - html 태그속성에 class, id로 css/js의 타겟으로 삼는데 자바스크립트에서는 class라는 이름이 정의되어 있음 - 대신 className 사용 `<h1 className="">` 
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
return <>
    {
        Arr.map((elem, idx) => {
            return <p>{elem}</p>
        })
    }
</>
```
이렇게 하면 컴포넌트 내에서 컴포넌트를 반환하는 함수를 쓰는 건가?

크롬 콘솔창 열기 - ctrl + option + i
- each clild in a list should have  aunique "key" prop. 이거때매 터지진 않았음. 컴포넌트 내 컴포넌트 반복 리턴시 고유의 키값을 줘야 함 (인덱스로 보통 줌)


### 리액트 스테이트
