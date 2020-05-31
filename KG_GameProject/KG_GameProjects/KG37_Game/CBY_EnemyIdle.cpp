#include "CBY_EnemyIdle.h"
#include "CBY_BulletMgr.h"
#include "KG_Collision.h"
#include "MyEffectParser.h"
#include "VFX_ObjMgr.h"

namespace CBY
{
	void CBY_EnemyIdle::Process()
	{
		m_pEnemy->SetState(CHAR_IDLE);
	
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
						m_pEnemy->obj2 = VFX_MGR->find(VFX_EFFECT_TYPE::VFX_EFFECT_GUN1_SHOT);
						D3DXVECTOR3 pos = m_pEnemy->GetColPos(ibox);
						pos += zpos;
						m_pEnemy->obj2->Execute(pos);
						
						m_pEnemy->SetAction(EVENT_DAMAGE);
						return;
					}
				}
			}
		}

		/*if (SetColDirection())
		{
			return;
		}*/

		if (m_fTime > 2.0f)
		{
			srand(time(NULL));
			int iCase = rand() % 5;
			
			if (iCase < 4)
			{
				m_pEnemy->SetAction(EVENT_MOVE);
			}
			else
			{
				m_pEnemy->SetAction(EVENT_JUMP);
			}
			m_fTime = 0.0f;
		}
		else
		{
			m_fTime += g_SecondTime;
		}
	}

	CBY_EnemyIdle::CBY_EnemyIdle(CBY_EnemyAi* host) : CBY_EnemyProcess(host)
	{
	}


	CBY_EnemyIdle::~CBY_EnemyIdle()
	{
	}
}
