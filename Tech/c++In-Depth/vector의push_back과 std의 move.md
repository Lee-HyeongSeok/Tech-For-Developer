## vector의push_back과 std의 move

***

<br>

### :pushpin: vector::push_back

> **void push_back(const value_type& val);**
>
> **void push_back(value_type&& val);**

- vector의 끝에 새 요소를 추가하는 vector 함수

- 현재 vector 용량을 초과하는 경우에만 할당된 저장 공간이 자동으로 **재할당된다**.

  - 재할당 실패 시 예외를 throw할 수 있는 컨테이너의 할당자를 사용하여 스토리지를 할당
  - 기본 할당자의 경우 할당 요청 실패 시 bad_alloc이 throw된다.

- val의 내용이 새 요소로 **복사** 또는 **이동**된다(**복사 생성자**를 호출할 수 있다)

  ```c++
  class A{
      private : 
      	int num;
      	std::string name;
      public : 
      	A(int num, std::string name): this->num(num), this->name(name){ }
  }
  
  int main(void){
      std::vector<A> A_class_vector;
      A A_class(24, "LEE");
      
      A_class_vector.push_back(A_class); // A클래스의 복사 생성자 호출
  }
  ```

  - 복사 생성자로 인한 오버헤드 증가, 성능 저하

- **push_back과 std::move**

  ```c++
  std::vector<std::string> example;{
      std::string input = "example";
      example.push_back(input); // push_back이후 input은 사용되지 않기 때문에 input은 vector에 string을 삽입하기 위한 임시 객체 역할만 수행, 이때 move를 사용하면 성능 향상
  }
  ```

  ```c++
  str::vector<std::string> example;{
      str::string input="example";
      example.push_back(std::move(input)); // input은 Lvalue, move로 인해 Rvalue로 casting
  }
  ```

  - 해당 예제에서는 std::string이 move constructor, move assignment operator를 지원하기 때문에 move로 기대하는 동작을 얻을 수 있다.
  - 사용자가 정의한 class의 경우 destructors, assignment operators를 명시적으로 선언했다면 move constructor, move assignment operators가 암시적으로 생성되지 않으므로 직접 생성해주거나 default로 선언해야 한다.

  ```c++
  class myClass{
      private:
      	std::string str1;
      	std::string str2;
      public:
      	myClass(myClass&& rhs):this->str1(std::move(rhs.str1)), this->str2(std::move(rhs.str2)){ }
  }
  ```

  