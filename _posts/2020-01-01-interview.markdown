---
layout: post
title:  "Interviews"
date:   2020-02-09 09:59:00 +0800
categories: coding
use_math: true
tags: coding
---

Also interviews are not only solving problems, it's also about showing that you understand the problem, your solution, what corner cases to cover, how to test and how to discuss it with others


### Amazon
Status: 3 YOE
Position: SDE 2 at a 2nd Tier Tech Company
Location: Boston, MA
Date: Feb, 2020

I've read many interview experiences on this site, it's lead to effectively preparing for my interviews so it's my turn to give back.

Premise
I've been seeing a girl since college (6 years relationship) and after graduation, we ended up getting different jobs on both sides of the country. She worked at MSFT in Redmond while I was in Boston. After 1 year of long distance, I decided to leave my current company and move in with my GF. We planned this decision a long time ago but I didn't start really practicing until October 2019. So that gives me about 4 months of practice. I started slow day one but ended up doing about 3-4 hours a day on a work day and 8-10 hours each day on the weekend with lots of breaks in between. The month December and January is where I went really hard and I had most of my interviews in Feb. The investment was real, I figured I had a single opportunity to improve my quality of life so why not give it my all. Over the course of studying, I found the practice in coding and system to be very helpful to my day job where it lead to success in design discussions. I set up 7 onsites with Amazon, Google, MSFT (3 teams), Zillow, Redfin over three weeks of interviews.

Tools that helped me succeed:

Leetcode premium - worth it, I started slow at first but ended up completing 47/128/49 easy/med/hard problems in 4 months.
Grooking the system design interview - this was what passed my system design at amazon.
Youtube - I watched several mock system design interviews to get a sense of what it was asked and this was incredibly helpful.
System Design Primer (donnemartin) - good system design finger food
DanCroitor - the best LP preperation you could do
Questions to ask after your interview - this makes you seem smart and care about the work to build additional trust with your interviewer
The Entry
A recruiter found me on LinkedIn so I chatted with him over the phone. He asked me about my work experience and two LP questions "what-if questions". They weren't really technical and I answered generally. He scheduled me for an OA.

OA
Standard two hour online assessment, two questions and self evaluation.

https://leetcode.com/discuss/interview-question/411357/ all test cases passed
https://leetcode.com/discuss/interview-question/460127/ (Top N Competitors/Buzzwords ⭐⭐⭐ [Experienced]) 19/21 test cases. When I reflect why it was not fully passed, I forgot to consider the case where a popular toy's name has an apostrophe or a special character in it like ["popeye's", "beyblade!"]. I used a brute regex in java (\W+) to tokenize the string.
The recruiter contacted me right after saying I did well and scheduled me for a onsite for 3 weeks later.

On site
I had a very enjoyable time interviewing with Amazon. They respected me and allowed me to take breaks in between. They flew me into Seattle and put me in a nearby hotel. I woke up at 7am that morning, naturally because of EST time, had a good breakfast and went to the office for interviews from 8:30 to 12:30. I was extermely nervous, palms sweaty, and in the back of my mind I had a sense of pressure that I could not f@ck this up and everything was on the line (in fact the pressure helped me succeed in a way, more on this later). I tried to talk to another dude that came to interview to try to drown out my stress, which it helped. As soon as I started my interviews, I think I just let my personality do the talking. As a reflection, the interviewers have two phases, LP and technical. If the interviewer asks the coding question first, I found a positive correlation between doing well in coding means the LPs will go smoothly as well.

