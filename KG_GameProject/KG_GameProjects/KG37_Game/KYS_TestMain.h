#pragma once

#pragma once
#include "KG_GameStd.h"
#include "CBY_Character.h"
#include "CBY_CharacterCamera.h"
#include "KG_Point.h"

#include"QuadTree.h"
#include"KG_ShapeBox.h"
#include"KG_Minimap.h"
#include"KG_BackViewCamera.h"
#include"KG_DebugCamera.h"
//#include"MaxObj.h"
#include"KG_SkyBox.h"

#define CTL_CHARS		31
#define SINGLE_QUOTE	39 // ( ' )
#define ALMOST_ZERO 1.0e-4f

struct OBJECT
{
	D3DXMATRIX		matWorld;
	int				m_iQuadTreeIndex;
	OBJECT()
	{
		D3DXMatrixIdentity(&matWorld);
	}
};
struct QuadTreeData
{

	vector<OBJECT> m_ObjList;
	QuadTreeData()
	{

	}
};

struct MAPDATA
{
	int iCol;
	int iRow;
	int iCellCount;
	int iCellSize;
	T_STR m_BaseTextureFile;
	T_STR m_NormalMapFile;
	T_STR m_ShaderFile;

	T_STR				m_pSplattAlphaTextureFile;
	vector<float>		m_fHegihtList;
	vector<T_STR>		m_pSplattTextureFile;

	QuadTreeData		m_sQTData;
	void Reset()
	{
		m_BaseTextureFile.clear();
		m_NormalMapFile.clear();
		m_ShaderFile.clear();
		m_pSplattAlphaTextureFile.clear();
		m_fHegihtList.clear();
		m_pSplattTextureFile.clear();
	}


};

namespace KYS
{
	class VFX_EffectObj;
}


class KYS_TestMain :public KG_Core
{
	/////char//////////
public:
	std::shared_ptr<CBY::CBY_Character> m_Character;
	std::shared_ptr<CBY::CBY_Character> m_Enemy;
	std::shared_ptr<CBY::CBY_CharacterCamera> m_CharCamera;
	std::shared_ptr<KG_Point> m_Point;
	D3DXMATRIX m_matCharWorld;
	D3DXVECTOR3 m_vMove;
	D3DXVECTOR3 m_vMoveBegin;
	bool m_bFire;
	float m_GameTime;


	std::shared_ptr<KYS::VFX_EffectObj> obj1;
	std::shared_ptr<KYS::VFX_EffectObj> obj2;

public:
	LRESULT WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;
	///////////////////

public:
	virtual bool Init() override;
	virtual bool Frame() override;
	virtual bool Render() override;
	virtual bool Release() override;

	/////////Map////////
public:
	shared_ptr<KG_SkyBox>			m_SkyBox;
	ComPtr<ID3D11ComputeShader>			m_pCS;

public:
	MAPDATA m_sMapData;
public:
	shared_ptr<JH_Map>		m_Map;
	shared_ptr<HQuadTree>	m_QuadTree;
	TCHAR		m_tmpBuffer[MAX_PATH];
public:
	//Load
	int					m_iTemp;
	TCHAR				m_pBuffer[256];
	TCHAR				m_pString[256];
	//Save
	const TCHAR*		m_pSPTAFile;
public:
	bool CreateMap(int iWidth,
		int iHeight,
		int iCellCount,
		int iCellSize,
		const TCHAR* pTexturFileName,
		const TCHAR* pNormalMapFileName = nullptr);
	TCHAR* FixupName(T_STR name);
	bool   LoadMapData(const TCHAR* LoadFile);
	///////////////////////////////
public:
	KYS_TestMain();
	virtual ~KYS_TestMain();
};

KGCA37_RUN(KYS_TestMain, KGCA_37_Game, KGCA_37_Game)


