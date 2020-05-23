#pragma once
#include "VFX_ObjMgr.h"
#include "KG_Camera.h"

KYS::VFX_ObjMgr::VFX_ObjMgr()
{
}

KYS::VFX_ObjMgr::~VFX_ObjMgr()
{
}

bool KYS::VFX_ObjMgr::Init()
{
	return false;
}

bool KYS::VFX_ObjMgr::Frame()
{
	for (auto effectObj : _vfxList)
	{
		if (!effectObj.second->getInfo()._active)
			continue;

		effectObj.second->Frame();
	}
	return false;
}

bool KYS::VFX_ObjMgr::Render(KG_Camera* camera)
{
	D3DXMATRIX matViewInverse;
	D3DXMATRIX matBillBoard;
	D3DXMATRIX matWorld;
	D3DXMATRIX matRotateX;
	D3DXMATRIX matRotateY;
	D3DXMATRIX matRotateZ;
	D3DXVECTOR3 objPos;
	D3DXVECTOR3 trans;
	ParticleInfo info;
	std::shared_ptr<VFX_EffectObj> obj;

	for (auto effectObj : _vfxList)
	{
		obj = effectObj.second;

		if (!obj->getInfo()._active)
			continue;
		//CDX::ApplyRS(m_pContext, _raster);
		int blendType = obj->getInfo()._blendType;

		CDX::ApplyDSS(_context, CDX::KG_DxState::g_pDSSMaskZero);
		//CDX::ApplyRS(m_pContext, _raster);
		//CDX::ApplyBS(m_pContext, CDX::KG_DxState::g_pBlendState[2]);
		for (auto& iter : obj->getParticleList())
		{
			
			//CDX::ApplyBS(m_pContext, CDX::KG_DxState::g_pBlendState[blendType]);
			if (obj->getInfo()._billboard)
			{
				//	//billboard

				info = iter.getInfo();
				matViewInverse = camera->m_View;
				D3DXMatrixInverse(&matViewInverse, NULL, &matViewInverse);
				matWorld = iter.getInfo()._matWorld;

				matViewInverse._41 = 0;
				matViewInverse._42 = 0;
				matViewInverse._43 = 0;
				matViewInverse._44 = 1;

				matWorld._41 = 0;
				matWorld._42 = 0;
				matWorld._43 = 0;
				matWorld._44 = 1;

				matBillBoard = matWorld * matViewInverse;

				objPos = obj->getPos();
				matBillBoard._41 += objPos.x + info._pos.x;
				matBillBoard._42 += objPos.y + info._pos.y;
				matBillBoard._43 += objPos.z + info._pos.z;

				obj->SetMatrix(&matBillBoard,
					&camera->m_View,
					&camera->m_Proj);
			}
			else
			{

				info = iter.getInfo();
				matWorld = info._matWorld;

				////effect 회전값
				float rotX = D3DXToRadian(obj->getRotate().x);
				float rotY = D3DXToRadian(obj->getRotate().y);
				float rotZ = D3DXToRadian(obj->getRotate().z);
				D3DXMatrixIdentity(&matRotateX);
				D3DXMatrixIdentity(&matRotateY);
				D3DXMatrixIdentity(&matRotateZ);
				D3DXMatrixRotationX(&matRotateX, rotX);
				D3DXMatrixRotationY(&matRotateY, rotY);
				D3DXMatrixRotationZ(&matRotateZ, rotZ);
				matWorld *= (matRotateX * matRotateY * matRotateZ);
				// 파티클 위치 + 이펙트 위치
				objPos = obj->m_vPos;
				matWorld._41 += info._pos.x + objPos.x;
				matWorld._42 += info._pos.y + objPos.y;
				matWorld._43 += info._pos.z + objPos.z;

				obj->SetMatrix(&matWorld,
					&camera->m_View,
					&camera->m_Proj);
			}
			CDX::ApplyBS(_context, CDX::KG_DxState::g_pBlendState[blendType]);
			obj->Render();

		}
	}
	CDX::ApplyDSS(_context, CDX::KG_DxState::g_pDSS);
	CDX::ApplyBS(_context, CDX::KG_DxState::g_pAlpahBlendDisable);

	return false;
}

bool KYS::VFX_ObjMgr::Release()
{
	return false;
}

void KYS::VFX_ObjMgr::add(std::shared_ptr<VFX_EffectObj> effectObj)
{
	int number = _vfxList.size();
	_vfxList.insert(std::make_pair(number, effectObj));
}

KYS::VFX_EffectObj* KYS::VFX_ObjMgr::find(int index)
{
	std::shared_ptr<VFX_EffectObj> obj;
	obj = _vfxList.find(index)->second;

	return  obj.get();
}
