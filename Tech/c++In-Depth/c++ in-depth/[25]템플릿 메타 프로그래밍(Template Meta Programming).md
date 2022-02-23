템플릿 메타 프로그래밍(Template Meta Programming)

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

<br>

## 

```c++
template <int N>
struct Int{
  static const int num=N;
}
```

이 클래스는 템플릿 인자로 int 값을 받는다.

```static const```에 값을 저장하는 이유

1 . C++ 클래스 멤버 중에 클래스 자체에서 저런식으로 초기화 할 수 있는 멤버의 타입은 static const 밖에 없다.

2. static const는 이 클래스는 이것이다 라는 의미를 가장 잘 나타낸다.
   - static 타입 멤버 특성 상 이 클래스가 생성한 객체들 사이에서 공유되는 값
   - 이 타입이면 이 값을 나타낸다라고 볼 수 있다.
   - const 이므로 나타내는 값이 변하지 않게 된다.

```c++
typedef Int<1> one;
typedef Int<2> two;
```

이 처럼 객체를 생성하듯 타입들을 생성 가능하다.

one과 two 타입은 1과 2 값을 나타내는 타입이 된다(객체가 아니다)

이들은 int 변수를 다루는 것 처럼 연산자를 만들 수 있다.

```c++
#include <iostream>
#include <typeinfo>

template <int N>
struct Int{
  static const int num = N;
}

template <typename T, typename U>
struct add{
  typedef Int<T::num + U::num> result;
}

int main(){
  typedef Int<1> one;
  typedef Int<2> two;
  typedef add<ont, two>::result three;
  cout<<three::num<<endl;
}
```

위 코드에서 ```typedef add<one, two>::result three``` 는 실제 덧셈을 수행하는 부분

계산 결과를 내부 result 타입으로 반환한다.

one과 two를 더한 것을 나타내는 타입이 result로 정의되고, 이를 three라고 부른다.

결과는 3인데, 이 값이 프로그램이 실행되면서 계산되는 것이 아니라 컴파일 시에 컴파일러가 ```three:num```을 3으로 치환 해버린다.

<br>

### :pushpin: 템플릿 메타 프로그래밍(Template Meta Programming; TMP)

- 템플릿 메타 프로그래밍 이전

  > 어떤 객체에 무엇을 저장하는가(타입 자체가 어떠한 값을 가지지 않았다)

- 템플릿 메타 프로그래밍

  > 객체를 생성하지 않아도 타입에 어떠한 값을 부여할 수 있다.
  >
  > 그 타입들을 가지고 연산을 할 수 있다.
  >
  > 타입은 반드시 컴파일 타임에 확정되어야 하므로, 컴파일 타임에 모든 연산이 끝난다(위에서 컴파일러가 ```trhee::num```을 3으로 치환한 것 처럼)
  >
  > **타입을 가지고 컴파일 타임에 생성되는 코드로 프로그래밍 하는 것을 메타 프로그래밍이라고 한다.**



```c++
#include <iostream>

template <int N>
struct Factorial{
  static const int result = N * Factorial<N-1>::result;
};

template <>
struct Factorial<1>{
  static const int result=1;
};

int main(){
	cout<<Factorial<5>::result<<endl; // 결과 120
}
```

```Factorial<1>``` 타입의 경우만 따로 ```result=1```로 만들어주어 재귀적 구조를 끝날 수 있게 해주었다 :point_right: 템플릿 특수화

위 코드에서 실질적으로 값을 가지는 객체는 없다(값을 가지고 있는 변수는 메모리 상에서 없다는 뜻, 컴파일 타임에서 모든 연산이 끝나기 때문)

for문으로 구현 가능한 모든 코드는 템플릿 메타 프로그래밍을 이용해서 구현 가능

if문 역시 템플릿 특수화를 통해 TMP로 구현 가능



<br>

### :pushpin: 템플릿 메타 프로그래밍을 왜 쓰는가?

> 어떠한 C++ 코드도 템플릿 메타 프로그래밍 코드로 변환 가능
>
> 템플릿 메타 프로그래밍으로 작성된 코드는 모두 컴파일 타임에 모든 연산이 끝나기 때문에 실행 속도 향상 가능
>
> :point_right: 컴파일 시간은 향상

> 하지만
>
> 템플릿 메타 프로그래밍은 매우 복잡하다.
>
> 템플릿 메타 프로그래밍으로 작성된 코드는 버그를 찾는 것이 매우 힘들다.
>
> 컴파일 타임에 연산하기 때문에 디버깅이 불가능하다.
>
> C++ 컴파일러 특성 상 템플릿 오류 시에 많은 양의 오류를 출력한다.

