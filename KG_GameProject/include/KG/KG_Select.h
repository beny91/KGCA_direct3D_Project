#pragma once
#include "KG_Std.h"

class KG_Select
{
public:
	KGCA37_Ray m_Ray;
	D3DXMATRIX m_World;
	D3DXMATRIX m_View;
	D3DXMATRIX m_Proj;

public:
	bool PickCheck(float* pft, D3DXVECTOR3 v0, D3DXVECTOR3 v1, D3DXVECTOR3 v2);
	bool ChkOBBToRay(KG_Box* pbox);
	void SetMarix(D3DXMATRIX* pWorld, D3DXMATRIX* pView, D3DXMATRIX* pProj);
	void Update();
	bool OBBToRay(KG_Box* pBox);
	D3DXVECTOR3 GetIntersection(float t);

public:
	KG_Select();
	virtual ~KG_Select();
};
