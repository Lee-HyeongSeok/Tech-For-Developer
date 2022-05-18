## C++ In-Depth Coding rules(class 39)

***

<br>



### :pushpin: 안전한 오버라이딩을 연습하라

- 가상 함수를 오버라이딩할 때는 대체성을 유지해야 한다.
- 기본 클래스 내에 있는 함수의 전/후 조건을 잘 관찰해야 한다.
- 가상 함수의 표준 인자를 변경하지 말고, 직접적인 재선언 방식의 오버라이딩을 사용하는 것이 좋다.

<br>

### :pushpin: 파생 클래스는 기반 클래스보다 존재감이 적은 부분집합일 뿐이며, 적절한 상속 관계 내에서 파생 클래스는 보다 일반적인 기본 개념의 특별한 경우에 해당한다.

- 이러한 개념은 오버라이딩에도 영향을 미친다.
- 포함의 개념을 따른다는 것은 대체성을 유지한다는 것이며, 전체에 적용되는 작업은 그 일부에도 적용되어야 한다는 의미가 된다.
- 기본 클래스에서 작업의 전후 조건에 대한 규칙을 정해 놓았으면 그로부터 얻어지는 파생 클래스 역시 그러한 규칙을 따라야 하며, 규칙에 대한 책임이 다소 적거나 제공하는 기능이 더 많을 수는 있겠지만 호출하는 코드와 기본 클래스가 만들어놓은 약속을 깨서는 안 된다.

<br>


### :pushpin: 오버라이드된 부분이 실패할 수 있는 경우는 기본 클래스에서 작업이 항상 성공하지는 않음을 명시해두었을 때에만 가능하다.

```c++
class Employee{
    virtual void GetBuilding();
}
```

만약 ```Employee``` 클래스에 직원이 일하는 공간에 대한 정보를 얻는 ```GetBuilding()```이라는 가상 멤버 함수가 있을 때,

```c++
void RemoteContractor(){
    GetBuilding();
}
```

```RemoteContractor()``` 함수를 만들어 ```GetBuilding()```을 오버라이드했다고 가정한다.

이때 ```RemoteContractor()```가 예외를 발생시키거나 null을 리턴하면 어떨까?

```c++
class Employee{
    virtual void GetBuilding();
}
```

```Employee``` 에서 ```GetBuilding()``` 호출 시 예외가 발생하거나 null이 리턴될 수 있으며, 그 방식 그대로 ```RemoteContractor()```가 작동한 것이라면 문제 없겠지만 그렇지 않다면 오버라이드가 잘못된 것이다.

:point_right: 오버라이딩을 진행할 때는 표준 인자를 바꾸어서는 안 된다. 표준 인자는 함수 서명의 일부가 아니며, 클라이언트 코드는 접근하고 있는 계층 구조의 노드에 따라 다른 인자를 함수에 전달할 수 있기 때문이다.

예를 들어,

호출자의 입장에서는 접근하는 타입에 따라 같은 개체의 멤버 함수가 받아들이는 인자가 달라진다는 점을 이해하기 힘들 것이다. 이때는 함수 오버라이딩을 할 때 virtual을 추가하여 의도를 명확하게 이해시키는 편이 좋다.

```c++
class Base{
    virtual void Foo(int x=0);
};

class Derived : public Base{
    virtual void Foo(int x=1);
};

Derived *pD = new Derived;
pD->Foo();
Base *pB = pD;
pB->Foo();
```



<br>

### :pushpin: 기본 클래스 내에 오버로드를 숨기는 것도 좋은 방법이 아니다.

```c++
class Base{
    virtual void Foo(int);
    virtual void Foo(int, int);
    void Foo(int, int, int);
};

class Derived : public Base{
    virtual void Foo(int);
};

Derived d;
d.Foo(1);
d.Foo(1,2);
d.Foo(1, 2, 3);
```

위에서 ```d.Foo(1, 2);```와 ```d.Foo(1, 2, 3);```은 오류가 발생한다.

기본 클래스의 오버로드가 보여져야 한다면 얻어진 클래스 내에서 using을 사용해서 다시 선언하는 것이 해결책이다.

```c++
class Base{
    virtual void Foo(int);
    virtual void Foo(int, int);
    void Foo(int, int, int);
};

class Derived : public Base{
    virtual void Foo(int); // Base::Foo(int) 오버라이드
    using Base::Foo; // 다른 Base::Foo 오버로드들도 범위 내로 가져옴
};

Derived d;
d.Foo(1);
d.Foo(1,2);
d.Foo(1, 2, 3);
```

