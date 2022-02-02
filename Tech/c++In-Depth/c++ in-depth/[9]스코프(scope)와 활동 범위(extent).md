## 스코프(scope)와 활동 범위(extent)

***

<br>



### :pushpin: 스코프(Scope)와 활동범위(Extent)

> **지역(local) 객체의 주소를 함수에서 반환하는 것은 심각한 런타임 에러를 일으킬 수 있다.**

- 함수는 프로그램 스택이라는 특별한 메모리 영역에 실행하는 동안에만 임시로 존재한다.

- 지역 객체들은 이러한 메모리 영역에 저장된다.

- 함수 종료 시 이 메모리 영역은 사라진다(지역 객체는 더 이상 존재하지 않는다)

- **존재하지 않는 객체를 주소화하는 것은 바람직하지 않다.**

  > ```c++
  > vector<int> fibon_seq(int size){
  >     if(size <= 0 || size > 1024){
  >         cerr<<"Warning : fibon_seq() : "<<size<<" not supported -- resetting to 8\n";
  >         size=8;
  >     }
  >     
  >     vector<int> elems(size);
  >     for(int ix=0; ix<size; ++ix){
  >         if(ix == 0 || ix == 1)
  >             elems[ix]=1;
  >         else
  >             elems[ix] = elems[ix-1]+elems[ix-2];
  >     }
  >     
  >     return elems; 
  > }
  > ```
  >
  > :point_right: elems는 fibon_seq() 함수의 종료와 함께 더 이상 존재하지 않기 때문에 레퍼런스 또는 포인터로 elems를 반환하는 것은 잘못된 것이다.
  >
  > :point_right: elems를 값으로 반환하는 것은 괜찮다, 객체가 복사되기 때문에 함수 바깥에서도 여전히 존재하기 때문이다.

- **저장 지속기간(storage duration), 활동 범위(extent)** : 어떤 메모리가 객체에 할당되어 있는 시간

  - **지역 활동범위(local extent)** : 지역 메모리(함수의 매개변수, 로컬 변수 등)의 할당과 해제 범위
  - **정적 활동범위(static extent)** : main()의 시작 전에 메모리가 할당되어 프로그램이 종료될 때까지 할당된 상태를 유지하는 범위

- **스코프(scope)** : 객체가 유효한 프로그램의 영역

  - **지역 스코프(local scope)** : size와 elems는 fibon_seq 함수 내에서 지역 스코프를 가진다.
    - :point_right: 프로그래머의 초기값 지정 없이는 초기화되지 않는 상태로 남아있는다.
  - **파일 스코프(file scope)** : 함수 외부에 선언된 객체(선언 시점부터 파일의 마지막까지 유효한 객체)
    - :point_right: 파일 스코프상의 객체는 **정적 활동범위(static extent)**를 가진다
    - :point_right: 파일 스코프에서 정의된 기본 타입 객체는 항상 0으로 초기화된다.

<br>



### :pushpin: 동적 메모리 관리(Dynamic Memory Management)

> **지역 활동범위와 파일 활동범위 모두 자동적으로 관리된다.**

- **저장 지속 기간(storage duration)의 형태**
  1. 지역 활동범위(local extent)
  2. 정적 활동범위(static extent)
  3. 동적 활동범위(dynamic extent)
- **동적 활동범위(dynamic extent)**
  - 이 메모리는 프로그램을 실행시키기 위해 만들어진 주소 공간 중에 아무도 쓰지 않는 빈 공간(free store, 자유 영역)에서 만들어진다(이를 힙, heap 메모리라고 부른다)
    - :point_right: 힙 객체는 동적 활동범위를 가진다고 말한다.
  - 이 메모리는 프로그래머에 의해 명시적으로 관리된다.
  - 메모리 할당은 new 연산자를 사용하여 수행되고, 메모리 해제는 delete 연산자를 사용해서 수행한다.
    - :point_right: new 연산자 : 할당된 메모리의 주소를 반환한다.
    - :point_right: delete 연산자 : 가리키고 있는 주소의 메모리를 해제한다.
- **메모리 누출(memory leak)**
  - 프로그래머가 어떠한 이유로 동적 할당된 객체를 해제하지 않았을 경우 발생

<br>