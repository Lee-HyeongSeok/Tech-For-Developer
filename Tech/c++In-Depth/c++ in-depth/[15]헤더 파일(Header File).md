## 헤더 파일(Header File)

***

<br>

### :pushpin: 헤더 파일

```c++
bool seq_elem(int pos, int &elem, const vector<int>* (*seq_ptr)(int)){
 const vector<int> *pseq = seq_ptr(pos); // 해당 위치의 수열을 계산하는 함수 간접 호출
 if(!pseq){
     elem=0;
     return false;
 }

 elem = (*pseq)[pos-1];
 return true;
}
```

- 5개의 프로그램 텍스트 파일에서 이를 호출해야 한다면? 

  - :point_right: 다섯 번의 선언이 있어야 한다.

- 5개의 파일에서 매번 seq_elem()을 선언하는 것보다 **헤더 파일에서 한 번 함수 선언**을 하는 것이 좋다.

  - 이러한 규약(convention)을 쓴다면 오직 한 번의 함수 선언만 필요하다.
  - 매개변수 또는 반환 타입이 변해도 이 선언만 수정하면 된다.
  - 이 규약에 의한 헤더 파일은 .h라고 하는 확장자가 붙는다.

- 헤더 파일을 NumSeq.h라 이름짓고, 수열과 관련된 모든 함수의 선언을 이 안에 넣는다.

  > ```c++
  > // NumSeq.h
  > bool seq_elem(int pos, int &elem);
  > const vector<int> *fibon_seq(int size);
  > const vector<int> *lucas_seq(int size);
  > const vector<int> *pell_seq(int size);
  > const vector<int> *triang_seq(int size);
  > const vector<int> *square_seq(int size);
  > const vector<int> *pent_seq(int size);
  > ```
  >
  > :point_right: 프로그램에서 함수의 정의는 한 번만 올 수 있다.
  >
  > :point_right: 헤더 파일에는 정의가 올 수 없다(프로그램의 여러 텍스트 파일에서 포함시킬 수 있기 때문)
  >
  > :point_right: 단 한 번의 정의만 올 수 있는 규칙에 하나의 예외가 있다.
  >
  > - 인라인 함수의 정의
  > - 인라인 함수의 확장(함수 코드를 호출부에 끼워 넣는 것)을 위해 호출하는 시점에서 그 정의를 컴파일러가 알아야만 하기 때문
  > - 즉, **인라인 함수 정의를 프로그램 텍스트 파일이 아닌 헤더 파일에 위치시킬 수 있다.**

<br>

### :pushpin: 헤더 파일의 파일 스코프에 객체 정의하기

```c++
// NumSeq.h
extern const vector<int>* (*seq_array[seq_cnt])(int); // 함수 포인터 선언
```

- seq_cnt 또한 extern으로 선언해야 하는 것인가?
  - :point_right: 인라인 함수가 그렇듯이 상수(const) 객체도 예외적인 규칙이다.
  - :point_right: 상수 객체의 정의는 파일 밖에서는 유효하지 않는다(즉, 여러 개의 프로그램 파일에서도 에러 없이 정의할 수 있음을 의미한다)
  - :point_right: 이는 상수식이 있는 배열의 선언, 그 밖의 다른 상황에서 컴파일러가 그 값을 사용할 수 있게 하려고 그렇다.

<br>

### :pushpin: 헤더 파일의 사용

```c++
#include "NumSeq.h" // 따옴표로 헤더 파일 포함

void test_it(){
    int elem=0;
    if(seq_elem(1, elem) && elem==1){
        // ...
    }
}
```

- 부등호(<, >)가 아닌 따옴표를 사용하여 헤더 파일을 포함시켰다.
  - :point_right: 따옴표 사용 : 헤더 파일과 헤더 파일을 포함하려는 프로그램 텍스트 파일이 같은 디렉토리에 있을 때
  - :point_right: 부등호 사용 : 헤더 파일과 헤더 파일을 포함하려는 프로그램 텍스트 파일이 다른 위치에 있을 때(파일이 프로젝트나 표준 헤더 파일로 가정되어 있다)
- 부등호 사용
  - 헤더 파일을 찾기 위해서 미리 정의된 위치들에서 검색을 진행
- 따옴표 사용
  - 사용자에 의해 제공된 헤더 파일이라 가정하고, 이를 찾으려면 포함하는 파일이 위치한 디렉토리부터 찾기 시작