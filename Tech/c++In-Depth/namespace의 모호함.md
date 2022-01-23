## namespace의 모호함

***

<br>

### :pushpin: namespace의 모호함

> **namespace의 중복문제**

- 나중에 std가 아닌 다른 namespace를 import한다고 가정했을 때

  > using namespace **std**;
  >
  > using namespace **myNamespace**; 

  - 위 두 namespace는 cin이라는 동일한 이름을 가진 함수를 포함한다.

  - 개발자는 myNamespace의 cin 함수를 호출하려 할 때 컴퓨터는 std::cin인지, myNamespace::cin인지 모호해진다.

  - **이런 경우 namespace가 같은 함수를 import해서 모호하다는 메시지가 아닌**, 

    > **컴퓨터가 std::cin을 강제로 실행**
    >
    > **사용자가 myNamespace::cin에 전달한 인자를 컴퓨터가 std::cin에 전달하고**
    >
    > **이때 발생하는 오류를 출력**