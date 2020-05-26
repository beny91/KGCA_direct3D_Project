#pragma once
#include"JH_BaseObj.h"
class JH_MapObj:public JH_BaseObj
{
	const TCHAR*	m_FileName;
	int				m_ID;
	//int				m_iObjIndex;
	int				m_iQuadIndex;
public:
	//int					GetObjIndex() { return m_iObjIndex; };
	//void				SetObjIndex(int Index) { m_iObjIndex = Index; };
	int					GetID() { return m_ID; };
	void				SetID(int Index) { m_ID = Index; };
	const TCHAR*		GetName() { return m_FileName; };
	void				SetName(const TCHAR* FileName) { m_FileName = FileName; };

	int					GetQuadIndex() { return m_iQuadIndex; };
	void				SetQuadIndex(int Index) { m_iQuadIndex = Index; };
	JH_MapObj();
	virtual ~JH_MapObj();
};

