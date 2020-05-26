#pragma once
#include "CBY_EnemyAi.h"

namespace CBY
{
	class CBY_EnemyMove : public CBY_EnemyProcess
	{
	public:
		void Process()override;

	public:
		CBY_EnemyMove(CBY_EnemyAi* host);
		virtual ~CBY_EnemyMove();
	};
}

