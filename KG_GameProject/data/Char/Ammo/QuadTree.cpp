#include "QuadTree.h"
#include"KG_Input.h"
#include<queue>

bool HQuadTree::FindInterSection()
{
	D3DXVECTOR3 v0, v1, v2, vIntersection;
	m_fTimer += g_SecondTime;
	if (I_Input.KeyCheck(VK_LBUTTON))//&& m_fTimer >=0.5)
	{

		m_fTimer = 0.0f;
		GetSelectNode(m_pRootNode);

		for (int iNode = 0; iNode <
			m_SelectNodeList.size(); iNode++)
		{
			DWORD dwFace = m_SelectNodeList[iNode]->m_IndexList.size() / 3;
			for (int iFace = 0; iFace < dwFace; iFace++)
			{
				DWORD i0 = m_SelectNodeList[iNode]->m_IndexList[iFace * 3 + 0];
				DWORD i1 = m_SelectNodeList[iNode]->m_IndexList[iFace * 3 + 1];
				DWORD i2 = m_SelectNodeList[iNode]->m_IndexList[iFace * 3 + 2];
				v0 = m_pMap->m_VerTex[i0].p;
				v1 = m_pMap->m_VerTex[i1].p;
				v2 = m_pMap->m_VerTex[i2].p;

				D3DXVECTOR3 vDIR = m_pSelect->m_Ray.m_Dir;
				D3DXVECTOR3 vEnd = m_pSelect->m_Ray.m_Orig + vDIR * m_pCamera->m_fFar;

				D3DXVECTOR3 vNormal;
				D3DXVECTOR3 e0 = v1 - v0;
				D3DXVECTOR3 e1 = v2 - v0;
				D3DXVec3Cross(&vNormal, &e0, &e1);
				float t=0.0f;
			if (m_pSelect->PickCheck(&t,v0, v1, v2)); //CJH version
				{
					vIntersection = m_pSelect->GetIntersection(t);




					if (m_pMap->m_bMapEdit)
					{
						SPHERE RangeSphere;
						RangeSphere.vCenter = vIntersection;
						RangeSphere.Radius = 10;
					}
				}
					/*if (m_pSelect->GetIntersection(
						m_pSelect->m_Ray.m_Orig,
						vEnd,
						vNormal,
						v0, v1, v2))
					{
						if (I_Select.PointInPolygon(
							I_Select.m_vIntersection,
							vNormal,
							v0, v1, v2))
						{
							vIntersection = I_Select.m_vIntersection;
							TCHAR szBuffer[256] = { 0, };
							swprintf_s(szBuffer,
								L"전체[%02d],%10.4f:%10.4f:%10.4f:",
								m_QuadTree->m_SelectNodeList.size(),
								vIntersection.x,
								vIntersection.y,
								vIntersection.z);
							m_Write.Add(szBuffer);

						}
					}*/
			}
		}
	}
	return true;
}

