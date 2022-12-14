---
layout: post
title:  "PS codebase"
date:   2020-07-24 09:00:05 +0800
categories: problem_solving
use_math: true
tags: problem_solving need_review coding
---

### CPP

### Python
- sort `d = sorted(a, key = lambda x : x[1])`
- deque `pop, popleft, append, appendleft, rotate`


### KMP
```cpp
for (int i = 1, j = 0; i < N; i++) {
    while (j > 0 && P[i] != P[j])j = fail[j - 1];
    if(P[i] == P[j])fail[i] = ++j;
}
int ans = 0;
for (int i = 0, j = 0; i < K; i++) {
    while (j > 0 && W[i] != P[j])j = fail[j - 1];
    if (W[i] == P[j]) {
        j++;
        if (j == N ) {
            j = fail[j-1];
            ans++;
        }
    }
}
```

- `fail[i]` : i번째 index까지 substr에서, 접미사=접두사 인 길이
- "길이" 이므로, `j = fail[j-1]` 로 설정 시, fail[j-1]=2 (길이가 2)였다면 3번째 다음 문자열과 현재 i를 비교하게 됨 

### bipartite matching
```cpp
bool vis[max_row];
int colMatched[max_col]; //matched row number of column

bool dfs(int cur_row) {
	if (vis[cur_row]) return false;
	vis[cur_row] = true;
	for (const auto& nxt_col : adjRow[nd]) {
		if (colMatched[nxt_col] == -1 || dfs(colMatched[nxt_col])) {
			colMatched[nxt_col] = cur_row;
			return true;
		}
	}
	return false;
}

....


int ans = 0;
memset(colMatched, -1, sizeof(colMatched));
for (int i = 0; i < N; i++) {
    memset(vis, 0, sizeof(vis));
    if (dfs(i))ans++;
}


```

### hasing (pseudo-random)
```cpp

const int KEY = 769, MOD = 100003, INF = 1e+9;
int ary[MOD];

void insert(int key) {
	int tk = key;
	while (ary[tk] != INF)tk = (tk + KEY) % MOD;
	ary[tk] = key;
}

bool find(int key) {
	int tk = key;
	while (ary[tk] != key && ary[tk] != INF)tk = (tk + KEY) % MOD;
	return ary[tk] == key;
}

int s2k(char str[]) {
	int ret = 0;
	for (int i = 0; i < strlen(str); i++) {
		ret = (ret * 29) % MOD;
		ret = (ret + str[i] - 'A') % MOD;
	}
	return ret;
}
```
* 라빈카프는 알아서 잘 짜시길.

### Map (splay tree)
* 실수가 잦구나...!

