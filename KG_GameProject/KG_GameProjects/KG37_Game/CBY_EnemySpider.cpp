#include "CBY_EnemySpider.h"

namespace CBY
{

	bool CBY_EnemySpider::Create(ID3D11Device* pd3dDevice, ID3D11DeviceContext* Context)
	{
		m_Character = std::make_shared<CBY::CBY_Character>();
		m_Character->CharacterLoad(pd3dDevice, Context, L"../../data/char/save/Mob_0_Test.txt");
		SetEffectVal(4.0f);
		//m_Bullet.Create(pd3dDevice, Context, L"../../data/shader/SkinShader.txt", nullptr, "VSSKIN", "PS");
		//m_Bullet.SkinLoad(L"../../data/Char/Ammo/Ammo.skn");
		//m_Bullet.BoneLoad(L"../../data/Char/Ammo/Ammo.mtr");

		//m_Bullet.SetPower(1);
		//m_Bullet.SetSpeed(25.0f);
		SetHP(5);
		m_Character->SetState(0);

		return Init();
	}


	CBY_EnemySpider::CBY_EnemySpider()
	{
		m_vCharPos = D3DXVECTOR3(30, 0, 20);
	}


	CBY_EnemySpider::~CBY_EnemySpider()
	{
	}
}

