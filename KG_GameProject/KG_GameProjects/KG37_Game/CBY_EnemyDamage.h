#pragma once
#include "CBY_EnemyAi.h"

namespace CBY
{
	class CBY_EnemyDamage : public CBY_EnemyProcess
	{
	public:
		void Process()override;

	public:
		CBY_EnemyDamage(CBY_EnemyAi* host);
		virtual ~CBY_EnemyDamage();
	};
}

