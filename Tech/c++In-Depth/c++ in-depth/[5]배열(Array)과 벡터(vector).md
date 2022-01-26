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