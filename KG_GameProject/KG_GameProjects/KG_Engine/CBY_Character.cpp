#include "CBY_Character.h"
#include "CBY_Object.h"
#include "CBY_CharMgr.h"

namespace CBY
{
	bool CBY_Character::SkinLoad(T_STR pszLoad)
	{
		int index, list;
		index = I_CHARACTER.SkinLoad(pszLoad, m_obj.m_pd3dDevice, m_obj.m_pContext);
		m_SkinObjIndex.push_back(index);

		list = m_ObjList.size();
		m_ObjList.push_back(std::make_shared<CBY_SkinObj>());
		*m_ObjList[list] = *I_CHARACTER.m_SkinLoadList[index];

		m_ObjList[0]->m_ObjList[0]->m_CharBox.vMax.z *= 1.5;
		m_ObjList[0]->m_ObjList[0]->m_CharBox.vMin.z *= 1.5;

		SetCharBox();
		return true;
	}

	bool CBY_Character::CharacterLoad(ID3D11Device* pd3dDevice, ID3D11DeviceContext* Context,T_STR pszLoad, const TCHAR* ShaderFileName, const TCHAR* TexFileName, const CHAR* VSName, const CHAR* PSName)
	{
		m_CharData.Load(pszLoad.c_str());
		Create(pd3dDevice, Context, ShaderFileName, TexFileName, VSName, PSName);
		for (DWORD dw = 0; dw < m_CharData.m_data.SknNameList.size(); dw++)
		{
			SkinLoad(m_CharData.m_data.SknNameList[dw]);
		}

		if (m_CharData.m_data.m_CharType == CHAR_FRAMETYPE)
		{
			SetStateNum(m_CharData.m_data.dwStateNum);

			for (DWORD dwState = 0; dwState < m_CharData.m_data.dwStateNum; dwState++)
			{
				SetCharAction(dwState, m_CharData.m_data.StateList[dwState].m_iStartFrame,
					m_CharData.m_data.StateList[dwState].m_iEndFrame);
			}

			for (DWORD dw = 0; dw < m_CharData.m_data.MtrList.size(); dw++)
			{
				BoneLoad(m_CharData.m_data.MtrList[dw].MtrName);
			}
		}
		else
		{
			SetStateNum(m_CharData.m_data.dwStateNum);

			for (DWORD dw = 0; dw < m_CharData.m_data.MtrList.size(); dw++)
			{
				if (m_CharData.m_data.MtrList[dw].State == -1)
				{
					BoneLoad(m_CharData.m_data.MtrList[dw].MtrName);
				}
				else
				{
					SetMTRApply(m_CharData.m_data.MtrList[dw].MtrName, m_CharData.m_data.MtrList[dw].State);
				}
			}
		}
		SetColBoxList(m_CharData.m_data.ColBoxList);
		m_CharData.m_data.ColBoxList.clear();

		for (DWORD dw = 0; dw < m_CharData.m_data.ObjList.size(); dw++)
		{
			for (DWORD ob = 0; ob < m_CharData.m_data.SknNameList.size(); ob++)
			{
				ObjLoad(m_CharData.m_data.ObjList[dw].objdata.SknNameList[0]);
			}

			if (m_CharData.m_data.ObjList[dw].objdata.m_CharType == CHAR_FRAMETYPE)
			{
				m_ObjectList[dw]->SetStateNum(m_CharData.m_data.ObjList[dw].objdata.dwStateNum);

				for (DWORD dwState = 0; dwState < m_CharData.m_data.ObjList[dw].objdata.dwStateNum; dwState++)
				{
					SetCharAction(dwState, m_CharData.m_data.ObjList[dw].objdata.StateList[dwState].m_iStartFrame,
						m_CharData.m_data.ObjList[dw].objdata.StateList[dwState].m_iEndFrame);
				}

				for (DWORD ob = 0; ob < m_CharData.m_data.MtrList.size(); ob++)
				{
					m_ObjectList[dw]->BoneLoad(m_CharData.m_data.ObjList[dw].objdata.MtrList[ob].MtrName);
				}
			}
			else
			{
				m_ObjectList[dw]->SetStateNum(m_CharData.m_data.ObjList[dw].objdata.dwStateNum);

				for (DWORD ob = 0; ob < m_CharData.m_data.ObjList[dw].objdata.MtrList.size(); ob++)
				{
					if (m_CharData.m_data.ObjList[dw].objdata.MtrList[ob].State == -1)
					{
						m_ObjectList[dw]->BoneLoad(m_CharData.m_data.ObjList[dw].objdata.MtrList[ob].MtrName);
					}
					else
					{
						m_ObjectList[dw]->SetMTRApply(m_CharData.m_data.ObjList[dw].objdata.MtrList[ob].MtrName,
							m_CharData.m_data.ObjList[dw].objdata.MtrList[ob].State);
					}
				}
			}

			SetObjectSocket(m_CharData.m_data.ObjList[dw].Socket, m_CharData.m_data.ObjList[dw].ObjSocket, m_CharData. m_data.ObjList[dw].FireSocket,dw);
			m_ObjectList[dw]->SetState(0);
		}

		SetState(0);
		return true;
	}

