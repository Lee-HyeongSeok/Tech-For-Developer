## C++ In-Depth Coding rules(class 48)

***

<br>

### :pushpin: 멤버 변수의 정의와 선언은 같은 순서로 하라

- 멤버 변수의 초기화는 클래스 정의 내에 선언된 순서대로 이루어진다.
- 생성자 초기화 목록에 쓴 순서는 무시된다.

<br>

```c++
class Employee{
    String email_, firstName_, lastName_;
    
    public:
    Employee(const char* firstName, const char* lastName)
        : firstName_(firstName), lastName_(lastName), email_(firstName_+"."+lastName_+"@acme.com") {}
};
```

위 코드에는 발견하기 힘든 버그를 숨기고 있다.

- 클래스 정의 내 email\_이 first\_와 last\_ 보다 먼저 선언되어 있지만 먼저 초기화되고, 아직 초기화되지 않은 다른 필드를 사용하기 때문이다.
- 적절한 정의와 초기화 순서는 파괴 순서와도 관련이 있으며, 적절한 순서를 유지하지 않으면 객체를 만드는 생성자에 따라 객체를 파괴하는 소멸자의 성향에 의해 문제가 생긴다.

<br>



### :pushpin: 해결책

멤버가 선언된 순서와 동일한 순서로 초기화하는 것.

- 잘못된 종속성이 분명히 드러난다.
- 초기화되지 않은 멤버가 다른 멤버에 의해 의존하는 현상을 쉽게 파악 가능
- 대부분의 컴파일러는 이 규칙을 어길 경우 경고 문구를 출력한다.