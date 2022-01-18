## C++ Memory Model : malloc, realloc, new

***

<br>

### :pushpin: malloc(C Language)

- 프로그램 실행 중에 동적으로 메모리를 할당하는 함수

- Heap 영역에 할당

- **void * malloc(size_t size)** 형태

- 성공 시 할당한 메모리의 시작 주소 리턴

- 실패 시 NULL 리턴

- 할당된 메모리는 반드시 해제 -> 메모리 릭(누수) 발생 가능

- 항상 OS가 관리하는 시스템 자원을 가져다 주는 것이 아닌, 미리 할당된 메모리 풀을 사용

- 메모리 공간의 요소들을 자동으로 초기화 하지 않는다(쓰레기 값을 가진 메모리 주소 반환)

  - 특정 값으로 초기화를 원한다면 -> **calloc** 함수 사용

- 연속된 메모리를 가진 자료형에 대해서만 크기를 할당

  > **ex) char, int, float, double, 배열 등**

<br>

### :pushpin: new(C++ Language)

- 프로그램 실행 중에 동적으로 메모리를 할당하는 함수

- 내부적으로 malloc을 사용

- **new를 사용하는 이유**

  > **new 연산자는 POD 타입이 아닌 자료형을 동적 할당하기 위해 만들어짐**
  >
  > **POD(Plan Old Data structure)란? 오브젝트가 아닌, 레코드를 의미하는 말**

  1. C에서는 구조체 내부에 함수 선언 불가
  2. 함수를 가진 구조체는 POD 아니다. 즉, malloc으로 동적 할당이 불가능
  3. C++은 구조체 내부에 함수 선언이 가능하다(클래스 개념)
  4. 이러한 구조체 내부에 함수를 선언한 오브젝트를 동적 할당하기 위해 new 연산자를 따로 구현하였다.

<br>

### :pushpin: realloc

- malloc 함수를 사용하여 할당된 메모리의 크기를 축소하거나 확장할 때 사용

- **void * realloc(void *ptr, size_t size)** 형태

- 메모리 크기 조정 성공 시 주소 값이 바뀐다면 기존 메모리는 해제시켜 준다.

- 메모리 크기 조정 실패 시 새 영역을 할당 후 **기존 요소들을 복사하여 새 메모리 주소를 반환**

  - **ptr이 항상 같은 주소를 가지고 있다 말할 수 없음**
  - **이때 기존 주소를 백업하여 해제하는 로직이 없으면 메모리 릭(누수) 발생**

- 메모리 누수 예시

  ```c
  void * val;
  val = malloc(SIZE);
  val = realloc(val, 2*SIZE); // 재할당 실패 시 NULL 반환, 기존 val이 사라지면서 힙 영역에 할당된 메모리 주소를 잃어버리게 된다.
  ```

- 올바른 재할당 예시

  ```c
  void * val;
  void * temp;
  
  val = malloc(SIZE);
  temp = realloc(val, 2*SIZE);
  if(temp != NULL)
      val = temp;
  ```

  ```c
  char * buffer = (char*)malloc(4);
  char * backupBuffer = buffer; // buffer를 백업하기 위한 포인터
  
  // realloc 실패 시
  if(NULL == (buffer = (char*)realloc(buffer, 8))){
      free(backupBuffer);
      cout<<"Memory allocation is failed"<<endl;
      exit(1);
  }
  ```

  

<br>

### :pushpin: new와 malloc 차이

- malloc은 함수, new는 연산자 이다.

  - 따라서 new는 오버로딩이 가능하다.

- malloc/free는 라이브러리가 제공하는 함수, new/delete는 언어가 제공하는 연산자(라이브러리 없이 사용 가능)

- malloc은 동적 할당만을 목적으로 하여 할당과 동시에 값을 초기화 불가, new는 할당과 동시에 초기화 가능

  > **ex) int * ptr = new int(256);**

- malloc은 realloc으로 메모리 크기 조정 및 재할당 가능, new는 기존 메모리 해제 후 재할당 해야 함

- new연산자는 내부적으로 malloc을 사용

  ```c++
  void * __CRTDECL operator new(size_t const size){ // size는 byte단위
      for(;;){
          // malloc을 이용하여 할당된 메모리 시작 주소를 block에 반환
          if(void * const block = malloc(size)){
              return block;
          }
          
          if(_callnewh(size) == 0){
              if(size == SIZE_MAX){
                  __scrt_throw_std_bad_array_new_length();
              }
              else{
                  __scrt_throw_std_bad_alloc();
              }
          }
      }
  }
  ```

  