## C++ In-Depth Coding rules(class 44)

***

<br>

### :pushpin: Pimpl을 적절히 활용하라

- C++의 사영(private) 멤버는 접근이 어렵게 되어 있지만, 숨겨져 있는 것은 아니다.
- 적절한 이득을 취할 수 있는 상황이라면 Pimpl을 사용하여 **컴파일러 방화벽**을 만들고, 사영 멤버를 감추어 정보를 숨기는 것이 좋다.

<br>



### :pushpin: 컴파일러 방화벽을 만들어 호출 코드를 클래스의 private 부분과 분리해야 할 필요가 있을 때는 Pimpl을 사용하라

- 포인터(선언되었으나 정의되지는 않은 클래스로의 스마트 포인터가 적당하다) 뒤로 정보를 숨기는 것이다.

```c++
class Map{
private:
    struct Impl;
    std::shared_ptr<Impl> pimpl_;
}
```

- Pimpl은 멤버 데이터와 사영 멤버 함수를 모두 저장하는 데 사용 가능
- 이를 통해 호출 코드를 재 컴파일하지 않고도 클래스의 사영 임플리먼테이션을 변경 가능
- 즉 독립성과 자유가 보장되는 것

<br>



### :pushpin: 주의할 점

```c++
class Map{
private:
    struct Impl;
    std::shared_ptr<Impl> pimpl_;
    
    // struct Impl* pimpl_;이 적절함
}
```

과 같이 두 개의 선언으로 Pimpl을 사용하는 것은 좋지 않다.

```struct Impl* pimpl```과 같은 방식으로 두 라인을 결합하여 타입을 선언하고 포인터를 지정하는 것이 네임스페이스와 타입의 구조상 적절하다.



<br>

### :pushpin: Pimpl이 유용한 이유 - 1

C++이 가진 접근성(무언가를 호출, 사용할 수 있는지의 여부)과 가시성(내용 확인, 그 정의에 의존 가능한지의 여부) 사이의 분리 특성과 밀접한 관련이 있다. **특히 클래스의 모든 사영 멤버가 외부의 멤버 함수에서 접근이 불가능하지만, 모든 코드에서 클래스의 정의를 확인할 수 있다는 특징이 중요**

<br>

:point_right: 이러한 특징의 결과

불필요한 타입 정의의 처리로 인한 상대적으로 긴 빌드 타임으로 나타남

이는 사영 데이터 멤버와 사영 멤버 함수 인자에 대한 타입이 컴파일에 필요하지 않더라도 반드시 정의되어야 하기 때문

```c++
class C{
private:
    AcomplicatedType act_;
}
```

클래스 C의 정의를 담고 있는 헤더 파일은 반드시 AcomplicatedType에 대한 정의를 담고 있는 헤더를 \#include 해야 하므로, AcomplicatedType이 필요로 하는 모든 헤더가 첨가될 것이다.

:point_right: 헤더가 크다면 컴파일 시간을 증가 시킨다.

<br>

### :pushpin: Pimpl이 유용한 이유 - 2

함수를 호출하는 코드에 대한 이름 조회 때문이다.

사영 멤버 함수가 클래스 외부에서 절대 호출될 일이 없는 상황이라 해도 이름 조회에는 포함되며, 결과적으로 호출 자체를 애매하게 만드는 요인이 된다.

- C++은 접근성 검사 이전에 이름 조회를 진행
- 가시성이 더 높은 우선순위를 가지는 것

```c++
int Twice(int);

class Calc{
public:
    std::string Twice(std::string);
private:
    char* Twice(char*);
    
    int Test(){
        return Twice(21);
    }
};

Calc c;
c.Twice("Hello");
```

위에서 ```int Test(){ return Twice(21); }``` 부분을 보면 전역 함수를 선택하도록 되었으며, ```c.Twice("Hello");``` 를 통해 의도된 함수를 선택되도록 오버로드하였다(Pimpl 외에도 이런 문제를 해결하는 방법은 있다).

멤버 함수에 대한 사영 오버로드를 아예 쓰지않으면 되긴 한다.

<br>



### :pushpin: Pimpl이 유용한 이유 - 3

오류 처리와 안전에 미치는 영향 때문이다.

```c++
class Widget{
public:
    Widget& operator=(const Widget&);
private:
    T1 t1_;
    T2 t2_;
};
```

T1이나 T2 작업 중 하나라도 실패할 경우 ```operator=``` 작업의 성공을 장담할 수 없다.

하지만 아래와 같은 간단한 변환을 거치면 적어도 오류는 발생하지 않는 할당이 가능하며, T1과 T2 작업에 대한 부작용을 피할 수 있다.

**멤버 객체는 값이 아닌 포인터를 통해, 하나의 Pimpl 포인터를 통해 홀딩하는 것이 좋다.**

```c++
class Widget{
public:
    Widget& operator=(const Widget&);
private:
    struct Impl;
    std::shared_ptr<Impl> pimpl_;
};

Widget& Widget::operator=(const Widget&){
    // temp->t1, temp->t2로 변경, 성공 여부에 따라 사용
    std::shared_ptr<Impl> temp(new Impl(t1 또는 t2));
    
    pimpl_ = temp;
    return *this;
}
```



<br>



### :pushpin: 예외

간접 방식을 사용하는 것이 이득이 됨을 확신할 때는 Pimpl 사용이 오히려 복잡성을 증가 시킨다.