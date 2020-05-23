#include "KG_TestMain.h"
#include"KG_DxState.h"
#include"KG_Input.h"
#include"KG_ShapeMap.h"
#include"LightMgr.h"
#include "KG_Input.h"
#include "KG_Collision.h"


bool KG_TestMain::Init()
{
	CDX::ApplyBS(m_pContext, CDX::KG_DxState::g_pAlpahBlend);
	CDX::ApplySS(m_pContext, CDX::KG_DxState::g_pSampler);
	CDX::ApplyRS(m_pContext, CDX::KG_DxState::g_pRSSold);

	////////////////Char////////////////////	
	m_Character = std::make_shared<CBY::CBY_Character>();
	m_Character->CharacterLoad(m_pd3dDevice, m_pContext, L"../../data/char/save/CharTest.txt");

	m_Enemy = std::make_shared<CBY::CBY_Character>();
	m_Enemy->CharacterLoad(m_pd3dDevice, m_pContext, L"../../data/char/save/GirlInfoEx.txt");
	m_CharCamera = std::make_shared<CBY::CBY_CharacterCamera>();
	m_CharCamera->SetViewProj();
	m_CharCamera->SetCameraSpeed(30);
	m_pMainCamera = m_CharCamera.get();
	//////////////////////////////////////////

	//SetCursor(LoadCursor(g_hInstance, IDB_BITMAP1));

	//////////////Map/////////////////////////
	//LoadMapData(L"../../data/MapSave/SampleRust.Map");
	LoadMapData(L"../../data/MapSave/aa.Map");
	I_LIGHT_MGR.GetDevice(m_pd3dDevice);
	I_LIGHT_MGR.GetContext(m_pContext);
	I_LIGHT_MGR.Create(L"../../data/Shader/JHMapShader.txt", L"../../data/LightSrc/LightInfo.txt");

	//ComPuteShader
	(CDXH::CreateComputeShader(L"../../data/shader/ComputeAlpha.HLSL", "CSMAIN", m_pd3dDevice, m_pCS.GetAddressOf()));
	//////////////////////////////////////////

	return true;
}

