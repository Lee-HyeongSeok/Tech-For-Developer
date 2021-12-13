## :round_pushpin: Spring Framework

***

<br>

### :pushpin: Spring Framework란?

- 단순히 라이브러리만 가져다 쓰는 것이 아니라 **의존성 주입(DI : Dependency Injection)**을 쉽게 구현할 수 있게 하여 모듈간의 결합을 쉽게 해주는 도구

  - **의존성 주입** : 인터페이스 타입만 생성하면 실제 객체에 접근 가능하도록 스프링 컨테이너에서 런타임시 생성해서 제공하는 것

    > **결합도를 낮춰준다.**

- **IoC** 컨테이너를 위해 사용

  - 역전제어(IoC) : 코딩할 때 객체간의 관계를 프로그래머가 결정했지만, 스프링 프레임워크 컨테이너가 객체를 생성해놓고<br> 필요 시점에 주입하는 것
  - DI 컨테이너라고도 부름
  - **IoC 컨테이너 역할**
    - 스프링 빈의 생명주기 관리
    - 의존관계 주입

<br>

### :pushpin: Spring Bean 이란?

- 의존 관계에 해당하는 객체
- 스프링 컨테이너가 관리하는 객체

<br>

### :pushpin: POJO(Plain Old Java Object)

-  특정 인터페이스 또는 클래스를 상속받을 필요 없는 가벼운 객체를 의미

<br>

### :pushpin: 의존성 주입(DI : Dependency Injection)

- 객체들 간의 **의존 관계를 설정**하는 것을 의미
- 프로그램 런타임 시 설정한 의존관계가 주입된다.
- 객체 간의 결합도를 낮춰준다.
- 의존성 주입을 수행하는 주체는 **Spring Container**이다.
- **설정 방법**
  1. XML 설정
  2. Annotation 설정
  3. Java 코드 설정

<br>

### :pushpin: Maven 이란?

- 자바용 프로젝트 관리 도구
- Maven의 기능은 크게 **프로젝트 관리**와 **빌드**가 있다.
  - 빌드 기능은 제공하지만 설정을 통해 빌드할 수 있는 환경을 구성해 주는 역할을 한다.
- pom.xml에 필요한 것을 명시하면 네트워크를 통해서 라이브러리들을 자동으로 다운받아준다.
- 프로젝트 **라이프사이클**에 포함되는 각 테스트를 지원해준다.
  - **라이프사이클** : 미리 정의된 빌드 순서, 빌드 단계를 Phase라고 한다.
- Maven은 각 라이프 사이클에 해당되는 **Goal**과 **Plugin**을 매칭시켜준다.
  - **Goal** : 빌드 시 기본적으로 해야될 작업
  - **Plugin** : Goal을 수행하는 주체

<br>

### :pushpin: 웹 애플리케이션 아키텍처

- 물리층과 논리층으로 나뉘어짐
- 물리층
  - 클라이언트
  - 중간
  - ELS(DB 등)
- 논리층
  - 프레젠테이션
  - 비즈니스 로직
  - 데이터 액세스

<br>

### :pushpin: 좋은 아키텍처 설계란?

- 프레젠테이션 층과 데이터 액세스 층의 변동이 비즈니스 로직에 영향을 받지 않게 하는 것
- 각 논리층 간에 결합 부분에 인터페이스를 사용하여 느슨한 결합 설계 및 구현이 필요

<br>

### :pushpin: Annotation을 사용하는 이유

- Annotation 이란
  - 추가적인 정보를 제공해주는 **메타데이터**
    - **메타데이터** : 데이터를 위한 데이터
- Annotation 용도
  - 컴파일러에게 코드 작성 문법 에러를 체크하도록 정보를 제공한다.
  - 스프링 프레임워크가 IoC 컨테이너에 의해 미리 객체를 생성해놓고 사용해야 하는데,<br> 이때 코드를 자동으로 생성할 수 있도록 정보를 제공하기 위함
  - 즉, 빌드나 배치 시에 코드를 자동으로 생성할 수 있도록 정보를 제공

<br>

### :pushpin: 스프링 JDBC란?

- 반복되는 처리를 개발자가 아닌 프레임워크에 위임하는 것
- **JDBC**와 **Spring JDBC**는 다름
- **JDBC**
  - DB에 접근할 수 있도록 Java에서 제공하는 API
- **Spring JDBC**
  - 일반 JDBC의 장점, 단순성을 그대로 유지
  - 간결한 형태의 API 사용법 제공
  - 반복 작업들을 프레임워크에서 대신 수행
  - 커넥션 연결 객체인 **DataSource**를 빈으로 등록 후 사용해야 함 -> 커넥션 풀 지원
    - **DataSource** : 데이터 액세스 기술(JDBC, MyBatis 등) 종류와 상관없이 DB 접속을 관리해주는 인터페이스
  - 쿼리 실행 결과를 어떤 객체에 넘겨 받을지 지정만 하면 된다.

<br>

### :pushpin: MVC 패턴 - 디자인 패턴

- Front Controller 패턴에 기초한 MVC 프레임워크
- Model, View, Controller

<br>

### :pushpin: Java Web Application 설계 방식

- Model 1
  - JSP로만 구현, Java Bean을 포함하여 개발
- Model 2
  - MVC 패턴 적용
  - 뷰와 베이스 로직을 분리시킨 구조
  - 클라이언트 요청마다 서블릿 생성
- Front Controller(= DispatcherServlet)
  - MVC 패턴 + Front Controller 패턴
  - Servlet Container에서 클라이언트 요청을 별도의 Front Controller에 집중
    - 이것을 **DispatcherServlet**이라 한다.

