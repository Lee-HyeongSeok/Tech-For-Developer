## 데이터 객체(data object)의 정의(definition)와 초기화

***

<br>

### :pushpin: 데이터 객체(data object) 정의

> **이름과 타입(type)이 필요**
>
> [1] **객체의 이름**은 객체를 직접 조회하는 데 사용된다.
>
> [2] **자료 타입**은 객체가 저장할 수 있는 값의 범위와 이 값들을 저장하기 위해 할당되어 지는 메모리의 크기를 결정한다.

- **이름 규칙**

  - 영문자, 숫자, 밑줄(under score)의 조합으로 이루어진다.

  - 영문자는 대소문자를 구분한다.

    > User_name, user_name, user_Name은 모두 다른 객체

  - 이름은 숫자로 시작 불가

    > name_1은 가능하지만 1_name은 불가능

  - C++언어의 키워드와 일치해서는 안된다.

    > delete는 키워드이므로 이름으로 사용 불가

<br>

### :pushpin: 객체의 선언과 초기화 방식

- 객체 선언 방식

  ```c++
  int num_right;
  ```

- 객체 초기화 방식

  ```c++
  int num_right=0;
  int num_tries(0);
  ```

  > int num_tries(0)과 같은 초기화 구문을 **생성자 구문(constructor syntax)**이라고 부른다.

<br>

### 왜 초기화 구문이 두 개 있을까?

> :point_right: 초기화를 위해 사용한 **대입(assignment) 연산자**는 C언어로부터 계승되어 왔다.
>
> - 기본 타입 객체 또는 string class에서 하나의 값으로 초기화되는 객체에서는 잘 동작한다.
>
>   > string sequence_name = "Fibonacci";
>
> :point_right: 하지만, 초기화를 위해 여러 개의 값이 필요한 클래스 객체의 경우는 동작하지 않는다.
>
> > #include <complex>
> >
> > complex<double> purei(0, 7);
>
> - 표준 라이브러리의 복소수(complex) 클래스로 실수부와 허수부를 나타내는 두 개의 초기값이 필요
> - complex 다음에 오는 부등호 표기는 template 클래스임을 나타낸다.

<br>

### :pushpin: 복소수(complex) 클래스

- 두 개의 멤버 객체를 갖는다.
  - 실수부
  - 허수부
- 해당 멤버들은 부동 소수점 실수 타입이 되어야 한다.
- C++은 세 가지 크기의 부동 소수점 실수를 지원한다.
  1. **단일 정밀도(single precision)** : float 키워드로 나타냄
  2. **2배 정밀도(double precision)** : double 키워드로 나타냄
  3. **확장 정밀도(extended precision)** : long double 키워드로 나타냄

<br>

