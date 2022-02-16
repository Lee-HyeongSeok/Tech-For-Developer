## 상수 표현식(Constant Expressions)과 기본 매개변수

***

<br>

### :pushpin: 템플릿 매개변수로 상수 표현식을 선언할 수 있다.

예를 들어 항의 개수를 매개변수로 하는 템플릿 클래스를 정의할 수 있다.

```c++
template <int len>
class num_sequence{
    public:
    num_sequence(int beg_pos=1);
}

template <int len>
class Fibonacci : public num_sequence<len>{
    Fibonacci(int beg_pos=1): num_sequence<len>(beg_pos){}
}
```

위 코드에서 ```Fibonacci``` 객체를 아래와 같이 만든다면

```c++
Fibonacci<16> fib1; // beg_pos가 default인 1로 지정
Fibonacci<16> fib2(17); // beg_pos가 17로 지정
```

파생된 두 ```Fibonacci``` 인스턴스와 기본 클래스인 ```num_sequence```의 인스턴스 모두 len이 16으로 되어 생성된다.



또 다음과 같은 방법으로 길이와 시작 위치 모두를 매개변수로 만들 수 있다.

```c++
template <int len, int beg_pos>
class NumericSeries;

// 대부분의 클래스 객체는 1의 위치에서 시작
template <int len, int beg_pos>
class num_sequence{};

template <int len, int beg_pos=1> // 기본값으로 제공하는 것이 편리
class Fibonacci : public num_sequence<len, beg_pos>{
    // ...
}
```

위 클래스 객체들은 아래와 같이 정의될 수 있다.

```c++
// 다음과 같이 확장할 수 있다.
num_sequence<32, 1> *pns1to32 = new Fibonacci<32, 1>;

// 기본 매개변수 값을 오버라이딩
num_sequence<32, 33> *pns33to64 = new Fibonacci<32, 33>;
```

함수의 기본 매개변수값과 같이 기본 매개변수값은 **오른쪽에서 왼쪽**으로 결정된다.



### :pushpin: 기본 매개변수값을 이용한 구현

```c++
// num_sequence class
// 길이와 시작 위치를 템플릿 매개변수로 저장한다.

template <int len, int beg_pos>
class num_sequence{
    public:
    virtual ~num_sequence(){};
    int elem(int pos) const;
    const char* what_am_i() const;
    static int max_elems(){ return _max_elems; }
    ostream& print(ostream &os=cout) const;
    
    protected:
    virtual void gen_elems(int pos) const=0;
    bool check_integrity(int pos, int size) const;
    num_sequence(vector<int> *pe) : _pelems(pe){}
    static const int _max_elems=1024;
    vector<int> *_pelems;
};
```

```c++
// 출력 연산자 함수 템플릿의 정의(비멤버)
template <int len, int beg_pos> 
ostream& operator<<(ostream &os, const num_sequence<len, beg_pos> &ns){
    return ns.print(os);
}
```

```c++
// num_sequence class member
template <int len, int beg_pos>
int num_sequence<len, beg_pos>::elem(int pos) const{
    if(!check_integrity(pos, _pelems->size()))
        return 0;
    return (*_pelems)[pos-1];
}

template <int length, int beg_pos>
const char* num_sequence<length, beg_pos>::what_an_i() const{
    return typeid(*this).name(); // typeid를 위한 헤더를 포함해야 함
}

template <int length, int beg_pos>
bool num_sequence<length, beg_pos>::check_integrity(int pos, int size) const{
    if(pos <= 0 || pos > max_elems()){
        cerr<<"invalid position : "<<pos<<'\n';
    	return false;
    }
    if(pos > size) gen_elems(pos);
    return true;
}

template <int length, int beg_pos>
ostream& num_sequence<length, beg_pos>::print(ostream &os) const{
    int elem_pos = beg_pos-1;
    int end_pos = elem_pos + length;
    
    if(!check_integrity(end_pos, _pelems->size()))
        return os;
    
    os<<"("<<beg_pos<<", "<<length<<")";
    
    while(elem_pos < end_pos)
        os<<(*_pelems)[elem_pos++]<<' ';
    return os;
}
```

```c++
// 기본 매개변수값이 있는 Fibonacci 클래스 템플릿

template <int length, int beg_pos=1>
class Fibonacci : public num_sequence<length, beg_pos>{
    public:
    Fibonacci() : num_sequence<length, beg_pos>(&_elems){}
    
    protected:
    virtual void gen_elems(int pos) const;
    static vector<int> _elems;
};
```

```c++
// Fibonacci member

template <int length, int beg_pos>
vector<int> Fibonacci<length, beg_pos>::_elems;

template <int length, int beg_pos>
void Fibonacci<length, beg_pos>::gen_elems(int pos) const{
    if(pos <= 0 || pos > max_elems())
        return;
    
    if(_elems.empty()){
        _elems.push_back(1);
        _elems.push_back(1);
    }
    
    if(_elems.size() <= pos){
        int ix = _elems.size();
        int n_2 = _elems[ix-2];
        int n_1 = _elems[ix-1];
        
        int elem;
        for(; ix <= pos; ++ix){
            elem = n_2 + n_1;
            _elems.push_back(elem);
            n_2 = n_1;
            n_1 = elem;
        }
    }
}
```

```c++
int main(){
    Fibonacci<8> fib1;
    Fibonacci<8, 8> fib2;
    Fibonacci<12, 8> fib3;
    
    cout<<"fib1 : "<<fib1<<'\n';
    cout<<"fib2 : "<<fib2<<'\n';
    cout<<"fib3 : "<<fib3<<'\n';
    
}
```

<br>

### :pushpin: 매개변수로 함수의 포인터를 취하는 수열 클래스

```c++
template <void (*pf)(int pos, vector<int>&seq)>
class numeric_sequence{
    public:
    numeric_sequence(int len, int beg_pos=1){
        if(!pf)
            return 0;
        
        _len = len > 0 ? len : 1;
        _beg_pos = beg_pos > 0 ? beg_pos : 1;
        
        pf(beg_pos + len-1, _elems);
    }
    
    private:
    int _len;
    int _beg_pos;
    vector<int> _elems;
};
```

이는 다음과 같이 쓰인다.

```c++
void fibonacci(int pos, vector<int> &seq);
void pell(int pos, vector<int> &seq);
// ...

numeric_sequence<fibonacci> ns_fib(12);
numeric_sequence<pell> ns_pell(18, 8);
```

