## C++ In-Depth Coding rules(class 20)

***

<br>

### :pushpin: 변수는 항상 초기화하여 사용하라

- 초기화되지 않은 변수는 C, C++에 있어 버그의 온상이므로 항상 변수 사용 전에 깨끗한 메모리 상태를 만들어야 한다.
- 컴파일러가 변수의 초기화를 강요하지는 않는다(로컬 변수나 컨스트럭터 초기화 목록에 빠진 멤버 등)
- 다른 문맥에서의 호출, 재 컴파일 등 프로그램의 다른 부분에 생긴 변화로 인해 간헐적인 프로그램 중단이 발생할 수 있다.

<br>

### :pushpin: 변수 초기화 권장 방법

- 권장되지 않는 방법, 변수를 초기화하지 않을 때

  > ```c++
  > int speedupFactor;
  > if(condition)
  >     speedupFactor=2;
  > else
  >     speedupFactor=-1;
  > ```

- 보다 나은 방법, 변수를 초기화하였을 때

  > ```c++
  > int speedupFactor = -1;
  > if(condition)
  >     speedupFactor=2;
  > ```

- 보다 나은 방법, 변수를 초기화하였을 때(변수의 정의와 초기화 사이에 간격을 두지 않는 것)

  > ```c++
  > int speedupFactor = condition ? 2 : -1;
  > ```

- 복잡한 계산의 흐름을 함수로 대체하는 방법

  > ```c++
  > // 권장되지 않는 방법
  > int speedupFactor;
  > if(condition){
  >     // .. code ..
  >     speedupFactor = someValue;
  > }
  > else{
  >     // .. code ..
  >     speedupFactor = someOtherValue;
  > }
  > 
  > // 보다 나은 방법
  > int speedupFactor = ComputeSpeedupFactor();
  > ```

<br>

### :pushpin: 배열의 초기화 방법

- 배열과 같은 집합 타입의 경우는 적절한 초기화가 모든 데이터에 대한 적절한 조치를 의미하는 것은 아니다.

- MAX_PATH라는 크기를 가지는 고정된 문자 배열을 사용해야 하는 API가 있을 경우

  > :point_right: 배열이 null로 마무리되는 C 문자열로 다루어질 것이라는 확신이 있다면 즉시 값을 할당하는 것이 좋은 방법이다.
  >
  > ```c++
  > // 사용 가능한 방법, 빈 경로를 만든다.
  > char path[MAX_PATH];
  > path[0] = '\0';
  > ```
  >
  > :point_right: 배열 내의 모든 문자를 0으로 채우는 것이 보다 안전한 방법이다.
  >
  > ```c++
  > // 보다 나은 방법, 0으로 채워진 경로를 만든다.
  > char path[MAX_PATH] = { '\0' };
  > ```



<br>

### :pushpin: 예외적인 상황

- 하드웨어나 다른 프로세서에 의해 작성되는 입력 버퍼 등의 데이터는 프로그램에서 초기화할 필요가 없다.

