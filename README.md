# 레드-블랙 트리
## 📢 개요

 `레드-블랙 트리(RB Tree; Red-Black Tree)`는 각각의 노드가 **레드**나 **블랙**인 색상을 가지고 있는 이진 탐색 트리다. 삽입, 삭제, 검색에서 어떠한 경우에도 일정한 시간을 보장한다는 것이 특징이다. 때문에 실시간 처리 등 실행 시간이 중요한 경우에 주로 쓰인다. 실제로 STL의 내부 구현에 레드-블랙 트리가 사용되었다고 알려져 있다.
 
## 💻 트리 GDI
 BS 트리와 RB 트리의 노드 추가, 제거 과정을 볼 수 있는 시뮬레이션 프로그램. 마우스로 화면을 드래그하여 화면 바깥으로 나간 부분을 볼 수도 있다.
 
 ![BSTree](https://github.com/kbm0996/WinAPI-Tree_Structure/blob/master/figure/bstree.png)
 
 **figure 1. BSTree*

 
 ![BSTree](https://github.com/kbm0996/WinAPI-Tree_Structure/blob/master/figure/rbtree.png)
 
 **figure 2. RBTree*
 
## 🅿 원리
>### ● 레드-블랙 트리의 특성
>>1. 노드는 레드 혹은 블랙 중의 하나이다.
>>2. 루트 노드는 블랙이다.
>>3. 모든 널 포인터(Nil)는 블랙이다.
>>4. 레드 노드의 자식노드 양쪽은 언제나 모두 블랙이다. (즉, 레드 노드는 연달아 나타날 수 없으며, 블랙 노드만이 레드 노드의 부모 노드가 될 수 있다)
>>5. 어떤 노드로부터 시작되어 리프 노드에 도달하는 모든 경로에는 리프 노드를 제외하면 모두 같은 개수의 블랙 노드가 있다.
>
> 위 조건들을 만족하게 되면, 레드-블랙 트리는 가장 중요한 특성을 나타내게 된다: 루트 노드부터 가장 먼 경로까지의 거리가, 가장 가까운 경로까지의 거리의 두 배 보다 항상 작다. 다시 말해서 레드-블랙 트리는 개략적(roughly)으로 균형이 잡혀 있다(balanced). 따라서, 삽입, 삭제, 검색시 최악의 경우(worst-case)에서의 시간복잡도가 트리의 높이(또는 깊이)에 따라 결정되기 때문에 보통의 이진 탐색 트리에 비해 효율적이라고 할 수 있다.

 ### 1. 노드 추가
   단순 연결 리스트와 거의 비슷합니다. 중요한 차이점은 양방향으로 연결을 해야 한다는 점입니다. 새로운 노드(25)를 기존의 노드(20, 30)와 연결하는 방법만 살펴보겠습니다.

  ![](https://s3.ap-northeast-2.amazonaws.com/opentutorials-user-file/module/1335/2958.png)

 **figure 2. Phase 1*

  25의 다음 노드로 30을 연결합니다.

  ![](https://s3.ap-northeast-2.amazonaws.com/opentutorials-user-file/module/1335/2959.png)

 **figure 3. Phase 2*

  30의 이전 노드로 25를 연결합니다.

  ![](https://s3.ap-northeast-2.amazonaws.com/opentutorials-user-file/module/1335/2960.png)

 **figure 4. Phase 3*

  20의 다음 노드로 25를 지정합니다. 

  ![](https://s3.ap-northeast-2.amazonaws.com/opentutorials-user-file/module/1335/2961.png)

 **figure 5. Phase 4*

  25의 이전 노드로 20을 지정합니다.

  ![](https://s3.ap-northeast-2.amazonaws.com/opentutorials-user-file/module/1335/2962.png)

 **figure 6. Phase 5*

  노드의 추가가 끝났습니다.

  ![](https://s3.ap-northeast-2.amazonaws.com/opentutorials-user-file/module/1335/2963.png)

 **figure 7. Phase 6*
 
 ### 2. 노드 제거
 
  ![](https://s3.ap-northeast-2.amazonaws.com/opentutorials-user-file/module/1335/2969.png)

 **figure 8. Phase 1*

  삭제하려는 노드의 이전 노드(20)을 찾습니다.
  
  ![](https://s3.ap-northeast-2.amazonaws.com/opentutorials-user-file/module/1335/2970.png)

 **figure 9. Phase 2*
  
  삭제하려는 노드(30)도 찾습니다.

  ![](https://s3.ap-northeast-2.amazonaws.com/opentutorials-user-file/module/1335/2971.png)

 **figure 10. Phase 3*

  삭제하려는 노드의 다음 노드(40)도 찾습니다.

  ![](https://s3.ap-northeast-2.amazonaws.com/opentutorials-user-file/module/1335/2972.png)

 **figure 11. Phase 4*

  30을 삭제합니다.

  ![](https://s3.ap-northeast-2.amazonaws.com/opentutorials-user-file/module/1335/2973.png)

 **figure 12. Phase 5*

  20의 다음 노드로 40을 지정합니다.

  ![](https://s3.ap-northeast-2.amazonaws.com/opentutorials-user-file/module/1335/2974.png)

 **figure 13. Phase 6*

  40의 이전 노드로 20을 지정합니다.

  ![](https://s3.ap-northeast-2.amazonaws.com/opentutorials-user-file/module/1335/2975.png)

 **figure 14. Phase 7*

  삭제가 완료 되었습니다.
 
 
 ## 📌 이미지 및 설명 출처 
 
 레드-블랙트리의 특성 - https://ko.wikipedia.org/wiki/레드-블랙_트리
 원리 파트 - https://opentutorials.org/module/1335/8940
 



