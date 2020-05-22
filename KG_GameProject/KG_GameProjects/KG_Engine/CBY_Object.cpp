#include "CBY_Object.h"
#include "CBY_CharMgr.h"

namespace CBY
{
	bool CBY_Object::SkinLoad(T_STR pszLoad)
	{
		int index, list;
		index = I_CHARACTER.SkinLoad(pszLoad, m_obj.m_pd3dDevice, m_obj.m_pContext);
		m_SkinObjIndex.push_back(index);

		list = m_ObjList.size();
		m_ObjList.push_back(std::make_shared<CBY_SkinObj>());
		*m_ObjList[list] = *I_CHARACTER.m_SkinLoadList[index];

		SetCharBox();
		return true;
	}

	bool CBY_Object::BoneLoad(T_STR pszLoad)
	{
		m_BoneIndex = I_CHARACTER.BoneLoad(pszLoad, m_obj.m_pd3dDevice, m_obj.m_pContext);

		m_BindBone = std::make_shared<CBY_BoneObj>();
		*m_BindBone = *I_CHARACTER.m_BoneLoadList[m_BoneIndex];

		m_Bone = m_BindBone.get();

		m_Scene = m_BindBone->m_Scene;
		return true;
	}

	bool CBY_Object::Create(ID3D11Device* pd3dDevice, ID3D11DeviceContext* Context, const TCHAR* ShaderFileName, const TCHAR* TexFileName, const CHAR* VSName, const CHAR* PSName)
	{
		HRESULT hr = S_OK;

		m_obj.m_pd3dDevice = pd3dDevice;
		m_obj.m_pContext = Context;

		if (FAILED(LoadShader(ShaderFileName, VSName, PSName)))
		{
			return false;
		}

		if (FAILED(CreateConstantBuffer()))
		{
			return false;
		}

		if (FAILED(CreateInputLayout()))
		{
			return false;
		}
		if (FAILED(LoadTexture(TexFileName)))
		{
			return false;
		}
		Init();
		return true;
	}

