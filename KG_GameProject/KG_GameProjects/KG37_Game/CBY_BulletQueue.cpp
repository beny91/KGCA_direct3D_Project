#include "CBY_BulletQueue.h"


namespace CBY
{
	void CBY_BulletQueue::Push(CBY_Bullet* pobj)
	{
		m_List.push(pobj);
	}

	CBY_Bullet* CBY_BulletQueue::Pop()
	{
		CBY_Bullet* pobj = nullptr;
		if (m_List.empty() == false)
		{
			pobj = m_List.front();
			m_List.pop();
		}

		return pobj;
	}

	void CBY_BulletQueue::Release()
	{
		CBY_Bullet* pobj = nullptr;
		while (m_List.size() > 0)
		{
			pobj = m_List.front();
			delete pobj;
			m_List.pop();
		}
	}

	CBY_BulletQueue::CBY_BulletQueue()
	{
	}


	CBY_BulletQueue::~CBY_BulletQueue()
	{
	}
}