```cpp
template <class K, class V>
struct _map{

    struct _node{
        _node *l = 0, *r = 0, *p = 0;
        K key;
        V val;
    };

    _node* root = 0;

    void rotate(_node *nd){
        if(nd == root)return;
        _node *p = nd->p, *b;
        if(p->l == nd){
            b = p->l = nd->r; //여기서 함 실수함
            nd->r = p;
        }else if(p->r == nd){
            b = p->r = nd->l;
            nd->l = p;
        }
        if(b)b->p = p;
        nd->p = p->p;
        p->p = nd;

        if(nd->p){
            if(nd->p->l == p)nd->p->l = nd;
            else if(nd->p->r == p)nd->p->r = nd;
        }else root = nd;
    }

    void splay(_node *nd){
        if(!nd)return;
        while(nd->p){
            _node *p = nd->p, *g = nd->p->p;
            if(g){
                if((g->l == p && p->l == nd) || g->r == p && p->r == nd)rotate(p);
                else rotate(nd);

            }
            rotate(nd);
        }
        root = nd;
    }

    void insert(K _key, V _val){
        if(!root){ //이거 빼먹은 적 있음
            root = new _node;
            root->key = _key;
            root->val = _val;
            root->p = root->l = root->r = 0;
            return;
        }
        _node *nd = root, **targ;
        while(nd){
            if(_key < nd->key){
                if(!nd->l){
                    targ = &(nd->l);
                    break;
                }
                nd = nd->l;
            }else if(_key > nd->key){
                if(!nd->r){
                    targ = &(nd->r);
                    break;
                }
                nd = nd->r;
            }else{
                nd->val = _val;
                return;
            }
        }
        _node *tmp = new _node;
        tmp->key = _key;
        tmp->val = _val;
        *targ = tmp;
        tmp->p = nd;
        tmp->l = tmp->r = 0;
        splay(tmp);
    }

    bool find(K key){
        _node* nd = root;
        while(nd){
            if(nd->key == key){ //방향 함 실수함
                splay(nd);
                return true;
            }
            else if(key < nd->key){
                if(!nd->l){
                    splay(nd);
                    return false;
                }
                nd = nd->l;
            }else{
                if(!nd->r){
                    splay(nd);
                    return false;
                }
                nd = nd->r;
            }

        }
        return false;
    }

    void erase(K key){
        if(!find(key))return;
        _node* nd = root;
        if(nd->l){
            if(nd->r){
                root = nd->l;
                root->p = 0;
                _node* findr = root;
                while(findr->r)findr = findr->r;
                findr->r = nd->r;
                nd->r->p = findr;
            }else{
                root = nd->l;
                root->p = 0;
            }
        }else if(nd->r){
            root = nd->r;
            root->p = 0;
        }else root = 0; //이 조건 까먹은 적 많음
        delete nd;
    }

    void clear(){
        while(root){
            erase(root->key);
        }
    }

    ~_map(){
        clear();
    }


    V& operator[](K _key){
        if (!find(_key)){
			insert(_key, V(0));
        }
        return root->val; //splay tree 이므로..
    }
};
```

### Vector
벡터는 항상 push_back / pop_back만 사용하기. 안그러고 멋대로 조작하기 시작하면 머리아퍼진다
```c++
template<class V>
struct _vector{
    V* ary;
    int m_size, m_cap;
    _vector(int _cap = 2){
        m_cap = _cap;
        m_size = 0;
        ary = new V[m_cap];
    }

    void push_back(const V& val){
        if(m_size == m_cap){
            m_cap *= 2;
            V* tmp = new V[m_cap];
            for(int i = 0; i<m_size; i++)tmp[i] = ary[i];
            delete[] ary;
            ary = tmp;
        }
        ary[m_size++]=val;
    }

    V back(){
        return ary[m_size-1];
    }

    void pop_back(){
        if(m_size)m_size--;
    }

    int size(){
        return m_size;
    }

    void clear(){
        if(m_size)delete[] ary;
        m_size = 0;
        m_cap = 5;
        ary = new V[m_cap];
    }

    ~_vector(){
        delete[] ary;
    }

    V& operator[](int ind){
        return ary[ind];
    }
};
```

### Random Access Linked list (or similar sort)
from <a href="https://blog.naver.com/PostView.nhn?blogId=jinwooo_hong&logNo=221325054415&redirect=Dlog&widgetTypeCall=true&directAccess=false" target="_blank">link</a>

```c++
#include <iostream>
using namespace std;

int arr_idx = 0;

struct node {
    int v;
    node * prev;
}a[100000];

node * myalloc(void)
{
    return &a[arr_idx++];
}

void main(void)
{
    node * pList = NULL;		// 싱글링크드 리스트 선언 (싱글리스트의 시작)
    node * p;
    arr_idx = 0;

    p = myalloc();				// 첫번째 노드 추가
    p->v = 1;
    p->prev = pList;
    pList = p;

    p = myalloc();				// 두번째 노드 추가
    p->v = 2;
    p->prev = pList;
    pList = p;

    for (node * pp = pList; pp != NULL; pp = pp->prev)
    {
        cout << pp->v << " " ;
    }
    cout << endl;
    return;
}
```

### LCA - Binary Lifting
* 구간트리와 비슷한 원리 (또는 뭐, 이진법...)
* 공통부모가 같지 않으면 lift up!
* 2^level을 까먹지 말자.
* \\(\text\{dp[nd][lvl] \}\\) : 노드 nd의 \\(2^\text\{lvl\}\\) 번째 조상. 이 값은 노드 nd의 \\(2^\text\{lvl-1\}\\)번째 조상이 있다는 가정하에, 그 조상의 \\(2^\text\{lvl-1\}\\)번째 조상으로 업데이트 할 수 있음

