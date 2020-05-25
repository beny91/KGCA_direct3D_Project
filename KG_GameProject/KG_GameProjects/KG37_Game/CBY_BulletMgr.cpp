#include "CBY_BulletMgr.h"

namespace CBY
{
	bool CBY_BulletMgr::Init()
	{
		for (int i = 0; i < BULLET_NUM; i++)
		{
			CBY_Bullet* wea = new CBY_Bullet;
			m_BulletQueue.Push(wea);
		}
		return true;
	}

	bool CBY_BulletMgr::Frame()
	{
		for (int i = 0; i < m_pBulletList.size(); i++)
		{
			m_pBulletList[i]->Frame();
		}
		return true;
	}

	bool CBY_BulletMgr::Render()
	{
		for (int i = 0; i < m_pBulletList.size(); i++)
		{
			m_pBulletList[i]->SetMatrix(&m_matWorld, &m_matView, &m_matProj);
			m_pBulletList[i]->Render();
		}
		return true;
	}

	bool CBY_BulletMgr::Release()
	{
		for (int i = 0; i < m_pBulletList.size();)
		{
			m_pBulletList[0]->Release();
			Bulletiter iter = m_pBulletList.begin();
			BulletPop(iter);
		}
		m_pBulletList.clear();
		m_BulletQueue.Release();

		return true;
	}

	void CBY_BulletMgr::SetMatrix(D3DXMATRIX* world, D3DXMATRIX* view, D3DXMATRIX* proj)
	{
		if (world != nullptr)
		{
			m_matWorld = *world;
		}

		if (view != nullptr)
		{
			m_matView = *view;
		}

		if (proj != nullptr)
		{
			m_matProj = *proj;
		}

		m_Select.SetMarix(nullptr, view, proj);
	}

	void CBY_BulletMgr::BulletMake(CBY_Bullet* weapon, D3DXVECTOR3 vpos, D3DXVECTOR3 vdir,D3DXMATRIX* world)
	{
		CBY_Bullet* wea = m_BulletQueue.Pop();
		*wea = *weapon;
		wea->SetPos(vpos);
		//wea->SetDirection(m_Select.m_Ray.m_Dir);
		wea->SetDirection(vdir);
		wea->SetWorld(*world);
		m_pBulletList.push_back(wea);
	}

	Bulletiter CBY_BulletMgr::BulletPop(Bulletiter iweapon)
	{
		Bulletiter wea;
		m_BulletQueue.Push(*iweapon);
		wea = m_pBulletList.erase(iweapon);
		return wea;
	}

	void CBY_BulletMgr::BulletPop(int iweapon)
	{
		m_pBulletList[iweapon]->Release();
		Bulletiter iter = m_pBulletList.begin() + iweapon;
		m_BulletQueue.Push(*iter);
		m_pBulletList.erase(iter);
	}


	CBY_BulletMgr::CBY_BulletMgr()
	{
		D3DXMatrixIdentity(&m_matWorld);
		D3DXMatrixIdentity(&m_matView);
		D3DXMatrixIdentity(&m_matProj);
	}


	CBY_BulletMgr::~CBY_BulletMgr()
	{
	}
}