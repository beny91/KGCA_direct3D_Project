#include "CBY_EnemyAi.h"
#include "CBY_BulletMgr.h"
#include "KG_Collision.h"
#include "MyEffectParser.h"
#include "VFX_ObjMgr.h"

namespace CBY
{
	bool CBY_EnemyAi::Create(ID3D11Device* pd3dDevice, ID3D11DeviceContext* Context)
	{

		return true;
	}

	void CBY_EnemyAi::SetAction(DWORD Event)
	{
		m_dwCharState = CBY_HeroFSM::Get().Output(m_dwCharState, Event);
		m_Action = m_ActionList[m_dwCharState];
	}

	void CBY_EnemyAi::Process()
	{
		m_Action->Process();
		Frame();
	}


	bool CBY_EnemyAi::Init()
	{
		if (m_Character == nullptr)
			return false;

		m_Character->Init();
		D3DXVECTOR3 scale = D3DXVECTOR3(5.0f, 5.0f, 0.0f);
		obj2 = VFX_MGR->find(VFX_EFFECT_GUN_SHOT);
		obj2->setParticleScale(scale);

		/*CBY_HeroFSM::Get().Init();

		m_dwCharState = CHAR_IDLE;

		m_ActionList[CHAR_IDLE] = new CBY_HeroIdle(this);
		m_ActionList[CHAR_MOVE] = new CBY_HeroMove(this);
		m_ActionList[CHAR_JUMP] = new CBY_HeroJump(this);
		m_ActionList[CHAR_RUN] = new CBY_HeroRun(this);
		m_ActionList[CHAR_FIRE] = new CBY_HeroFire(this);
		m_ActionList[CHAR_DAMAGE] = new CBY_HeroDamage(this);
		m_ActionList[CHAR_DEATH] = new CBY_HeroDeath(this);

		m_Action = m_ActionList[CHAR_IDLE];*/

		return true;
	}

	bool CBY_EnemyAi::Frame()
	{
		if (m_Character == nullptr)
			return false;

		m_Character->Frame();

		if (GetStateAnimationEnd(CBY::CHAR_FIRE))
		{
			SetState(CBY::CHAR_IDLE);
		}

		for (int i = 0; i < CBY_CHAR_BULLET.GetBulletNum(); i++)
		{
			KG_Box AmmoBox = CBY_CHAR_BULLET.GetBulletBox(i);

			if (KG_COLLOSION::ChkOBBToOBB(m_Character->GetCharBox(), AmmoBox))
			{
				for (int ibox = 0; ibox < m_Character->GetColBoxSize(); ibox++)
				{
					if (KG_COLLOSION::ChkOBBToOBB(m_Character->GetColBox(ibox), AmmoBox))
					{
						//KG_Box box = m_Character->GetCharBox();
						CBY_CHAR_BULLET.BulletPop(i);
						SetState(CBY::CHAR_FIRE);
						D3DXVECTOR3 zpos = D3DXVECTOR3(0, 0, 0);
						zpos -= m_pCamera->m_LookDir * 2;
						//zpos += box.vAxis[2] * 2;
						obj2 = VFX_MGR->find(VFX_EFFECT_GUN_SHOT);
						D3DXVECTOR3 pos = m_Character->GetColPos(ibox);
						pos += zpos;
						//D3DXVECTOR3 dir = D3DXVECTOR3(5.0f, 0.0f, 0.0f);

						obj2->Execute(pos);
						i--;
						break;
					}
				}
			}
		}
		return true;
	}

	bool CBY_EnemyAi::Render()
	{
		if (m_Character == nullptr)
			return false;

		m_Character->Render();
		return true;
	}

	bool CBY_EnemyAi::Release()
	{
		if (m_Character == nullptr)
			return false;

		m_Character->Release();
		return true;
	}

	CBY_EnemyAi::CBY_EnemyAi()
	{
	}


	CBY_EnemyAi::~CBY_EnemyAi()
	{
	}
}
