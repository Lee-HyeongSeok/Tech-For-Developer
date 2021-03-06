## C++ In-Depth Coding rules(class 19)

***

<br>

### :pushpin: 가능하면 로컬 변수를 선언하여 사용하라

- 사용 범위가 넓은 함수는 가능하면 최소화하라(파일 스코프 객체 등)
- 변수는 하나의 상태이고, 가능하면 최소의 상태를 다루는 것이 편하다.
- **변수의 수명은 최소한 짧게 유지하도록 하자.**

<br>

### :pushpin: 필요 이상으로 수명이 길게 정해진 변수의 단점

1. 프로그램의 이해와 관리가 힘들다.

   > 현재 드라이브만이 바뀌었을 때 모듈 경로 문자열은 업데이트되어야 할 필요가 없다.

2. 문맥상의 의미를 파악하기 힘들다.

   > 대부분의 영역에서 유효한 범위인 네임스페이스 수준의 변수가 최악의 경우이다.

3. 값이 초기화되기 쉽다.

   > 적절한 초기화 없이 변수를 선언해서는 안 된다.
   >
   > 초기화되지 않은 변수는 C, C++ 프로그램에서 버그를 발생시키는 큰 원인이며, 컴파일러에 의해 언제나 감지될 수 있다.

<br>

### :pushpin: 올바른 변수 정의

- 변수를 가능하면 로컬 범위로 정의, 초기화에 필요한 충분한 데이터를 얻은 시점, 사용 직전에 초기화
- 루프에 사용되는 변수는 때로 루프 외부에서 선언하는 것이 나은 경우가 있다.