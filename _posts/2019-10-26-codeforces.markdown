---
layout: post
title:  "Codeforces reviews"
date:   2020-02-13 09:00:05 +0800
categories: problem_solving
use_math: true
tags: problem_solving need_review multiset
---

천천히 합시다

### EDU 86
1. C  
   (1, maxx-1)까지 특정 0/1 패턴이 나타나는데, (l, r)구간에서의 합은?  
   4개의 포인트를 고려해야 해서 썡으로 풀면 어렵다. 
   ```c++
   ll left_to = l / (maxx);
   ll right_to = r / (maxx);
   ```
   로 해 놓고,  
   1. left_to == right_to 이면, 둘이 같은 (1, maxx-1) 구간에 들어 간 거니까 그 안에서 계산
   2. !=이면, 왼쪽/오른쪽 따로 (1, maxx-1)구간을 계산하고, `(right_to - left_to - 1)` 번 만큼 (1, 1-maxx)구간이 반복되는 것임
2. D  
   [1, K] 구간에 아이템이 있나 없나 빨리 봐야 했음. map과 lower_bound를 써서 품.   
   `lower_bound(key)`: inclusive. key에 대해 lower_bound인 아이템을 반환하는 게 아니고, key본인이 lower_bound가 될 수 있는 아이템을 반환하는 것 (본인 포함, 오른쪽)  
   `upper_bound(key)`: not inclusive (본인 미포함 왼쪽)  
   오른쪽 왼쪽 계속 햇갈린다. 
3. E   
   <details>
   <summary>다시풀기</summary> 
    inclusion-exclusion / 2배 하기. 이걸 대회시간내에 어케 풀지. 풀면 바로 퍼플 갈텐데...
   </details>

### 619 Div2
<a href="https://codeforces.com/contest/1301" targeg="_blank">https://codeforces.com/contest/1301</a>

1. C - Ayoub's function  
   1. 전체 - 0만 있는 경우로 1이 들어간 경우를 계산함
   2. 1이 1개만 있을 시, 가운데에 집어넣는게 가장 좋고
   3. 1이 N개일시, N+1개의 빈칸의 길이를 가장 크게 하는것이 좋다. 전체가 N+1개로 안나뉘면, 앞 remnant개는 +1개로 해줌 - `분배문제`
2. D - Time to run
   1. 오일러 패스 - 답이 항상 존재
   2. 예외케이스때매 3번쯤 틀린듯. 0이 될때를 고려하지 않고 등...
   3. 어케 혼자 풀긴 풀었는데  ㅜㅜ 그래도 D까지 풀리는 거 보니 아직 완전히 죽진 않은듯
   4. 오일러 패스 프린팅 알고리즘 알아보자. 좀 일반적으로 풀어야지..


### 599 Div2
1. B - Character swap  
   예전이면 못풀었을 것 같은데..어케 나름 일찍 풀긴 풀었네
2. C - Tile Painting  
   1. 패턴을 발견해내는 것이 느렸다. transitive 1to1이 생긴다는 걸 이렇게 늦게 보다니..이건 그냥 훈련이 더 필요한 듯
   2. 나머지는 long long인데 함수 리턴값만 int로 하는 사람이 있다?
3. <a href="https://codeforces.com/contest/1243/problem/D" target="_blank">D - 0-1 MST</a>  
   첨엔 진짜 MST로 푸는건가 했음. 이런 패턴의 문제가 좀 나올 것 같은데, 기억해두어도 좋을 듯.
   <details>
   <summary>editorial</summary>0끼리는 뭉쳐도 손해가 없으므로 결국 서로 0인 엣지로 갈 수 있는 노드끼리 뭉쳐야 하고, 해당 blob개수 - 1이 답임. union-find로 노드 하나에 대해, 모든 블롭을 대상으로 포문을 돔. 현 노드에서 해당 블롭에 연결된 엣지 개수를 구할 수 있으므로 (u-v에서 find(v)), 그 갯수가 blob노드갯수랑 일치하면 해당 블롭과는 disjoint 한 것. 아니면 0인 엣지가 하나라도 있으니 그런것끼리 merge해주면 됨.  
   </details>