void HQuadTree::Set()
{
	m_BoxLine = make_shared<KG_ShapeLine>();

	m_BoxLine->Create(m_pMap->m_obj.m_pd3dDevice,
		m_pMap->m_obj.m_pContext,
		L"../../data/shader/DefaultShader.txt", nullptr,
		"VSLine", "PSLine");
}
void HQuadTree::CreateBB(KG_Node* pNode)
{



	DWORD dwTL = pNode->m_dwCorner[0];
	DWORD dwTR = pNode->m_dwCorner[1];
	DWORD dwBL = pNode->m_dwCorner[2];
	DWORD dwBR = pNode->m_dwCorner[3];

	pNode->m_Box.vMin.x = m_pMap->m_VerTex[dwTL].p.x;
	pNode->m_Box.vMin.y = 999999999.0f;
	pNode->m_Box.vMin.z = m_pMap->m_VerTex[dwBL].p.z;
	pNode->m_Box.vMax.x = m_pMap->m_VerTex[dwTR].p.x;
	pNode->m_Box.vMax.y = -999999999.0f;
	pNode->m_Box.vMax.z = m_pMap->m_VerTex[dwTL].p.z;

	DWORD dwSize = (dwTR - dwTL)*(dwTR - dwTL) * 2 * 3;
	pNode->m_IndexList.resize(dwSize);

	DWORD dwStartRow = dwTL / m_pMap->m_iRowNum;
	DWORD dwEndRow = dwBL / m_pMap->m_iRowNum;;

	DWORD dwStartCol = dwTL % m_pMap->m_iRowNum;
	DWORD dwEndCol = dwTR % m_pMap->m_iRowNum;

	DWORD dwIndex = 0;
	if (pNode->m_ObjList.size() <= 0)
	{
		for (DWORD dwRow = dwStartRow; dwRow < dwEndRow; dwRow++)
		{
			for (DWORD dwCol = dwStartCol; dwCol < dwEndCol; dwCol++)
			{
				dwIndex = dwRow * m_pMap->m_iRowNum + dwCol;
				if (pNode->m_Box.vMin.y > m_pMap->m_VerTex[dwIndex].p.y)
				{
					pNode->m_Box.vMin.y = m_pMap->m_VerTex[dwIndex].p.y;
				}
				if (pNode->m_Box.vMax.y < m_pMap->m_VerTex[dwIndex].p.y)
				{
					pNode->m_Box.vMax.y = m_pMap->m_VerTex[dwIndex].p.y;
				}
			}
		}
	}
	else
	{
		for (int iObj = 0; iObj < pNode->m_ObjList.size(); iObj++)
		{
			if (pNode->m_Box.vMin.y > pNode->m_ObjList[iObj].m_Box.vMin.y)
			{
				pNode->m_Box.vMin.y = pNode->m_ObjList[iObj].m_Box.vMin.y;
			}
			if (pNode->m_Box.vMax.y < pNode->m_ObjList[iObj].m_Box.vMax.y)
			{
				pNode->m_Box.vMax.y = pNode->m_ObjList[iObj].m_Box.vMax.y;
			}
		}
	}

	
	pNode->m_Box.vCenter = (pNode->m_Box.vMax + pNode->m_Box.vMin) / 2;
	pNode->m_Box.vAxis[0] = D3DXVECTOR3(1, 0, 0);
	pNode->m_Box.vAxis[1] = D3DXVECTOR3(0, 1, 0);
	pNode->m_Box.vAxis[2] = D3DXVECTOR3(0, 0, 1);
	D3DXVECTOR3 vHalf = pNode->m_Box.vMax - pNode->m_Box.vCenter;
	pNode->m_Box.fExtent[0] = D3DXVec3Dot(&pNode->m_Box.vAxis[0], &vHalf);;
	pNode->m_Box.fExtent[1] = D3DXVec3Dot(&pNode->m_Box.vAxis[1], &vHalf);
	pNode->m_Box.fExtent[2] = D3DXVec3Dot(&pNode->m_Box.vAxis[2], &vHalf);
	if (pNode->m_Box.vMax.y == 0)
	{
		pNode->m_Box.fExtent[1]=10;
	}

}
void HQuadTree::ChangeBB(KG_Node* pNode,KG_Box Box)
{
	pNode->m_Box = Box;
}
KG_Node* HQuadTree::CreateNode(KG_Node* pParent, DWORD dwTL, DWORD dwTR, DWORD dwBL, DWORD dwBR)
{
	KG_Node* pNode = 0;
	SAFE_NEW(pNode, KG_Node);



	pNode->m_dwCorner[0] = dwTL;
	pNode->m_dwCorner[1] = dwTR;
	pNode->m_dwCorner[2] = dwBL;
	pNode->m_dwCorner[3] = dwBR;





	pNode->m_iQuadTreeIndex = m_iQuadTreeIndex;

	CreateBB(pNode);
	if (pParent != nullptr)
		pNode->m_dwDepth = pParent->m_dwDepth + 1;
	else
	{
		pNode->m_dwDepth = 0;
	}
	m_iQuadTreeIndex++;
	return pNode;

}

