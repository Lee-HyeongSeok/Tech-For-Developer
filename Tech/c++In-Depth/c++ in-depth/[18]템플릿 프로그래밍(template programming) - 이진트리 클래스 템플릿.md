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

### :pushpin: 이진 트리(binary tree)

- 트리(Tree)
  - 노드(node)와 노드들을 연결하는 링크(link, vertex라고도 함)로 이루어진다.
- 이진 트리(Binary Tree)
  - 노드가 두 개의 링크를 갖는 형태
  - 두 링크는 왼쪽 자식(left child), 오른쪽 자식(right child)으로 부른다.
  - 트리는 루트(root)라고 부르는 최초의 노드를 가진다.
  - 왼쪽 자식과 오른쪽 자식은 각각 자신들의 서브트리(subtree)에 대해서 루트로 기능할 수 있다.
  - 자식을 갖지 않는 노드는 리프 노드(leaf node)라고 부른다.

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

> 다음은 BTnode에 대한 비-템플릿 선언이다
>
> :point_right: BTnode : 실제 값과 왼쪽 자식, 오른쪽 자식에 대한 링크를 갖는 클래스
>
> - 노드에 저장되는 값 : string class의 객체
>
> ```c++
> class string_BTnode{
> public:
>     // ...
> private:
>     string _val;
>     int _cnt;
>     string_BTnode *_lchild; // 왼쪽 자식
>     string_BTnode *_rchild; // 오른쪽 자식
> }
> ```
>
> - 템플릿 메커니즘은 타입에 의존적인 부분과 클래스 정의에서 변하지 않는 부분을 분리시켜 준다.
> - 트리 탐색, 노드 삽입 및 삭제, 개수 저장 등의 코드는 값의 타입에 관계없이 모두 동일하다.
>   - 이 코드들은 클래스 템플릿의 모든 인스턴스가 재사용 가능(한 번의 함수 정의, 여러 타입의 접근 가능)
> - 각각의 노드에 저장된 값의 타입은 클래스 템플릿의 각 인스턴스에서 바뀌게 된다.
>   - 어떤 경우는 string, 또 다른 경우는 double, int 등

<br>

> BTnode 클래스의 매개변수화
>
> ```c++
> // BTnode 클래스 템플릿의 전방 선언(forward declaration)
> template <typename valType>
> class BTnode;
> ```
>
> 