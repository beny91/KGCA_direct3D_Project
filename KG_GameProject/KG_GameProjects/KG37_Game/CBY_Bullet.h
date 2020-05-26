#pragma once
#include "CBY_Object.h"

namespace CBY
{
	class CBY_Bullet : public CBY_Object
	{
	private:
		float m_fSpeed;			//�Ѿ��� �ӵ�
		int m_iPower;			//�Ѿ��� ����
		D3DXVECTOR3 m_vAmmoDir;		//�Ѿ��� ���ư� ����
		D3DXVECTOR3 m_vAmmoPos;		//�Ѿ��� ��ġ
		D3DXMATRIX m_matAmmoWorld;	//ó�� �� ���� ȸ������ ����ִ� ���

	public:
		bool Init();
		bool Frame();

	public:
		virtual void SetMatrix(D3DXMATRIX* world, D3DXMATRIX* view, D3DXMATRIX* proj) override;

	public:
		inline void SetSpeed(float fspeed)
		{
			m_fSpeed = fspeed;
		}
		inline void SetPower(int i)
		{
			m_iPower = i;
		}
		inline void SetPos(D3DXVECTOR3 pos)
		{
			m_vAmmoPos = pos;
		}
		inline void SetDirection(D3DXVECTOR3 dir)
		{
			m_vAmmoDir = dir;
		}
		inline void SetWorld(D3DXMATRIX world)
		{
			m_matAmmoWorld = world;
		}

	public:
		inline int GetPower()
		{
			return m_iPower;
		}
		inline D3DXVECTOR3 GetPos()
		{
			return m_vAmmoPos;
		}

	public:
		CBY_Bullet();
		virtual ~CBY_Bullet();
	};
}

