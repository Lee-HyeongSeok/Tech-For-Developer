## C++ In-Depth: Cmake

***

<br>

### :pushpin: CMake란?

- ```Makefile```은 간단한 프로젝트를 관리하기 좋지만, 프로젝트 크기가 커질 경우 또는 해당 프로젝트를 여러 플랫폼에서 배포하기 위해서는 불편한 점이 많다.

- 이러한 문제를 해결하기 위해 자주 사용하는 프로그램이 ```CMake```이다.

- 빌드 파일을 생성해주는 프로그램

  :point_right: **CMake를 통해서 빌드 파일을 생성하면** 빌드 프로그램을 통해 프로젝트를 빌드하는 것

- 예를 들어 ```make```를 사용한다면 ```CMake```를 통해 ```Makefile```을 생성할 것이고, ```Ninja```를 사용한다면 ```CMake```를 통해서 ```.ninja``` 빌드 파일을 만들어줄 것이다.

  > ```Ninja``` : 빌드 시스템

<br>

### :pushpin: CMake 개요

- CMake를 사용하는 모든 프로젝트에서는 반드시 프로젝트 최상위 디렉토리에 CMakeLists.txt 파일이 있어야 한다.
- 해당 파일에는 CMake가 빌드 파일을 생성하는데 필요한 정보들이 들어있다.

