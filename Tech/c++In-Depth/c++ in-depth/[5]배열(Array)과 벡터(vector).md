## 배열(Array)과 벡터(vector)

***

<br>

### :pushpin: Container type

- 연속된 값을 저장
- 값은 이름이 아닌 위치(인덱스)에 의해 참조된다.

<br>

### :pushpin: C++ Container

- 기본 배열(built-in array)이나 표준 라이브러리의 벡터 클래스로 정의 가능
- 일반적으로 기본 배열보다는 벡터 클래스의 사용을 권장

<br>

### :pushpin: vector class

- 명시적 초기화를 지원하지 않는다.

  > vector<int> elem_seq(seq_size);
  >
  > elem_seq[0] = 1;
  >
  > elem_seq[1] = 2;
  >
  > // ...
  >
  > elem_seq[17] = 22;

- 기본 배열을 초기화해서 그것을 벡터 클래스의 초기화에 이용하는 방법

  > int elem_vals[seq_size]={
  >
  > ​	1, 2, 3, 3, 4, 7, 2, 5, 12,
  >
  > ​	 3, 6, 10, 4, 9, 16, 5, 2, 3
  >
  > };
  >
  > // elem_vals에 저장된 18개 요소를 표시해 elem_seq 안에 복사한다.
  >
  > vector<int> elem_seq(elem_vals, elem_vals+seq_size);

<br>

### :pushpin: C++에서 배열(Array)을 사용할 때?

- 표준 라이브러리인 array 헤더를 사용해서 작성하는 것을 권장

- 기존에 C style의 배열은 범위를 벗어난 메모리 작업이 가능했기 때문에 안전하지 않지만, 이를 대체하는 새로운 형태의 컨테이너(array)가 정의되었다.

  > **C++ array 표준 라이브러리 : 범위를 벗어난 메모리 작업의 위험이 없는 배열 타입**

- std::array가 도입되기 전에는 std::vector를 사용해야 했지만, std::array는 std::vector와는 다르게 크기가 고정되어 있어 새로운 항목을 추가하거나 삭제할 수는 없지만 **오버헤드가 적은 장점**이 있다.

- std::array는 배열의 크기를 항상 정확히 알 수 있고, 포인터가 자동으로 잘못 타입 캐스팅되는 것도 피할 수 있다.

- C++ STL의 iterator를 활용하여 항목을 순회하거나 STL 알고리즘 사용 가능

```c++
#include <array>

int main(){
    std::array<int, 5> ia; // int형 타입의 array 5개를 선언
    std::cout<<sizeof(ia); // 20byte가 출력된다.
}
```

