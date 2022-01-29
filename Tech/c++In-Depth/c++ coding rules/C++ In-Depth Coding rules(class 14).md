## C++ In-Depth Coding rules(class 14)

***

<br>

### :pushpin: 자원은 개체가 가지게끔 하라. RAII와 스마트 포인터를 활용하라

- **자원 획득은 초기화이다(Resource acquisition is initialization)**, C++ 설계 패턴중 하나인 키워드
- 직접 코딩할 필요 없이 컴파일러가 강력하고 자동화된 자원 관리 시스템을 지원함을 의미한다.
- 원시(Raw) 자원을 할당할 때는 자원을 소유하는 개체에 곧바로 전달하면 된다.
- 한 구문 내에서 하나 이상의 자원 할당을 해서는 안 된다.

<br>

### :pushpin: RAII의 예시

1. 동적 프로그래밍을 위해 new 연산자를 사용하여 힙 메모리에 할당 받는다.

2. 해당 메모리의 리소스를 개발자가 직접 관리하게 된다.

3. 개발자의 실수, Exception이 발생하는 등의 문제로 인해 할당 받은 메모리를 해제하지 못하고 Memory leak이 발생한다(mutex의 lock에서도 발생 가능)

4. 이런 문제들을 안전하게 관리하고자 **unique_ptr, shared_ptr, lock_guard** 등이 있다.

   > 해당 클래스들은 함수가 종료되면 무조건 실행하게 해준다.

5. 이러한 클래스들의 기능적인 부분을 RAII라고 부른다.

<br>

### :pushpin: C++ 스마트 포인터(smart pointer)

> **포인터처럼 동작하는 클래스 템플릿**
>
> :point_right: **사용이 끝난 메모리를 자동으로 해제**

- C++ 프로그램에서 new 연산자를 사용하여 동적으로 할당받은 메모리는, 반드시 delete 연산자를 사용하여 해제해야 한다.
- C++에서는 메모리 누수(Memory leak)로부터 프로그램의 안전성을 보장하기 위해 스마트 포인터를 제공하고 있다.

<br>

### :pushpin: 스마트 포인터의 동작

> **new 연산자가 반환하는 동적 할당된 메모리의 주소값을 스마트 포인터에 대입하면, 따로 메모리를 해제할 필요가 없어진다.**

- **new 연산자**를 사용해 **기본 포인터(raw pointer)**가 실제 메모리를 가리키도록 초기화한 후에, 기본 포인터를 스마트 포인터에 대입하여 사용
- 정의된 스마트 포인터의 수명이 다하면, 소멸자는 **delete 연산자**를 사용하여 할당된 메모리를 자동으로 해제

<br>

### :pushpin: 스마트 포인터의 종류(C++ 11 부터 제공)

1. std::unique_ptr
2. std::shared_ptr
3. std::weak_ptr
4. std::auto_ptr(C++11 표준부터 삭제되었다)

<br>

### :pushpin: std::unique_ptr이란?

- **하나의 스마트 포인터만이 특정 객체를 소유할 수 있도록**, 객체에 소유권 개념을 도입한 스마트 포인터

- 해당 객체의 소유권을 가지고 있을 때만, 소멸자가 해당 객체를 삭제할 수 있다.

- 보통의 C++ 객체에 대해 스마트 포인터가 필요한 상황에서는 주로 std::unique_ptr을 사용하면 된다.

- std::unique_ptr 인스턴스는 std::move() 멤버 함수를 통해 **소유권을 이전할 수 있지만, 복사 불가**

  >  :point_down: 소유권이 이전되면, 이전 std::unique_ptr 인스턴스는 더는 해당 객체를 소유하지 않게 재설정된다.
  >
  > ```c++
  > int *raw_ptr = new int[100]; // 기본 포인터 동적 할당
  > std::unique_ptr<int> u_ptr(raw_ptr); // int형 unique_ptr인 u_ptr을 선언하고 초기화
  > 
  > std::unique_ptr<int> new_u_ptr = std::move(u_ptr); // u_ptr에서 new_u_ptr로 소유권 이전
  > /* std::unique_ptr<int> new_u_ptr = u_ptr; 대입 연산자를 이용한 복사는 오류 발생 */
  > new_u_ptr.reset(); // new_u_ptr이 가리키는 메모리 영역 삭제
  > u_ptr.reset(); // u_ptr이 가리키는 메모리 영역 삭제
  > ```

