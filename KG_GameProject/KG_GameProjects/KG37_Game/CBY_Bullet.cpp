#include "CBY_Bullet.h"

namespace CBY
{
	bool CBY_Bullet::Init()
	{
		CBY_Object::Init();
		return true;
	}

	bool CBY_Bullet::Frame()
	{
		CBY_Object::Frame();

		m_vAmmoPos += m_vAmmoDir * m_fSpeed * g_SecondTime;		//총알의 위치를 디렉션 방향으로 계속 날려주는중
		return true;
	}

	void CBY_Bullet::SetMatrix(D3DXMATRIX* world, D3DXMATRIX* view, D3DXMATRIX* proj)
	{
		D3DXMATRIX matworld;
		if (world != nullptr)
		{
			matworld = m_matAmmoWorld * (*world);
		}
		else
		{
			matworld = m_matAmmoWorld;
		}

		matworld._41 = m_vAmmoPos.x;
		matworld._42 = m_vAmmoPos.y;
		matworld._43 = m_vAmmoPos.z;
		
		//CBY_Object::SetMatrix(&matworld, view, proj);
		KG_Model::SetMatrix(&matworld, view, proj);

		{	//캐릭터를 감싼 바운딩 박스의 움직임을 제어하는 곳
			D3DXMATRIX matRot;
			D3DXVECTOR3 vScale, vPos, vSize;
			D3DXQUATERNION qRot;
			D3DXMatrixDecompose(&vScale, &qRot, &vPos, &matworld);
			D3DXMatrixRotationQuaternion(&matRot, &qRot);

			vSize = m_ObjList[0]->m_ObjList[0]->m_CharBox.vMax - m_ObjList[0]->m_ObjList[0]->m_CharBox.vCenter;
			vSize.x *= vScale.x;
			vSize.y *= vScale.y;
			vSize.z *= vScale.z;
			//vPos += m_ObjList[0]->m_ObjList[0]->m_CharBox.vCenter;
			D3DXVec3TransformCoord(&vSize, &vSize, &matRot);

			m_CharBox.CreateBox(0, vPos, vSize.x, vSize.y, vSize.z, matRot);		//박스 업데이트

			m_CharBox.UpdateBoxAxis(matRot);
		}		
	}

	CBY_Bullet::CBY_Bullet()
	{
		m_iPower = 0;
	}


	CBY_Bullet::~CBY_Bullet()
	{
	}

}