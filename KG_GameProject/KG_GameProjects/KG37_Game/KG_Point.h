#pragma once
#include "KG_ShapeObject.h"

class KG_Point :public KG_ShapeObject
{
public:
	HRESULT CreateVertexData();

public:
	KG_Point();
	virtual ~KG_Point();
};