bool KG_TestMain::Frame()
{
	//////////////////Map/////////////////
	if (m_Map == nullptr)return true;

	//test/adsfadsf
	m_Select.SetMarix(nullptr, &m_pMainCamera->m_View, &m_pMainCamera->m_Proj);

	D3DXVECTOR3 v0, v1, v2, vIntersection;
	I_LIGHT_MGR.Frame();
	I_LIGHT_MGR.m_cbLight.vEyeDir = { m_pMainCamera->m_Look,30 };
	I_LIGHT_MGR.m_cbLight.vEyePos = { m_pMainCamera->m_Pos,30 };

	m_QuadTree->Frame();
	////////////////////////////////////////


	//////////////char//////////////////////
	if (m_Character == nullptr)return true;
	if (m_GameTime > 3)
	{
		bool bClick = false;
		bool bRun = false;
		float fSpeed = 10;
		float fM = 0;
		D3DXVECTOR3 vN, vLook, vSide, vLookPush, vSidePush, vObjPush;
		vLookPush = D3DXVECTOR3(0, 0, 0);
		vSidePush = D3DXVECTOR3(0, 0, 0);
		vLook = m_pMainCamera->m_LookDir;
		vSide = m_pMainCamera->m_SideDir;

		if (KG_COLLOSION::ChkOBBToOBBAndDirection(m_Character->GetCharBox(), m_Enemy->GetCharBox(), vN, fM))
		{
			float fdot = D3DXVec3Dot(&m_pMainCamera->m_LookDir, &vN);

			if (fdot < 0)
			{
				vLookPush = (2 * D3DXVec3Dot(&-m_pMainCamera->m_LookDir, &vN)) * vN + m_pMainCamera->m_LookDir; //벽밀림
				vSidePush = (2 * D3DXVec3Dot(&-m_pMainCamera->m_SideDir, &vN)) * vN + m_pMainCamera->m_SideDir;
				//vObjPush = (2 * D3DXVec3Dot(&-m_pMainCamera->m_ObjDir, &vN)) * vN + m_pMainCamera->m_SideDir;

				vLook = m_pMainCamera->m_LookDir - vN * (D3DXVec3Dot(&m_pMainCamera->m_LookDir, &vN));
				vSide = m_pMainCamera->m_SideDir - vN * (D3DXVec3Dot(&m_pMainCamera->m_SideDir, &vN));

				m_vMove += vLookPush * fM *g_SecondTime;
			}
			else
			{
				vLookPush = (2 * D3DXVec3Dot(&-m_pMainCamera->m_LookDir, &vN)) * vN + m_pMainCamera->m_LookDir; //벽밀림
				vSidePush = (2 * D3DXVec3Dot(&-m_pMainCamera->m_SideDir, &vN)) * vN + m_pMainCamera->m_SideDir;
				//vObjPush = (2 * D3DXVec3Dot(&-m_pMainCamera->m_ObjDir, &vN)) * vN + m_pMainCamera->m_SideDir;

				vLook = m_pMainCamera->m_LookDir - vN * (D3DXVec3Dot(&m_pMainCamera->m_LookDir, &vN));
				vSide = m_pMainCamera->m_SideDir - vN * (D3DXVec3Dot(&m_pMainCamera->m_SideDir, &vN));

				m_vMove -= vLookPush * fM *g_SecondTime;
			}

		}

		if (I_Input.GetKeyCheck(VK_SHIFT))
		{
			m_Character->SetState(CBY::CHAR_RUN);
			bClick = true;
			bRun = true;
			fSpeed += 10;
		}

		if (I_Input.GetKeyCheck('W'))
		{
			if (!bRun && !m_bFire)
			{
				m_Character->SetState(CBY::CHAR_MOVE);
			}
			m_vMove += vLook * fSpeed * g_SecondTime;

			bClick = true;
		}
		if (I_Input.GetKeyCheck('S'))
		{
			if (!bRun && !m_bFire)
			{
				m_Character->SetState(CBY::CHAR_MOVE);
			}
			m_vMove -= vLook * fSpeed * g_SecondTime;
			bClick = true;
		}
		if (I_Input.GetKeyCheck('A'))
		{
			if (!bRun && !m_bFire)
			{
				m_Character->SetState(CBY::CHAR_MOVE);
			}
			m_vMove += vSide * fSpeed * g_SecondTime;
			bClick = true;
		}
		if (I_Input.GetKeyCheck('D'))
		{
			if (!bRun && !m_bFire)
			{
				m_Character->SetState(CBY::CHAR_MOVE);
			}
			m_vMove -= vSide * fSpeed * g_SecondTime;
		}

		if (I_Input.GetKeyCheck(VK_SPACE))
		{
			m_Character->SetState(CBY::CHAR_JUMP);
			bClick = true;
		}

		if (!bClick && !m_bFire)
		{
			m_Character->SetState(CBY::CHAR_IDLE);
		}

		m_vMove.y = m_Map->GetHeight(m_vMove.x, m_vMove.z);

		m_Character->Frame();
		D3DXMATRIX zpos;
		D3DXMatrixIdentity(&zpos);
		zpos._42 = 20;
		zpos._43 = -30;
		D3DXMATRIX charmat = m_Character->m_pMatrixList[46] * zpos * m_Character->m_matWorld;
		D3DXVECTOR3 bonepos = D3DXVECTOR3(charmat._41, charmat._42, charmat._43);
		m_pMainCamera->m_Pos = bonepos;

		m_Enemy->Frame();
	}
	else
	{
		m_GameTime += g_SecondTime;
	}

	/////////////////////////////////////////////
	return true;
}

bool KG_TestMain::Render()
{
	CDX::ApplyBS(m_pContext, CDX::KG_DxState::g_pAlpahBlend);
	CDX::ApplySS(m_pContext, CDX::KG_DxState::g_pSampler, 0);
	CDX::ApplySS(m_pContext, CDX::KG_DxState::g_pSSClampLinear, 1);

	/////////////////////Map////////////////////
	ID3D11ShaderResourceView* ppSRVNULL[1] = { NULL };
	ID3D11UnorderedAccessView* ppUAViewNULL[1] = { NULL };
	ID3D11Buffer* ppCBNULL[1] = { NULL };

	if (m_Map == nullptr)return true;
	else
	{
		m_Map->SetMatrix(nullptr, &m_pMainCamera->m_View, &m_pMainCamera->m_Proj);
		ID3D11Buffer*               pBuffers[3];
		pBuffers[0] = I_LIGHT_MGR.m_pLightConstantBuffer[0].Get();
		LightConstantBuffer mcb = I_LIGHT_MGR.m_cbLight;
		m_Map->UpdateConstantBuffer(I_LIGHT_MGR.m_pLightConstantBuffer[0].Get(), &I_LIGHT_MGR.m_cbLight);
		m_Map->m_obj.m_pContext->PSSetConstantBuffers(1, 1, pBuffers);
		m_Map->m_obj.m_pContext->PSSetConstantBuffers(1, 1, pBuffers);

		UINT offset = 0;
		UINT stride = sizeof(D3DXVECTOR3);
		if (!m_Map->m_pNormMapFileName)
		{
			m_Map->m_obj.m_pContext->PSSetShaderResources(1, 1, &m_Map->m_pTexture->m_pTextureRV);
			m_Map->m_obj.m_pContext->IASetVertexBuffers(1, 1, &m_Map->m_pTangentVB, &stride, &offset);
		}

		m_QuadTree->Render();
		m_pContext->PSSetShaderResources(2, 1, ppSRVNULL);
	}
	////////////////////////////////////////////

	///////////////////Char//////////////////////
	m_pMainCamera->m_At;
	D3DXMATRIX scale;
	D3DXMatrixScaling(&scale, 0.025, 0.025, 0.025);
	scale._41 = 30;
	//scale._42 = m_vMove.y;
	scale._43 = 20;
	m_Enemy->SetMatrix(&scale, &m_pMainCamera->m_View, &m_pMainCamera->m_Proj);
	m_Enemy->Render();

	scale._41 = m_vMove.x;
	scale._42 = m_vMove.y;
	scale._43 = m_vMove.z;
	m_Character->SetMatrix(&(m_pMainCamera->m_World*scale), &m_pMainCamera->m_View, &m_pMainCamera->m_Proj);
	m_Character->Render();
	/////////////////////////////////////////////
	return true;
}

