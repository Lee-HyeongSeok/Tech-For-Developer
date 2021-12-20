## :round_pushpin: 알고리즘

***

<br>

### :pushpin: 알고리즘(Algorithm) 이란?

- 문제를 해결하기 위한 여러 동작들의 모임

<br> 

### :pushpin: 알고리즘 종류

- **재귀 함수(Recursive Call)**
- **정렬(Sorting)**
  - 선택 정렬
  - 버블 정렬
  - 퀵 정렬
  - 삽입 정렬
  - 쉘 정렬
  - 힙 정렬
  - 병합 정렬
  - 기수 정렬
- **탐색(Searching)**
  - 선형 탐색
  - 이진 탐색
  - 레드 블랙 트리
- **해시(Hash)**
  - 해시 테이블
- **그래프(Graph)**
  - 그래프 순회 알고리즘
    - DFS(깊이 우선 탐색)
    - BFS(넓이 우선 탐색)
  - 최소 신장 트리(MST)
    - 크루스 칼 알고리즘
    - 프라임 알고리즘
  - 최단 경로 알고리즘
    - 다익스트라
- **문자열 검색(String Matching)**

<br> 

### :pushpin: 알고리즘 설계 기법

- **분할 정복(Divide and Conquer)**
- **동적 계획법(Dynamic Programming)**
- **탐욕 알고리즘(Greedy Algorithm)**
- **퇴각 탐색(Backtracking)**

<br>

### :pushpin: 재귀 함수(Recursive Call)

- 자신을 정의할 때 자기 자신을 재참조하는 방법, 이를 프로그래밍에 적용한 것

```c
int Fibonacci(int n){
    if(n == 0) return 0;
    if(n == 1 || n == 2) return 1;
    else return Fibonacci(n-1)+Fibonacci(n-2);
}
```

<br>

### :pushpin: 정렬

- **선택 정렬**

  - 주어진 리스트 중에 최소값을 찾아, 그 값을 맨 앞에 위치한 값과 교체한다.
  - 맨 처음 위치를 뺀 나머지 리스트를 같은 방법으로 교체한다.
  - **최악의 경우** : O(n^2), **최선의 경우** : O(n)

  ```c
  #define SWAP(a, b){int t=a; a=b; b=t;}
  void selectionSort(int *list, const int n){
      int i, j, indexMin;
      
      for(i=0; i<n-1; i++){
          indexMin=i;
          for(j=i+1; j<n; j++){
              if(list[j] < list[indexMin]) indexMin=j;
          }
          SWAP(list[indexMin], list[i]);
      }
  }
  ```

  <br>

- **버블 정렬**

  - 서로 인접한 두 원소를 검사하여 정렬하는 알고리즘
  - **최악의 경우** : O(n^2), **최선의 경우** : O(n)

  ```c
  #define SWAP(a, b){int t=a; a=b; b=t;}
  void bubbleSort(int *list, const int n){
      int i, j;
      for(i=n-1; i>0; i--){
          for(j=0; j<i; j++){
              if(list[j] > list[j+1]) SWAP(list[j], list[j+1]);
          }
      }
  }
  ```

  <br>

- **퀵 정렬**

  - 분할 정복 방법을 통해 리스트를 정렬
    - 리스트 가운데서 하나의 원소를 선택, 이를 피벗(Pivot)이라 함
    - 피벗 앞에는 피벗보다 값이 작은 원소들, 뒤에는 큰 원소들이 배치되도록 리스트를 둘로 나눔
    - 분할된 두 리스트에 대해 재귀적으로 이 과정을 반복, 재귀는 리스트의 크기가 0이나 1이될 때까지 반복
  - 퀵 정렬의 내부 루프는 **컴퓨터 아키텍처에서 효율적으로 작동하도록 설계됨**
    - 메모리 참조가 지역화되어 있기 때문에 **CPU 캐시의 히트율**이 높아짐
  - **최악의 경우** : O(n^2), **최선의 경우** : O(n log n)

  ```c
  #define SWAP(a, b){int t=a; a=b; b=t;}
  void quickSort(int *list, int left, int right){
      int i=left, j=right;
      int pivot = list[(left+right)/2]; // 중간 값
      // 피벗보다 작은 원소, 큰 원소를 배치하는 부분
      do{
          while(list[i] < pivot) // 인덱스 0부터 pivot보다 작은값이 존재하면 i++
              i++;
          while(list[j] > pivot) // 인덱스 n부터 pivot보다 큰 값이 존재하면 j--
              j--;
          if(i <= j){
              SWAP(list[i], list[j]);
              i++;
              j--;
          }
      }while(i <= j);
      // 분할된 두 리스트에 대해 재귀적으로 위에 do~while 과정을 반복
      if(left < j) quickSort(list, left, j);
      if(i < right) quickSort(list, i, right);
  }
  ```

  <br>

