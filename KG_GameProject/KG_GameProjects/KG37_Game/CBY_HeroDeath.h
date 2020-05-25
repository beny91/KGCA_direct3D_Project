#pragma once
#include "CBY_Hero.h"

namespace CBY
{
	class CBY_HeroDeath : public CBY_HeroProcess
	{
	public:
		void Process()override;

	public:
		CBY_HeroDeath(CBY_Hero* host);
		virtual ~CBY_HeroDeath();
	};
}

