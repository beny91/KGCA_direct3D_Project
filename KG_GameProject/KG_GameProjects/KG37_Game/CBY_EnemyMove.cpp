#include "CBY_EnemyMove.h"
#include "CBY_BulletMgr.h"
#include "KG_Collision.h"
#include "MyEffectParser.h"
#include "VFX_ObjMgr.h"

namespace CBY
{
	void CBY_EnemyMove::Process()
	{
		m_pEnemy->SetState(CHAR_MOVE);

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

		D3DXVECTOR3 vmove;
		GetLookDir();
		/*if(SetColDirection())
		{
			m_fDirTime = 3.0f;
			return;
		}*/
		vmove = m_pEnemy->GetHeroPos();
		vmove += m_LookDir * m_pEnemy->GetMoveSpeed() * g_SecondTime;
		m_pEnemy->SetHeroPos(vmove);

		m_fTime += g_SecondTime;
		if (m_fTime > 4.0f)
		{
			m_pEnemy->SetAction(EVENT_IDLE);
			m_fTime = 0.0f;
		}
	}

	CBY_EnemyMove::CBY_EnemyMove(CBY_EnemyAi* host) : CBY_EnemyProcess(host)
	{
	}


	CBY_EnemyMove::~CBY_EnemyMove()
	{
	}
}