The first interviewer started off asking LP for 30 minutes. He really dug into my past, I was not prepared to go that deep and I wasn't sure how well I STAR formatted the answer. After thirty minutes, I was given a question was about "given a file of parents and children of humans", write me a function to tell me the parent with the most direct children. This was simple. Follow up was "change your code to return the parent with the most children/grandchildren at n generations away". My initial verbal answer was DFS which was wrong (nervous), but when I started to code, I realized it was a BFS and I've done a ton of those on leetcode. Similar to https://leetcode.com/problems/all-nodes-distance-k-in-binary-tree/
The second interviewer was the bar raiser. He started off with the system design question: build uber. Now there are example of this on Youtube (search designing uber) and Grooking the SS interview that I read so I was fairly prepared. Being hit with this question in reality was not the same as the books, no constrains were given, no requirements given, you must ask everything. I started off with the functional and non functional requirements. I drew a very high level design of app, servers, and database on the board and then I went into thinking about the use cases. I asked my interviewer what use case should I design first, he said the driver discovery feature, so I ended up drawing a sequence diagram on what services this feature migh touch. Broken up into application servers, search servers, quad tree servers, notification servers, and several others like google maps services. He asked several other follow up questions which I then added to my sequence diagram which now spanned the entire white board. He challenged me on how I would attain my non-functional requirements (speed, consistency, etc) and I replied with all the knowledge I got from the Grooking SS course. After the system design was over, I felt really good about it and we went into LP. He asked what I have invented at my previous job (plenty as we are a medium sized company), when have I ever exceeded my expectations. I worked on a generally impact piece of the business so his questions were easy for me to answer. I know not everyone reading this will have the benefit of leaving an impactful position. My advice is to critically think how you can tell your story to make it sound impressive. Say "I" more than "we", explain what tools and tech you used in detail, and give quantitative results (I cut down algo time by 10% etc).
The third interviwer asked me a coding question first. The requestion related to sumarizing statistic from a log file. I had to do some simple maths here. The interviewer was very helpful and would confirm my answers immediately which gave me confidence (unlike my other interviews at other companies). When I was done, the follow up question was how to extend the log parser if we wanted to make it extensible to keep track of more fields. I tought the Visitor pattern would make sense here, each log line is visted by multiple stat collectors that only take what the collector should keep track off. The interviewer was impression with this application of the design pattern, and the LP questions went really smoothly. The LPs question had asked when I have taken initiative to design something.
The last interview was with two folks, I think there was one person shadowing. At this point my brain was pretty fried from all the talking so I was on cruise control. We started out with LP, we went into a little bit about a time when I made a decision and committed to it. I talked about my previous projects and drew some architecture diagrams on the board. The coding question was implement an LRU with a product usecase. I think it was a spotify music playlist. I got it done in 10 minutes using a LinkedHashMap. Then the interviewer challenged me to implement my own LRU, with my own static node class and pointere management. I had to be very careful when implementing a doubly linked list when changing the pointers around. As I was coding I spoke everything out loud because my brain wasn't working, but my mouth was. If I made a mistake and it sounded wrong, either I or the interviewer would react and allowed me to fix it. I finished the implementation with the nick of time left and I was escorted out of the building.
Aftermath
I had lunch near the Amazon campus, took a walk near South Union lake to relax and reflect. Got an email from my recruiter 3 hours after the interview with an invitation to talk the following Monday. Since I did my interview on a Friday, this was really fast turn around. I stressed over the weekend and got a call on Monday telling me that I will be getting an offer. I was really estatic... so happy that I bombed my next interview at Google, knowing that I secured my place already for the move. Don't be me, stay focused! Hold your emotions in when you get an offer or else your brain will not be incentivized to work hard. My initial offer was high, but not the number that I asked for: 260k TC. The recruiter and I shared feedback and I told him that I'll be pursuing onsites at multiple places. It was approximately two weeks until I would get my next offer at MSFT. Due to burn out and competition, I canceled my Redfin, Zillow, and one of the MSFT interviews. Interviewing back to back days proved to be difficult for me in a variety of ways, something I would never do again.

At last, it was a MSFT vs an Amazon offer. I spent 10 days negotiating back and forth with the amazon recruiter. I tried to be as nice as I can to my recruiter, complementing him on preparing me for success (because the recruiters will reach out to you before the interview and give you a study sheet) and replying to his offers with respect. Used words like "the offer is really nice, but I was hoping we can do more..." and "I really appreciate what you put together for me but I have to commit to my other interviews...". Eventually, on the last day of offer expiration, I choose Amazon because the sign on bonus was high and that money is paid out to you in the first two years that don't need to vest. I think this was a right choice as we see what's happening in the market these days. Yes, Amazon bonuses are almost non-existent (expecially for the first 18 months) and benefits are not great, but I'll probably marry a MSFT employee and jump on her insurance plan, I would advise the same for anyone who joins Amazon.

The offer: https://leetcode.com/discuss/compensation/535277/Amazon-or-SDE-2-or-Seattle

Wish everyone best of luck interviewing!

### Google
Sorry this post is going to be long :)
Leetcode has always been a huge help to me. My daily routine has been opening the discussion tab and reading others experiences of which so ever company they applied into, I felt like even I had to contribute into this community. I didn’t go anonymous this time :P

YOE: 0 (Pursuing last semester)

I was contacted by google recruiter on 29th November 2019. I did not expect any response back. Mainly cause this has been the case in all the other companies I applied into-Microsoft, Apple, Facebook etc. Being Google my dream company, getting a response itself was a huge thing to me. They asked if I was available for a phone interview in the coming week which I wasn’t able to as I was in the process of having my semester end exams. Scheduled the interview just after my exams ended that was on 18th December 2019.

