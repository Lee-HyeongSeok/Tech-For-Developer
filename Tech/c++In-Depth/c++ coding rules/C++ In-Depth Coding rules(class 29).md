## C++ In-Depth Coding rules(class 29)

***

<br>

### :pushpin: ```++```와 ```--```의 표준적인 형식과 접두 형식을 사용하라

++value가 된다면 value++도 되어야 한다. ```operator++```와 ```operator--```의 정의는 일반적인 기능을 그대로 따르되, 원래의 값이 필요하지 않은 경우라면 접두어 형태를 사용하는 것이 좋다.

- ```++```와 ```--```를 변수 뒤에 붙이면 원래의 값이 리턴, 앞에 붙이면 새로운 값이 리턴된다.

<br>

### :pushpin: 접두 형식

```c++
T& T::operator++(){
    return *this;
}

T& T::operator--(){
    return *this;
}
```

<br>

### :pushpin: 접미 형식

```c++
T T::operator++(int){
    T old(*this);
    ++*this;
    return old;
}

T T::operator--(int){
    T old(*this);
    --*this;
    return old;
}
```

- 객체가 하나 덜 만들어지기 때문에 효율이 좋다.