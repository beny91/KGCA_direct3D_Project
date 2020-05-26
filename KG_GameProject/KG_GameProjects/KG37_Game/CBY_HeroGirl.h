#pragma once
#include "CBY_Hero.h"

namespace CBY
{
	class CBY_HeroGirl : public CBY_Hero
	{
	public:
		bool Create(ID3D11Device* pd3dDevice, ID3D11DeviceContext* Context)override;

	public:
		CBY_HeroGirl();
		virtual ~CBY_HeroGirl();
	};
}