Phone Screen:
I was asked one major question and then follow ups on the basis of the question. The question in layman terms was that we were given a long string like ‘Every breathe you take, every move you make’ and another word-‘boom’, we need to find the shortest string where each letter of the word 'boom' is present in one word of a string at a time i.e the output here will be: ‘breathe you take, every move you make’ and print it. I did this via sliding window with O(n) complexity and space. After that there were couple of follow ups which I was able to answer.

I was contacted by my recruiter the very next day and was told that I have been selected to go for onsites. I was extremely happy on hearing that I didn’t have another phone screen. Since we were approaching the holidays I was told that my interviews will be happening in January. When my recruiter contacted my again, I told her that I wanted some time to prepare as whatever be the result I just didn’t want any regrets on my side that I was underprepared. Thankfully my recruiter understood that and I was able to schedule my onsites for 12 February 2020.

Onsites:
Round 1: Technical
The interviewer that came in had a 8 YOE. The question he asked me was that we are given a dictionary where every animal has a start and end year at time they existed. Given a year list out all the animals that exists in that time. This was the general question and then we had follow ups. I don’t remember everything but it was on the lines of intervals problem and I solved it via Binary search.

Round 2: Technical
The next interview I had was over hangouts. The interviewer asked me a BFS and DFS question. The question was that there was a grid given with each number being the height of a place where you are standing. You can move ahead to the next place only if the difference between the point where you are standing and the next is more that the threshold given. Find whether you can reach there or not. I was able to tell both BFS and DFS+backtracking question. I coded up the BFS solution. We had discussion for follow ups but I was unable to code the follow up.

Round 3: Googlyness and Leadership
This was the Googlyness and Leadership round. It went well but that depends from person to person :)

Round 4: Tecnical
The question asked here unfortunately I don’t remember that well. I was able to solve it quickly and was able to micro-optimise it the best. The question was on basis of heaps and arrays. Even though it was my best interview I can’t recall the question well. Sorry about that.

Round 5: Tecnical
If the previous round was my best round, this round was my exact opposite round. The question asked was given digits 1-9 with each digit associated with a value. Now we have a wall that needs to be painted with those digits and each digit painted requires the value volume, you need to form the largest number possible from this. Given that the sum of the volume of the number is equal to the wall volume.

Input:
```
1 2 3 4 5 6 7 8 9
1 3 1 5 6 7 2 5 2
```
wall volume: 5
Output: 33333

I gave a solution with backtracking but it took the complexity of O(n!). I gave one with DP as well on the lines of coin change with complexity of O(n^2) in time and space as well. But was unable to optimise it further. After discussions for 35 minutes, I was unable to come up with a better solution. Ultimately the interviewer changed the question to a BFS question, which I was able to code up in 5 minutes. After that the interview ended. I was crushed by the last round knowing that if I had a rejection it’ll be mainly because of this round.

I didn’t hear back from my recruiter for a month until just few days back letting me know that I was rejected. Even though at the back of my head I knew this was going to happen but still it crushed me. I was told that my interviews had no major red flags and I am strong with my coding skills and my code quality is good as well. But I take time to code as well I require hints. My googlyness round recommended me as a strong hire as well as Round 1 and 4 too. In Round 2, I messed up my time complexity analysis which was the reason for my average rating in that. Round 5, I knew I screwed up as well as I was told my DP skills are weak. Being a borderline case, I was told to appear again in a year :)

After preparing my heart and soul for this interview for almost three months, Am I sad?-yes, absolutely. But even when the rejection came, I didn’t feel any regret mainly because I did whatever the best I could do. I studied loads on Leetcode, pretty visible from the amount of questions I did. I covered so many new topics I never did before. So I’m pretty sure I am not the same coder as I was four months ago. To everyone who appeared, or is in the process I just want to say that:

Never compare yourself to another person-be it over here or anywhere. If that person has done 80 questions or 800 it doesn’t matter to you. Just be yourself and do your own preparations.
Rather than doing 100 questions of one type, do one question of 100 types. It’s better to do more in quality than in quantity.
If you need more time, just ask the recruiter. They are on your team and will try there best to help you-So be thankful to them.
Interview process is long and tedious. The onsites feel pretty long so just be calm and work through the day. I felt that my interviews went great cause I took all of them more like a discussion rather than an interview itself.
Don’t take interviews as a Do-or-die situation. It is not the end of the world and panicking will never lead you anywhere. Being nervous is alright but don’t let that nervousness hinder your interviews. The interviewers are there to help you and they want you to suceed as well.
Get your feedback straight. Know your weak points so that if you appear again or try somewhere else, these points are not the reason for you to fail.
Rejection always hurts but I feel like this rejection is what motivates me to do better. I failed but I learnt so much more that I don’t see it as a negative experience. Maybe one day I will get into Google and then I will remember that I did struggle a lot but that is what makes me what I am today :)
Luck factor will always come into play and interviews are a gamble of luck. You can just try the best you can as to never have any regrets.
I went to write this post as a way to let go of my negative thoughts that I started having post rejection. After four months of preparations it does hurt but there's nothing I can do about it now. I can only learn more and more and try again.

