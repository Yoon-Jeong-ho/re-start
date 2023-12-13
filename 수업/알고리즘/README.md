# 힙
### 힙 순서

```key(v) >= ket(parent(v)) ```

### 힙 높이
$\log{n}$
## 힙을 이용한 우선 순위 큐 구현
### 힙 삽입

```
Alg insertItem(k)

1. advanceLast()
2. z= last
3. Set node z to k
4. expandExternal(z) 
5. upHeap(z)
6 return


Alg upHeap(v)

1. if(isRoot(v))
    return
2. if(key(v) >= key(parent(v)))
    return
3. swapElements(v,parent(v))
4. upHeap(parent(v))
```

### 힙 삭제

```
Alg removeMin()

1. k = key(root())
2. w = last
3. Set root to key(w)
4. retreatLast() - 삭제 후 마지막 노드 갱신
5. z = rightChild(w)
6. reduceExternal(z)
7. downHeap(root())
8. return k


Alg downHeap(v)

1.if(isExternal(leftChild(v))&isExternal(rightChild(v)))
    return
2. smaller = leftChild(v)
3.if(isInternal(rightChild(v)))
    if(key(rightChild(v)) < key(smaller))
        smaller = rightChild(v)
4.if(key(v)<= key(smaller))
    return
5. swapElements(v,smaller)
6. downHeap(smaller)
외부노드면 끝 > 좌우 중 작은 것 찾기 > 그게 나랑 비교해서 크면 바꾸기 > 재귀


Alg reduceExternal(z)

1. w= z.parent
2. zs = sibling(z)
3. if(isRoot(w))
        root = zs
        zs.parent = NULL
    else
        g = w.parent
        zs.parent = g
        if(w == g.left)
            g.left = zs
        else if(w == g.right)
            g.right = zs
4. putnode(z)
5. putnode(w)
6. return zs
```

### 마지막 노드 갱신

```
Alg advancelast
1. 현재 노드가 오른쪽 자식인 동한 부모 노드로 이동한다. 
2. 현재 노드가 왼쪽 자식임녀 형제 노드로 이동한다.
3. 현재 노드가 내부노드인 동안, 왼쪽 자식으로 이동한다.
6시에서 시계 방향으로 돌기

Alg retreatLast
1. 현재 노드가 왼쪽 자식인 동안 부모 노드로 이동한다.
2. 현재 노드가 오른쪽 자식이면 형제 노드로 이동한다.
3. 현재 노드가 내부노드인 동안 오른쪽 자식으로 이동한다.
6시에서 반 시계 방향으로 돌기
```

## 힙 성능
|힙구현|size ,isEmpty|insertItem, removeMin|minKey, minElement|advanceLast, retreatLast|공간소요|
|---|---|---|---|---|---|
|연결|O(1)|O($log{n}$)|O(1)|O($log{n}$)|O(n)|
|순차|O(1)|O($log{n}$)|O(1)|O(1)|O(n)|

## 힙 정렬
```
Alg heapSort(L)

1. H = empty heap
2. while(!L.isEmpty())     -phase 1
    k = L.removeFirst()
    H.insertItem(k)
3. while(!H.isempty())     -phase 2
    k = H.removeMin()
    L.addLast(k)
4. return
```
### 제자리 힙 정렬
heapSort의 공간 사용을 줄일 수 있다.  
여기선 우리가 써왔던 최소힙(루트가 제일 작은 힙)이 아니라 최대힙(루트가 제일 큰 힙)을 사용한다.
```
Alg inPlaceHeapSort(a)

1. buildHeap(a)           -phase1
2. for i = n downto 2     -phase2
    a[1] swap a[i]
    downHeap(1,i-1)
3. return


Alg buildHeap(a)

1. for i = 1 to n
    insertItem(a[i])
2. return


Alg downHeap(i,last)

1. left = 2i
2. right = 2i+1
3. if(left > last)
    return
4. greater = left
5. if(right<=last)
        if(key(a[right])>key(a[greater]))
            greater = right
6. if(key(a[i])>= key(a[greater]))
    returnm
7. a[i] swap a[greater]
8. downHea(greater,last)
```


### 상향식 힙 생성
heapSort의 속도를 높일 수 있다.

#### 재귀적 상향식 힙 생성

```
Alg buildHeap(l)

1. t = convertToCompleteBinaryTree(l)
2. rBuildHeap(T.root())
3. return t


Alg rBuildheap(v)
if(isInternal(v))
    rbuildHeap(leftChild(v))
    rbuildHeap(rightChild(v))
    downHeap(v)
return
```

#### 비 재귀적 상향식 힙 생성

```
Alg buildHeap(a)

1. for i = n/2 downto 1
    downHeap(1,n)
2. return
```

## 요약
- 우선순위 큐를 구현하는 또 하나의 방안으로 힙이 있다. 힘은 힙 순서 속성과 완전 이진 트리 속성을 모두 만족하는 이진트리를 할한다.
- n개의 키를 저장한 힙의 높이는$O(\log{n})$이다.
- 힙을 연결 또는 순차 데이터 구조롤 구현할 수 있다. 두가지 구현에 대한 성능은 대부분 작업에서 동일하지만 마지막 노드의 갱신 작업에서는 차이가 있다.
- 힙정렬은 힙을 이용한 정렬이다.
- 힙 정렬은 반복적인 삽입에 의해 힙을 생성하는 1기와 힙으로부터 반복적인 루트 삭제를 통해 정렬을 수행하는 2기로 구성된다. 각 기는 $O(n\log{n})$ 시간에 수행하므로 힙 정렬은 전체적으로 $O(n\log{n})$ 시간에 수행한다.
- 힙 정렬의 기억장소 소요량을 줄이기 위해 제자리에서 수행하도록 구현할 수 있다.
- 재귀적 또는 비재귀적 상향식 힙 생성을 통해 힙 정렬 1기의 수행시간을 $O(n)$ 시간으로 단축할 수 있다.

## 연습문제
### 힙 내 최대 키의 위치
#### 적어도 두 개 이상의 키를 저장한 최소힙에 최대 키를 가진 항목이 저장되는 위치는 어디인가? 힙이 유일한 키만 저장하는 경우와 중복 키를 저장하는 경우로 나누어 각각 답하라.
- 아무노드 
>중복 허용: 최대키가 중복이면 그 위에 있을 가능성
- 루트를 제외한 아무 노드
- 가장 깊은 내부 노드 가운데 하나
- 외부 노드 바로 위의 내부노드 가운데 하나 
>유일키: 최대키가 유일이면 제일 밑에 저장

### 힙과 이진트리 순회
#### 7개의 유일한 원소(1, 2, 3, 4, 5, 6, 7)를 저장하는 힙 T를 다음 방식으로 순회할 경우 T의 원소들이 정렬 순서로 얻어지는 T가 존재할 수 있을까? 있다면 각각의 T의 예를 들어라
- 선위순회 O
- 중위순회 X
- 후위순회 O

# 합병정렬
### 분할 통치법
1. 재귀적으로 계속 나눈다.
2. 제일 밑에서 각각에 대한 문제를 재귀적으로 해결한다.
3. 합치면서 각각의 문제를 해결한다.

## 합병 정렬

```
Alg mergeSort(l)

1. if(l.size()>1)
    l1, l2 = partition(l,n/2)
    mergeSort(l1)
    mergeSort(l2)
    l = merge(l1,l2)
2. return
```

### 합병
```
Alg merge(l1,l2)

1. l= emptylist
2. while(!l1.isEmpty() && !l2.isEmpty() ){
    if (l1.get(1) <= l2.get(1))
        l.addLast(l1.removeFirst)
    else
        l.addLast(l2.removeFirst)
}
3. while(!l1.Empty)
    l.addLast(l1.removeFirst())
4. while(!l2.Empty)
    l.addLast(l2.removeFirst())
5. return l
```
### 점화식
$ T(n) = c$ __________________ (n<2)  
$    T(n) = 2T(n/2) + O(n) $ (n>=2)

### 배열로 구현한 합병 정렬
```
Alg mergeSort(a)

1. rMergeSort(A,0,n-1)
2. return


Alg rMergeSort(a,l,r)

1. if(l<r){
    m = (i+r)/2
    rMergeSort(a,l,m)
    rMergeSort(a,m+1,r)
    merge(a,l,m,r)
}
2. return


Alg merge(a,l,m,r)

1. i, k = l
2. j = m+1
3. while(i<=m &&j<=r){
    if (a[i]<= a[j])
        b[k++] = a[i++]
    else
        b[k++] = a[j++]
}
4. while(i<= m)
    b[k++] = a[i++]
5. while(j<= r)
    b[k++] = a[j++]
6. for( k = l to r)
    a[k] = b[k]
7. return
```

## 요약
- 분할통치법은 일반적인 알고리즘 설계 기법의 일종이다. 분할통치법에 의한 알고리즘은 분할, 재귀, 통치의 세 단계 해결 과정을 가진다.
- 합병 정렬은 분할통치법에 기초한 정렬 알고리즘이다. 합병 정렬은 힙 정렬처럼, 비교에 기초한 정렬이며 $O(n\log{n})$ 시간에 수행한다. 하지만 힙 정렬과는 달리, 외부의 우선순의 큐를 사용하지 않으며 데이터를 순차적 방식으로 접근한다.
- 두개의 순서 리즈트를 합병하는 merge는 $O(n)$ 시간과 $O(n)$ 공간을 소요한다.
## 연습문제
### n개의 수를 저장한 무순배열 A의 최대 원소를 분할통치법에 의해 찾는 알고리즘 arrayMax(A,n)
다 반씩 잘라서 하나씩 만든다음에 둘이 비교해서 가장 큰것 가지고 오기
```
Alg arrayMax(A,n)

1. return rArrayMax(A,0,n-1)


Alg rArrayMax(A,l,r)

1. if(l==r)
    return A[l]
2. mid = (l+r)/2
3. maxL= rArrayMax(A,l,mid)
4. MaxR = rArrayMax(A,mid+1,r)
5. return max(maxL, maxR)
```


# 퀵 정렬

```
Alg quickSort(l)

1. if(l.size()>1){
    k = a position in l
    lt, eq, gt = partition(l,k)
    quickSort(lt)
    quickSort(gt)
    l = merage(lt,eq,gt)
}
2. return
```

1. 피봇을 기준으로 큰 것은 오른쪽, 작은것은 왼쪽으로 나눈뒤 그 나눈 것 다시 재귀하여 크기 1이 될 때 까지 돌리기.
2. 합치는 것은 그대로 합치기

### 분할
합병정렬에선 merge가 오래걸렸지만 퀵정렬에서는 partition이 오래걸린다.
```
Alg partition(l,k)

1. p = l.get(k)
2. lt,eq,gt = empty list
3. while(!l.isEmpty()){
    e = l.removeFirst
    if(e<p)
        lt.addLast(e)
    else if(e == p)
        EQ.addLast(e)
    else {e > p}
        gt.addLast(e)
}
4. return lt,eq,gt
```


## 제자리 퀵 정렬

```
Alg inPlaceQuickSort(l,i,r)

1. if(l >= r)
    return
2. k = a position between i and r
3. a, b = inPlacePartition(l,i,r,k)
4. inPlaceQuickSort(l,i,a-1)
5. inPlaceQuickSort(l,b+1,r)


Alg inPlacePartition(l,i,r,k)

1. p = a[k]
2. a[k] swap a[r]
3. i = l
4. j = r-1
5. while(i<=j){
    while(i<=j && a[i] <= p )
        i = i+1
    while(j>= i && a[j]>=p)
        j = j-1
    if(i<k)
        a[i] swap a[j]
}
6. a[i] swap a[r]
7. return i
```

| |합병정렬|퀵정렬|
|----|----|----|
|기법|분할통치법|분할통치법|
|실행시간|O($nlog{n}$)최악실행시간|O($n^2$)최악 실행 시간 </br>  O($nlog{n}$)기대 실행 시간|
|분할 vs 합병|분할은 쉽고, 합병은 어렵다.|분할은 어렵고, 합병은 쉽다.|
|제자리 구현|제자리 합병이 어렵다.|제자리 분할이 쉽다.|
|실제 작업 순서|작은 것에서 점점 큰 부문제로 진행|큰 것에서 점점 작은 부문제로 진행|

## 요약
- 퀵 정렬은 합병 정렬과 마찬가지로 분할 통치법에 기초한 정렬 알고리즘이다.
- 합병 정렬에서 합병 단계가 시간이 가장 많이 걸리는 단계였는데 비해 퀵 정렬에서는 분할 단계에 가장 많은 시간을 소요한다.
- 퀵 정렬의 최악은 분할 시에 기준원소가 항상 유일한 최소 또는 유일한 최대 원소일 경우다. 이 경우 퀵 정렬의 최악 실행시간은 O($n^2$)이다.
- 무작위 퀵 정렬 버전은 분할 때마다 리스트의 원소 가운데 무작위 원소를 기준원소로 선택합으로써 O($n\log{n}$)기대실행시간을 보장한다.
- 무작위 큌 정렬의 점근적 실행시간은 힙 정렬이나 합병 정렬과 동일하지만, 퀵 정렬이 반복 수행하는 작업의 내용이 비교적 간단한 관계로 실제 수행시간 면에서 위의 두 정렬 알고리즘에 비해 매우 빠르다.

