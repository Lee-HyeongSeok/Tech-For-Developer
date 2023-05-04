## CRTP(Curiously Recursing Template Pattern)

---

기반 클래스 포인터에 파생 클래스 객체의 포인터를 대입하여 사용하는 것을 피하면서

가상 함수의 오버라이드를 흉내내는 템플릿 패턴으로, 주로 지연된 계산을 사용할 때 유용함

파생 클래스 : 자기 자신의 타입을 템플릿 인자로 갖는 기반 클래스를 상속함

기반 클래스 : 자신의 멤버 함수가 템플릿 인자의 동일한 함수를 호출하는 형식



### :pushpin: 일반적인 상속과 업캐스팅(프로그램 런타임에 결정)

```c++
#include <iostream>
#include <boost/shared_ptr.hpp>

class Base
{
public:
    Base() = default;
    
    virtual void PrintClass() const = 0;
};

class Derived
    : Base
{
public:
    Derived() = default;
	
    void PrintClass() const override
    {
        std::cout<<"Derived Class\n";
    }
};

int main()
{
    boost::shared_ptr<Base> object = boost::make_shared<Derived>();
    object->PrintClass(); // print "Derived Class"
}
```

위 방식은 ```boost::shared_ptr<Base> object``` 객체가 프로그램의 런타임에 어떤 타입인지 결정되기 때문에

오버라이드 된 메서드를 호출하면, 프로그램 실행 시간에 어떤 객체의 가상함수인지 상속 트리를 순회하며 찾게 된다. 이러한 방식은 상속 트리가 깊고, 해당 가상함수가 자주 호출되는 상황이라면 프로그램 성능에 영향을 미칠 수 있다.

이러한 문제를 해결하기 위해 컴파일 타임에 객체의 타입이 유추되도록 하는 CRTP를 발견 하게 되었다.

```c++
#include <iostream>

template <typename DerivedT>
class Base 
{
public:
	Base() = default;

	DerivedT* derived()
	{
		return static_cast<DerivedT*>(this);
	}

	void PrintClass()
	{
		derived()->PrintClass();
	}
};

// template 특수화, BaseT가 template class라고 알려주는 것
template <template <class> typename BaseT>
class Derived 
	: BaseT<Derived<BaseT>>
{
public:
	typedef BaseT<Derived<BaseT>> BaseType;

	Derived() = default;

	void Start()
	{
		BaseType::PrintClass();
	}

	void PrintClass()
	{
		std::cout << "Derived Class\n";
	}
};

int main()
{
	Derived<Base> derivedObject;
	derivedObject.Start(); // print "Derived Class"
}
```

