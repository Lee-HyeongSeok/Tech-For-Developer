## C++ In-Depth Coding rules(class 18)

***

<br>

### :pushpin: 마법의 숫자는 쓰지 말라

- 42나 3.14159와 같은 리터럴은 사용하지 말라

- 이런 값들은 자체적으로 자신을 설명하지 못할뿐더러, 여러 곳에서 사용할 경우 관리도 어렵다.

- 대신에 width * aspectRatio와 같은 심볼 이름과 표현식을 사용하는 것이 좋다.

- 이름은 정보를 추가하고 관리에 있어 구심점 역할을 한다.

- 프로그램에 원시적인 숫자를 반복해서 사용하는 것은 프로그램의 이해도를 떨어뜨리고 관리를 힘들게 하므로, **상수보다는 열거형이나 const 값**, **범위가 주어지고 이름이 정해진 값을 사용하는 것**이 바람직하다.

- 문자열을 직접 프로그램에 써넣는 것보다는 상징적인 상수를 사용하자.

  > **문자열을 코드에서 분리하고(.cpp이나 리소스 파일), 프로그래머가 아닌 사람이 보아도 그 의미와 용도를 알 수 있게끔 해야 한다.**
  >
  > ```c++
  > // 네임스페이스 수준의 특정한 영역을 가진 상수
  > const size_t PAGE_SIZE	= 8192,
  > 			WORDS_PER_PAGE	= PAGE_SIZE / sizeof(int),
  > 			INFO_BITS_PER_PAGE	= 32 * CHAR_BIT;
  > ```
  >
  > ```c++
  > // 특정한 클래스에 소속된 상수
  > // 클래스 정의 내에 정적인 통합 상수를 정의하여 사용하는 경우
  > // 다른 타입의 상수는 분리된 정의로 쓰거나 짧은 함수로 분리하는 것이 좋다.
  > 
  > // widget.h 파일
  > class Widget{
  >     static const int defaultWidth = 400; // 선언부에서 제공된 값
  >     static const double defaultPercent; // 정의부에서 제공된 값
  >     static const char* Name(){ return "widget"; }
  > }
  > 
  > // widget.cpp 파일
  > const double Widget::defaultPercent = 66.67; // 정의부에서 제공된 값
  > const int Widget::defaultWidth; // 정의가 필요함
  > ```
  >
  > 