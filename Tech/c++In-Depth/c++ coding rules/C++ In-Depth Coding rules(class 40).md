## C++ In-Depth Coding rules(class 40)

***

<br>

### :pushpin: 가상 함수는 비공용으로, 공용 함수는 비가상으로 설정하라

- 변경된 내용이 다른 클래스에 많은 영향을 주는 클래스(기본 클래스, 라이브러리나 프레임웍 내의 클래스)에서는 공용(public) 함수를 비가상으로, 가상 함수는 비공용(private)으로 설정하자
- 파생 클래스가 기본 버전을 호출해야 한다면 protected를 사용하면 된다.
- 변화에 민감한 구조에서는 완전한 추상화를 이루는 것이 좋다. 공용 함수를 비가상으로, 가상 함수를 사영으로 만드는 것
  - 이를 비가상 인터페이스(Nonvirtual Interface; NVI) 패턴이라고 한다.

<br>



### :pushpin: 공용 가상 함수는 두 가지의 서로 다른, 경쟁적인 관계에 있는 역할을 가지고 있다.

- 인터페이스를 지정한다.
  - 공용이라는 점은 외부에 표현되는 클래스 인터페이스의 직접적인 일부분이 됨을 의미한다.
- 구현상의 세부 사항을 지정한다.
  - 가상이라는 점은 파생 클래스가 함수의 기본 구현체를 대체하는데 관련이 있음을 의미한다.

이러한 두 역할은 서로 다른 목적과 쓰임을 가지고 있기 때문에 종종 충돌하며, 정의상으로는 하나의 함수가 두 역할을 완벽하게 만족시키는 것이 불가능하다.

<br>

### :pushpin: 공용 함수와 가상 함수를 분리하면 좋은점

- 각 인터페이스가 보다 자연스러운 형태를 가지게 된다.
  - 공용 인터페이스를 커스텀화된 인터페이스에서 분리하면 각 인터페이스가 서로 간의 타협을 위한 압박을 피할 수 있다.
  - 때문에 원래의 목적에 보다 충실한 자연스러운 형태를 가질 수 있다.
- 기본 클래스를 제어할 수 있다.
  - 기본 클래스가 자신의 인터페이스와 정책을 완전하게 제어하고, 인터페이스의 전후 조건을 지정할 수 있으며, 지침을 추가하는 등의 작업을 하나의 편리하고 재사용 가능한 장소, 즉 비가상 인터페이스 함수에서 이룰 수 있다.
- 기본 클래스는 변화에 보다 잘 대처할 수 있다.
  - 인터페이스의 전후 조건을 추가하거나
  - 작업을 여러 단위로 나누거나
  - 핌플 방식을 통해 완전한 인터페이스/임플리먼테이션 분리를 이루거나
  - 기본 클래스의 커스텀화 특성 등을 클래스로부터 상속받거나
  - 클래스를 사용하는 코드에 영향을 주지 않고 자유롭게 행할 수 있다.

<br>

### :pushpin: NVI는 특별한 실행 순서를 가진 소멸자에는 적용되지 않는다.

- NVI 공변(covariant) 리턴 타입을 직접 지원하지는 못하므로, dynamic_cast 다운캐스트를 사용하지 않고도 이러한 리턴 타입을 호출 코드에서 사용하기 위해서는 가상 함수를 공용으로 만드는 것이 좋다.



