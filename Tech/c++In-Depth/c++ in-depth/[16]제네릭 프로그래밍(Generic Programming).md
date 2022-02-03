## 제네릭 프로그래밍(Generic Programming)

***

<br>

### :pushpin: 표준 템플릿 라이브러리(Standard Template Library; STL)

:point_right: 두 가지 요소로 구성되어 있다.

1. **컨테이너(Container) 클래스의 모음**

   - 벡터, 리스트, 셋, 맵 등

   - **구성**

     - 순차 컨테이너(sequential container) : 벡터, 리스트 등

       > [1] 첫 번째, 두 번째와 같은 식으로 계속해 마지막 요소까지 유지
       >
       > [2] 주로 반복(iteration)을 수행

     - 연관 컨테이너(associative container) : 맵, 셋 등

       > 값을 빨리 참조할 수 있다.

2. **컨테이너에 대한 연산을 수행하는 제네릭 알고리즘의 모음**

   - find(), sort(), replace(), merge() 등

<br>

### :pushpin: 연관 컨테이너(associative container)

- **맵(map)**

  1. 키(key)와 값(value) 한 벌로 구성되어 있다.
  2. 키는 참조에 이용
  3. 값은 저장과 인출에 쓰이는 데이터를 나타냄

- **셋(set)**

  1. 오직 키값만 저장, 그 값이 존재하는지에 대해 질의하게 된다.

     > ex) 뉴스에서 나오는 단어들의 인덱스를 구성하려고 할 때
     >
     > [1] the, a, but 등의 중요하지 않은 의미의 단어들을 배제하려고 한다.
     >
     > [2] 단어를 인덱스로 만들기 전에 excluded_word(배제될 단어들) 셋에 질의한다.
     >
     > [3] 단어가 그 셋(set)에 존재하면 무시, 그렇지 않으면 단어를 인덱스에 추가

<br>

### :pushpin: 제네릭 알고리즘(= 포괄 알고리즘)

- 컨테이너 클래스와 기본 배열 모두에 적용할 수 있는 많은 수의 연산들을 제공한다.
- 알고리즘은 연산이 수행될 요소들의 타입(int, double, string 등)과 요소가 저장되는 컨테이너의 타입(벡터, 리스트, 기본 배열 등)에 대해 독립적이기 때문에 알고리즘이 포괄적이라고 말한다.
  - :point_right: 함수 템플릿으로 구현되어 있어서 **타입에 대해** 이러한 독립성을 가질 수 있다.
  - :point_right: 컨테이너를 직접 조작하지 않으므로 **컨테이너에 대해**서도 독립성을 갖게 된다.

<br>

### :pushpin: 포인터의 계산(Arithmetic)

- [1] 정수 벡터와 정수값이 주어진다, 벡터에 그 정수값이 저장되어 있으면 그것을 가리키는 포인터를 반환하고 그렇지 않으면 존재하지 않는 값을 가리키는 의미로 0을 반환

  > ```c++
  > int* find(const vector<int> &vec, int value){
  >     for(int ix=0; ix<vec.size(); ++ix){
  >         if(vec[ix] == value)
  >             return &vec[ix];
  >     }
  >     return 0;
  > }
  > ```

- [2] 상등 연산자(==)가 적용될 수 있는 모든 타입에 대해 동작하도록 만드는 과정

> ```c++
> template <typename elemType>
> elemType* find(const vector<elemType> &vec, const elemType &value){
>     for(int ix=0; ix<vec.size(); ++ix){
>         if(vec[ix] == value)
>             return &vec[ix];
>     }
>     return 0;
> }
> ```