	bool CBY_Character::ObjLoad(T_STR pszSkinLoad)
	{
		std::shared_ptr<CBY_Weapon> obj = std::make_shared<CBY_Weapon>();
		obj->Create(m_obj.m_pd3dDevice, m_obj.m_pContext, L"../../data/shader/SkinShader.txt", nullptr, "VSSKIN", "PS");
		obj->SkinLoad(pszSkinLoad);
		//obj->BoneLoad(pszMtrLoad);
		m_ObjectList.push_back(obj);
		return true;
	}

	bool CBY_Character::Init()
	{
		CBY_Object::Init();
		return true;
	}

	bool CBY_Character::Frame()
	{
		m_fElapseTick = 0;
		if (m_dwAniType == CHAR_FRAMETYPE)
		{
			m_Bone->Update(m_StateList[m_dwState].m_iStartFrame, m_StateList[m_dwState].m_iEndFrame,
				m_fElapseTick, m_pMatrixList);
		}

		else if (m_dwAniType == CHAR_MTRTYPE)
		{
			m_Bone->MTRUpdate(0, 0, 0, m_pMatrixList);
		}

		for (int iBone = 0; iBone < m_ObjList[0]->m_matBoneBindPoss.size(); iBone++)
		{
			D3DXMATRIX mat = m_ObjList[0]->m_matBoneBindPoss[iBone] * m_pMatrixList[iBone];		//���ε� ����� �����̴�
			D3DXMatrixTranspose(&m_cbBoneWorld.g_matConstBoneWorld[iBone], &mat);
		}

		D3D11_MAPPED_SUBRESOURCE mapResource;
		m_obj.m_pContext->Map(m_pCBConstBoneWorld.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mapResource);
		memcpy(mapResource.pData, &m_cbBoneWorld, sizeof(CBConstBoneWorld));
		m_obj.m_pContext->Unmap(m_pCBConstBoneWorld.Get(), 0);


		for (int i = 0; i < m_ObjectList.size(); i++)
		{
			D3DXMATRIX mat;
			D3DXMatrixScaling(&mat, 0.5, 0.5, 0.5);

			if (m_ObjectList[i]->GetSocket() == -1)
			{
				m_ObjectList[i]->Frame();
			}
			else
			{
				mat._41 += m_pMatrixList[m_ObjectList[i]->GetSocket()]._41 / 2;
				mat._42 += m_pMatrixList[m_ObjectList[i]->GetSocket()]._42 / 2;
				mat._43 += m_pMatrixList[m_ObjectList[i]->GetSocket()]._43 / 2;
				m_ObjectList[i]->Update(&m_pMatrixList[m_ObjectList[i]->GetSocket()]);
			}

			//m_ObjectList[i]->SetMatrix(&(mat*m_matWorld), &m_matView, &m_matProj);
			m_ObjectList[i]->SetMatrix(&m_matWorld, &m_matView, &m_matProj);
		}

		return true;
	}

