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

- LLVM을 위한 C 프론트 엔드
- GCC 프론트 엔드보다 빠르고 메모리를 적게 사용
- 관리하기 쉬우며 사용자 친화적인 오류 메시지 송출
- 확장 및 사용이 쉬운 프론트 엔드 작성을 목표로 하는 컴파일러
- BSD 라이센스로 개발되고 있음

<br>

### :pushpin: Clang&GCC  difference

- 