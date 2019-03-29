#include "stdafx.h"

mylib::CRedBlackTree::CRedBlackTree()
{
	_iNodeCnt = 0;
	_stNil.Color = BLACK;
	_stNil.pParent = &_stNil;
	_stNil.pChild_left = &_stNil;
	_stNil.pChild_Right = &_stNil;
	_pRoot = &_stNil;
}

bool mylib::CRedBlackTree::InsertNode(int iKey)
{
	stNODE* pNode = new stNODE;
	stNODE* pUncle;
	pNode->Key = iKey;
	pNode->pParent = &_stNil;
	pNode->pChild_left = &_stNil;
	pNode->pChild_Right = &_stNil;
	if (_pRoot == &_stNil)
	{
		pNode->Color = BLACK;
		_pRoot = pNode;
		++_iNodeCnt;
		return true;
	}
	if (insertnode(_pRoot, pNode))
	{
		pNode->Color = RED;
		////////////////////////////////////////////////////////////
		//  Loop End Requirements
		// 
		////////////////////////////////////////////////////////////
		// If the parent node of new node is `BLACK`
		while (pNode->pParent->Color == RED)
		{
			// If the parent node is a LEFT child of other node 
			if (pNode->pParent == pNode->pParent->pParent->pChild_left)
			{
				pUncle = pNode->pParent->pParent->pChild_Right;
				// If the parent is `RED`, the parent's sibling is `RED`
				if (pUncle->Color == RED)
				{
					pNode->pParent->Color = BLACK;
					pUncle->Color = BLACK;
					pNode->pParent->pParent->Color = RED;
					pNode = pNode->pParent->pParent;
				}
				// If the parent is `RED`, the parent's sibling is `BLACK`
				else
				{
					//  When you make a right turn, the left child goes to the left side of the tree.
					// -> the BLACK count balance is broken.
					// * Solution : Make a left turn to bring the nodes together in one direction.
					if (pNode == pNode->pParent->pChild_Right) 
					{
						pNode = pNode->pParent;
						turnleft(pNode);
					}
					pNode->pParent->Color = BLACK;
					pNode->pParent->pParent->Color = RED;
					turnright(pNode->pParent->pParent);
				}
			}
			// If the parent node is a RIGHT child of other node 
			else
			{
				pUncle = pNode->pParent->pParent->pChild_left;
				// If the parent is `RED`, the parent's sibling is `RED`
				if (pUncle->Color == RED)
				{
					pNode->pParent->Color = BLACK;
					pUncle->Color = BLACK;
					pNode->pParent->pParent->Color = RED;
					pNode = pNode->pParent->pParent;
				}
				// If the parent is `RED`, the parent's sibling is `BLACK`
				else
				{
					if (pNode == pNode->pParent->pChild_left)
					{
						pNode = pNode->pParent;
						turnright(pNode);
					}
					pNode->pParent->Color = BLACK;
					pNode->pParent->pParent->Color = RED;
					turnleft(pNode->pParent->pParent);
				}
			}
		}
		_pRoot->Color = BLACK;
		_stNil.Color = BLACK;
		_stNil.pChild_left = &_stNil;
		_stNil.pParent = &_stNil;
		_stNil.pChild_Right = &_stNil;
		++_iNodeCnt;
		return true;
	}
	return false;
}

