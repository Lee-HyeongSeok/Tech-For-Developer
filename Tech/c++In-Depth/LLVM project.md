## LLVM project

***

<br>

### :pushpin: LLVM(Low Level Virtual Machine)

- modular
- 재사용 가능한 컴파일러(Reusable Compiler)
- Tool Chain 기술의 집합체
- 즉, 컴파일러이자 툴킷

<br>

### :pushpin: LLVM의 서브 프로젝트

- LLVM Core
- Clang
- LLDB 등

<br>

### :pushpin: LLVM의 역할

- 중간 또는 이진 기계 코드를 구성, 최적화 및 생성하는데 사용되는 라이브러리
- 고급 언어를 파싱하여 IR(Intermediate Representation)으로 만든다.

<br>

### :pushpin: LLVM 구성

![캡처](https://user-images.githubusercontent.com/55940552/150275154-e41b8176-d8c1-4576-82d3-24b15bb6102b.PNG) 

- 프론드 엔드
  - C++, C, Objective-C, Swift, Python, Ruby와 같은 고급 언어를 읽고 파싱
  - 파싱 후 해당 언어들은 IR(Intermediate Representation)이 된다.
- 백 엔드
  - 프론드 엔드 과정에서 생성된 IR로 최적화하고 타겟 머신에 맞는 기계어로 변환한다.

***

[출처: 티스토리](https://zeddios.tistory.com/1175)

