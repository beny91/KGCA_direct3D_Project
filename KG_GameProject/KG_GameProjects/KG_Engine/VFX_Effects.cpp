#include "VFX_Effects.h"
#include "KG_Camera.h"

KYS::VFX_Effects::VFX_Effects()
{
	_type = VFX_EFFECT_TYPE::VFX_EFFECT_NONE;
	_active = true;
}

KYS::VFX_Effects::~VFX_Effects()
{
}

bool KYS::VFX_Effects::Init()
{
	return false;
}

bool KYS::VFX_Effects::Frame()
{
	if (!_active) return false;
	for (auto obj : _objList)
	{
		if (!obj.second->getInfo()._active)
			continue;
		obj.second->Frame();
	}

	UpdateState();
	return true;
}

int KYS::VFX_Effects::Add(std::shared_ptr<VFX_EffectObj> obj)
{
	if (obj == nullptr)
		return -1;

	int index = -1;
	int size = 0;

	index = GetEffectObj(obj);
	size = _objList.size();

	if (index >= 0)
		return index;
	else
		_objList.insert(std::make_pair(size,obj));
	

	return size;
}

std::shared_ptr<KYS::VFX_EffectObj> KYS::VFX_Effects::GetEffectObj(int index)
{

	if (index < 0)
		return nullptr;

	std::shared_ptr<VFX_EffectObj> reObj;

	reObj = _objList.find(index)->second;

	return reObj;
}

int KYS::VFX_Effects::GetEffectObj(std::shared_ptr<VFX_EffectObj> obj)
{
	for (DWORD index = 0; index < _objList.size(); index++)
	{
		if (obj == _objList[index])
			return index;
	}
	return -1;
}

void KYS::VFX_Effects::Execute(D3DXVECTOR3 pos, D3DXVECTOR3 dir)
{
	ResetState();
	for (auto& obj : _objList)
	{
		obj.second->Execute(pos, dir);
	}
}

void KYS::VFX_Effects::UpdateState()
{
	bool active = true;
	for (auto obj : _objList)
	{
		active = obj.second->getInfo()._active;
		if (active) break;
	}

	if (!active) _active = false;
}

void KYS::VFX_Effects::ResetState()
{
	_active = true;
}

void KYS::VFX_Effects::SetScale(D3DXVECTOR3 scale)
{
	ParticleInfo info;
	for (auto& obj : _objList)
	{
		obj.second->setParticleScale(scale);
	}
}

D3DXVECTOR3 KYS::VFX_Effects::GetScale()
{
	return D3DXVECTOR3();
}



bool KYS::VFX_Effects::Render(KG_Camera* camera, ID3D11Device* _device,ID3D11DeviceContext* _context)
{
	if (!_active) return false;

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

	for (auto effectObj : _objList)
	{
		obj = effectObj.second;

		if (!obj->getInfo()._active)
			continue;
		//blend
		int blendType = obj->getInfo()._blendType;
		CDX::ApplyDSS(_context, CDX::KG_DxState::g_pDSSMaskZero);
		
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

	return true;
}

bool KYS::VFX_Effects::Release()
{
	for (auto obj : _objList)
	{
		obj.second->Release();
	}
	return false;
}