```cpp
for (int lvl = 1; lvl < 20; lvl++) {
    for (int n = 1; n <= N; n++) {
        if (dp[n][lvl - 1] != -1) {
            dp[n][lvl] = dp[dp[n][lvl - 1]][lvl - 1];
        }
    }
}
int l, r;
for (int m = 0; m < M; m++) {
    cin >> l >> r;
    if (lvls[l] < lvls[r])swap(l, r);
    for (int lvl = 19; lvl >= 0; lvl--) {
        if (dp[l][lvl] != -1 && lvls[l] - lvls[r] >= pow(2, lvl))l = dp[l][lvl];
    }
    if (l == r) {
        cout << l << endl;
        continue;
    }
    for (int lvl = 19; lvl >= 0; lvl--) {
        if (dp[l][lvl] != dp[r][lvl])l = dp[l][lvl], r = dp[r][lvl];
    }
    cout << dp[l][0] << endl;
}
```

### Sparse Table
```cpp
for (int lvl = 1; lvl < lgN; lvl++) {
    for (int n = 0; n < max_N; n++) {
        if (n + pw2[lvl-1] >= max_N)
            continue; // 이 부분이 속도개선에 중요. 거의 4배차이쯤 나는듯. 브레이크가 아니고?
        dp[n][lvl] = min(dp[n][lvl - 1], dp[n + pw2[lvl - 1]][lvl - 1]);
    }
}
```
lg2, pw2계산, 0번 레벨 초기화는 알아서 하시고...


### Heap
* 시작은 1
* heapsize는 항상 valid한 마지막 item을 가르키게 (0일시 empty)

```cpp
const int max_heap = 501;
pair<int, int> heap[max_heap];
int heapSize=0;

void pop(){
    if (heapSize == 0)return;
    int nd = 1;
    heap[nd] = heap[heapSize--];
    while (nd <= heapSize){
        int l = -1, r = -1;
        if (nd * 2 <= heapSize)
            l = nd * 2;
        if (nd * 2 + 1 <= heapSize)
            r = nd * 2 + 1;

        int minI = -1;
        if (l != -1 and r != -1) minI = heap[l] > heap[r] ? r : l;
        else if (l == -1) minI = r;
        else if (r == -1) minI = l;

        if(minI != -1 && heap[minI] < heap[nd]){
            swap(heap[minI], heap[nd]);
            nd = minI;
        }else break;
    }
}

void push(pair<int, int> val){
    heap[++heapSize] = val;
    int nd = heapSize;
    while(nd != 1){
        int p = nd / 2;
        if(heap[p] > heap[nd]){
            swap(heap[p], heap[nd]);
            nd = p;
        }else break;
    }
}
```

### Segtree
```c++
int ary[MAXN * 4];

int update(int ind, int val, int node, int from, int to){
	if (ind < from || to < ind)return ary[node];
	if (from == to)return ary[node] = val;
	int mid = (from + to) / 2;
	return ary[node] = update(ind, val, node * 2, from, mid) + update(ind, val, node * 2 + 1, mid+1, to);
}

int squery(int x, int y, int node, int from, int to){
	if (x > y)return 0;
	if (y < from || to < x)return 0;
	if (x <= from && to <= y)return ary[node];
	int mid = (from + to) / 2;
	return squery(x, y, node * 2, from, mid) + squery(x, y, node * 2 + 1, mid+1, to);
}
```


### Union-and-find
* rank가 낮은 트리를 높은 트리 밑에 집어넣어야 1자형이 안생긴다

```cpp
int find(int u){
    if(u == p[u])return u;
    return p[u] = find(p[u]);
}

void merge(int u, int v){
    u = find(u);
    v = find(v);
    if (u == v)return;
    if (rank[u] > rank[v])swap(u, v);
    p[u] = v;
    if(r[u] == r[v])r[v]++;
}
```

### Quicksort

