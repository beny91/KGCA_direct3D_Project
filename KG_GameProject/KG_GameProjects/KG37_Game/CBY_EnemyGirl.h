#pragma once
#include "CBY_EnemyAi.h"

namespace CBY
{
	class CBY_EnemyGirl : public CBY_EnemyAi
	{
	public:
		bool Create(ID3D11Device* pd3dDevice, ID3D11DeviceContext* Context)override;

	public:
		CBY_EnemyGirl();
		virtual ~CBY_EnemyGirl();
	};
}


