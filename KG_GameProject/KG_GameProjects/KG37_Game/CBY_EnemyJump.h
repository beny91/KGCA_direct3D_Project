#pragma once
#include "CBY_EnemyAi.h"

namespace CBY
{
	class CBY_EnemyJump : public CBY_EnemyProcess
	{
	public:
		void Process()override;

	public:
		CBY_EnemyJump(CBY_EnemyAi* host);
		virtual ~CBY_EnemyJump();
	};
}

