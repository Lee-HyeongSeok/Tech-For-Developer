## C++ In-Depth Coding rules(class 41)

***

<br>

### :pushpin: 간접 변환을 피하라

- 간접 변환은 좋은 측면보다 나쁜 측면이 더 많다.
- 따라서 개발자가 정의하는 타입에 대한 간접 변환을 허용하기 전에 두 번 생각해보고, 가능하다면 직접 변환(직접 생성자와 변환 함수)를 사용하자.

<br>

### :pushpin: 간접 변환이 가지는 두 가지 문제점

1. 예상치 못한 곳에서 이루어진다.
   - 간접 변환의 생성자는 오버로딩과의 상호작용이 안정적이지 못하다.
   - 여기저기 등장하는 임시객체에서 보여지지 않는다.
   - operator T 형식의 멤버 함수로 정의된 변환 역시 간접 생성자와의 상호작용뿐만 아니라, 잘못된 코드의 컴파일을 그대로 허용한다는 점에 있어서 결코 좋지 않은 방식이다.
2. 코드의 다른 부분과 항상 융합되지는 못한다.

<br>


### :pushpin: 예시

사용자 정의 변환은 하나 정도이지만, 기본 변환 방식이라 해도 여러 가지가 결합될 경우에는 혼란스러워질 수 있다. 해결 방법은 다음과 같다.

- 표준적으로 하나의 인자를 가진 생성자에는 ```explicit```을 사용한다.

- ```c++
  class Widget{
      // explicit 키워드는 자신이 원치 않는 형변환이 일어나지 않도록 제한하는 키워드이다.
      explicit Widget(unsigned int widgetizationFactor);
      explicit Widget(const char* name, const Widget* other=0);
  };
  ```

- 변환 연산자 대신 변환을 수행하는 함수를 사용한다.

- ```c++
  class String{
      const char* as_char_pointer() const;
  };
  ```

<br>

오버로딩의 경우, 간접적으로 호출될 수 있는 ```Widget::Widget(unsigned int)```가 있고, Widget과 double에 대한 오버로드된 display 함수가 있다고 가정하자.

```c++
void Display(double); // double 출력
void Display(const Widget&); // Widget 출력
Display(5); // Widget을 임시생성하고 출력
```

<br>

오류가 있음에도 그대로 진행하는 경우, String 클래스에 대한 operator const char*를 만들었다고 가정하자.

```c++
class String{
    public:
    operator const char*();
};
```

이제 말도 안 되는 여러 가지 표현식들이 오류 없이 컴파일되어 버린다.

```c++
int x = s1-s2;  // 예측할 수 없는 결과로 컴파일 됨
const char* p = s1-5; // 예측할 수 없는 결과로 컴파일 됨
p = s1+'0'; // 기대와는 다른 결과로 컴파일 됨

if(s1 == '0'){ ... }
```

<br>



### :pushpin: 예외

조심스럽게 사용한다면 간접 변환으로 인해 호출 코드를 보다 짧고 직관적으로 만들 수 있다.

표준 std::string은 const char*를 받아들이는 간접 생성자를 정의하는데, 다음과 같은 몇 가지 부분에 세밀한 주의를 기울였기 때문에 괜찮다.

- const char*에 대한 자동 변환이 일어나지 않는다.
  - c_str과 data라는 두 함수를 통해서만 변환이 일어난다.
- std::string에 정의된 모든 비교 연산자가 const char*와 std::string의 모든 순서 배합에 대한 비교를 위해 오버로드 되어 있다.
  - 즉 숨겨진 임시 변수가 생기지 않는다.