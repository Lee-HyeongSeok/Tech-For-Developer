## Memory 헤더의 allocator class

***

<br>

### :pushpin: memory header, allocator\<T> 클래스

- 유연한 메모리 관리를 위한 클래스로 **할당자**라고도 한다.
- 주로 표준 라이브러리의 컨테이너를 구현할 때 많이 사용된다.
- find-grained(특정 프로세스 및 서비스를 잘게 쪼개는 것) 방식, 메모리 관리를 좀 더 세밀하게 다루고 효율적으로 사용해야 할 경우에 개발자가 원하는 메모리 할당 방식으로 구현 가능
- allocator class를 상속받아 멤버 함수를 오버라이딩하여 커스텀할 수 있다.

<br>

### :pushpin: Container와 new/delete의 문제

- **컨테이너**는 **데이터를 저장하고 관리하는 공간**으로 저장 공간의 생성, 삭제, 확장, 추가 등이 빈번히 발생하기 때문에 메모리를 최대한 효율적으로 관리할 수 있어야 함

- new/delete 연산자는 다루는 데이터가 클래스라는 전제에서 아래와 같은 조건이 필요하기 때문에 비효율적

  > **[1] 기본 생성자 필요**
  >
  > **[2] 메모리할당**
  >
  > **[3] 모든 요소 초기화**

- 컨테이너가 다루는 요소가 증가할 수록 컴퓨터 자원의 사용량이 상당히 증가

- 추가적으로 new 연산자는 개발자가 원하는 메모리 할당 방식으로 커스터마이징 불가

- **하지만**

  - allocator class를 사용하면 위 3가지 단계들을 각각 원할 때 사용 가능

<br>

### :pushpin: vector container와 allocator class

> **보통 vector를 사용할 때 타입 매개변수로 하나만을 전달**
>
> **사실 vector는 기본 타입 매개변수로 allocator를 사용하고 있었다.**

```c++
template <class _Ty, class _Alloc = allocator<_Ty>> // 유연한 메모리 사용과 관리를 위한 allocator
class vector{
    
}
```

<br>

#### allocator의 장점

> 메모리를 동적 할당 할 경우 초기화 되지 않은 공간으로 할당할 수 있다.
>
> 즉, **초기화 되지 않은 상태의 메모리 시작 주소를 얻을 수 있다.**

- new 연산자의 경우 메모리 할당 후 기본 값 또는 객체를 의무적으로 초기화한다.
- 이는 요소가 많을 수록 오버헤드가 증가하며 초기화를 원치 않을 경우에도 불필요한 오버헤드 발생

> 할당받은 메모리에 객체를 생성 후 메모리 해제없이 **소멸**시킬 수 있다.
>
> 즉, **메모리의 재할당 없이 그 공간을 초기 상태로 만들 수 있다.**

<br>

#### allocator class

```c++
template <class T>
class allocator{
    public:
    	T* allocate(size_t); // 초기화되지 않은 메모리 공간을 할당하여 시작 주소를 반환하는 함수
    	void deallocate(T*, size_t);
    	void construct(T*, const T&);
    	void destroy(T*);
    ...
};

template <class ln, class For>
For uninitialized_copy(ln, ln, For);

template <class For, class T>
void uninitialized_fill(For, For, const T&);
```

- **T* allocate(size_t)**

  - 인자로 생성할 T 객체의 개수(n)를 받는다.

  - 인자로 전달받은 개수만큼 메모리 공간을 할당하는 함수

  - 인자로 전달된 개수만큼 T type의 객체를 **충분히** 할당할 수 있는 공간을 생성 후 시작 주소 반환

    > **타입 크기 * 인자로 전달된 개수 + 4byte**
    >
    > **ex) 8byte 타입의 객체를 5개 생성**
    >
    > **(8bytes * 5) + 4bytes = 44bytes**

- **void deallocate(T*, size_t)**

  - allocate() 함수로 할당했던 메모리 공간을 해제하는 함수
  - 인자로 **T type 포인터**와 **개수**를 받는다.
    - 포인터 : allocate()로 할당했던 메모리의 시작 주소를 가리키는 포인터
    - 개수 : allocate()로 전달했던 개수
    - **cppreference에서는 allocate()로 전달했던 개수와 동일해야 한다고 말함**

- **void construct(T*, const T&)**

  - 초기화 되지 않은 공간에 요소를 저장하는 함수
  - T type 포인터와 객체를 인자로 전달 받으며, 포인터가 가리키는 위치에 객체를 저장
  - 초기화 되지 않은 공간에 \*(간접 참조)연산자를 사용하여 값을 대입할 경우 에러 발생
    - **하지만 이 함수를 통해 에러 없이 저장 가능**

- **void destroy(T*)**

  - 객체를 소멸시키는 함수
  - T type 포인터가 가리키는 위치에 존재하는 객체의 소멸자를 호출
  - destroy()를 호출하지 않고 deallocate()을 호출할 경우
    - 각 요소에 저장된 객체는 소멸되지만, 사라진 객체가 가리키던 객체들은 그대로 메모리에 남아있어 **메모리 누수(memory leak)**가 발생 가능하다.

- ```c++
  template <class ln, class For>
  For uninitialized_copy(ln, ln, For);
  ```

  - **입력 반복자 2개(First, last)**와 **순방향 반복자 1개(out)**을 인자로 전달 받는다.

  - [first, last) 범위의 요소들을 out이 가르키는 위치에 순서대로 복사한다.

  - 이후 복사가 완료된 위치의 다음 요소를 가리키는 포인터를 반환

    > **ex) 1~5위치에 복사 완료 시에 6위치를 가리키는 포인터를 반환**

- ```c++
  template <class For, class T>
  void uninitialized_fill(For, For, const T&);
  ```

  - 주어진 범위의 공간을 3번째 인자로 주어진 값으로 채운다.

    >  **[first, last) 범위의 모든 요소에 const T&로 주어진 값으로 채운다.**