## 연습문제
### 다음 입력 리스트에 대한 quick-sort 알고리즘의 수행 내용을 보여라. 분할이 완료될 때마다 분할의 내용을 ((LT),EQ,(GT))형태로 괄호로 묶어 표시하라
- 22 15 36 44 10 3 9 25 29 13
### 퀵 정렬 알고리즘의 결정적 버전이다. n-원소 리스트의 마지막 원소를 기준으로 삼는 대신 위치 $\lfloor n/2 \rfloor$ 의 원소, 즉 리스트의 중앙에 있는 원소를 기준원소로 삼는다고 전제한다. 퀵 정렬의 이 버전을 이미 정렬된 리스트에 대해 수행할 경우의 실행시간을 구하라. 그리고 이 버전을 수행할경우 $O(n^2)$시간이 소요되는 입력 리스트의 특성을 설명하라
nlogn시간이 소요된다.  
- $O(n^2)$ 최악 실행 시간, $O(n\log{n}$)기대 실행 시간에 수행된다.  

항상 최소나 최대값을 가질 경우이다.
- 이 버전을 수행할 경우 $O(n^2)$시간이 소요되는 입력리스트는 선택된 기준원소가 항상 부리스트의 최대 또는 최소 원소가 되는 특성을 가져야 한다. 다시 말해 GT 또는 LT어느 한쪽에 항상 아무 원소가 없게 되면 $O(n^2)$ 최악시간을 초래하게 된다.

### 혜진이는 어떤 무작위 알고리즘에 대해서라도 최악실행시간과 기대실행시간은 상수시간 배수의 차이만 있다고 주장한다. 혜진이의 주장이 옳은지 그른지 논거와 함께 설명해라
이미 퀵정렬만 봐도 $O(n^2), O(n\log{n})$ 이기 때문에 아니다.
- 그르다. 무작위 퀵 정렬의 경우 최악실행시간은 $O(n^2)$이지만 기대실행시간은 $O(n\log{n})$ 이기 때문이다.
### 불할 대상 배열의 중앙값을 찾아 기준 원소로 삼는 patition 알고리즘을 사용하는 quickSort 알고리즘이 있다. 이 quickSort 알고리즘의 실행시간을 구하라.
$O(n\log{n})$
- $O(n\log{n})$ 시간이 걸린다. 중앙값은 퀵 선택을 이용하면 O(n) 시간에 찾을 수 있기 때문이다.

# 정렬 일반

## 정렬의 안전성
두 개의 항목 $(k_i,e_i)$와 $(k_j,e_j)$에 대해, $k_i == k_j$이며 i<j일 때 정렬 후에도 $(k_i,e_i)$가 $(k_j,e_j)$보다 앞서 있는 것이 보장된다면 그 정렬 알고리즘을 안정적(stable)이라고 한다.

## 비교 정렬 알고리즘 비교
| |시간|주요 전략|비고|
|---|---|---|---|
|선택 정렬|O($n^2$)|우선 순위 큐 </br>(무순리스트로 구현)|제자리 구현 가능</br>느림(소규모 입력에 적당)</br>안정|
|삽입 정렬|O($n^2$)|우선 순위 큐 </br>(순서리스트로 구현)|제자리 구현 가능</br>느림(소규모 입력에 적당)</br>안정|
|힙 정렬|O($nlog{n}$)|우선 순위 큐 </br>(힙으로 구현)|제자리 구현 가능</br>빠름(대규모 입력에 적당)</br>재구성 과정에서 바뀜(불안정)|
|합병 정렬|O($nlog{n}$)|분할통치 |순차 데이터 접근</br>빠(초대규모 입력에 적당)</br>안정|
|퀵 정렬|O($nlog{n}$)기대시간|분할통치|제자리 구현 가능, 무작위 버전</br>가장 빠름(대규모 입력에 적당)</br>분할 과정에서 바뀐다 (불안정)|

## 요약
- 입력 리스트ㅡ이 키들을 비교하여 원소들을 키 순서에 따라 재배치하는 방식의 정렬을 비교정렬이라 한다. 
- 어떤 비교 정렬 알고리즘이라도 최소 $n\log{n}$ 시간에 수행한다.
- 비교정렬 알고리즘 가운데 힙 정렬, 합병 정렬, 그리고 무작위 버전 퀵 정렬은, 비교정렬의 하한데 수행한다. 이에 비해 선택 정렬, 삽입 정렬, 그리고 결정적 버전 퀵 정렬 알고리즘의 최악의 경우는 비교정렬의 하한에 미치지 못하는 느린 시간에 수행한다.

## 연습문제

### 유신은 어떤 비교 정렬 알고리즘이라도 그 실행시간에 상수 배수 이상의 영향 없이 안정적 알고리즘으로 수정할 수 있다고 주장한다. 유신의 주장이 옳은지 그른지 논거와 함께 설명하라.

같은 값이 있는지 한번 확인만 하는 것이면 1시간에 끝날 수 있다.
- 옳다. 수정 방법은 다음과 같다.
> 비교 정렬 알고리즘을 안정적으로 수정하기 위해 입력 리스트 A의 모든 원소에 리스트에서의 원래 위치를 표시한다.(라벨 등으로 저장).  
만약 A[i]= A[j]이면 i와 j를 비교하여 두 원소의 위치를 알아내 안정적인 결과가 되도록 처리한다.  
이 과정에서 실행 시간은 (최대)상수 2배만큼 증가한다.

### 계백은 비교 정렬 알고리즘에서 사용할 우선순위 큐를 다음 두 성질을 모두 만족하도록 설계 가능하다고 주장한다.
- 작업 removeMin을 O(1)시간에 수행
- 작업 buildHeap을 O(n)시간에 수행    

제거하는데 1 시간은 말이 안된다. 로그 엔이 필수이다.
> 그르다. 이유는 다음과 같다.  
그러한 우선순위 큐가 존재한다면 buildHeap을 수행한 후 (O(n) 시간 소요), 최소 키를 n번 삭제함으로 써(n*O(1)= O(n)) 정렬을 완료할 수 있을 것이다.
그러면 이 알고리즘은 비교에 기초하여 O(n)시간에 정렬한 것이 된다. 이는 비교 정렬의 하한시간 $O(n\log{n})$을 위반한 것이 된다.

### 개소문은 "최악의 경우 최대 6번의 비교를 수행하여 5개의 수를 비교정렬할 수 있다."고 개소문이 옳은지 그른지 논거와 함께 설명하라
ㄴㄴ 10번
- 그르다. 이유는 다음과 같다.
> 5개의 수를 비교정렬 하는 결정트리의 잎의 수는 5!이며 트리의 높이는 최소 log 5! 이다.  
5!= 120이므로 $6<\log{5!}<7$ 이다. 왜냐하면 $2^6 = 64, 2^7= 128$이므로  
따라서 최소 7번의 비교가 필요하다.

### 문희는 제자리 정렬 알고리즘에 이미 정렬된 배열이 입력으로 주어지면 열의 내용을 전혀 변경(즉, write) 하지 않은 채로 반환한다고 주장한다. 문희가 옳은지 그른지 논거와 함께 설명하라.
ㄴㄴ 퀵정렬은 바뀔 수 있다. 안정성이 별로다.
- 그르다. 제자리란 말은 상수의 추가 이억 공간만을 사용한다는 의미다. 안정적인 정렬 알고리즘이어야만 주어진 순서 배열을 변경하지 않는다.
### 최악의 겨우 O($n\log{n}$) 의 실행시간을 가지는 비교정렬 알고리즘 가운데 안정성이 보장되니 않는 알고리즘이 무엇인지 답하고 안정성이 보장되지 않는 이유를 간략히 설명하라
힙, 퀵 정렬 같은 것이 있을 경우 순서가 바뀌게 된다.
- 힙정렬이다. 힙을 재구성하는 과정에서 동일한 키에 대해 순서가 바뀔 수 있기 때문이다.

# 사전 

## method
### 일반
- integer size(): 사전의 항목 수를 반환
- boolean isEmpty(): 사전이 비어있는지 여부를 반환
### 접근
- element findElement(k): (키, 원소) 항목들의 모음인 사전에 키 k를 가진 항목이 존재하면 해당 원소를 반환, 그렇지 않으면 특별 원소 NoSuchKey를 반환

### 갱신
- insertItem(k,e): 사전에 (k,e) 항목을 삽입
- element removeElement(k) : 사전에 키 k를 가진 항목이 존재하면 해당 항목을 삭제하고 원소를 반환, 그렇지 않으면 특별 원소 NoSuchKey를 반환

## 사전 ADT 구현
|구현 형태|구현 종류|예|주요 탐색 기법|
|:---:|:---:|:---:|:---:|
|리스트|무순사전ADT|기록 파일|선형 탐색|
|리스트|순서사전|일람표|이진 탐색|
|트리|탐색트리|이진탐색트리,</br>AVL트리,</br>스플레이 트리|트리 탐색|
|해시 테이블| | |해싱|

### 무순사전

```
Alg findElement(k)

1. l.initialize(i)
2. while(l.isValid(i)){
    if(l.key(i)==k)
        return l.element(i)
    else
        l.advance(i)
}
3. return NoSuchKey
```
### 순서 사전

- 탐색 : 이진탐색을 사용하면 O(logn)시간에 수행
- 삽입 : 최악의 경우 O(n)
- 삭제 : O(n)

#### 선형 탐색
조기 실패가 보장, O(n)최악 실행 시간
```
Alg findElement(k)

1. l.initialize(i)
2. while(l.isvalid(i)){
    if(l.key == k)
        return l.element(i)
    else if(l.ket(i)> k)
        return NoSuchKey
    else
        l.advance(i)
}
3. return NoSuchKey
```

#### 이진 탐색
배열로 구현되었다면 $O(\log{n})$ 시간에 수행  
연결리스트로 구현되었다면 이진 탐색으로 얻는 이득은 없다.
```
Alg findElement(k)

1. return rFindElement(k,0,n-1)


Alg rFindElement(k,l,r)

1. if(l>r)
    return NoSuchKey
2. mid = (l+r)/2
3. if(k == key(a[mid]))
    return element(a[mid])
   else if( k< key(a[mid]))
    return rFindElement(k,l,mid-1)
   else {k > key(a[mid])}
    return rFindElement(k,mid+1,r)
```

## 요약
- 사전 ADT는 (키,원소) 쌍으로 구성된 데이터 항목의 집단을 모델링한다.
- 사전 ADT에 대한 주요 작업은 탐색, 삽입 그리고 삭제가 있다.
- 사전 관련 작업에 영향을 미치는 두 가지의 상이한 전제로는 유일 키와 중복 키 두 가지가 있다.
- 기록 파일로 대표되는 무순사전 ADT는 삽입이 빠른 대신 탐색과 삭제가 트린 특성을 가진다. 무순 사전에 대해서는 선형 탐색을 수행한다.
- 일람표로 대표되는 순서사전 ADT는 탐색이 빠른 대신 삽입과 삭제가 느린 특성을 가진다. 순서사전에 대해서는 이진탐색을 수행할 수 있다.
- 배열로 구현된 순서리스트에 대한 이진탐색은 최악의 경우$O(\log{n})$시간에 수행한다.
## 연습문제

### 무순리스트에 대한 선형탐색 알고리즘 findElement의 배열 버전과 연결리스트 버전을 각각 의사코드로 다시 작성하라.
while문 돌면서 하루종일 찾기 찾으면 그 키 반환하는거고 없으면 없다고 반환하는거고...


### 이번엔 무순리스트와 순서리스트에 대한 선형탐색 알고리즘 findElement를 그대로 사용한다는 전제 하에 findElement가 호출하는 아래의 보조 메쏘드들을 배열과 연결리스트 버전으로 각각 의사코드로 작성하라.

### 크기 n인 순서배열 A에서 키 k를 가지는 원소를 찾는 findElement(k)의 비재귀 버전을 의사코드로 작성핟라.
중앙찍고 와일문 돌려야주

### 정수가 아닐 수도 있는 수들의 순서 배열 A[0..m-1]이 있다. A의 원소는 중복이 있을 수 있다. 역시 정수가 아닐 수도 있는 주어진 수 s에 대해,$A[i_1] + A[i_2] = s$ 를 만족하는 $i_1,i_2$를 찾는 알고리즘을 의사코드로 작성하라. 알고리즘은 $O(n^2)$시간보다 빨리 수행되어야 한다. 참고로 앞어 응용문제에서는 무순배열에 대해 다루었다.
시작과 끝에서 출발하여 더해서 작으면 시작을 한칸 앞으로 가고 크면 끝에서 앞으로 한칸 오기.

### n개의 유일한 키로 이루어진 배열 A로 순서사전을 구현했다. 주어진 두개의 키 $k_1, k_2$에 대해, 사전의 키들 중 $k_1<=k <=k_2$를 만족하는 키 k의 원소들을 반환하는 $O(\log{n} + s)$ 시간 알고리즘을 의사코드로 작성하라. 여기서 s는 반환되는 원소의 수다.
두개 다 이진분류로 찾고 그사이 하나씩 주르륵 하면 저 시간 나올듯?



