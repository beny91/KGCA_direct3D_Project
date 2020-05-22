#pragma once
#include"JH_Map.h"
#include"KG_Camera.h"
#include"KG_Select.h"
#include"KG_ShapeLine.h"
#include"KG_Node.h"



class HQuadTree
{
public:
	float										m_fTimer;
	KG_Node*									m_pRootNode;
	JH_Map*										m_pMap;
	KG_Camera*									m_pCamera;
	vector<KG_Node*>							m_SelectNodeList;
	KG_Node*									m_pNearPointNode;
	float										m_fdistance;
	KG_Select*									m_pSelect;
	int											m_iQuadTreeIndex;
	vector<KG_Node*>							m_ContainObjNode;

	vector<KG_Node*>							m_DrawNodeList;
	vector<KG_Node*>							m_DrawObjNodeList;

	shared_ptr<KG_ShapeLine>	m_BoxLine;
public:
	BOOL Build(JH_Map* pMap, KG_Camera* pCamera);
	BOOL BuildTree(KG_Node* pNode);
	void FindDrawNode(KG_Node* pNode);
	void VisibleNode(KG_Node* pNode);
	BOOL DivideNode(KG_Node*pNode);
	void DrawNodeLine(KG_Node* pNode);
	void DrawLine(KG_Node* pNode);
	KG_Node* CreateNode(KG_Node* pParent, DWORD dwTL, DWORD dwTR, DWORD dwBL, DWORD dwBR);
	void GetSelectNode(KG_Node* pNode);
	bool GetObjectAddNode(JH_MapObj& Obj);
	KG_Node* FindNode(KG_Node* pNode, JH_MapObj& Obj);
	bool CheckRect(KG_Node* pNode, JH_MapObj& Obj);
	void CreateIndexList(KG_Node* pNode);
	void CreateBB(KG_Node* pNode);
	void CreateObjBB();
	void DirectSelect(KG_Node* pNode);
	void Set();
	bool Frame();
	bool Render();
	bool Release();
	bool Draw(KG_Node* pNode, ID3D11DeviceContext* pContext);
public:
	bool FindInterSection();
	void FindNearInterSectionNode(KG_Node* pNode, D3DXVECTOR3 vInterSection);
public:
	HQuadTree();
	virtual ~HQuadTree();
};

