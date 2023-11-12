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