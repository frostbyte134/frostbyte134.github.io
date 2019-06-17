---
layout: post
title:  "BOJ 11577: Condition of the deep sleep"
date:   2019-06-17 10:45:05 +0800
categories: problem_solving
use_math: true
tags: problem_solving array_marking reference_problem
problem: 11577
---

<a target="_blank" href="https://www.acmicpc.net/problem/{{page.problem}}">https://www.acmicpc.net/problem/{{page.problem}}</a><br/>

1. 우선, 왼쪽부터 0을 만들어가야 함. 1이 나오는 경우, 왼쪽의 0은 냅두고 오른쪽으로 negation 해야 함
2. 그럼, negation을 빨리 하는 방법이 필요한데, N^2의 simulation은 안됨. 생각해보니 코테 나오기 좋은 문제 아닌가? \\(N^2\rightarrow N\\)이니까..
3. 우선 K=3인 경우를 예로 들면  

```cpp

int N, K;
int ary[100012];

int neg(int& i){
	if (i == 0)return 1;
	else return 0;
}

int main(){
	scanf("%d %d ", &N, &K);
	int cnt = 0, num;
	for (int i = 1; i <= N; i++){
		scanf("%d ", &num);
		ary[i] += ary[i - 1];
		if (num ^ (ary[i] % 2) && (i + K <= N + 1)){
			ary[i]++;
			ary[i + K]--;
			cnt++;
		}
		if (num ^ (ary[i] % 2)){
			cout << "Insomnia" << endl;
			return 0;
		}
	}
	cout << cnt << endl;
	return 0;
}
```  

<img src="{{site.url}}/images/ps/cond_deep_sleep.png">  
* ary[i]는  base라고 생각하면 됨. 0부터 시작
* num=1이 들어왔을 시, 둘이 다르므로 negation을 할 것임
* 윗 그림처럼 ary[i+K]에는 base 값이 줄어들도록 세팅해 놓음
* 이러면 다음번에 1이 들어오면, base%2 == 1이므로 negation을 안함 (이미 negation을 했으므로, 들어온 1은 0이 되었기 때문)
* 개인적으로는 array marking이라는 이름으로 부르는데, 남들은 뭐라고 하는지 모르겠음
* 저 ary[i]를 다루는 것 비슷한 문제를 몇 번 풀어봤는데..기억이 잘 안나네
* 큐를 써도 된다는데, ary[i]를 다루는 법 없이 풀 수 있나? K의 시작과 끝이 어디인지 잘 모를텐데