# 탐색 트리
## 이진 탐색 트리
```
Alg findElement(k)

1. w = treeSerch(root(),k)
2. if (isExternal(w))
    return NoSuchKey
   else 
    return element(w)


Alg treeSearch(v,k)

1. if(isExternal(v))
    return v
2. if(k == key(v))
    return v
   else if(k < key(v))
    return treeSerch(leftChild(v),k)
   else {k > key(v)}
    return treeSearch(rightChild(v),k)


Alg insertItem(k,e)

1. w = treeSearch(root(),k)
2. if(isInternal(w)) - 이건 이미 똑같은게 있다는 것
    return
   else
    Set node w to(k,e)
    expandExternal(w)
    return
```
### 삭제
1. 트리 T에 대해 w의 중위순회 계승자 y와 그 자식노드 z을 찾아낸다.  
- 노드 y는 우선 w의 오른쪽 자식으로 이동한 후, 거기서부터 왼쪽 자식들만을 따라 끝까지 내려가면 도달하게 되는 마지막 내부노드며, 노드 z은 y의 왼쪽 자식인 외부노드다.
- y는 T를 중위순회할 경우 노드 w 바로 다음에 방문하게 되는 내부노드이므로 w의 중위순회 계승자라 불린다.
- 따라서 y는 w의 오른쪽 부트리 내 노드 중 가장 왼쪽으로 돌출된 내부노드다.
2. y의 내용을 w에 복사한다.
3. reduceExternal(z) 작업을 사용하여 노드 y와 z를 삭제한다.

```
Alg remoceElement(k)

1. w = treeSerch(root(),k)
2. if (isExternal(w))
    return NoSuchKey
3. e = element(w)
4. z = leftchild(w) - 오른쪽으로 가야 되는거 아닌가?
5. if (!isExternal(z))
    z=rightChild(W) - 이건 왼쪽 아닌가???
6. if (isExternal(z))
    reduceExternal(z)
   else 
    y = inOrderSucc(w)
    z = leftChild(y)
    Setnode w to (key(y),element(y))
    reduceExternal(z)
7. return e
```

- 오른쪽 트리에서 가장 작은 값을 넣거나 왼쪽 트리에서 가장 큰 값을 넣는 경우가 있다.

## AVL트리
자식들의 좌우 높이 차이가 1을 넘지 않는 이진탐색트리  
삽입이나 삭제 작업 후에 불균형이 생길 수 있다.
### 삽입

```
Alg insertItem(k,e)

1. w = treeSearch(root(),k)
2. if (isInternal(w))
    return
   else
    Set node w to(k,e)
    expandExternal(w)
    searchAndFixAfterInsertion(w)
    return

Alg searchAndFixAfterInsertion(w)

1. w에서 t의 루트로 향해 올라가다가 처음 만나는 불균형 노드를 z라 하자.
(없으면 return)
2. z의 높은 자식을 y라 하자.
    {수행 후 y는 w의 조상이 되는 것에 유의}
3. y의 높은 자식을 x라 하자
    {수해 후 노드 x가 w와 일치할 수도 있으며 x가 z의 손자임을 유의. y의 높이는 자신의 형제노드의 높이보다 2가 더 많다.}
4. restructure(x,y,z)
    {수행 후, 이제 b를 루트로 하는 부트리의 모든 노드는 균형을 유지한다. 높이균형 속성은 노드x,y,z에서 지역적으로나 전역적으로나 모두 복구된다.}
5. return


Alg restructure (x,y,z)

1. x,y,z의 중위순회 방문순서의 나열을 (a,b,c)라 하자
2. x,y,z의 부트리들 가운데 x,y,z을 루트로하는 부트리를 제외한 4개의 부트리들의 중위순회 방문순서의 나열을 (t0,t1,t2,t3)라 하자.
3. z을 루트로 하는 부트리를 b를 루트로 하는 부트리로 대체한다.
4. t0와 t1을 각각 a의 왼쪽 및 오른쪽 부트리로 만든다.
5. t2와 t3를 각각 c의 왼쪽 및 오른쪽 부트리로 만든다.
6. a와 c를 각각 b의 왼쪽 및 오른쪽 자식으로 만든다.
7. return b
```

### 삭제
```
Alg removeElement(k)

1. w = treeSearch(root(),k)
2. if (isExternal(w))
    return NoSuchKey
3. e = element(w)
4. z = leftChild(w)
5. if (!isExternal(z))
    z = rightChild(w)
6. if (isExternal)
    zs = reduceExternal(z)
   else{
    y = inOrdersucc(w)
    z = leftChild(y)
    Set node w to (key(y),element(y))
    zs = reduceExternal(z)
   }
7. searchAndFixAfterRemoval(parent(zs))
8. return e


Alg searchAndFixAfterRemoval(w)

1. w에서 t의 루트로 향해 올라가다가 처음 만나는 불균형 노드를 z이라 하자 (그러한 z이 없다면 return).
2. z의 높은 자식을 y라 하자.
    {수행 후 y는 w의 조상이 아닌 z의 자식이 되는 것에 유의}
3. y의 두 자식 중 어느 한쪽이 높으면 높은 자식을 x라 하고, 두 자식의 높이가 같으면 둘 중 y와 같은 쪽의 자식을 x로 선택한다.
4. b = restructure(x,y,z)
    {수행 후 높이 균형 속성은 방금 전 z을 루트로 했으나 지금은 변수 b를 루트로 하는 부트리에서 지역적으로 복구된다. 하지만 방금의 개조에 의해 b를 루트로 하는 부트리의 높이가 하나 줄어들 수 있으며 바로 이 때문에 b의 조상도 균형을 잃을 수 있다. 즉, 삭제 후 한번의 개조만으로는 높이균형속성을 전역적으로 복구하지 못할 수도 있다.}
5. t를 b의 부모부터 루트까지 올라가면서 균형을 잃은 노드를 찾아 수리하는 작업을 계속한다.
```

## 요약
- 탐색트리를 이용하여 사전 ADT를 구현할 수 있으며 여기에는 이진탐색트리, AVL트리, 스플레이 트리 등의 방식이 있다.
- u, v, w가 이진탐색트리의 노드며 u와 w가 각각 v의 왼쪽과 오른쪽 부트리에 존재할 때 key(u)< key(v) <= key(w) 가 성립한다.
- AVL트리는 트리 T의 모든 내부노드 v에 대해 v의 자식들의 좌우 높이 차이가 1을 넘지 않는 이진탐색트리를 말한다. 이를 높이균형 속성이라고 한다.
- AVL 트리에 대한 갱신은 높이 균형 속성을 파괴할 수 있다. 트리에 대한 개조 작업을 통해 높이균형 속성을 회복할 수 있으며 삽입 후의 개조 작업은 O(1) 시간에, 삭제 후의 개조 작업은 $O(\log{n})$시간에 수행한다.
- AVL 트리로 구현된 사전의 주요 메쏘드들은 모두 $O(\log{n})$ 시간에 수행한다.

## 연습문제
### D를 이진탐색트리로 구현된 n 항목의 순서사전이라고 가정하자. D를 위한 다음의 메쏘드를 O(n) 시간에 수행하도록 구현하라.
- elements(): 이진탐색트리로 구현된 사전 D의 모든 원소들을 반환
그냥 선,중,후위순회로 돌아다니면 끝인거 아녀?

```
Alg elements()

1. L = empty list
2. rElements(T.root(),L)
3. return L.elements()


Alg rElements(v,L)

1. if(T.isExternal(v))
    return
2. L.addLast(T.element(v))
3. rElements(T.leftChild(v),L)
4. rElements(T.rightchild(v),L)
```

### 알고리즘 treeSearch(v,k)의 비재귀 버전을 의사코드로 작성하라
제일 왼쪽에서 시작해서 올라가면서 왼쪽 오른쪽 다 보면서 가기...?

```
Alg treeSearch(v,k)

1. while(isInternal(v)){
    if(k == key(v))
        return v
    else if (k<key(v))
        v = leftChild(v)
    else {k > key(v)}
        v = rightChild(v)
}
2. return v
```

전체를 보는게 아니라 찾는 것이었다.
### 비어있는 이진탐색트리에 아래 키들을 가진 항목들을 주어진 순서대로 삽입한다. 
- 키 : 30, 40, 24, 58, 48, 26, 11, 13  

삽입이 수행될 때마다 변화하는 트리 모습을 보여라  
30 가운데로 알아서 찢어지겄지

### 중복 키를 가진 이진트리 응용문제에서 제시했던 탐색알고리즘 findAllElements의 다른버전을 의사코드로 작성하라.

```
Alg findAllElements(k)

1. L = empty list
2. w = T.root()
3. while(T.isInternal(w)){
    if(k == T.key(w)){
        L.addLast(T.element(w))
        w = T.rightChild(w)
    }
    else if (k<T.key(w))
        w = T.leftChild(w)
    else {k>T.key(w)}
        w = T.rightChild(w)
}
return L.elements()
```

### 윤하는 이진탐색트리에 특정 집단의 키들을 삽입할 때 삽입 순서는 상관이 없다고 주장한다. 즉, 동일한 키 집단에 대해서는 동일한 이진탐색트리가 생성된다는 것이다. 윤하가 옳은지 그른지 논거와 함께 설명하라

그르다. 시작 키에 따라 전혀 다른 트리가 나오기 때문이다.
> 그르다. 그름을 보일 수 있는 사례는 하나만이 아니다. 일례로 먼저 키 9, 5, 12, 7, 13를 주어진 순서로 삽입하여 생성된 이진탐색트리를 만들어 보인다. 다음, 앞서의 입력에서 5와 7의 순서를 뒤바꿔서, 즉 9,7,12,5,13를 삽입하여 생성된 이진탐색트리를 만들어 보인다.

### 윤하는 앞서 자신이 내세운 주장을 약간 수정했다. 이제 그녀는 이진탐색트리가 아니라 AVL 트리에 특정 집단의 키들을 삽입할 때 삽입 순서는 상관이 없다고 주장한다. 동일한 키 집단에 대해 동일한 AVL 트리가 생성된다는 것이다. 윤하가 옳은지 그른지 논거와 함께 설명하라.
그르다. 불균형만 안만들고 트리를 만든다면 그 트리는 모양이 전혀 다르게 여러개가 나올 것 이기 때문이다.
> 그르다. 그름을 보일 수 있는 사례는 하나만이 아니다. 일례로 먼저 키 9, 5, 12, 7, 13을 주어진 순서로 삽입하여 생성된 AVL트리를 만들어 보인다. 다음, 5와 7을 순서를 뒤바꿔서, 즉 키 9,7,12,5,13를 삽입하여 생성된 AVL트리를 만들어 보인다.

### 비어 있는 AVL트리에 아래 키들을 가진 항목들을 주어진 순서대로 삽입한다. 삽입이 수행될 때마다 변화하는 트리 모습을 보여라
- 키: 2, 1, 4, 5, 9, 3, 6, 7  

### 배열로 표현된 n-노드 이진트리에서 회전을 수행하는데 n시간이 소요되는 이유를 설명하라
뒤에 까지 다 봐야 해서?
> 연결트리에서는 회전에 관여하는 부트리들의 루트만 재위치시키면 자손 노드들 까지 회전에 참여하게 된다. 하지만 배열로 표현된 n노드의 이진트리를 회전하기 위해서는 해당 노드들의 자손 노드들까지 재배치시켜야 한다. 따라서 n시간이 소요된다.

### 다음 AVL 트리 관련 알고리즘을 의사코드로 작성하라
- searchAndFixAfterInsertion  - $\log{n}$
- searchAndFixAfterRemoval- $\log{n}$
- restructure- $\log{1}$

