## 템플릿 프로그래밍(template programming) - 이진트리 클래스 템플릿

***

<br>

### :pushpin: 초기 C++ 언어 설계

- 템플릿을 매개변수화된 타입(parameterized)이라고 불렀다.

  > 정의에서 공통된 요소를 뽑아내므로 매개변수화되었다고 하며, 클래스 또는 함수 템플릿이 일반적으로 하나나 그 이상의 타입에 의해 변화하므로 타입이라고 한다.

- 실제 타입은 나중에 사용자가 지정한다.

- 템플릿의 정의

  > 사용자가 지정한 값이나 타입에 따라 고유한 인스턴스를 자동으로 생성하게 해준다.

<br>

### :pushpin: 이진 트리(Binary Tree)

> Tree : 노드와 노드들을 연결하는 링크로 이루어지며, 루트라고 부르는 최초의 노드를 가진다.

> Binary Tree : 노드가 두 개의 링크를 갖는 형태(자식 노드가 2개)
>
> :point_right: 일반적으로 왼쪽 자식과 오른쪽 자식으로 부른다.
>
> :point_right: 왼쪽 자식과 오른쪽 자식은 각각 자신들의 서브 트리(subtree)에 대해서 루트로 기능할 수 있다.
>
> :point_right: 자식을 갖지 않는 노드는 리프 노드(leaf node)라고 부른다.



<br>

### :pushpin: 템플릿 이진 트리의 설계

- 두 개의 클래스로 구성된다.

  1. 루트를 가리키는 포인터를 갖는 BinaryTree 클래스
  2. 실제 값과 왼쪽 자식, 오른쪽 자식의 링크를 갖는 BTnode 클래스
  3. 노드 값의 타입은 매개변수화시키게 된다(template)

- 지원되어야 할 BinaryTree의 연산

  1. 사용자는 요소들을 삽입(insert)하거나 삭제(remove)할 수 있어야 한다.
  2. 어떤 요소가 있는지 검색(find)할 수 있어야 한다.
  3. 모든 트리의 요소를 제거(clear)할 수 있어야 한다.
  4. inorder, preorder, postorder라는 세 가지 탐색(traversal) 알고리즘에 의해 출력(print)할 수 있어야 한다.

