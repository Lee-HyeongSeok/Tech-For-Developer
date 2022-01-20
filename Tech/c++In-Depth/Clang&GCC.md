## Clang&GCC

***

<br>

### :pushpin: GCC

- GNU 프로젝트의 프레웨어 컴파일러
- 본래 C언어 컴파일러로 시작, 2..9버전 이후로 Objective-C, Pascal, Ada와 같은 언어도 지원
- GNU/Linux부터 솔라리스 2, 윈도우즈 NT 등 많은 운영체제를 지원할 정도로 호환성이 좋음
- 자동 레지스터 할당, 반복 코드 제거, 상수 곱셈 최적화 등 매우 많은 최적화를 수행하는 컴파일러

<br>

### :pushpin: LLVM

- 프로그래밍 언어 컴파일러 집합

- 컴파일 시간, 런타임 시간 등 다양한 상황에서 최적화를 쉽게 구현할 수 있도록 구성

- LLVM 라이선스를 가지는 프론트 엔드를 위해 Clang이라는 프로젝트를 진행 중

- 언어에 가상 머신을 생성, 가상 머신은 특정 머신을 생성하고 언어와 플랫폼에 독립적인 최적화 실행(LLVM 문서 참조)

  > [LLVM Project](https://github.com/Lee-HyeongSeok/Tech-For-Developer/blob/master/Tech/c%2B%2BIn-Depth/LLVM%20project.md)

<br>

### :pushpin: Clang

- C, C++, Objective-C, Objective-C++ 프로그래밍 언어를 위한 컴파일러 프론트 엔드
- LLVM을 백 엔드로 사용하며 LLVM 2.6 이후로 릴리즈의 일부로 자리잡음
- GNU 컴파일러 모음(GCC)를 대체하기 위한 목적
- GCC 프론트 엔드보다 빠르고 메모리를 적게 사용
- 관리하기 쉬우며 사용자 친화적인 오류 메시지 송출
- 확장 및 사용이 쉬운 프론트 엔드 작성을 목표로 하는 컴파일러
- BSD 라이센스로 개발되고 있음

<br>

### :pushpin: Clang&GCC  difference

- 둘다 프론트 엔드 컴파일러가 고급 언어를 컴파일 하여 중간 언어(IR)로 번역, 이를 백 엔드 컴파일러가 기계어로 번역하는 과정을 거침
- 이 과정에서 생성되는 **중간 언어(IR)과 최적화 방법, 프로그래밍 언어와의 호환성**에서 차이가 발생