```
Alg searchAndFixAfterInsertion(w)

1. w.left.height, w.right.height, w.height = 0,0,1
2. if(isRoot(w))
    return
3. z = w.parent
4. while(updateHeight(z)&& isBalanced(z)){
    if(isRoot(z))
        return
    z = parent(z)
}
5. if(isBalanced(z))
    return
6. if(z.left.height > z.right.height)
    y = z.left
   else {z.left.height < z.right.height}
    y=z.right
7. if(y.left.height > y.right.height)
    x = y.left
   else {y.left.height<y.right.height}
    x = y.right
8. restructure(x,y,z)
9. return


Alg searchAndFixAfterRemovel(z)

1. while (updateHeight(z)&& izBalanced(z)){
    if(isRoot(z))
        return
    z = parent(z)
}
2. if(isBalanced(z))
    return
3. if(z.left.height > z.right.height)
    y = z.left
   else {z.left.height < z.right.height}
    y=z.right
4. if(y.left.height > y.right.height)
    x = y.left
   else if (y.left.height<y.right.height)
    x = y.right
   else {y.left.height == y.right.height}{
    if(z.left==y)
        x = y.left
    else {z.right = y}
        x = y.right
   }
5. b = restructure(x,y,z)
6. if (isRoot(b))
    return
7. searchAndFixAfterRemoval(b.parent)


Alg restructure(x,y,z)

1. if(key(z)<key(y)<key(x)){ - 자식으로 가면서 오른쪽으로 밀리는 그래프
    a,b,c = z,y,x - 작은 순서대로 abc
    t0,t1,t2,t3 = a.left,b.left,c.left,c.right - t는 작은 순서대로
}
   else if (key(x)<key(y)<key(z)){ - 왼쪽으로 밀리는 그래프
    a,b,c = x,y,z
    t0,t1,t2,t3 = a.left,a.right,b.right,c.right
   }
   else if (key(z)<key(x)<key(y)){
    a,b,c = z,x,y
    t0,t1,t2,t3 = a.left,b.left,b.right,c.right
   }
   else {key(y)<key(x)<key(z)} {
    a,b,c = y,x,z
    t0,t1,t2,t3 = a.left,b.left,b.right,c.right
   }
2. if (isRoot(z)){   - 가장 위에 b 만들기
    root = b
    b.parent = NULL
}
   else if (z.parent.left = z){
    z.parent.left = b
    b.parent = z.parent
   }
   else {z.parent.left ==z} {
    z.parent.right = b
    b.parent = z.parent
   }
3. a.left, a.right = t0,t1 - a 밑에 완성시키기
4. t0.parent, t1.parent = a
5. updateHeight(a) - a완성시키기
6. c.left, c.right = t2,t3 - c밑에 완성시키기
7. t2.parent, t3.parent = c
8. updateHeight(c)
9. b.left, b.right = a,c - b 밑에 완성시키기
10. a.parent,c.parent = b
11. updateHeight(b)
12. return b


Alg updateHeight(w)

1. h = max(w.left.height, w.right.height) +1
2. if (h!= w.height){
    w.height = h
    return Treu
}
   else
    return False


Alg isBalanced(w)

1. return |w.left.height - w.right.height|<2
```

# 해시테이블
## 해시함수
ex)  
```
h(x) = x%m
```
정수 h(x)를 키 x의 해시값이라 부른다.  
### 해시테이블 구성
- 해시 함수 h
- 크기 m의 배열(해시 테이블이라고 불린다.)
### 압축 맵
#### 나머지셈
$h_2(k) = |k| \% m$  
m은 일반적으로 소수이다.
#### 승합제
$h_2(k) = |ak+ b| \% m$  
a,b는 음이 아닌 정수로서 a % m이 0이 아니어야 한다. 그렇지 않으면 모든 정수가 동일한 수 b로 매핑되기 때문이다.

## 충돌 해결

### 분리 연쇄법
해쉬에 하나만 저장하는 것이 아닌 여러개를 저장하여 리스트로 연결한다.
```
Alg findElement(k)

1. v = h(k)
2. return a[v].findElement(k)


Alg insertItem(k,e)

1. v = h(k)
2. a[v].insertItem(k,e)
3. return


Alg removeElement(k)

1. v = h(k)
2. return a[v].removeElement(k)


Alg initBucketArray()

1. for (i = 0 to M-1)
    a[i] = empty list
2. return
```
### 개방 주소법
개방주소법은 분리연쇄법에 비해 공간사용을 절약하지만 삭제가 어렵다는것과 사전 항목들이 연이어 군집화하는 결점이 있다.

#### 선형조사법
a[(h(k)+f(i))%m], f(i) = i , i = 0,1,2,3,4,5,,,,,  
1차 군집화가 발생할 수 있고, 군집을 순회하는데 많은 시간이 소요된다.
#### 2차 조사법
a[(h(k)+f(i))%m], f(i) = $i^2$ , i = 0,1,2,3,4,5,,,,,  
여기에서도 2차 군집화가 발생할 수 있다. 또한 m이 소수가 아니거나 혹은 버켓 배열이 반 이상이 차면 비어있는 버켓이 남아있더라도 찾지 못할 수도 있다는 단점이 있다.
#### 이중 해싱
a[(h(k)+f(i))%m], f(i) = $i*h'(k)$ , i = 0,1,2,3,4,5,,,,,  
$h'(k) = q - (k \% q)$ 또는 $h'(k) = q + (k \% q)$를 사용한다. p<m이며 p는 소수이다.  
h'(k)와 m은 서로소이다.

### 개방주소법 알고리즘
```
Alg findElement(k)

1. v= h(k)
2. i = 0
3. while(i < m){
    b = getNextBucket(v,i)
    if (isEmpty(A[b]))
        return NoSuchKey
    else if (k == key(A[b]))
        return element(A[b])
    else
        i = i +1
}
4. return NoSuchKey


Alg insertItem(k,e)

1. v = h(k)
2. i = 0
3. while(i<m ){
    b = getNextBucket(v,i)
    if (isEmpty(A[b]))
        Set bucket A[b] to (k,e)
        return
    else
        i = i +1
}
4. overflowException()
5. return


Alg getNextBucket(v,i)

1. return(v+i)%m


Alg getNextBucket(v,i)

1. return (v + i*i) %m


Alg getNextBucket(v,i)

1. return(v + i * h'(k)) % m


Alg initBucketArray()

1. for i = 0 to m-1
    A[i].empty = 1
return


Alg isEmpty(b)

1. return b.empty
```
## 해시테이블 성능
### 적재율
해시테이블의 적재율 $\alpha$ 는 n/m으로 정의된다.  
주요 작업의 효율을 높이려면 적재율을 낮게 유지해야 한다.  
주요 작업의 기대 실행시간은 O($\alpha$)이다.
#### 분리 연쇄법
$\alpha$ > 1 이어도 작동하지만 다소 비효율적이다.  
$\alpha$ <= 1이면 O($\alpha$) = O(1) 기대실행시간이 성취 가능하다.
#### 개방 주소법
항상 $\alpha$ <= 1 이다.
$\alpha$ > 0.5면, 선형 및 2차 조사법인 경우 군집화 가능성이 높으며 이에 따른 성능 저하가 있게 된다.  
$\alpha$<= 0.5로 유지하면 O($\alpha$)= O(1) 기대실행시간에 수행한다.
### 재해싱
- 적재율의 최적치를 초과했을 때
- 삽입이 실패한 때
- 너무 많은 비활성 셀들로 포화되어 성능이 저하되었을 때
#### 재해싱 단계
1. 버캣 배열의 크기를 증가시킨다.(원래 배열의 두강 두배 크기로 - 이때 새 배열의 크기를 소수로 설정하는 것을 잊지 말아야 한다).
2. 새 크기에 대응하도록 압축뱁을 수정.
3. 새 압축맵을 사용하여 기존 해시테이블의 원소들을 새 테이블에 삽입.

## 요약
- 해시테이블은 키-주소 매핑에 의해 구현된 사전 ADT를 말한다.
- 해시테이블은 버켓 배열과 해시함수가 결합되어 정의된다. 버켓 배열은 해시 테이블을 구현한 1차원 배열을 의미하며, 해시함수는 키-주소 매핑을 위한 연산을 수행하는 함수다.
- 해시 함수는 보통 해시 코드 맵과 압축맵 두 함수의 복합체로 명세된다.
- 상이한 두 개의 키가 동일한 해시 테이블 주소로 매핑되면 충돌이 일어났다고 말한다. 충돌 해결을 위한 전략으로는 크게 분리연쇄법과 개방주소법 두 가지가 있다.
- 해시테이블의 적재율 $\alpha$는 n/m으로 정의된다. 다시 말해 적재율은 좋은 해시함수를 사용할 경우 각 버켓의 기대 크기를 말한다. 주요 작업의 효율을 위해 적재율은 낮게 유지되어야 한다.
## 연습문제
### 아래 주어진 키를 해시테이블 A[0..M-1], M =11 에 해시함수  h(k) = (2k + 5)%M 을 사용하여 해싱한 결과를 보여라
- 키(주어진 순서로): 12,44,13,88,23,94,11,39,20,16,5  
충돌이 다음 전략에 의해 해결된다고 가정하고 각각의 경우에 대해 답하라
- 분리 연쇄법 : 리스트
- 선형 조사법 : 옆에 옆에
- 2차 조사법 :a[(h(k)+f(i))%m], f(i) = $i^2$ , i = 0,1,2,3,4,5,,
- 이중해싱,h'(k) = t-(k%7)을 사용하라 : a[(h(k)+f(i))%m], f(i) = $i^2*h'(k)$ , i = 0,1,2,3,4,5,,,,, 
### 아래의 해시테이블을 새로운 해시함수 h(k)= 2k%m 을 사용하여 크기 M = 19의 테이블로 재해싱한 결과를 보여라 13,1,15,28,16,31,7,20,25

### 해시함수$h_A$를 사용하는 크기 $M_A$의 기존 해시테이블 A로부터, 새로운 해시함수 $h_B$를 사용하는 크기 $M_B$의 새로운 해시테이블 B로 재해싱을 수행하는 알고리즘을 의사코드로 작성하라. -분리연쇄법
하나씩 빼서 만들면 되는 것 아닌가...?

```
Alg rehash()

1. for i = 0 to M_A-1
    while(!A[i].isEmpty())
        B.insertItem(key(A[i]),element(A[i]))
2. return
```

### 해시함수$h_A$를 사용하는 크기 $M_A$의 기존 해시테이블 A로부터, 새로운 해시함수 $h_B$를 사용하는 크기 $M_B$의 새로운 해시테이블 B로 재해싱을 수행하는 알고리즘을 의사코드로 작성하라. - 개방주소법

```
Alg rehash()

1. for i = 0 to M_A-1
    if(active(A[i]))
        B.insertItem(key(A[i]),element(A[i]))
2. return
```

### m개의 슬롯, 즉 셀을 가진 개방주소법에 의한 해시테이블에 단 한개의 키 k가 저장되어 있고, 나머지 슬롯은 모두 비어있다. k가 아닌 다양한 키로 해시테이블을 r번 탐색한다고 하자. 홍도는 좋은 해시 함수를 사용한다고 전제하면 r번의 탐색을 수행하는 과정에서 k를 저장한 유일한 슬롯을 조사할 확률은 r/m이라고 주장한다. 홍도의 주장이 옳은지 그른지 논거와 함께 설명하라.

이것도 힙이랑 똑같지 로그로 간디. 제곱해주라 $r^2/m$
> 그르다. 이유는 다음과 같다. 어떤 키에 대한 탐색이 유일한 키 k가 있는 슬롯과 충돌하지 않을 확률은 (1 - 1/m)이다. 따라서 r번의 탐색 가운데 하나라도 유일한 키 k가 있는 슬롯과 충돌할 확률p는, r번의 탐색 모두가 그 슬롯과 충돌하지 않을 확률을 1에서 뺀 것과 같다. 따라서 $p = 1 - (1 - 1/m)^r$

### S를 n개의 정수로 이루어진 집합이라 하자. 윤복은 임의의 정수 x가 S에 속하는지 여부를 O(1) 최악실행시간에 결정하도록 지원하는 데이터구조를 설계할 수 있다고 주장한다. 윤복의 주장이 옳은지 그른지 논거와 함께 설명하라.
메모리를 많이 사용하면 O(1)시간에 가능하다.
> 옳다. 조은 해시함수를 사용하는 해시테이블로 가능하다.

### 정은이는 동적인 집합 S를 유지하며 insertItem, removeElement,member 작업을 각각 O(1) 기대시간에 수행할 수 있는 데이터구조가 있다고 주장한다. 정은이가 옳은지 그른지 논거와 함께 설명하라.
이것도 좋은 해시함수를 사용하는 해시테이블로 가능한거 아니야?
> 옳다. 좋은 해시함수를 사용하는 해시테이블로 가능하다.

### 김찬은 키 수 보다 슬롯 수가 더 많은 해시테이블에서 분리연쇄법으로 해싱을 수행할경우 최악의 탐색시간이 상수시간이라고 주장한다. 김찬의 주장이 옳은지 그른지 논거와 함께 설명하라.
분리연쇄법 = 리스트로 쭉 이어버리기 이다. 즉 좋지 않은 해시함수를 사용하면 한줄로 쭉 이어진 리스트가 만들어질 수 있고 이것은 O(n)시간이 나올 것이다.
> 그르다. 최악의 경우 모든 키가 동일한 슬롯으로 해시될 수 있으며 이에 따른 탐색은 O(n) 시간이 소요된다.

### M = 2r(r >1은 정수)로 전제한다. 해시함수 h(k) = k%M을 사용하여 키 k를 M개의 슬롯 가운데 하나로 매핑한다. 이 해시함수가 좋지 않은 이유를 하나만 대라.
고르게 분포되지 않는다.
> 키가 모두 짝수라면 홀수 슬롯은 전혀 사용하지 않게 된다. 키의 이진수 표현의 낮은 차수의 r 비트만을 취하므로 키의 분포가 r보다 낮은 차수의 비트들은 같고 r 보다 높은 차수의 비트가 상이한 경우 키들이 모두 동일한 슬롯으로 해시되기 때문이다.

