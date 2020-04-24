---
layout: post
title:  "Leetcode problems"
date:   2020-02-09 09:59:00 +0800
categories: problem_solving
use_math: true
tags: problem_solving leetcode need_review
---

solve the problem while explain it to yourself, and write examples (must!)

TODO: make a post on
* https://www.educative.io/courses/grokking-the-system-design-interview


### divide array in sets of k consecutive numbers (need review)
<a href="https://leetcode.com/problems/divide-array-in-sets-of-k-consecutive-numbers" target="_blank">https://leetcode.com/problems/divide-array-in-sets-of-k-consecutive-numbers</a>
* 일단 하위30퍼로 풀긴 풀음
* consequtive란 단서 때문에 더 빠르게 풀 수 있음. 그림을 잘 그려 보자

### minimum distance to type a word using two fingers (need review)
<a href="https://leetcode.com/problems/minimum-distance-to-type-a-word-using-two-fingers/" target="_blank">https://leetcode.com/problems/minimum-distance-to-type-a-word-using-two-fingers/</a>
* 일단 O(KN^2) dp로는 쉽게 풀음
* <details>
   <summary>O(N)</summary> iterative dp로 풀면 K를 없애도 됨. 왼/오를 구분하지 않아도 되고, 항상 한쪽 손가락만 움직이는 경우보다 얼만큼 절약할 수 있나를 a[26] 상태공간에 넣으면 O(N)임 
   </details>

### Hand of Straights	
- consecutive한 그룹으로 숫자를 쪼개는 문제 (미디엄). counter 배열로 해결. 어서 풀어본 거 같은데..
- 각 그룹이 conseq한 숫자들로 이루어져야 하기 떄문에 답이 있다면 구성이 deterministic함

### Robot Room Cleaner
- 재밌는 하드 문제였음
- __범위가 주어지지 않은 보드판__을, 로봇이 front / left, right만 갈 수 있을 때 완전탐색하는 법
- 상대좌표로 vis를 찍는 dfs. dfs이기 때문에, 돌아오는 연산도 구현해 줘야 함 (왼2, 전진, 다시 왼2). 안그럼 vis가 정확하지 않기 때문에 무한루프 돔. 


### delete nodes and return forest
- <a href="https://leetcode.com/problems/delete-nodes-and-return-forest/" target="_blank">https://leetcode.com/problems/delete-nodes-and-return-forest</a>
- 복습까진 필요없는 듯. 중복정보를 본인도 처리하고 자손도 중복으로 처리해서 느렸다. 자손에서 return으로 보내 줬으면 됐을 껄...이거 면접에서 이래 죽쓰면 풀긴 풀었는데 감점 엄청 당할듯.

#### Minimum Swaps to make subsequences increasing
* <a href="https://leetcode.com/problems/minimum-swaps-to-make-sequences-increasing/" target="_blank">https://leetcode.com/problems/minimum-swaps-to-make-sequences-increasing/</a>
* 일단 O(N * range(val))dp로 풀음
* <details>
   <summary>다시 풀어 보기</summary> O(N) dp로 가능. swap[i] = i번째 스왑이 일어났다는 가정 하에, 필요한 최소의 스왑 / notswap[i] = i번째 스왑이 일어나지 않았다는 가정 하에, 필요한 최소의 스왑. 밑에번부터 어떻게 채울지 생각하면 풀린다. 
   </details>

#### Split Array into Consecutive Subsequences
* <a href="https://leetcode.com/problems/split-array-into-consecutive-subsequences/" target="_blank">https://leetcode.com/problems/split-array-into-consecutive-subsequences/</a>
* 무식하게 풀었던 거 같음. 구현연습에 좋은듯.
* 아니면 각 숫자별로 count 샌 다음에 없애면서 나가도 되지 않나?
* <details>
   <summary>다시 풀어 보기</summary> 그리디하게 가능. 작은 숫자부터, 1. 이 숫자가 기존 list의 맨 뒤에 붙거나, 2. 그 숫자로부터 이어지는 숫자 2개가 더 있어야 함. 그리디네...
   </details>

