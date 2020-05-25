#pragma once
#include "CBY_Hero.h"

namespace CBY
{
	class CBY_HeroDamage : public CBY_HeroProcess
	{
	public:
		void Process()override;

	public:
		CBY_HeroDamage(CBY_Hero* host);
		virtual ~CBY_HeroDamage();
	};
}

