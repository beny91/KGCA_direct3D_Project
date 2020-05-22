#pragma once
#include "KG_Camera.h"

class KG_BackViewCamera :public KG_Camera
{
public:
	virtual bool Frame() override;
	void Side(float fValue);
	void Front(float fValue);

public:
	KG_BackViewCamera();
	virtual ~KG_BackViewCamera();
};

