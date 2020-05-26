#pragma once
#include "CBY_Hero.h"

namespace CBY
{
	class CBY_HeroRun : public CBY_HeroProcess
	{
	public:
		void Process()override;

	public:
		CBY_HeroRun(CBY_Hero* host);
		virtual ~CBY_HeroRun();
	};
}