- [3] find() 가 벡터는 물론, 상등 연산자가 정의된 모든 타입의 요소에 대한 배열에서도 잘 동작하게 만드는 것

  - **벡터를 취하는 경우, 배열을 취하는 경우를 각각 제공하여 함수를 오버로딩하는 방법?**

    - :point_right: 오버로딩을 권장하지 않는다.

  -  **하나의 인스턴스가 벡터의 요소와 기본 배열의 요소를 모두 처리할 수 있도록 find() 구현**

    - :point_right: 어렵다.

  - **여러 개의 작고 단순한 문제들로 나누는 것**

    - :point_right: 배열임을 명시하지 않고 find()에 배열의 요소를 넘긴다.
    - :point_right: 벡터임을 명시하지 않고 find()에 벡터의 요소를 넘긴다.
    - **이 두 문제를 풀 수 있는 해결책이 존재**

  - **기본 배열의 문제점**

    - :point_right: 어떻게 배열이라는 명시가 없이 배열의 요소를 find()로 전달할 수 있을까?

      > ```c++
      > int min(int array[24]){ ... }
      > ```
      >
      > - min()은 24개 요소의 배열만을 받고, 실제 배열은 값에 의해 전달되는 것으로 보인다.
      >
      > - 그러나 배열은 값에 의해 복사되는 것이 아니다.
      >
      > - 어떤 크기의 배열이라도 min()으로 넘길 수 있다.
      >
      >   :point_right: 배열이 전달되거나 반환될 때 배열의 첫 요소의 주소만 넘겨진다.
      >
      > <br>
      >
      > 
      >
      > ```c++
      > // min()의 정확한 선언
      > // min()은 어떤 크기의 정수 배열도 받아들인다.
      > int min(int *array){ ... } 
      > ```

    - :point_right: 배열을 읽는 것을 멈춰야 할 때 어떤 식으로든 min()에게 알려야 한다.

      1. 배열의 크기를 갖는 매개변수를 추가하는 방법

         > ```c++
         > template <typename elemType>
         > elemType* find(const elemType* array, int size, const elemType& value);
         > ```

      2. 더 이상 배열 요소를 읽어들이지 않을 주소를 넘기는 방법**(이러한 값을 흐름제어용 경계값(sentinel)이라 부른다)**

         > ```c++
         > template <typename elemType>
         > elemType* find(const elemType* first, const elemType* sentinel, const elemType &value);
         > ```

<br>

### :pushpin: find()를 구현하는 방법

1. 0부터 시작하여 size-1까지 차례로 요소에 접근하는 방법

   > ```c++
   > template <typename elemType>
   > elemType* find(const elemType *array, int size, const elemType &value){
   >     if(!array || size < 1)
   >         return 0;
   >     for(int ix=0; ix<size; ++ix){
   >         if(array[ix] == value)
   >             return &array[ix];
   >     }
   >     return 0; // 값이 발견되지 않음
   > }
   > ```
   >
   > :point_right: find()의 첫 매개변수에 배열을 포인터로 넘겨도 배열 처럼 개개인의 요소에 접근 가능
   >
   > - 실제 첨자는 요소의 주소를 얻기 위해 배열의 시작 주소에 인덱스를 더한다(array+ix의 형태)
   >
   > - 그리고 요소의 값을 반환하기 위해 그 주소를 역참조한다.
   >
   >   > array[2];는 *(array+2)와 같으며,
   >   >
   >   > array의 첫 요소의 주소가 1000이라면 array+2의 주소는 1000+(2*4byte)이므로 1008이다.

2. 배열의 요소를 차례로 가리키기 위해 루프를 돌면서 1만큼을 더하는 방법

   > ```c++
   > template <typename elemType>
   > elemType* find(const elemType* array, int size, const elemType& value){
   >     if(!array || size < 1)
   >         return 0;
   >     for(int ix=0; ix<size; ++ix, ++array)
   >         if(*array == value)
   >             return array;
   >     return 0;
   > }
   > ```

