## C++ In-Depth : Coding rules(class 2)

***

<br>

### :pushpin: 사소한 경고 메시지라도 무시하지 말라

> **경고 메시지, 오류 내용은 항상 주의 깊게 봐야 한다.**

- 경고 메시지가 전혀 발생하지 않는 상태의 깨끗한 빌드를 수행할 것
- 컴파일러의 경고 수준을 항상 최상위로 설정(사소한 문제라도 확인 가능)
- 문제 발생 시 **코드를 수정**하여 경고 또는 오류를 해결할 것
- 메시지 자체를 이해하고, 코드를 적절히 수정하여 사람과 컴파일러 모두에게 명확한 상태로 만들어야 함

<br>

### :pushpin: 성공적인 빌드

> **하나의 오류도 없이 조용히 이루어지는 빌드**

<br>

### :pushpin: 컴파일러 경고 예시 및 해결 방안

1. **제3의 헤더 파일**(개발자가 변경 불가한 라이브러리 헤더 파일이 오류를 일으키는 구조로 되어 있는 경우)

   > **원래부터 경고를 발생하는 표준 헤더 파일의 경우 wrapper 헤더를 만들어서 포장하고, #pragma warning 기법으로 최소화 시키는 방법**

   - 원래의 헤더를 #include 하는 자체적인 버전의 **랩(wrap) 파일**을 만든다.
   - 해당 범위의 경고 메시지 출력을 막아놓은 후 프로젝트의 나머지 부분에 대해서 미리 만들어 놓은 **래퍼**를 #include 하는 것

   ```c++
   // myproject/my_lambda.h 파일은 lambda.hpp를 래핑한 것
   // lambda.hpp를 직접 사용하지 않고 이 파일을 첨가하여 사용하길 권장
   // 현재 빌드에서는 "grep lambda.hpp <srcfile>"을 자동으로 검사
   
   #pragma warning(push) // 현재 헤더만을 사용하지 않게 한다(모든 경고에 대한 현재 경고 상태를 저장)
   #pragma warning(disable:4512)
   #pragma warning(disable:4180)
   #include <boost/lambda/lambda.hpp>
   #pragma warning(pop) // 원래의 경고 수준을 복구(스택에 푸쉬된 마지막 경고 상태를 반환)
   ```

   - 여기서 stack이란 warning state의 저장소
   - 저장 방식은 stack을 따름
   - **해당 기법을 사용하는 이유**
     - 경고가 발생하는 표준 헤더를 wrapper 헤더에 포함시켜 경고를 없애고, 다른 곳에서의 경고는 발생 시켜, 경고의 발생 위치를 편하게 찾기 위함

2. **사용되지 않은 함수 인자입니다.**

   > **함수 인자가 정말 필요 없는지 확인 후 함수 인자를 삭제**
   >
   > -> 이후 확장을 위해 자리를 마련해둔 것 또는 표준화된 형식의 일부로 사용된 경우

   ```c++
   // localityHint라는 함수 인자가 사용되지 않는다는 경고 발생 시
   pointer allocate(size_type numObjects, const void* localityHint=0){
       return static_cast<pointer>(mallocShared(numObjects * sizeof(T)));
   }
   
   // 다음과 같이 삭제
   pointer allocate(size_type numOjects, const void* /*localityHint*/=0){
       return static_cast<pointer>(mallocShared(numObjects * sizeof(T)));
   }
   ```

3. **정의된 변수가 사용되지 않았습니다.**

   > **해당 변수를 사용하지 않을 것인지 확실히 검사(RAII 스택 기반의 개체에서 가끔 발생)**
   >
   > -> 필요 없다면 변수 자체를 표현식으로 추가하여 경고문 없애는 것을 권장(이 표현식은 런타임 속도에 영향을 미치지 않는다.)

   ```c++
   void Fun(){
       Lock lock; // 변수 'lock'이 선언되었으나 사용되지 않음 경고 표시
   }
   
   void Fun(){
       Lock lock;
       lock; // 경고 문구 사라짐
   }
   ```

4. **초기화되지 않은 변수가 사용됨**

   > 변수를 초기화 한다

5. **return이 없음**

   > **프로그램 흐름상 함수의 끝에 도달할 일이 없어도 컴파일러가 return 구문을 요구하는 경우 존재**
   >
   > -> 프로그램 흐름이 함수의 끝에 도달하게 되는 예외 상황을 대처하는 것을 권장**(ex. 무한루프, throw 구문 등)**

   ```c++
   // c 값이 지정된 범위를 벗어날 경우에 return 구문이 없어서 오류 발생
   int func(Color c){
       switch(c){
           case Red: return 2;
           case Green: return 0;
           case Blue: 
           case Black: return 1;
       }
   }
   ```

   - c 값이 범위를 벗어났을 경우를 대비한 default 구문을 넣어 오류 제거

   ```c++
   #include <cassert> // cassert header include!
   int func(Color c){
       switch(c){
           case Red: return 2;
           case Green: return 0;
           case Blue: 
           case Black: return 1;
           default: assert(!"흐름상 도달하지 않는 부분"); // !"문자열"은 false로 처리된다.
               return -1;
       }
   }
   ```

6. **부호가 있는 숫자와 없는 숫자의 잘못된 쓰임**

   > **비교 또는 할당하는 두 변수의 타입이 다를 때 오류 발생 가능**
   >
   > [1] 비교 가능한 타입으로 변경
   >
   > [2] 직접 변환(캐스팅) : 컴파일러의 자동 캐스팅으로 인한 경고 문구 출력보단 직접 해주는 것을 권장