### 598 Div3
1. <a href="https://codeforces.com/contest/1256/problem/C" target="_blank">C, Platforms Jumping</a>
   첨에 dp를 생각함. 상태공간을 ary[1000][1000]에 우겨넣으려고 고생했다. 그리디한면이 있어서 될꺼같긴했는데 잘 되지 않았음. 판을 "전부 다 써야" 한다는 제한조건이 꽤나 까다로웠다.
   <details>
   <summary>editorial</summary>결국 greedy하게 풀 수 있음. 일단 판을 다 오른쪽에 몰아넣고, d만큼 쩜프 시 착지하는 곳이 물이면 판을 1개씩 끌어옴. 이 때 판을 가장 놓을 수 있는 오른쪽으로 놓음. 놓지 못할 염려는 없고, 왼쪽으로 놔봤자 이득이 없기 때문.
   </details>
2. E - 와 이걸 못풀었다고....? 담부터 술1잔이라도 먹으면 코포 ㄴㄴ
3. F - Equalize Two strings

### 592 Div2
1. <a href="https://codeforces.com/contest/1244/problem/C" target="_blank">C. The football season</a>  
   난 이분탐색으로 도전했다. 안되는 이유는, 각 상태간의 상하관계를 확실히 정의할 수 없어서였음. convex한 문제도 아니었고...
   <details>
   <summary>editorial</summary>d, w 범위가 작음. 이긴 횟수가 d를 넘어가면, 결국 d보다 낮은 케이스로 동일 점수로 매핑할 수 있어서, d안에서만 이긴 횟수를 따져보면 됨. 증명 다시 해보자. 
   </details>
   확장 유클리드 호제법 문제였슴. 
   1. Integer programming서, \\(ax + by = c\\)인 경우에서 당연히 \\(gcd(a, b)\\)는 c를 나눌 수 있음.
   2. 일단 \\(c=gcd(a, b)\\)인 경우에 (아니라면, 원래 c / gcd(a, b)를 곱해주면 되겠지 뭐)
   3. \\(a=bq+r\\) 이라고 하면 (포인트!), \\[(bq+r)x + by = gcd(a, b)\\] \\[(b(qx + y)+rx = gcd(a,b) = gcd(b, r)\\]이 되고, b는 유클리드gcd처럼 언젠가 0이 됨.

### Edu 74
1. C. Standrad Free2play
   - 경우를 잘 따지고 코딩해서 맞음
2. <a href="https://codeforces.com/contest/1238/problem/D" target="_blank">D. AB-string</a>
   <details>
   <summary>editorial</summary>반대의 경우를 세면 쉽다. 다시 풀어볼 것
   </details>

### 596 Div2
와씨...망
1. TV subscriptions  
   ㅡㅡ...입력이 \\(2\times 10e5\\)였는데 2를 빼먹었다. 근데 왜 TLE가 나는거지? runtime err가 나 줬으면 좋았게쓴ㄴ데..  
   번외로 단번에 잘 못풀었다. 특정 구간에 나타나는 distinct한 숫자 갯수를 세어야 했고, incremental하게 구간 범위는 증가함. 그냥 count배열에 세 주면서, 0이 되면 빼고 0에서 숫자가 증가하면 ++해주면 됐는데 map도 쓰고 난리났었음 
2. p-binary  
   1. binary representation - "최소한으로 해당 숫자를 2의 power들의 합으로 나타낼 수 있음"
   2. 예를들어 N이 bin rep으로 나타냈을 시 101이라면 (1이 2개), 3번째 1을 2개로 쪼개서 1을 3개로 (2번째에 중복2개) 해서 2의 power들의 합으로 나타낼 수 있음. 문제조건과 완전 동일.
   3. 예외처리때매 systest에서 망함. N이 너무 클 시 && N이 너무 작을시 (예를 들면, 8을 2의 power들의 합으로 나타내려면, 2^i꼴이 최소 8개는 있어야함) 체크만 해 줬어도 맞았을 듯

당분간은 2, 3번만 풀까...

### 595 Div3
1. <a href="https://codeforces.com/contest/1249/problem/C2" target="blank">Good Numbers (hard version)</a>   
N보다 크면서, 중복 없는 3의 배수들을 더한 것 중 가장 작은 숫자 찾기. `3의 배수들을 더한다`는 거에서 3진수를 떠올렸어야 했음. 3진수로 표현 후 3진수법에서 2가 없이 (=중복 없이) 현 숫자보다 크면서 가장 작은 수를 찾으면 됨.
1. <a href="https://codeforces.com/contest/1249/problem/D2" target="blank">Too Many Segments (hard version)</a>   
PQ로 easy는 풀었는데, PQ서 가장 큰 객체와 가장 작은 객체를 빼내야 해서 막힘.  
`multiset`으로 풀었어도 되고...set도 index붙이면 unique해서 됐을듯. 담부턴 multiset 쓰자  
```c++
while (pq.size() && pq.begin()->first < p)pq.erase(pq.begin());
while (pq.size() > K) {
   auto it = prev(pq.end());
   pq.erase(it);
}
```
<details>
<summary>에디토리얼</summary> 작은 객체를 뺴야 하는 이유: 현재 포인트에서 세그먼트 몇 개가 있는지 알기 위해.  <br/> 큰 객체를 뺴야 하는 이유: 그리디하게 풀기 위해 (최소의 객체 제외). 답 보니 첫번째껄 구간 counting (line[seg[0]]++, line[seg[1]]--, 각 포인트 (0~2만)에서 line[pnt] 더해주기)으로 대체했네. 
</details>


마찬가지로 시간이 모자랐음. C, D hard는 못풀었다고 치고, E를 갔으면 바로 풀었을텐데...ㅡㅡ  
F는 안봄. 141명이 풀었네. 직장인 주제에 사치인듯

### 593 Div2
1. <a href="https://codeforces.com/contest/1236/problem/B" target="blank">Alice an the List of Presents</a>    
\\(N\\)개의 아이템을 \\(M\\)개의 bin에, 각 bin별로
   1. bin 내의 중복은 불가능
   2. bin끼리의 중복은 가능
   3. 한번도 안쓰이는 아이템이 없게
   
   집어넣을 시 경우의 수.  
   
   <details>
   <summary>editorial</summary>bin을 기준으로 경우의 수를 세려고 해서 못풀었다. 각 아이템 별로 생각하면, \\(2^m-1\\)의 경우의 수가 있음. (1은 모든 bin에 들어가지 않는 경우).
   </details>
2. <a href="https://codeforces.com/contest/1236/problem/D" target="blank">Alice and the Doll</a>  
   N이 너무 커서 완탐은 불가능한 보드판. 소용돌이 모양으로 움직이다 장애물이 나오면 꺾으면 됨 (1번 꺾는것만 허용).  
   장애물 갯수가 작아 장애물 기준으로 완탐하려다가 실패
   <details>
   <summary>editorial</summary>소용돌이 모양 - (xmin, xmax), (ymin, ymax)의 범위를 점점 줄여가면 됨. 각 row/col 별로 col/row좌표를 정렬 후 저장했다 이분탐색으로 장애물 부딪쳤는지를 판별. k개의 장애물이 있을 시, N * M - K 번 가야 하고, 각 jump의 길이도 계산할 수 있음.
   </details>
3. <a href="https://codeforces.com/contest/1236/problem/E" target="blank">Alice and the Doll</a>   
   거꾸로+dp. 의존관계 찾기가 좀 빡셌음. 혼자 생각해서 2시간은 걸린듯. 관계를 어떻게 계산해야 하는지는 몰랐지만.
   <details>
   <summary>editorial</summary>의존관계 순서를 역순으로 계산해야 함. 각 guess가 주는 영향은 양쪽 1칸밖에 없는데, "앞(미래)에서 밀린 만큼" 영향을 받기 때문
   </details>

시간이 엄청 부족하네. 각 안보이면 ㅌㅌ를 빨리 해야할듯. 2번은 풀 만도 했는데..