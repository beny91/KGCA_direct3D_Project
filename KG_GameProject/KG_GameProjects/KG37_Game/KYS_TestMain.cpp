#include "KYS_TestMain.h"
#include"KG_DxState.h"
#include"KG_Input.h"
#include"KG_ShapeMap.h"
#include"LightMgr.h"
#include "KG_Input.h"
#include "KG_Collision.h"
#include "MyEffectParser.h"
#include "VFX_ObjMgr.h"
#include "CBY_BulletMgr.h"


bool KYS_TestMain::Init()
{
	CDX::ApplyBS(m_pContext, CDX::KG_DxState::g_pAlpahBlend);
	CDX::ApplySS(m_pContext, CDX::KG_DxState::g_pSampler);
	CDX::ApplyRS(m_pContext, CDX::KG_DxState::g_pRSSold);
	
	///////////////Camera//////////////////////
	m_CharCamera = std::make_shared<CBY::CBY_CharacterCamera>();
	m_CharCamera->SetViewProj();
	m_CharCamera->SetCameraSpeed(30);
	m_pMainCamera = m_CharCamera.get();
	//////////////////////////////////////////


	//////////////Map/////////////////////////
	LoadMapData(L"../../data/MapSave/aa.Map");
	//LoadMapData(L"../../data/MapSave/SampleRust.Map");
	//LoadMapData(L"../../data/MapSave/SampleRubber.Map");

	//ComPuteShader
	(CDXH::CreateComputeShader(L"../../data/shader/ComputeAlpha.HLSL", "CSMAIN", m_pd3dDevice, m_pCS.GetAddressOf()));
	//////////////////////////////////////////

	//effect
	EFFECT_PARSER->createEffectDataFromFile(L"../../data/effectData/LoadEffectDataList.txt", m_pd3dDevice, m_pContext);
	VFX_MGR->setDevice(m_pd3dDevice);
	VFX_MGR->setContext(m_pContext);

	D3DXVECTOR3 scale = D3DXVECTOR3(5.0f, 5.0f, 0.0f);
	std::shared_ptr<KYS::VFX_EffectObj>obj;
	obj = VFX_MGR->find(VFX_EFFECT_GUN_SHOT);
	obj->setParticleScale(scale);

	obj1 = VFX_MGR->find(VFX_EFFECT_GUN_SHOT);
	obj1->setParticleScale(scale);

	////////////////Char////////////////////	
	CBY::CBY_CHAR_BULLET.Init();
	m_Character = std::make_shared<CBY::CBY_HeroGirl>();
	m_Character->Create(m_pd3dDevice, m_pContext);
	m_Character->SetFireTime(0.5f);

	m_Enemy = std::make_shared<CBY::CBY_EnemyGirl>();
	m_Enemy->Create(m_pd3dDevice, m_pContext);
	m_Enemy->SetCamera(m_pMainCamera);

	m_Character->SetEnemy(m_Enemy.get());
	m_Character->SetCamera(m_pMainCamera);
	//////////////////////////////////////////

	return true;
}

bool KYS_TestMain::Frame()
{
	//////////////////Map/////////////////
	if (m_Map == nullptr)return true;

	//test/adsfadsf
	m_Select.SetMarix(nullptr, &m_pMainCamera->m_View, &m_pMainCamera->m_Proj);

	D3DXVECTOR3 v0, v1, v2, vIntersection;
	JH::I_LIGHT_MGR.Frame();
	JH::I_LIGHT_MGR.m_cbLight.vEyeDir = { m_pMainCamera->m_Look,30 };
	JH::I_LIGHT_MGR.m_cbLight.vEyePos = { m_pMainCamera->m_Pos,30 };

	m_QuadTree->Frame();
	////////////////////////////////////////


	//////////////char//////////////////////
	if (m_Character == nullptr)return true;
	if (m_GameTime > 3)
	{
		D3DXVECTOR3 pos = m_Character->GetHeroPos();
		pos.y = m_Map->GetHeight(pos.x, pos.z);
		m_Character->SetHeroPos(pos);

		m_Character->Process();
		
		m_pMainCamera->m_Pos = m_Character->GetCamerPos();

		m_Enemy->Frame();
	}
	else
	{
		m_GameTime += g_SecondTime;
	}

	/////////////////////////////////////////////

	//effect
	VFX_MGR->Frame();

	D3DXMATRIX matViewInverse, matWorld;
	matViewInverse = m_pMainCamera->m_View;
	D3DXMatrixInverse(&matViewInverse, NULL, &matViewInverse);

	m_matBillBoard = matViewInverse;

	/////////////ammo////
	D3DXMATRIX scale;
	D3DXMatrixScaling(&scale, 0.2, 0.2, 0.2);
	//D3DXMatrixScaling(&scale, 1, 1, 1);
	CBY::CBY_CHAR_BULLET.SetMatrix(&scale, &m_pMainCamera->m_View, &m_pMainCamera->m_Proj);
	CBY::CBY_CHAR_BULLET.Frame();

	return true;
}

