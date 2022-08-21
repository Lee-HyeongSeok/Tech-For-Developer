## C++ In-Depth Coding rules(class 46)

***

<br>

### :pushpin: new와 delete는 항상 함께 제공하라

- 오버로드된 ```void* operator new(인자)```는 항상 오버로드된 ```void operator delete(void*, 인자)```와 함께 사용되어야 한다.
  - 여기서 인자는 인자 타입의 목록을 말하며, 배열 형식인 ```new[]```와 ```delete[]```에서도 마찬가지 이다.

<br>

### :pushpin: new와 delete를 오버로드 할 때, 반드시 양쪽 모두 제공해야 한다.

> 호출할 일이 없다고 해도 컴파일러가 new에 해당하는 delete를 원하기 때문이다.

아래 커스텀화된 할당 방식으로 새로운 클래스를 정의한다고 가정한다.

```c++
class T{
    static void* operator new(std::size_t);
    static void* operator new(std::size_t, CustomAllocator&);
    static void operator delete(void*, std::size_t);
};
```

- 호출자는 표준 할당자(new T 사용)나 커스텀 할당자(new(alloc) T 사용)을 통해 T 타입의 객체를 할당할 수 있다.
  - 여기서 alloc은 CustomAllocator 타입의 객체
- 호출자가 호출할 수 있는 operator delete 방식은 표준적인 operator delete(size_t) 밖에 없으므로 이를 통해 적절한 해지가 이루어지게끔 구현해야 한다.

<br>

여기까지는 별다른 문제가 없지만,

호출할 필요가 없다고 해도 컴파일러는 delete의 오버로드된 버전의 ```T::operator delete(size_t, CustomAllocator&)```를 필요로 한다.

만약 ```T* p = new(alloc) T;``` 와 같은 구문이 있다면 아래와 같이 확장되기 때문이다.

```c++
void* __compilerTemp = T::operator new(sizeof(T), alloc);

T* p;
try{
    p = new (__compilerTemp) T;
}
catch(...){
    T::operator delete(__compilerTemp, sizeof(T), alloc);
    throw;
}
```

- 할당 성공 시, 컴파일러는 오버로드된 ```T::operator new```에 맞는 적절한 ```T::operator delete``` 호출을 위해 자동으로 코드를 추가하지만, 결과적으로 생성자는 실패한다.

<br>

C++은 오버로드된 ```operator delete```가 있을 때만 코드가 만들어지도록 되어 있으며, 그렇지 않으면 컨스트럭터가 실패했을 때 ```operator delete```를 호출하지 않도록 하고 있다.

-  생성자 실패 시
  - 메모리상의 손해가 발생

<br>



### :pushpin: 결론

> ```void* operator new(params)```의 오버로드가 있다면 ```void operator delete(void*, params)```의 오버로드 또한 있어야 한다.

