#include "JH_MapMgr.h"


namespace JH
{
	JH_MapMgr::JH_MapMgr()
	{
	}


	JH_MapMgr::~JH_MapMgr()
	{
	}
	void JH_MapMgr::Set(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, KG_Camera* pCamera, KG_Select& select)
	{
		m_pd3dDevice = pDevice;
		m_pContext = pContext;
		m_pCamera = pCamera;
		m_Select = select;
	}
	INT	JH_MapMgr::AddMap(const TCHAR* LoadFile)
	{
		FILE* fp;
		TCHAR  szFile[256] = { 0, };

		fp = _tfopen(LoadFile, _T("rt"));

		if (fp == nullptr)
		{
			return false;
		}
		JH::MAPDATA MapData;
		//Map Basic Text Data

		GAME_MAP GMData;
		GMData.m_pMap = std::make_shared<JH_Map>();
		GMData.m_pQuadTree = std::make_shared<JH::HQuadTree>();
		TCHAR   Temp[256];
		_fgetts(m_pBuffer, 256, fp);
		_stscanf(m_pBuffer, _T("%s %s\n"), m_pString,
			Temp);

		MapData.m_BaseTextureFile = Temp;
		_fgetts(m_pBuffer, 256, fp);
		_stscanf(m_pBuffer, _T("%s %s\n"), m_pString, Temp);

		MapData.m_NormalMapFile = Temp;
		_fgetts(m_pBuffer, 256, fp);
		_stscanf(m_pBuffer, _T("%s %s\n "), m_pString, Temp);

		MapData.m_ShaderFile = Temp;



		_fgetts(m_pBuffer, 256, fp);
		_stscanf(m_pBuffer, _T("%s %s\n"), m_pString,
			Temp);
		MapData.m_pSplattAlphaTextureFile = Temp;




		//Splatt Texture
		_fgetts(m_pBuffer, 256, fp);
		_stscanf(m_pBuffer, _T("%s %d\n"), m_pString, &m_iTemp);

		MapData.m_pSplattTextureFile.resize(m_iTemp);
		for (int i = 0; i < MapData.m_pSplattTextureFile.size(); i++)
		{

			_fgetts(m_pBuffer, 256, fp);
			_stscanf(m_pBuffer, _T("%d %s"), &m_iTemp, Temp);
			MapData.m_pSplattTextureFile[i] = Temp;
		}
		_fgetts(m_pBuffer, 256, fp);
		_stscanf(m_pBuffer, _T("%s %d %d %d %d\n"), m_pString, &MapData.iRow, &MapData.iCol, &MapData.iCellCount, &MapData.iCellSize);
		// Vertex Height Data
		_fgetts(m_pBuffer, 256, fp);
		_stscanf(m_pBuffer, _T("%s %d\n "), m_pString, &m_iTemp, m_pString);

		_fgetts(m_pBuffer, 256, fp);
		_stscanf(m_pBuffer, _T(" %s\n"), m_pString);

		MapData.m_fHegihtList.resize(m_iTemp);
		int layer = 0;
		for (int iVertex = 0; iVertex < m_iTemp; iVertex++)
		{

			_fgetts(m_pBuffer, 256, fp);
			_stscanf(m_pBuffer, _T("%f "), &MapData.m_fHegihtList[iVertex]);


		}

		_fgetts(m_pBuffer, 256, fp);
		_stscanf(m_pBuffer, _T("%s %d \n"), m_pString, &m_iTemp);

		MapData.m_sQTData.m_ObjList.resize(m_iTemp);

		for (int iObj = 0; iObj < MapData.m_sQTData.m_ObjList.size(); iObj++)
		{
			JH::OBJECT OBJ =
				MapData.m_sQTData.m_ObjList[iObj];
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

		CreateMap(GMData.m_pMap.get(), GMData.m_pQuadTree.get(), MapData.iRow, MapData.iCol, MapData.iCellCount, MapData.iCellSize,
			MapData.m_BaseTextureFile.c_str(), MapData.m_NormalMapFile.c_str());
		for (int iTex = 0; iTex < MapData.m_pSplattTextureFile.size(); iTex++)
		{
			GMData.m_pMap->AddSplattTexture(MapData.m_pSplattTextureFile[iTex].data(), iTex + 1);
		}
		HRESULT hr;

		GMData.m_pMap->m_pCopySrv.Reset();


		hr = D3DX11CreateShaderResourceViewFromFile(m_pd3dDevice,
			(MapData.m_pSplattAlphaTextureFile.data()), NULL, NULL, GMData.m_pMap->m_pCopySrv.GetAddressOf(), NULL);
		if (FAILED(hr))
		{

		}
		for (int i = 0; i < MapData.m_sQTData.m_ObjList.size(); i++)
		{
			AddObject(MapData.m_sQTData.m_ObjList[i]);
		}

	}
	//오브젝트 바운딩 박스 추가해야함
	INT JH_MapMgr::AddObject(JH::OBJECT Obj)
	{
		/*static int ID;
		shared_ptr<CBY::CBY_Object> Object;
		Object = make_shared<CBY::CBY_Object>();
		Object->Create(m_pd3dDevice, m_pContext, L"../../data/shader/ObjectShader.txt", nullptr, "VSOBJECT", "PS");
		Object->ObjLoad(Obj.m_FileName);

		Object->m_matWorld = Obj.matWorld;
		JH_MapObj MapObj;
		MapObj.SetID(ID);
		MapObj.SetName(Object->m_Obj->m_szname.data());
		MapObj.SetQuadIndex(Obj.m_iQuadTreeIndex);
		m_CurrentMap.m_pQuadTree->FindObjectNode(m_CurrentMap.m_pQuadTree->m_pRootNode, MapObj);
		m_CurrentMap.m_pQuadTree->m_pFindNode->m_ObjList.insert(make_pair(MapObj.GetID(),MapObj));
		m_CurrentMap.m_ObjectList.insert(make_pair(MapObj.GetID(),Object));*/
		return 1;

	}

	bool JH_MapMgr::CreateMap(JH_Map* pMap, JH::HQuadTree* pQuad, int iWidth,
		int iHeight,
		int iCellCount,
		int iCellSize,
		const TCHAR* pTexturFileName,
		const TCHAR* pNormalMapFileName)
	{


		if (pMap != nullptr)
		{
			pMap->Release();
			pQuad->Release();

		}



		pMap->m_iCellCount = iCellCount;
		pMap->m_iRowNum = iCellCount * iWidth + 1;
		pMap->m_iColumNum = iCellCount * iHeight + 1;


		//	CreateSplattingTexture();

		pMap->SetMapDesc(pTexturFileName, L"../../data/Shader/JHMapShader.txt", pMap->m_iRowNum, pMap->m_iColumNum, iCellSize, 1.0f);


		pMap->m_pNormMapFileName = pNormalMapFileName;
		pMap->Load(m_pd3dDevice, m_pContext);


		pQuad->Build(pMap, m_pCamera);
		pQuad->m_pSelect = &m_Select;


		return true;
	}
	bool JH_MapMgr::Release()
	{
		return true;
	}
}