#### Minimum Window Subsequence
* <a href="https://leetcode.com/problems/minimum-window-subsequence/" target="_blank">https://leetcode.com/problems/minimum-window-subsequence/</a>
* 몇시간 삽질해서 dp로 풀긴 함. dp 식이나 다시 세워보자
* 난 O(NM) dp로 풀었는데 더 효율적으로 푸는 dp가 있다네. 그럴 꺼 같긴 했는데...

#### Optimal Account Balancing
* <a href="https://leetcode.com/problems/optimal-account-balancing/" target="_blank">https://leetcode.com/problems/optimal-account-balancing/</a>
* 다시

#### Copy list with Random Pointer
* 다시 풀 필요는 없고, 생각정도는 해볼 만 함
* linked list를 deep copy할 시, random pointer도 갖고 있으면 이건 어떻게 deep copy에 반영하나?
* 일단 풀기는 python으로, `dic[node]=len(lis)` 를 통해 주소를 넣으면 index를 주는 dic만들어 풀음
* 이게 결국, 주소를 받았을 때 이 주소가 몇 번째 아이템인지 (내지는 deep copy된 배열의 corresponding item의 주소를) 받을 수 있어야 함.
* C++이면 어캐해야 하나. 지금 생각나는 건, 결국 포인터도 정수이므로 pair{pointer, index}를 만들고 정렬시킨 후 pointer를 받으면 binary search 로 찾으면 될듯.
* Damn! give this guy a Novel prize! https://raw.githubusercontent.com/hot13399/leetcode-graphic-answer/master/138.%20Copy%20List%20with%20Random%20Pointer.jpg
* 에전에 K사 면접문제. 끝을 모르는 링크드 리스트에서 뒤에서 K번째를 찾을 때 그 느낌하고 비슷한가 했는데 비슷하진 않네

#### Minimum Swaps To Make Sequences Increasing
- <a href="https://leetcode.com/problems/minimum-swaps-to-make-sequences-increasing/" target="_blank">https://leetcode.com/problems/minimum-swaps-to-make-sequences-increasing/</a>
- 미디엄이라 쉽게 보고 O(N^2) dp로 풀음
- O(N) 풀이가 존재하네....? 다시 풀어봅시다

#### Longest Increasing Path in a Matrix
- <a href="https://leetcode.com/problems/longest-increasing-path-in-a-matrix/" target="_blank">https://leetcode.com/problems/longest-increasing-path-in-a-matrix/</a>
- 하드인데 쉬웠음. 보드에서의 increasing path이므로, 왔던 곳으로 다시 못 감 - cache 이용가능 

#### Shortest Subarray with Sum at Least K
- <a href="https://leetcode.com/problems/shortest-subarray-with-sum-at-least-k/" target="_blank">https://leetcode.com/problems/shortest-subarray-with-sum-at-least-k/</a>
- 못풀고 답 봤다. 디큐문제는 항상 어렵네...다시 풀어보자
- 다시 풀었는데도 못풀었다. 디큐보다는 그리디네. 는 디큐 안쓰면 TLE나구요.

#### Minimum Area Rectangle
- <a href="https://leetcode.com/problems/minimum-area-rectangle/" target="_blank">Minimum Area Rectangle</a>
- 쉬운 문제고 어렵지 않게 풀긴 했는데, 검사조건을 명확하게 도출하지 못함. 다시 해보자. 다시 했음. 이전문제는 좀 naive하게 풀었던거 같음.


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


#### Search Autocomplete system (need review)
<a href="https://leetcode.com/problems/design-search-autocomplete-system/" target="_blank">https://leetcode.com/problems/design-search-autocomplete-system/</a>
- B형이랑 쪼까 비슷한듯
- 연관문제도 풀어볼까
- 제약조건이 좀 약하긴 함. 그래서 매 query마다 소팅을 하는데, 효율적으로 풀 수 없을까

#### Valid square
<a href="https://leetcode.com/problems/valid-square/" target="_blank">https://leetcode.com/problems/valid-square/</a>

