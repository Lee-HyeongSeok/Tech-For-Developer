## Lvalue, Rvalue 그리고 std::move

***

<br>

### :pushpin: Rvalue, Lvalue

> **Rvalue :** x, y처럼 이름을 가지고 있고, 그 이름으로 접근 가능한 것
>
> **Lvalue :** (x+y)나 상수 10, 20 등은 이름을 가지지 않고, 식 또는 연산이 끝난 후 다음 라인에서 그 값에 접근할 수 없는 것

```c++
int some_Rvalue(){ int z=30; return z; }
void some_func(){
    int x=10; // x는 Lvalue, 10은 Rvalue
    int y=20; // y는 Lvalue, 20은 Rvalue
    
    x=y; // x와 y모두 Lvalue
    x = (X+y); // x는 Lvalue, (x+y)는 Rvalue
    x = some_Rvalue(); // x는 Lvalue, some_Rvalue()는 Rvalue
}
```

- Rvalue를 함수의 매개변수로 받고 싶으면 \&&로 선언

```c++
class A;
// class A의 인스턴스를 Rvalue로 받고 싶을 때
void some_func(A&& rhs){ }
```

<br>

### :pushpin: std::move

> **Lvalue를 Rvalue로 casting해주는 함수**

```c++
class myClass{
    private:
    	std::string data;
    public:
    	myClass(){}
    	myClass(std::string data): this->data(data){ }
}
int main(void){
    myClass A("aaa");
    myClass B;
    myClass C;
    
    B=A; // 복사 생성자 발생(copy)
    C = std::move(A); // Lvalue인 A를 Rvalue로 casting(move)
}
```

- B=A일 때

  - 복사 생성자 발생
  - B.data에는 "aaa"가 복사되며 A.data도 여전히 "aaa"를 가지고 있다.

- C=std::move(A)일 때

  - A.data는 C.data로 이동되면서 A.data는 빈 문자열이 된다.

  - 새로 메모리를 할당하지 않아도 되며, 메모리에 할당된 것을 소유권만 C에게 넘겨주는 것

  - copy 동작보다 빠르다.

  - **move로 할당된 이후로는 A를 사용하지 못한다.**

    <br>

- **이동 생성자 예시**

```c++
#include <iostream>
#include <utility>
#include <string>

class myClass{
    std::string str1;
    std::string str2;
    // string 클래스 Rvalue를 인자로 받는 이동 복사 생성자
    myClass(std::string&& str1, std::string&& str2):str1(std::move(str1)), str2(std::move(str2)){ }
    
    // 일반 클래스 Rvalue를 인자로 받는 이동 복사 생성자
    myClass(myClass&& rhs):str1(std::move(rhs.str1)), str2(std::move(rhs.str2)){ }
    
    void show_myClass(){
        std::cout<<str1<<", "<<str2<<std::endl;
    }
}

int main(void){
    std::string str1="aaa", str2="bbb";
    std::cout<<"show myClass A"<<std::endl;
    myClass myClassA(str1, str2); // myClass(std::string&&, std::string&&) 호출
    myClassA.show_myClass(); // aaa, bbb출력
    
    std::cout<<"show myClass B"<<std::endl;
    myClass myClassB(std::move(myClassA)); // myClass(myClass&&) 호출
    myClassA.show_myClass(); // , 출력
    myClassB.show_myClass(); // aaa, bbb 출력(myClassA의 인스턴스가 myClassB로 이동)
    
    std::cout<<"show myClass C"<<std::endl;
    myClass myClassC = std::move(myClassB); // myClass(myClass&&) 호출
    myClassA.show_myClass(); // , 출력
    myClassB.show_myClass(); // , 출력
    myClassC.show_myClass(); // aaa, bbb 출력
}
```

