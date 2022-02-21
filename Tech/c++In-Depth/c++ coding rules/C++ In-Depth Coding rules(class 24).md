## C++ In-Depth Coding rules(class 24)

***

<br>

### :pushpin: 헤더 파일은 충분히 완성된 형태로 만들어라

- 각 헤더 파일이 자체적으로 완성도가 있게끔 작성하라

- 헤더의 내용과 관련있는 다른 헤더는 첨가시켜 주어야 한다.

- 만약 어떤 헤더 파일이 다른 헤더 파일을 포함시켜야만 작동할 수 있도록 만들어진다면 그만큼 그 헤더 파일의 완성도는 떨어지게 되고, 그 헤더 파일의 사용자는 활용에 어려움을 겪는다.

- 필요 없는 헤더는 첨가하지 말고 불필요한 의존성을 만들지 말자

- **헤더는 충분히 자급자족할 수 있는 형태로 완성도 있게 만들어야 한다.**

  > 빌드 내에서 각 헤더는 분리시켜 컴파일하고, 각각 오류나 경고가 없게 만들어야 한다.

<br>

### :pushpin: 템플릿과 연결되었을 때의 미묘한 이슈들

- 의존 이름

  >  템플릿은 정의되는 시점에 컴파일되는 것이 일반적이지만, 의존 이름이나 타입이 아직 그 시점까지 컴파일되지 않았을 경우는 예외이다.
  >
  > ```c++
  > template <class T>
  > class Widget{
  >     std::deque<T> ..
  > }
  > ```
  >
  > :point_right: \<deque\>가 첨가되어 있지 않다고 해도 Widget의 인스턴스가 만들어지기 전까지는 컴파일 오류를 발생시키지 않지만, Widget의 인스턴스가 만들어지기 위해서는 헤더에 분명히 #include \<deque\>가 있어야 한다. 

- 멤버 함수 템플릿 및 템플릿의 멤버 함수는 사용될 때에만 인스턴스가 만들어져야 한다.

  > Widget은 std::deque\<T\> 타입의 멤버가 없지만, Widget의 멤버 함수 중 하나인 Transmogrify가 deque를 사용한다면?
  >
  > :point_right: Transmogrify를 사용하지 않는 호출자는 \<deque\>를 첨가하지 않고도 Widget의 인스턴스를 만들고 사용할 수 있겠지만, 표준적으로 Widget 헤더에는 #include \<deque\>가 있어야 한다.
  >
  > :point_right: 어떤 호출자가 deque를 필요로 할지 모르기 때문
  >
  > 즉, 누군가 사용할 가능성이 있다면 추가해주어야 한다.