# 그래프
## 그래프 ADT
그래프틑 (V,E) 쌍이다.
#### 정점 vertex
#### 간선 edge
### 방향간선과 무방향간선
#### 방향 간선
첫 정점 u 는 시점(orign), 둘째 정점 v는 종점(destination)이고 (u,v)로 이루어져 있다.
## 그래프 주요 개념
### 그래프 용어
- 간선의 끝점(end vertex,end point): 간선의 양쪽 끝에 있는 두 개의 정점들
- 정점의 부착간선(incident edge): 그 정점에 연결된 간선
- 인접정점(adjacent):간선 한개를 사이에 두고 이웃한 정점
- 정점의 차수(degree): 정점에 연결된 간선의 수
- 병렬간선(parallel edges): 양끝점을 공유하는 두 개 이상의 간선(동일한 곳에서 출발해서 동일한 곳에 도착하는 2개 이상의 edge)
- 루프(loop, self-loop): 양끝점이 동일한 간선
- 경로(path): 정점과 간선의 고대열, 경로는 정점으로 시작하여 정점으로 끝난다.
- 단순경로(simple path): 모든 정점과 간선이 유일한 경로(동일 정점, 간선을 지나지 않는다.)
- 싸이클(cycle): 정점과 간선이 교대하는 원형 열
- 단순싸이클(simple cycle): 모든 정점과 간선이 유일한 싸이클
- 단순그래프(simple graph): 싸이클이나 루프가 없는 그래프

### 그래프 속성
- n: 정점 수
- m: 간선 수
- dev(v): 정점 v의 차수
- $\sum_v{deg(v)} = 2m$이다. 즉, 그래프 내 모든 정점의 차수의 합은 간선 수의 2배이다.
> - 증명 : 차수 계산에서 그래프 내 각 간선이 두 번씩 세어지기 때문이다.
- 루프와 병렬간선이 없는 무방향그래프에서 m<= n(n-1)/2다. 즉, 그래프 내 간선 수 m의 상한은 n(n-1)/2이다.
> - 증명 : 각 정점의 최대 차수는 n-1이기 때문이다.

### 그래프 주요 개념
#### 부분집합
그래프 G의 부그래프(subgraph) S는 다음과 같은 그래프이다.
- S의 정점들은 G의 정점들의 부분집합이다.
- S의 간선들은 G읜 간선들의 부분집합이다.  

##### 신장부그래프
G의 신장 부그래프(spanningn subgraph)는 G의 모든 정점을 포함하는 부그래프다.
#### 연결성
- 연결그래프(connected graph): 모든 정점 쌍에 대해 경로가 존재하는 그래프
- 연결요소(connected component): G의 최대 연결 부그래프
#### 밀집도
- 밀집도(density): 그래프 내 간선의 밀집 정도, 즉 정점 수와 비교해 상대적으로 간선이 얼마나 많은지
- 희소 그래프(sparse graph): 간선 수가 적은 그래프
- 밀집 그래프(dense graph): 간선 수가 많은 그래프
- 비연결 그래프(nonconnected graph): 간선이 전혀 없는 그래프
- 완전그래프(complete graph): 모든 정점 쌍 사이에 간선이 존재
#### 싸이클
자유트리 or 트리는 다음 두 조건을 만족하는 무방향 그래프 T를 말한다.
- T는 연열됨
- T에 싸이클이 존재하지 않음  

위의 트리에 대한 정의는 루트트리에 대한 정의와는 다르다.
- 숲: 싸이클이 없은 무방향 그래프이다. 숲의 연결요소는 트리들이다.
#### 신장
연결그래프의 신장트리는 신장 부그래프 가운데 트리인 것을 말한다. 

## 그래프 ADT method
### 일반 method
- integer numVertices(): 그래프 내 정점 수를 반환
- integer numEdges(): 그래프 내 간선 수를 반환
- iterator vertices(): 그래프 내 모든 정점을 반환
- iterator edges(): 그래프 내 모든 간선을 반환
### 접근 method
- vertex aVertex(): 그래프 내 아무 한 정점을 반환
### 질의 method
- boolean isDirected(e): 간선 e가 방향간선인지 여부를 반환
### 반복 method
- iterator directedEdges(): 그래프 내 모든 방향간선을 반환
- iterator undirectedEdges(): 그래프 내 모든 무 방향간선을 반환
### 갱신 method
- vertex insertVertex(o): 항목 o를 저장한 (고립된) 새 정점을 삽입하고 반환
- removeVertes(v): 정점 v와 v의 부착간선을 모두 삭제
- removeEdge(e): 간선 e를 삭제


## 무방향그래프 ADT method
### 일반 method
- integer deg(v): 정점 v의 차수를 반환 
-  vertiex opposite(v,e): 정점 v의 간선 e에 대한 반대쪽 끝점을 반환
### 질의 method
- boolean areAdjacent(v,w): 정점 v와 w가 인접한지 여부를 반환
### 반복 method
- iterator endVertices(e): 간선 e의 양끝 정점들을 반환
- iterator adjacentVertices(v): 정점 v의 인접정점을 모두 반환
- iterator incidentEdges(v): 정점 v의 부착간선을 모두 반환
### 갱신 method
- edge insert(v,w,o): 정점 v와 w 사이에 항목 o를 저장한 무방향간선을 삽입하고 반환

## 그래프 ADT 구현과 성능
간선 리스트 구조, 인접리스트 구조, 인접행렬 구조
|  |  | 인접리스트 |인접 행렬 |
|:-----|-----:|:----:|:----:|
| 연결리스트 | 정점리스트,간선리스트 | 동적 메모리 노드의 연결리스트 | 같다.|
| 연결리스트 | 정점, 간선 | 동적메모리 노드 | 같다|
| 연결리스트 | 인접 정보 | 포인터의 연결리스트 |2D 포인터 배열|
| 연결리스트 | 장점 | 동적 그래프에 사용 시 유리 | 같다|
| 연결리스트 | 단점 | 다수의 푸인터 사용으로 복잡 |같다|
| 배열 | 정점리스트,간선리스트 | 구조체 배열 |같다|
| 배열 | 정점, 간선 | 구조체 | 같다|
| 배열 | 인접 정보 | 첨자의 연결리스트 | 2D 첨자 배열|
| 배열 | 장점 | 다수의 포인터를 첨자로 대체하여 단순 | 같다|
| 배열 | 단점 | 동적 그래프에 사용 시 불리 | 같다 |

| 구현 방식 | 간선 리스트 | 인접 리스트 |인접 행렬 |
|:----:|:-----:|:----:|:----:|
| 기억장소 사용량 | n+m | n+m |$n^2$|
| deg(v) | m | degree if v |n|
| opposite(v,e) | m | 1 |1|
| areAdjacent(v,w) | m | min(deg(v),deg(w)) |1|
| adjacentVertices(v) | m | deg(v) |n|
| incidentEdge(v) | m | deg(v) |n|
| insertVertex(o) | 1 | 1 |n|
| insertEdge(v,w,o) | 1 | 1 |1|
| removeVertex(v) | m |deg(v) |n|
| removeEdge(e) | 1 | 1 |1|

## 요약
- 그래프는 (V,E) 쌍이다. 여기서 V는 정점이라 불리는 노드의 집합이며 E는 간선이라 불리는 정점 쌍들의 집합이다. 각 정점과 간선은 원소를 저장한다.
- 그래프의 간선에는 방향간선과 무방향간선 두 가지 종류가 있다. 방향간선은 정점들의 순서 쌍(u,v)으로 표현되며 두 정점 중 첫 정점 u는 시점을, 둘째 정점 v는 종점을 나타낸다. 무방향간선은 정점들의 무순 쌍(u,v)으로 표현된다.
- 그래프 내 모든 정점의 차수의 합은 간선 수의 2배다. 또한 루프와 병렬간선이 없는 무방향그래프에서 m<=n(n-1)/2다.
- 그래프에서 부분집합, 연결성, 밀집도, 싸이클, 신장 등의 개념은 알고리즘 이해와 작성을 위해 중요하다.
- 그래프 ADT를 컴퓨터에 구현하는 데는 간선리스트 구조, 인접리스트 구조, 그리고 인접행렬 구조를 사용하는 세가지 방식이 있다. 간선리스트 구조는 이 가운데 가장 단순한 구조로써, 여기에 데이터구조를 선택적으로 추가함에 따라 다른 두가지의 실전적인 구현 방식이 파생된다.
## 연습문제
### 무방향그래프와 관련된 method만을 가지며 갱신 메쏘드를 포함하지 않는, 단순화한 그래프 ADT를 그림 13-14(그래프 ADT의 연결리스트 구현)에 보인 것처럼 연결리스트를 사용하여 구현하기 위해 다음 A,B 두 가지 경우 각각에 대해 다음 메쏘드 들을 의사코드로 작성하라.
- integer deg(v): 정점 v의 차수를 반환
- vertex opposite(v,e): 정점 v의 간선 e에 대한 반대쪽 끝점을 반환
- boolean areAdjacent(v,w): 정점 v와 w가 인접한지 여부를 반환
- iterator adjacentVertices(v): 정점 v의 인접정점을 모두 반환
- iterator incidentEdges(v): 정점 v의 부착간선을 모두 반환

#### 그래프가 인접 리스트 구조로 표현됨

```
Alg deg(v)              $O(deg(v))$

1. c= 0
2. e = (v.incidentEdges).next
3. while(e != NULL){
    c++;
    e++;
}
4. return e;


Alg opposite(v,e)           $O(1)$

1. w,v= e.endpoints
2. if (v==u) return w
   else return u


Alg areAdjacent(v,w)   $O(min(deg(v),deg(w)))$

1. if(deg(v)<deg(w))
    m= v
   else
    m=w
2. e = (m.incidentEdges).next
3. while( e!= NULL){
    a,b = e.endpoints
    if((v==a)&&(w==b) || (v==b)&&(w==a))
        return True
    e = e.next
}
4. return False


Alg adjacentVertices(v)        $O(deg(v))$

1. L = empty list
2. e = (v.incidentEdges).next
3. while(e != NULL){
    L.addLast(opposite(v,e))
    e = e.next
}
4. return L.elements()


Alg incidentEndges(v)       $O(deg(v))$

1. L = empty list
2. e = (v.incidentEdges).next
3. while(e!= NULL){
    L.addLast(e)
    e = e.next
}
4. return L.elements()

```


#### 그래프가 인접 행렬 구조로 표현됨

```
Alg deg(v)              $O(n)$

1. c = 0
2. vi = index(v)
3. for j = 0 to n-1
    if(A[vi,j]!= NULL)
        c ++
4. return c


Alg opposite(v,e)           $O(1)$

1. w,v= e.endpoints
2. if (v==u) return w
   else return u


Alg areAdjacent(v,w)   $O(1)$

1. return A[index(v),index(w)]!= NULL


Alg adjacentVertices(v)        $O(n)$

1. L = empty list
2. vi = index(v)
3. for j = 0 to n-1
    if(A[vi,j] != NULL)
        L.addLast(opposite(v,A[vi,j]))
3. return L.elements()


Alg incidentEndges(v)       $O(n)$

1. L = empty list
2. vi = index(v)
3. for j = 0 to n -1
    if(A[vi,j]!=NULL)
        L.addLast(A[vi,j])
4. return L.elements()

```

### 12개의 정점과 18개의 간선으로 이루어지고 3개의 연결요소를 가진 단순 무방향그래프 G를 그려라. 위에서 만약 G가 18개가 아닌 66개의 간선으로 이루어졌다면 G를 그리는 것이 불가능한 이유를 설명하라
4개의 정점을 가진 3개의 연결요소가 각각 22개의 간선을 가지는 것 or 10개의 정점을 가진 1개의 연결요소와 아무와도 연결되지 않은 정점 1개를 가진 2개의 연결요소 일 경우 66개의 간선을 가질 수 없다. 를 논리적으로 설명해야 하는데 흠...
> G가 66개의 간선으로는 이루어질 수 없다. G가 12개의 정점과 3개의 연결요소로 이루어졌다면 G가 가질 수 있는 최대 간선수는 45개이다. 이는 10개의 정점으로(따라서 45개의 간선을 가짐) 이루어진 완건 연결요소와 각각 단일 정점으로 이루어진 두 개의 연결요소로 이루어지 경우다.    

아 최대 간선 수는 n(n-1)/2였다...

### G를 n개의 정점과 m개의 간선으로 이루어진 단순 연결그래프라 하자. 왜 $O(\log{m}) = O(\log{n})$ 인지 설명하라
단순연결그래프면 m<= n(n-1)/2 이기 때문이다.

> m<= n(n-1)/2며 이는 $O(n^2)$이다. 따라서 $O(\log{m}) =O(\log{n^2})=O(2\log{n})= O(\log{n})$

## 심층문제