4개의 점이 주어졌을 시, 정사각형인가?
* 첨에 회전을 생각안해서 함 틀림
* 좌표가 같은지아닌지로 하려다 계속 틀려서, 벡터 + 내적 (90도 판별)로 풀음.
* 말하면서 풀어야 하는데..넘모 귀찮은 것임

#### Path with Maximum Gold
<a href="https://leetcode.com/problems/valid-square/" target="_blank">https://leetcode.com/problems/valid-square/</a>


2차원 grid에서, 재방문이 불가 & 0을 방문하지 못할 시, 모을 수 있는 가장 많은 값은? (방문시 값 get)
* n, m이 해봐야 15, 논제로 아이템이 25개가 맥시멈 -> 완탐
* dp도 되지 않을까? 논제로 아이템 25개에 대한 상태공간 (25bit)만...안되겠네

#### Split Array Largest Sum
<a href="https://leetcode.com/problems/split-array-largest-sum/" target="_blank">https://leetcode.com/problems/split-array-largest-sum/</a>


* 배열을 m개의 non-empty subarray로 나눔.
* 각 subary의 합의 최대를 x라 하면, 최소의 x는?
* x를 픽스했을 시 각 trial을 만들기 쉽고, 범위가 정해져 있음 (0~원래 array의 합)
  * 이분탐색

#### https://leetcode.com/problems/shortest-way-to-form-string/ (review)
<a href="https://leetcode.com/problems/path-with-maximum-gold/" target="_blank">https://leetcode.com/problems/path-with-maximum-gold/</a>

1. 그리디함 증명
2. next table - 뒤부터 iter돌면서 만듬

#### Design Hit Counter
<a href="https://leetcode.com/problems/design-hit-counter/" target="_blank">https://leetcode.com/problems/design-hit-counter/</a>
increasing하게 들어오는 timestamp. 특정 시점의 300초전까지의 hit수를 구해야 함. 제약조건을 이용해 이진탐색으로 풀음

#### Minimum Knight Moves (복습요망)
<a href="https://leetcode.com/problems/minimum-knight-moves/" target="_blank">https://leetcode.com/problems/minimum-knight-moves/</a>

#### Time Based Key-Value Store (medium)
- <a href="https://leetcode.com/problems/time-based-key-value-store/" target="_blank">https://leetcode.com/problems/time-based-key-value-store/</a>
- 문제를 잘 읽읍시다..
- 그나저나, 새 item이 계속 추가되는 상태에서 정렬된 배열을 유지하는 건 계속 나오네. 이 문제의 경우는 increasing하는 순서로 주어져서 별 상관 없었지만. 문제를 잘 읽지 않은 덕분에 파이썬으로 어떻게 구현해야 하는지 계속 생각함.
  1. map (splay tree) - lower_bnd연산을 구현하면 쉬울듯.
  2. key가 정해져있고 좌표압축이 가능하며 범위가 작은 경우 - random access linked list로 짜면 될 듯. 근데 이거 만들어 본 적이 없어서..연습요망

#### Text justification
- <a href="https://leetcode.com/problems/text-justification/submissions/" target="_blank">https://leetcode.com/problems/text-justification/submissions/</a>, hard
- 큰 루프 두고, 예외케이스 3개 두고 풀음
  - 단어가 N개 (마지막에 whitespace 두지 않음)
  - 단어가 N개이나 마지막 (1번씩 띄고 left정렬)
  - 단어가 1개 (마지막 whitesapce 둠)
- 각 case에 규칙을 consistent하게 적용해야 하는데 이게 아직 잘 안되네. 이건 머리로 체크하는 수 밖에 없는 듯.
- round-robin

#### Minimum Domino Rotations For Equal Row
문제자체는 엄청 쉬웠다. 첫 submission은 맞았는데 실행시간이 바닥을 달림. 숫자가 consequtive하게 나와야 한다는 것 (강한 조건)을 이용해 필터링 함.