* `TODO`: 템플릿 입히기 (< 연산자를 comp(a, b)로 바꾸기)
* 정렬되어 있는 상황에 강한 퀵소트인듯
* 피봇이 앞에 있고 (종료 시 ri는 피봇보다 작은 마지막 원소를 가르키고, le는 피봇보다 큰 첫 번째 원소를 가르킴. 피봇보다 큰 걸 맨앞으로 보내면 안됨), le가 ri보다 먼저 움직이므로 (le <= ri 조건에 걸려 ri가 업데이트되지 않기 때문), ri의 마지막 위치가 피봇임 
* 조건문 : `le <= ri && !(위반 조건))`. 따라서
    1. le의 while문은 위반조건이 피봇보다 큰 원소를 만날 시
    2. ri의 while문은 위반조건이 피봇보다 작은 원소를 만날 시
    3. 둘이 스왑해주면 ok
* 조건문의 상황
    1. 끝까지 le < ri: 스왑해주면 됨
    3. 처음인 le <= ri여서 첫번째 while은 좀 가다 le > ri가 됨: 첫 while문은 ri인곳에서 걸림. ri인곳은 swap이 된 영역이므로 피봇보다 큰 (이전에 li가 찾은) 원소가 있기 때문
    2. 처음부터 le > ri: ri가 맞음
    4. 모두 피봇보다 작은 경우: le는 r 오른쪽 한칸 더 나감. ri는 끝에서 멈춤
    5. 모두 피봇보다 큰 경우: le는 제자리, ri는 피봇 자리

```cpp
void qsort(int l, int r, int ary[MAX]){
    if(l >= r)return;
    int pi = l, le = l+1, ri = r;
    while(le <= ri){
        while(le <= ri && !(ary[pi] < ary[le]))le++;
        while(le <= ri && !(ary[ri] < ary[pi]))ri--;
        if(le < ri)swap(ary[le], ary[ri]);
    }
    swap(ary[pi], ary[ri]);

    qsort(l, ri-1, ary);
    qsort(ri+1, r, ary);
}
```

* 밑에건 엄청 느림 (근데 케바케 아닐까?))
* Random_shuffle 한 번 돌리고 시작하거나 (expert에선 못쓰지 않나) pivot을 랜덤으로 잡아줄 것
* merge sort가 나은 것 같은디...? 보통 sorting이 가능한데 메모리가 부족한 경우는 없을 테니까?..
* 항상 smInd=-1 로 잡네 ㅡㅡ;

```cpp
void qsort(vector<pair<int, int>>& ary, int fr, int to){
    if(fr >= to)return;
    int piv = to, smInd = fr-1;
    for(int ind = fr; ind < to; ind++){
        if(ary[ind] < ary[piv]){
            smInd++;
            swap(ary[ind], ary[smInd]);
        }
    }
    swap(ary[smInd+1], ary[piv]);
    qsort(ary, fr, smInd);
    qsort(ary, smInd+2, to);
}
```

### Mergesort
N=1일때 다음 null처리 깜빡하지 말자 (linked list sorting하는 경우)
```cpp
ListNode* mergesort(ListNode* head, int N){
    if (N == 1){
        head->next = NULL; //이부분 중요
        return head;
    }
    int mid = (int)(N/2);
    ListNode* r = head;
    for(int i = 0; i<mid; i++)r = r->next;
    head = mergesort(head, mid);
    r = mergesort(r, N-mid);
    ListNode* ret = NULL;
    ListNode* pnt = NULL;
    if(head->val < r->val){
        ret = head;
        head = head->next;
    }else{
        ret = r;
        r = r->next;
    }
    pnt = ret;
    while(head != NULL || r != NULL){
        if(head != NULL && r != NULL){
            if(head->val < r->val){
                pnt->next = head;
                head = head->next;
            }else{
                pnt->next = r;
                r = r->next;
            }
        }else if(head != NULL){
            pnt->next = head;
            head = head->next;
        }else{
            pnt->next = r;
            r = r->next;
        }
        pnt = pnt->next;
    }
    return ret;
}

```


### Dijkstra

### Bellman-ford

### Edmond-Karp

### Dinic