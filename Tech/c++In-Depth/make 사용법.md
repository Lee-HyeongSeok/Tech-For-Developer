## C++ In-Depth: CMake

***

<br>

### :pushpin: make 프로그램

- 어떤 파일들을 컴파일 하고, 어떤 방식으로 컴파일 할 지 직접 컴파일러에게 알려주는 것

- 프로젝트의 크기 증가, 파일 개수 증가 시 매번 명령어 작성 어려움

  :point_right: 리눅스 make 프로그램을 통해 Makefile을 읽어서 주어진 방식대로 명령어를 처리



<br>

### :pushpin: C 프로그램 빌드 절차

- 컴파일(compile) 

  - 각 **source file**을 컴파일하여 **object file(*.o)**을 생성

  - 개발자의 소스 코드를 컴퓨터가 이해할 수 있는 기계어로 변환하는 과정

    > ```bash
    > clang++ -c main.cpp
    > ```
    >
    > main.cpp을 컴파일 하기 위해서는 위와 같은 명령어를 수행하면 된다.
    >
    > clang++에 전달하는 ```-c``` 인자는 주어지는 파일을 컴파일 해서 목적 파일(object file)을 생성하라는 의미

- 링크(link) 
  
  - 컴파일 과정에서의 **object file(*.o)**들을 묶는 과정, 실행 파일인 **(*.out)**을 생성
  
  - 해당 과정에서 **source file**에 정의된 함수를 **main**에서 호출하는 의존성 존재(목적 파일을 하나로 합치는 과정)
  
    > ```bash
    > clang++ main.o foo.o bar.o -o main
    > ```
    >
    > ```-o ``` 옵션은 그 뒤에 링킹 후에 생성할 실행 파일 이름을 의미한다.
    >
    > 위 경우 ```main``` 이라는 실행 파일을 만들었고, 이를 따로 지정하지 않는다면 ```./a.out```이라는 파일을 디폴트로 생성하게 된다.

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
    
  - 왜 쉘 스크립트를 사용하지 않는가?
  
    :point_right: 쉘 스크립트는 모든 명령어를 재수행 하기 때문에 재컴파일이 필요 없는 부분도 하게 된다.
  
    :point_right: 이는 컴파일 시간을 증가 시킨다.

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
  
    > ```Tab```이 ```Spacebar```로 바뀌었기 때문
    >
    > ```Spacebar```로 간격을 띄우면 실행되지 않는다.

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

### :pushpin: Makefile 변수

```bash
CC=gcc # CC : 컴파일러
CXXFLAGS=-g -Wall # CFLAGS : 컴파일 옵션
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
	rm $(OBJS) $(TARGET)
```

- **내장 변수**
  - **CC** : 컴파일러
  - **CFLAGS** : 컴파일 옵션(C의 경우)
  - **CXXFLAGS** : 컴파일 옵션(C++의 경우)
  - **OBJS** : 중간 산물, Object 파일 목록
  - **TARGET** : 빌드 대상(실행 파일) 이름
  - **LDFLAGS** : 링커 옵션
- **LDLIBS** : 링크 라이브러리
  
- **자동 변수**(확장성을 용이하게 해줌)
  
  - **$@** : 현재 Target 이름
  - **$^** : 현재 Target이 의존하는 대상들의 전체 목록
  - **$?** : 현재 Target이 의존하는 대상들 중 변경된 것들의 목록
  - **$%** : 대상의 이름(해당 규칙 대상이 아카이브인 경우)
  
