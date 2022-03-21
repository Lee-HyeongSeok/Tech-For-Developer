## C++ In-Depth Coding rules(class 28)

***

<br>

### :pushpin: 표준적인 형식의 산술 및 할당 연산자를 사용하라

- a+b가 있다면 a+=b도 같은 의미인 것이 좋다.
- 두 대상 사이에서 이루어지는 산술 연산자의 경우 같은 효과를 가지는 할당 연산자도 제공해야만 중복을 피하고 효율을 극대화할 수 있다.

```c++
T& T::operator@=(const T&){
    //...
    return *this;
}

T operator@(const T& lhs, const T& rhs){
    T temp(lhs);
    // ...
    return temp@=rhs;
}
```

위 두 함수의 기능은 같다고 볼 수 있다.

할당 형식은 실제 작업을 수행하고 인자를 리턴하지만, 할당 형식이 아닌 버전에서는 lhs라는 임시값을 만들고, 할당 형식을 호출하여 값을 변형한 후에 리턴한다는 차이점이 있을 뿐이다.

```operator@```는 멤버 함수가 아니기 때문에 연산이 이루어지는 양쪽 대상에 대해 간접적인 변환을 할 수 있다는 점에 주의해야 한다. 예를 들어 char 타입을 받아들이는 String 클래스를 정의했다고 하면, ```operator+(const String&, const String&)```을 비멤버 함수로 만들면 ```char + String```과 ```String + char``` 모두 가능하게 된다는 의미이다.

만약 멤버 함수인 ```String::operator+(const String&)``` 라면 ```String + char``` 방식만이 가능할 것이다.

:point_right: 가능하다면 비멤버 함수로 만드는 것이 좋으며, 모든 비멤버 연산자들은 같은 네임스페이스 내에 넣어 호출자가 편하게 사용할 수 있도록 하고, 이름 조회가 필요 없게끔 해주면 더욱 좋다.



### :pushpin: 예시

```c++
String& String::operator+=(const String& rhs){
    // ...
    return *this;
}
```

문자열을 결합할 때에는 그 길이를 알 수 있도록 해야 필요한 메모리 양을 가늠할 수 있다.

위를 아래와 같이 바꾼다.

```c++
String operator+(const String& lhs, const String& rhs){
    String temp;
    temp.Reserve(lhs.size() + rhs.size());
    return (temp+=lhs) += rhs;
}
```

