#pragma once
#include "CBY_Hero.h"

namespace CBY
{
	class CBY_HeroFire : public CBY_HeroProcess
	{
	private:
		float m_fFireTime;

	public:
		void Process()override;

	public:
		CBY_HeroFire(CBY_Hero* host);
		virtual ~CBY_HeroFire();
	};
}

