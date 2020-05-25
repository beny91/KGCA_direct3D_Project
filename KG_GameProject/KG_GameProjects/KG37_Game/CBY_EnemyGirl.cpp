#include "CBY_EnemyGirl.h"

namespace CBY
{

	bool CBY_EnemyGirl::Create(ID3D11Device* pd3dDevice, ID3D11DeviceContext* Context)
	{
		m_Character = std::make_shared<CBY::CBY_Character>();
		m_Character->CharacterLoad(pd3dDevice, Context, L"../../data/char/save/CharTest.txt");

		//m_Bullet.Create(pd3dDevice, Context, L"../../data/shader/SkinShader.txt", nullptr, "VSSKIN", "PS");
		//m_Bullet.SkinLoad(L"../../data/Char/Ammo/Ammo.skn");
		//m_Bullet.BoneLoad(L"../../data/Char/Ammo/Ammo.mtr");

		//m_Bullet.SetPower(1);
		//m_Bullet.SetSpeed(25.0f);

		m_Character->SetState(0);

		return Init();
	}


	CBY_EnemyGirl::CBY_EnemyGirl()
	{
	}


	CBY_EnemyGirl::~CBY_EnemyGirl()
	{
	}
}