bool KYS_TestMain::Render()
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
		pBuffers[0] = JH::I_LIGHT_MGR.m_pLightConstantBuffer[0].Get();
		JH::LightConstantBuffer mcb = JH::I_LIGHT_MGR.m_cbLight;
		m_Map->UpdateConstantBuffer(JH::I_LIGHT_MGR.m_pLightConstantBuffer[0].Get(), &JH::I_LIGHT_MGR.m_cbLight);
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
	D3DXMATRIX scale;
	D3DXMatrixScaling(&scale, 0.025, 0.025, 0.025);
	scale._41 = 30;
	scale._42 = m_Map->GetHeight(30, 20);
	scale._43 = 20;
	m_Enemy->SetMatrix(&scale, &m_pMainCamera->m_View, &m_pMainCamera->m_Proj);
	m_Enemy->Render();
	
	m_vMove = m_Character->GetHeroPos();
	D3DXMatrixScaling(&scale, 0.025, 0.025, 0.025);
	scale._41 = m_vMove.x;
	scale._42 = m_vMove.y;
	scale._43 = m_vMove.z;
	//m_matBillBoard._41 = m_vMove.x;
	//m_matBillBoard._42 = m_vMove.y;
//	m_matBillBoard._43 = m_vMove.z;
	//m_Character-._42>SetMatrix(&(m_pMainCamera->m_World*scale), &m_pMainCamera->m_View, &m_pMainCamera->m_Proj);
	m_Character->SetMatrix(&(m_pMainCamera->m_World*scale), &m_pMainCamera->m_View, &m_pMainCamera->m_Proj);
	m_Character->Render();
	/////////////////////////////////////////////

	//effect
	VFX_MGR->Render(m_pMainCamera);

	CBY::CBY_CHAR_BULLET.Render();
	return true;
}

bool KYS_TestMain::Release()
{
	m_Character->Release();
	m_Enemy->Release();
	m_CharCamera->Release();
	CBY::CBY_CHAR_BULLET.Release();
	return true;
}