- **C++14 이후부터 제공되는** make_unique() 함수를 사용하면 std::unique_ptr 인스턴스를 안전하게 생성 가능

  > [1] make_unique() 함수는 전달받은 인수를 사용해 지정된 타입의 객체를 생성하고, 생성된 객체를 가리키는 unique_ptr을 반환한다.
  >
  > [2] 이 함수를 사용하면, 예외 발생에 대해 안전하게 대처 가능(컴파일러에 의해 제어될 수 있는 자원 할당과 같은)
  >
  > ```c++
  > #include <iostream>
  > #include <memory>
  > #include <string>
  > using namespace std;
  > 
  > class Person{
  > private:
  >     string name;
  >     int age;
  > public:
  >     Person(const string& name, int age);
  >     ~Person(){ cout<<"destructor call"<<endl; }
  >     void ShowPersonInfo();
  > }
  > 
  > int main(void){
  >     /* [1] make_unique() 함수 : 전달받은 인수를 사용해 지정된 타입의 객체 생성 후, 생성된 객체를 가리키는 unique_ptr을 반환
  >        [2] 기본 포인터(raw pointer)와 달리 unique_ptr 인스턴스인 p_ptr은 사용이 끝난 후 delete 연산자를 사용하여 메모리를 해제할 필요가 없다.
  >     */
  >     unique_ptr<Person> p_ptr = make_unique<Person>("Lee", 26);
  >     p_ptr->ShowPersonInfo();
  >     return 0;
  > }
  > 
  > Person::Person(const string& name, int age){
  >     this->name = name;
  >     this->age = age;
  >     cout<<"constructor call"<<endl;
  > }
  > 
  > void Person::ShowPersonInfo(){ cout<<name<<age<<endl; }
  > ```

<br>

### :pushpin: std::shared_ptr이란?

- 하나의 특정 객체를 참조하는 스마트 포인터가 총 몇 개인지를 참조하는 스마트 포인터

  > **참조하고 있는 스마트 포인터의 개수를 참조 횟수(reference count)라고 한다.**

- **참조 횟수**는 특정 객체에 새로운 shared_ptr이 추가될 때마다 1씩 증가, 수명이 다할 때마다 1씩 감소

- 마지막 std::shared_ptr의 수명이 다하여, 참조 횟수가 0이 되면 delete 연산자를 사용하여 메모리를 자동으로 해제

  > ```c++
  > int *raw_ptr = new int[5]; // 기본 포인터 동적 할당 선언
  > 
  > std::shared_ptr<int> s_ptr(raw_ptr); // int형 shared_ptr인 s_ptr을 선언하고 초기화
  > cout<< s_ptr.use_count() <<endl; // 1
  > 
  > std::shared_ptr<int> new_s_ptr1(s_ptr); // 복사 생성자를 이용한 초기화
  > cout<< s_ptr.use_count() <<endl; // 2, 현재 s_ptr과 new_s_ptr1이 raw_ptr 리소스 참조 중
  > 
  > std::shared_ptr<int> new_s_ptr2(s_ptr); // 대입 연산자를 이용한 초기화
  > cout<< s_ptr.use_count() <<endl; // 3, 현재 s_ptr과 new_s_ptr1, new_s_ptr2가 raw_ptr 리소스 참조중
  > 
  > new_s_ptr2.reset(); // shared_ptr인 new_s_ptr2를 해제함.
  > cout<< s_ptr.use_count() <<endl; // 2, 현재 s_ptr, new_s_ptr1이 raw_ptr 리소스 참조중
  > ```
  >
  > :point_right: use_count() 멤버 함수는 shared_ptr 객체가 현재 가리키고 있는 리소스를 참조 중인 소유자의 수를 반환해준다.

