#pragma once
#include"KG_Std.h"
#include"JH_MapObj.h"

class KG_Node
{
public:
	KG_Box m_Box;
	
	std::vector<int> m_ObjListIndexList;

	std::map<int,JH_MapObj>			m_ObjList;
	BOOL	m_isLeaf;
	DWORD	m_dwDepth;
	DWORD	m_dwCorner[4];// 꼭지점 네점
	KG_Node*	m_pChild[4];
	std::vector<DWORD> m_IndexList;
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_pIndexBuffer;
	int		m_iQuadTreeIndex;
public:
	KG_Node();
	virtual ~KG_Node();
	

};