- **변수를 정의하는 방법**

  - ```=```를 사용해서 정의하는 방법

    > ```=```를 사용해서 변수를 정의했을 때, 정의에 다른 변수가 포함되어 있다면
    >
    > 해당 변수가 정의될 때까지 변수의 값이 정해지지 않는다.
    >
    > ```bash
    > B=$(A)
    > C=$(B)
    > A=a
    > ```
    >
    > ```B=```를 실행한 시점에서 ```A```가 정의되지 않았으므로 ```B```는 그냥 빈 문자열이 되어야 하지만 ```=```로 정의했기 때문에 ```A```가 실제로 정의될 때 까지 ```B```와 ```C```가 결정되지 않는다.
    >
    > 마지막에 ```A=a```를 통해 ```A```가 ```a```로 대응되어야 ```C```가 ```a```로 결정된다.

  - ```:=```를 사용해서 정의하는 방법

    > ```:=```를 사용해서 변수를 정의했을 때, 해당 시점에서의 변수 값만 확인한다.
    >
    > ```bash
    > B:=$(A)
    > A=a
    > ```
    >
    > ```B```는 빈 문자열이 된다.
    >
    > 대부분의 상황에서는 ```=```나 ```:=``` 중 아무거나 사용해도 상관없지만,
    >
    > 변수들의 정의 순서에 구애받고 싶지 않다면 ```=```를 사용하고
    >
    > ```A=```와 같이 자기 자신을 수정하고 싶다면 ```:=```를 사용해야 무한루프를 피할 수 있다.

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
CXXFLAGS= -m64 -std=c++1z -stdlib=libstdc++
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



<br>

### :pushpin: make의 작동 이해

```bash
a.o : a.h a.cpp
	clang++ -c a.cpp

b.o : b.h b.cpp
	clang++ -c b.cpp

main.o : main.cpp a.h b.h
	clang++ -c main.cpp
	
main : a.o b.o main.o
	clang++ a.o b.o main.o -o main

clean : 
	rm *.o
```

<br>

위 Makefile을 make하면 아래와 같은 명령어를 수행한다.

```bash
$ make main
clang++ -c a.cpp
clang++ -c b.cpp
clang++ -c main.cpp
clang++ a.o b.o main.o -o main
```

그리고 실제로 ```-o``` 인자 뒤에 이름으로 ```main``` 실행 파일이 생성된다.

한 번도 컴파일 하지 않은 상태에서 make main을 실행하면 make 파일은 다음과 같은 순서로 명령어를 처리한다.

1. ```make main``` 이므로 ```Makefile```에서 타겟이 ```main```인 것을 찾는다.
2. ```main```에 필요한 파일들이 ```a.o b.o main.o```임을 ```main: a.o b.o main.o```를 통해 확인하고 각 파일의 ```*.o``` 파일을 어떻게 생성하는지 타겟들을 찾는다.
3. ```a.o```의 경우 ```a.o : a.h a.cpp```를 통해 필요한 파일을 확인하고 주어진 명령어를 수행하여 ```a.o```를 생성한다.
4. 마찬가지로 ```b.o```와 ```main.o```도 컴파일 한다.
5. ```main``` 타겟을 생성하기 위해 필요한 파일들을 생성한 후 ```clang++ a.o b.o main.o -o main``` 명령어를 수행한다.

<br>

만약 make main을 한 번 실행한 상태에서 ```a.cpp```만 수정했을 때는 아래와 같이 필요한 부분만 재컴파일 된다.

1. ```make main```이므로 ```Makefile```에서 타겟이 ```main```인 것을 찾는다.
2. ```main```에 필요한 파일들이 ```a.o b.o main.o```임을 ```main: a.o b.o main.o```를 통해 확인하고 각 파일의 ```*.o``` 파일을 어떻게 생성하는지 타겟들을 찾는다.
3. ```a.o```의 경우 ```a.o : a.h a.cpp```을 통해 필요한 파일을 확인하는데, ```a.o```의 생성 시간보다 ```a.cpp```의 수정 시간이 더 나중임을 확인하고 주어진 명령어인 ```clang++ -c a.cpp```을 다시 실행한다.
4. ```b.o```의 경우 ```b.o : b.h b.cpp```을 통해 필요한 파일을 확인하는데, ```b.o```의 생성 시간보다 ```b.cpp```의 수정 시간이이전임을 확인하고(수정 후 컴파일을 통해 b.o가 생성되었으므로 생성 이후 수정되지 않았다는 뜻) 명령어를 재실행하지 않는다.
5. 다른 파일들도 생성 시간과 수정 시간을 확인하고 ```main```의 생성에 필요한 파일들 중 ```a.cpp```이 재컴파일 되며 ```a.o``` 또한 바뀌었기 때문에 ```main``` 생성 명령어도 재실행 한다.
6. 따라서 ```clang++ -c a.cpp```과 ```clang++ a.o b.o main.o -o main``` 명령어 만이 실행된다.

