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

### :pushpin: C++ 11 이후 NULL

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

