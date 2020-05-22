#pragma once
#include "KG_Std.h"

namespace KG_COLLOSION
{
	bool ChkOBBToOBB(const KG_Box box1, const KG_Box box2);
}

class KG_Collision
{
public:
	KG_Collision();
	virtual ~KG_Collision();
};