bool KG_TestMain::Release()
{
	m_Character->Release();
	m_CharCamera->Release();
	return true;
}

bool KG_TestMain::CreateMap(int iWidth,
	int iHeight,
	int iCellCount,
	int iCellSize,
	const TCHAR* pTexturFileName,
	const TCHAR* pNormalMapFileName)
{


	if (m_Map != nullptr)
	{
		m_Map->Release();
		m_QuadTree->Release();

	}


	m_Map = make_shared<JH_Map>();
	if (m_sMapData.m_fHegihtList.size() > 0)
	{
		std::copy(m_sMapData.m_fHegihtList.begin(),
			m_sMapData.m_fHegihtList.end(),
			back_inserter(m_Map->m_vHeightList));
	}
	if (false)
	{
		m_Map->CreateHeightMap(m_pd3dDevice, m_pContext, L"../../data/map/heightMap513.bmp");
	}
	else
	{
		m_Map->m_iCellCount = iCellCount;
		m_Map->m_iRowNum = iCellCount * iWidth + 1;
		m_Map->m_iColumNum = iCellCount * iHeight + 1;
	}

	//	CreateSplattingTexture();
	//CreateCSTexture();


	m_Map->SetMapDesc(pTexturFileName, L"../../data/Shader/JHMapShader.txt", m_Map->m_iRowNum, m_Map->m_iColumNum, iCellSize, 1.0f);


	m_Map->m_pNormMapFileName = pNormalMapFileName;
	m_Map->Load(m_pd3dDevice, m_pContext);

	m_QuadTree = make_shared<HQuadTree>();
	m_QuadTree->Build(m_Map.get(), m_pMainCamera);
	m_QuadTree->m_pSelect = &m_Select;


	return true;
}