BOOL HQuadTree::Build(JH_Map* pMap, KG_Camera* pCamera)
{
	m_pMap = pMap;
	m_pCamera = pCamera;
	Release();//전 데이터 삭제

	Set();
	DWORD dwTL = 0;
	DWORD dwTR = m_pMap->m_iColumNum - 1;
	DWORD dwBL = m_pMap->m_iColumNum*(m_pMap->m_iRowNum - 1);
	DWORD dwBR = m_pMap->m_iColumNum*m_pMap->m_iRowNum - 1;
	m_pRootNode = CreateNode(nullptr, dwTL, dwTR, dwBL, dwBR);

	BuildTree(m_pRootNode);


	return TRUE;
}
BOOL HQuadTree::BuildTree(KG_Node* pNode)
{
	if (DivideNode(pNode))
	{
		for (int iNode = 0; iNode < 4; iNode++)
		{
			BuildTree(pNode->m_pChild[iNode]);
		}
	}
	return TRUE;
}
BOOL HQuadTree::DivideNode(KG_Node*pNode)
{
	//dwTL		c0			dwTR




	//c1		c2			c3



	//dwBL		c4			dwBR
	if (pNode->m_dwDepth < 3)
	{
		DWORD dwTL = pNode->m_dwCorner[0];
		DWORD dwTR = pNode->m_dwCorner[1];
		DWORD dwBL = pNode->m_dwCorner[2];
		DWORD dwBR = pNode->m_dwCorner[3];

		DWORD c0 = (dwTR + dwTL) / 2;
		DWORD c1 = (dwBL + dwTL) / 2;
		DWORD c2 = (dwBR + dwTL) / 2;
		DWORD c3 = (dwTR + dwBR) / 2;
		DWORD c4 = (dwBR + dwBL) / 2;

		pNode->m_pChild[0] = CreateNode(pNode, dwTL, c0, c1, c2);
		pNode->m_pChild[1] = CreateNode(pNode, c0, dwTR, c2, c3);
		pNode->m_pChild[2] = CreateNode(pNode, c1, c2, dwBL, c4);
		pNode->m_pChild[3] = CreateNode(pNode, c2, c3, c4, dwBR);

		return TRUE;
	}
	else
	{
		pNode->m_isLeaf = TRUE;
		CreateIndexList(pNode);
	}


	return FALSE;

}
void HQuadTree::DirectSelect(KG_Node* pNode)
{

}
void HQuadTree::DrawNodeLine(KG_Node* pNode)
{
	if (pNode == nullptr) { return; }

	if (pNode->m_isLeaf == TRUE)
	{
		int Pos = m_pCamera->CheckOBBInPlane(pNode->m_Box);
		if (Pos != P_BACK)
		{
			DrawLine(pNode);
		}

	}
	for (int iNode = 0; iNode < 4; iNode++)
	{

		DrawNodeLine(pNode->m_pChild[iNode]);
	}

}
void HQuadTree::DrawLine(KG_Node* pNode)
{
	m_BoxLine->SetMatrix(nullptr,
		&m_pCamera->m_View,
		&m_pCamera->m_Proj);

	D3DXVECTOR3 vS;
	vS.x = pNode->m_Box.vMin.x;
	vS.y = pNode->m_Box.vMax.y;
	vS.z = pNode->m_Box.vMax.z;
	D3DXVECTOR3 vE;
	vE.x = pNode->m_Box.vMax.x;
	vE.y = pNode->m_Box.vMax.y;
	vE.z = pNode->m_Box.vMax.z;
	m_BoxLine->Draw(vE, vS, D3DXVECTOR4(1, 0, 0, 1));
	vS.x = pNode->m_Box.vMax.x;
	vS.y = pNode->m_Box.vMax.y;
	vS.z = pNode->m_Box.vMin.z;
	m_BoxLine->Draw(vE, vS, D3DXVECTOR4(1, 0, 0, 1));
	vE.x = pNode->m_Box.vMin.x;
	vE.y = pNode->m_Box.vMax.y;
	vE.z = pNode->m_Box.vMin.z;
	m_BoxLine->Draw(vS, vE, D3DXVECTOR4(1, 0, 0, 1));
	vS.x = pNode->m_Box.vMin.x;
	vS.y = pNode->m_Box.vMax.y;
	vS.z = pNode->m_Box.vMax.z;
	m_BoxLine->Draw(vS, vE, D3DXVECTOR4(1, 0, 0, 1));


	vS.x = pNode->m_Box.vMin.x;
	vS.y = pNode->m_Box.vMin.y;
	vS.z = pNode->m_Box.vMax.z;
	vE.x = pNode->m_Box.vMax.x;
	vE.y = pNode->m_Box.vMin.y;
	vE.z = pNode->m_Box.vMax.z;
	m_BoxLine->Draw(vE, vS, D3DXVECTOR4(1, 0, 0, 1));
	vS.x = pNode->m_Box.vMax.x;
	vS.y = pNode->m_Box.vMin.y;
	vS.z = pNode->m_Box.vMin.z;
	m_BoxLine->Draw(vE, vS, D3DXVECTOR4(1, 0, 0, 1));
	vE.x = pNode->m_Box.vMin.x;
	vE.y = pNode->m_Box.vMin.y;
	vE.z = pNode->m_Box.vMin.z;
	m_BoxLine->Draw(vS, vE, D3DXVECTOR4(1, 0, 0, 1));
	vS.x = pNode->m_Box.vMin.x;
	vS.y = pNode->m_Box.vMin.y;
	vS.z = pNode->m_Box.vMax.z;
	m_BoxLine->Draw(vS, vE, D3DXVECTOR4(1, 0, 0, 1));


	vS.x = pNode->m_Box.vMin.x;
	vS.y = pNode->m_Box.vMax.y;
	vS.z = pNode->m_Box.vMax.z;
	vE.x = pNode->m_Box.vMin.x;
	vE.y = pNode->m_Box.vMin.y;
	vE.z = pNode->m_Box.vMax.z;
	m_BoxLine->Draw(vE, vS, D3DXVECTOR4(1, 0, 0, 1));
	vS.x = pNode->m_Box.vMax.x;
	vS.y = pNode->m_Box.vMax.y;
	vS.z = pNode->m_Box.vMax.z;
	vE.x = pNode->m_Box.vMax.x;
	vE.y = pNode->m_Box.vMin.y;
	vE.z = pNode->m_Box.vMax.z;
	m_BoxLine->Draw(vE, vS, D3DXVECTOR4(1, 0, 0, 1));
	vS.x = pNode->m_Box.vMax.x;
	vS.y = pNode->m_Box.vMax.y;
	vS.z = pNode->m_Box.vMin.z;
	vE.x = pNode->m_Box.vMax.x;
	vE.y = pNode->m_Box.vMin.y;
	vE.z = pNode->m_Box.vMin.z;
	m_BoxLine->Draw(vS, vE, D3DXVECTOR4(1, 0, 0, 1));
	vS.x = pNode->m_Box.vMin.x;
	vS.y = pNode->m_Box.vMax.y;
	vS.z = pNode->m_Box.vMin.z;
	vE.x = pNode->m_Box.vMin.x;
	vE.y = pNode->m_Box.vMin.y;
	vE.z = pNode->m_Box.vMin.z;
	m_BoxLine->Draw(vS, vE, D3DXVECTOR4(1, 0, 0, 1));
}
void HQuadTree::GetSelectNode(KG_Node* pNode)
{
	
	if (pNode == nullptr) return;
	if (m_pSelect->OBBToRay(&pNode->m_Box) == false) return;
	
	if (pNode->m_isLeaf)
	{

		m_SelectNodeList.push_back(pNode);
		return;
	}
	for (int iNode = 0; iNode < 4; iNode++)
	{
		GetSelectNode(pNode->m_pChild[iNode]);

	}
}
void HQuadTree::GetSelectObj(KG_Node* pNode)
{
	if (pNode == nullptr) return;
	if (m_pSelect->ChkOBBToRay(&pNode->m_Box) == false) return;


	for (int iObj = 0; iObj < pNode->m_ObjList.size(); iObj++)
	{
		if (m_pSelect->ChkOBBToRay(&pNode->m_ObjList[iObj].m_Box))
		{
			m_SelectObjList.push_back(pNode->m_ObjList[iObj]);
			CreateBB(pNode);
		}
	}

	for (int iNode = 0; iNode < 4; iNode++)
	{
		GetSelectObj(pNode->m_pChild[iNode]);
	}
}
	
