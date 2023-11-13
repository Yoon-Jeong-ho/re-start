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
2. a[k] = a[r]
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

| |size ,isEmpty|insertItem, removeMin|
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
||순서사전|일람표|이진 탐색|
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
    z = rightChild
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