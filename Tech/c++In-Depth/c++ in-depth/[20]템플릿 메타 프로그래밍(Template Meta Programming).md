## 템플릿 메타 프로그래밍(Template Meta Programming)

***

<br>

### :pushpin: 일반화 프로그래밍(제네릭 프로그래밍, generic grogramming)

> 템플릿을 통해서 타입이 마치 인자 인것 처럼 사용하는 것
>
> :point_right: 템플릿 인자로는 타입 뿐만 아니라 특정 조건을 만족하는 값들도 올 수 있다.

```c++
#include <iostream>
using namespace std;

template <typename T, unsigned int N>
class Array{
    T data[N];

    public:
    // 배열을 받는 레퍼런스 arr
    Array(T (&arr)[N]){
        for(int i=0; i<N; ++i){
            data[i] = arr[i];
        }
    }
    
    T* get_array(){ return data; }
    unsigned int size(){ return N; }
    
    void print_all(){
        for(int i=0; i<N; ++i){
            cout<<data[i]<<", ";
        }
        cout<<endl;
    }
};

int main(){
    int arr[3] = {1, 2, 3};
    Array<int, 3> arr_w(arr);
    arr_w.print_all();
}
```

```Array<int, 3> arr_w(arr);```와 같이 템플릿 인스턴스화를 하게 되면, T 자리에는 int가, N 자리에는 3이 들어간다.

컴파일러는 ```T data[N];```을 ```int data[3]```로 대체해서 코드를 생성하게 된다.

```Array(T (&arr)[N])``` 생성자 역시 ```Array(int (&arr)[3])```으로 코드가 생성되어 실행된다.

이 처럼 배열을 감싸는 wrapper 클래스를 만들어서 배열 처럼 사용한다면 배열을 사용함으로써 발생하는 문제들을 많이 해결할 수 있다.

ex) 일반 배열은 배열 범위가 넘어가도 알 수 없지만, 위 Array 클래스는 index 범위가 넘어 가는 곳을 가리키면 메시지를 띄우거나 오류를 발생 시켜 사용자에게 알려줄 수 있다.

<br>

```Array<int, 5> Array<int, 3>``` 이 두 클래스는 같은 클래스인가?

:point_right: 이를 확인하려면 ```typeid```로 확인할 수 있다.

```cout<<(typeid(Array<int, 3>) == typeid(Array<int, 5>))<<endl;``` 

결과는 0이 나온다(다른 클래스이다)

:point_right: 템플릿 인자로 인스턴스화 되었기 때문이다.

컴파일러는 ```Array<int, 5>```와 ```Array<int, 3>```를 위해 각기 다른 코드를 생성하며 다른 클래스의 객체들을 만들게 된다.