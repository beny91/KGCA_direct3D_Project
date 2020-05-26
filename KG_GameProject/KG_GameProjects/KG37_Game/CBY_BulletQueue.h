#pragma once
#include "CBY_Bullet.h"
#include <queue>

#define BULLET_NUM 1000

namespace CBY
{
	class CBY_BulletQueue
	{
	public:
		std::queue<CBY_Bullet*> m_List;
		void Push(CBY_Bullet* pobj);
		CBY_Bullet* Pop();
		void Release();

	public:
		CBY_BulletQueue();
		virtual ~CBY_BulletQueue();
	};
}

