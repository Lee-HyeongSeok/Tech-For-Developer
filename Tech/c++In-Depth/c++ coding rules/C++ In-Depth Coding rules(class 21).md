## C++ In-Depth Coding rules(class 21)

***

<br>

### :pushpin: 너무 긴 함수와 많은 중첩 구조는 피하라

- 짧은 것이 긴 것보다 낫다.
- 평면적인 것이 깊은 것보다 낫다.
- 길이가 긴 함수와 중첩된 코드의 구조는 한 함수에 너무 많은 역할을 부여할 우려가 있으므로, 적절한 재 할당을 통해 그 문제를 해결해야 한다.
- 모든 함수는 이름에 맞는 적절한 하나의 역할을 가져야 한다.
- 너무 긴 라인으로 구성된 함수와 여러 블록(if, for, while, try 등)이 중첩된 구조는 함수의 이해를 힘들게 하고, 관리를 힘들게 한다.

<br>

### :pushpin: 함수의 길이와 중첩 구조를 제어하자.

- 묶기를 선호하라

  > 하나의 함수가 하나의 역할만을 가지도록 하자

- 반복하지 말라

  > 반복되는 비슷한 코드 조각은 함수로 만들어 재사용되도록 하자

- &&를 활용하라

  > if 구조를 중첩하기보다는 &&조건을 사용하는 것이 좋다.

- try를 복잡하게 사용하지 말라

  > 소멸자(destructor)를 사용한 자동 해제 방식을 활용하라

- 알고리즘을 활용하라

  > 루프보다 평면적이고 깔끔하며, 기능도 낫다

- 타입 태그에 switch 구문을 사용하지 말라

  > 다형적 함수가 보다 나은 방법이다.

<br>

### :pushpin: 예외적인 상황

- 다른 작업들과는 독립적으로 처리되어야 하는 특수한 기능에 대해서는 긴 함수나 중첩 구조가 필요한 경우도 있다.
- 작은 조각으로 기능을 나누었을 때 로컬 변수의 전달이나 자원의 사용이 너무 많이 요구되는 경우
- 각 조각의 함수가 비슷한 인자를 가지는 경우에는 새로운 클래스의 멤버로 만들어 사용하는 것이 낫다.