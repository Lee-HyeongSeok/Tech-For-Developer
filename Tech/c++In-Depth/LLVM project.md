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

<br>

### :pushpin: LLVM 컴파일러 인프라 3단계 구조

![Untitled Diagram drawio](https://user-images.githubusercontent.com/55940552/150293127-aa6e6ec4-a15e-4967-a704-82546a411c06.png) 

> **이러한 구조로 인해 필요한 기능을 컴파일러에 쉽게 추가 가능**

- **핵심**
  - 구조적으로 소스(source)와 대상(target)으로부터 독립적인 최적화(optimizer) 기능을 제공한다
  - 프로그래밍 언어와 기계어 사이에서 **LLVM IR(Intermediate Representation)**이라는 중간 언어를 사용하고 있기 때문
  - 최적화(optimizer) 단계에서 오직 LLVM IR만을 처리하기 때문에 언어와 기계어로부터 완전히 독립적이고 투명하게 동작 가능
  - LLVM 컴파일러 인프라는 GCC, MSVC(Microsoft compiler)에도 호환, LLVM 기반의 여러 개발 환경 지원 가능
- **하위 프로젝트**
  - LLVM 컴파일러 인프라는 GCC 프론트 엔드를 대체해 **C/C++ 형식의 언어를 지원하기 위해서** Clang이라는 하위 프로젝트를 포함하고 있다.

<br>

### :pushpin: 오크(ORK)  프로젝트 : LLVM 컴파일러 인프라 기반 난독화 도구

- **LLVM 컴파일러 인프라를 기반**으로 구현한 공유 라이브러리
- 소스 코드는 LLVM 프로젝트와 분리(별도의 프로젝트에서 관리 중)
- **특징**
  - 매번 새로운 난독화 결과물 생성(난독화 생명 주기에서 가장 중요한 부분)
    - 모든 난독화 기능은 **원본 소스 코드의 내용, 컴파일 시점**에 따라 임의의 분기와 변수, 조건으로 LLVM IR을 변경하거나 추가하도록 설계
  - 기존 개발 환경과 쉽게 통합 가능
    - 기존 프로젝트의 컴파일 설정을 변경하지 않도록 독립적인 난독화 설정 기능 제공

<br>

### :pushpin: Clang 컴파일 과정

> **목표 : 각 컴파일 단계와 오크(ORK)가 어느 시점에 난독화를 수행하는지 확인**

- **처리 과정 핵심**

  - Clang은 컴파일러 드라이버

  - 먼저 실행되어 다른 컴파일러와 호환 가능한 설정으로 **프론트 엔드**와 **링커**를 실행

  - 일련의 **컴파일 과정** 처리

    > **이 과정에서 Clang은 C/C++ 형식의 언어를 지원하는 프론트 엔드 기능으로 실행됨**

    ```bash
    # -cc1 설정 추가 시 바로 프론트 엔드로 실행할 수 있다.
    clang -cc1 test.cpp
    
    # -### 설정 추가 시 프론트 엔드를 실행하기 위해 필요한 설정을 미리 확인 가능
    clang -### test.cpp
    ```

- **컴파일 단계**

  1. **전처리(preprocessor)**

     > 프론트 엔드가 가장 먼저 수행하는 작업,
     >
     > #include, #define 등을 확장하는 과정

     ```bash
     # -E 옵션을 사용하여 소스 코드의 전처리 결과 확인 가능
     clang -E test.cpp
     ```

     

  2. **구문 분석(parsing)**

     > [1] 입력된 소스 코드 **구문**과 **어휘** 분석
     >
     > [2] 분석된 내용을 추상 구문 트리(AST, Abstract Syntax Tree)의 자료 구조 형태로 저장
     >
     > [3] 컴파일 속도를 향상하기 위해 중복 참조되는 헤더, 모듈에 대한 **'미리 컴파일된 헤더(PCH, Precompiled headers)'** 또는 **'미리 컴파일된 모듈파일(PCM, Precompiled module files)'**을 생성

     ```bash
     # -emit-ast 옵션을 통해 확장자가 '.ast'인 AST 파일을 생성 가능
     clang -emit-ast test.cpp
     
     # -cc1 -ast-dump 옵션을 통해 생성되는 AST 파일의 정보 출력 가능
     clang -cc1 -ast-dump test.cpp
     
     # --precompile 옵션을 통해 이번 단계의 결과 출력 가능
     clang --precompile test.cpp
     ```

  3. **LLVM IR(Intermediate Representation) 생성**

     > [1] AST 형태로 저장된 소스 코드를 **최적화(optimizer)**하기 위해 **LLVM IR 형태로 변환**하는 단계
     >
     > [2] LLVM IR : 모든 고급 언어를 나타낼 수 있는 **표현 방식, 타입 확장, 타입 정보**를 제공하는 중간 언어

     - **LLVM의 최적화, 오크 난독화**
       - LLVM IR 분석, 생성, 수정, 삭제 과정을 통해 이루어짐
         - LLVM IR을 구성하는 모듈과 함수, 기본 블록, 명령어 등의 **구조적 측면**
         - 타입 요소, SSA(Static Single Assignment) 등과 같은 **기능적 측면**
     - **LLVM IR 표현 방식**
       1. LLVM 어셈블리어(사람이 읽을 수 있는 문자열로 표현)
          - LLVM IR을 해당 파일로 저장 시 **'.ll' 확장자**로 저장
       2. LLVM 비트코드(바이너리로 표현)
          - LLVM IR을 해당 파일로 저장 시 **'.bc' 확장자**로 저장

     ```bash
     # 해당 명령어를 통해 LLVM 어셈블리 언어를 컴파일 단계에서 저장 가능
     clang -S -emit-11vm test.cpp
     
     # 해당 명령어를 통해 LLVM 비트코드를 어셈블(assemble) 단계에서 저장할 수 있다.
     clang -c -emit-11vm test.cpp
     ```

     - **어셈블리 언어와 비트코드의 전환**
       - 서로 간에 자유롭게 전환 가능
         - LLVM 명령어 도구 **llvm-dis** : LLVM 비트코드 -> LLVM 어셈블리 언어로 전환
         - LLVM 명령어 도구 **llvm-as** : LLVM 어셈블리 언어 -> LLVM 비트코드
     - **LLVM IR의 최적화 및 특정 CPU 아키텍처에 해당하는 기계어 생성**
       - **opt 명령어**로 최적화
       - **11c 명령어**로 특정 CPU 아키텍처에 해당하는 기계어 생성

  4. **최적화**

     > [1] LLVM Pass 단위로 최적화 작업을 관리
     >
     > [2] LLVM Pass는 등록된 우선순위에 따라 순차적으로 LLVM IR을 전달 받음
     >
     > [3] 각 최적화 Pass는 전달 받은 LLVM IR을 최적화 한 뒤, 해당 IR을 다음 Pass로 전달

     ![캡처](https://user-images.githubusercontent.com/55940552/150342235-a3e2b136-74e5-4216-891f-2cc306e2144e.PNG) 

     - **난독화 Pass가 최적화 Pass에 영향받지 않게 하려면?**
       - 난독화하기 위해 추가한 가비지 코드, 정크 코드 또는 일부 난독화 로직이 다른 최적화 Pass에서 언제든 제거될 수 있다.
       - 이를 위해 난독화 코드가 외부에서 참조되는 것처럼 연결 속성(linkage type)을 지정하는 방법으로 최적화를 우회할 수 있게 고려해야 한다.
     - **한계점**
       - 소스 코드의 범위를 넘어서는 기능, 특정 CPU 아키텍처에 밀접한 기능 구현 불가
     - **장점**
       - LLVM 최적화와 동일하게, 프로그래밍 언어와 기계어에 독립적인 난독화 기능을 제공

     ```bash
     # 해당 명령어를 통해 각 Pass에서 수정된 LLVM IR을 출력 가능
     opt -O3 -print-after-all test.ll
     ```

     

  5. **컴파일러 백 엔드**

     > [1] 최적화된 **LLVM IR을** 특정 CPU 아키텍처에 의존적인 **어셈블리어**로 변환

     ```bash
     # 확장자가 '.s'인 어셈블리어 파일을 저장 가능
     clang -S test.cpp
     ```

     

  6. **어셈블러(assembler)**

     > [1] 어셈블리어를 기계어로 변경하여 확장자가 '.o'인 오브젝트 파일로 저장
     >
     > [2] Clang은 기본적으로 내부에 통합된 어셈블러를 사용
     >
     > [3] 설정을 통해 GNU 어셈블러와 같은 외부 도구 사용 가능

     ```bash
     # 확장자가 '.o'인 오브젝트 파일로 저장
     clang -c test.cpp
     ```

     

  7. **링커(linker)**

     > [1] 참조 관계를 확인
     >
     > [2] 저장된 오브젝트 파일들을 하나로 묶어서 **실행 파일** 또는 **공유 라이브러리 파일**을 생성
     >
     > [3] **링크 시점 최적화(LTO, Link Time Optimizer)**도 수행 가능

     - **호스트 시스템의 링커 외 또 다른 링커**
       - LLVM의 자체 링커 프로젝트 : LLD

***

<br>

### :round_pushpin: 자료 출처

[출처1 : 티스토리](https://zeddios.tistory.com/1175)

[출처2 : 티스토리](https://engineering.linecorp.com/ko/blog/code-obfuscation-compiler-tool-ork-1/)