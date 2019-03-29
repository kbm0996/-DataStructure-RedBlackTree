#include "stdafx.h"
#include "CTree.h"

bool mylib::CTree::SearchNode(int Key)
{
	if (_pRoot == &_stNil)
		return false;

	if (searchnode(_pRoot, Key) != NULL)
		return true;
	return false;
}

void mylib::CTree::PreOrder()
{
	wprintf(L"PreOrder :	");
	preorder(_pRoot);
	wprintf(L"\n");
}

void mylib::CTree::InOrder()
{
	wprintf(L"InOrder :	");
	inorder(_pRoot);
	wprintf(L"\n");
}

void mylib::CTree::PostOrder()
{
	wprintf(L"PostOrder :	");
	postorder(_pRoot);
	wprintf(L"\n");
}

int mylib::CTree::GetNodeCount()
{
	return _iNodeCnt;
}

bool mylib::CTree::insertnode(stNODE * pCurrent, stNODE * pInsert)
{
	if (pCurrent == &_stNil)	
		return false;

	if (pCurrent->Key == pInsert->Key) 
		return false;

	if (pCurrent->Key > pInsert->Key)
	{
		if (pCurrent->pChild_left == &_stNil)
		{
			pCurrent->pChild_left = pInsert;
			pInsert->pParent = pCurrent;
			return true;
		}
		else
			return insertnode(pCurrent->pChild_left, pInsert);
	}

	if (pCurrent->Key < pInsert->Key)
	{
		if (pCurrent->pChild_Right == &_stNil)
		{
			pCurrent->pChild_Right = pInsert;
			pInsert->pParent = pCurrent;
			return true;
		}
		else
			return insertnode(pCurrent->pChild_Right, pInsert);
	}

	return false;
}

mylib::CTree::stNODE * mylib::CTree::searchnode(stNODE * pNode, int iKey)
{
	if (pNode == &_stNil)	
		return nullptr;

	if (pNode->Key == iKey)
		return pNode;

	if (pNode->Key > iKey)
	{
		if (pNode->pChild_left == &_stNil)
			return nullptr;
		else
			return searchnode(pNode->pChild_left, iKey);
	}

	if (pNode->Key < iKey)
	{
		if (pNode->pChild_Right == &_stNil)
			return nullptr;
		else
			return searchnode(pNode->pChild_Right, iKey);
	}

	return nullptr;
}

mylib::CTree::stNODE * mylib::CTree::deletenode(stNODE * pNode, int iKey)
{
	stNODE* pSourceNode;
	if (pNode == &_stNil)	
		return nullptr;

	if (pNode->Key == iKey)
	{
		// Case 1. If not have child
		if (pNode->pChild_left == &_stNil && pNode->pChild_Right == &_stNil) 
		{
			if (pNode->pParent == &_stNil)	
				_pRoot = &_stNil;
			else if (pNode->pParent->pChild_left == pNode)	
				pNode->pParent->pChild_left = &_stNil;
			else if (pNode->pParent->pChild_Right == pNode)	
				pNode->pParent->pChild_Right = &_stNil;

			return pNode;
		}
		// Case 2. If have only one child
		else if (pNode->pChild_left == &_stNil || pNode->pChild_Right == &_stNil) 
		{
			if (pNode->pChild_left != &_stNil)	
				pSourceNode = pNode->pChild_left;
			else	
				pSourceNode = pNode->pChild_Right;

			pNode->Key = pSourceNode->Key;
			pNode->pChild_left = pSourceNode->pChild_left;
			pNode->pChild_Right = pSourceNode->pChild_Right;

			if (pSourceNode->pChild_left != &_stNil)	
				pSourceNode->pChild_left->pParent = pNode;

			if (pSourceNode->pChild_Right != &_stNil)	
				pSourceNode->pChild_Right->pParent = pNode;

			return pSourceNode;
		}
		// Case 3. If have both children
		else 
		{
			pSourceNode = pNode->pChild_Right;

			while (pSourceNode->pChild_left != &_stNil)
				pSourceNode = pSourceNode->pChild_left;

			pNode->Key = pSourceNode->Key;
			pSourceNode->pChild_Right->pParent = pSourceNode->pParent;

			if (pSourceNode->pParent->pChild_left == pSourceNode)
				pSourceNode->pParent->pChild_left = pSourceNode->pChild_Right;
			else
				pSourceNode->pParent->pChild_Right = pSourceNode->pChild_Right;

			return pSourceNode;
		}
	}
	
	if (pNode->Key > iKey)
	{
		if (pNode->pChild_left == nullptr)
			return nullptr;
		else
			return deletenode(pNode->pChild_left, iKey);
	}

	if (pNode->Key < iKey)
	{
		if (pNode->pChild_Right == nullptr)
			return nullptr;
		else
			return deletenode(pNode->pChild_Right, iKey);
	}

	return nullptr;
}



void mylib::CTree::preorder(stNODE* pNode)
{
	if (pNode == &_stNil || pNode == nullptr)
		return;
	
	wprintf(L" %d", pNode->Key);
	preorder(pNode->pChild_left);
	preorder(pNode->pChild_Right);
}

void mylib::CTree::inorder(stNODE * pNode)
{
	if (pNode == &_stNil || pNode == nullptr)
		return;

	inorder(pNode->pChild_left);
	wprintf(L" %d", pNode->Key);
	inorder(pNode->pChild_Right);
}

void mylib::CTree::postorder(stNODE * pNode)
{
	if (pNode == &_stNil || pNode == nullptr)
		return;

	postorder(pNode->pChild_left);
	postorder(pNode->pChild_Right);
	wprintf(L" %d", pNode->Key);
}