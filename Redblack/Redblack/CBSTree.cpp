#include "stdafx.h"

mylib::CBinarySearchTree::CBinarySearchTree()
{
	_iNodeCnt = 0;
	_stNil.Color = BLACK;
	_stNil.pParent = &_stNil;
	_stNil.pChild_left = &_stNil;
	_stNil.pChild_Right = &_stNil;
	_pRoot = &_stNil;
}

bool mylib::CBinarySearchTree::InsertNode(int Key)
{
	stNODE* pNode = new stNODE;
	pNode->Key = Key;
	pNode->pParent = &_stNil;
	pNode->pChild_left = &_stNil;
	pNode->pChild_Right = &_stNil;
	if (_pRoot == &_stNil || _pRoot == nullptr)
	{
		_pRoot = pNode;
		++_iNodeCnt;
		return true;
	}
	if (insertnode(_pRoot, pNode))
	{
		++_iNodeCnt;
		return true;
	}
	else
		return false;
}

bool mylib::CBinarySearchTree::DeleteNode(int Key)
{
	stNODE* pDeleteNode = deletenode(_pRoot, Key);
	if (pDeleteNode != nullptr)
	{
		delete pDeleteNode;

		--_iNodeCnt;
		return true;
	}

	return false;
}

void mylib::CBinarySearchTree::DrawNode(HDC hdc, POINT ptRoot, int iDepth, stNODE * stpCurNode, int iNodeCnt, POINT ptParent)
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

	SetDCBrushColor(hdc, RGB(0, 0, 0));
	SelectObject(hdc, GetStockObject(DC_BRUSH));
	Ellipse(hdc, rectTempNode.left, rectTempNode.top, rectTempNode.right, rectTempNode.bottom);

	wsprintf(chKey, L"%d", pNode->Key);
	DrawText(hdc, chKey, -1, &rectTempNode, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	if (pNode->pParent != &_stNil)
	{
		prevPos = ptParent;
		rectTempNode = { rectNode.left + prevPos.x, rectNode.top + prevPos.y, rectNode.right + prevPos.x, rectNode.bottom + prevPos.y };


		SetDCBrushColor(hdc, RGB(0, 0, 0));
		SelectObject(hdc, GetStockObject(DC_BRUSH));
		Ellipse(hdc, rectTempNode.left, rectTempNode.top, rectTempNode.right, rectTempNode.bottom);

		wsprintf(chKey, L"%d", pNode->pParent->Key);
		DrawText(hdc, chKey, -1, &rectTempNode, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}

	if (pNode->pChild_left != &_stNil)	
		DrawNode(hdc, ptRoot, iDepth + 1, pNode->pChild_left, iNodeCnt, curPos);
	if (pNode->pChild_Right != &_stNil)	
		DrawNode(hdc, ptRoot, iDepth + 1, pNode->pChild_Right, iNodeCnt, curPos);
}
