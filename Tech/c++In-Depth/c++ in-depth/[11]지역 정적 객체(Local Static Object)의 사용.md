## 지역 정적 객체(Local Static Object)의 사용

***

<br>

### :pushpin: 파일 스코프의 객체는 함수의 독립성을 해치고, 이해하기 복잡하게 만든다.

> **이 경우의 대안은 지역 정적 객체(Local Static Object)이다.**

- **정적 지역 변수로 된 메모리(static)** : 함수를 호출하고 난 후에도 계속 유지된다.

- 예시

  > ```c++
  > const vector<int>* fobon_seq(int size){
  >     static vector<int> elems; // 지역 정적 객체로 선언
  >     // ...
  >     
  >     return &elems;
  > }
  > ```
  >
  > :point_right: 비정적(nonstatic) 지역 변수와는 달리 함수를 호출하고 난 후에도 계속 유지
  >
  > :point_right: 안전하게 elems의 주소를 반환 가능

  



