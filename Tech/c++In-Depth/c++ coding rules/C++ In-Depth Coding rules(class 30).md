## C++ In-Depth Coding rules(class 30)

***

<br>

### :pushpin: 간접적인 타입 변환을 피하기 위해 오버로딩을 활용하라

간접적인 타입 변환은 임시 객체가 만들어진다는 점에서 효율적이지 못하다. 따라서 변환이 일어나지 않는 범위 내에서 일반적인 인자 타입을 사용한 오버로딩 함수를 활용해야 한다.

```c++
class String{
    String(const char* text);
};

bool operator==(const String&, const String&);

if(someString == "Hello"){
    ...
}
```

위 코드의 경우 if문에서 리터럴 문자열인 ```Hello``` 때문에 문자열을 복사하면서 간접 타입 변환이 이루어진다.

```c++
bool operator==(const String&, const String&);
bool operator==(const String&, const char*);
```

이처럼 오버로딩을 통해 간접 변환을 피한다.

- 이러한 방식의 오버로딩은 너무 이른 최적화라는 측면이 있다.
- 성능에 민감한 코드에 쓰이기에는 적절하지 않다.