bool mylib::CRedBlackTree::DeleteNode(int iKey)
{
	stNODE* pDeleteNode = deletenode(_pRoot, iKey);
	if (pDeleteNode == NULL)
		return false;

	if (pDeleteNode == _pRoot)
	{
		delete pDeleteNode;
		_pRoot = &_stNil;
		--_iNodeCnt;
		return true;
	}

	if (pDeleteNode->Color == RED)
	{
		delete pDeleteNode;
		--_iNodeCnt;
		return true;
	}
	else
	{
		stNODE* pRepNode;
		// Except when there are all LEFT and RIGHT children in the process of actually finding the node to be erased
		// If it is a LEFT child
		if (pDeleteNode->pChild_left != &_stNil)
			pRepNode = pDeleteNode->pChild_left;
		// If it is a RIGHT child
		else if (pDeleteNode->pChild_Right != &_stNil)	
			pRepNode = pDeleteNode->pChild_Right;
		// If there is no child
		else
		{
			pRepNode = &_stNil;
			pRepNode->pParent = pDeleteNode->pParent;
		}
		delete pDeleteNode;
		--_iNodeCnt;

		// Balance
		// Check in which direction the replacement node is from the parent node. 
		// Assuming that BLACK in the direction is -1
		while (pRepNode->Color != RED && pRepNode != _pRoot)
		{
			// me == `BLACK`
			stNODE* pSibling;

			// me == parent's LEFT child
			if (pRepNode == pRepNode->pParent->pChild_left)
			{
				pSibling = pRepNode->pParent->pChild_Right;
				// sibling == `RED`
				if (pSibling->Color == RED)
				{
					pSibling->Color = BLACK;
					pRepNode->pParent->Color = RED;
					//  On rotation, parent's parent(will becoming sibling) becomes `BLACK`
					// and parent(will becoming me) becomes `BLACK`, so parent is set to `RED`
					turnleft(pRepNode->pParent);
					
					// The sibling's left child(`BLACK`) has crossed over to the pRepNode's sibling
					// The pRepNode goes down one step.
					pSibling = pRepNode->pParent->pChild_Right;
				}
				// sibling == `BLACK`
				else
				{
					// If Sibling's both children are `BLACK`
					if (pSibling->pChild_left->Color == BLACK && pSibling->pChild_Right->Color == BLACK)
					{
						pSibling->Color = RED;
						pRepNode = pRepNode->pParent;
						// Situation of `BLACK` -1 under parent
					}
					// If Sibling's left Child is `RED`, right child is `BLACK`
					else if (pSibling->pChild_left->Color == RED && pSibling->pChild_Right->Color == BLACK)
					{
						pSibling->Color = RED;
						pSibling->pChild_left->Color = BLACK;
						turnright(pSibling);
						// As a result, pRepNode - based sibling is become `BLACK`, right child is become `RED`

						pSibling = pRepNode->pParent->pChild_Right;
					}
					// If Sibling's right child is `RED`
					if (pSibling->pChild_Right->Color == RED)
					{
						pSibling->Color = pRepNode->pParent->Color;
						pSibling->pChild_Right->Color = BLACK;
						pRepNode->pParent->Color = BLACK;
						turnleft(pSibling->pParent);
						// As a result, move the right side `BLACK` to the left to balance
						break;
					}
				}
			}
			else
			{
				pSibling = pRepNode->pParent->pChild_left;
				// Sibling == RED
				if (pSibling->Color == RED)
				{
					pSibling->Color = BLACK;
					pRepNode->pParent->Color = RED;
					turnright(pRepNode->pParent);

					pSibling = pRepNode->pParent->pChild_left;
				}
				else
				{
					if (pSibling->pChild_left->Color == BLACK && pSibling->pChild_Right->Color == BLACK)
					{
						pSibling->Color = RED;
						pRepNode = pRepNode->pParent;
					}
					else if (pSibling->pChild_Right->Color == RED && pSibling->pChild_left->Color == BLACK)
					{
						pSibling->Color = RED;
						pSibling->pChild_Right->Color = BLACK;
						turnleft(pSibling);

						pSibling = pRepNode->pParent->pChild_left;
					}

					if (pSibling->pChild_left->Color == RED)
					{
						pSibling->Color = pRepNode->pParent->Color;
						pSibling->pChild_left->Color = BLACK;
						pRepNode->pParent->Color = BLACK;
						turnright(pSibling->pParent);
						break;
					}
				}
			}
			pRepNode->Color = BLACK;
		}
		_stNil.Color = BLACK;
		_stNil.pChild_left = &_stNil;
		_stNil.pParent = &_stNil;
		_stNil.pChild_Right = &_stNil;
		_pRoot->Color = BLACK;
	}

	return true;
}

