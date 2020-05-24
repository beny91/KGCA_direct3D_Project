#pragma once
#include "KG_GameStd.h"
#include "CBY_Character.h"
#include "CBY_CharacterCamera.h"



class KG37_GameMain:public KG_Core
{
public:
	std::shared_ptr<CBY::CBY_Character> m_Character;
	std::shared_ptr<CBY::CBY_CharacterCamera> m_CharCamera;

public:
	virtual bool Init() override;
	virtual bool Frame() override;
	virtual bool Render() override;
	virtual bool Release() override;

public:
	KG37_GameMain();
	virtual ~KG37_GameMain();
};

//KGCA37_RUN(KG37_GameMain, KGCA_37_Game, KGCA_37_Game)