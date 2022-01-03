## C++ Memory Model 변수와 메모리

***

<br>

### :pushpin: 변수와 메모리

![캡처](https://user-images.githubusercontent.com/55940552/147939914-e85cc6a7-1e4c-430a-bac4-5a8176c27a2e.PNG) **프로그램 실행 시 이러한 정적 데이터는 Stack에 저장**

<br>

![Untitled Diagram drawio](https://user-images.githubusercontent.com/55940552/147940139-deb3a7bf-a97c-48f3-916a-99c4ff1e930a.png) 

- 하지만, 컴퓨터는 변수 a, b, c를 이해할 수 없다.
- 컴퓨터가 변수를 이해하는 방식은 메모리의 가장 위에서 몇번째에 존재하는가로 이해함
- a+b는 a의 주소에 있는 공간(0)과 b의 주소에 있는 공간(3)을 더한 값을 가짐

![Untitled Diagram drawio (1)](https://user-images.githubusercontent.com/55940552/147940818-d2491eb1-399e-4f7e-8aae-9187e6928cee.png) 

<br>

![캡처2](https://user-images.githubusercontent.com/55940552/147941287-f6f4209c-f103-4333-be7c-929f83876b3c.PNG) 

- 다음과 같은 프로그램의 실행에서 각 변수의 주소 값은 오른쪽 그림과 같이 나타난다.
- int형 변수의 주소 간격은 12, double은 16의 형태를 보이고 있다(현재 build 옵션은 Debug)
  - 지역 변수를 컴파일러가 할당할 때 C/C++ 표준은 컴파일러가 어떻게 배치해야 할지에 대해 아무런 규정을 정해놓지 않음
  - 지역 변수의 메모리 레이아웃도 나름 수행 성능에 영향을 주는 부분이므로, 컴파일러가 상황에 따라 적절하게 구성할 수 있도록 제어권을 부여한 것
  - int a=0, int b=3 으로 정의했을 때 Stack에 b 다음 a가 쌓일 것이라는 연속성을 가정하는 모든 작업은 정의되지 않은 동작이고 이식성이 없으므로 개체가 생성되는 주소의 순서조차 확신할 수 없다(1.8 C++ 개체 모델)
  - 따라서 **빌드 옵션에 따라** 동일한 컴파일러에서 주소의 순서가 변경될 수도 있다.
  - **Release 모드**에서 변수는 연속적이지만 같은 순서는 아니다.
  - **Debug 모드**에서 변수의 주소에 대한 추가 공백(기존 int형 4byte + 8byte)은 **/RTCs 옵션**에서 가져온다.
  - 이런 **/RTCs 옵션**을 제거하면 예상한 대로 각 4byte인 연속 변수를 얻게 되는 것
    - /RTCS 옵션 : 런타임 에러 체크
- 따라서 Debug 모드에서 Release 모드로 변환하여 컴파일 하여 아래와 같은 결과를 얻었다.

![캡처3](https://user-images.githubusercontent.com/55940552/147943804-0b4e223a-d461-4d33-a93a-5fbdc7a6569a.PNG) 

- int형 4byte, double 형 8byte로 정상적인 스택 주소가 보인다.

![Untitled Diagram drawio (2)](https://user-images.githubusercontent.com/55940552/147945299-41a817ca-8948-4a79-8ad8-b6176e9a33c6.png) 

- 왼쪽의 스택이 실제 오른쪽과 같은 메모리 공간에 할당되는 과정이다.
- 주소가 스택에 쌓여갈 수록 줄어드는 이유
  - 스택은 높은 주소에서 낮은 주소의 방향인 감소하는 형태로 쌓여가기 때문
  - 하지만 실제로 높은 주소는 가장 끝단이 아니다.
  - 윗 부분에 또 다른 프로그램 정보가 들어있기 때문(enbinment)