#pragma once
#include "CBY_EnemyAi.h"

namespace CBY
{
	class CBY_EnemyAttack : public CBY_EnemyProcess
	{
	public:
		void Process()override;

	public:
		CBY_EnemyAttack(CBY_EnemyAi* host);
		virtual ~CBY_EnemyAttack();
	};
}