If you were able to read this long post, thank you so much for reading it. I hope you were able to get something out of it. To anyone appearing for any onsites - All the very best. I hope you clear it :)

P.S: I was told that My DP and Time analysis is weak. If you can tell me any resources worth studying to get them strong. And just not DP, recursion and backtracking as well. It’ll be of great help :)

TODO: 급할 건 없으니까 (...) 천천히 완성하기. 제목 수정

### 0813 인터뷰
까먹기 전에...  
면접은 쉬울 때가 없네 ㅜㅜ

load_average : 의미를 말하지 않고 헛소리만 좀 했던듯. 실제 계산중 + IO load로 구성되어 있다는 점을 잘 말했어야 했음.


TODO: 날짜 지우고 내용 따로 묶어서, 내용 보강

1. 좀비프로세스는 힙을 남겨 놓는가? 난 GPU메모리를 좀비프로세스가 잡아놓는걸 생각해서 남겨놓는다고 말했는데..
   1. 일단 아는대로 heap은 per process https://stackoverflow.com/questions/3147014/is-heap-memory-per-process-or-common-memory-location-shared-by-different-proc
   2. https://unix.stackexchange.com/questions/272278/defunct-processes-remain-behind 남겨놓는 것 같은데. 근데 자세한 내용이 없네
2. 왜 좀비 프로세스가 있는가? 해제해버리면 되는데. 답을 잘 못함. 디버깅 때문이라는 힌트를 줘서 그걸 입밖으로 말한 정도 ㅡㅡㅋ
3. 윈도에서 우분투 도커를 만들 수 있는가? 되네 ㅡㅡ; https://medium.com/rkttu/wsl%EC%97%90%EC%84%9C-native-docker-%EC%8B%A4%ED%96%89%ED%95%98%EA%B8%B0-ff75b1627a87
4. 또...? 파이썬 멀티프로세싱을 쓰기 좋지 않은 상황? 이런게 있나?? 파이썬만의??...찾아봐야 할 듯. 크롤러ㅇ를 원래 염두에 두신 것 같은데...


결국 이직 이유에 대해 또 답을 잘 못했다.
1. 상무님이 반도체 출신이라고 했어야 했나...? 뭔가 상무님을 까는 것 같은 느낌인데..
2. 너 또 도망갈꺼 아니야? 에 대답할 수 있는 확실한 답이 필요한듯. 어렵다...
3. 감사하다고는 말할 수 있었지만 (많이 배웠습니다도 했어야 했을듯...) 마지막에 뭔가 갑분싸였다. 질문을 좀 더 생각했어야 하는데..평소에 질문 생각하는 훈련 좀 할껄.

역시 월차가 답이었다. 이멘탈로 회사갔으면 걍 멍때렸을듯. 면접이 오후에 잡히는게 차라리 좋을 듯 한데...


### 0805

#### 추가
1. 문제풀이 - 업무용 언어 바뀔때 이용 (파이썬, C 예시로 들자)


#### 옮기는 이유
1. 딥러닝 쪽을 못말하다 보니 (내가 생각한 뱡향과 주제가 어긋나다 보니) 이직 이유를 잘 말하지 못했다. 그냥 지금 있는 팀이 못해서 나간다 처럼 되어버림. 사전 조사가 부족했다고 할 수 있는걸까?
   - 우선, 저는 지금 제조업 회사를 다니고 있는데, 제가 하는 프로젝트는 IT쪽입니다. 주력 아이템이 아니다보니 프로젝트의 방향이 굉장히 불안하고, 윗분들도 자주 바뀝니다. (고용안정성은 있지만 프로젝트 방향 안정성은 없음) 이력서에 썼다시피 난 길에서 사람들이 써줄 만 한, 높은 수준의 무언가를 만들고 싶은데 이 상황에서는 불가
   - 둘째는, 우리는 선행/양산으로 구분하는데 내가 맡은 건 높은분이 단독으로 추진한 선행프로젝트였고, 좋은말로 하면 도전적이지만 나쁜말로 하면 선행의 선행 같은 분야였다. 나는 굉장히 도전적일 것 같아 지원했는데, 막상 들어가보니 내가 방향을 정할 ㅅ순 없었고 주어진 상황에서 최대한 잘 해야 (위에도 어떻게 잘은 모르지만) 하는 상황. 나는 방향이 좀 잘못되었다고 생각하고 여러 번 말했지만 먹히지 않았고, 1년 반 이상 위에서 시키는 것과 내가 생각하는 방향을 동시에 진행하는 상황. 위에 말한 것과 겹치며 이직을 준비하게 되었다.