3. 두 번째 매개변수인 size를 흐름제어용 경계값(sentinel) 주소를 가리키는 또다른 포인터로 대체하는 방법

   > ```c++
   > template <typename elemType>
   > elemType* find(const elemType* first, const elemType* last, const elemType& value){
   >     if(!first || !last)
   >         return 0;
   >     // first와 last가 서로 다를 동안 first가 가리키는 요소의 값과 value를 비교
   >     // 두 개가 같다면 first를 반환, 그렇지 않으면 first가 다음 요소를 가리키도록 증가시킴
   >     for(; first != last; ++first)
   >         if(*first == value)
   >             return first;
   >     return 0;
   > }
   > 
   > // find의 호출
   > int main(void){
   >     int *pi = find(ia, ia+8, ia[3]);
   >     double *pd = find(da, da+6, da[3]);
   > }
   > ```
   >
   > :point_right: 벡터도 인접하여 연속된 메모리 영역에 요소가 저장된다.
   >
   > - 배열에서 했던 것과 같은 방법으로 find()에 처음과 마지막 주소를 넘길 수 있다.
   >
   > - 하지만 배열과 달리, 벡터는 비어 있을 수 있다.
   >
   >   > ```c++
   >   > vector<string> svec;
   >   > ```
   >   >
   >   > 위는 빈 문자열 요소의 벡터를 정의
   >   >
   >   > svec이 비어 있다면 다음의 find() 호출은 정확하지 않고, 실행 중에 프로그램의 실패를 초래한다.
   >   >
   >   > ```c++
   >   > find(&svec[0], &svec[svec.size()], search_value);
   >   > ```
   >   >
   >   > 보다 안전한 구현은 svec이 비어 있지 않음을 먼저 확인하는 것
   >   >
   >   > ```c++
   >   > if(!svec.empty()) // ...ok, find()를 호출해도 됨
   >   > ```
   >   >
   >   > 이것이 더 안전하지만, 이 연산을 함수로 만드는 것이 첫 요소의 주소를 접근하는 보다 일관적인 방법이 된다.
   >   >
   >   > ```c++
   >   > template <typename elemType>
   >   > inline elemType* begin(const vector<elemType> &vec){
   >   >     return vec.empty() ? 0 : &vec[0]; // 비어 있다면 0, 그렇지 않다면 첫 번째 요소의 주소를 반환
   >   > }
   >   > ```
   >   >
   >   > 위 연산자를 통해 안전하게 find()를 호출 가능
   >   >
   >   > ```c++
   >   > find(begin(svec), end(svec), search_value);
   >   > ```

<br>

### :pushpin: 순차 컨테이너(sequential container)

- 벡터(vector)

  - 인접하여 연속된 메모리 영역에 요소가 저장된다.

- 리스트(list)

  - 리스트의 요소는 한 쌍의 포인터에 의해 서로 연결되어 있다.

    > **한 쌍의 포인터 : 다음 요소를 가리키는 정방향 포인터, 이전의 요소를 가리키는 역방향 포인터**

  - 리스트에서 포인터의 계산은 동작하지 않는다(요소가 인접하게 연속적이라는 가정하에 동작하기 때문)

    > **포인터의 계산 : array[2] == array+2**

<br>

### :pushpin: 리스트를 위한 find() 함수?

> 포인터의 계산을 사용하지 못하는 리스트를 위해 새로운 인스턴스의 find()를 만들고 오버로딩해서 리스트 객체만을 받아들이는 방법(X) 
>
> :point_right: 기본 포인터의 동작에 추상화 계층(layer of abstraction)을 제공하는 것이 해결책

- 기본 포인터들을 직접적으로 다루지 않고 추상화 계층을 만든다.

- 사용자로부터 보호된 **그 계층** 내에서 각각의 기본 포인터를 개개의 경우에 맞게 처리한다.

  :point_right: **이런 기법 때문에 어떤 STL의 컨테이너 클래스도 하나의 find() 인스턴스로 처리 가능**

<br>

### :pushpin: 반복자(Iterator)의 이해

> 기본 포인터들을 직접적으로 다루지 않고 **추상화 계층**을 만든다.
>
> 이러한 추상화 계층을 어떻게 구현하는가?

- 기본 포인터의 연산자(++, --, \*=, !=)와 동일한 연산자들을 지원하는 객체가 필요

- 그 연산자들의 구현은 고유하게 제공되는데, C++의 클래스 메커니즘을 통해 이를 실현한다.

- 포인터와 동일한 구문을 사용해 프로그램된 반복자(iterator)라는 클래스의 모음 설계 가능

