#pragma once
#include "CBY_Character.h"
#include "CBY_Bullet.h"


namespace KYS
{
	class VFX_EffectObj;
	class VFX_Effects;
}

namespace CBY
{
	class CBY_Enemy
	{
	private:
		float m_fFireTime;		//발사 설정 시간
		float m_fFireSetTime;	//발사 시간까지의 계산시간
		bool m_bFireTime;
		KG_Camera* m_pCamera;

	public:
		std::shared_ptr<CBY::CBY_Character> m_Character;
		CBY::CBY_Bullet m_Bullet;
		std::shared_ptr<KYS::VFX_Effects> obj2;

	public:
		virtual bool Create(ID3D11Device* pd3dDevice, ID3D11DeviceContext* Context);
		virtual bool Init();
		virtual bool Frame();
		virtual bool Render();
		virtual bool Release();

	public:
		virtual void SetMatrix(D3DXMATRIX* world, D3DXMATRIX* view, D3DXMATRIX* proj);
		virtual void SetState(int i);
		virtual void SetFireTime(float ftime);
		virtual void SetCamera(KG_Camera* pcamera);

	public:
		virtual KG_Box GetCharBox();
		virtual D3DXVECTOR3 GetFirePos(int i);
		virtual bool GetStateAnimationStart(int i);
		virtual bool GetStateAnimationEnd(int i);
		virtual bool GetFire(int i);
		virtual CBY_Bullet* GetBullet();

	public:
		CBY_Enemy();
		virtual ~CBY_Enemy();
	};
}