TCHAR* KG_TestMain::FixupName(T_STR name)
{
	memset(m_tmpBuffer, 0, sizeof(TCHAR)*MAX_PATH);

	TCHAR* cPtr;
	_tcscpy(m_tmpBuffer, name.c_str());
	cPtr = m_tmpBuffer;

	while (*cPtr)
	{
		if (*cPtr == '"')		*cPtr = SINGLE_QUOTE;
		else if (*cPtr == ' ' || *cPtr <= CTL_CHARS)
			*cPtr = _T('_');
		cPtr++;
	}
	return m_tmpBuffer;
}
bool  KG_TestMain::LoadMapData(const TCHAR* LoadFile)
{
	FILE* fp;
	TCHAR  szFile[256] = { 0, };

	fp = _tfopen(LoadFile, _T("rt"));

	if (fp == nullptr)
	{
		return false;
	}

	//Map Basic Text Data


	TCHAR   Temp[256];
	_fgetts(m_pBuffer, 256, fp);
	_stscanf(m_pBuffer, _T("%s %s\n"), m_pString,
		Temp);

	m_sMapData.m_BaseTextureFile = Temp;
	_fgetts(m_pBuffer, 256, fp);
	_stscanf(m_pBuffer, _T("%s %s\n"), m_pString, Temp);

	m_sMapData.m_NormalMapFile = Temp;
	_fgetts(m_pBuffer, 256, fp);
	_stscanf(m_pBuffer, _T("%s %s\n "), m_pString, Temp);

	m_sMapData.m_ShaderFile = Temp;



	_fgetts(m_pBuffer, 256, fp);
	_stscanf(m_pBuffer, _T("%s %s\n"), m_pString,
		Temp);
	m_sMapData.m_pSplattAlphaTextureFile = Temp;




	//Splatt Texture
	_fgetts(m_pBuffer, 256, fp);
	_stscanf(m_pBuffer, _T("%s %d\n"), m_pString, &m_iTemp);

	m_sMapData.m_pSplattTextureFile.resize(m_iTemp);
	for (int i = 0; i < m_sMapData.m_pSplattTextureFile.size(); i++)
	{

		_fgetts(m_pBuffer, 256, fp);
		_stscanf(m_pBuffer, _T("%d %s"), &m_iTemp, Temp);
		m_sMapData.m_pSplattTextureFile[i] = Temp;
	}
	_fgetts(m_pBuffer, 256, fp);
	_stscanf(m_pBuffer, _T("%s %d %d %d %d\n"), m_pString, &m_sMapData.iRow, &m_sMapData.iCol, &m_sMapData.iCellCount, &m_sMapData.iCellSize);
	// Vertex Height Data
	_fgetts(m_pBuffer, 256, fp);
	_stscanf(m_pBuffer, _T("%s %d\n "), m_pString, &m_iTemp, m_pString);

	_fgetts(m_pBuffer, 256, fp);
	_stscanf(m_pBuffer, _T(" %s\n"), m_pString);

	m_sMapData.m_fHegihtList.resize(m_iTemp);
	int layer = 0;
	for (int iVertex = 0; iVertex < m_iTemp; iVertex++)
	{
		float fh;
		_fgetts(m_pBuffer, 256, fp);
		_stscanf(m_pBuffer, _T("%f "), &fh);

		m_sMapData.m_fHegihtList[iVertex] = fh * 3;

	}

	_fgetts(m_pBuffer, 256, fp);
	_stscanf(m_pBuffer, _T("%s %d \n"), m_pString, &m_iTemp);

	m_sMapData.m_sQTData.m_ObjList.resize(m_iTemp);

	for (int iObj = 0; iObj < m_sMapData.m_sQTData.m_ObjList.size(); iObj++)
	{
		OBJECT OBJ =
			m_sMapData.m_sQTData.m_ObjList[iObj];
		_fgetts(m_pBuffer, 256, fp);
		_stscanf(m_pBuffer, _T("%d \n"), &OBJ.m_iQuadTreeIndex);

		_fgetts(m_pBuffer, 256, fp);
		_stscanf(m_pBuffer, _T("\t%s\n"), m_pString);
		_fgetts(m_pBuffer, 256, fp);
		_stscanf(m_pBuffer, _T("\t%f %f %f %f\n"),
			&OBJ.matWorld._11, &OBJ.matWorld._12, &OBJ.matWorld._13, OBJ.matWorld._14);
		_fgetts(m_pBuffer, 256, fp);
		_stscanf(m_pBuffer, _T("\t%f %f %f %f\n"),
			&OBJ.matWorld._21, &OBJ.matWorld._22, &OBJ.matWorld._23, &OBJ.matWorld._24);
		_fgetts(m_pBuffer, 256, fp);
		_stscanf(m_pBuffer, _T("\t%f %f %f %f\n"),
			&OBJ.matWorld._31, &OBJ.matWorld._32, &OBJ.matWorld._33, &OBJ.matWorld._34);
		_fgetts(m_pBuffer, 256, fp);
		_stscanf(m_pBuffer, _T("\t%f %f %f %f\n"),
			&OBJ.matWorld._41, &OBJ.matWorld._42, &OBJ.matWorld._43, &OBJ.matWorld._44);
	}

	CreateMap(m_sMapData.iRow, m_sMapData.iCol, m_sMapData.iCellCount, m_sMapData.iCellSize,
		m_sMapData.m_BaseTextureFile.c_str(), m_sMapData.m_NormalMapFile.c_str());
	for (int iTex = 0; iTex < m_sMapData.m_pSplattTextureFile.size(); iTex++)
	{
		m_Map->AddSplattTexture(m_sMapData.m_pSplattTextureFile[iTex].data(), iTex + 1);
	}
	HRESULT hr;

	m_Map->m_pCopySrv.Reset();


	hr = D3DX11CreateShaderResourceViewFromFile(m_pd3dDevice,
		(m_sMapData.m_pSplattAlphaTextureFile.data()), NULL, NULL, m_Map->m_pCopySrv.GetAddressOf(), NULL);
	if (FAILED(hr))
	{

	}


	return true;
}

KG_TestMain::KG_TestMain()
{
	D3DXMatrixIdentity(&m_matCharWorld);
	m_vMove = D3DXVECTOR3(0, 0, 0);
	m_vMoveBegin = D3DXVECTOR3(0, 0, 0);
	m_bFire = false;
	m_GameTime = 0;
}


KG_TestMain::~KG_TestMain()
{
}

LRESULT KG_TestMain::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (m_Character != nullptr)
	{
		if (message == WM_LBUTTONDOWN)
		{
			m_Character->SetState(CBY::CHAR_FIRE);
			m_bFire = true;
		}
		
		if(message==WM_LBUTTONUP)
		{
			m_bFire = false;
		}
	}
	return KG_Core::WndProc(hWnd, message, wParam, lParam);
}