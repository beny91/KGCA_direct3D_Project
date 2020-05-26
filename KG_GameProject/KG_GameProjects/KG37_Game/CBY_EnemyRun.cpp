#include "CBY_EnemyRun.h"
#include "CBY_BulletMgr.h"
#include "KG_Collision.h"
#include "MyEffectParser.h"
#include "VFX_ObjMgr.h"
#include "CBY_Hero.h"

namespace CBY
{
	void CBY_EnemyRun::Process()
	{
		m_pEnemy->SetState(CHAR_RUN);

		for (int i = 0; i < CBY_CHAR_BULLET.GetBulletNum(); i++)
		{
			KG_Box AmmoBox = CBY_CHAR_BULLET.GetBulletBox(i);

			if (KG_COLLOSION::ChkOBBToOBB(m_pEnemy->GetCharBox(), AmmoBox))
			{
				for (int ibox = 0; ibox < m_pEnemy->GetColBoxSize(); ibox++)
				{
					if (KG_COLLOSION::ChkOBBToOBB(m_pEnemy->GetColBox(ibox), AmmoBox))
					{
						CBY_CHAR_BULLET.BulletPop(i);
						D3DXVECTOR3 zpos = D3DXVECTOR3(0, 0, 0);
						zpos -= m_pEnemy->GetCamera()->m_LookDir * m_pEnemy->GetEffectVal();
						m_pEnemy->obj2 = VFX_MGR->find(VFX_EFFECT_GUN_SHOT);
						D3DXVECTOR3 pos = m_pEnemy->GetColPos(ibox);
						pos += zpos;
						m_pEnemy->obj2->Execute(pos);

						m_pEnemy->SetAction(EVENT_DAMAGE);
						return;
					}
				}
			}
		}

		D3DXVECTOR3 vmove, vpos;
		D3DXMATRIX matlook;
		vpos = m_pEnemy->GetHero()->GetHeroPos() - m_pEnemy->GetHeroPos();
		D3DXVec3Normalize(&m_LookDir, &vpos);

		D3DXMatrixLookAtLH(&matlook, &m_pEnemy->GetHero()->GetHeroPos(), &m_pEnemy->GetHeroPos(), &D3DXVECTOR3(0, 1, 0));
		//m_LookDir = -(m_pEnemy->GetCamera()->m_LookDir);
		//m_SideDir = -(m_pEnemy->GetCamera()->m_SideDir);
		matlook._41 = 0;
		matlook._42 = 0;
		matlook._43 = 0;
		if (SetColDirection())
		{
			m_pEnemy->SetAction(EVENT_ATTACK);
			return;
		}

		vmove = m_pEnemy->GetHeroPos();
		vmove += m_LookDir * (m_pEnemy->GetMoveSpeed()+5) * g_SecondTime;


		m_pEnemy->SetYaw(m_fYawy);
		m_pEnemy->SetLookDir(m_LookDir);
		m_pEnemy->SetHeroPos(vmove);

		D3DXMatrixInverse(&matlook, NULL, &matlook);
		m_pEnemy->SetLookWorldMatrix(matlook);

	}

	CBY_EnemyRun::CBY_EnemyRun(CBY_EnemyAi* host) : CBY_EnemyProcess(host)
	{
		m_fYawy = 0.0;
	}


	CBY_EnemyRun::~CBY_EnemyRun()
	{
	}
}