#### Guess the Word (hard)
- <a href="https://leetcode.com/problems/guess-the-word/" target="_blank">https://leetcode.com/problems/guess-the-word/</a>
- SWE B번예시같았다. 현재까지 던진 query와, 대상이 될 문자열들 candidate가 있다고 할 시, query와 최대한 겹치지 않는 걸 candidate에서 찾아서 query넣어봄 (최대한 많은 정보 획득).

### Amazon
* https://www.amazon.jobs/en/principles

### Interviews
* https://leetcode.com/discuss/interview-experience/479413/NDA-Google-Facebook-Amazon-or-L5-E5-L5-or-London-or-Dec-2019-Offer
  * Here typical advices would apply: think outloud, do not give anything for granted and ask lots of clarifying questions, state from the very beginning what kind of complexity (both time and space) and check with the interviewer if that complexity is ok or you should aim for something better.
  * System Design: I found this one to be the most complex for two main reasons: I did not have a lot of experience on scaled distributed systems, you do not really know how to prepare on this one (whereas you can prepare well for the coding one). This was the one where I performed the worst both at Google and Facebook, and Facebook asked me to repeat this interview a second time (just the System Design one, not the whole thing). The main takeaway here is: start with a very generic design, and then deep dive and be (very) concrete on 1-2 aspects. If the aspect is the Database, say which technology, which schema, how many replicas, and so on. If you deep dive on one server, say how many servers you need, say what kind of requests/responses, say what happens if one server goes down while serving a request, and so on.
  * Behavioral: Do not underestimate this one, as for example Google introduced it recently since they understood the importance of such interview. Prepare some answers to questions like Tell me one time where you disagree with your colleagues or Tell me one time that you went outside your normal boundaries to complete some tasks. My suggestion here is be real, try to come up with real scenarios from your experience, which may very well be stuff from university. Do not try to fool the interviewer with cool answers, these guys have been doing interviews for many years and they most likely know how to spot a fake answer. Amazon requires a special preparation, as you need to go through all their principles and associate 1 or 2 stories to each of the principle.
  * For system design questions I prepared by purchasing the course grokking the system design interview, reading high scalability blog and watch lots of videos on Youtube. Do as many mock interviews as possible, even alone and even if it seems stupid at the beginning.
### reference problems

#### LRU Cache

linked list + hash = O(1) LRU Cache!

#### 2-sum problems
1. 2-sum - lr (O(N))
2. 3-sum - 2sum * N
3. 4-sum - 3sum * N

### Minimum Window Substring
<a href="https://leetcode.com/problems/minimum-window-substring/" target="_blank">https://leetcode.com/problems/minimum-window-substring/</a>

* 긴 string s에서 짧은 string t의 permutation을 포함하는 substing의 최소길이를 찾아야 함
* Permutation을 포함만 하면 되므로, count가 적었다가 같아지는 순간이 중요
* 윈도우 (2 indices - st, ed)로 체크함.   
    1. ed : 고정된 st에서, permutation을 포함하는 최소 끝점을 찾음
    2. st : 해당 ed에서, permutation을 포함할 때 까지 줄여감
* 왠일로 하드를 수월하게 풀었네...?

#### Merge Intervals

<a href="https://leetcode.com/problems/merge-intervals/" target="_blank">https://leetcode.com/problems/merge-intervals/</a>

1. 인터벌 (a, b)들을 오름차순으로 정렬
2. valid non-intersecting interval 집합을 유지한다고 할 시, 현재 고려중인 interval은 
    1. valid 집합의 마지막 interval보다 a값은 크다
    2. 따라서, valid 집합의 마지막 interval과 머지되지 않을 시, 나머지들과 머지될 일은 없음.



#### Best time to buy and sell stock
<a href="https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-cooldown/submissions/" target="_blank">https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-cooldown/</a>

1. DP
\\[\text\{maxx\}[i] = \max(\text\{maxx\}[i], \text\{maxx\}[i-1], ary[i] - ary[j] + \text\{maxx\}[j-2]),\\ j=1,...,i-1\\]
when j<2, maxx[j-2] = 0 (there is no profit we can obtain in day=i=0, 1)
2. __Notice__ that, the term \\(- ary[j] + \text\{maxx\}[j-2])\\) is calculated over and over