- **힙 정렬**

  - **최대 힙 트리** 또는 **최소 힙 트리**를 구성해 정렬하는 방법
    - **최대 힙** : 내림 차순 정렬, 부모 노드가 자식 노드보다 큰 힙
    - **최소 힙** : 오름 차순 정렬, 부모 노드가 자식 노드보다 작은 힙
  - **알고리즘**
    - [1] n개 노드에 대한 완전 이진 트리 구성
    - [2] 최대 힙 또는 최소 힙 구성
    - [3] 한번에 하나씩 요소를 힙에서 꺼내어 배열의 뒤부터 저장
  - **최악의 경우** : O(n log n), **최선의 경우** : O(n log n)

  ```c
  void downheap(int cur, int k)
  {
    int left, right, p;
      while(cur < k) {
        left = cur * 2 + 1;
        right = cur * 2 + 2;
  
        if (left >= k && right >= k) break;
  
        p = cur;
        if (left < k && data[p] < data[left]) {
          p = left;
        }
        if (right < k && data[p] < data[right]) {
          p = right;
        }
        if (p == cur) break;
  
        swap(&data[cur],&data[p]);
        cur=p;
      }
  }
  
  void heapify(int n)
  {
    int i,p;
    for(i = (n-1)/2; i >= 0; i--){
      downheap(i,n);
    }
    //for(i=0;i<size;++i)printf("%d ",data[i]);
    //printf("\n");
  }
  
  void heap()
  {
    int k;
    heapify(size);
    for(k = size-1; k > 0; ){
      swap(&data[0],&data[k]);
      //k--;
      downheap(0,k);
      k--;
    }
  }
  ```

  <br>

### :pushpin: 탐색

- **선형 탐색**

  - 선형적 자료를 순차적으로 탐색하는 알고리즘
  - 선형적 자료의 크기가 커질수록 시간이 오래 걸린다.
  - **최악의 경우** : O(n), **최선의 경우** : O(1)

  ```c
  int linearSearch(int *list, int find_The_Value_Of_X){
      for(int i=0; i<list.size(); i++){
          if(find_The_Value_Of_X == list[i]) return i;
      }
      return -1; // 찾는 값이 없음
  }
  ```

  <br>

- **이진 탐색**

  - 오름차순으로 정렬된 배열에서 특정 값의 위치를 찾는 알고리즘
  - 처음 중간의 값을 임의의 값으로 선택, 그 값과 찾고자 하는 값의 크고 작음을 비교하는 방식 사용
  - **알고리즘**
    - 처음 선택한 중앙 값이 찾는 값보다 크면, 그 값은 새로운 최대값이 됨
    - 처음 선택한 중앙 값이 찾는 값보다 작으면, 그 값은 새로운 최솟값이 됨

  ```c
  // loop version : A[0 ~ N-1]
  int binarySearch(int A[], int low, int high, int target){
      while(low <= high){
          int mid = (low + high) / 2;
          if(A[mid] == target) return mid;
          if(A[mid] > target) high = mid - 1;
          else low = mid + 1;
      }
      return -1;
  }
  ```

  <br>

- **레드 블랙 트리**

  - 자가 균형 이진 탐색 트리
  - 이진 트리의 특수한 형태
  - 모든 노드에 대해 자신이 가진 자료는 자신보다 오른쪽에 위치한 부분 트리가 가진 모든 자료보다 작거나 같고, 자신보다 왼쪽에 위치한 부분 트리가 가진 모든 자료보다 크거나 같은 조건을 만족하고 있다.
  - 삽입과 삭제, 검색에서 최악의 경우에도 일정한 실행 시간을 보장

