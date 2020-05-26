#include "VFX_ObjMgr.h"

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
	for (auto effectObj : _effectList)
	{
		if (!effectObj->getInfo()._active)
			continue;

		effectObj->Frame();
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

	for (auto effectObj : _effectList)
	{
		obj = effectObj;

		if (!obj->getInfo()._active)
			continue;
		//CDX::ApplyRS(m_pContext, _raster);
		int blendType = obj->getInfo()._blendType;

		CDX::ApplyDSS(_context, CDX::KG_DxState::g_pDSSMaskZero);
		//CDX::ApplyDSS(_context, CDX::KG_DxState::g_pDSSDisable);
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
	KYS::VFX_EFFECT_INFO info;

	int number = VFX_EFFECT_NONE + _vfxList.size() + 1;
	info = effectObj.get()->getInfo();
	info._effectType = number;
	effectObj.get()->setInfo(info);
	effectObj.get()->setInitInfo(info);

	_vfxList.insert(std::make_pair(number, effectObj));
}

std::shared_ptr<KYS::VFX_EffectObj> KYS::VFX_ObjMgr::find(int index)
{
	
	std::shared_ptr<VFX_EffectObj> reObj;

	reObj = getEffect(index);
	
	if (reObj == nullptr)
	{
		// 없으면 vfxlist 오브젝트 복사해서 vector에 추가
		// 복사한 obj에는 타입 추가
		std::shared_ptr<VFX_EffectObj> obj;
		obj = _vfxList.find(index)->second;

		reObj = std::make_shared< VFX_EffectObj>();
		*reObj = *obj;

		_effectList.push_back(reObj);
		
	}

	return reObj;
}

std::shared_ptr<KYS::VFX_EffectObj> KYS::VFX_ObjMgr::getEffect(int type)
{
	std::shared_ptr<VFX_EffectObj> obj = nullptr;

	for (auto& iter : _effectList)
	{
		if (!iter.unique())
			continue;
		if (iter->getInfo()._effectType == type && 
			iter->getInfo()._active == false)
		{
			obj = iter;
			break;
		}		
	}

	return obj;
}