void mylib::CRedBlackTree::DrawNode(HDC hdc, POINT ptRoot, int iDepth, stNODE * stpCurNode, int iNodeCnt, POINT ptParent)
{
	TCHAR	chKey[20];
	POINT	prevPos, curPos;
	RECT	rectNode = { -20, -20, 20, 20 };
	RECT	rectTempNode;
	int		iLineLength = 30 * iNodeCnt / 2;
	stNODE* pNode = stpCurNode;

	if (pNode == nullptr)
		pNode = _pRoot;

	if (pNode->pParent != &_stNil)
	{
		prevPos = ptParent;
		MoveToEx(hdc, prevPos.x, prevPos.y, nullptr);
	}

	int iInterval = 1;
	int itempDepth = iDepth + 1;
	while (itempDepth > 1)
	{
		iInterval *= 2;
		--itempDepth;
	}

	// height length 50
	if (pNode->pParent == &_stNil)
		prevPos = { ptRoot.x, ptRoot.y + 50 * iDepth }; 
	// left child pos
	else if (pNode->pParent->Key > pNode->Key) 
		prevPos = { ptParent.x - iLineLength / iInterval, ptRoot.y + 50 * iDepth };
	// right child pos
	else	
		prevPos = { ptParent.x + iLineLength / iInterval, ptRoot.y + 50 * iDepth };

	curPos = prevPos;
	rectTempNode = { rectNode.left + prevPos.x, rectNode.top + prevPos.y, rectNode.right + prevPos.x, rectNode.bottom + prevPos.y };

	// Line Color : BLACK_PEN
	SelectObject(hdc, GetStockObject(BLACK_PEN));
	if (pNode->pParent != &_stNil)
		LineTo(hdc, prevPos.x, prevPos.y);

	// Shape Border Color : NULL_PEN(Transparency)
	SelectObject(hdc, GetStockObject(NULL_PEN));
	if (pNode->Color == BLACK)
	{
		SetDCBrushColor(hdc, RGB(0, 0, 0));
		SelectObject(hdc, GetStockObject(DC_BRUSH));
		Ellipse(hdc, rectTempNode.left, rectTempNode.top, rectTempNode.right, rectTempNode.bottom);
	}
	else
	{
		SetDCBrushColor(hdc, RGB(255, 0, 0));
		SelectObject(hdc, GetStockObject(DC_BRUSH));
		Ellipse(hdc, rectTempNode.left, rectTempNode.top, rectTempNode.right, rectTempNode.bottom);
	}
	wsprintf(chKey, L"%d", pNode->Key);
	DrawText(hdc, chKey, -1, &rectTempNode, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	if (pNode->pParent != &_stNil)
	{
		prevPos = ptParent;
		rectTempNode = { rectNode.left + prevPos.x, rectNode.top + prevPos.y, rectNode.right + prevPos.x, rectNode.bottom + prevPos.y };

		if (pNode->pParent->Color == BLACK)
		{
			SetDCBrushColor(hdc, RGB(0, 0, 0));
			SelectObject(hdc, GetStockObject(DC_BRUSH));
			Ellipse(hdc, rectTempNode.left, rectTempNode.top, rectTempNode.right, rectTempNode.bottom);
		}
		else
		{
			SetDCBrushColor(hdc, RGB(255, 0, 0));
			SelectObject(hdc, GetStockObject(DC_BRUSH));
			Ellipse(hdc, rectTempNode.left, rectTempNode.top, rectTempNode.right, rectTempNode.bottom);
		}
		wsprintf(chKey, L"%d", pNode->pParent->Key);
		DrawText(hdc, chKey, -1, &rectTempNode, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}

	if (pNode->pChild_left != &_stNil)	
		DrawNode(hdc, ptRoot, iDepth + 1, pNode->pChild_left, iNodeCnt, curPos);
	if (pNode->pChild_Right != &_stNil)	
		DrawNode(hdc, ptRoot, iDepth + 1, pNode->pChild_Right, iNodeCnt, curPos);
}


void mylib::CRedBlackTree::turnleft(stNODE * pNode)
{
	stNODE * pRightChild = pNode->pChild_Right;
	pNode->pChild_Right = pRightChild->pChild_left;

	if (pRightChild->pChild_left != &_stNil)
		pRightChild->pChild_left->pParent = pNode;

	pRightChild->pParent = pNode->pParent;

	if (pNode == pNode->pParent->pChild_left)
		pNode->pParent->pChild_left = pRightChild;
	else
		pNode->pParent->pChild_Right = pRightChild;

	pRightChild->pChild_left = pNode;
	pNode->pParent = pRightChild;

	if (pRightChild->pParent == &_stNil)
		_pRoot = pRightChild;
	_pRoot->Color = BLACK;
}

void mylib::CRedBlackTree::turnright(stNODE * pNode)
{
	stNODE * pLeftChild = pNode->pChild_left;
	pNode->pChild_left = pLeftChild->pChild_Right;

	if (pLeftChild->pChild_Right != &_stNil)
		pLeftChild->pChild_Right->pParent = pNode;

	pLeftChild->pParent = pNode->pParent;

	if (pNode == pNode->pParent->pChild_left)
		pNode->pParent->pChild_left = pLeftChild;
	else
		pNode->pParent->pChild_Right = pLeftChild;

	pLeftChild->pChild_Right = pNode;
	pNode->pParent = pLeftChild;

	if (pLeftChild->pParent == &_stNil)
		_pRoot = pLeftChild;
	_pRoot->Color = BLACK;
}