2. 그렇더라도..좀더 일반적인 관점에서 풀어서 설명한걸 준비했으면 어땠을까. 잘 뒷받침이 되는걸로다가.
3. 업무 싸이클이 연구 -> 양산 (Mission Critical) 으로 바뀌는건데 준비가 되어 있나? 도 준비를 헀어야 했음
4. 내가 자율적으로 업무를 주도해나간다는 사례?
5. 최근에 어려웠던 것?
    - 제3자도 이해하기 쉬운 spec 문서 만들기

#### 커뮤니케이션
1. 업무 조율 방법, 경험? (기획자 등 비개발자도 포함하여)
2. logic / engine / front-end 의견 충돌시? 본적이 별로 없어서 잘 모르겠지만 우리 양산쪽하고 대응해서 생각해 봐야 할 듯

#### 기술
1. fork시 메모리가 복사되는데, 엄청 큰 메모리도 바로 복사되는것처럼 보이는 이유는? 난 메모리맵 어쩌고로 헛소리했는데 demand paging 이야기였음. malloc할때 demand paging은 생각했었는데ㅡㅡㅋ fork도 내부에서 말록같은걸 쓰겠지?
1. socket의 epoll (multiplexing과 관련있다 함)
    - select는 fd_set이라는 구조체를 통해 fd들을 등록하게 되는데, 불행하게도 이 fd_set는 bitmask라서 1024개까지만 등록할 수 있다 (커널을 뜯어고치면 늘릴 수 있다는 말도 들어본거 같기는 하다만...). 게다가 이벤트 발생을 감지하기 위해 내부적으로 순차검사를 시행하므로 동시접속이 늘어날수록 불리해진다.
    - epoll에 file descriptor 등록 가능
        1. epoll_create로 커널 폴링공간 생성 (여기는 동일한 점)
        2.  `epoll_ctl`로 fd와 (해당 fd에 관심있는 event 등록) 
        3.  `epoll_wait`에서 사건들의 리스트를 (epoll_event).events[] 의 배열로 전달받음 (여기가 차이점)
