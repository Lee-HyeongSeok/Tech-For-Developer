## 인라인(Inline) 함수 선언

***

<br>

### :pushpin: 인라인 함수 선언

- **기준 함수**

  > ```c++
  > const vector<int> * fibon_seq(int size){
  >     const int max_size=1024;
  >     static vector<int> elems;
  >     
  >     if(size <= 0 || size > max_size){
  >         cerr<<"fibon_seq(): oops: invalid size: "<<size<<" -- can't fullfill request.\n";
  >         return 0;
  >     }
  >     
  >     for(int ix-elems.size(); ix<size; ++ix){
  >         if(ix == 0 || ix == 1)
  >             elems.push_back(1);
  >         else
  >             elems.push_back(elems[ix-1]+elems[ix-2]);
  >     }
  >     return &elems;
  > }
  > ```

- **기준 함수의 분화 작업**

  > ```c++
  > bool is_size_ok(int size){
  >     const int max_size=1024;
  >     if(size <= 0 || size > max_size){
  >         cerr<<"Oops: requested size is not supported: "<<size<<" -- can't fullfill request.\n";
  >         return false; // 허용된 사이즈가 아닐 때 false 리턴
  >     }
  >     return true; // 허용된 사이즈 범위일 때 true 리턴
  > }
  > 
  > // size까지 피보나치 수열을 계산
  > // 항들을 저장한 정적 컨테이너의 주소를 반환
  > const vector<int>* fibon_seq(int size){
  >     static vector<int> elems;
  >     if(!is_size_ok(size))
  >         return 0;
  >     
  >     for(int ix=elems.size(); ix<size; ++ix){
  >         if(ix == 0 || ix == 1)
  >             elems.push_back(1);
  >         else
  >             elems.push_back(elems[ix-1]+elems[ix-2]);
  >     }
  >     return &elems;
  > }
  > 
  > // pos 위치의 피보나치 항을 반환
  > // 첫 항은 0의 위치에 저장되어 있기 때문에 1만큼을 빼야 한다.
  > // 위치가 지원되지 않으면 false 반환, 지원된다면 elem 참조 변수를 통해 전달
  > bool fibon_elem(int pos, int &elem){
  >     const vector<int> *pseq = fibon_seq(pos);
  >     
  >     if(!pseq){
  >         elem=0;
  >         return false;
  >     }
  >     
  >     elem = (*pseq)[pos-1];
  >     return true;
  > }
  > ```
  >
  > - **장점**
  >   - :point_right: 크기를 검사하는 부분은 is_size_ok(), 항들을 계산하는 부분은 fibon_seq()로 분화시킴으로써 fibon_elem()을 구현, 이해하는 것을 단순화시킬 수 있다.
  >   - :point_right: is_size_ok()와 fibon_seq() 함수는 다른 어플리케이션에서도 사용 가능(재사용성)
  > - **단점**
  >   - :point_right: fibon_elem()이 연산을 수행하기 위해서 함수를 세 번 호출해야 한다.
  >   - :point_right: 이러한 추가적인 오버헤드는 사용하는 환경에 따라 다르다.

- **인라인 함수화**

  > :point_right: **인라인 함수 선언** 
  >
  > 1. 컴파일러에게 특정한 요구를 하는 것(컴파일러는 함수가 호출되는 부분을 실제 실행되는 코드의 복사본으로 대체시킨다)
  > 2. 여러 개의 함수를 유지하면서도 fibon_elem() 함수를 하나로 합치는 성능 개선 효과
  > 3. 인라인 함수는 **보통 헤더 파일에 위치**
  > 4. 인라인 함수가 대체되어 들어가기 위해서는 호출하기 전에 그 정의가 있어야만 한다.
  > 5. **인라인 함수로 지정하기 좋은 함수는 자주 호출되며, 계산하기에 복잡하지 않은 경우**
  >
  > ```c++
  > // 함수의 정의 앞에 inline 키워드를 붙여서 인라인 함수를 선언
  > inline bool fibon_elem(int pos, int &elem){ 
  >     // ... 
  > }
  > ```



