#ifndef __CRBTREE_H__
#define __CRBTREE_H__

namespace mylib
{
	class CRedBlackTree : public CTree
	{
	public:
		CRedBlackTree();
		~CRedBlackTree() {}
		bool InsertNode(int Key);
		bool DeleteNode(int Key);
		void DrawNode(HDC hdc, POINT ptRoot, int iDepth, stNODE* stpCurNode, int iNodeCnt, POINT ptParent = { 712,80 });

	protected:
		void turnleft(stNODE* pNode);
		void turnright(stNODE* pNode);

	};
}
#endif // !__CRBTREE_H__
