#pragma once
#include"JH_BaseObj.h"
class JH_MapObj:public JH_BaseObj
{
	int m_iObjIndex;
	int m_iQuadIndex;
public:
	int		GetObjIndex() { return m_iObjIndex; };
	void	SetObjIndex(int Index) { m_iObjIndex = Index; };

	int		GetQuadIndex() { return m_iQuadIndex; };
	void	SetQuadIndex(int Index) { m_iQuadIndex = Index; };
	JH_MapObj();
	virtual ~JH_MapObj();
};

