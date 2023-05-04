## C++ 컴파일 타임의 구문 분석에 따른 nullptr 가능성

---

다음과 같은 코드가 있다.

```c++
class Http
{
public:
    void inject();
    void is_tls(int payload)
    {
        inject();
    }
};

class Controller
{
public:
    void Start(int payload)
    {
        http_protocol->is_tls(payload); // http_protocol이 nullptr 이라면?
    }
private:
    Http *http_protocol;
};

void something(int event)
{
    auto object = boost::make_shared<Controller>();
    object->Start(event); 
}

int main()
{
    int event = 1; 
    
    something(event);
}
```

위 코드에서 ```something``` 함수를 통해 Controller 클래스를 shared_ptr로 생성한 뒤에 Controller 클래스의 Start 멤버 함수를 실행 시키고 있다.

Start 멤버 함수에서는 Http 클래스의 is_tls 멤버 함수를 실행 시키고 있는데, 이때 Http 클래스 인스턴스가 nullptr이여도 is_tls 함수를 실행하게 된다. 이는 아래와 같은 구문 분석 때문이다.

```c++
void is_tls(int payload)
{
    inject();
}
```

Http 클래스에 의하여 위 is_tls 함수가 실행되면, 아래와 같이 컴파일 된다.

```c++
void is_tls(Http* this, int payload)
{
    this->inject();
}
```

멤버 함수의 첫 번째 인자로는, 해당 클래스를 가리키는 this 포인터가 삽입되고, this 포인터를 통해 inject라는 멤버 함수를 실행 시킨다.

따라서 is_tls를 실행 시킨 Http class의 인스턴스가 nullptr이라면, 다음과 같은 상황이 일어난다.

```c++
void is_tls(Http* this, int payload)
{
    nullptr->inject();
}
```

