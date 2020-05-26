#pragma once

#pragma once
#include "KG_GameStd.h"
//enemy///
#include "CBY_EnemyGirl.h"
#include "CBY_EnemySpider.h"
////////////

/////char////
#include "CBY_HeroGirl.h"
#include "CBY_CharacterCamera.h"
////////////
#include "KG_Point.h"

#include"QuadTree.h"
#include"KG_ShapeBox.h"
#include"KG_Minimap.h"
#include"KG_BackViewCamera.h"
#include"KG_DebugCamera.h"
//#include"MaxObj.h"
#include"KG_SkyBox.h"
#include "JH_MapMgr.h"

#define CTL_CHARS		31
#define SINGLE_QUOTE	39 // ( ' )
#define ALMOST_ZERO 1.0e-4f

namespace KYS
{
	class VFX_EffectObj;
}

class KYS_TestMain :public KG_Core
{
	/////char//////////
public:
	std::shared_ptr<CBY::CBY_HeroGirl> m_Character;
	std::vector<std::shared_ptr<CBY::CBY_EnemySpider>> m_EnemyList;
	std::shared_ptr<CBY::CBY_EnemySpider> m_Enemy;
	std::shared_ptr<CBY::CBY_CharacterCamera> m_CharCamera;
	std::shared_ptr<KG_Point> m_Point;
	D3DXMATRIX m_matCharWorld;
	D3DXVECTOR3 m_vMove;
	D3DXVECTOR3 m_vMoveAfter;
	bool m_bFire;
	float m_GameTime;
	D3DXMATRIX m_matBillBoard;
	float m_fFireTime;

	//effect/////
public:
	std::shared_ptr<KYS::VFX_EffectObj> obj1;
	//////////////
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
	std::shared_ptr<JH::KG_SkyBox>			m_SkyBox;
	ComPtr<ID3D11ComputeShader>			m_pCS;

public:
	JH::MAPDATA m_sMapData;
public:
	std::shared_ptr<JH::JH_Map>		m_Map;
	std::shared_ptr<JH::HQuadTree>	m_QuadTree;
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
		const TCHAR* pNormalMapFileName = nullptr,
		const TCHAR* pHeightMapFileName = nullptr);
	TCHAR* FixupName(T_STR name);
	//Load
	bool   LoadMapData(const TCHAR* LoadFile);
public:
	KYS_TestMain();
	virtual ~KYS_TestMain();
};

KGCA37_RUN(KYS_TestMain, KGCA_37_Game, KGCA_37_Game)


