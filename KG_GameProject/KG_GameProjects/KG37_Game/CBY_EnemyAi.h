#pragma once
#include "CBY_CharacterSrc.h"
#include "CBY_EnemyFSM.h"

namespace KYS
{
	class VFX_EffectObj;
	class VFX_Effects;
}

namespace CBY
{
	class CBY_Hero;
	class CBY_EnemyAi;

	class CBY_EnemyProcess
	{
	protected:
		CBY_EnemyAi* m_pEnemy;
		D3DXVECTOR3 m_vLook, m_vSide, m_vLookPush, m_vSidePush, m_vMove;
		D3DXVECTOR3 m_LookDir;
		D3DXVECTOR3 m_SideDir;
		float m_fYaw, m_fPitch, m_fRoll;
		float m_fDirTime;		//디렉션이 바뀔 시간
		float m_fTime;			//스테이트별 전환 시간

	public:
		virtual bool SetColDirection();
		virtual D3DXVECTOR3 GetLookDir();
		
		virtual void Process() {};

	public:
		CBY_EnemyProcess(CBY_EnemyAi* host) : m_pEnemy(host)
		{
			m_fYaw = 0.0f;
			m_fPitch = 0.0f;
			m_fRoll = 0.0f;
			m_fTime = 0.0f;
			m_fDirTime = 3.0f;
		};
		~CBY_EnemyProcess() {};
	};

	class CBY_EnemyAi:public CBY_CharacterSrc
	{
	protected:
		CBY_EnemyProcess* m_Action;
		CBY_EnemyProcess* m_ActionList[CHAR_STATECOUNT];
		D3DXVECTOR3 m_LookDir;
		D3DXMATRIX m_matLook;
		float m_fYaw;
		float m_fEffetLookVal;	//유저가 볼 이펙트가 더 앞으로 나와서 터질 거리
		int m_iHP;

	public:
		CBY_Hero* m_pHero;


	public:
		std::shared_ptr<KYS::VFX_Effects> obj2;

	public:
		virtual bool Init()override;
		virtual bool Frame()override;
		virtual bool Render()override;
		virtual bool Release()override;

	public:
		virtual bool Create(ID3D11Device* pd3dDevice, ID3D11DeviceContext* Context) override;
		virtual void Process();
		virtual void SetAction(DWORD Event);
		virtual void SetMatrix(D3DXMATRIX* world, D3DXMATRIX* view, D3DXMATRIX* proj)override;

	public:
		inline virtual void SetEffectVal(float f)//유저가 볼 이펙트가 더 앞으로 나와서 터질 거리
		{
			m_fEffetLookVal = f;
		}
		inline virtual void SetHero(CBY_Hero* hero){m_pHero = hero;}
		inline virtual void SetYaw(float yaw) { m_fYaw = yaw; }
		inline virtual void SetLookDir(D3DXVECTOR3 lookdir) { m_LookDir = lookdir; }
		inline virtual void SetLookWorldMatrix(D3DXMATRIX matlook) { m_matLook = matlook; }
		inline virtual void SetHP(int HP) { m_iHP = HP; }

	public:
		inline virtual float GetEffectVal()//유저가 볼 이펙트가 더 앞으로 나와서 터질 거리
		{
			return m_fEffetLookVal;
		}
		inline virtual CBY_Hero* GetHero(){return m_pHero;}
		inline virtual D3DXVECTOR3 GetLookDir(){ return m_LookDir; }
		inline virtual float GetYaw() { return m_fYaw; }
		inline virtual int GetHP() { return m_iHP;}

	public:
		CBY_EnemyAi();
		virtual ~CBY_EnemyAi();
	};
}