bool HQuadTree::GetObjectAddNode(JH_MapObj Obj)
{
	bool b = false;
	if (!m_pRootNode) return false;
	
		if (CheckRect(m_pRootNode,Obj))
		{
			KG_Node* pNode = FindNode(m_pRootNode, Obj);
			if (pNode)
			{
				
				Obj.SetQuadIndex(pNode->m_iQuadTreeIndex);
				
				pNode->m_ObjList.insert(make_pair(Obj.GetID(),Obj));
				CreateBB(pNode);
				m_ContainObjNode.push_back(pNode);
				b = true;
				return b;
			}
		}

	
	return b;

}
KG_Node* HQuadTree::FindNode(KG_Node* pNode, JH_MapObj Obj)
{
	std::queue<KG_Node*>   m_QueueList;
	do {
		for (int iChild = 0; iChild < 4; iChild++)
		{
			if (pNode->m_pChild[iChild] == nullptr) break;
			if (CheckRect(pNode->m_pChild[iChild], Obj))
			{
				m_QueueList.push(pNode->m_pChild[iChild]);
			}
		}
		if (m_QueueList.empty()) break;
		pNode = m_QueueList.front();
		m_QueueList.pop();

	} while (pNode);
	return pNode;
}
bool HQuadTree::CheckRect(KG_Node* pNode, JH_MapObj Obj)
{
	if (pNode->m_Box.vMin.x <= Obj.m_Box.vMin.x &&
		pNode->m_Box.vMax.x >= Obj.m_Box.vMax.x)
	{
		/*if (pNode->m_Box.vMin.y <= obj.m_tBox.vMin.y &&
			pNode->m_Box.vMax.y >= obj.m_tBox.vMax.y)*/
		{
			if (pNode->m_Box.vMin.z <= Obj.m_Box.vMin.z &&
				pNode->m_Box.vMax.z >= Obj.m_Box.vMax.z)
			{
				return true;
			}
		}
	}
	return false;
}
void  HQuadTree::FindObjectNode(KG_Node* pNode, JH_MapObj Obj)
{
	if (pNode == nullptr) return;
	if (m_bFind) { return; }

	if (pNode->m_iQuadTreeIndex==Obj.GetQuadIndex())
	{
		m_pFindNode = pNode;
		CreateBB(pNode);
		m_bFind = true;
		return;
	}
	for (int iNode = 0; iNode < 4; iNode++)
	{
		FindObjectNode(pNode->m_pChild[iNode],Obj);

	}
	
	m_bFind = false;
}

