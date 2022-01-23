## C++ Memory Model static_assert의 사용

***

<br>

### :pushpin: integer cppreference 참조

- 우리가 알고있는 int와 unsigned int의 경우 32bits(4bytes)라 생각했지만, **Width in bits by data model** 정의에 따르면 C++ standard : at least 16이라 표기되어 있다.

  > **즉, int 또는 unsigned int는 컴파일러나 아키텍처마다 16bit가 될 수도 있다는 뜻이다.**

- **이를 해결하기 위한 방법**

  1. **compilation assertion을 사용하는 방법**

     > **컴파일 과정에서 어떠한 조건의 만족 여부를 평가해준다**

     ```c++
     #include <iostream>
     
     int main(void){
         // int가 4byte임을 확인하고자 할때, int가 4byte라는 것을 검증하는 코드
         static_assert(sizeof(int)==4, "int is 4bytes"); 
     }
     ```

  2. **fixed width integer types(C++ 11)**

     ```c++
     #include <cstdint>
     #include <iostream>
     
     int main(void){
         // 숫자는 bits를 의미
         std::cout<<sizeof(int8_t)<<std::endl; // 1byte형 integer type
         std::cout<<sizeof(int64_t)<<std::endl; // 8byte형 integer type
     }
     ```

     