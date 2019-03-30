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
 
 #### ● 소스 코드
      void DoublyLinkedlist::push_front(char* szData)
      {
        stNODE *pNode = (stNODE*)malloc(sizeof(stNODE));

        memcpy(pNode->szData, szData, sizeof(pNode->szData));

        pNode->pPrev = &_Head;
        pNode->pNext = _Head.pNext;
        pNode->pPrev->pNext = pNode;
        pNode->pNext->pPrev = pNode;
      }

      void DoublyLinkedlist::push_back(char* szData)
      {
        stNODE *pNode = (stNODE*)malloc(sizeof(stNODE));

        memcpy(pNode->szData, szData, sizeof(pNode->szData));

        pNode->pPrev = _Tail.pPrev;
        pNode->pNext = &_Tail;
        pNode->pPrev->pNext = pNode;
        pNode->pNext->pPrev = pNode;
      }
 
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
 
 
  #### ● 소스 코드
      bool DoublyLinkedlist::Delete(char* szData)
      {
        stNODE *pNode = _Head.pNext;

        while (pNode->pNext != NULL)
        {
          if (strcmp(pNode->szData, szData) == 0)
          {
            pNode->pPrev->pNext = pNode->pNext;
            pNode->pNext->pPrev = pNode->pPrev;
            free(pNode);
            return true;
          }
          pNode = pNode->pNext;
        }
        return false;
      }
 
 
 ## 📌 이미지 및 설명 출처 
 
 원리 파트 - https://opentutorials.org/module/1335/8940