#### Next permutation

<a href="https://leetcode.com/problems/next-permutation/" target="_blank">https://leetcode.com/problems/next-permutation/</a>

Permutation의 다음번째는 무엇인가? (lexicographical order)

1. Permutation이므로 swap
2. lexi-order이므로, 자릿수가 작은 숫자를
	1. 자기보다 자릿수가 더 낮으면서
	2. 값은 더 큰 숫자
	3. 중 최소의 숫자와 바꿔야 함.
	
	이렇게 i번째 숫자를 j(<i) 번째 숫자와 바꾸었으면, i-1번째부터는 작은 순으로 정렬해주어야 함. 그래야 바로 다음번이 되니까.
3. 위에 해당하는 경우가 없을 시, 모든 숫자는 자기보다 자릿수가 낮은 숫자보다 큼. (ex - 4321) 문제에서 이러면 낮은순정렬하랬으므로 1d transpose해줌



#### Finding cycle in linked list
<a href="https://leetcode.com/problems/linked-list-cycle-ii/" target="_blank">https://leetcode.com/problems/linked-list-cycle-ii/</a>

1. travel with `slow` (goes 1 pointer in a time) and `fast` (goes 2 point in a time)
2. Let
* \\(L\_1\\): distance between the starting point and cycle entrance
* \\(L\_2\\): distance between the cycle entrance and meeting point
* \\(C\\): cycle length
* \\(n\\): number of times `fast` ran through circle until it meets with `slow`
그러면,
1. \\(2(L\_1+L\_2)=L\_1+L\_2+nC\\)
2. \\(n=1\\): 어차피 `fast`와 `slow`는 1번에 1칸씩밖에 차이가 안나기때문에, `fast`는 1번의 순회만으로 `slow`와 만남.

그러므로, \\(L\_1+L\_2=C \quad\rightarrow\quad L\_1=C-L\_2\\). 현재 slow위치에서 계속 앞으로 나가고, starting point에서 앞으로 나가면 만나는곳이 cycle entry가 됨.


#### Task Scheduler
<a href="https://leetcode.com/problems/task-scheduler/" target="_blank">https://leetcode.com/problems/task-scheduler/</a>

1. task 갯수가 n+1번째보다 많을 시, 억지로 n+1에 끼워넣기보단 n+1보다 더 벌리는 것이 좋음. 그림을 그러보면 알기 쉬운데, 전자는 net loss가 발생하기 때문
2. 위와 같이 하고, 중복 고려해서 마지막 끝나는 시간을 찾으면 됨


### Need review

#### Find All Numbers Disappeared in an Array
https://leetcode.com/problems/find-all-numbers-disappeared-in-an-array/

Cycle 찾기 문제. 이게 이지라고?

#### search a 2d matrix

<a href="https://leetcode.com/problems/search-a-2d-matrix-ii" target="_blank">https://leetcode.com/problems/search-a-2d-matrix-ii</a>


\\(m\times n\\) 행렬이, 행 / 열 별로 독립적으로 정렬되어 있을 시,

1. 난 그냥 m*logn으로 풀음
2. 행렬은 각 element 별로 4개로 쪼갤 수 있다. 왼위가 자기보다 무조건 작은 곳, 오른아래가 무조건 자기보다 큰 곳.  
   왼쪽 위부터 시작하지 말고, 오른쪽 위부터 시작해서
   1. ary[i][j] < target: 더 큰 수 를 찾아야 하므로, 오른 아래는 무조건 없다. 왼쪽으로 빠꾸. 위는 예전에 갔으므로 갈 필요가 없음.
   2. ary[i][j] > target: 더 작은 수를 찾아야 하므로, 왼위는 무조건 없다. 아래로 ㄱ. 오른쪽은 오른쪽부터 시작했으므로 갈 필요가 없음.  
   의 방식으로 \\(\mathop\{O\}(m+n\\) 탐색 가능.

이런 문제를 바로바로 풀어야 할 텐데...


#### Generate Parentheses

<a href="https://leetcode.com/problems/generate-parentheses/" target="_blank">https://leetcode.com/problems/generate-parentheses/</a>

n개의 parentheses로 가능한 모든 조합을 만드는 문제

1. 재귀 - dp로 풀음
2. backtracking - 새로운 parentheses는 항상 오른쪽에 붙인다고 하면 backtracking 가능  
3. 어떻게 붙여도 숫자만 맞고, 오른쪽에 붙이므로 )를 먼저 다 쓰는 일 없이 r > l일때만 )를 써주면 valid함.