> 많은 C++ 라이브러리들이 TMP를 이용해서 구현되었다(Boost 라이브러리)
>
> TMP를 통해 컴파일 타임에 여러 오류를 잡아낼 수 있다(단위, 통화 일치 여부 등)
>
> 속도가 매우 중요한 프로그램의 경우 TMP를 통해 런타임 속도를 향상시킬 수 있다.

<br>

### :pushpin: TMP를 사용한 최대공약수 구하는 프로그램

> 최대 공약수를 구하는 일반적인 방법(유클리드 호제법)

```c++
int gcd(int a, int b){
  if(b == 0)
    return a;
  return gcd(b, a%b);
}
```



> 위 코드를 템플릿 메타 프로그래밍(TMP)로 변환

```c++
#include <iostream>
using namespace std;

// 재귀적 구조를 수행하는 템플릿 메타 프로그래밍 코드
template <int n1, int n2>
struct gcd{
	static const int result = gcd<n2, n1%n2>::result;
};

// if문 역할을 해주는 템플릿 특수화된 코드
template <int n1, 0>
struct gcd{
  static const int result = n1;
};

int main(){
  cout<<gcd<36, 24>::result<<endl;
}
```

> 최대 공약수 계산 클래스를 만든 이유는 ```Ratio``` 클래스를 만들기 위함
>
> ```Ratio``` 클래스 : 유리수(p/q 꼴로 쓸 수 있는 수)를 오차 없이 표현해 주는 클래스

```c++
template <int N, int D=1> // 분모와 분자를 템플릿 인자로 받는다.
struct Ratio{
  typedef Ratio<N, D> type; // 자기 자신을 가리키는 타입, 클래스에서 this와 비슷한 역할
  static const int num = N;
  static const int den = D;
};
```

> ```Radio``` 클래스로 덧셈을 수행하는 템플릿

```c++
template <class R1, class R2>
struct _Ratio_add{
	typedef Ratio<R1::num * R2::den + R2::num * R1::den, R1::den * R2::den> type;
};
```

> 두 분수의 더한 결과를 ```Ratio```에 분자 분모로 전달하면 알아서 기약분수로 만들어 준다.

```c++
typedef Ratio<R1::num * R2::den + R2::num * R1::den, R1::den * R2::den> type;
```

> 이후에 덧셈 결과를 type으로 나타내게 된다.
>
> 이를 수행하기 위해서는 ```typedef _Ratio_add<rat, rat2>::type result;``` 식으로 사용하면 된다.



### :pushpin: using 키워드

> ```c++11``` 부터 typedef 대신에 직관적인 ```using``` 키워드 사용 가능

```c++
typedef Ratio_add<rat1, rat2> result;
using result = Ratio_add<rat1, rat2>; // 둘다 같은 표현
```

> 함수 포인터인 경우, void 를 리턴하고 int, int를 인자로 받는 함수의 포인터 타입을 func라고 정의할 떄

```c++
typedef void (*func)(int, int);
using func = void (*)(int, int); // 둘다 같은 표현이다, func이 새로 정의된 타입 이름이 된다.
```



### :pushpin: using 키워드로 직관적으로 변경한 코드

```c++
#include <iostream>
using namespace std;

template <int n1, int n2>
struct gcd{
	static const int result = gcd<n2, n1%n2>::result;
};

// if문 역할을 수행하는 템플릿 특수화
template <int x>
struct gcd<x, 0>{
  	static const int result = x; 
};

template <int N, int D=1>
struct Ratio{
	using type = Ratio<N, D>; // typedef Ratio<N, D> type;
	static const int num = N;
	static const int den = D;
}

template <class R1, class R2>
struct _Ratio_add{
	// typedef Ratio<R1::num * R2::den + R2::num * R1::den, R1::den * R2::den> type;
	using type = Ratio<R1::num * R2::den + R2::num * R1::den, R1::den * R2::den>;
};

template <class R1, class R2>
struct Ratio_add : _Ratio_add<R1, R2>::type{};

template <class R1, class R2>
struct _Ratio_sub{
	// typedef Ratio<R1::num * R2::den + R2::num * R1::den, R1::den * R2::den> type;
	using type = Ratio<R1::num * R2::den + R2::num * R1::den, R1::den * R2::den>;
};

template <class R1, class R2>
struct Ratio_add : _Ratio_sub<R1, R2>::type{};

int main(){
  using rat1 = Ratio<2, 3>; // typedef Ratio<2, 3> rat1;
  using rat2 = Ratio<3, 4>;	// typedef Ratio<3, 4> rat2;
  using result1 = Ratio_add<rat1, rat2>; // typedef Ratio_add<rat1, rat2>::type result1;
  cout<<result::num<<"/"<<result::den<<endl;
  
  using rat3 = Ratio<1, 3>;
  using rat4 = Ratio<2, 3>;
  using result2 = Ratio_sub<rat3, rat4>;
  cout<<result2::num<<"/"<<result2::den<<endl;
}
```

