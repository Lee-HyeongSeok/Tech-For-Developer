## C++ In-Depth Coding rules(class 23)

***

<br>

### :pushpin: 정의의 의존성과 순환 의존성을 최소화하라

- 정의 내용을 #include하여 의존하게 되는 상황을 줄여야 한다.
- 상호 의존적인 것도 피해야 한다.
  - 순환 의존성은 두 모듈이 직/간접적으로 서로에게 의존하고 있을 때 발생하는데, 두 모듈이 응집된 단위이기 때문에 서로 의존하는 모듈은 진정한 개별 모듈이라고 볼 수 없다.
  - 순환 의존성은 모듈의 장점에 위배되는 것
- 타입의 정의가 절실히 필요한 경우가 아니라면 일방적인 방향으로의 선언을 사용하는 것이 좋다.

<br>

### :pushpin: 클래스의 완전한 정의가 필요한 두 가지 경우

- 클래스 객체의 크기를 알아야 할 경우

  > 스택에 클래스 객체를 할당할 때나 다른 타입과 직접적으로 연결된 멤버로 사용할 경우

- 클래스의 멤버에 이름을 매기거나 호출해야 할 경우

  > 멤버 함수를 호출해야 할 경우

<br>

### :pushpin: 순환 의존성으로 인해 발생하는 컴파일 오류 또는 문제

- 순환 의존성의 가장 간단한 형태 : 두 클래스가 서로를 직접적으로 의존하고 있는 경우

  - ```c++
    class Child; // 의존 사이클
    class Parent{
        Child* myChild;
    }
    ```

  - ```c++
    class Child{ // 다른 헤더에 존재 가능
        Parent* myParent;
    }
    ```

  - 위 코드에서 Parent와 Child는 서로 연결되어 있다.

  - 컴파일에는 문제가 없지만, 서로 의존하고 있는 클래스는 같은 모듈 내에 있어야 하기 때문에 불안하다.

  - 이러한 의존 사이클이 여러 모듈에 걸쳐 있을 때에는 상황이 더욱 악화되며, 이러한 모든 모듈은 결합하여 하나의 큰 모듈을 이룰 수밖에 없고, 이는 모듈의 기본 특성에 해를 끼치는 방식이 된다.

- 한 클래스로부터 얻어진 클래스의 임시적인 의존성도 디자인에 악영향을 미치는 요소 중 하나이다.

  - 직/간접적으로 기본 클래스로부터 대부분의 특성을 물려받기 때문
  - 완전하게 안정된 계층 구조가 아니라면, 디자인 자체를 바꾸어야 한다.

<br>

### :pushpin: 순환 의존성 사이클을 피하기 위해서

- 의존성 반전 원칙을 적용해야 한다.

  > **저수준 모듈에 의존하는 고수준 모듈을 만들지 말고, 양쪽 모두 추상체에 의존하게끔 하는 것이다.**

- Parent와 Child 모두에 대해 독립적인 추상 클래스를 만들 수 있다면 사이클을 깨뜨릴 수 있다.

<br>

### :pushpin: 예외 상황

- 같은 모듈에 있고, 함께 테스트되며, 함께 사용되는 클래스들이라면 서로 간의 의존성이 크게 문제되지 않는다.
- 즉, 전체적인 디자인 측면에서 보았을 때 굳이 그렇게 할 필요가 없는 경우가 많다.