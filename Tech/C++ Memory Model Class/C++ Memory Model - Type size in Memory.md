## C++ Memory Model : Type size in Memory

***

<br>

### :pushpin: 학습 목표

- 각 변수나 클래스 구조, 포인터가 메모리 상에 어느정도의 크기로 할당되는지 알아본다.

<br>

### :pushpin: 저번 시간

- 스택에서 변수에 접근하는 방법
  - Top 위치에서 몇 번째 떨어져있는지로 변수의 위치를 찾는다.
- 실제로는 격자 무늬 속에서 각각의 변수가 사이즈에 맞는 공간을 차지하고 있음

<br>

### :pushpin: 변수의 사이즈 출력

```c++
int main(){
    int a=0;
    cout<<sizeof(a)<<endl;
    cout<<sizeof(int)<<endl;
}

// 출력 결과
/*
4
4
*/
```

- 4의 의미 : 4byte(32bit)
- a라는 변수를 할당하는 순간 4byte의 공간을 차지하게 된다.
- 정수형 데이터 타입 : short(2byte), int(4byte), long(8byte)
- 양수 정수형 데이터 타입 : unsigned short(2byte), unsigned int(4byte), unsigned long(8byte)
- 실수형 데이터 타입 : 4byte가 float, 8byte가 double이 되어 사용하고 있음

<br>

### :pushpin: C++ Reference Integer

- int형 또는 unsigned int형은 4byte(32bit)를 가지고 있다 생각하였지만 C++ Standard를 보면 at least 16로 나와있다.

- 이는 int형 또는 unsigned int형이 2byte(16bit)가 될수도 있다는 뜻

- 즉, 컴파일러 또는 아키텍처마다 다를 수도 있다는 뜻

- **해결 방안**

  1. **Compiler Asserts** : 컴파일 과정에서 어떤 조건이 만족하는가를 평가 해준다.

     - int형이 4byte임을 확인할 때

       ```c++
       int main(){
           // int형이 4byte임을 확인하는 compiler assertion
           static_assert(sizeof(int)==4, "int is 4bytes");
           int a=0;
           
           cout<<sizeof(a)<<endl;
           cout<<sizeof(int)<<endl;
       }
       
       // 컴파일 수행 시 성공적으로 수행 완료
       ```

     - 다른 아키텍처 또는 컴파일러 환경에서는 static_assert가 깨지게 된다.

     - static_asset에 조건을 만족하지 않으면 컴파일 오류 발생

  2. **Fixed Width integer types(google, cppreference fixed size integer 검색)**

     - Fixed width integer types(since C++ 11)을 코드에 활용

       ```c++
       #include <cstdint> // 해당 헤더 포함
       
       int main(){
           int a=0;
           cout<<sizeof(int8_t)<<endl; // 8bit, 1byte형 int
           cout<<sizeof(int64_t)<<endl; // 64bit, 8byte형 int
       }
       
       // 출력 결과
       /*
       1
       8
       */
       ```

     - 팀, 회사마다 기준은 다름

       ```c++
       #include <cstdint>
       #include <array> // c++에서 Array를 사용할 때는 해당 헤더를 포함시켜서 사용해야 좋다.
       
       int main(){
           // c 스타일 배열 선언
           int a[10];
           cout<<sizeof(a)<<endl;
           // c++ 스타일 배열 선언, 5개의 int형 배열이 생성됨 
           array<int, 5> ia;
           cout<<sizeof(ia)<<endl;
           
           uint64_t ui8;
           
           uint64_t * ui64ptr = &ui8;
           
           cout<<sizeof(ui64ptr)<<endl; // 포인터의 사이즈
           cout<<(uint64_t)ui64ptr<<endl; // 포인터의 주소
       }
       
       // 출력 결과
       /*
       40
       20
       8
       14072894554856 ui64ptr 포인터가 가지고 있는 ui8의 주소
       */
       ```

       ![Untitled Diagram drawio](https://user-images.githubusercontent.com/55940552/148965140-9ff6b1e8-7a66-49f6-9f62-a421962f1596.png) 

  