	void CBY_Character::SetObjectSocket(int iSocket, int iObjSocket, int iFireSocket,int iobj)
	{
		if (m_ObjectList.size() < 0)
		{
			return;
		}
		m_ObjectList[iobj]->SetSocket(iSocket);
		m_ObjectList[iobj]->SetObjSocke(iObjSocket);
		m_ObjectList[iobj]->SetFireSocket(iFireSocket);
	}

	bool CBY_Character::Render()
	{
		PreRender();
		CharPostRender();
		for (int i = 0; i < m_ObjectList.size(); i++)
		{
			m_ObjectList[i]->Render();
		}
		return true;
	}

	bool CBY_Character::Release()
	{
		CBY_Object::Release();

		m_ObjList.clear();
		for (int i = 0; i < m_ObjectList.size(); i++)
		{
			m_ObjectList[i]->Release();
		}
		return true;
	}

	void CBY_Character::SetCharAction(int state, float start, float end)
	{

		if (state >= m_CharData.m_data.StateList.size())
		{
			Char_State_Info info;
			info.m_iStartFrame = start;
			info.m_iEndFrame = end;
			m_CharData.m_data.StateList.push_back(info);
		}
		else
		{
			m_CharData.m_data.StateList[state].m_iStartFrame = start;
			m_CharData.m_data.StateList[state].m_iEndFrame = end;
		}

		SetFrameTime(state, start, end);
	}

	void CBY_Character::SetCharBox()
	{
		D3DXVECTOR3 size = m_ObjList[0]->m_ObjList[0]->m_CharBox.vMax - m_ObjList[0]->m_ObjList[0]->m_CharBox.vCenter;
		m_CharBox.CreateBox(0,
			m_ObjList[0]->m_ObjList[0]->m_CharBox.vCenter, size.x, size.y, size.z);
	}

	void CBY_Character::SetMatrix(D3DXMATRIX* world, D3DXMATRIX* view, D3DXMATRIX* proj)
	{
		KG_Model::SetMatrix(world, view, proj);

		{	//ĳ���͸� ���� �ٿ�� �ڽ��� �������� �����ϴ� ��
			D3DXMATRIX matRot;
			D3DXVECTOR3 vScale, vPos, vSize;
			D3DXQUATERNION qRot;
			D3DXMatrixDecompose(&vScale, &qRot, &vPos, world);
			D3DXMatrixRotationQuaternion(&matRot, &qRot);

			vSize = m_ObjList[0]->m_ObjList[0]->m_CharBox.vMax - m_ObjList[0]->m_ObjList[0]->m_CharBox.vCenter;
			vSize.x *= vScale.x;
			vSize.y *= vScale.y;
			vSize.z *= vScale.z;
			vPos += m_ObjList[0]->m_ObjList[0]->m_CharBox.vCenter;


			m_CharBox.CreateBox(0, vPos, vSize.x, vSize.y, vSize.z);		//�ڽ� ������Ʈ

			m_CharBox.UpdateBoxAxis(matRot);
		}

		{
			for (int iBox = 0; iBox < m_BoxList.size(); iBox++)
			{
				D3DXMATRIX matRot;
				D3DXVECTOR3 vScale, vPos, vSize;
				D3DXQUATERNION qRot;
				D3DXMatrixDecompose(&vScale, &qRot, &vPos, world);
				D3DXMatrixRotationQuaternion(&matRot, &qRot);

				vSize = m_BoxList[iBox].GetSize();
				vSize.x *= vScale.x;
				vSize.y *= vScale.y;
				vSize.z *= vScale.z;
				vPos += m_BoxList[iBox].GetPos();

				m_BoxList[iBox].CreateBox(m_BoxList[iBox].GetBoneIndex(),
					vPos, vSize.x, vSize.y, vSize.z);

				m_BoxList[iBox].UpdateBoxAxis(matRot);
			}
		}
	}

	CBY_Character::CBY_Character()
	{
	}


	CBY_Character::~CBY_Character()
	{
	}



}