<br>

### :pushpin: Front Controller 패턴 처리 방식(흐름)

1. Tomcat이 클라이언트로부터 받은 요청을 **DispatcherServlet**에게 전달
2. **DispatcherServlet**은 개발자가 개발한 서브 컨트롤러에 요청을 위임
   - 이 단계에서 **DispatcherServlet**은 서브 컨트롤러를 Spring Bean으로 등록하는 과정이 있어야 함
3. 서브 컨트롤러는 DAO 객체를 호출하고, 결과를 처리해서 Model 객체에 저장 후 View 정보를 <br>**DispatcherServlet**에 리턴
4. **DispatcherServlet**은 어떤 화면을 처리해야 할 객체인지 알아내기 위해 View Resolver에 화면 처리를 요청
5. View Resolver는 적당한 객체를 **DispatcherServlet**에게 리턴
6. **DispatcherServlet**은 해당 결과 화면에 Model 객체를 가져와 처리하도록 요청
7. 이 결과를 요청했던 클라이언트에게 응답

![Untitled Diagram](https://user-images.githubusercontent.com/55940552/113391064-e38a4300-93cd-11eb-92b6-6fe1927c3f35.png) 

<br>

### :pushpin: WAS

- Tomcat은 main 처럼 시작점이 없기 때문에 **ContextLoaderListener Class**를 통해 **ServletContainer** 생성 시점에<br> 이벤트를 받아서 처리함

- **ServletContainer**가 클라이언트의 요청을 **DispatcherServlet Class**에 등록

- **DispatcherServlet Class**는 서브 컨트롤러에게 요청을 위임..

- 이후 **Front Controller Pattern** 흐름에 따라 처리 진행 

  > **ContextLoaderListener Class, DispatcherServlet Class 둘다 web.xml에 등록되어 있어야  Web Application Context를 만드는 과정을 수행 한다.**

<br>

### :pushpin: Annotation

- @Component : 일반적인 컴포넌트
  - @Repository : 프레젠테이션 층 컴포넌트
  - @Service : 비즈니스 로직 층 컴포넌트
  - @Controller : 프레젠테이션 층 컴포넌트
- @RestController = @Controller + @ResponseBody
  - 컨트롤러가 Rest API 형태로 JSON 포맷을 주고 받기 위해 별도로 구현한 애노테이션

<br>

### :pushpin: MyBatis란?

- SQL과 Java 객체를 매핑하는 사상에서 개발된 DB 접근용 프레임워크

<br>

### :pushpin: Spring Interceptor

- 컨트롤러의 호출 전과 후에 추가적 기능을 가능하도록 구조를 제공한다.
- DispatcherServlet과 Controller 사이에서 동작하며, 인터셉터는 사용자의 요청이 컨트롤러를 수행할 수 있는지에 대한 권한을 검사하고 실행 여부를 결정한다.
- Spring의 **Context** 범위 내에 존재하므로 Context의 모든 객체를 활용 가능하다.
  - **Context** : 스프링 컨테이너 내부에 컨텍스트라는 공간이 포함되어 존재, 스프링 빈을 다루기 쉽도록 기능들이 추가된 공간

<br>

### :pushpin: Spring Filter

- 서블릿, JSP에서 사용
- 웹 애플리케이션 내에서 동작하여 스프링 Context에 접근이 어렵다.
- 클라이언트의 요청에 대한 인증, 권한 확인 등에 사용된다.
- 클라이언트와 DispatcherServlet 사이에서 역할을 수행한다.

<br>

### :pushpin: Interceptor와 Filter의 차이점

- 영역 제어 측면
  - 인터셉터는 스프링 빈으로 등록된 컨트롤러, 서비스 객체를 주입 받는다.
- 위치적
  - 인터셉터는 Context 내에 존재하므로 내부의 모든 객체를 활용 가능하지만, 필터는 웹 애플리케이션 내에서 동작하므로 Context 접근이 어렵다.
- 처리 순서
  - 클라이언트와 DispatcherServlet 사이에서 역할을 수행하는 필터는 DispatcherServlet 호출 전에 동작하고, DispatcherServlet과 Controller 사이에서 역할을 수행하는 인터셉터는 DispatcherServlet 호출 후에 동작한다.

<br>

### :pushpin: Spring Security

- 애플리케이션 보안 기능 구현에 사용되는 프레임워크
- **인증, 인가** 기능 제공(다양한 필터 클래스를 통해..)
  - **인증** : 애플리케이션에 접근하는 사용자를 특정함
  - **인가** : 특정 사용자에 대한 정보 및 권한을 통해 리소르 접근을 제한

<br>

### :pushpin: Spring Boot 란

- Java를 기반으로 한 웹 애플리케이션 프레임워크
- Spring Framework의 초기 환경 설정시 시간이 많이 할애되는 문제를 해결하고자 설계됨
- Maven 또는 Gradle의 dependency에 **starter 라이브러리**만 작성하면 초기 셋팅에 필요한 라이브러리들을<br> 모두 세팅해준다.
  - **starter 라이브러리** : dependency에 존재하는 라이브러리들의 버전 관리를 자동으로 해줘<br> 버전이 맞지 않아 발생하는 오류 방지 가능
- 톰캣과 같은 내장 서버가 존재한다는 것

<br> 

### :pushpin: Gradle 이란?

- **그루비**를 기반으로 한 빌드 도구이다.
  - **그루비** : 빌드 스크립트를 JVM에서 동작하는 언어
- **Gradle Wrapper**를 이용하면 **Gradle**이 설치되지 않은 시스템에서도 프로젝트를 빌드할 수 있다.

