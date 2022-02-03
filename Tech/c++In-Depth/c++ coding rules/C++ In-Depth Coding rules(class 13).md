## C++ In-Depth Coding rules(class 13)

***

<br>

### :pushpin: 안전한 공유를 위한 코딩의 시기와 방식을 결정하라

> 다중 스레드 및 프로세스 기법을 사용할 때, 공유 개체를 최소화할 수 있는 방법과 올바르고 안전한 공유를 위한 시기를 알아야 한다.

<br>

### :pushpin: 스레드에 대한 설명

- 스레드는 상당히 범위가 넓은 영역
- 스레드의 영역은 중요하다.
- 중요 이슈
  - **데드락(deadlock) = 교착상태**
  - **라이브락(livelock)의 대비**
  - **경쟁 상태(race condition) - 지나친 경쟁 상황의 해결(적절하지 못한 잠금 때문에 발생하는 피해)**

<br>

### :pushpin: 데드락(deadlock) = 교착상태

- 두개 이상의 프로세스(혹은 스레드)가 자원을 공유하는 상황에서 서로 끝나기를 기다리는 상태를 의미

- **발생 조건**

  1. **상호배제(Mutual Exclusion)**

     > 한 번에 한 프로세스만 자원을 사용할 수 있어야 한다.
     >
     > 사용중인 자원을 다른 프로세스가 사용하려면 요청한 자원이 모두 사용된 후 해제될 때까지 기다려야 한다.

  2. **점유와 대기(Hold and Wait)**

     > 자원을 가진 상태에서 다른 프로세스가 사용하는 자원의 반납을 기다리는 상태

  3. **비선점(Non Preemptive)**

     > 다른 프로세스가 점유한 자원을 강제로 뺏어오지 못하는 것

  4. **순환(환형) 대기(Circle wait)**

     > 자원을 점유한 상태에서 또 다른 자원의 반납을 기다리는 상태가 순환형으로 연결된 대기 상태

<br>

### :pushpin: 라이브락(livelock)

- 두개 이상의 스레드가 다른 스레드의 행동에 영향을 받으며 진행되는 경우, 두 스레드는 lock의 해제와 획득을 무한 반복하여 또 다른 스레드가 자원을 획득할 수 없는 상황이 발생한다.
- 자원 획득의 처리가 진행되고 있음에도 불구하고 block된 것처럼 행동한다.
- 데드락을 피하려는 의도에서 수정된 코드가 불완전할 때 발생한다.

<br>

### :pushpin: 경쟁 상태(race condition)

- 여러 스레드 또는 프로세스가 한정된 공유 자원에 동시에 접근하는 경우
- 데이터의 불일치(inconsistency) 문제를 야기할 수 있다.
- 이를 해결하기 위해서는 **동기화(synchronize)**를 사용해야 한다.

<br>

### :pushpin: 애플리케이션 개발, 스레드 간의 안전한 데이터 공유 방법

1. **타겟 플랫폼의 문서를 참조하라**

   - 사소한 정수 연산에서부터 내부 프로세스 및 크로스 프로세스 연산까지 로컬 범위의 싱크로 문제에 대해서는 일단 타겟 플랫폼이 어떤 기능을 갖추고 있는지 확인할 것
   - 멀티스레드 프로그램에서 표준 라이브러리 구성 요소를 사용할 경우(string, container 등) 그 라이브러리의 문서를 통해 어떤 기능이 지원되는지 확실히 알아야 한다.

2. **플랫폼의 기본 기능들을 개발자의 자체적인 추상체에 포함시켜라**

   - 여러 플랫폼 간의 호환이 필요할 때 좋은 방법이다.
   - 플랫폼이 지원하는 기능을 그대로 쓰지 않고, 추상화하여 제어하는 것
   - 이 과정을 진행해주는 라이브러리를 사용하는 것도 또 다른 방법이다.

3. **사용하고 있는 타입이 멀티 스레드 프로그램에서 안전한지 확인하라**

   > :point_down: 각 타입에 필요한 조건

   - 공유되지 않는 개체들은 서로 독립적이어야 한다.

     > **두 스레드가 호출자 쪽에서의 특별한 조치 없이도 각 개체들을 자유롭게 사용 가능해야 한다.**

   - 서로 다른 스레드에 있는 해당 타입의 같은 개체를 사용할 때 호출자가 어떻게 해야 하는지 명시해 두어야 한다.

     > **공유 개체로의 접근이 일련화되어야 하는 타입이 대부분이지만, 그렇지 않은 경우도 있다.**
     >
     > **내부 또는 외부적으로 잠금 메커니즘 등이 필요하므로 주의해야 한다.**

<br>

### :pushpin: 멀티스레드 프로그램에서 사용할 용도로 자체적인 타입을 만들 때 주의점

1. 잠금 메커니즘 없이 서로 다른 스레드가 그 타입의 개체를 사용할 수 있어야 한다(변경 가능한 정적 데이터는 일반적으로 이 기능이 지원되지 않는다)

2. 서로 다른 스레드에서  같은 개체를 사용할 경우 어떤 과정이 필요한지 명시해 두어야 한다.

> 가장 기본적인 디자인 이슈 : 클래스와 클라이언트 사이의 올바른 실행(경쟁 또는 데드락 방지)을 위한 역할 분담
>
> :point_down: 사용 가능한 방법

