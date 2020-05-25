#pragma once
#include "CBY_CharacterSrc.h"

namespace KYS
{
	class VFX_EffectObj;
}

namespace CBY
{
	class CBY_EnemyAi;

	class CBY_EnemyProcess
	{
	protected:
		CBY_EnemyAi* m_pEnemy;
		D3DXVECTOR3 m_vLook, m_vSide, m_vLookPush, m_vSidePush, m_vMove;

	public:
		//virtual void SetColDirection();
		virtual void Process() {};

	public:
		CBY_EnemyProcess(CBY_EnemyAi* host) : m_pEnemy(host)
		{
		};
		~CBY_EnemyProcess() {};
	};

	class CBY_EnemyAi:public CBY_CharacterSrc
	{
	protected:
		CBY_EnemyProcess* m_Action;
		CBY_EnemyProcess* m_ActionList[CHAR_STATECOUNT];

	public:
		std::shared_ptr<KYS::VFX_EffectObj> obj2;

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
		CBY_EnemyAi();
		virtual ~CBY_EnemyAi();
	};
}

