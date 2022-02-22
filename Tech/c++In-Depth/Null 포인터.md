## Null 포인터

***

<br>

### :pushpin: C++ 11 이전 NULL

컴파일러가 NULL을 포인터가 아닌 정수 0과 동일하게 여긴다.

C에서, T 매크로 ```NULL```은 null pointer 상수로 정의되는데, C99에서 간편하게 정수 값 ```0```으로 표현되며, 암묵적 또는 명시적으로 타입 ```void*```으로 변환된다.

null pointer 역참조는 일반적으로 매핑되지 않은 메모리(세그먼테이션 오류 또는 접근 위반 유발)를 읽거나 쓰려는 시도를 초래하였고, 개발자들에게 스스로 프로그램 충돌을 의미하거나 잡힐 수 있는 예외로 변형되었다.

그러나 이것이 불가능한 환경이 존재하는데 x86 모드에서, 주소 0000:0000은 읽을 수 있고, 보통 사용할 수 있으므로 널 포인터를 역참조하는 것이 가능했지만 원치 않은 행동으로 이어진다.

또한 컴파일러가 세그멘테이션 오류를 피하기 위해 NULL 포인터 역참조를 최적화하지만 다른 의도되지 않은 행위를 유발할 가능성이 있다.



```컴파일러가 NULL을 포인터가 아니라 정수 0과 동일하게 여긴다.```

이는 switch 문에 NULL인 값을 넣으면 정수 0에 매칭되어 0에 대한 로그가 캡처된다.

```c++
void ServiceClass::nullPtrTest(char *test){
    int a = NULL;
    
    switch(a){
        case 0:
            cout<<"null log"<<endl; break;
    }
}
```



<br>

### :pushpin: C++ 11 이후 NULL(type_traits 헤더에 정의)

C++에서는 ```NULL``` 매크로를 C로부터 상속받았지만, 0을 위한 정수 리터럴이 전통적으로 널 포인터 상수를 표현하는 것보다 더 선호되고 있다.

```int *ptr = 0;```과 같이..

하지만 C++ 11은 명시적 ```nullptr``` 상수를 도입해서 이것 대신 사용되도록 하였다.

C++ 11부터 만들어진 nullptr 타입은 ```<cstddef>``` 헤더에 있는 std::nullptr_t 타입이다.

해당 std::nullptr_t 타입은 모든 타입의 포인터로 암시적 형 변환이 가능하다.

```c++
int *ptr1 = nullptr;
char *ptr2 = nullptr;
double *ptr3 = nullptr;
void (*func1)(int, int) = nullptr;
void (*func2)() = nullptr;
```

위 코드처럼 모든 타입의 포인터를 초기화할 수 있다.

<br>

### :pushpin: Null pointer

유효한 객체를 참조하지 않는 포인터를 나타내기 위해 예약된 값을 갖는다.

NULL은 포인터로 0 주소라고 정의할 수 있으며 ```(void *)0```의 형식으로 정의되어 있다.

일반적으로 0 주소부터 0xFFFF 까지는 예약되어 있는 주소로, Null pointer는 사용할 수 없으며 일반적으로 접근할 수 없는 메모리 영역이다.

<br>

### :pushpin: C++ NULL 매크로

```c++
#ifndef NULL
	#ifndef __cplusplus
		#define NULL 0
	#else
		#define NULL ((void *)0)
	#endif
#endif
```

C++에서는 NULL을 0으로 사용하고, C++ 이 아닌 C에서는 NULL을 ```((void *)0)```으로 치환해서 사용하겠다는 의미

:point_right: NULL은 Null pointer가 아니라 정수 0이었다.

진짜 포인터를 표현할 수 있는 ```nullptr```을 사용해야 한다.

<br>

### :pushpin: 따라서 nullptr을 사용해야 하는 이유

아래 코드는 C++98에서 작동 안할 수 있는 포인터 오버로딩의 예시이다.

```c++
void f(int);
void f(bool);
void f(void*);

f(0); // f(void*)를 부르기 원했다해도 f(int)가 불린다, 0은 정수이기 때문
f(NULL); // f(void*)를 부르기 원했다해도 어떤 일이 일어날지 모른다.
```

```NULL```은 포인터가 아니라 매크로에서 정의된 상수 0이기 때문에 컴파일러는 정수 값 0을 넣는 것으로 인식한다.

:point_right: 개발자의 의도와는 다른 함수가 호출될 가능성이 존재한다.

즉 포인터가 사용되는 곳에서 0과 NULL을 포인터로 해석할 뿐 실제 동작에서는 포인터로 동작하지 않는다.



```nullptr```은 어떤 하나의 포인터가 아니라 모든 클래스의 포인터다.

어떤 타입의 값과 포인터를 명확히 구분해야 할 때에는 포인터에 ```NULL```보다는 ```nullptr```을 사용하는 것이 좋다.

:point_right: 컴파일러가 타입 추론에 혼란을 겪지 않도록 하려면 ```nullptr```을 사용해야 한다.

위의 코드에서 ```f(nullptr)```을 호출할 경우 ```f(void*)```가 호출된다.

<br>

### :pushpin: type_traits의 is_null_pointer

```<type_traits>``` 헤더를 포함하면 is_null_pointer라는 템플릿 클래스를 사용할 수 있다.

해당 클래스의 멤버로는 ```value```가 있는데, ```is_null_pointer```로 검사한 값이 ```nullptr```이라면 true를, 그렇지 않다면 false를 ```value```가 갖는다.



가능한 구현으로는

```c++
template <typename T>
struct is_null_pointer : std::is_same<std::nullptr_t, std::remove_cv-t<T>>{ };
```

이 있는데, 템플릿 인자로 전달된 타입이 ```nullptr``` 타입인지 확인하는 코드이다.



참고로

```nullptr```은 ```std::is_pointer```가 아니다, 내장 포인터 타입이 아니기 때문이다.

단지 0주소를 가리키는 포인터일 뿐이지 일반적인 포인터가 아니다.

```c++
#include <iostream>
#include <type_traits>
int main(){
    std::cout<<std::boolalpha
        << std::is_null_pointer< decltype(nullptr) >::value<<' ' // true, nullptr은 nullptr이 맞음
        << std::is_null_pointer< int* >::value<<' '	// false, int*은 nullptr이 아님
        << std::is_pointer< decltype(nullptr) >::value<<' ' // false, nullptr은 포인터가 아님
        << std::is_pointer< int* >::value<<' ' // true, int*는 포인터
}
```

