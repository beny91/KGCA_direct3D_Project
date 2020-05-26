#pragma once
#include "CBY_Character.h"
#include "CBY_Bullet.h"
#include "KG_Collision.h"
#include "KG_Camera.h"

namespace CBY
{
	class CBY_CharacterSrc
	{
	protected:
		float m_fFireTime;		//발사 설정 시간
		float m_fFireSetTime;	//발사 시간까지의 계산시간
		bool m_bFireTime;
		float m_fSpeed;
		D3DXVECTOR3 m_vCharPos;
		KG_Camera* m_pCamera;

	protected:
		DWORD m_dwCharState;
		std::shared_ptr<CBY::CBY_Character> m_Character;
		CBY::CBY_Bullet m_Bullet;

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
		virtual void SetHeroPos(D3DXVECTOR3 vpos);
		inline virtual void SetEndClip(int iState, bool bclip) { m_Character->SetEndClip(iState, bclip); }
		inline virtual void SetCamera(KG_Camera* pCamera)
		{
			m_pCamera = pCamera;
		}
		inline virtual void SetMoveSpeed(float fSpeed)
		{
			m_fSpeed = fSpeed;
		}

	public:
		virtual D3DXVECTOR3 GetCamerPos();
		virtual KG_Box GetCharBox();
		virtual KG_Box GetColBox(int ibox);
		virtual D3DXVECTOR3 GetColPos(int ibox);
		virtual int GetColBoxSize();
		virtual D3DXVECTOR3 GetFirePos(int i);
		virtual bool GetStateAnimationStart(int i);
		virtual bool GetStateAnimationEnd(int i);
		virtual bool GetFire(int i);
		virtual D3DXVECTOR3 GetHeroPos();
		virtual CBY_Bullet* GetBullet();
		inline virtual KG_Camera* GetCamera()
		{
			return m_pCamera;
		}
		inline virtual float GetMoveSpeed()
		{
			return m_fSpeed;
		}

	public:
		CBY_CharacterSrc();
		virtual ~CBY_CharacterSrc();
	};
}

