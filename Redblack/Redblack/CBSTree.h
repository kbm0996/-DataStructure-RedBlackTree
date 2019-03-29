#ifndef __CBSTREE_H__
#define __CBSTREE_H__

namespace mylib
{
	class CBinarySearchTree : public CTree
	{
	public:
		CBinarySearchTree();
		~CBinarySearchTree() {}
		bool InsertNode(int iKey);
		bool DeleteNode(int iKey);
		void DrawNode(HDC hdc, POINT ptRoot, int iDepth, stNODE* stpCurNode, int iNodeCnt, POINT ptParent = { 712,80 });
	};
}

#endif // !__CBSTREE_H__