TCHAR* KYS_TestMain::FixupName(T_STR name)
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
bool  KYS_TestMain::LoadMapData(const TCHAR* LoadFile)
{
	FILE* fp;
	TCHAR  szFile[256] = { 0, };

	fp = _tfopen(LoadFile, _T("rt"));

	if (fp == nullptr)
	{
		return false;
	}

	//Map Basic Text Data
	m_sMapData.Reset();

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
	if (Temp == m_sMapData.m_NormalMapFile)
	{
		//m_sMapData.m_HeightMapFile;
	}
	else
	{
		m_sMapData.m_HeightMapFile = Temp;
	}

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
	_stscanf(m_pBuffer, _T("%s %d\n "), m_pString, &m_iTemp);

	_fgetts(m_pBuffer, 256, fp);
	_stscanf(m_pBuffer, _T(" %s\n"), m_pString);

	m_sMapData.m_fHegihtList.resize(m_iTemp);
	int layer = 0;
	for (int iVertex = 0; iVertex < m_iTemp; iVertex++)
	{

		_fgetts(m_pBuffer, 256, fp);
		_stscanf(m_pBuffer, _T("%f "), &m_sMapData.m_fHegihtList[iVertex]);


	}

	_fgetts(m_pBuffer, 256, fp);
	_stscanf(m_pBuffer, _T("%s %d \n"), m_pString, &m_iTemp);

	m_sMapData.m_sQTData.m_ObjList.resize(m_iTemp);

	for (int iObj = 0; iObj < m_sMapData.m_sQTData.m_ObjList.size(); iObj++)
	{
		JH::OBJECT &OBJ =
			m_sMapData.m_sQTData.m_ObjList[iObj];
		_fgetts(m_pBuffer, 256, fp);
		_stscanf(m_pBuffer, _T("%d \n"), &OBJ.m_iQuadTreeIndex);

		_fgetts(m_pBuffer, 256, fp);
		_stscanf(m_pBuffer, _T("%s \n"), m_pString);
		OBJ.m_FileName = m_pString;

		_fgetts(m_pBuffer, 256, fp);
		_stscanf(m_pBuffer, _T("\t%s\n"), m_pString);
		_fgetts(m_pBuffer, 256, fp);
		_stscanf(m_pBuffer, _T("\t%f %f %f %f\n"),
			&OBJ.matWorld._11, &OBJ.matWorld._12, &OBJ.matWorld._13, &OBJ.matWorld._14);
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
		m_sMapData.m_BaseTextureFile.c_str(), m_sMapData.m_NormalMapFile.c_str(), m_sMapData.m_HeightMapFile.c_str());
	for (int iTex = 0; iTex < m_sMapData.m_pSplattTextureFile.size(); iTex++)
	{
		m_Map->AddSplattTexture(m_sMapData.m_pSplattTextureFile[iTex].data(), iTex + 1);
	}
	HRESULT hr;

	m_Map->m_pCopySrv.Reset();


	hr = D3DX11CreateShaderResourceViewFromFile(m_pd3dDevice,
		(m_sMapData.m_pSplattAlphaTextureFile.data()), NULL, NULL, m_Map->m_pCopySrv.GetAddressOf(), NULL);

	//m_ObjectList.clear();

	//for (int i = 0; i < m_sMapData.m_sQTData.m_ObjList.size(); i++)
	//{
	//	OBJECT& obj = m_sMapData.m_sQTData.m_ObjList[i];
	//	AddObject(obj);
	//}

	return true;
}
bool KYS_TestMain::CreateMap(int iWidth,
	int iHeight,
	int iCellCount,
	int iCellSize,
	const TCHAR* pTexturFileName,
	const TCHAR* pNormalMapFileName,
	const TCHAR* pHeightMapFileName)
{


	if (m_Map != nullptr)
	{
		m_Map->Release();
		m_QuadTree->Release();

	}


	m_Map = std::make_shared<JH::JH_Map>();
	T_STR strnull;
	if (pHeightMapFileName!= strnull)
	{
		m_Map->CreateHeightMap(m_pd3dDevice, m_pContext, pHeightMapFileName);
	}
	else
	{
		m_Map->m_iCellCount = iCellCount;
		m_Map->m_iRowNum = iCellCount * iWidth + 1;
		m_Map->m_iColumNum = iCellCount * iHeight + 1;
	}
	if (m_sMapData.m_fHegihtList.size() > 0)
	{
		std::copy(m_sMapData.m_fHegihtList.begin(),
			m_sMapData.m_fHegihtList.end(),
			back_inserter(m_Map->m_vHeightList));
	}
	m_Map->SetMapDesc(pTexturFileName, L"../../data/Shader/JHMapShader.txt", m_Map->m_iRowNum, m_Map->m_iColumNum, iCellSize, 1.0f);


	m_Map->m_pNormMapFileName = pNormalMapFileName;
	m_Map->m_HegithFileName = pHeightMapFileName;
	m_Map->Load(m_pd3dDevice, m_pContext);

	m_QuadTree = std::make_shared<JH::HQuadTree>();
	m_QuadTree->Build(m_Map.get(), m_pMainCamera);
	m_QuadTree->m_pSelect = &m_Select;


	return true;
}

KYS_TestMain::KYS_TestMain()
{
	D3DXMatrixIdentity(&m_matCharWorld);
	m_vMove = D3DXVECTOR3(0, 0, 0);
	m_vMoveAfter = D3DXVECTOR3(0, 0, 0);
	m_bFire = false;
	m_GameTime = 0;
	m_fFireTime = 0;
}


KYS_TestMain::~KYS_TestMain()
{
}

LRESULT KYS_TestMain::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (m_Character != nullptr)
	{
		if (message == WM_LBUTTONDOWN)
		{
			m_bFire = true;
		}

		if (message == WM_LBUTTONUP)
		{
			m_bFire = false;
		}
	}
	return KG_Core::WndProc(hWnd, message, wParam, lParam);
}