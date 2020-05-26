#pragma once
#include "CBY_EnemyAi.h"

namespace CBY
{
	class CBY_EnemyDeath : public CBY_EnemyProcess
	{
	public:
		void Process()override;

	public:
		CBY_EnemyDeath(CBY_EnemyAi* host);
		virtual ~CBY_EnemyDeath();
	};
}