### n개의 정점과 m개의 간선으로 이루어진 그래프 G를 간선리스트 구조로 표현한다고 가정한다. 이 경우 왜 insertVertex 메쏘드는 $O(1)$시간에 수행되지만 removeVertex 메쏘드는 $O(m)$시간에 수행되는가?
간선을 찾고 만드는데 시간이 오래 걸리기 때문에...? 삽입시에는 만들어서 제일 앞에 넣으면 되기 때문에
- GPT
> insertVertex 메서드 (시간 복잡도: O(1)):
새 정점을 추가하는 작업은 그래프의 간선 리스트 구조에 직접적인 영향을 주지 않습니다. 새 정점이 추가되면, 이 정점의 간선 리스트는 초기에 비어 있으며, 이를 그래프의 정점 배열에 추가하는 것은 단순한 작업입니다.
새 정점을 추가할 때, 기존의 간선 리스트를 수정하거나 탐색할 필요가 없기 때문에, 이 작업은 상수 시간((1)O(1))에 수행됩니다.  
removeVertex 메서드 (시간 복잡도:O(m)):정점을 제거할 때, 그 정점에 연결된 모든 간선을 찾아서 제거해야 합니다. 이는 그래프 내의 다른 모든 정점의 간선 리스트를 확인하고, 제거하려는 정점과 연결된 간선을 찾아서 삭제해야 하는 작업을 포함합니다. 간선 리스트 구조에서 특정 정점과 연결된 모든 간선을 찾기 위해서는 그래프의 모든 간선을 순회해야 할 수 있습니다. 그래프에 총 m개의 간선이 있다면, 최악의 경우 모든 간선을 검사해야 하므로, 이 작업의 시간 복잡도는 O(m)이 됩니다.
각 정점의 간선 리스트에서 해당 정점을 지우는 작업도 포함되어야 하며, 이는 추가적인 시간을 요구할 수 있습니다.  
결론적으로, insertVertex는 단순히 새로운 정점을 추가하는 작업이므로 상수 시간이 소요되지만, removeVertex는 그래프의 모든 간선을 확인하고 수정해야 하기 때문에 시간 복잡도가 O(m)이 됩니다. 이는 간선 리스트 구조에서 간선의 수에 직접적으로 영향을 받는 작업이기 때문입니다.


# 그래프 순회
그래프 내 모든 정점과 간선을 검사함으로써 그래프를 탐험하는 체계적인 절차
## 깊이 우선 탐색 DFS
이진트리의 선위순회와 유사한 양식이다.  
출발 정점에서 시작하여 간선을 따라 정점과 간선들을 방문하는 순서가 선위 순회에서와 마찬가지로 출발 정점에서 멀어지는 외길 방향으로 진행한다. O(n+m)
- G의 모든 정점과 간선을 방문하는 문제
- G가 연결그래프인지 결정하는 문제
- G의 연결요소들을 계산하는 문제
- G의 신장숲을 계산하는 문제

```
Alg DFG(G)

1. for each u ∈ G.vertices()
    l(u) = Fresh
2. for each e ∈ G.edges()
    l(e) = Fresh
3. for each v ∈ G.vertices()
    if(l(v)== Fresh)
        rDFS(G,v)
4. return


Alg rDFS(G,v)

1. l(v) = Visited
2. for each e ∈ G.incidentEdges(v){
    if(l(e) == Fresh){
        w = G.opposite(v,e)
        if(l(w) == Fresh){
            l(e) = Tree - 이 edge는 신장 트리이다.
            rDFS(G,w)
        }
        else
            l(e) = back - 이 edge는 갔던 곳을 간다.
    }
}
3. return
```

### DFS 속성
용감하고 모험적이다.
- rDFS(G,v)는 v의 연결요소 내의 모든 정점과 간선을 방문한다.
- rDPS(G,v)에 의해 Tree로 라벨된 간선들은 v의 연결요소의 신장트리를 형성한다. 이를 깊이우선트리(DFS tree)라고도 한다.

### DFS 성능
정점과 간선의 라벨을 읽고 쓰는 데 O(1) 시간을 소요한다.  

## 너비 우선 탐색 BFS
이진트리에 대한 레벨순회와 유사한 양식으로 순회를 진행한다.  
출발 정점에서 시작하여 간선을 따라 정점과 간선들을 방문하는 순서가 레벨순회에서와 마찬가지로 출발정점에서 레벨단위로 멀어지는 방향으로 진행한다.

```
Alg BFS(G)

1. for each u ∈G.vertices()
    l(u) = Fresh
2. for eace e ∈ G.edges()
    l(e) = Fresh
3. for each v ∈ G.vertices()
    if(l(v)== Fresj)
        BFS1(G,v)
4. return


Alg BFS1(G,v)

1. L0 = empty list
2. L0.addLast(v)
3. l(v) = visited
4. i = 0
5. while(!Li.isEmpty()){
    L(i+1) = empty list
    for each v ∈Li.elements()    - 리스트에 있는 모든 원소들 v로 해서 반복
        for each e ∈ G.insidentEdges(v)    - v의 모든 간선 e로 하기
            if(l(e)==Fresh)     - 이 간선을 간 적이 없다
                w = G.opposite(v.e)   - 이 간선을 통해 나오는 정점
                if(l(w)==Fresh)   - 안갔다
                    l(e) = Tree   -  트리에 추가
                    l(w) = Visited
                    L(i+1).addLast(w) - 다음 리스트에 집어넣는다
                else
                    l(e) = Cross  - 갔으면 아쉬운거지
    i = i +1
}
6. return

```

### BFS 속성
겁이 많은 성격이라 항상 복도 한개 길이 만큼의 실타래만 푼다.
- BFS1(G,v)는 $G_v$의 모든 정점과 간선을 방문한다.
- BFS1(G,v)에 의해 라벨된 트리간선들은 $G_v$의 신장트리 $T_v$를 형성하며 이를 너비우선트리(BFS tree)라고도 한다.
- $L_i$내의 각 정점 w에 대해, $T_v$의 v에서 w로 향하는 경로는 i개의 간선을 가지며 $G_v$내의 v로부터 w로 향하는 모든 경로는 최소 i개의 간선을 가진다.

### BFS 성능
정점과 간선의 라벨을 쓰고 읽는데 O(1)시간 소요한다.  
그래프가 인접리스트로 표현된경우 $\sum_v{deg(v)} = 2m$이므로 명령문 5행은 종합적으로 O(m)시간에 수행한다. 그러므로 그래프가 인접리스트로 표현된 경우에 BFS는 O(n+m) 시간에 수행한다.

## 요약
- 그래프 순회란 그래프 내 모든 정점과 간선을 검사함으로써 그래프를 탐험하는 체계적인 절차를 말한다. 대표적으로 깊이우선탐색과 너비우선 탐색 두 가지가 있다.
- 깊이 우선 탐색은 그래프를 순회하기 위한 일반적 기법이다. 깊이우선탐색은 이진트리에 대한 선위순회와 유사한 양식으로 순회를 진행한다.
- 정점 v를 출발정점으로 한 깊이우선탐색에 의해 방문된 간선들은 v의 연결요소의 신장트리를 형성한다. 이를 깊이우선트리라고도 한다.
- 너비우선탐색은 그래프를 순회하기 위한 일반적인 기법이다. 너비우선탐색은 이진트리에 대한 레벨순회와 유사한 양식으로 순회를 진행한다.
- 정점 v를 출발정점으로 한 너비우선탐색에 의해 방문된 간선들은 v의 연결요소의 신장트리를 형성한다. 이를 너비우선트리라고도 한다.
- 그래프가 인접리스트로 표현된 경우 깊이우선탐색과 너비우선탐색 모두 O(m+n) 시간에 수행한다.

## 연습문제
### 그래프 G의 정점은 1에서 8까지의 정수고 각 정점의 인접정점들은 아래 테이블에 나열된대로다. G를 순회할 때 주어진 정점의 인접정점들이 테이블에 나열된 순서와 동일한 순서로 반환된다고 가정하고 다음에 답해라
| 정점 | 인접정점들 | 
|:----:|:-----:|
| 1 | 2,3,4 |
| 2 | 1,3,4 |
| 3 | 1,2,4 |
| 4 | 1,2,3,6 |
| 5 | 6,7,8 |
| 6 | 4,5,7 |
| 7 | 5,6,8 |
| 8 | 5,7 |
#### 그래프 G를 그려라

#### 정점 1에서 출발하는 DFS순회에서 정점들이 방문되는 순서를 구하라
1 - 2 - 3 - 4 - 6 - 5 - 7 - 8
#### 정점 1에서 출발하는 BFS 순회에서 정점들이 방문되는 순서를 구하라
1 - 2 - 3 - 4 - 6 - 5 - 7 - 8

### 인접행렬 구조로 표현된 n-정점 단순그래프에서 DFS 순회가 $O(n^2)$시간에 수행하는 이유를 설명하여라

모든 정점을 두 번씩 방문하기 때문이다.  
> 정점과 간선의 라벨을 쓰고 읽는데 $O(1)$ 시간이 소요한다. 이는 정점이나 간선을 구현하는 노드가 Fresj, Visited, Tree, Back 등의 값을 저장하는 라벨을 가지도록 각 노드의 데이터구조를 확장하면 가능하다. 각 정점은 두 번 라벨된다. 한 번은 Fresh로, 또 한번은 Visited로 라벨된다. 각 간선 역시 두 번 라벨된다. 한 번은 Fresh로, 또 한 번은 Tree 또는 Back으로 라벨된다. 알고리즘 rDFS에서 수행하는 메쏘드 incidentEdges는 각 정점에 대해 한 번 호출된다. 그래프가 인접행렬로 표현된 경우 한 번 호출에 $O(n)$ 시간을 소요하며 $\sum_v{n} = n^2$이므로 명령문 2행은 총 $O(n^2)$ 시간에 수행한다. 그러므로 그래프가 인접행렬로 표현된 경우 DFS는 $O(n^2)$ 시간에 수행한다.

### 꺽정은 방향그래프 G에 대한 DFS 순회를 수행한 결과로 얻은 DFS 숲에서 동일한 DFS트리 내의 두 정점 a와 b에 대한 방문 시각이 t(a)< t(b) , 즉 a를 b보다 먼저 방문한 것으로 나타났다면 해당 DFS 트리에서 a는 b의 조상임을 의미한다고 주장한다. 꺽정의 주장이 옳은지 그른지 논거와 함께 설명하라.

DFS는 계속 가다가 갈 곳이 없으면 이전의 지나친 길 중에서 안간 길로 다시 가기 시작한다. 그러므로 항상 a가 b의 조상은 아니다. 형제일 경우도 있고, 이모와 같이 v가 더 위일 수 있다.
> 다르다. 이유는 세개의 정점 s,a,b와 두 개의 간선 (s,a),(s,b)만이 존재하는 그래프에서 s를 출발정점으로 하는 DFS순회로 얻은 DFS트리에서 a와 v는 형제(siblings)가 된다. 그러므로 어느 정점도 다른 정점의 조상이 아니다. 

### DFS 순회 알고리즘의 비재귀적 버전을 작성하라
정점에 다른 길이 있었다면 리스트의 마지막에 넣어두고, 갈 길이 없다면 마지막에서 하나씩 빼서 쓴다.

```
Alg DFS1(G,v)

1. S = empty stack
2. S.push(v)
3. while(!S.isEmpty()){
    v = S.pop()
    l(v) = Visted
    for each e ∈ G.incidentEdges(v){
        if(l(e)== Fresh){
            w = G.opposite(v,e)
            if(l(w)==Fresh){
                l(e) = Tree
                S.push(w)
            }
            else
                l(e) = back
        }
    }

}
4. return
```

# 방향 그래프
모든 간선이 방향 간선인 그래프
### 속성과 구현
진입간선(in-edge)와 진출간선(out-edge)들을 별도의 부착리스트로 보관한다면 진입간선의 집합과 진출간선의 집합을 각각의 크기에 비례한 시간에 순회할 수 있다.  
### 방향 DFS 간선(v,w)
- 트리간선 : w가 v의 자식이다.
- 후향간선 : w가 v의 조상이다.
- 전향간선 : w가 v의 자손이다.
- 교차간선 : w가 v와 동일하 레벨 또는 직계가 아닌 다음 레벨에 위치한다.
### 강연결성
정점 u와 v에서 서로 도달 가능하다면 강연결 그래프라고 한다.
#### 강연결 검사
1. G의 임의의 정점 v를 선택
2. G의 v로부터 DFS를 수행
- 방문되지 않은 정점 w가 있다면 False를 반환
3. G의 간선들을 모두 역행시킨 그래프 G'을 얻음
4. G'의 v로부터 DFS를 수행
- 방문되지 않은 정점 w가 있다면 False를 반환
- 그렇지 않으면 True를 반환  
두 번의 DFS를 수행하므로 O(m+n)시간 소요
#### 강연결요소
각 정점으로부터 다른 모든 정점으로 도달할 수 있는 최대의 부 그래프

### 이행적 패쇄

- G*는 G와 동일한 정점들로 구성된다.
- G에 u로부터 v != u로의 방향경로가 존재한다면, G*에 u로부터 v로의 방향간선이 존재한다.  

즉 거쳐서 가는 길이 있다면 한번에 가는 길을 만들어 놓은 것이 G*이다.
#### Floyd-Warshall
그래프의 각 정점에서 DFS를 수행한 결과를 종합하여 보여주므로 O(n(m+n))시간이 소요된다.  
1. 정점들을 1,2,....n으로 번호를 매긴다.
2. 1,2,...,k로 번호 매겨진 정점들만 경유 정점으로 사용하는 경로들을 고려한다.