- make_shared() 함수를 사용하면 shared_ptr 인스턴스를 안전하게 생성 가능

  > [1] make_shared() 함수는 전달받은 인수를 사용해 지정된 타입의 객체를 생성하고, 생성된 객체를 가리키는 std::shared_ptr을 반환한다.
  >
  > [2] 이 함수를 사용하면 예외 발생에 대해 안전하게 대처할 수 있다.
  >
  > ```c++
  > #include <iostream>
  > #include <memory>
  > #include <string>
  > using namespace std;
  > 
  > class Person{
  > private:
  >     string name;
  >     int age;
  > public:
  >     Person(const string& name, int age);
  >     ~Person(){ cout<<"destructor call"<<endl; }
  >     void ShowPersonInfo();
  > }
  > 
  > int main(void){
  >     shared_ptr<Person> origin_shared_ptr = make_shared<Person>("Lee", 26);
  >     cout<<"현재 Person(Lee, 26) 리소스 소유자 수 : "<<origin_shared_ptr.use_count()<<endl; // 1
  >     
  >     shared_ptr<Person> new_shared_ptr1(origin_shared_ptr); // 복사 생성자를 사용한 초기화
  >     cout<<"현재 Person(Lee, 26) 리소스 소유자 수 : "<<origin_shared_ptr.use_count()<<endl; // 2
  >     
  >     new_shared_ptr1.reset(); // shared_ptr인 new_shared_ptr1을 해제함.
  >     cout<<"현재 Person(Lee, 26) 리소스 소유자 수 : "<<origin_shared_ptr.use_count()<<endl;
  >     return 0;
  > }
  > 
  > Person::Person(const string& name, int age){
  >     this->name = name;
  >     this->age = age;
  >     cout<<"constructor call"<<endl;
  > }
  > 
  > void Person::ShowPersonInfo(){
  >     cout<<name<<age<<endl;
  > }
  > ```

<br>

### :pushpin: std::weak_ptr이란?

- 하나 이상의 std::shared_ptr 인스턴스가 소유하는 객체에 대한 접근을 제공하지만, 소유자의 수에는 포함되지 않는 스마트 포인터

  > [1] std::shared_ptr은 참조 횟수(reference count)를 기반으로 동작하는 스마트 포인터
  >
  > [2] 만약 서로가 상대방을 가리키는 shared_ptr를 가지고 있다면, 참조 횟수는 절대 0이 되지 않으므로 메모리는 영원히 해제되지 않는다(순환 참조, circular reference)
  >
  > [3] weak_ptr은 이러한 shared_ptr 인스턴스 사이의 순환 참조를 제거하기 위해 사용된다.

<br>

### :pushpin: std::unique_ptr의 RAII 예시

```c++
void func(){
    int *ptr = new int[100];
    if(error()) return; // 에러 발생 시 ptr 메모리가 해제되지 않는다.
    delete[] ptr;
}
```

```c++
void func(){
    int *ptr = new int[100];
    std::unique_ptr<int> u_ptr(ptr);
    if(error()) return; // 에러 발생 시 unique_ptr로 인해 delete[] 구문을 수행하고 종료
    delete[] ptr;
}
```

<br>

### :pushpin: mutex의 RAII 예시

```c++
void func(){
    std::mutex m;
    m.lock();
    
    sum += num;
    // m.unlock()의 부재 또는 연산 진행 중에 발생한 오류, 해당 함수의 sum+=num 구문은 lock()을 점유, 다른 스레드들은 해당 함수에 접근 불가, wait 상태 돌입
}
```

```c++
void func(){
    std::mutex m;
    std::lock_guard<std::mutex> lock(m); // 함수 종료 시 자동으로 .unlock() 가능
    // 또는
    std::unique_lock<std::mutex> lock(m); // unique_lock 사용
    sum+=num;
}
```

<br>

### :pushpin: C++ 언어가 가진 생성자/소멸자 대칭 구조

- 자원의 획득과 해제 함수에도 그대로 적용되었다.
- **fopen/fclose, lock/unlock, new/delete** 등의 기능을 만들어 냈다.
- 이러한 기능은 자원을 얻는 생성자와 해제하는 소멸자를 스택 기반의 개체에 추가하여 자원의 관리와 청소에 완벽한 도구로 만들어주었다.