- 메커니즘

  - 비어 있는 트리에 삽입되는 최초의 값은 루트가 된다.

  - 뒤따라 삽입되는 모든 값들은 루트보다 작으면 루트의 왼쪽 서브트리에 위치, 크다면 루트의 오른쪽 서브트리에 위치

  - 같은 트리 내에서 같은 값이 중복되어 저장되지 않는다, 같은 값이 삽입되면 그 대신 빈도수를 증가시킨다.

    > #1
    >
    > ```BinaryTree<string> bt;```
    >
    > ```bt.insert("piglet");```
    >
    > :point_right: piglet은 이진 트리의 루트가 된다(최초의 삽입)
    >
    > #2
    >
    > ```bt.insert("Eeyore");```
    >
    > :point_right: Eeyore는 알파벳상에서 piglet보다 작기 때문에 piglet의 왼쪽 자식이 된다.
    >
    > #3
    >
    > ```bt.insert("Roo");``` Roo는 piglet보다 크기 때문에 piglet의 오른쪽 자식이 된다.
    >
    > #4-
    >
    > ```bt.insert("Tigger");```
    >
    > ```bt.insert("Chris");```
    >
    > ```bt.insert("Pooh");```
    >
    > ```bt.insert("Kanga");```
    >
    > :point_right: 이렇게 하여 이진트리의 결과는 아래와 같다.
    >
    > ![Untitled Diagram drawio (3)](https://user-images.githubusercontent.com/55940552/152998559-60d9c2a2-2bbc-4f43-99ca-8199bfda1eca.png) 
    >
    > - Chris, Kanga, Pooh, Tigger는 리프 노드(leaf node)

<br>

### :pushpin: 탐색(traversal) 알고리즘 - preorder, inorder, postorder

> 루트(root) 노드에서 시작
>
> ![Untitled Diagram drawio (3)](https://user-images.githubusercontent.com/55940552/152998559-60d9c2a2-2bbc-4f43-99ca-8199bfda1eca.png) 

- **preorder 탐색** : 노드 먼저 출력, 왼쪽 자식 방문, 오른쪽 자식 방문

  > Piglet, Eeyore, Chris, Kanga, Roo, Pooh, Tigger

- **inorder 탐색** : 왼쪽 자식 먼저 방문 후 노드 출력, 오른쪽 자식 방문

  > Chris, Eeyore, Kanga, Piglet, Pooh, Roo, Tigger

- **postorder 탐색** : 왼쪽 자식과 오른쪽 자식을 방문한 후에 노드 출력

  > Chris, Kanga, Eeyore, Pooh, Tigger, Roo, Piglet

<br>



### :pushpin: 매개변수화된 타입(Parameterized Types)

> BTnode에 대한 비 템플릿 선언
>
> 이 노드에 저장되는 값은 string 클래스의 객체

```c++
class string_BTnode{
  public:
  private:
  	string _val;
  	int _cnt;
  	string_BTnode *left_child;
  	string_BTnode *right_child;
};
```

:point_right: 템플릿 메커니즘이 없다면?

- 각 타입에 대해 서로 다르게 구현된 BTnode 클래스 필요

:point_right: 템플릿 메커니즘 영향

- 타입에 의존적인 부분, 클래스 정의에서 변하지 않는 부분을 분리시켜 준다.
  - 탐색, 삽입, 삭제, 개수 저장 등의 연산은 값의 타입과 관계 없이 모두 동일
  - 각 노드에 저장된 값의 타입은 클래스 템플릿의 각 인스턴스에서 바뀌게 된다.



<br>

### :pushpin: 이진 트리의 구현

- 2개의 클래스로 구성
  1. Root를 가리키는 포인터를 갖는 BinaryTree class
  2. 실제 값과 왼쪽 자식, 오른쪽 자식의 링크를 갖는 BTnode class(노드 값의 타입은 매개변수화, 템플릿화 시킨다)

<br>

### :pushpin: BinaryTree에서 지원할 연산

- 삽입(insert)
  - 비어 있는 트리에 삽입되는 최초의 값은 루트가 된다.
  - if 삽입되는 값 < 루트 값 : 루트의 왼쪽 서브 트리에 위치
  - if 삽입되는 값 > 루트 값 : 루트의 오른쪽 서브 트리에 위치
  - 같은 트리 내 중복되는 값은 저장하지 않지만, 빈도수를 증가시킨다.
- 삭제(remove)
- 요소 검색(find)
- 모든 요소 제거(clear)
- 탐색(traversal) 알고리즘 - inorder, preorder, postorder
  - inorder : 왼쪽 자식 먼저 방문 후 노드 출력, 오른쪽 자식 방문
  - preorder : 노드가 먼저 출력, 왼쪽 자식 방문, 오른쪽 자식 방문
  - postorder : 왼쪽 자식과 오른쪽 자식 방문 후 노드 출력
- 출력(print)

<br>



### :pushpin:  BTnode의 구현

> string_BTnode 클래스 매개변수화

```c++
template <typename valType>
class BTnode{
	valType _val; // 여러 타입을 받을 수 있는 변수 _val
	int _cnt;
	BTnode * left_child;
	BTnode * right_child;
};
```

> 실제 값, 빈도수, 왼쪽 자식과 오른쪽 자식 링크(포인터)를 가진다.
>
> 그리고
>
> BTnode 클래스는 그에 대응하는 BinaryTree 인스턴스가 프렌드로 되어야 한다.
>
> ```c++
> template <typename Type>
> class BinaryTree; // 전방 선언
> 
> template <typename valType>
> class BTnode{
> 	friend class BinaryTree<valType>; // friend 선언
> }
> ```

<br>

### :pushpin: friend 키워드

> c++ 에서 지원하는 예외적인 기능의 키워드로 접근 지정자를 무시할 수 있는 기능을 가졌다.
>
> :point_right: private 또는 protected에서 friend로 선언된 대상에게는 public으로 작용한다.
>
> friend로 선언한 주체 클래스의 private, protected 멤버에 friend로 선언 당한 클래스가 접근할 수 있다.
>
> 정보 은닉 개념에 위배된다.

<br>

### :pushpin: BinaryTree의 구현

> BinaryTree 클래스는 데이터 멤버 하나를 선언 :point_right: 트리의 루트 노드를 가리키는 BTnode의 포인터

```c++
template <typename Type>
class BinaryTree{
public:
	BinaryTree();
	BinaryTree(const  BinaryTree&);
	~BinaryTree();
	BinaryTree& operator=(const BinaryTree&);
	bool empty(){ return root==0; }
	void clear();
private:
	BTnode<Type> * root;
	void copy(BTnode<Type> *tar, BTnode<Type> *src);
};

template <typename valType>
class BTnode{
public:
private:
	valType value;
	int cnt;
	BTnode * left_child;
	BTnode * right_child;
}

template <typename Type>
inline BinaryTree<Type>::BinaryTree() : root(0){ }

template <typename Type>
inline BinaryTree<Type>::~BinaryTree(){ clear(); }

// 복사 생성자
template <typename Type>
inline BinaryTree<Type>::BinaryTree(const BinaryTree &rhs){
	copy(root, rhs.root);
}
// 복사 대입 연산자
template <typename Type>
inline BinaryTree<Type>& BinaryTree<Type>::operator=(const BinaryTree &rhs){
  if(this != &rhs){
      clear();
      copy(root, rhs.root);
  }
  return *this;
}

// 소멸자

```

> 클래스 템플릿의 이름에 매개변수 목록을 붙이는 것이 제외된 경우는? (템플릿 클래스의 이름에 매개변수 목록을 붙이는 것을 의미)
>
> - 클래스 템플릿의 정의
> - 클래스 템플릿에 멤버들의 정의
>
> 그 외의 경우 :point_right: 템플릿 클래스의 이름에 매개변수 목록을 붙여야 한다.
>
> ```BinaryTree<string> st;``` BinaryTree 매개변수로 이와 같이 실제 타입을 명시한다면 ```BTnode<Type> *root```는 string 타입 값을 갖는 BTnode 객체의 포인터가 된다.

<br>

### :pushpin: 템플릿 타입 매개변수의 처리

- 명시적 int 매개변수 함수 선언

  > ```bool find(int val);```
  >
  > 위 함수는 값에 의한 전달을 진행

- 명시적 Matrix 클래스 매개변수 함수 선언

  > ```bool find(const Matrix& val);```
  >
  > Matrix 클래스 전체를 복사하지 않고 레퍼런스에 의해 전달하고 있다.

- 왜 이런 차이점이 생길까?

  - 클래스를 인자로 전달할 때 값에 의한 전달은 비효율적이다.

    > :point_right: find가 빈번히 호출될 경우 속도가 느리다.
    >
    > 클래스를 복사할 메모리 영역을 만들고, 내부 멤버를 복사해야 하며, 복사 생성자를 호출하는 부분이 생기기 때문이라고 이해하고 있음

- 그렇다면 템플릿 타입의 매개변수를 다룰 때는?

  - 사용자에 의해 지정되는 실제 값이 어떤 타입이라고 예측 불가

  - 즉, 값에 의한 전달을 했을 때 성능이 위험할 수도 있다.

    > ```BinaryTree<int> bt;``` 의 경우 기본 타입이라면 find() 함수의 매개변수가 값에 의한 전달이 낫다.
    >
    > ```BinaryTree<Matrix> btm;``` 의 경우 클래스 타입이라면 find() 함수의 매개변수가 레퍼런스에 의한 전달이  낫다.

  - 권장하는 프로그래밍 전략

    > 템플릿 타입의 매개변수가 클래스 타입일 것이라 가정하고 처리하라

  - 생성자의 정의 내에서 권장하는 프로그래밍 전략

    > 멤버 초기화 목록에서 각 타입 매개변수를 초기화하라(템플릿 타입)
    >
    > :point_right: 생성자의 몸체 안에서 초기화하는 것은 바람직하지 못하다(클래스 타입일 수도 있기 때문)
    >
    > ```val = const valType &val``` 형식이고 valType이 클래스라면 대입 생성자의 호출 야기
    >
    > ```val(const valType &val)``` 형식이라면 valType으로 클래스 타입을 지정했을 때도 성능 최적화를 보증
    >
    > ```c++
    > template <typename valType>
    > inline BTnode<valType>::BTnode(const valType &val): val(val){ cnt=1; left_child=right_child=0; }
    > ```

  - 생성자 & 복사 생성자 & 레퍼런스에 의한 전달

    > ```BTnode<int> btni(42);``` 와 ```BTnode<Matrix> btnm(transform_matrix);``` 는 성능 상의 차이점 존재
    >
    > 1. BTnode 생성자의 몸체가 실행되기 전에 Matrix 생성자가 BTnode에서 복사될 변수에 적용됨
    > 2. 복사 주체를 매개변수로 넘겨 복사 대상의 복사 대입 연산자를 적용
    >
    > :point_right: 하지만 생성자의 멤버 초기화 목록에서 복새 대상을 초기화하면 하나의 단계만을 거친다(복사 대상의 복사 생성자만 호출한다)

<br>

### :pushpin: 템플릿 클래스의 구현

- 새로운 값의 삽입(insert 연산 구현)

  - BTnode 객체 생성, 초기화, 연결 과정 필요
  - 각 노드의 할당과 해제는 new, delete 연산자를 통해 관리
  - root가 빈 상태라면 새로운 BTnode를 할당, 그렇지 않다면 BTnode의 insert_value()를 호출하여 트리에 새로운 값 삽입

  ```c++
  template <typename Type>
  inline void BinaryTree<Type>::insert(const Type& elem){
  	if(!root) // root가 비었을 때
  		root = new BTnode<Type>(elem); // 최초의 노드, root가 된다.
  	else // 그렇지 않을 때
  		root->insert_value(elem); 
  }
  ```

> 위 코드에서 new 연산자가 수행하는 연산은 두 단계를 거친다.
>
> 1. 프로그램의 빈 공간(free store)에 메모리 요구
>    - 충분한 메모리가 있다면 객체의 포인터가 반환된다(해당 메모리의 첫 번째 주소)
>    - 그렇지 않다면 bad_alloc 예외 발생
> 2. 첫 단계 성공 시 객체는 적절하게 초기화 된다.
>
> ```new BTnode<Type>(elem);```에서 elem을 BTnode의 생성자로 전달한다.

```c++
// insert_value()의 구현, BTnode class

template <typename valType>
void BTnode<valType>::insert_value(const valType& val){
  if(value == val){ // 중복 값이 있으면 빈도수 증가, 함수 종료(중복 값 저장 x)
      cnt++;
      return;
  }
  
  if(value > val){ // root의 값보다 삽입 대상 값이 더 작다면 왼쪽 서브 트리로
  	if(!left_child) // 현재 root 기준으로 왼쪽 자식이 없다면
  		left_child = new BTnode(val); // 메모리 생성 후 자신이 왼쪽 자식이 됨
  	else // 현재 root 기준으로 왼쪽 자식이 존재한다면
  		left_child->insert_value(val); // 왼쪽 자식의 insert_value()를 호출하여 값의 위치 검사 후 동작 수행
  }
  else{ // root의 값보다 삽입 대상 값이 더 크다면 오른쪽 서브 트리로
  	if(!right_child)
  		right_child = new BTnode(val);
  	else
  		right_child->insert_value(val);
  }
}
```



- 기존에 값을 삭제(remove 연산 구현)

  - 삭제 알고리즘

    > 삭제된 대상의 왼쪽 자식은 대체된 오른쪽 자식의 왼쪽 서브트리의 리프 노드로 연결된다.

```c++
template <typename Type>
inline void BinaryTree<Type>::remove(const Type& elem){
if(root){ // 노드가 존재할 때
	if(root->value == elem) remove_root(); // root 노드의 삭제는 특수한 경우로 처리한다.
	else root->remove_value(elem, root); // 삭제 대상 노드가 root 노드가 아닐 때, 삭제 프로세스 진행
}
```

> ```remove_root()```와 ```remove_value()``` 모두 왼쪽 자식을 오른쪽 자식 서브트리의 리프 노드로 붙인다.
>
> 이러한 연산을 BTnode class에서 ```left_child_leaf()```로 따로 구현한다.

```c++
template <typename valType> // leaf node, 서브 트리 root
void BTnode<valType>::left_child_leaf(BTnode *leaf, BTnode *subtree){
	while(subtree->left_child) // 서브 트리의 왼쪽 자식 노드가 존재할 때까지 loop
      subtree = subtree->left-child;
  	subtree->left_child = leaf; // leaf 노드를 서브 트리의 가장 왼쪽 leaf 노드에 연결
}
```

> ```remove_root()```는 존재하는 자식들 중 하나를 루트 노드로 셋팅한다.

```c++
template <typename Type>
void BinaryTree<Type>::remove_root(){
	if(!root) return; // root노드가 비어있을 때
	
	BTnode<Type> *temp = root; // root 노드를 잠시 저장
    if(root->right_child){ // 현재 root의 오른쪽 자식이 존재하면
    	root = root->right_child; // 오른쪽 자식으로 이동
    	
        if(temp->left_child){
        	BTnode<Type> *lc = temp->left_child;
        	BTnode<Type> *newlc = root->left_child;
        	
        	if(!newlc) root->left_child = lc;
        	else BTnode<Type>::left_child_leaf(lc, newlc);
        }
    }
    else root = root->left_child;
    
    delete temp;
}
```

> ```remove_value()```는 두 개의 매개변수를 취한다.
>
> 1. 삭제될 값
> 2. 검색을 시작할 노드의 부모 노드
>    - 부모 노드는 포인터로 넘겨진다.

```c++
template <typename valType>
void BTnode<valType>::remove_value(const valType &val, BTnode *&prev);
```

> 두 번째 매개변수 prev는 왜 포인터의 레퍼런스로 넘기는가?
>
> 매개변수로 포인터를 넘기는 것은 포인터에 의해 가리키는 객체를 변경시킬 수 있다.
>
> 하지만 포인터에 셋팅된 주소는 변경 불가능 하다.
>
> 실제 주소값을 변경하기 위해서는 prev를 포인터의 레퍼런스로 선언하여 그 주소값과 주소가 가리키는 객체 모두를 변경할 수 있다.

```c++
template <typename valType>
void BTnode<valType>::remove_value(const valType& val, BTnode *& prev){
  if(val < value){ // 삭제 하려는 값이 현재 노드의 값보다 작을 때
	if(!left_child) return; // 왼쪽 자식이 존재하지 않음
	else left_child->remove_value(val, left_child);
  }
  else if(val > value){ // 삭제 하려는 값이 현재 노드의 값보다 클 때
  	if(!right_child) return; // 오른쪽 자식이 존재하지 않음
  	else right_child->remove_value(val, right_child);
  }
  else{ // 삭제 하려는 값을 찾았을 때
    if(right_child){
		prev = right_child;
        if(left_child){
        	if(!prev->left_child) prev->left_child = left_child; // 대체된 오른쪽 자식의 왼쪽 서브트리가 없다면, 그 자리에 삭제 대상의 왼쪽 서브트리를 연결
        }
        else
        	BTnode<valType>::left_child_leaf(left_child, prev->left_child);
    }
    else // 오른쪽 서브트리가 없을 때
    	prev = left_child;
    	delete this;
  }
}
```



- 모든 트리를 제거(clear 연산)
  - 인라인 public 함수와 실제로 작업을 하는 오버로딩된 private 인스턴스로 구현되었다.

```c++
// BinaryTree.h
public: 
void clear(){ // 인라인 public 함수
  if(root){
    clear(root); // 오버로딩된 private 인스턴스
    root = 0;
  }
}

private:
void clear(BTnode<Type> *);
```

```c++
template <typename Type>
void BinaryTree<Type>::clear(BTnode<Type> *pt){ // 리프 노드부터 순차적으로 제거
  if(pt){
	clear(pt->left_child);
	clear(pt->right_child);
	delete pt;
  }
}
```



<br>

### :pushpin: 이진트리 클래스 템플릿 전체 구현 코드



아래 코드는 ```BTnode.h``` 헤더의 선언이다.

```c++
#ifndef BTnode_h
#define BTnode_h

// BinaryTree 전방 선언
template <typename Type>
class BinaryTree;

template <typename valType>
class BTnode{
public:
	BTnode(const valType&); // 어떤 타입의 값이 전달될지 모르므로 참조 선언
	void insert_value(const valType&);
	static void left_child_leaf(BTnode*, BTnode*);
	void remove_value(const valType&, BTnode*&); // 주소와 값 모두를 변경하기 위한 포인터 참조 연산자 형태
	// 탐색 메서드
	void preorder(BTnode*, std::ostream&) const;
	void inorder(BTnode*, std::ostream&) const;
	void postorder(BTnode*, std::ostream&) const;
	
	void display_val(BTnode*, std::ostream&) const;
private:
	friend class BinaryTree<valType>;
	valType value;
	int cnt;
	BTnode* left_child;
	BTnode* right_child;
};
```

<br>

아래 코드는 ```BTnode.h```의 정의이다.

```c++
template <typename valType>
inline BTnode<valType>::BTnode(const valType& val) : value(val){
	cnt=1;
	left_child = right_child = 0;
}
template <typename valType>
void BTnode<valType>::insert_value(const valType& val){
  if(value==val){
  	cnt++;
  	return;
  }
  if(value > val){
  	if(!left_child) left_child = new BTnode(val);
  	else left_child->insert_value(val);
  }
  else{
  	if(!right_child) right_child = new BTnode(val);
  	else right_child->insert_value(val);
  }
}
template <typename valType>
void BTnode<valType>::left_child_leaf(BTnode* leaf, BTnode* subtree){
	while(subtree->left_child)
		subtree = subtree->left_child;
	subtree->left_child=leaf;
}

template <typename valType>
void BTnode<valType>::remove_value(const valType& val, BTnode*& prev){
  if(val < value){ // 삭제하려는 값이 현재 노드 값보다 작을 때
	if(!left_child) return;
	else left_child->remove_value(val, left_child);
  }
  else if(val > value){
  	if(!right_child) return;
  	else right_child->remove_value(val, right_child);
  }
  else{
  // 오른쪽 자식의 왼쪽 서브트리 리프 노드로 붙이는 알고리즘이기 때문에 right_child의 유무를 검사
    if(right_child){
		prev = right_child;
		
        if(left_child){
        	if(!prev->left_child) prev->left_child = left_child;
        }
        else{
        	// 왼쪽 서브트리 리프 노드를 찾기 위한 left_child_leaf 메서드 실행
        	BTnode<valType>::left_child_leaf(left_child, prev->left_child);
        }
    }
    else{
    	prev = left_child;
    }
    delete this;
  }
}

template <typename valType>
void BTnode<valType>::preorder(BTnode* pt, std::ostream& os) const{
  if(pt){
	display_val(pt, os);
	if(pt->left_child) preorder(pt->left_child, os);
	if(pt->right_child) preorder(pt->right_child, os);
  }
}

template <typename valType>
void BTnode<valType>::inorder(BTnode* pt, std::ostream& os) const{
  if(pt){
	if(pt->left_child) preorder(pt->left_child, os);
	display_val(pt, os);
	if(pt->right_child) preorder(pt->right_child, os);
  }
}

template <typename valType>
void BTnode<valType>::postorder(BTnode* pt, std::ostream& os) const{
  if(pt){
	if(pt->left_child) preorder(pt->left_child, os);
	if(pt->right_child) preorder(pt->right_child, os);
	display_val(pt, os);
  }
}

template <typename valType>
void BTnode<valType>::display_val(BTnode* pt, std::ostream& os) const{
	os<<pt->value<<' ';
}

#endif
```

위 코드의 ```inline BTnode<valType>::BTnode(const valType& val) : value(val)``` 부분에서 value를 val로 이니셜라이저로 초기화 하는 코드가 있다.

:point_right: 생성자의 정의 내에서는 각 타입 멤버변수를 멤버 초기화 목록(initializer list)에서 초기화하는 것이 좋다.

만약 멤버 초기화 목록을 사용하여 초기화하지 않았으며 템플릿 인자인 ```valType```이 클래스 타입이라면 

> ex) ```BTnode(){ value = val }```

1. ```val```의 기본 생성자가  적용되고 
2. ```value```의 복사 대입 연산자를 적용한다. 

하지만 초기화 목록을 사용한다면 ```BTnode() : value(val){ }```

1. ```value```의 복사 생성자를 호출하는 단계만을 거친다.



위 코드의 ```void BTnode<valType>::preorder(BTnode* pt, std::ostream& os) const``` 부분에서 const 함수로 선언한 이유는 내부적으로 mutable로 선언된 멤버 이외에는 값을 바꾸지 않는다는 것을 선언한 것이다.

<br>

아래 코드는 ```binary_tree.h``` 헤더의 선언이다.

```c++
#ifndef binary_tree_h
#define binary_tree_h

#include "BTnode.h"

template <typename Type>
class BinaryTree{
public:
	// 생성자, 복사 생성자
	BinaryTree();
	BinaryTree(const BinaryTree&);
	~BinaryTree();
	BinaryTree& operator=(const BinaryTree&); // 대입 연산자
	
	// 기본 연산
	bool empty(){ return root==0; }
	void insert(const Type&);
	void remove(const Type&);
	void remove_root();
	void clear(){ if(root){ clear(root); root=0; } }
	friend std::ostream& operator<<(std::ostream&, const BinaryTree<Type>&); // ostream에서 BinaryTree 객체에 접근할 수 있도록 friend 선언
	
	// 탐색 연산
	void preorder() const;
	void inorder() const;
	void postorder() const;
	
private:
	BTnode<Type> *root;
	void copy(BTnode<Type> *tar, BTnode<Type> *src);
	void clear(BTnode<Type> *pt);
	void print(std::ostream&);
};
```

<br>

아래 코드는 ```binary_tree.h``` 헤더의 정의이다.

```c++
template <typename Type>
void BinaryTree<Type>::print(std::ostream& os){ // 아직 구현 진행x
	os<<"print impl..! \n";
}

template <typename Type>
void BinaryTree<Type>::clear(BTnode<Type> *pt){ // pt가 가리키는 모든 노드를 제거
  // 재귀적 제거
  if(pt){
	clear(pt->left_child);
	clear(pt->right_child);
  }
}

template <typename Type>
inline BinaryTree<Type>::BinaryTree() : root(0){ }

template <typename Type>
inline BinaryTree<Type>::~BinaryTree(){ clear(); } // BinaryTree의 public 멤버에 clear() 

template <typename Type>
inline BinaryTree<Type>::BinaryTree(const BinaryTree& rhs){ // 복사 생성자
	copy(root, rhs.root); // private 멤버에 copy()
}

template <typename Type>
inline BinaryTree<Type>& BinaryTree<Type>::operator=(const BinaryTree& rhs){
  if(this != &rhs){
      clear();
      copy(root, rhs.root);
  }
  return *this;
}

template <typename Type>
inline void BinaryTree<Type>::insert(const Type& elem){
	if(!root) root = new BTnode<Type>(elem);
	else root->insert_value(elem);
}

template <typename Type>
inline void BinaryTree<Type>::remove(const Type& elem){
  if(root){
      if(root->value == elem) remove_root(); // 삭제할 원소가 root일 떄
      else root->remove_value(elem, root);
  }
}

template <typename Type>
void BinaryTree<Type>::remove_root(){
	if(!root) return;
	
	BTnode<Type> *temp = root; // 루트를 가리키고 있을 임시 포인터 temp
	
    if(root->right_child){
    	root = root->right_child;
    	
        if(temp->left_child){
        	BTnode<Type> *lc = temp->left_child;
        	BTnode<Type> *newlc = root->left_child;
        	
        	if(!newlc) root->left_child = lc; // 루트에서 오른쪽 서브트리에 왼쪽 서브트리가 없다면
        	else BTnode<Type>::left_child_leaf(lc, newlc);
        }
    }
    else root = root->left_child;
    
    delete temp;
}

template <typename Type>
inline std::ostream& operator<<(std::ostream& os, const BinaryTree<Type>& bt){
	os<<"Tree: \n";
	bt.print(os); // print() 현재 구현 안됨, 전 노드 출력
	return os;
}

template <typename Type>
void BinaryTree<Type>::preorder() const{
	root->preorder(root, std::cout); 
}

template <typename Type>
void BinaryTree<Type>::inorder() const{
	root->inorder(root, std::cout); 
}

void BinaryTree<Type>::postorder() const{
	root->postorder(root, std::cout); 
}

#endif
```

위 코드에서 ```root->preorder(root, std::cout); ``` 이 부분

```ostream& os```를 인자로 받는 부분에 ```cout```을 전달한 것이다.

<br>

아래 코드는 ```main.cpp```이다.

```c++
#include <iostream>
#include "binary_tree.h"
#include <string>

using namespace std;

int main(){
  BinaryTree<string> bt;
  bt.insert("Piglet");
  bt.insert("Eeyore");
  bt.insert("Roo");
  bt.insert("Tigger");
  bt.insert("Chris");
  bt.insert("Pooh");
  bt.insert("Kanga");
  
  cout<<"insert complete\n";
  cout<<"\n ---------- binary tree preorder ------------\n";
  bt.preorder();
  bt.remove("Piglet");
  
  cout<<"\n ---------- binary tree preorder ------------\n";
  bt.preorder();
  bt.remove("Eeyore");
  
  cout<<"\n ---------- binary tree preorder ------------\n";
  bt.preorder();
	
  return 0;
}
```

<br>

아래 스크립트는 ```Makefile``` 스크립트이다.

```bash
CC=clang++
CFLAGS=-m64 -Wall -std=c++17 -stdlib=libstdc++
TARGET=main # 실행 파일(최종 프로그램)
OBJS=main.o # 실행 파일을 만들기 위한 목적 파일

$(TARGET):$(OBJS)
	$(CC) -o $@ $(OBJS)

main.o: BTnode.h binary_tree.h main.cpp

clean:
	rm -rf *.o

```