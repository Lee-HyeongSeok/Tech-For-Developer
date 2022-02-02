## 오버로딩(overloading)된 함수, 템플릿(template) 함수의 정의와 사용

***

<br>

### :pushpin: 오버로딩(overloading)된 함수

> **오버로딩 : 서로 다른 타입과 매개변수를 가지지만 같은 이름을 사용하는 함수를 정의하는 것**
>
> ```c++
> void display_message(char ch);
> void display_message(const string&);
> void display_message(const string&, int);
> void display_message(const string&, int, int);
> ```
>
> :point_right: 함수를 호출할 때 전달한 실제 인수를 오버로딩된 경우의 매개변수와 각각 비교하여 결정
>
> :point_right: 반환 타입으로는 오버로딩된 함수를 만들 수 없다.
>
> ```c++
> // 반환 타입으로 오버로딩한 예시
> // 반환 타입만으로는 어떤 경우인지 구별하는 데 충분한 정보를 줄 수 없기 때문
> ostream& display_message(char ch);
> bool display_message(char ch);
> ```

<br>

### :pushpin: 템플릿(template) 함수의 정의와 사용

- **오버로딩된 함수**

  > ```c++
  > void display_message(const string&, const vector<int>&);
  > void display_message(const string&, const vector<double>&);
  > void display_message(const string&, const vector<string>&);
  > ```

- **템플릿화된 함수**

  > **:point_right: 템플릿이란?**
  >
  > - 매개변수 목록의 모두나 일부의 타입 정보를 인자(factor)로 만드는 것
  > - 이 인자(factor)는 나중에 실제 타입으로 치환된다.
  >
  > <br>
  >
  > ```c++
  > template <typename elemType>
  > void display_message(cosnt string& msg, const vector<elemType> &vec){
  >     cout<<msg;
  >     for(int ix=0; ix<vec.size(); ++ix){
  >         elemType t = vec[ix];
  >         cout<<t<<' ';
  >     }
  > }
  > ```
  >
  > :point_right: typename이라는 키워드를 사용해서 함수 템플릿인 display_message() 안의 elemType이 특정한 타입으로 대체됨을 지정한다.
  >
  > :point_right: 함수 템플릿은 무제한적으로 함수 인스턴스를 생성해내는 틀과 같다.
  >
  > :point_right: 함수 인스턴스의 elemType은 기본 타입 또는 사용자가 정의한 클래스 타입으로 대체된다.

<br>

### :pushpin: 오버로딩과 템플릿의 사용 시기

- 구현이 다양하게 존재할 때 :point_right: 함수 오버로딩
- 각 인스턴스가 동일한 서비스를 제공하면서 타입만 변하고, 코드 몸체가 변하지 않을 때 :point_right: 함수 템플릿

<br>

### :pushpin: 함수 템플릿 오버로딩

```c++
// typename은 같지만, 인자로 전달되는 vector와 list의 차이
template <typename elemType>
void display_message(const string& msg, const vector<elemType> &vec);

template <typename elemType>
void display_message(const string& msg, const list<elemType> &vec);
```



