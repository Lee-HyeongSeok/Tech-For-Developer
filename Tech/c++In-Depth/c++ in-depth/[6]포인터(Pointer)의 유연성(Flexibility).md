## 포인터(Pointer)의 유연성(Flexibility)

***

<br>

### :pushpin: Pointer

- 프로그램에서 객체를 간접적으로 다루는 방법을 제공한다.
- 객체를 직접 처리하지 않고 객체의 주소값이 저장된 포인터를 처리하게 된다.
- 포인터를 사용하면 프로그램의 유연성은 높이지만, 객체를 직접 다루지 않으므로 복잡성이 증가한다.

<br>

### :pushpin: 포인터의 2가지 속성

- 포인터에 저장된 주소값을 다룬다.
- 포인터가 가리키는 객체를 다룬다.

<br>

### :pushpin: 포인터의 사용

- ival 변수를 1024로 초기화하는 정수 타입의 객체를 정의

  > ```c++
  > int ival=1024;
  > ```

- 특정한 타입의 포인터를 정의하기 위해 타입의 이름 뒤에 별표(*)를 붙인다

  > ```c++
  > int *pi; // int형 타입 객체의 포인터(포인터를 특정 타입의 객체 주소를 저장)
  > ```

- ival을 포인터로 가리키도록 초기화

  > ```c++
  > int *pi = &ival; // 객체의 주소값을 알아내기 위해 주소 연산자(address-of operator) 사용
  > ```

<br>

### :pushpin: 역참조(dereference)

> 포인터가 가리키는 객체에 접근할 때 사용하는 방법
>
> 즉, 포인터에 저장된 주소값을 이용해 그 주소에 저장된 객체를 가져오는 것

- 포인터에 별표(*)를 붙여서 역참조 수행

  > ```c++
  > if(*pi != 1024)
  > ```

<br>

### :pushpin: 어떠한 객체도 가리키지 않을 때

- *pi라고 쓰면 실행중에 프로그램이 실패할 수도 있다.
  - pi의 주소가 객체를 가리킨다면 pi를 역참조해도 바르게 동작하지만, pi가 어떤 객체도 가리키지 않는다면 pi를 역참조하는 것은 정의되지 않은 동작을 시도한다.
- 포인터를 역참조하려 할 때는 반드시 **포인터가 객체를 가리키고 있는지 확인**해야 한다.

<br>

### :pushpin: 아무 객체도 가리키지 않는 포인터

- 0의 주소값을 갖는다(이는 종종 널(null) 포인터라고 부른다)

- 어떤 포인터 타입이라도 0의 값으로 초기화되거나 대입될 수 있다.

  > ```c++
  > int *pi = 0;
  > double *pd = 0;
  > string *ps = 0;
  > ```

- 널 포인터를 역참조하는 것을 막으려면 포인터의 주소가 0인지 검사해야 한다.

  > ```c++
  > // pi &&는 pi에 0이 아닌 다른 주소값이 저장되어 있을 때에만 true가 된다.
  > if(pi && *pi != 1024){
  >     //...
  > }
  > 
  > // pi가 0일 때 true 반환
  > if(!pi){
  >     //...
  > }
  > ```

<br>

### :pushpin: vector pointer example

```c++
#include <vector>
#include <cstdlib>

int main(){
    const int seq_cnt=6;
    vector<int> fibonacci, lucas, pell, triangular, square, pentagonal;
    
    // seq_addrs[0]에는 fibonacci 벡터의 주소가 저장됨
    // seq_addrs[1]에는 lucas 벡터의 주소가 저장됨
    vector<int> *seq_addrs[seq_cnt] = {
        &fibonacci, &lucas, &pell,
        &triangular, &square, &pentagonal
    };
    
    // 인덱스를 통해 개개의 벡터에 접근
    vector<int> *current_vec=0;
    
    for(int ix=0; ix < seq_cnt; ++ix){
        current_vec = seq_addrs[ix];
    }
    
    // 수열들의 출력 순서를 임의로 할 때 표준 라이브러리의 rand()와 srand() 함수 사용
    srand(seq_cnt);
    seq_index = rand() % seq_cnt; // 유효한 인덱스가 되기 위해 0~5 사이의 값을 취하도록 조정해야  한다.
    current_vec = seq_addrs[seq_index];
}
```