<br>

### :pushpin: PHONY

Makefile에 아래와 같이 ```clean``` 타겟과 빌드 관련된 파일들(*.o)을 제거하는 명령을 추가한다.

```bash
clean: 
	rm -f $(OBJS) main
```



이후 ```make clean``` 명령을 수행하면 빌드 관련 파일들인 ```*.o``` 파일들이 삭제되는 것을 볼 수 있다.

하지만 같은 디렉토리에 ```clean```이라는 파일이 존재하고, ```make clean```을 실행 시키면

```make```는 ```clean```의 필요 파일들이 없는데, ```clean``` 파일이 있으니까 ```clean``` 파일은 항상 최신임을 확인하고 ```rm -f $(OBJS) main``` 명령어를 실행시키지 않는다. :point_right: ```make clean``` 명령을 무시한다.

```bash
$ make clean
make: 'clean' is up to date.
```

```make clean``` 명령을 수행했지만, 같은 디렉토리 내에 clean 파일이 있기 때문에 ```make: 'clean' up to date.```와 같은 메시지를 출력한다.



이러한 상황을 막기 위해서는 ```clean```을 ```PHONY```로 등록하면 된다.

```bash
.PHONY: clean
clean: 
	rm -f $(OBJS) main
```

```make clean```을 수행하게 되면 ```clean``` 파일의 유무와 상관 없이 언제나 해당 타겟의 명령을 실행하게 된다.

<br>

### :pushpin: 패턴 사용하기

실제 프로젝트에서는 수십~수백 개의 파일들을 다룬다.

각 파일들에 대해 빌드 방식을 명시한다면 Makefile의 크기가 증가한다.

Makefile에서는 패턴 매칭을 통해 특정 조건에 부합하는 파일들에 대해서 간단하게 ```recipe```를 작성할 수 있게 한다.

```bash
a.o : a.h a.cpp
    	$(CC) $(CXXFLAGS) -c a.cpp
b.o : b.h b.cpp
    	$(CC) $(CXXFLAGS) -c b.cpp
```

위 두 명령어를 하나로 간단하게 나타내려면 아래와 같이 패턴을 작성한다.

```bash
%.o : %.h %.cpp
	$(CC) $(CXXFLAGS) -c $<
```

```%.o```는 ```.o```로 끝나는 파일 이름들이 타겟이 됨을 의미한다.

예를 들어 ```a.o```가 타겟이라면 ```%```에는 ```a```가 들어갈 것이고 아래와 같이 대입된다.

```bash
a.o : a.h a.cpp
	$(CC) $(CXXFLAGS) -c $<
```



패턴은 타겟과 ```prerequisite``` 부분에만 사용 가능하다. 즉 ```a.o : a.h a.cpp``` 부분에만 사용 가능한 것

밑에 ```recipe```인 ```$(CC) $(CXXFLAGS) -c $<``` 부분에 ```a.cpp```을 전달할 경우 Makefile의 자동 변수를 사용해야 한다.

```$<```의 경우 ```prerequisite``` 에서 첫 번째 파일의 이름에 대응되어 있는 변수이다.

```bash
a.o : a.cpp a.h
	$(CC) $(CXXFLAGS) -c $<
```

의 경우 ```$<```는 ```a.cpp```이 된다.



Makefile에서 제공하는 자동 변수

1. ```$@``` : 타겟 이름에 대응된다.
2. ```$<``` : 의존 파일 목록에 첫 번째 파일에 대응된다.
3. ```$^``` : 의존 파일 목록 전체에 대응된다.
4. ```$?``` : 타겟보다 최신인 의존 파일들에 대응된다.
5. ```$+``` : 중복된 파일 이름들 까지 모두 포함된다.

<br>

### :pushpin: 자동으로 prerequisite 만들기

컴파일 시에 ```-MD``` 옵션을 추가해서 컴파일 한다.