> **[1] 외부 잠금**
>
> - 호출자가 잠금을 제어한다.
>
> - 이 옵션을 사용할 경우
>
>   > 1. 개체를 사용하는 코드에서는 해당 개체가 스레드 사이에 공유되어 있는지 확인 해야 한다.
>   > 2. 만약 공유되어 있다면 모든 개체 사용을 일련화해야 한다.
>
> - 개체가 문자열 타입의 경우
>
>   > 일반적으로 이 옵션이나 불변 방식을 사용한다.
>
> **[2] 내부 잠금**
>
> - 각 개체는 자신으로의 모든 접근을 일련화하고, 모든 공용 멤버 함수를 잠가 호출자가 개체 사용을 일련화할 필요가 없도록 해주는 방식
>
> - 생산자/소비자 큐 방식에서 일반적으로 사용하는 옵션이다.
>
>   > 개별적인 멤버 함수의 호출(Push, Pop)에 대해 적절한 수준의 잠금이 이루어지도록 디자인되는 방식
>
> - 이 옵션이 일반적으로 사용되는 경우
>
>   > 1. 해당 타입의 개체가 언제나 스레드 사이에서 공유될 것이라는 확신이 있어야 한다.
>   >    - 그렇지 않은 상황에서 이 옵션을 사용하면 필요 없는 잠금 때문에 성능에 악영향을 미친다.
>   >    - 대부분의 타입은 이 조건에 맞지 않는다.
>   >    - 멀티스레드에 크게 의존하는 프로그램이여도 스레드 간의 공유가 이루어지는 경우는 흔치 않다.
>   >
>   > 2. 각 멤버 함수에 대한 잠금이 대부분의 호출자에 대해 적절한 선택인지 확인해야 하며, 호출자가 하나의 작업이 아닌 여러 작업을 잠가야 하는 경우라면 이 옵션은 적절하지 않다.
>
> - 이 옵션을 사용하면 안되는 경우
>
>   > 1. 잠금의 주체가 호출자 위주로 이루어져야 할 때
>   >    - 유효하지 않은 반복자를 리턴하는 컨테이너 타입, 검색이 이루어지기 전에는 올바른 대답을 줄 수 없는 find와 같은 멤버 알고리즘을 생각했을 때
>   >    - 여러 가지 각각의 멤버 함수 호출이 모두 이루어질 때까지 유지될 수 있는 잠금을 호출자가 스스로 수행해야 한다.
>   >    - 즉, 내부 잠금은 불필요하다.
>
> - 내부 잠금은 공용 인터페이스와 밀접한 관계가 있다.
>
>   > 1. 타입의 각 작업이 완전히 독립적일 때 내부 잠금이 적당하다.
>   >    - 타입의 추상화 정도가 명확하게 표현되어야 하고, 캡슐화 되어야 한다는 의미
>   > 2. 기본 작업을 결합하여 보다 일반적이고 규모가 큰 작업을 만들 경우에는 내부 잠금이 적절치 않다.
>   >    - 콜백 기반의 모델(하나의 멤버 함수를 호출하면서 그 멤버 함수가 명령이나 함수 개체의 역할을 해주기 바라는 경우)을 사용하거나 잠금에 대한 정보를 어떤 방법으로든 공개하여 외부에서 제어할 수 있게 해줘야 한다.
>
> **[3] 읽기 전용 개체와 같이 잠금과 관계없는 디자인**
>
> - 잠금이 필요없도록 타입을 디자인하는 것도 가능하다.
>
> - 변하지 않는 개체가 좋은 예로, 변하지 않기 때문에 잠가둘 필요가 없다.
>
>   > 불변의 문자열 타입(const string)을 예시로,
>   >
>   > 한 번 만들어진 후 변하지 않으므로, 모든 문자열 작업에 의해 만들어지는 문자열은 모두 새로운 것으로 볼 수 있다.

<br>

### :pushpin: 멀티스레드 프로그래밍 요약

- 호출하는 코드는 타입에 대한 세부적인 정보를 알 필요가 없다는 것에 주의할 것

- 타입이 내부적인 데이터 공유 테크닉(copy-on-write과 같은)을 사용한다면 스레드 안전에 대한 문제를 개발자가 크게 신경 쓸 필요는 없다.

  > 표준 라이브러리 구성 문서에서 타입이 지원하는 기능을 확인해야 하는 이유

- 호출 코드가 **일반적인 방식으로** 그들의 작업을 수행하는 데에 필요한 **최소한의 스레드 안전성**을 보장하는 것은 개발자의 몫

  > [1] 타입을 사용하는 데 있어서는 최소한의 안전이 보장되어야 한다.
  >
  > [2] 각 타입은 서로 다른 스레드에 있는 구별된 개체를 충돌 없이 활용할 수 있게 만들어져야 한다.

<br>

### :pushpin: 잠금이 여러 번 일어날 때

- 같은 잠금에 연결된 모든 코드를 정렬하여 데드락이 발생하지 않도록 해야 한다.

  > [1] 메모리 주소를 기준으로 오름차순의 정렬을 하여 순서를 정한다.
  >
  > - 메모리 주소는 편리하고 고유하며, 애플리케이션 범위를 가지기 때문에 매우 유용하다.