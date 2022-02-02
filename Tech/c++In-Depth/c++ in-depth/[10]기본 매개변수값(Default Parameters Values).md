## 기본 매개변수값(Default Parameters Values)

***

<br>



### :pushpin: 기본 매개변수 값(Default Parameters Values)

- 일반적인 프로그래밍에서는 파일 스코프에서 정의된 객체를 사용하는 것보다 매개변수를 사용하여 함수간 통신을 하는 것이 더 좋다.

  - :point_right: 파일 스코프에 정의된 객체에 의존하는 함수는 다른 환경에서 재사용이 어렵다.
  - :point_right: 함수 수정이 어렵다(함수의 논리성과 파일 스코프에 정의된 객체의 논리성도 이해해야 하기 때문)

- 예시

  > ```c++
  > void bubble_sort(vector<int> &vec, ofstream &ofile){
  >     for(int ix=0; ix<vec.size(); ++ix){
  >         for(int jx=ix+1; jx<vec.size(); ++jx){
  >             if(vec[ix] > vec[jx]){
  >                 ofil<<"about to call swap! ix : "<<ix<<" jx : "<<jx<<"\tswapping: "<<vec[ix]<<" with "<<vec[jx]<<endl;
  >                 swap(vec[ix], vec[jx], ofil);
  >             }
  >         }
  >     }
  > }
  > ```
  >
  > 1. 파일 스코프의 의존성을 제거했지만, bubble_sort()를 호출할 때마다 ofstream 클래스 객체를 전달해야 한다.
  > 2. 또한 사용자는 이 기능을 중단할 수 없기 때문에 이런 디버깅 정보가 매번 생성된다.
  >
  > <br>
  >
  > **이때 기본적으로는 정보를 생성하지 않고(ofstream) 필요한 상황에서만 이런 정보를 생성하려 할때**
  >
  > :point_right: 매개변수 또는 일부의 매개변수에 대해 기본값(default value)을 지정하여 해결한다.
  >
  > <br>
  >
  > ```c++
  > void bubble_sort(vector<int> &vec, ofstream *ofile=0){
  >     // ...
  > }
  > ```
  >
  > 1. 개선된 bubble_sort() 에서는 두 번째 매개변수 ofstream을 포인터로 선언
  >
  >    - :point_right: 레퍼런스는 항상 어떤 객체를 참조해야 하기 때문에 0이 될 수 없다.
  >
  >    - :point_right: 기본값으로 어떤 ofstream도 가리키지 않는 0을 주기 위해 변경
  >
  > 2. 이를 통해 하나의 인수로 bubble_sort()를 호출하면 어떤 디버깅 정보도 생성되지 않는다.
  >
  > 3. 두 번째 인수로 ofstream 객체의 주소를 지정해서 함수를 호출하면 디버깅 정보를 생성한다.

<br>

### :pushpin: 기본 매개변수 값의 규칙

- 기본값은 그 위치가 오른쪽 매개변수부터 시작되어야 한다.

  > ```c++
  > void display(const vector<int> &vec, ostream &os = cout);
  > ```

- 선언이나 함수의 정의에서 기본값은 단 한 번만 지정될 수 있다(양쪽에서 지정 불가)

  - :point_right: 일반적으로, **헤더 파일**에 위치한 함수의 선언에 지정
  - :point_right: 함수의 정의는 일반적으로 프로그램 텍스트 파일에 위치(이 파일은 한 번만 컴파일되고, 함수를 사용할 때마다 프로그램에 연결(linking) 된다)

  > ```c++
  > // 헤더 파일
  > void display(const vector<int> &, ostream &= cout); // 함수의 선언에서 기본값 지정
  > ```
  >
  > ```c++
  > // 소스 파일(프로그램 텍스트 파일)
  > void display(const vector<int> &vec, ostream &os){ // 함수의 정의에서 기본값 미지정
  >     // ...
  > }
  > ```