dfs나 bfs로 상태공간 탐색가능

```python
class Solution:
    
    def solve(self, l, r):
        if l == 0 and r == 0:
            return [""]
        ret = []
        
        if l != 0:
            ret += ["(" + item for item in self.solve(l-1, r)]
        if r != 0 and r > l:
            ret += [")" + item for item in self.solve(l, r-1)]
        if l == 0 and r != 0:
            return [")"*r]
        
        return ret
    
    def generateParenthesis(self, n: int) -> List[str]:
        return self.solve(n, n)
```


#### Longest Valid Parenthesis
<a href="https://leetcode.com/problems/longest-valid-parentheses/submissions/" target="_blank">https://leetcode.com/problems/longest-valid-parentheses/submissions/</a>

핵심: `이전` 레벨의 시작으로 거리를 구하는 것. cur에 저장

cur = -1

1. (를 만났을 시
    1. `이전` 레벨의 시작(cur)을 스택에 저장
    2. 현재 레벨의 시작을 cur에 세팅
2. )를 만났을 시
    1. 이전에 쌓은 (가 없는 경우 - cur을 현재로 갱신해줌
    2. 있는 경우 - 이전 레벨의 시작 (st.top())과 현재의 거리를 답에 반영 후, pop. 

이렇게 하는 이유는, ()()나 (()()) 같은 경우를 해결하기 위해서.

```python
def longestValidParentheses(self, s: str) -> int:
    st = []
    
    lvlStart = -1
    ans = 0
    for i, ch in enumerate(s):
        if ch == '(':
            st.append(lvlStart)
            lvlStart = i
        else:
            if len(st) == 0:
                lvlStart = i
            else:
                lvlStart = st.pop()
                ans = max(ans, i - lvlStart)
        
    return ans
```



#### N-Queens
<a href="https://leetcode.com/problems/n-queens/" target="_blank">https://leetcode.com/problems/n-queens/</a>

1. Naive - on the board
2. 보드보다 상태공간을 더 잘 표현할 수 있음
    1. queen의 위치는, 1-d array의 위치가 row, 값이 column
    2. position의 조건이, rowInd+colInd와 rowInd-colInd 가 같으면 같은 대각에 있는 것이므로, 위의 두 값을 queen의 위치와 같이 저장. 같은 row/col체크는 하지 않을 것 (위에서 이미 결정하고 오므로)
    3. naive board solution은 정말 보드를 다 찾아보지만 이 solution은 row별로 어디에 놓을지만 결정해도 되므로 시간절약도 많이 될듯

	

#### Container With Most Water

<a href="https://leetcode.com/problems/container-with-most-water/" target="_blank">https://leetcode.com/problems/container-with-most-water/</a>

기본시도: 정렬가능시 정렬 (이문제 아님), 왼 안되면 왼+오, ...

스택으로 푸는 그 문제인 줄 알았다 ㅡㅡ 낙시쩔음

```python
class Solution:
    def maxArea(self, height: 'List[int]') -> 'int':
        fr, to = 0, len(height)-1
        ans = 0
        while(fr < to):
            ans = max(ans, min(height[fr], height[to]) * (to - fr))
            if height[fr] < height[to]:
                fr = fr + 1
            else:
                to = to - 1
        return ans
                         
                
```

#### Smallest Range
<a href="https://leetcode.com/problems/smallest-range-ii/" target="_blank">https://leetcode.com/problems/smallest-range-ii/</a>

1. 처음엔 [2][10000]의 동적계획법인가 했었다. 
	1. 부분문제 구조가 없어 보이고
	2. 상태공간 구성이 말도 안되서 포기
2. min-max 로 풀 수 있는 그리디인가 싶어 계속 해맴
3. 핵심은 결국, 리스트 정렬시 [K를 더하는 쪽, K를 빼는 쪽] 으로 나뉜다는 것.  
그렇다면 리스트를 임의로 나눴을 시 유의미한 숫자는 4개,
	1. K를 더하는 쪽의 첫번째 + K
	2. K를 더하는 쪽의 마지막 + K
	1. K를 빼는 쪽의 첫번째 - K
	2. K를 빼는 쪽의 마지막 - K
	
	4개만 검사하면 됨.
	

```python
class Solution:
    
    def smallestRangeII(self, A: 'List[int]', K: 'int') -> 'int':
        
        A.sort()
        maxx, minn = A[-1] - K, A[0] - K
        ans = maxx - minn
        for i in range(len(A)-1):
            ary = [A[-1] - K, A[0] + K, A[i] + K, A[i+1] - K]
            ans = min(ans, max(ary) - min(ary))
        
        return ans
```


### Reviewed

#### Coin change

<a href="https://leetcode.com/problems/coin-change/" target="_blank">https://leetcode.com/problems/coin-change/</a>

문제자체는 별거 없는, 동전교환 dp인데..
```python
dp[val] = min([dp[val - c]+1 if val - c >= 0 else float("inf") for c in coins])
```
으로 푸는게 2차원 배열에 동전갯수번만큼 min 을 해주는 것보다 2배는 빨랐다. ㄷㄷ해.  
결론:
1. 다수의 min/max보다는 List comprehension을 쓰자!
2. `float("inf")`

#### Subarray Sum Equals K
https://leetcode.com/problems/subarray-sum-equals-k/

부분합문제인데 N^2로 풀면 TLE남.  
힌트는 값의 범위가 좁다는거였음. dic에 지금까지 나온 값들 저장해놓고 체크하면 됨.  
`collections.counter`를 쓰면 더 빨라지는듯?


#### Find All Numbers Disappeared in an Array
https://leetcode.com/problems/find-all-numbers-disappeared-in-an-array/

리스트 값이 리스트 내부와 range가 같고, 리스트를 체크해야 할 시 리스트 값이 -를 해두면 좋은듯


#### Min stack
<a href="https://leetcode.com/problems/min-stack/" target="_blank">https://leetcode.com/problems/min-stack/</a>

stack의 최소값 - pair를 저장하면 됨. 큐와는 달리 top 밑에 있는 애들이 안빠지므로..


#### Rotate image

<a href="https://leetcode.com/problems/rotate-image/submissions/" target="_blank">https://leetcode.com/problems/rotate-image/submissions/</a>

행렬 90도 rotation

1. transpose + column exchange
2. 4개의 점끼리만 바꾸기. Row 2개로 swap하려고 해서 잘 안풀려서 1번으로 풀음


#### Regular expression
 
```python
class Solution:
    
    def cache_memoization(func):
        __cache = {}
        def wrapper(*args):
            if args in __cache:
                return __cache[args]
            else:
                result = func(*args)
                __cache.update({args:result})
                return result
        return wrapper
    
    @cache_memoization
    def isMatch(self, s: 'str', p: 'str') -> 'bool':
        if not p:
            return not s
        
        if len(p) >= 2 and p[1] == '*':
            if len(s) > 0:
                if p[0] == '.' or p[0] == s[0]:
                    return self.isMatch(s[1:], p) or self.isMatch(s[1:], p[2:]) or self.isMatch(s, p[2:])
            return self.isMatch(s, p[2:])
        
        
        if len(s) > 0 and len(p) > 0 and (s[0] == p[0] or p[0] == '.'):
            return self.isMatch(s[1:], p[1:])
        
        return False
        
```

* 클래스 내부에서 멤버함수 호출: 멤버변수와 같이 self.붙여줘야
* 메모이제이션 쩌네. 2차원 dp로 풀라다 실패. 생각해보니 이렇게 재귀함수 짜고 2차원 dp했어도 걍 풀었을듯. 재귀 먼저 짜자