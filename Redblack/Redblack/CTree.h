#ifndef __TREE_H__
#define __TREE_H__

namespace mylib
{
	class CTree
	{
	protected:
		enum enCOLOR
		{
			BLACK = 0,
			RED
		};

		struct stNODE
		{
			int Key;
			enCOLOR Color;
			stNODE* pParent;
			stNODE* pChild_left;
			stNODE* pChild_Right;
		};

	public:
		CTree() {}
		virtual ~CTree() {}

		virtual bool InsertNode(int Key) = 0;
		virtual bool DeleteNode(int Key) = 0;
		virtual void DrawNode(HDC hdc, POINT ptRoot, int iDepth, stNODE* stpCurNode, int iNodeCnt, POINT ptParent = { 712,80 }) = 0;

		bool SearchNode(int Key);
		void PreOrder();
		void InOrder();
		void PostOrder();
		int GetNodeCount();


	protected:
		bool insertnode(stNODE* pCurrent, stNODE * pInsert);
		stNODE* searchnode(stNODE* pNode, int Key);
		stNODE* deletenode(stNODE* pNode, int Key);
		void preorder(stNODE* pNode);
		void inorder(stNODE* pNode);
		void postorder(stNODE* pNode);

		stNODE* _pRoot;
		stNODE _stNil; // Virtual Leaf Node - Always 'BLACK'
		int _iNodeCnt;
	};
}

#endif