```
Alg Floyd-Warshall(G)

1.Let v1,v2,...,vn be an arbitrary numbering of the vertices of G
2. G0 = G
3. for k = 1 to n
    Gk = G(k-1)
    for i = 1 to n, i != k
        for j = 1 to n,j != i,k
            if(G(k-1).areAdjacent(vi,vk) && G(k-1).areAdjacent(vk,vj))
                if(!Gk.areAdjacemt(vi,vj))
                    Gk.insertDirectedEdge(vi,vj,k)
4. return Gn
```

## 동적 프로그래밍
- 부문제 단속성 : 부 문제들이 몇개의 기본 변수로 정의될 수 있음
- 부 문제 최적성: 전체 최적치가 최적의 부문제들에 의해 정의될 수 있음.
- 부 문제 중복성: 부 문제들이 독립적이 아니라 상호 겹쳐짐(따라서 해결을 "상향식"으로 구축할 필요가 있음)
### 공통점
문제공간 : 원점 - 목표점 구조
- 원점 : 문제의 초기 또는 기초 지점(복수 개수 가능)
- 목표점 : 최종해가 요구되는 지점(보통 1개)
- 추상적 개념 상의 두 지점
### 차이점
동적 프로그래밍 (단방향): 원점 -> 목표점
분할통치(양방향) : 목표점 -> 원점 -> 목표점
### 성능
- 동적 프로그래밍: 단방향 특성 때문에 종종 효율적
- 분할 통치: 분할 회수, 중복연산 수행 회수

## 방향 비 싸이클 그래프 DAG
싸이클식 참조가 없도록 정의된 그래프
### DAG와 위상 정렬
#### 위상 순서
모든 i < j인 간선(vi,vj)에 대해 정점들을 번호로 나열한 것
- 방향그래프가 DAG면 위상순서를 가지며 그 역도 참이다.  

#### 위상 정렬
DAG로부터 위상순서를 얻는 절차

```
Alg topologicalSort(G)

1. Q = empty queue
2. for each u to G.vertices()
    in(u) = inDegree(u)
    if(in(u)= 0)
        Q.enqueue(u)
3. i = 1
4. while(!Q.isEmpty()){
    u = Q.dequeue()
    Label u with topological number i
    i++
    for each e to G.outIncidentEdges(u){
        w = G.opposite(u,e)
        in(w) = in(w)-1
        if(in(w)= 0)
            Q.enqueue(W)
    }
}
5. if (i <= n)
    write("G has a directed cycle")
6. return
```

1. 0인걸 큐에 다 넣기
2. 0에서 나가는 간선 큐에서 하나 빼서 라벨링하고 반대편 전부 1씩 빼주기
3. 빼줬을 때 0이면 큐에 넣기
4. 무한 반복

```
Alg topologicalSortDFS(G)

1. n = G.numVertices()
2. for each u to G.vertices()
    l(u) = Fresh
3. for each v to G.vertices(){
    if(l(v) = Fresh)
        rTopologicalSortDFS(G,v)
}


Alg rTopologicalSortDFS(G,v)

1. l(v)= Visited
2. for each e to G.outIncidentEdges(v){
    w = opposite(v,e)
    if(l(w) = Fresh)
        rTopologicalSortDFS(G,w)
    else if w is not labeled with a topological number
        write("G has a directed cycle")
    else
        e is a nontree edge
}
3. Label v with topological number b
4. n--
```
1. Fresh 면 계속 가
2. 갈 곳 없으면 라벨 붙여
3. 직전 정점으로 돌아가서 반복

## 요약
- 방향 그래프는 모든 간선이 방향간선인 그래프를 말한다.
- 방향그래프 G의 어느 두 정점 u와 v에 대해서나 u와 v에 도달하며 v는 u에 도달하면 G를 강연결이라고 말한다.
- 동적프로그래밍은 언뜻 보기에 많은 시간이 소요될 것 같은 문제에 주로 적용한다. 적용에 적당한 문제들은 공통적으로 부문제 단순성, 부문제 최적성, 부문제 중복성 등 세 가지 특성을 가진다.
- 방향 비싸이클 그래프는 방향싸이클이 존재하지 않는 방향그래프를 말한다.
- 방향그래프의 위상순서는 모든 i < j 인 간선 $(v_i,v_j)$에 대해 정점들을 번호로 나열한 것을 말한다.
- 위상 정렬은 DAG로부터 위상순서를 얻는 절차를 말한다. 진입차수를 이용하는 방법과 DFS를 특화해서 얻는 방법 등 두가지 방식이 있다.

## 연습문제

### 인경이는 외국어를 좋아하여 다음 아홉개의 언어 과목을 수강할 계획을 세우고자 한다. LA15, LA16(LA15), LA22, LA31(LA15), LA32(LA16,LA31), LA66, LA67, LA71, LA89 각 과목에 대한 선수 과목들은 괄호안에 있다.

그냥 LA15,LA16, LA31순서로 듣고 나머진 맘대로 들으면 되는거 아님?
- ㅇㅈ 답은 무쟈게 많다.

### 피보나치 수열 만들기
- 선형공간으로 수행하는 버전  

이건 배열을 하나 만들어서 쭉 작성해놓기

```
Alg f(n)

1. if(n = 0 || n = 1)   return 1
2. A[0] = 1
3. A[1] = 1
4. for i = 2 to n
    A[i] = A[i-1] + A[i-2]
5. return A[n]
```

- 상수공간으로 수행하는 버전  

이건 와일문 !

```
Alg f(n)

1. if(n = 0 || n = 1)   return 1
2. a = 1
3. b = 1
4. for i = 2 to n{
    c = a+b
    a=b
    b= c
}
5. return c
```

# 최소 신장 트리
## 가중그래프
각 간선이 무게라 불리는 수치값을 가진다.
## 최소 신장 트리
신장 부그래프란 그래프 G의 모든 정점들을 포함하는 부그래프를 말하며 신장트리는 (자유) 트리인 신장 부그래프를 말한다. 가중그래프 G의 최소신장트리MST는 G의 신장트리 가운데 간선 무게의 합이 최소인 것을 말한다.
### 최소 신장 트리의 속성
#### 싸이클 속성
T를 가중그래프 G의 최소신장트리라 하자. e를 T에 존재하지 않는 G의 간선으로 e를 T에 추가하여 형성된 싸이클을 C로 가정하자. 그러면 C의 모든 간선 f에 대해 weight(f)<= weight(e)이다.
- 싸이클에서 가장 큰 숫자를 안써야 최소 신장 트리가 되기 때문이다.
#### 분할 속성
G의 정점들을 두 개의 부분집합 U와 V로 분할한다고 하자. e를 분할을 가로지르는 최소 무게의 간선이라고 하자. 그러면 간선 e를 포함하는 G의 최소신장트리가 반드시 존재한다.
- 분할할 땐 가장 작은 숫자를 써야 최소 신장 트리가 되기 때문이다.
## 탐욕법
- 구성: 다양한 선택, 모음, 또는 찾아야 할 값들
- 목표: 구성에 할당된 점수가 존재하며 이를 최대화 또는 최소화해야 하는 상황
## 최소 신장트리 알고리즘
### prime-Jarnik 알고리즘
임의의 정점 s를 택하여 s로부터 시작하여 정점들을 배낭에 넣어가며 배낭안에서 MST를 키워나가는 것.
- 거리: d(v)
- 위치자: 우선순위 큐에서의 v의 위치
- 부모: p(v), MST T(루트)에서 v의 부모를 향한 간선
- Q.replaceKey(e,k): 원수e의 키를 k로 변경하고 우선순위 큐 Q내의 e의 위치를 갱신
```
Alg Prime-JarnikMST(G)

1. for each v to G.vertices(){
    d(v) = INF
    p(v) = NULL
}
2. s = a vertex of G
3. d(s) = 0
4. Q = a priority queue contaning all the vertices of G using d labels as keys
5. while(!Q.isEmpty){
    u = Q.removeMin()
    for each e to G.incidentEdges(u)
        z = G.opposite(u,e)
        if((z in Q)&(w(u,z)<d(z))){
            d(z) = w(u,z)
            p(z) = e
            Q.replaceKey(z,w(u,z))
        }
}
```

1. 모든 정점의 거리를 무한으로 두고, 부모도 NULL로 둔다.
2. 아무 정점이나 잡아서 그 거리를 0으로 두고 모든 정점들을 큐에 넣는다.
3. 큐에서 가장 작은 값을 꺼내서 거기서 갈 수 있는 모든 정점들 중 큐에 존재하고, 거리가 갱신하는 것 보다 크다면 거리를 새롭게 갱신하고 큐를 재조정한다. (간선 하나의 거리만 생각한다. 처음부터 끝까지 고려하는 것이 아니다.)
4. 큐가 빌때 까지 3번을 반복한다.

#### 알고리즘 분석
incidentEdges는 각 정점에 대해 한번 씩 호출되고, 라벨 관련 작업은 O(deg(z))가 소모된다. Q를 힙으로 구현할 경우 삽입과 삭제는 각각 O(log n)시간이 소요된다. Q 내의 정점 w의 키는 최대 deg(w)번 변경된다. 각 키 변경은 O(log n)시간이 소요된다.
그러므로 알고리즘은 O((n+m)logn) 시간에 수행한다. 단순 연결 그래프에서 n = O(m)이므로 이를 O(mlog n)으로 단순화할 수 있따.

### Kruskal 알고리즘
각 정점을 각각의 배낭으로 두고, 두 배낭을 합칠 때 가장 작은 간선을 선택하는 식으로 키워가는 것이다. G의 정점 수 n보다 하나 작은 수의 간선을 배낭에 포함할 때까지 반복한다. 반복이 완료되면 MST T를 포함하는 한개의 배낭만 남는다.

```
Alg KurskalMST(G)

1. for each v to G.vertices()
    define a Sack(v) = {v}
2. Q = a priority queue contaning all the edges of G using weights as keys
3. T = NULL
4. while(T has fewer than n-1 edges){
    (u,v) = Q.removeMin()
    if(Sack(u)!= Sack(v)){
        Add edge(u,v) to T
        Merge Sack(u) and Sack(v)
    }
}
5. return T
```

1. 모든 정점을 각각의 sack로 둔다.
2. Q에 전부 넣고 T는 NULL로 둔다.
3. Q에서 최소(제일 작은 간선에 연결된 두 정점)를 뽑고 둘이 다른 sack이면 u,v를 T에 추가하고, sack를 합친다.
4. T의 edge가 n-1보다 작은 동안 3을 반복한다.


### BaruvKa 알고리즘

```
Alg BaruvkaMST(G)

1. T = V
2. while( T has fewer than n-1 edges){
    for each connected component Ci in T{
        Let edge e be the smallest-weight edge from Ci to anothor component in T
        if(e is not already in T)
            Add edge e to T
    }
}
3. return T
```

1. 각자 가장 작은 간선을 활용하여 주변 정점과 연결
2. 1번 반복하여 t의 edge가 n-1개가 될 때 까지 진행
### MST 알고리즘 비교

| 알고리즘 | 주요 전략 | 실행시간 |외부 데이터 구조 | 
|:----:|:-----:|:-----:|:-----:|
| PrimeJamik| 탐욕법 | $O(mlogn)$|정점들을 저장하기 위한 우선순위 큐 |
| Kruskal| 탐욕법 | $O(mlogn)$|간선들을 저장하기 위한 우선순위 큐</br> 배낭들을 구현하기 위한 분리집합 |
| PrimeJamik| 탐욕법 | $O(mlogn)$|정점들을 저장하기 위한 우선순위 큐 |

## 요약
- 가중그래프는 그래프 내 간선이 무게 또는 비용이라 부르는 관련 수치값을 가진 그래프를 말한다.
- 최소신장트리는 가중 그래프의 간선 무게의 합이 최소인 신장트리다.
- 최소신장트리의 두 가지 중요한 속성인 싸이클 속성과 분할 속성은 MST 알고리즘의 정확성 검증에 사용된다.
- 탐욕법은 일반적인 알고리즘 설계 기법 가운데 하나다. 중요한 요소로는 다양한 선택으로 된 구성과 최대화 또는 최소화해야 할 목표가 있으며, 탐욕적 속성이 있는 문제에 적용할 경우 잘 맞는다.
- MST를 구하는 Prime-Jarnik, Kruskal, Baruvka 알고리즘은 최악실행시간이 O(mlogn)으로 동일하지만 외부 데이터구조 사용과 접근 방식에 있어서 상이하다.

## 연습문제

### n개의 항목집합 S의 각 항목 i는 양의 이득 bi와 양의 무게 wi로 이루어졌다. 주어진 무게 W를 넘지 않으면서 최대 이득이 되는 S의 부분집합을 계산하는 효율적인 탐욕 알고리즘 Fractional-knapsack(S,W)을 작성하라

