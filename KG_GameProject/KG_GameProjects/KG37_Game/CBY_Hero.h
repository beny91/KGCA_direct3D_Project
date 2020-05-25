#pragma once
#include "CBY_CharacterSrc.h"

namespace CBY
{
	class CBY_EnemyAi;
	class CBY_Hero;

	class CBY_HeroProcess
	{
	protected:
		CBY_Hero* m_pHero;
		D3DXVECTOR3 m_vLook, m_vSide, m_vLookPush, m_vSidePush, m_vMove;

	public:
		virtual void SetColDirection();
		virtual void Process() {};

	public:
		CBY_HeroProcess(CBY_Hero* host) : m_pHero(host)
		{
		};
		~CBY_HeroProcess() {};
	};

	class CBY_Hero : public CBY_CharacterSrc
	{
	protected:
		CBY_HeroProcess* m_Action;
		CBY_HeroProcess* m_ActionList[CHAR_STATECOUNT];

	public:
		CBY_EnemyAi* m_pEnemy;

	public:
		virtual bool Init()override;
		virtual bool Frame()override;
		virtual bool Render()override;
		virtual bool Release()override;

	public:
		virtual bool Create(ID3D11Device* pd3dDevice, ID3D11DeviceContext* Context) override;
		virtual void Process();
		virtual void SetAction(DWORD Event);

	public:
		inline void SetEnemy(CBY_EnemyAi* enemy)
		{
			m_pEnemy = enemy;
		}

	public:
		CBY_Hero();
		virtual ~CBY_Hero();
	};
}

