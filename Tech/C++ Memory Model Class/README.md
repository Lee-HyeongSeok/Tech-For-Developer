## C++ 메모리 모델

***

<br>

### :pushpin: C++이란?

- 개발자가 직접 메모리를 관리해야 하는 언어
  - 개발자가 메모리 관리에 실패하면 메모리 leak 발생, 프로그램 실행 도중 멈춤

<br>

### :pushpin: 학습 목표

- high level 메모리 모델에서 데이터가 어떻게 저장되는지 학습
- low level 메모리 모델에서 데이터가 어떻게 저장되는지 학습
- 데이터가 왜 스택에 저장되는지, 어떤 데이터는 왜 힙에 저장되어야 하는지 학습

<br>

### :pushpin: 학습에 들어가기 전

- C++을 통해 프로그램을 만들었다.

  - 어떠한 형태로 실행되는가?

    > **사용자가 실행시키면 운영체제가 메모리 공간을 확보하고, 해당 프로그램을 Ram에 적재시켜 실행되며, 이를 프로세스라 한다.**

  - 프로세스란?

    > **[1] 컴퓨터에서 연속적으로 실행되고 있는 프로그램**
    >
    > **[2] 운영체제로부터 스택, 코드, 데이터, 힙 메모리 자원을 할당 받는 작업의 단위**
    >
    > **[3] 각 프로세스는 최소 1개 이상의 스레드를 보유**
    >
    > **[4] 실제로는 스레드 단위로 스케줄링 실행**
    >
    > **[5] 운영체제는 프로세스에서 실제 필요한 부분만 메모리에 적재하여 컴퓨터 램보다 큰 용량의 프로그램을 실행시킬 수 있는 것**
    >
    > **[6] 각 프로세스는 운영체제에서 프로세스 제어 블록(PCB)에 의해 표현된다.**
    >
    > **[7] 운영체제의 프로세스 관리 부에서 관리**
    >
    > **[8] 각 스레드는 스택 영역을 가지고 있으며 프로세스 내부의 코드, 데이터, 힙 영역을 공유한다.**

  - 프로세스 제어 블록(PCB)이란?

    > **[1] 각 프로세스는 하나의 PCB를 가짐**
    >
    > **[2] PCB에는 해당 프로세스에 대한 상태, CPU 사용 시간, 프로세스 아이디 등을 저장**

  - 프로그램과 프로세스의 차이?

    > **[1] 프로그램 : 특정 작업을 수행하기 위한 명령어와 데이터의 집합체(보조기억 장치에 2진 형태의 파일로 저장)**
    >
    > **[2] 프로세스 : 프로그램을 메모리에 적재하고 실행시킬 수 있는 자원 집합의 단위**

  - 프로세스 구조

    ![Untitled Diagram drawio](https://user-images.githubusercontent.com/55940552/147816400-56041885-3efd-47e1-b772-14b39a92e3ec.png) 

    - **Code 영역**
      - Read-Only 특성을 가짐
      - 프로세스가 실행할 코드와 매크로 상수가 기계어 형태로 저장된 공간
      - CPU는 코드 영역에 저장된 명령어를 하나씩 가져가서 처리
      - 컴파일 타임에 결정
    - **Data 영역**
      - Read/Write 특성을 가짐(실행 도중에 전역변수가 변경될 수 있기 때문)
      - 코드에서 선언한 전역 변수, Static 변수 등이 저장된 공간
      - 코드에서 전역변수 또는 static 값을 참조하면 컴파일 시 Data 영역의 주소를 가르킴
    - **Heap 영역**
      - 동적으로 생성되는 메모리 영역(런타임에 결정되는 영역)
      - 사용 후 반드시 해제해야 함(memory leak 발생)
      - 스택 영역보다 할당할 수 있는 메모리 공간이 많지만, 포인터로 접근하기 때문에<br> 다른 자료구조에 비해 데이터 Read/Write가 느린 단점
      - 메모리의 낮은 주소에서 높은 주소의 방향으로 할당
    - **Stack 영역**
      - 함수(스택 프레임) 안에서 선언된 지역 변수, 매개 변수, 리턴 값, 리턴 주소 등이 저장
      - 함수 호출 시 스택에 저장, 종료 시 스택에서 삭제(LIFO 방식을 따름)
      - 메모리의 높은 주소에서 낮은 주소의 방향으로 할당됨
      - 재귀 함수가 너무 깊게 호출되거나 함수에 지역 변수를 너무 많이 선언하여<br> 스택 영역을 초과하면 Stack Overflow 에러 발생
      - 함수의 인자로 전달되는 값들은 오른쪽에서부터 왼쪽으로 스택에 저장된다.

<br>

### :pushpin: Overflow

- 한정된 메모리 공간이 부족하여 다른 영역의 메모리 공간을 침범하는 것

- **종류**

  - **힙 오버플로우** : 힙 영역이 스택 영역을 침범하는 경우
  - **스택 오버플로우** : 스택 영역이 힙 영역을 침범하는 경우

- **스택과 힙 메모리 할당 방향**

  ![Untitled Diagram drawio (1)](https://user-images.githubusercontent.com/55940552/147821901-c1d3af55-0e1f-4123-9b88-6e9ca4611994.png) 

<br>

### :pushpin: 메모리 모델

- class 1 : [:page_facing_up: 변수와 메모리](https://github.com/Lee-HyeongSeok/Tech-For-Developer/blob/master/Tech/C%2B%2B%20Memory%20Model%20Class/C%2B%2B%20Memory%20Model%20%EB%B3%80%EC%88%98%EC%99%80%20%EB%A9%94%EB%AA%A8%EB%A6%AC.md) 
- class 2 : [:page_facing_up: Type size in Memory](https://github.com/Lee-HyeongSeok/Tech-For-Developer/blob/master/Tech/C%2B%2B%20Memory%20Model%20Class/C%2B%2B%20Memory%20Model%20-%20Type%20size%20in%20Memory.md)
- class 3 : [:page_facing_up: malloc, realloc, new](https://github.com/Lee-HyeongSeok/Tech-For-Developer/blob/master/Tech/C%2B%2B%20Memory%20Model%20Class/C%2B%2B%20Memory%20Model%20%20malloc%2C%20realloc%2C%20new.md)
- class 4 :  [:page_facing_up: static_assert의 사용](https://github.com/Lee-HyeongSeok/Tech-For-Developer/blob/master/Tech/C%2B%2B%20Memory%20Model%20Class/C%2B%2B%20Memory%20Model%20static_assert%EC%9D%98%20%EC%82%AC%EC%9A%A9.md)
- class 5 : [:page_facing_up: 구조체와 메모리](https://github.com/Lee-HyeongSeok/Tech-For-Developer/blob/master/Tech/C%2B%2B%20Memory%20Model%20Class/C%2B%2B%20Memory%20Model%20%EA%B5%AC%EC%A1%B0%EC%B2%B4%EC%99%80%20%EB%A9%94%EB%AA%A8%EB%A6%AC.md)

