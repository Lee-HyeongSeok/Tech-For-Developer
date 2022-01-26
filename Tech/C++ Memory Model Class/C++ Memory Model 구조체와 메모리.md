## C++ Memory Model 구조체와 메모리

***

<br>

### :pushpin: 구조체와 메모리

```c++
#include <iostream>

using namespace std;

struct ST{
    int a; // 4bytes
    int b; // 4bytes
};

int main(){
    cout<<sizeof(ST)<<endl;
    return 0;
}
```

> 구조체 내부에 int형 변수 2개를 선언
>
> 실행 결과는 8bytes가 출력된다.

<br>

```c++
#include <iostream>

using namespace std;

struct ST{
	long a; // 8bytes
    int b; // 4bytes
    short c; // 2bytes
}

int main(){
    cout<<sizeof(ST)<<endl;
    return 0;
}
```

> 구조체 내부에 long, int, short형 변수 3개를 선언
>
> **출력 결과는 14bytes로 예상하지만, 실제 결과는 16byte임을 알 수 있다.**
>
> 이러한 이유는 메모리 접근 패턴 때문에 컴파일러가 자동으로 구조체 내부에 패딩 비트를 삽입한다.
>
> [패딩 비트에 대한 자료 추천]([https://youtu.be/CwhIC7PsVwE?list=PLDV-cCQnUlIYnyH__ziGIwFhaCnRtkkLt](https://www.youtube.com/watch?v=CwhIC7PsVwE&list=PLDV-cCQnUlIYnyH__ziGIwFhaCnRtkkLt))

<br>

```c++
#include <iostream>

using namespace std;

class Cat{
    public:
    	void printCat();
    private:
    	int age; // 4bytes
    	float weight; // 4bytes
}

int main(){
    cout<<sizeof(Cat)<<endl;
    return 0;
}
```

> Cat 클래스 내부에 멤버변수에 int, float형 변수 2개를 선언
>
> 8bytes임을 예상할 수도 있지만, printCat() 함수를 가리키는 포인터가 생길 수 있고, 포인터를 저장하기 위해 8bytes가 추가될 수도 있다는 생각을 할 수 있다.
>
> **하지만 실제 출력 결과는 8bytes가 나오는 것을 알 수 있다.**
>
> **결국 멤버함수는 클래스 사이즈와 상관없다는 것을 알 수 있다.**

<br>

```c++
int main(){
    Cat cat1;
    Cat cat2;
}
```

> Cat 클래스에 대한 객체 2개를 선언했을 때

![Untitled Diagram drawio (1)](https://user-images.githubusercontent.com/55940552/151197405-28510e4e-394a-4cba-a043-28a530148c8b.png) 

<br>

### :pushpin: 왜 포인터는 그것이 가리키는 타입에 상관없이 항상 8bytes 크기를 가지는 것인가?

```c++
int main(){
    Cat * catPtr = &cat1;
    cout<<sizeof(catPtr)<<endl; // 8bytes 출력
    return 0;
}
```

> [1] 64bit 환경에서 최대 가질 수 있는 자료형의 크기는 8bytes
>
> [2] 포인터는 격자 무늬의 메모리에서 각각의 주소를 나타내는 목적
>
> [3] 64bit 환경에서는 이 주소를 가리키기 위해서 8bytes의 크기가 필요하기 때문
>
> [4] 모든 포인터는 8bytes의 크기를 갖는 것이다.

<br>

### :pushpin: 멤버를 사이즈가 작은 순서로 작성하는 이유

> **멀티 프로세스에서 false sharing이 일어나지 않게 하기 위함**