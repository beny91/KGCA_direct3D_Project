#pragma once
#include "CBY_EnemyAi.h"

namespace CBY
{
	class CBY_EnemyRun : public CBY_EnemyProcess
	{
	public:
		void Process()override;
		float m_fYawy;

	public:
		CBY_EnemyRun(CBY_EnemyAi* host);
		virtual ~CBY_EnemyRun();
	};
}

