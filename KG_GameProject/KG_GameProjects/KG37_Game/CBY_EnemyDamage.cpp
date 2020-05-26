#include "CBY_EnemyDamage.h"
#include "CBY_BulletMgr.h"
#include "KG_Collision.h"
#include "MyEffectParser.h"
#include "VFX_ObjMgr.h"

namespace CBY
{
	void CBY_EnemyDamage::Process()
	{
		m_pEnemy->SetState(CHAR_DAMAGE);
		if(m_pEnemy->GetStateAnimationEnd(CHAR_DAMAGE))
		{
			int hp = m_pEnemy->GetHP();
			hp -= 1;
			m_pEnemy->SetHP(hp);

			if (hp <= 0)
			{
				m_pEnemy->SetAction(EVENT_DEATH);
				return;
			}
			m_pEnemy->SetAction(EVENT_RUN);
			return;
		}

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
						m_pEnemy->obj2 = VFX_MGR->find(VFX_EFFECT_GUN1_SHOT);
						D3DXVECTOR3 pos = m_pEnemy->GetColPos(ibox);
						pos += zpos;
						m_pEnemy->obj2->Execute(pos);


						int hp = m_pEnemy->GetHP();
						hp -= 1;
						m_pEnemy->SetHP(hp);
						if (hp <= 0)
						{
							m_pEnemy->SetAction(EVENT_DEATH);
						}
						return;
					}
				}
			}
		}
	}

	CBY_EnemyDamage::CBY_EnemyDamage(CBY_EnemyAi* host) : CBY_EnemyProcess(host)
	{
	}


	CBY_EnemyDamage::~CBY_EnemyDamage()
	{
	}
}
