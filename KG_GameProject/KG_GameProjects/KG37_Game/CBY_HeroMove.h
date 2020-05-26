#pragma once
#include "CBY_Hero.h"

namespace CBY
{
	class CBY_HeroMove : public CBY_HeroProcess
	{
	public:
		void Process()override;

	public:
		CBY_HeroMove(CBY_Hero* host);
		virtual ~CBY_HeroMove();
	};
}