![캡처](https://user-images.githubusercontent.com/55940552/153751326-83e75ee9-78e0-47e0-ae72-1b6300c76bf9.PNG)

위 그림은 보통의 컴파일 과정을 그린 것이다.

```CMake```가 ```CMakeLists.txt```의 내용을 통해 ```Makefile```을 생성하고, 빌드 프로그램인 ```make```를 통해 컴파일 한다.

물론 꼭 ```Makefile```을 만들 필요는 없고 원하는 빌드 프로그램을 선택할 수 있다.

최상위 ```CMakeLists.txt```에는 반드시 아래 두 개의 내용이 들어가야 한다.

```cmake
# 1. CMake 프로그램의 최소 버전
cmake_minimun_required(VERSION 3.11)

# 2. 프로젝트 정보
project(
	ModooCode
	VERSION 0.1
	DESCRIPTION "exam project"
	LANGUAGES CSS
)
```

```CMakeLists.txt``` 최상단에는 해당 프로젝트에서 사용할 ```CMake```의 최소 버전을 명시해준다.

```CMake```는 버전에 따라 차이가 크기 때문에 옛날 버전의 ```CMake```를 사용할 경우 지원하지 않는 기능이 있을 수도 있다.



```cmake
# 2. 프로젝트 정보
project(
	ModooCode
	VERSION 0.1
	DESCRIPTION "exam project"
	LANGUAGES CSS
)
```

위에서 꼭 필요한 것은 프로젝트 이름(ModooCode 부분)이고, 나머지 정보는 없어도 된다.

LANGUAGES 부분은 C 프로젝트면 C, C++ 프로젝트면 CXX를 명시하면 된다. 만약 명시하지 않았을 경우 디폴트로 C와 CXX가 설정된다.

그 외에도 CUDA, OBJC, OBJCXX, Fortran 등등이 가능하다.

<br>

### :pushpin: 실행 파일 만들기

```c++
#include <iostream>
using namespace std;

int main(){
    cout<<"Hello, Cmake"<<endl;
    return 0;
}
```

위 내용을 main.cpp에 저장

```cmake
cmake_minimun_required(VERSION 3.11)

project(
	ModooCode
	VERSION 0.1
	DESCRIPTION "exam project"
	LANGUAGES CXX
)
add_executable (program main.cpp)
```

위 내용으로 CMakeLists.txt를 생성, 이때 두 파일은 같은 경로에 있어야 한다.

```add_executable``` 명령은 생성할 실행 파일을 추가하는 명령으로 원본 형태는

```add_executable(<실행 파일 이름> <소스1> <소스2>...<소스n>)```의 형태이다.

생성하고자 하는 실행 파일 이름을 적은 뒤에, 그 뒤로 해당 실행 파일을 만드는데 필요한 소스들을 나열한다.



이제 빌드 파일 생성, 

CMake에서 권장하는 방법은 빌드 파일과 작업하는 디렉토리 서로 다른 디렉토리에서 만드는 것

하나의 디렉토리에 ```CMakeLists.txt```와 ```main.cpp```, ```build``` 디렉토리가 존재

```build``` 디렉토리에 들어가서 ```cmake ..```을 실행한다

:point_right: CMake를 실행할 때는 최상위 CMakeLists.txt가 위치한 폴더의 경로를 입력해야 하는데, 바로 부모 디렉토리에 있으므로 ```..```을 사용하는 것



이후 CMake에서 여러 설정들을 체크한 뒤에 빌드 파일을 생성한다.

그리고 build 디렉토리 안에 여러 폴더와 파일들이 생성된 것을 볼 수 있다.

**반드시 빌드 파일 용 디렉토리를 생성한 후에 해당 디렉토리에서 CMake를 실행해야 한다.**

:point_right: CMake는 실행 시 여러가지 파일들(캐시 용도)을 생성하는데 이 때문에 프로젝트 디렉토리가 난장판이 되거나 이미 있는 파일을 덮어 씌운다.



이제 build 디렉토리에서 ```make```를 실행하면 여러 파일들이 나오는데 ```program```이라는 이름의 실행 파일이 생성된 것을볼 수 있다.



만약 실행 파일을 만드는데 필요한 소스 파일이 여러 개일 때

```c++
// foo.h
int foo();
```

```c++
// foo.cpp
#include "foo.h"
int foo(){ return 3; }
```

```c++
#include <iostream>
#include "foo.h"

int main(){
    cout<<"Foo : "<<foo()<<endl;
    return 0;
}
```

컴파일에 필요한 소스 파일들이 ```main.cpp```, ```foo.cpp``` 이므로, add_executable을

```cmake
add_executable(program main.cpp foo.cpp)
```

로 수정하면 된다.



위와 같이 수정한 후에는 ```cmake ..```를 통해서 다시 Makefile을 생성해야 한다.

:point_right: ```CMakeLists.txt```를 바꾸었지만 ```Makefile```을 바꾼 것은 아니기 때문에 오류 발생

<br>

### :pushpin: 컴파일 옵션 지정하기

- ```target_compile_options``` 명령 사용
- ```target_compile_options(<실행 파일 이름> PUBLIC <컴파일 옵션1> <컴파일 옵션2> ...)``` 형태

예를 들어

```target_compile_options(program PUBLIC -Wall -Werror)```의 경우

빌드할 때 컴파일 옵션으로 ```-Wall(모든 경고 표시)``` ```-Werror(경고는 컴파일 오류로 간주)```을 부여한다는 의미

```PUBLIC```은 실행 파일을 빌드할 때에는 중요하지 않다.

<br>

### :pushpin: CMake에서의 기본 개념 Target과 Property

- CMake에서 말하는 타겟(Target)이란?
  - 프로그램을 구성하는 요소들
  - 실행 파일, 라이브러리 파일 등
- CMake의 모든 명령들은 이 타겟들을 기준으로 돌아간다.
- 각 타겟에는 **속성(Property)**을 정의할 수 있다
  - 위와 같이 컴파일 옵션을 주는 것도 program이라는 타겟에 컴파일 속성을 설정하는 것
  - 어떤 라이브러리를 링크하는 것인지, include하는 파일은 어디서 보는지 등의 여러 속성 정의 가능

<br>

### :pushpin: include 경로 지정하기

- CMake에서는 컴파일 시에 헤더 파일들을 찾을 경로의 위치 지정 가능
- 보통 컴파일러의 경로 탐색
  - ```#include <>``` : include 되는 헤더 파일들을 시스템 경로에서 찾는다.
  - ```#include ""``` : include 되는 헤더 파일들을 따로 지정하지 않는 이상 현재 코드의 위치를 기준으로 찾는다.
- 경우에 따라 헤더 파일들을 다른 곳에 위치시키는 경우, 컴파일러가 해당 파일들을 찾기 위해서는 컴파일 시에 따로 경로를 지정해줘야 한다.
- ```target_include_directories(program PUBLIC ${CMAKE_SOURCE_DIR}/includes)``` 명령
  -  ```CMakeLists.txt```에 ```includes``` 디렉토리를 헤더 파일 경로 탐색 시 확인하라고 알려줘야 한다.
  - ```$(CMAKE_SOURCE_DIR)```은 CMake에서 기본으로 제공하는 변수, 최상위 ```CMakeLists.txt```의 경로를 의미(프로젝트의 경로)
- 원본은 ```target_include_directories(<실행 파일 이름> PUBLIC <경로1> <경로2> ...)``` 와 같다.

:round_pushpin: 중요한 점

```CMake```에서 디렉토리 경로 지정 시 왠만하면 절대 경로를 쓰지 않는 것이 좋다.

:point_right: CMake의 가장 큰 장점은 여러 플랫폼에서 사용할 수 있다는 것이지만, 절대 경로를 사용하게 된다면 다른 시스템에서 사용할 수 없기 때문

<br>

### :pushpin: 라이브러리 만들기

![캡처](https://user-images.githubusercontent.com/55940552/153753743-3c8d9872-b338-46c0-8818-7ee1fe8ab55e.PNG) 

위와 같은 프로젝트를 빌드 하기 위해서는

1. 외부 라이브러리들이 잘 설치되어 있는지 확인
2. 라이브러리 1과 라이브러리 2가 각각에 맞는 외부 라이브러리들을 참조할 수 있도록 설정
3. 실행 파일을 만들 때 라이브러리 1과 2를 사용하도록 해야 한다.



간단한 라이브러리 생성

```c++
// 사용할 라이브러리는 프로젝트의 lib 폴더 안에 생성
// lib/shape.cpp
#include "shape.h"
Rectangle::Rectangle(int width, int height) : width_(width), height(height){}
int Rectangle::GetSize() const{ return Width_ * height_; }
```

```c++
// 헤더 파일은 includes 폴더 안에 정의
// includes/shape.h
class Rectangle{
    public:
    Rectangle(int width, int height);
    int GetSize() const;
    private:
    int width_, height_;
};
```

C++ 라이브러리는 헤더와 소스를 따로 분리하는데, 라이브러리를 사용할 경우 라이브러리의 구현 부분을 참조할 필요는 없지만 헤더는 꼭 참조해야 하기 때문

:point_right: 따라서 구현 부분을 ```lib``` 안에, 헤더 파일은 ```includes``` 에 따로 분리



이제 해당 라이브러리를 어떻게 빌드 할지 알려주는 ```CMakeLists.txt```를 작성해야 한다.

shape 라이브러리는 ```/lib``` 내부에 구현되어 있으므로 해당 위치에 ```CMakeLists.txt```를 새로 만들어준다.

```cmake
# /lib/CMakeLists.txt

# 정적 라이브러리 shape를 만든다.
add_library(shape STATIC shape.cpp)

# 해당 라이브러리 컴파일 시 사용할 헤더 파일 경로
target_include_directories(shape PUBLIC ${CMAKE_SOURCE_DIR}/includes)

# 해당 라이브러리를 컴파일 할 옵션
target_compile_options(shape PRIVATE -Wall -Werror)
```

**[add_library 사용법]**

```add_library(<라이브러리 이름> [STATIC | SHARED | MODULE] <소스 1> <소스 2> ...)```

STATIC : 정적 라이브러리 생성

SHARED : 동적으로 링크되는 동적 라이브러리 생성

MODULE : 동적으로 링크되지는 않지만, dlopen과 같은 함수로 런타임 시에 불러올 수 있는 라이브러리 생성



**[정적 & 동적 라이브러리]**

정적 라이브러리 : 필요로 하는 라이브러리가 링킹 이후에 완성된 프로그램 안에 포함된다, 실행 파일의 크기가 커지는 대신 동적 라이브러리를 사용할 때보다 더 빠르다.

동적 라이브러리 : 프로그램 실행 파일에 라이브러리가 포함되어 있는 것이 아니라 메모리에 라이브러리가 따로 적재되는데 이를 참조하는 형태

```cmake
target_include_directories(shape PUBLIC ${CMAKE_SOURCE_DIR}/includes)

target_compile_options(shape PRIVATE -Wall -Werror)
```

**[PUBLIC과 PRIVATE 차이점]**

CMake에서 A 라이브러리가 B 라이브러리를 사용한다면 A는 B의 컴파일 옵션들과 헤더 파일 탐색 디렉토리 목록을 물려받는다.

이 부분에서 ```PUBLIC```으로 설정된 것은 물려 받고, ```PRIVATE```으로 설정된 것은 물려 받지 않는다.



**[target_include_directories 의미 및 사용법]**

1. ```shape```를 컴파일 할 때 헤더 파일 탐색 경로에 ```${CMAKE_SOURCE_DIR}/includes```를 추가해달라는 의미
2. ```shape```를 참조 하는 타겟의 헤더 파일 검색 경로에 ```${CMAKE_SOURCE_DIR}/includes``` 를 추가해달라는 의미

즉 위에서 보았던 ```program(타겟)```이 ```shape```를 사용한다면, ```program```을 컴파일 할 때 파일 탐색 경로에 ```${CMAKE_SOURCE_DIR}/includes```가 자동으로 추가된다.



**[target_compile_options 의미 및 사용법]**

1. ```PRIVATE```으로 설정되어 있다, 이유는 ```shape```를 빌드할 때 ```-Wall```과 ```-Werror``` 옵션을 사용하고 싶지만, ```shape```를 사용하는 소스 파일 또는 라이브러리들에게 이 옵션을 강제하고 싶지 않기 때문

<br>

### :pushpin: 라이브러리와 include 경로 지정을 사용한 CMake 수정

```cmake
# Cmake 프로그램의 최소 버전
cmake_minimum_required(VERSION 3.11)

# 프로젝트 정보
project(
	ModooCode
	VERSION 0.1
	DESCRIPTION "exam project"
	LANGUAGES CXX
)

# 확인할 디렉토리 추가
add_subdirectory(lib)
add_executable(program main.cpp)

# program에 shape를 링크
target_link_libraries(program shape)
```

먼저 ```add_subdirectory``` 명령을 통해 CMake가 추가로 확인해야 할 디렉토리 경로 지정

:point_right: CMake 실행 시, 해당 디렉토리 내부에 ```CMakeLists.txt```도 실행



```cmake
# program에 shape를 링크
target_link_libraries(program shape)
```

위와 같이 ```program```을 빌드할 때 ```shape``` 라이브러리를 링크 시켜 준다.

참고로 실행 파일은 private, public의 여부가 크게 중요하지 않다. 실행 파일을 다른 타겟이 참조할 수 없기 때문

그래서 ```program shape``` 까지만 ```target_link_libraries```에 기재하면 된다.



이후 ```cmake ..```를 실행하면 build 디렉토리에 ```libshape.a``` 파일이 생긴 것을 볼 수 있다.

CMake는 라이브러리를 만들게 되면 앞에 ```lib```를 붙인 라이브러리 파일을 생성한다.



### :pushpin: 현재의 CMake 패러다임은 타겟들을 기준으로 돌아간다.

> 꼭 ```target_*``` 형태의 명령을 사용해야 한다.



***

### 출처

[CMake 모두의 코드](https://modoocode.com/332)