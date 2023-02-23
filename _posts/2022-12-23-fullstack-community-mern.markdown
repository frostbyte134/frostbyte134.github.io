---
layout: post
title:  "인프런-풀스택-MERN-커뮤니티 만들기"
date:   2022-12-24 08:00:05 +0800
categories: coding
use_math: true
tags: coding
---


복지포인트가 남아서 ㅎㅎ 일단 지르고 봄. 첫 시작으로 리액트에 흥미를 붙이는 정도...? 백엔드는 fastapi로 바꾸고 헤로쿠 말고 AWS에 올리는 식으로 할듯

리액트는 [여기](https://create-react-app.dev) 많이 참고한 듯

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
- __결국 리액트로 짠 모든 내용이 이 id=root을 체우는 데 들어가게 됨__

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

__routes는 switch-case랑 비슷__
- html dom 내에서의 switch-case (현재 선택된 것만 페이지에 보여짐)

<a href="https://github.com/frostbyte134/react-fastapi-blog/commit/76e656962850d206d87bb314eb73891b43bf3ea1" target="_blank">코드</a>

6버전 이후로 해야 함
라우팅을 백엔드말고 프론트에서

index.js로 라우팅 규칙 정의
- `<BrowserRouter><Routes>`로 일단 감싸고
- `<Route>`에서 각 라우터 규칙 정함. 여기 element 속성으로 컴포넌트 지정가능

react-router-dom에서 invalid hook call에러 발생 (일단 hook이 뭔지 잘모름 ㅋㅋ)
- 이 라이브러리 설치를 다른 터미널에서 해서 그런가? npm install을 -i -s로 해서 그런가. 


보통 index.js에서는 `<BrowserRouter><App /></BrowserRouter>`만 설정해 주고, 실제 router 설정은 App에서 리턴되는 html에 끼워넣는듯

#### props

하기전에 헤더에서 [Link](https://reactrouter.com/en/main/components/link) 컴포넌트? 추가해서 쉽게 링크 만듬 (커밋 [diff](https://github.com/frostbyte134/react-fastapi-blog/commit/156b40db2e7946a7d393e7e7ec1dfbd12c5e2bd6) 참고)

현 구조
1. index.js에서 라우팅 규칙 정의 - App만 끼워넣고 반환
2. 이러면 결국 App은 index.js에서 감싼 라우터규칙 태그 안에 있음 -> 앱에서 라우팅규칙 정의해도 됨
3. 앱에서 list.js, upload.js 임포트하고 여기 컴포넌트들을 라우팅규칙으로 각자 추가 (`/list`는 list 컴포넌트 띄우게)
4. 근데 content list state를 list.js, upload.js에서 각자 들고 있으니, 업로드해서 추가하도 리스트엔 반영이 안됨 -> 이걸 해결
5. App.js에서 컨텐트리스트를 정의해서 list, upload에 넘김 -> 문제 해결!

App.js 에서 list.js의 List컴포넌트로 스테이트/스테이트 설정 함수 넘겨주기
```javascript
<Routes>
   <Route path="/List" element={
      <List contentList={contentList} setContentList={setContentList}/>
   } />
   ...
</Routes>
```

굳이 스테이트가 아니여도 이렇게 전달가능하다고 함
- 약간..암묵적인 의존관계가 좀 생길 거 같은데?
- 자식 의 입장에선 부모에게 전달받은 걸 `props`라고 함
- (자식) 함수 컴포넌트에선 매개변수에 props란 이름으로 변수 하나 만들고, `props.변수명 / 함수명` 등으로 사용가능

우왕ㅋ굳ㅋ

[코드링크](https://github.com/frostbyte134/react-fastapi-blog/commit/156b40db2e7946a7d393e7e7ec1dfbd12c5e2bd6)


#### useEffect
아까 router는 switch-case라고 했음
- 현재 선택된 case 컴포넌트만 보여지고, 나머지는 안보여짐 = 안보여질때도 많음
- 컴포넌트에는 라이프사이클이 있음 (보여질떄/안보여질때가 이 싸이클 상태가 다른가 봄)


리액트 `hook`
- mount 전/이전 이런 것도 있는데 이건 알아서 찾아봐라
- 컴포넌트가 보일떄/안보일 때 hook을 통해 이밴트를 캐치할 수 있음
- `useEffect`하나로 혹에 대한 코딩을 전부 할 수 있음

```javascript
    useEffect(() => {
      // when component appears (when the component is mounted)
    
      return () => {
        // when component dies
      }
    }, [/* useEffect가 실행될 조건. 빈 배열 = 살거나 죽을 때만 실행 */])
```
- 조건에는 state가 들어갈 수 있음 - state가 들어갈 시,  컴포넌트가 아니고 해당 스테이트가 살거나 죽을 떄 실행
- component lifecycle에 대한 이해가 있어야 한다고 함. 난 뭐 아직 모르니까. 이 떄 서버랑 통신/데이터를 받아오는 경우가 많은 듯?

[코드 링크](https://github.com/frostbyte134/react-fastapi-blog/commit/ca7c7d60d242c3ed53e37efb33c3c986c10425a9)


### Chap 2

#### express
node.js 기반 웹 앱 https://expressjs.com/ko/

시작하기대로 설치
1. `npm init -y` -> package.json 설치
2. `npm i express@4.17.2 --save`
  - `npm audit fix` 하래서 함. 뭔진 모름
3. [hello world](https://expressjs.com/ko/starter/hello-world.html) 예제
4. `package.json`에 script에 `"start":"node index.js"` 추가 -> `npm start`로 실행

클라이언트에 가서 `npm run-script build` 실행 -> 리액트의 App 컴포넌트가 들어간 build 폴더를 빌드함 (원랜 이걸 그냥 리턴하는 서버? 를 띄웠겠지?)
- 여기엔 우리가 만든 js를 압축해서 임포트하는 index.html가 있음

이제 express 서버에서 이 `/` path에서 sendFile로 응답으로 이 html을 반환할 거임 -> 왜?
- 결국 리액트 서버 - express 서버 구조가 아니고
- 리액트 (static html file) - express 서버 구조로 가는 듯?
- 또 해줘야 하는게, 저 리액트를 빌드한 build 폴더를 static용으로 쓸 거라고 express에 알려줘야 함. `pp.use(express.static(path.join(__dirname, "../client/build")))`

익스프레스를 매번 켜기 귀찮으니, 노드몬? 을 써서
- `npm i nodemon --save`
- ? 안돼서 찾아보니 `sudo npm install -g nodemon`하고 맥북 비번 입력하라 함
- 이걸 start에 등록함 `nodemon index.js`

[코드](https://github.com/frostbyte134/react-fastapi-blog/commit/5eefb6d2dda57f8a688377aa2dba32dfb182a3af) - 스태틱파일때매 디프가 깨지네..깃이그노어 등록할껄
- `node_modules` 때문이었ㅇ.ㅁ 깃이그노어에 등록함

#### mongodb

서버의 역할 - html 제어 및 routing
- but react에서 라우팅규칙을 정의할 수 있고 우린 이걸 쓰기로 함
- -> 이러면 서버는 라우팅을 하면 안됨 -> 어느 uri로 오든 `/`로 보내야 함 -> 정규식 이용 (from express)


몽고 - 몽고디비 아틀라스 신청
- 왜 신청하지 ㅡㅡㅋ 난그냥 로컬 몽고디비 쓰기로 함
- 몽고 관리용 라이브러리 설치 `npm i mongoose --save`
- [mongoose](https://mongoosejs.com/)

connect().then().catch() -> js의 `promise`를 봐야 한다고 함

[코드](https://github.com/frostbyte134/react-fastapi-blog/commit/f64c07d6d5890f48279d0b10627daa0d6bf2ecd4)

#### axios and cors
`cors` = cross origin resource sharing
- 브라우저에서 어떤 리소스를 허용하고자 할 떄, 다른 포트에서 온 정보들에 대해서 보안 규칙을 지켜야 한다
- `axios` 라이브러리로 처리 (프론트에서)

프론트에서 `http://localhost:5000/api/test`로 (브라우저 내에서) 서버로 요청을 보내도 에러가 뜸
```
Access to XMLHttpRequest at 'http://127.0.0.1:5000/api/test' from origin 'http://localhost:3000' has been blocked by CORS policy: No 'Access-Control-Allow-Origin' header is present on the requested resource.
```
이게 cors구만

[http-proxy-middleware](https://github.com/chimurai/http-proxy-middleware#readme)를 이용해서 해결할 거라고 함
- 아니 [이 페이지](https://create-react-app.dev/docs/proxying-api-requests-in-development/#configuring-the-proxy-manually) 보고 그냥 읽어주는 느낌인데

src/setupProxy.js에 다음 내용 추가하고 성공 (브라우저에선 'http://127.0.0.1:5000/api/test' 말고 '/api/test'라고 해야 함. 전자는 axios 적용 안됨)
```javascript.js
const { createProxyMiddleware } = require('http-proxy-middleware');

module.exports = function(app) {
  app.use(
    '/api',
    createProxyMiddleware({
      target: 'http://localhost:5000',
      changeOrigin: true,
    })
  );
};
```

클라이언트에서 `/api/test POST`할때 뒤에 대충 json 하나 (req body)로 넣었더니, 서버에서는 undefine가 뜸
- `body-parser`사용 필요? (express의 내장 모듈)

[코드](https://github.com/frostbyte134/react-fastapi-blog/commit/77db1a3428b6c054febc4d45e37a9c146e582280)



#### Mongoose
몽고디비의 모델 = 스키마를 감싸주고, 스키마를 쓸 수 있게 해줌
- json 스키마에 대한 facade?


mongoose db명 = connection string에서 바꿈
- colleciton name: 스키마 닫기 전에 옵션으로

```js
const someSchema = new mongoose.Schema (
    {some_schema},
    {collection: "Posts"}
;)
```

편하네 ㄷㄷ 파이썬에는 json schema정하는 거 없나? 그냥 파이덴틱 써야 하나..

<a href="https://github.com/frostbyte134/react-fastapi-blog/commit/dde77f39e5ed4de838c4f3d80be15a44ec937322" target="_blank">코드 diff</a>

#### React Bootstrap
부트스트랩: css 템플릿 프레임워크

리엑트를 위한 react-bootstrap이 따로 있음
- 나오는 순서에 따라 설치 ㄱㄱ
- `npm i react-bootstarp@5.1.3`

`import { Button } from 'react-bootstrap'` 처럼 중괄호가 있는 이유 - export할 때 여러개가 있어서 중괄호로 export했기 때문

cdn방식으로 스타일을 가져옴
- html파일에 `<link rel ...>`을 넣어줘야 하는데, 리액트에는 `index.html`밖에 html파일이 없음 -> 여기 해더 내 마지막에 선언 

헤더영역을 꾸밀 것 - nav bar에서 가져올 수 있음
- 기본적으로 반응형

인라인이 css 모듈보다 우선됨

<a href="https://github.com/frostbyte134/react-fastapi-blog/commit/64cdb934694ad60ff101cc3a058e3c15df10d720" target="_blank">react-bootstarp 코드 diff</a>

### emotion
포스트 업로드 페이지는 직접 만들껀데, 이 때 css라이브러리로 `emotion`을 쓸 것

좀 기네 ㅋㅋ 나중에..