```bash
clang++ -c -MD main.cpp
```

그렇다면 ```main.d``` 라는 파일을 생성, ```main.d``` 파일 내용을 보면

```main.o: main.cpp /usr/include/stdc-predef.h a.h b.h``` 를 확인할 수 있다.

Makefile의 ```target: prerequisite``` 인것 같은 부분을 생성하였다.

컴파일 시에 ```-MD``` 옵션을 추가해주면, 목적 파일 말고도 컴파일 한 소스파일을 타겟으로 하는 의존파일 목록을 담은 파일을 생성해준다.

```stdc-predef.h``` 파일은 컴파일러가 컴파일 할 때 암묵적으로 참조하는 헤더 파일이다.



:point_right: ```main.d```를 Makefile에 포함하여 작성

```bash
CC=clang++
CXXFLAGS= -Wall -02
OBJS=a.o b.o main.o

%.o: %.cpp %.h
	$(CC) $(CXXFLAGS) -c $<

main : $(OBJS)
	$(CC) $(CXXFLAGS) $(OBJS) -o main
	
.PHONY : clean
clean:
	rm -f $(OBJS) main
	
include main.d
```

```include main.d```는 ```main.d```라는 파일의 내용을 Makefile에 포함하라는 의미

```bash
%.o : %.cpp %.h
	$(CC) $(CXXFLAGS) -c $<
```

부분을 컴파일러가 생성한 ```.d``` 파일로 대체할 수 있는가?

```bash
CC=clang++
CXXFLAGS= -Wall -02
OBJS= a.o b.o main.o

%.o: %.cpp
	$(CC) $(CXXFLAGS) -c $<

main: $(OBJS)
	$(CC) $(CXXFLAGS) $(OBJS) -o main
	
.PHONY: clean
clean:
	rm -f $(OBJS) main
	
-include $(OBJS:.o=.d)
```

```$(OBJS:.o=.d)``` 부분은 ```OBJS```에서 ```.o```로 끝나는 부분을 ```.d```로 모두 대체하라는 의미

:point_right: 해당 부분은 ```-include a.d b.d main.d```가 된다.

```a.d```나 ```b.d```가 ```include```될 때 이미 있는 ```%.o: %.cpp```은 같은 타겟에 대해 여러 의존파일 목록들이 정해져 있다면 이는 make에 의해 모두 하나로 합쳐진다.

<br>

### :pushpin: Makefile 예제