void HQuadTree::FindNearInterSectionNode(KG_Node* pNode, D3DXVECTOR3 vInterSection)
{
	
	float distance = D3DXVec3Length(&(vInterSection - m_pCamera->m_Pos));
	
	if (m_fdistance>distance)
	{
		m_fdistance = distance;
		m_pNearPointNode = pNode;
	}
}
bool HQuadTree::Frame()
{
	m_SelectNodeList.clear();
	m_DrawObjNodeList.clear();
	m_DrawNodeList.clear();
	m_SelectObjList.clear();
	FindDrawNode(m_pRootNode);
	

	m_pMap->m_SkyBox->Frame();
	I_LIGHT_MGR.Frame();
	I_LIGHT_MGR.m_cbLight.vEyeDir = { m_pCamera->m_Look,30 };
	I_LIGHT_MGR.m_cbLight.vEyePos = { m_pCamera->m_Pos,30 };
	return true;
}
bool HQuadTree::Render()
{

	m_pMap->m_SkyBox->SetMatrix(nullptr, &m_pCamera->m_View, &m_pCamera->m_Proj);
	m_pMap->m_SkyBox->Render();
	m_pMap->RenderSet(m_pCamera);
	m_pMap->PreRender();

	ID3D11ShaderResourceView* SRVLIST[10] = {nullptr};

	int iSPTNum = m_pMap->m_vSplattTextureList.size();//스플래팅 텍스쳐 개수


		for (int i = 0; i < m_pMap->m_vSplattTextureList.size(); i++)
		{
			
			if (i >= 8)
			{
				iSPTNum = 8; //100 개이상 넘어가면 더이상 추가하지않음 
				break;
			}
			SRVLIST[i] = m_pMap->m_vSplattTextureList[i]->m_pTextureRV;
		
		}

		if (iSPTNum>0)
		{
			m_pMap->m_obj.m_pContext->PSSetShaderResources(3,
				iSPTNum, SRVLIST);
			m_pMap->m_CBSubData.MapSubData.x = iSPTNum;
			m_pMap->m_obj.m_pContext->UpdateSubresource(m_pMap->m_CBSub.Get(), 0, 0, &m_pMap->m_CBSubData, 0, 0);
			m_pMap->m_obj.m_pContext->PSSetConstantBuffers(2, 1, m_pMap->m_CBSub.GetAddressOf());
		}
	

		m_pMap->m_obj.m_pContext->PSSetShaderResources(2, 1,m_pMap->m_pCopySrv.GetAddressOf());

		//CDX::ApplyRS(m_pMap->m_obj.m_pContext, CDX::KG_DxState::g_pRSDepth);
	for (int iNode = 0; iNode < m_DrawNodeList.size(); iNode++)
	{
		KG_Node* pNode = m_DrawNodeList[iNode];
		m_pMap->m_obj.m_pContext->IASetIndexBuffer(pNode->m_pIndexBuffer.Get(),
			DXGI_FORMAT_R32_UINT, 0);
		m_pMap->m_obj.m_pContext->DrawIndexed(pNode->m_IndexList.size(), 0, 0);
	}
	return true;
}
bool HQuadTree::Draw(KG_Node* pNode, ID3D11DeviceContext* pContext)
{
	if (pNode == nullptr) { return false; }

	if (pNode->m_isLeaf == TRUE)
	{
		int Pos = m_pCamera->CheckOBBInPlane(pNode->m_Box);
		if (Pos != P_BACK)
		{
			pContext->IASetIndexBuffer(pNode->m_pIndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
			pContext->DrawIndexed(pNode->m_IndexList.size(), 0, 0);
		}

	}
	for (int iNode = 0; iNode < 4; iNode++)
	{
		Draw(pNode->m_pChild[iNode], pContext);
	}
}
void HQuadTree::CreateIndexList(KG_Node* pNode)
{
	DWORD dwTL = pNode->m_dwCorner[0];
	DWORD dwTR = pNode->m_dwCorner[1];
	DWORD dwBL = pNode->m_dwCorner[2];
	DWORD dwBR = pNode->m_dwCorner[3];

	DWORD dwSize = (dwTR - dwTL)*(dwTR - dwTL) * 2 * 3;

	pNode->m_IndexList.resize(dwSize);

	DWORD dwStartRow = dwTL / m_pMap->m_iRowNum;
	DWORD dwEndRow = dwBL / m_pMap->m_iRowNum;

	DWORD dwStartCol = dwTL % m_pMap->m_iRowNum;
	DWORD dwEndCol = dwTR % m_pMap->m_iRowNum;

	DWORD dwIndex = 0;
	for (int iRow = dwStartRow; iRow < dwEndRow; iRow++)
	{

		for (int iCol = dwStartCol; iCol < dwEndCol; iCol++)
		{
			pNode->m_IndexList[dwIndex++] = iRow * m_pMap->m_iColumNum + iCol;
			pNode->m_IndexList[dwIndex++] = iRow * m_pMap->m_iColumNum + iCol + 1;
			pNode->m_IndexList[dwIndex++] = (iRow + 1) * m_pMap->m_iColumNum + iCol;

			pNode->m_IndexList[dwIndex++] = (iRow + 1) * m_pMap->m_iColumNum + iCol;
			pNode->m_IndexList[dwIndex++] = iRow * m_pMap->m_iColumNum + iCol + 1;
			pNode->m_IndexList[dwIndex++] = (iRow + 1) * m_pMap->m_iColumNum + iCol + 1;

		}
	}
	pNode->m_pIndexBuffer.Attach(CDXH::CreateIndexBuffer(
		m_pMap->m_obj.m_pd3dDevice,
		&pNode->m_IndexList.at(0),
		pNode->m_IndexList.size(), sizeof(DWORD)));



}
bool HQuadTree::Release()
{
	SAFE_DEL(m_pRootNode);
//	if(m_pNearPointNode)SAFE_DEL(m_pNearPointNode);
	return true;
}


void HQuadTree::FindDrawNode(KG_Node* pNode)
{
	if (pNode == nullptr) return;
	int pos = m_pCamera->CheckOBBInPlane(pNode->m_Box);

	if (pNode->m_isLeaf == TRUE && pos != P_BACK)
	{
		m_DrawNodeList.push_back(pNode);
		if (pNode->m_ObjList.size() > 0)
		{
			m_DrawObjNodeList.push_back(pNode);
		}
		return;
	}
	if (pos == P_FRONT)
	{
		VisibleNode(pNode);
		return;
	}

	if (pNode->m_ObjList.size() > 0)
	{
		m_DrawObjNodeList.push_back(pNode);
	}

	for (int iNode = 0; iNode < 4; iNode++)
	{
		FindDrawNode(pNode->m_pChild[iNode]);
	}
}

void HQuadTree::VisibleNode(KG_Node* pNode)
{
	if (pNode == nullptr) return;
	if (pNode->m_isLeaf == TRUE)
	{
		m_DrawNodeList.push_back(pNode);
		if (pNode->m_ObjList.size() > 0)
		{
			m_DrawObjNodeList.push_back(pNode);
		}
		return;
	}
	if (pNode->m_ObjList.size() > 0)
	{
		m_DrawObjNodeList.push_back(pNode);
	}
	for (int iNode = 0; iNode < 4; iNode++)
	{
		VisibleNode(pNode->m_pChild[iNode]);
	}
}

HQuadTree::HQuadTree()
{
	m_bFind = false;
	float m_fTimer = 0.0f;
	m_fdistance = 100000.0f;
	m_pRootNode = nullptr;
	m_pNearPointNode = nullptr;
	m_iQuadTreeIndex = 0;
}
HQuadTree::~HQuadTree()
{
	Release();
}