- first와 last가 리스트 클래스의 반복자일 경우

  > ```c++
  > while(first != last){
  >     cout<<*first<<' ';
  >     ++fisrt;
  > }
  > ```
  >
  > fisrt와 last는 포인터처럼 사용되었다.
  >
  > 차이점
  >
  > :point_right: 역참조 연산자(\*), 부등 연산자(!=), 증가 연산자(++)가 반복자 클래스와 관련된 인라인(inline) 함수의 호출을 나타낸다는 점

- 리스트 클래스의 반복자를 예로 든다면,

  - 증가 함수 : 정방향(following) 리스트 포인터에 의해 다음 요소로 위치시킨다.

    > 벡터 클래스에서의 증가 함수는 현재 주소에서 하나의 요소 크기만큼을 더해 다음 요소로 위치시킴

<br>

### :pushpin: 반복자를 어디서 얻어오는가?

> **각 컨테이너 클래스는 첫 요소의 주소를 반환하는 begin() 연산과 컨테이너의 마지막보다 1이 큰 요소의 주소를 반환하는 end() 연산을 제공**
>
> ```c++
> for(iter = svec.begin(); iter != svec.end(); ++iter){
>     cout<<*iter<<' ';
> }
> ```
>
> 반복자(iter)들은 대입, 비교, 증가, 역참조 가능

<br>

### :pushpin: 반복자 선언

- 문자열 요소의 벡터에 대한 반복자 정의

  > ```c++
  > vector<string> svec;
  > vector<string>::iterator iter = svec.begin(); // svec의 첫 요소를 가리키도록 초기화
  > ```

- const 벡터에 대해 반복자 정의

  > ```c++
  > const vector<string> cs_vec;
  > vector<string>::const_iterator = cs_vec.begin(); // const_iterator를 사용
  > ```
  >
  > **const_iterator는 벡터의 요소를 읽을 수만 있고, 쓸 수는 없다.**

<br>

### :pushpin: 반복자를 통한 요소 접근

- 기본 포인터에서처럼 역참조하기만 하면 된다.

  > ```c++
  > cout<<"string value of element : "<<*iter;
  > ```

- 컨테이너의 기본 타입에 대한 연산을 호출하기 위해서는 멤버 선택 화살표 구문을 사용한다.

  > ```c++
  > vector<string> svec;
  > vector<string>::iterator = svec.begin();
  > 
  > cout<<iter->size()<<' '<<*iter;
  > ```

<br>

### :pushpin: 특정 타입의 컨테이너에 대해 기본 포인터와 반복자를 모두 지원하도록 함수 정의

```c++
template <typename IteratorType, typename elemType>
IteratorType find(IteratorType first, IteratorType last, const elemType &value){
    for(; first != last; ++first){
        if(value == *first)
            return first;
    }
    return last; // 찾는 값이 없을 경우
}

// find()를 사용하는 부분
int main(void){
	const int asize=8;
    int ia[size] = {1, 1, 2, 3, 5, 8, 13, 21};
    
    // 리스트와 벡터를 ia의 8개 요소로 초기화
    vector<int> ivec(ia, ia+asize); 
    list<int> ilist(ia, ia+asize);
    
    int *pia = find(ia, ia+asize, 1024);
    if(pia != ia+asize){
        cout<<"find"<<endl;
    }
    
    vector<int>::iterator it;
    it = find(ivec.begin(), ivec.end(), 1024);
    if(it != ivec.end()){
        cout<<"find"<<endl;
    }
    
    list<int>::iterator iter;
    iter = find(ilist.begin(), ilist.end(), 1024);
    if(iter != ilist.end()){
        cout<<"find"<<endl;
    }
}
```

- 현재 find()의 구현은 기본 요소 타입의 상등 연산자(==)를 사용한다.
- 사용자가 상등 연산자를 다르게 정의하길 원한다면?
  1. 상등 연산자를 사용하지 않고, 함수의 포인터와 같이 함수를 넘기는 것
  2. 함수 객체(function object)라는 특별한 클래스를 구현하는 것