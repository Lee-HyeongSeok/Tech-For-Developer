## type_traits 라이브러리

***

<br>

### :pushpin: 템플릿 메타 함수

사실 함수는 아니지만 마치 함수 처럼 동작하는 템플릿 클래스들

:point_right: 보통의 함수들은 값에 대해 연산을 수행하지만, 메타 함수는 **타입에 대해 연산**을 수행한다.



예를 들어

함수일 경우, 음수인지 아닌지 판별하는 함수 ```is_negative```가 있다고 하자

```c++
if(is_negative(x)){ ... }
```

예를 들어

템플릿 메타 함수일 경우, 어떤 타입이 ```void```인지 아닌지 판단하는 ```is_void``` 함수가 있다고 하자

```c++
if(is_void<T>::value)
```



실제 void 구분 템플릿 메타 함수

```c++
#include <type_traits>
template <class T>
    struct is_void : std::is_same<void, typename std::remove_cv<T>::type>{};

int main(){
    std::cout<<std::boolalpha;
    std::cout<<std::is_void<void>::value<<'\n'; // true
    std::cout<<std::is_void<int>::value<<'\n'; // false
}
```



템플릿 메타 함수 예제

```c++
template <iostream>
template <type_traits>

template <typename T>
void tell_type(){
    if(std::is_void<T>::value){
        std::cout<<"T는 void";
    }
    else{
        std::cout<<"T는 void가 아니다";
    }
}
int main(){
    tell_type<int>(); // void가 아님
    tell_type<void>(); // void!
}
```



### :pushpin: 템플릿 메타 프로그래밍에서 ```if```문은 템플릿 특수화를 통해서 구현된다.

```c++
#include <iostream>

template <typename T>
struct is_void{ // 일반적인 모든 타입 T에 매칭되는 부분
    static constexpr bool value=false;
};

template <typename T>
struct is_void<void>{ // 템플릿 특수화를 통해 모든 타입중 void일 경우에만 매칭되는 부분
    static constexpr bool value=true;
};

template <typename T>
void tell_type(){
    if(is_void<T>::value){
        std::cout<<"T is void";
    }
    else{
        std::cout<<"T is not void";
    }
}

int main(){
    tell_type<int>(); // not void
    tell_type<void>(); // void
}
```



