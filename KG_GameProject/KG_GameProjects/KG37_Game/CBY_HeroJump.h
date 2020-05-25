#pragma once
#include "CBY_Hero.h"

namespace CBY
{
	class CBY_HeroJump : public CBY_HeroProcess
	{
	public:
		void Process()override;

	public:
		CBY_HeroJump(CBY_Hero* host);
		virtual ~CBY_HeroJump();
	};
}