	HRESULT CBY_Object::CreateInputLayout()
	{
		HRESULT hr = S_OK;
		const D3D11_INPUT_ELEMENT_DESC layout[] =
		{
			{ "POSITION",  0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "NORMAL",  0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "COLOR",  0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 24,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD",  0, DXGI_FORMAT_R32G32_FLOAT, 0, 40,  D3D11_INPUT_PER_VERTEX_DATA, 0 },

			{ "TEXCOORD",  1, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 48,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD",  2, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 64,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};
		UINT iElementCount = sizeof(layout) /
			sizeof(layout[0]);
		m_obj.m_pd3dDevice->CreateInputLayout(
			layout,
			iElementCount,
			m_obj.m_pVertexCode->GetBufferPointer(),
			m_obj.m_pVertexCode->GetBufferSize(),
			&m_obj.m_pVertexLayout);
		return hr;
	}
	HRESULT CBY_Object::CreateConstantBuffer()
	{
		KG_Model::CreateConstantBuffer();

		HRESULT hr = S_OK;
		ZeroMemory(&m_cbBoneWorld, sizeof(CBConstBoneWorld));

		m_pCBConstBoneWorld.Attach(
			CDXH::CreateConstantBuffer(
				m_obj.m_pd3dDevice,
				nullptr, 1,
				sizeof(CBConstBoneWorld),
				true));
		return hr;
	}

	void CBY_Object::SetMatrix(D3DXMATRIX* world, D3DXMATRIX* view, D3DXMATRIX* proj)
	{
		KG_Model::SetMatrix(world, view, proj);

		{	//캐릭터를 감싼 바운딩 박스의 움직임을 제어하는 곳
			D3DXVECTOR3 vScale, vPos, vSize;
			D3DXQUATERNION qRot;
			D3DXMatrixDecompose(&vScale, &qRot, &vPos, world);
			vSize = m_ObjList[0]->m_ObjList[0]->m_CharBox.vMax - m_ObjList[0]->m_ObjList[0]->m_CharBox.vCenter;
			vSize.x *= vScale.x;
			vSize.y *= vScale.y;
			vSize.z *= vScale.z;
			vPos += m_ObjList[0]->m_ObjList[0]->m_CharBox.vCenter;


			m_CharBox.CreateBox(0, vPos, vSize.x, vSize.y, vSize.z);		//박스 업데이트
		}

		{
			for (int iBox = 0; iBox < m_BoxList.size(); iBox++)
			{
				D3DXVECTOR3 vScale, vPos, vSize;
				D3DXQUATERNION qRot;
				D3DXMatrixDecompose(&vScale, &qRot, &vPos, world);
				vSize = m_BoxList[iBox].GetSize();
				vSize.x *= vScale.x;
				vSize.y *= vScale.y;
				vSize.z *= vScale.z;
				vPos += m_BoxList[iBox].GetPos();

				m_BoxList[iBox].CreateBox(m_BoxList[iBox].GetBoneIndex(),
					vPos, vSize.x, vSize.y, vSize.z);
			}
		}
	}

	bool CBY_Object::Init()
	{
		for (int iBone = 0; iBone < 255; iBone++)
		{
			D3DXMatrixIdentity(&m_pMatrixList[iBone]);
		}

		return true;
	}

	bool CBY_Object::Frame()
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
			D3DXMATRIX mat = m_ObjList[0]->m_matBoneBindPoss[iBone] * m_pMatrixList[iBone];		//바인드 포즈는 공통이다
			D3DXMatrixTranspose(&m_cbBoneWorld.g_matConstBoneWorld[iBone], &mat);
		}

		D3D11_MAPPED_SUBRESOURCE mapResource;
		m_obj.m_pContext->Map(m_pCBConstBoneWorld.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mapResource);
		memcpy(mapResource.pData, &m_cbBoneWorld, sizeof(CBConstBoneWorld));
		m_obj.m_pContext->Unmap(m_pCBConstBoneWorld.Get(), 0);

		return true;
	}

	bool CBY_Object::Update(D3DXMATRIX* parmat)
	{
		m_fElapseTick = 0;
		if (m_dwAniType == CHAR_FRAMETYPE)
		{
			m_Bone->Update(m_StateList[m_dwState].m_iStartFrame, m_StateList[m_dwState].m_iEndFrame,
				m_fElapseTick, m_pMatrixList);
		}

		else if (m_dwAniType == CHAR_MTRTYPE)
		{
			m_Bone->ObjUpdate(0, 0, 0, m_pMatrixList, parmat, m_iObjSocket);
		}

		for (int iBone = 0; iBone < m_ObjList[0]->m_matBoneBindPoss.size(); iBone++)
		{
			D3DXMATRIX mat;
			mat = m_ObjList[0]->m_matBoneBindPoss[iBone] * m_pMatrixList[iBone];		//바인드 포즈는 공통이다
			D3DXMatrixTranspose(&m_cbBoneWorld.g_matConstBoneWorld[iBone], &mat);
		}

		D3D11_MAPPED_SUBRESOURCE mapResource;
		m_obj.m_pContext->Map(m_pCBConstBoneWorld.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mapResource);
		memcpy(mapResource.pData, &m_cbBoneWorld, sizeof(CBConstBoneWorld));
		m_obj.m_pContext->Unmap(m_pCBConstBoneWorld.Get(), 0);
		return true;
	}

	bool CBY_Object::Render()
	{
		PreRender();
		CharPostRender();

		return true;
	}

	bool CBY_Object::Release()
	{
		return true;
	}

	bool CBY_Object::PreRender()
	{
		m_obj.m_pContext->VSSetShader(m_obj.m_pVS.Get(), NULL, 0);
		m_obj.m_pContext->PSSetShader(m_obj.m_pPS.Get(), NULL, 0);

		m_obj.m_pContext->VSSetConstantBuffers(0, 1, m_obj.m_pConstantBuffer.GetAddressOf());
		m_obj.m_pContext->PSSetConstantBuffers(0, 1, m_obj.m_pConstantBuffer.GetAddressOf());

		m_obj.m_pContext->IASetInputLayout(m_obj.m_pVertexLayout.Get());

		m_obj.m_pContext->PSSetShaderResources(0, 1, m_obj.m_pSRV.GetAddressOf());

		m_obj.m_pContext->VSSetConstantBuffers(1, 1, m_pCBConstBoneWorld.GetAddressOf());
		return true;
	}

	void CBY_Object::CharPostRender()
	{
		for (int iObj = 0; iObj < m_ObjList.size(); iObj++)
		{
			//m_ObjList[iObj]->SetMatrix(&m_matWorld,&m_matView, &m_matProj);
			m_ObjList[iObj]->Render();
		}
	}

	void CBY_Object::BoneBoxRender(CBY_MeshSkin* obj, int index)
	{
		D3DXMATRIX scl;
		D3DXMatrixIdentity(&scl);
		D3DXMatrixScaling(&scl, 5, 5, 5);
		D3DXMATRIX mat = m_ObjList[0]->m_matBoneBindPoss[index] * scl * m_pMatrixList[index];
		obj->m_BoneBox.SetMatrix(&(mat*m_matWorld), &m_matView, &m_matProj);
		//obj->m_BoneBox.SetMatrix(nullptr, &m_matView, &m_matProj);
		obj->m_BoneBox.Render();
	}

	void CBY_Object::SetStateNum(int statenum)
	{
		m_StateList.resize(statenum);
	}

	void CBY_Object::SetState(int dw)
	{
		if (dw == m_dwState)
		{
			return;
		}
		if (m_dwAniType == CHAR_MTRTYPE)
		{
			m_StateList[m_dwState].m_Bone.m_fElapseTick = 0;
		}
		else
		{
			m_BindBone->m_fElapseTick = m_StateList[m_dwState].m_iStartFrame;
		}
		m_dwState = dw;

		m_Bone = &m_StateList[m_dwState].m_Bone;
		SetCharBox();
	}

	int CBY_Object::GetStateNum()
	{
		return m_StateList.size();
	}

	void CBY_Object::SetMTRApply(T_STR pszLoad, int state)
	{
		m_dwAniType = CHAR_MTRTYPE;

		if (m_StateList.size() > 0)
		{
			DWORD index = I_CHARACTER.BoneLoad(pszLoad, m_obj.m_pd3dDevice, m_obj.m_pContext);

			if (m_StateList.size() > state)
			{
				m_StateList[state].m_Bone = *I_CHARACTER.m_BoneLoadList[index];
			}
			else
			{
				for (int i = m_StateList.size(); i <= state; i++)
				{
					Char_State_Info info;
					info.m_Bone = *I_CHARACTER.m_BoneLoadList[index];
					m_StateList.push_back(info);
				}
			}
		}
		else
		{
			DWORD index = I_CHARACTER.BoneLoad(pszLoad, m_obj.m_pd3dDevice, m_obj.m_pContext);
			for (int i = m_StateList.size(); i <= state; i++)
			{
				Char_State_Info info;
				info.m_Bone = *I_CHARACTER.m_BoneLoadList[index];
				m_StateList.push_back(info);
			}
		}
	}

	void CBY_Object::SetFrameTime(int m_dwState, float start, float end)
	{
		if (m_dwState >= m_StateList.size())
		{
			Char_State_Info info;
			info.m_iStartFrame = start;
			info.m_iEndFrame = end;
			m_StateList.push_back(info);
		}
		else
		{
			m_StateList[m_dwState].m_iStartFrame = start;
			m_StateList[m_dwState].m_iEndFrame = end;
		}
	}

	void CBY_Object::SetCharRootBone(int ibone)
	{
		m_iRoot = ibone;
	}

	D3DXVECTOR3 CBY_Object::GetCharPos()
	{
		D3DXMATRIX mat = m_pMatrixList[m_iRoot] * m_matWorld;
		D3DXVECTOR3 pos = D3DXVECTOR3(mat._41, mat._42, mat._43);
		return pos;
	}

	void CBY_Object::SetCharBox()
	{
		D3DXVECTOR3 size = m_ObjList[0]->m_ObjList[0]->m_CharBox.vMax- m_ObjList[0]->m_ObjList[0]->m_CharBox.vCenter;
		m_CharBox.CreateBox(0,
			m_ObjList[0]->m_ObjList[0]->m_CharBox.vCenter, size.x, size.y, size.z);

		//m_Bone->m_CharBox.vCenter.y = (m_ObjList[0]->m_ObjList[0]->m_CharBox.vMax.y + m_ObjList[0]->m_ObjList[0]->m_CharBox.vMin.y) / 2;
		//D3DXVECTOR3 size = m_ObjList[0]->m_ObjList[0]->m_CharBox.vMax - m_ObjList[0]->m_ObjList[0]->m_CharBox.vCenter;
		//m_CharBox.Create(m_obj.m_pd3dDevice, m_obj.m_pContext);
		//m_CharBox.CreateBox(0, m_ObjList[0]->m_ObjList[0]->m_CharBox.vCenter, size.x, size.y, size.z);
	}

	CBY_CharBox CBY_Object::GetCharBox()
	{
		return m_CharBox;
	}

	void CBY_Object::SetColBoxList(std::vector<CBY_CharBox>& boxlist)
	{
		boxlist.swap(m_BoxList);
		CreateColBox();
	}

	CBY_CharBox CBY_Object::SetColBoxList(int ibox)
	{
		return m_BoxList[ibox];
	}

	int CBY_Object::GetColBoxSize()
	{
		return m_BoxList.size();
	}


	void CBY_Object::CreateColBox()
	{
		for (int iBox = 0; iBox < m_BoxList.size(); iBox++)
		{
			D3DXVECTOR3 size = m_BoxList[iBox].GetSize();
			m_BoxList[iBox].CreateBox(m_BoxList[iBox].GetBoneIndex(),
				m_BoxList[iBox].GetPos(), size.x, size.y, size.z);
		}
	}

	void CBY_Object::SetSocket(int i)
	{
		m_iCharSocket = i;
	}

	int CBY_Object::GetSocket()
	{
		return m_iCharSocket;
	}

	void CBY_Object::SetObjSocke(int i)
	{
		m_iObjSocket = i;
	}

	int CBY_Object::GetObjSocke()
	{
		return m_iObjSocket;
	}

	CBY_Object::CBY_Object()
	{
		m_fElapseTick = 0;
		m_dwState = CHAR_IDLE;
		m_dwAniType = CHAR_FRAMETYPE;
		m_iStartFrame = 0;
		m_iEndFrame = 0;
		m_iCharSocket = -1;
		m_iObjSocket = -1;
	}


	CBY_Object::~CBY_Object()
	{
	}
}
