## C++ In-Depth Coding rules(class 47)

***

<br>

### :pushpin: 특정한 클래스에 맞는 new를 제공한다면 모든 표준 형식을 제공해야 한다.

- 오버로드된 operator new를 정의할 경우
- 평범한 형식
- 내부 형식
- nothrow 형식의 세 가지 표준 형식
- 을 함께 오버로드하여 제공해야 한다. 그렇지 않으면 클래스의 사용자로부터 숨겨져 사용될 수 없다.

<br>

### :pushpin: new와 delete를 오버라이드 하는 경우

- 그에 적절한 형식을 모두 오버로드하여 제공해야 한다.

<br>



### :pushpin: C++에서 특정 범위(ex. 클래스 범위) 내에 이름을 정의하게 되면 내부에 포함된 모든 범위 내의 같은 이름이 덮어 쓰여지며, 범위 밖에 있는 이름에 대해서는 오버로딩이 발생하지 않는다.

```c++
class C{
    static void *operator new(size_t, MemoryPool&); // 세 가지 일반적인 형식이 숨겨짐
};
```

위와 같이 정의하면 지정된 형식 이외에 우리가 흔히 사용하는 세 가지 다른 형식은 사용할 수 없게 된다.

MemoryPool 인자를 가지는 C::operator new 오버로드가 다음과 같이 보편적으로 사용되는 다른 세 가지 오버로드를 숨기기 때문

```c++
void* operator new(std::size_t); // 평범한 new
void* operator new(std::size_t, std::nothrow_t) throw(); // nothrow new
void* operator new(std::size_t, void*); // 내부 new
```

사용자가 지정한 클래스에서 세 가지 new 중 한 가지 버전을 제공하는 경우에는 이를 제외한 나머지 두 형식이 숨겨진다.

```c++
class C{
    static void* operator new(size_t, void*); // 다른 두 가지 형식이 숨겨진다.
}
```

- 물론 세 가지 일반적인 형식 모두 사용할 수 있는 범위로 클래스를 만드는 것이 가장 좋다.

  - 각 형식에 대한 사용 여부를 별도로 지정 가능

- 내부 new 형식의 경우는 STL 컨테이너가 활용하는 경우가 많으므로 항상 사용 가능하게 만들어야 한다.

- 이미 숨겨진 new를 노출시키는 방식이 상황에 따라 두 가지로 나뉜다.

  - 만약 클래스의 기반 클래스에 이미 operator new가 정의되어 있다면 다음과 같이 하면 된다.

    - 

    ```c++
    class C			
        : public B{
            public:
            using B::operator new;
    };	
    ```

  - 만약 기반 클래스가 없거나 기반 클래스에서 operator new가 정의되어 있지 않으면 다음과 같이 간략한 포워딩 함수를 작성하면 된다. 이는 전역 namespace에서 이름을 가져오는 데 using을 사용할 수 없기 때문이다.

    - ```c++
      class C{
      public:
          static void* operator new(std::size_t s){
              return ::operator new(s);
          }
          static void* operator new(std::size_t s, std::nothrow_t nt) throw(){
              return ::operator new(s, nt);
          }
          static void* operator new(std::size_t s, void* p){
              return ::operator new(s, p);
          }
      };
      ```

    - 