2. file descriptor 개수가 바닥나면? 이 주제 예전에 어디서 봤는데...조사해보자
    - Yes, file descriptors are local to the process. When a process forks a child, however, the parent and child have the same file descriptor table. This is great because it allows for IO redirection, which is a pretty handy trick. - `epoll`에 등록가능
    - epoll의 정체성  (<a href="https://ozt88.tistory.com/21" target="_blank">https://ozt88.tistory.com/21</a>)
    epoll은 select의 단점을 많이 개선한 형태의 통지방식이다. FD_SET을 운영체제가 직접 관리하는 것으로 많은 부분이 개선되었다. 하지만 그 본질적인 동작 구조는 select와 크게 다르지 않다. 프로세스가 커널에게 지속적으로 I/O 상황을 체크하여 동기화 하는 개념은 여전히 유효하다. (__첨에 epoll_create로 커널 폴링공간 생성!__) 따라서 epoll의 통지모델 역시 동기형 통지모델이다.  
    그리고 timeout개념이 select와 동일한 방식으로 동작하기 때문에 timeout에 들어온 인자가 어떠냐에 따라 blocking이기도 하고 non-blocking이기도 하다. 따라서 epoll의 전체적인 개념모델은 select와 같다고 생각한다.  
    (차이점 - epoll_wait함수는 관심있는 fd 들에 무슨일이 일어났는지 조사한다. 다만 그 결과는 앞서 살펴본바와 같이 select나 poll과는 차이가 있다. 사건들의 리스트를 (epoll_event).events[] 의 배열로 전달한다. 또, 실제 동시접속수와는 상관없이 maxevents 파라미터로 최대 몇개까지의 event만 처리할 것임을 지정해 주도록 하고 있다.)
    - `c10k` problem 풀어보기
3. distributed sort - merge sort를 쓴다고 함 (K-way merge땐 tournament method. 이거 생각 났는데 말을 못했다 )
    - 그냥 각 머신에서 분산으로 heap을 구성한다고만 했음. merge sort는 뭔가 chunk와 연관된 최적화가 있는 듯 (그 selection 관련해서도 있을 수도)
    - <a href="https://stanford.edu/~rezab/classes/cme323/S16/notes/Lecture04/cme323_lec4.pdf" target="_blank">https://stanford.edu/~rezab/classes/cme323/S16/notes/Lecture04/cme323_lec4.pdf</a>
4. hash collision - 값 올리기 / 뒤에 링크드리스트 달기까지만 생각나서 바로 말하고 멀티레벨은 좀 나중에 생각남 ㅡㅡ
5. crawler에 url이 1000개 있을 때, 코어갯수만큼 worker를 돌린다고 하면, 각 url마다 처리시간이 다를 텐데 이에 대응하는 방법은? 난 멀티프로세스 큐를 쓴다고 했는데 좀 더 좋은방법이 있을 듯
6. Daemon process의 생성 방법? 어디에 쓰이는지는 알았지만 어떻게 만드는지는 전혀 몰랐다. 직계 부모 process와의 연결을 끊는다고 했는데 일반상식과 달라서 당황했음
    - <a href="http://tmmse.xyz/2017/10/19/daemon/" target="_blank">http://tmmse.xyz/2017/10/19/daemon/</a>
    1. `daemon proc`에는 controlling terminal이 없음
    2. 파일디스크립터로 singleton daemon(이 용어는 없는듯 ㅡㅡㅋ) 생성 가능. 
    헐..생각보다 어려운항목이었네 ㅡㅡ
    1. <a href="https://mug896.github.io/bash-shell/session_and_process-group.html" target="_blank">https://mug896.github.io/bash-shell/session_and_process-group.html</a>
    2. <a href="hhttp://tmmse.xyz/2017/10/19/daemon/" target="_blank">http://tmmse.xyz/2017/10/19/daemon/</a>
    3. <a href="https://richong.tistory.com/180" target="_blank">https://richong.tistory.com/180</a>https://richong.tistory.com/180
    4. <a href="https://outshine90.tistory.com/entry/9-Process-RelationShips" target="_blank">https://outshine90.tistory.com/entry/9-Process-RelationShips</a>


시스템 콜/리눅스 등을 아는 것이 생산성 증대로 이어짐  
- Trouble shooting시, document대로 동작하지 않을 떄 그 이유를 스스로 추론 가능. (아무도 해보지 않은 걸 prototyping 할 때도)

잘 되든 (특히) 안되든 마지막에 시간을 내 주셔서 감사하다고 했어야 하는데 말이 잘 안 나온다. 뭐 개털린 극한상황이긴 했으니까 ㅡㅡㅋ 면접보기 전에 한번 머리에 박고 시작해야 할 듯

### Google
#### Google Interview Experience
I think now it's my turn of giving back to the community. I had been recently interviewed at Google, unfortunately couldn't clear it.

Phone Screen:

Problem : Variation of the Course scheduled problem, Given the dependency of the courses, if a course A is prerequisite for course B then course A must be completed in some semester before the semester in which course B is completed, find the minimum no. of semesters required to complete all the courses.

I could solve this problem and then I was invited for the onsite to Google's Hyderabad office. In Hyderabad office, there were five back to back coding rounds and no G & L round.

Round - 1 :

Problem - 1:
You have a machine with one core and you are given start time and end time of the programs, check whether new program can be scheduled or not. You are basically given query describing schedule of the new program i.e, [s, e] s and e are the start and end time of the new program, return true if it can be scheduled, false otherwise.

Follow-up:
Your are given machine with 4 cores (4 programs can run simultaneously) check whether new program can be added or not.

Firstly I gave the brute force solution(O(N)) then I suggested then optimized solution using binary search** O(Log N)**.

Ran out of time for the follow up question, so I could solve this partially.

Round - 2
Problem - 1:
Given an array and an integer K, find the length of longest subarray that has sum less than or equal to K.

First gave O(N2) solution, then gave O(N) solution using sliding window.

Follow-up:
Given a matrix of M * N find the size of the biggest square that has sum less than or equal to K.

First gave brute force solution, then optimzed one using DP.

Problem - 2:
Find the length of longest AP sequence which is there in the tree.

Couldn't solve this one, ran out of time.

Round - 3

Problem - 1:
You are given D units of data that needs to be transferred over the network and packet size K, find minimum no of packets required to transfer all the data.

This was a no brainer, I think this was the warmup problem.

Follow up:
Distribute data in each packet such that difference between data in any two packets should be minimum.

Round - 4:

Given an array of integers that is already sorted based on first 28 bits, solve the array by all the bits.

Couldn't solve this problem

Round - 5:

Problem - 1:

Given a binary locking system, you are also given initial and final state of the lock and all the states that are safe.

From one state you can go to another state by flipping one bit at a time and the new generated state should be same.

You need to check whether you can unlock the given binary lock or not.

Follow Up:
Later he limited the size of safe states to 100 and asked me to optimize.

First I gave the DFS solution, later optimized using DSU. couldn't derive time complexity for this solution.

Lessons Learned

Focus on speed, take the timed contests when you are preparing.
Do not take more than 2-3 minutes to discuss brute force solution.
If you already know the solution, immediately after brute force jump to it, don't waste time in discussing two three alternative approaches.
Many of you may not agree with the third point, but the thing is that when you are interviewing with google, each round last for exactly 45 mins and you are expected to write the complete code.

#### Google 2
I think it's my turn to give back to the wonderful leetcode community. I recently received an offer from Google. Following is my experience.

Journey

I have about 3.5 years of experience working as a Software Engineer. I actively started looking for Job 4 months back wherein I interviewed for Facebook and Google. I got rejected in onsite interviews of Facebook. I have solved around 110 questions on leetcode around 32 Easy 60 Medium and 20 Hard. I have found difficult implementing Hard level leetcode questions (to this date I still do).I didn't want to loose out on any of my options hence I purchased Leetcode premium which was definitely helpful for Facebook's preparation(All the questions I received in my phone screen and onsite were already part of Premium problems)although not that helpful for Google. I tried to solve problems on codeforces and topcoder back during my college days and was on and off with leetcode during past couple of months. In retrospect I should have tried to implement more problems on Leetcode as I have been scared of problems which involve heavy implementation :(

I had already interviewed with Google around 2 years back which went very bad according to the recruiter neverthless I was given one more shot.I thought I would share my Interview experience with Leetcode community below post summarises my Interview experience.

Interview Experience

Phone Screen (45 Minutes)

It was fairly easy question involving priority queue. I had already seen some similar questions hence wasn't difficult for me to come up with approach. The interviewer was happy with the approach and asked me to code it up which I did. Afterwards the interviewer found some syntatical errors in my code which I corrected immediately (nothing logical). I thought I did good.

The recruiter followed up and said the feedback was quite positive and I will move to onsite. She told me that there will be 3 Algo/DS round with 1 Algorithm Design round and 1 behavioural round. I scheduled my onsite after approximately 30 days of my phone screen.

**Onsite Interviews **

Round 1 (Googlyness)

I think the focus of this round is to eliminate false positives. I made sure to give examples for most of the questions. In retrospect I think this round went well although you can never tell :) .

Round 2 (Technical)

It was fairly easy question on rectangles. I made sure to ask some clarifying questions which helped me narrow down my approach. I could come up with n^2 solution in no time (which i think was the best possible approach). I coded the solution but the interviewer found 1 very small logical bug which I found and corrected. After which there was a follow up question for which I gave couple of different solutions although I am not sure if the interviewer was looking for some thing else. In retropspect I think this round was meh meh.

Round 3 (Technical)

I bombed this interview. It was so bad that after 25 minutes the interviewer gave up and asked me to code it up(I guess he wasn't even looking at the solution). The Question involved thinking along lines of Dp (2D dp Specifically). I was able to figure out the states quite early but it was the transition between the states which I had problem with. In retrospect this round was very bad. If I get denied it will be most certainly because of this round.

Round 4 (Algorithm Design)

The problem statement was quite easy to comprehend although I had to make sure what tradeoffs have to be considered before presenting an optimal solution and refining it further. After I clarified everything I made sure to put a brute force solution and then afterwards an optimal approach using Stacks. The interviewer asked me to code it up which I did. The interviewer looked happy with my code and no modifications was required in the code. The key in this round is to balance thinking part with coding part. In retrospect I think I did well in this round

Round 5 (Technical)

This was my best round. The problem statement was an easy graph problem which I recognized and gave the interviewer the most optimal solution. The interviewer seemed happy with my approach and I coded up instantly in C++. We still had around 15 mins left so there was a follow up question which I was able to explain but there wasn't any coding part involved. In retrospect I think I aced this round.

Post Interview

After 1 week the recruiter reached to me telling that my feedback was tending positive although it's mixed. I was well aware that this was bound to happen. I also have to talk to Managers from different teams this week for Team matching(although I am not sure if this will help Hiring Committee or not). Fingers crossed 🤞. I think I have like 20% chance since I completely bombed one of my interviews. What do you guys think ?

#### Amazon - India
Getting help from the Leetcode community for a long time. I just wanted to give something back as well. :)
I gave an amazon interview last week and wanted to share my experience. I had given an online test prior to the onsites some time back but i do not remember the questions that well. Two weeks later, I was asked to come for onsites.
Pointers before discussing about onsites questions:

Every round was a coding round alongside LP round.
The rounds also consisted of a few questions asked in relation to core subjects like Operating Systems, DBMS, Networks etc.
Each round had atleast two coding questions asked.
Each round went on for atleast an hour in my case
Round 1: I was asked two questions. Both being from leetcode and of medium difficulty. Topics begin Trees and Arrays.

Given a binary tree and a sum. Find if there exists a path from root to leaf with sum of node values to be equal to the target value given.- https://leetcode.com/problems/path-sum/
I was able to come up with an O(n) solution and was able to code up pretty fast.
Trapping rainwater problem-https://leetcode.com/problems/trapping-rain-water/
This is a pretty well known problem and I did remember it doing a long time back. I had a discussion with the interviewer and was able to come up with an O(n) time and space solution. We went further discussing on STLs in C++ and couple of other topics.
Apart from this there was a resume discussion and couple of LP questions as well.
Round 2: Questions again were from leetcode. The topics asked were from stacks and heaps.

Given a stream of integers, find the median of numbers at any point.
I had never seen this question before hand, but first come up with a brute-force approach, but with a couple of hints from the interviewer I came up with a heap solution there. Later saw that this question is pretty well known leetcode-hard question.
https://leetcode.com/problems/find-median-from-data-stream/
Perform Push, Pop and Get_Min in O(1) complexity.
This question was easy and I had a good discussion with the interviewer about different approaches.
Here I was asked questions from OOPS and Networking. I was able to answer question from OOPS but unable to answer the questions from networking.
Round 3: I was asked three questions in this round. I was asked mostly DP and one Heap question in this round.

The question was given s1, s2, s3, find whether s3 is formed by the interleaving of s1 and s2.
I had never seen this question before and DP being a weak spot for me, I was unable to come up with a DP solution of this problem. I gave a recursive approach but was unable to further optimise it. Later found out that this question was available on leetcode as well.
https://leetcode.com/problems/interleaving-string/
The next question was again from DP, and I had seen the question before. The question was Decode Ways-https://leetcode.com/problems/decode-ways/
I was able to come up with both a tabularised and a recursive approach for this problem. I had a good amount of discussion with the interviewer on this question.
Later on, I was asked the question on K-frequent words from a stream of words incoming. I was able to come up with a brute force solution and then the interviewer asked me to code it up. Post that we had a discussion on everything in relation to designing of the hashmap and priority queues which was in relation to the question.
The interviewer also asked a couple of DBMS questions like ACID properties and some SQL queries.
Round 4: This was the last round. I was asked two questions here. I bombed this interview pretty badly, even though I was able to code it up but I took a lot of time even though the questions weren't that tough.

I was asked a couple of LP questions and things from my resume. Even though I was able to answer LP questions comfortably, I had not revised my resume projects that thoroughly and the interviewer went in depth analysis of my projects where I was unable to answer a couple of questions mainly because I hadn't revised.
It was a graph problem to be done using minheaps. I coded up that solution pretty fast. We had a discussion on minheaps and I was asked to write a code for minheap extraction which was the part where I made a mistake. I got confused in one point and I took a lot of time thinking and kept getting confused further. After sometime, the interviewer started getting slighly frustrated gave me a hint from which I was able to code up the question. I got so nervous and then gave the incorrect complexity analysis of it.
The second question was Word ladder - https://leetcode.com/problems/word-ladder/
I gave the brute force analysis and since I was nervous from the prior mistake I ended up again giving incorrect time complexity analysis. The interviewer helped me a bit further and I was able to come up with a optimised solution but since I had already taken a lot of time, I was unable to code that up.
Mistakes that I actually learnt from after giving the inteviews:

Revise everything on your resume that you think can be asked from you. Getting rejected just because you weren't able to answer something you had done a long time back sucks badly.
Even if you have made mistakes in one round or asked too many hints don't let that boggle you down. Consider every question a new opportunity in that interview irrespective of how the previous one went.
Get your time complexity analysis right. I realised that this concept still is an extremly weak portion of mine.
Interviews are luck based, but the only thing you can do is give your best shot so that you never have regret of not trying.
Rejections happen all the time and I'm pretty sure everyone here must have faced that atleast once. Just take it as a learning experience and move forward. Maybe that company wasn't for you right now, but that doesn't mean it will never be in the future.
I hope this experience is helpful to anyone who is trying in Amazon and I hope you do get in. All the best :)

