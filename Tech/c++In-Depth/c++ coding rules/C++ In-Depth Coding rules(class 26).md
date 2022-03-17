## C++ In-Depth Coding rules(class 26)

***

<br>

### :pushpin: 값, (스마트) 포인터, 참조 중 적절한 방식으로 인자를 얻어라

- 인자가 입력, 출력, 입력/출력 중 어떤 것인지
- 값, 참조 인자 중 어떤 것인지

이 두가지 상황에서 적절히 선택하는 것이 중요하다.

<br>

### :pushpin: 인자에 대한 값, 참조, 포인터를 적절히 선택하는 것은 안전과 효율성을 높인다.

**[입력 인자의 경우]**

1. 입력의 용도로만 사용되는 인자의 경우는 포인터와 참조에 대해 const 속성을 부여하는 것이 좋다.
2. 값에 의한 복사(Point, complex\<float>)가 용이한 기본 타입(char, float)과 값 객체를 사용하는 것이 좋다.
3. 다른 사용자가 정의한 타입을 받아들일 때에는 const로의 참조 방식을 사용하자
4. 함수에서 인자의 복사가 이루어지는 경우에는 참조보다는 값에 의한 전달을 사용하자. const로의 참조를 얻고 복사할 때에도 마찬가지이며, 이러한 방식은 컴파일러가 임시본을 최적화하는 데 도움을 준다.

<br>

**[출력 또는 입/출력 인자의 경우]**

1. 선택적으로 사용되는 인자(호출자가 null을 전달하여 값이 없거나 값이 필요 없음을 나타낼 수 있는 경우)이거나 함수가 포인터의 복사본을 저장하는 경우 혹은 인자의 소유권을 관리해야 할 경우는 (스마트) 포인터에 의한 전달 방식을 사용하자
2. 인자가 반드시 필요한 경우, 그리고 함수가 포인터를 저장하지 않으며 소유권이 아무런 영향을 미치지 못 할 때에는 참조에 의한 전달 방식이 적절하다. 해당 인자가 꼭 있어야 하고, 올바른 객체를 제공하는 책임을 **호출자가** 가질 때를 말한다.