![캡처](https://user-images.githubusercontent.com/55940552/153749466-bca79a19-ea0b-47b8-8001-f508eeb9ad90.PNG) 

이와 같은 구조에서 항상 사용할 수 있는 만능 Makefile은 아래와 같다.

```bash
# 컴파일러
CC=clang++

# C++ 컴파일러 옵션
CXXFLAGS=-Wall -02

#링커 옵션
LDFLAGS=

# 소스 파일 디렉토리
SRC_DIR=./src

# 오브젝트 파일 디렉토리
OBJ_DIR=./obj

# 생성하고자 하는 실행 파일 이름
TARGET=main

# make 할 소스 파일들
# wildcard로 SRC_DIR에서 *.cpp로 된 파일들 목록을 뽑아낸 뒤에 notdir로 파일 이름만 뽑아낸다.
# SRCS는 a.cpp b.cpp main.cpp이 된다.
SRCS=$(notdir $(wildcard $(SRC_DIR)/*.cpp))

# SRCS에서 .cpp로 끝나는 부분을 .o로 대체하라는 의미
OBJS=$(SRCS:.cpp=.o)

# OBJS 안에 object 파일들 이름 앞에 $(OBJ_DIR)/ 을 붙인다.
OBJECTS=$(patsubst %.o, $(OBJ_DIR)/%.o, $(OBJS))

# OBJECTS에서 .o로 끝나는 부분을 .d로 대체하라는 의미
DEPS=$(OBJECTS:.o=.d)

all: main

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CXXFLAGS) -c $< -o $@ -MD $(LDFLAGS)

$(TARGET): $(OBJECTS)
	$(CC) $(CXXFLAGS) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

.PHONY: clean all
clean:
	rm -f $(OBJECTS) $(DEPS) $(TARGET)

-include $(DEPS)
```



```wildcard```는 함수로 해당 조건에 맞는 파일들을 추출하는데

```a.cpp b.cpp main.cpp```이 있을 경우 ```$(wildcard $(SRC_DIR)/*.cpp)```의 실행 결과는 ```./src/a.cpp ./src/b.cpp ./src/main.cpp```이다.

그리고 위에서 경로를 제외한 파일 이름만 추출하기 위해 ```notdir``` 함수를 사용하여 앞에 오는 경로를 삭제하고 파일 이름만 깔끔하게 추출한다.



```OBJS```를 바탕으로 실제 ```.o``` 파일들의 경로를 만들어 낼 때

파일 이름 앞에 ```$(OBJ_DIR)/```을 붙여줘야 하기 때문에 ```patsubst``` 함수를 사용한다.

```OBJECTS=$(patsubst %.o, $(OBJ_DIR)/%.o, %(OBJS))``` 

```patsubst``` 함수는 ```$(patsubst 패턴, 치환 후 형태, 변수)```의 같은 꼴로 사용한다.

따라서 위에 경우 ```$(OBJS)``` 안에 있는 모든 ```%.o``` 패턴을 ```$(OBJ_DIR)/%.o``` 로 치환하라는 의미

결과적으로 ```./obj/a.o ./obj/b.o ./obj/main.o```가 들어가게 된다.

<br>

### :pushpin: 만약 헤더 파일들을 따로 분리한다면?

![캡처](https://user-images.githubusercontent.com/55940552/153749466-bca79a19-ea0b-47b8-8001-f508eeb9ad90.PNG) 

위 디렉토리 구조에서 tree 밑에 include 디렉토리 안에 ```a.h b.h``` 두 개의 헤더 파일이 존재한다면?

```bash
CC=clang++
CXXFLAGS=-Wall -02
LDFLAGS=
# 헤더 파일 경로 추가
INCLUDE=-Iinclude/
SRC_DIR=./src
OBJ_DIR=./obj
TARGET=main

SRCS=$(notdir $(wildcard $(SRC_DIR)/*.cpp))
OBJS=$(SRCS:.cpp=.o)
DEPS=$(SRCS:.cpp=.d)

OBJECTS=$(patsubst %.o, $(OBJ_DIR)/%.o, $(OBJS))
DEPS=$(OBJECTS:.o=.d)

all: main

# $(INCLUDE) 추가
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(CC) $(CXXFLAGS) $(INCLUDE) -c $< -o $@ -MD $(LDFLAGS)
	
$(TARGET) : $(OBJECTS)
	$(CC) $(CXXFLAGS) $(OBJECTS) -o $(TARGET) $(LDFLAGS)
	
.PHONY : clean all
clean:
	rm -f $(OBJECTS) $(DEPS) $(TARGET)
	
-include $(DEPS)
```



<br>

### :pushpin: 멀티 코어를 활용해서 Make 속도 향상

> 일반 ```make```를 실행하면 1 개의 스레드만 실행되어서 속도가 느리다.
>
> 인자로 ```-j``` 뒤에 몇 개의 스레드를 사용할 지 숫자를 적어서 전달하면 된다.

예를 들어

```bash
make -j8
```

을 실행하면 8개의 스레드에 나뉘어서 실행된다.

통상적으로 ```코어 개수 + 1``` 만큼의 스레드를 생성해서 수행시키는 것이 가장 속도가 빠르다.

만약 컴퓨터의 코어 개수를 모른다면 리눅스 터미널의 경우

```bash
make -j$(nproc)
```

으로 실행시키면 ```$(nproc)```이 알아서 내 컴퓨터의 현재 코어 개수로 치환된다.



***

<br>

### :round_pushpin: 출처

[[1] 블로그](https://velog.io/@hidaehyunlee/Makefile-%EB%A7%8C%EB%93%A4%EA%B8%B0)

[[2] 모두의 코드 - Cmake](https://modoocode.com/311)