<br>

### :pushpin: 자동화된 자원 관련 기능의 특징

- 편리하고, 간결하며, 비용이 적고, 오류로부터 안전하다.
- C++의 RAII > C 스타일의 세밀한 자원 재할당과 같은 방식

<br>

### :pushpin: 획득과 해제 함수 호출이 필요한 자원을 다룰 경우

- 자원을 개체 내에 캡슐화하여 **생성자와 소멸자를 통한 자원 관리**가 이루어지도록 하면 된다.

- example>

  > OpenPort/ClosePort와 같은 비멤버 함수를 직접 호출하는 것보다는 
  >
  > :point_down: __다음과 같은 방법을 사용하는 것이 좋다.__
  >
  > ```c++
  > class port{
  >     public:
  >     Port(const string& destination); // OpenPort() 호출
  >     ~Port(); // ClosePort() 호출
  >     // 포트는 복사될 수 없으므로 복사와 할당을 하지 않도록 설정
  > };
  > 
  > void DoSomething(){
  >     Port port1("server1:80");
  >     // ...
  > } // 범위의 끝에 도달하면 port1은 자동적으로 닫힌다(Port 클래스가 로컬로 선언되어있기 때문에 함수의 종료와 동시에 Port의 소멸자 호출)
  > 
  > std::shared_ptr<Port> port2=/*...*/; // port2 역시 shared_ptr에 의해 자동으로 닫힌다.
  > ```



<br>

### :pushpin: RAII 구현 시 주의점

- 복사와 할당 과정에 유의해야 한다(컴파일러가 만들어낸 버전은 올바르지 않은 경우가 많기 때문)

- **복사가 이루어지면 안 되는 경우**에는 개발자가 직접 복사가 불가능하도록 설정해야 한다.

- **복사가 이루어져야 하는 경우**에는 복사 생성자가 사용 회수에 따라 자원이나 참조 카운트를 복사하도록 하고, 할당 연산자도 같은 작업을 하도록 하되 원래 가지고 있던 자원을 해제하도록 제어해줘야 한다.

  > **새로운 복사본을 만들기 전에 원본 자원을 해제하면 안 된다.**

- 원본 자원을 개체가 가지게 하자.

  - **원시 포인터(raw pointer)** 대신에 **스마트 포인터(smart pointer)**를 사용해서 자원의 할당이 동적으로 이루어지게 한다.

  - 모든 직접적인 자원 할당(new 연산자와 같은)이 내부의 구문 내에서 실행되도록 하여, **할당된 자원이 관리 개체(shared_ptr과 같은)로 전달되도록 해야 한다.**

    > **함수 인자의 실행 순서가 정해지지 않았기 때문에 자원 누출 가능**
    >
    > :point_down: __예시__
    >
    > ```c++
    > void func(std::shared_ptr<Widget> sp1, shared_ptr<Widget> sp2);
    > //...
    > // 안정적이지 못한 코드
    > func(shared_ptr<Widget>(new Widget), shared_ptr<Widget>(new Widget));
    > ```
    >
    > 함수의 두 인자를 이루는 표현식이 컴파일러에 의해 제어될 수 있으므로 안정적이지 못하다.
    >
    > <br>
    >
    > **new 연산자에 의한 메모리 할당이 양쪽 개체에 대해 먼저 이루어지고, 두 Widget 생성자를 호출하는 시도가 이루어지도록 제어된다면?**(sp1 = new Widget, sp2=new Widget)
    >
    > [1] 첫 번째 생성자에서 예외 발생 시 다른 개체의 메모리가 계속 묶여있게 된다(Memory leak 가능)
    >
    > <br>
    >
    > :point_down: __이러한 문제를 해결하는 방법__
    >
    > 한 구문 내에 하나 이상의 자원을 할당하지 말고, new와 같은 직접 자원 할당을 코드 구문 내에 넣어 자원을 shared_ptr과 같은 개체에 즉시 전달하면 된다.
    >
    > ```c++
    > std::shared_ptr sp1(new Widget), sp2(new Widget);
    > func(sp1, sp2);
    > ```