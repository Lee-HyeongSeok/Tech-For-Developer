## printf & cout

***

<br>

### :pushpin: printf와 cout

- **공통점**

  - iostream header에 printf와 cout 모두 정의되어 있다.

- **차이점**

  - **printf**

    - 원칙적으로는 문자열 밖에 출력할 수 없다.

    - 정수 및 실수 등을 표현하려면 형식에 맞추어 캐스팅해야 함

      > printf("%d", n);	->	n이 %d(decimal) 타입임을 명시

  - **cout**

    - 출력 가능한 형식이 자유롭다(자동으로 캐스팅 해주기 때문)

      > std::cout<<n;	->	n이 어떤타입인지 명시할 필요 없음

- **영향**

  - printf는 그 자체로 한번에 출력하면 끝이지만, std::cout은 <<를 기준으로 여러 절차가 혼합되어 **속도가 느리다**.