```
Alg fractionalKnapsack(S,W)

1. for dach i to S{
    xi = 0
    vi = bi/wi  //무게에 따른 효율
}
2. w = 0  
3. Q = a priority queue contaning all the items of S using vi as keys
4. while (w < W){
    i = Q.removeMin() //왜 remove min인진 모르겠지만 고효율 부터 뽑아서 넣는다.
    xi = min(wi,W-w) // 무게가 넘치면 안쓴다.
    w = w + xi
}
5. return
```

### S = {a,b,c,d,e,f,g}를 다음과 같은 (이득, 무게)를 가진 개체들의 모음이라 하자. a:(12,4), b:(10,6), c:(8,5), d:(11,7), e:(14,3), f:(7,1), g:(9,6)
1. 배낭이 최대 18의 무게를 지탱할 수 있다고 가정하고 부분적 배낭 문제(물체를 조각낼 수 있다 > 가장 효율 좋은 것 순서대로 넣으면 되는 그리드 문제)라는 전제 하에 S에 대한 최적해를 구해라  
- f,e,a,b, 4 of c로 총 무게 18, 총 이득 49.4이다.

2. 이 문제를 0-1 배낭 문제(물건을 분해할 수 없어서 무게를 생각하고 넣어야 된다.)로 전제하고 최적해를 다시 구하라

- f,e,a,b로 총 무게 18, 총 이득 43이다.



# 최단 경로
### 최단 경로 속성
- 최단경로의 부분경로 역시 최단경로다.
출발정점으로부터 다른 모든 정점에 이르는 최단경로들의 트리가 존재한다. 이를 단일점 최단경로라고 부른다.

### 음의 무게를 가지는 간선과 싸이클

가중 방향, 무방향 그래프에 음의 무게를 가진 싸이클이 존재한다면 최단경로는 존재하지 않는다.

| 그래프 | 알고리즘 | 시간 | 
|:----:|:-----:|:-----:|
| 음의 무게를 가진 간선이 없는 그래프| Dijstra | $O(mlogn) or O(n^2)$|
| 음의 무게를 가진 간선이 있는 방향 그래프| bellman-Ford | $O(mn)|
| 비가중그래프| BFS |$O(m+n)$|
| DAG| 위상순서 | $O(m+n)$|

## 최단경로 알고리즘
### Dijkstra

```
Alg DijkstraShortestPaths(G,s)

1. for each v to G.vertices()
    d(v) = INF
2. d(s) = 0
3. Q = a priority queue contaning all the vertices of G using d labels as keys
4. while(!Q.isEmpty()){
    u = Q.removeMin()
    for each e to G.incidentEdges(u){
        z = G.opposite(u,e)
        if(z in Q.elements()){
            if(d(u)+ w(u,z)<d(z)){
                d(Z) = d(u) + w(u,z)
                Q.replaceKey(z,d(z))
            }
        }
    }
}

```

1. 여기서도 거리 다 무한으로 놓고 하나 뽑아서 0으로 두며, Q에 정점 전부 넣는다.
2. Q가 빌때까지 Q에서 가장 작은 값을 꺼내서 모든 인접 정점을 Q에 있는지 확인 후 거리를 계산하고, 거리가 짧으면 거리를 업데이트 후에 Q를 재정렬한다.(간선완화)

## 요약
- 최단경로 문제는 가중그래프와 두 개의 정점 u와 v가 주어졌을 때 u와 v 사이의 무게의 합이 최소인 경로를 구하는 문제를 말한다.
- 출발정점으로부터 다른 모든 정점에 이르는 최단경로들의 트리가 존재한다. 이를 단일점 최단경로라고 부른다.
- 가중 방향그래프에 음의 무게를 가진 싸이클이 존재한다면 최단경로는 존재하지 않는다. 마찬가지로 가중 무방향 그래프에 음의 무게를 가진 간선이 존재해도 최단경로는 존재하지 않는다.
- 최단경로를 찾는 알고리즘은 그래프의 형태에 따라 선택이 달라진다. 즉, 음의 무게를 가진 간선이 있는지 없는지, 무방향인지 방향인지, 그리고 비싸이클(DAG)인지 아닌지에 따라 최적 알고리즘이 따로 존재한다.
- Dijkstra 최단경로 알고리즘은 탐욕법에 기초하며 음의 무게를 가진 간선이 없는 그래프에 적용된다. 음의 무게를 가진 간선이 존재하는 그래프에 적용할 경우 최단경로를 구한다는 보장이 없다.
- 방향 비싸이클 그래프의 경우 Dijkstra나 Bellman-Ford 알고리즘보다 빨리 최단경로를 구하는 알고리즘이 있다. 이 알고리즘은 위상순서를 이용하며 DAG에 음의 무게를 가진 간선이 있더라도 정확히 작동한다.


# 기말 요약

## 퀵 기본 원리

```
1. lt, eq, gt = partition(l,k)
2. quickSort(lt)
3. quickSort(gt)

partition(l,k)
1. p = l.get(k)
2. e = l.removeFirst
3. if (e < p)
    lt.addLast(e)
else if(e==p)
    eq.addLast(e)
else {e>p}
    gt.addLast(e)
4.return lt,eq,gt

inPlacePartition(a,l,r,k)
1. p = a[k]
2. a[k] swap a[r]
3. i = l
4. j = r-1
5. while(i <= j){
    while(i <= j && a[i] <= p)
        i++
    while(j >= i && a[j] >= p)
        j++
    if(i<j )
        a[i] swap a[j]
} 
6. a[i] swap a[r]
7. return i
```

## 탐색트리
### 찾기
1. 외부노드면 반환
2. 키가 같으면 반환, 키가 작으면 오른쪽으로, 키가 크면 왼쪽으로 반환

### 삭제
1. w의 중위순위 계승자 y와 자식노드 z를 찾아낸다.
2. y의 내용을 w에 복사한다.
3. reduceExternal(z) 작업을 사용하여 노드 y와 z를 삭제한다.

### 삽입 후 재조정
1. w에서 루트 향해 올라가다가 처음 만나는 불균형 노드를 z
2. 거기서 w로 가는 방향으로 y, x 두기.
3. restruct(x,y,z)

### 삭제 후 재조정
삽입 후 재조정에서 위로 올라가서 계속 고친다.
### restructure
1. x,y,z 중위 순회 방문순서(크기순서) a,b,c라 둔다.
2. 그 밑의 부트리들을 중위 순회 방문순서(크기 순서) t0, t1, t2, t3로 둔다.
3. z를 루트로 하는 부트리를 b를 루트로 하는 부트리로 대체한다.
4. b의 왼쪽 자식a, 오른쪽 자식 c로 두고, t0,t1,t2,t3를 각각 달아준다.

## 그래프

| 구현 방식 | 간선 리스트 | 인접 리스트 |인접 행렬 |
|:----:|:-----:|:----:|:----:|
| 기억장소 사용량 | n+m | n+m |$n^2$|
| deg(v) | m | degree if v |n|
| opposite(v,e) | m | 1 |1|
| areAdjacent(v,w) | m | min(deg(v),deg(w)) |1|
| adjacentVertices(v) | m | deg(v) |n|
| incidentEdge(v) | m | deg(v) |n|
| insertVertex(o) | 1 | 1 |n|
| insertEdge(v,w,o) | 1 | 1 |1|
| removeVertex(v) | m |deg(v) |n|
| removeEdge(e) | 1 | 1 |1|


### 그래프가 인접 리스트 구조로 표현됨

```
Alg deg(v)              $O(deg(v))$

1. c= 0
2. e = (v.incidentEdges).next
3. while(e != NULL){
    c++;
    e++;
}
4. return e;


Alg opposite(v,e)           $O(1)$

1. w,v= e.endpoints
2. if (v==u) return w
   else return u


Alg areAdjacent(v,w)   $O(min(deg(v),deg(w)))$

1. if(deg(v)<deg(w))
    m= v
   else
    m=w
2. e = (m.incidentEdges).next
3. while( e!= NULL){
    a,b = e.endpoints
    if((v==a)&&(w==b) || (v==b)&&(w==a))
        return True
    e = e.next
}
4. return False


Alg adjacentVertices(v)        $O(deg(v))$

1. L = empty list
2. e = (v.incidentEdges).next
3. while(e != NULL){
    L.addLast(opposite(v,e))
    e = e.next
}
4. return L.elements()


Alg incidentEndges(v)       $O(deg(v))$

1. L = empty list
2. e = (v.incidentEdges).next
3. while(e!= NULL){
    L.addLast(e)
    e = e.next
}
4. return L.elements()

```


### 그래프가 인접 행렬 구조로 표현됨

```
Alg deg(v)              $O(n)$

1. c = 0
2. vi = index(v)
3. for j = 0 to n-1
    if(A[vi,j]!= NULL)
        c ++
4. return c


Alg opposite(v,e)           $O(1)$

1. w,v= e.endpoints
2. if (v==u) return w
   else return u


Alg areAdjacent(v,w)   $O(1)$

1. return A[index(v),index(w)]!= NULL


Alg adjacentVertices(v)        $O(n)$

1. L = empty list
2. vi = index(v)
3. for j = 0 to n-1
    if(A[vi,j] != NULL)
        L.addLast(opposite(v,A[vi,j]))
3. return L.elements()


Alg incidentEndges(v)       $O(n)$

1. L = empty list
2. vi = index(v)
3. for j = 0 to n -1
    if(A[vi,j]!=NULL)
        L.addLast(A[vi,j])
4. return L.elements()

```

## 그래프 순회
- DFS

> Fresh가 있으면 계속 간다. 없으면 이전으로 돌아가서 Fresh 찾기 반복  
O(n + m)시간  
깊이 우선 신장트리를 형성  
연결요소 내의 모든 정점과 간선을 방문한다.  

- BFS

> 리스트에 집어넣으면서 흩어지기  
너비 우선 트리를 형성한다.  
O(n+m)시간  

## 방향그래프 (v,w)
- 트리간선 : w가 v의 자식이다.
- 후향간선 : w가 v의 조상이다.
- 전향간선 : w가 v의 자손이다.
- 교차간선 : w와 v가 형제이거나 부모가 다르다.
- 강연결 : u->v도 가능, v->u도 가능
- 이행적 폐쇄 : 거쳐서 가는건 한번에!

### DAG
- 위상순서 : 정점들을 번호로 나열한 것
- 위상정렬 : DAG로부터 위상순서를 얻는 절차

1. 모든 정점에 들어오는 간선을 카운트 해줘서 0인 것들을 Q에 넣는다.
2. 큐에서 하나씩 빼서 i만큼 라벨해주고, 그 정점에서 나가는 간선이 들어가는 정점의 카운트를 한개씩 빼준다. 
3. 그 정점의 카운트가 0이라면 큐에 넣어준다.

- DFSDAG는 Fresh면 계속 가다가 갈 곳 없으면 라벨붙이고 돌아오기~

## 최소신장트리
- 신장 부그래프 : 모든 정점을 포함하는 부 그래프
- 신장트리 : 트리인 신장 부그래프
- 최소 신장 트리 : 신장트리 가운데 간선 무게의 합이 최소인 것
- 분할 속성 : 분할할 땐 가장 작은 숫자를 써야 된다.
- 싸이클 속성 : 싸이클에선 가장 큰 숫자를 안써야 최소 신장 트리가 된다.

### 잔돈 거스르기
- 탐욕법 : 제일 큰 동전으로 거슬러 준다.(32,8,1원인 경우)
- 탐욕 X : 30,20,5,1인 경우

### 부분적 배낭 문제 - 물건의 일부만 취해도 된다.
- 탐욕법 사용 O

### 0-1 배낭문제 - 물건 전체를 취해야 한다.
- 탐욕법 사용 X

### prime-Jarnik
- 임의의 정점 s를 택하여 s로부터 시작하여 d(v)가 가장 작은 정점들을 배낭에서 빼면서 다른 배낭안에서 MST를 키워나가는 것.
- O(mlogn)

### Kruskal
- 각각의 정점이 sack을 가지고 있다가 Q에서 가장 작은 간선을 꺼내고, 그 간선의 양쪽 정점이 다른 sack인 경우 그 둘을 합친다.

### Baruvka
- 각자 가장 작은 간선을 활용하여 주변 정점과 연결, 반복


| 알고리즘 | 주요 전략 | 실행시간 |외부 데이터 구조 | 
|:----:|:-----:|:-----:|:-----:|
| PrimeJamik| 탐욕법 | $O(mlogn)$|정점들을 저장하기 위한 우선순위 큐 |
| Kruskal| 탐욕법 | $O(mlogn)$|간선들을 저장하기 위한 우선순위 큐</br> 배낭들을 구현하기 위한 분리집합 |
| Baruvka| 탐욕법 | $O(mlogn)$|정점들을 저장하기 위한 우선순위 큐 |

## 최단경로
- 출발 정점으로부터 다른 모든 정점에 이르는 최단경로들의 트리

### Dijkstra
- 하나 빼고 거리를 전부다 INF로 두고 Q에서 가장 작은 것만 빼서 거리를 계산 후, 그 계산한 값이 원래 값보다 작으면 갱신, 반복