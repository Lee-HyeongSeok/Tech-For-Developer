## C++ In-Depth: Makefile

***

<br>

### :pushpin: C 프로그램 빌드 절차

- 컴파일(compile) : 각 **source file**을 컴파일하여 **object file(*.o)**을 생성
- 링크(link) : 컴파일 과정에서의 **object file(*.o)**들을 묶는 과정, 실행 파일인 **(*.out)**을 생성
  - 해당 과정에서 **source file**에 정의된 함수를 **main**에서 호출하는 의존성 존재

![1](https://user-images.githubusercontent.com/55940552/150473400-2a3b6ba2-d7cb-4dec-adf9-fd3111d21742.PNG) 

- a.c 내용

```c
#include <stdio.h>

void foo(){ printf("foo\n"); }
```

- a.h 내용

```c
void foo();
```

- b.c 내용

```c
#include <stdio.h>

void bar(){ printf("bar\n"); }
```

- b.h 내용

```c
void bar();
```

- main.c

```c
#include "a.h"
#include "b.h"

int main(){
    foo();
    bar();
    return 0;
}
```

<br>

### :pushpin: C 프로그램 절차

1. 각 source file을 컴파일하여 object file로 변환

```bash
# 헤더 파일들은 main.c에 포함되어 있으므로 명시해주지 않아도 된다.
# -c 옵션 : 링크하지 않고 컴파일만 하겠다는 것을 의미
gcc -c -o a.o a.c
gcc -c -o b.o b.c
gcc -c -o main.o main.c
```

2. 실행 파일 생성(링크) : object 파일들을 묶는다.

```bash
# 내부적으로 링커를 실행, 실행파일(a.out)을 생성
# main.o a.o b.o를 묶어서 실행파일 a.out을 생성
gcc -o a.out main.o a.o b.o
```

<br>

### :pushpin: Makefile을 사용하는 이유

- 위와 같은 복잡한 과정을 생략 가능

- Makefile이 제공하는 강력한 기능 중 하나인 **Incremental build**를 사용하기 위함

  - **Incremental build란?**

    - 반복적인 빌드 과정에서 변경된 소스코드에 의존성이 있는 대상들만 추려서 다시 빌드하는 기능

      > ex) 위 빌드 예제에서 main.c의 한 줄만 바꾸고 재빌드를 시도하면 main.o 컴파일과 app.out 링크만 수행하는 경우
      >
      > ```bash
      > gcc -c -o main.o main.c
      > gcc -o a.out main.o a.o b.o
      > ```

<br>

### :pushpin: Makefile 구조

- **대상(Target)**
  - 빌드 대상 이름, 명령에 의해 생성되는 결과 파일, 오브젝트 파일 또는 실행 파일
- **의존 관계(Dependency)**
  - 대상을 만들때 의존되는 파일들, 여기에 나열된 대상들을 먼저 만들고 빌드 대상을 생성
- **명령(Recipe)**
  - 빌드 대상을 생성하는 명령
  - 여러 줄로 작성 가능
  - 쉘에서 쓸 수 있느 명령을 사용 가능
  - 명령 작성 시 반드시 tab키로 띄운 후 작성할 것

```bash
<target> : <dependency>
(tab)<Recipe>
```

<br>

### :pushpin: Makefile 작성

```bash
a.out : a.o b.o main.o
	gcc -o a.out a.o b.o main.o
	
a.o : a.c
	gcc -c -o a.o a.c

b.o : b.c
	gcc -c -o b.o b.c

main.o : main.c
	gcc -c -o main.o main.c

clean : 
	rm *.o a.out
```

<br>

### :pushpin: Makefile 실행

```bash
make # make 명령어로 Makefile 실행

make clean # make clean 명령어로 make명령으로 인해 생성된 .o 파일과 .out 파일을 삭제
```

<br>

### :pushpin: Makefile 변수 사용

```bash
CC=gcc # CC : 컴파일러
CFLAGS=-g -Wall # CFLAGS : 컴파일 옵션
TARGET=a.out # TARGET : 빌드 대상(실행 파일) 이름
OBJS=a.o b.o main.o # OBJS : 중간 산물, object 파일 목록

$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS) # $@ : 현재 Target 이름
	
a.o : a.c
	$(CC) -c -o a.o a.c
b.o : b.c
	$(CC) -c -o b.o b.c
main.o : main.c
	$(CC) -c -o main.o main.c

clean:
	rm $(OBJECT) $(TARGET)
```

- **내장 변수**
  - **CC** : 컴파일러
  - **CFLAGS** : 컴파일 옵션
  - **OBJS** : 중간 산물, Object 파일 목록
  - **TARGET** : 빌드 대상(실행 파일) 이름
  - **LDFLAGS** : 링커 옵션
  - **LDLIBS** : 링크 라이브러리

- **자동 변수**(확장성을 용이하게 해줌)
  - **$@** : 현재 Target 이름
  - **$^** : 현재 Target이 의존하는 대상들의 전체 목록
  - **$?** : 현재 Target이 의존하는 대상들 중 변경된 것들의 목록
  - **$%** : 대상의 이름(해당 규칙 대상이 아카이브인 경우)
- **Makefile 기본 패턴**

```bash
CC=<컴파일러>
CFLAGS=<컴파일 옵션>
LDFLAGS=<링크 옵션>
LDLIBS=<링크 라이브러리 목록>
OBJS=<Object 파일 목록>
TARGET=<빌드 대상 이름>

all: $(TARGET)

clean:
	rm -f *.o
	rm -f $(TARGET)
$(TARGET): $(OBJS)
$(CC) -o $@ $(OBJS)
```

<br>

### :pushpin: Clang++ 컴파일러, 하나의 test.cpp을 대상으로 한 Makefile

```bash
CC=clang++
CFLAGS= -m64 -std=c++1z -stdlib=libstdc++
TARGET=test.out
OBJS=test.o

$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS)
test.o: test.cpp
	$(CC) -c -o test.o test.cpp
clean:
	rm -f *.o
	rm -f $(TARGET)
```



***

<br>

### :round_pushpin: 출처

[[1] 블로그](https://velog.io/@hidaehyunlee/Makefile-%EB%A7%8C%EB%93%A4%EA%B8%B0)

