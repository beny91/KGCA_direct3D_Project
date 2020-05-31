
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
		effectObj->Frame();
	}
	return false;
}

bool KYS::VFX_ObjMgr::Render(KG_Camera* camera)
{

	for (auto effectObj : _effectList)
	{
		effectObj->Render(camera,_device,_context);
	}
	return false;
}

bool KYS::VFX_ObjMgr::Release()
{
	return false;
}

void KYS::VFX_ObjMgr::add(std::shared_ptr<VFX_Effects> effectObj, bool typeUse)
{
	VFX_EFFECT_TYPE type;
	if (typeUse)
	{
		int convertType = 0;

		convertType = static_cast<int>(VFX_EFFECT_TYPE::VFX_EFFECT_NONE) + _vfxList.size() + 1;
		type = static_cast<VFX_EFFECT_TYPE>(convertType);
		effectObj->SetEffectType(type);

		_vfxList.insert(std::make_pair(type, effectObj));
	}
	
	_effectList.push_back(effectObj);
}

std::shared_ptr<KYS::VFX_Effects> KYS::VFX_ObjMgr::find(VFX_EFFECT_TYPE index)
{
	if (_vfxList.empty()) return nullptr;
	std::shared_ptr<VFX_Effects> reObj;

	reObj = getEffect(index);
	
	if (reObj == nullptr)
	{
		// 없으면 vfxlist 오브젝트 복사해서 vector에 추가
		// 복사한 obj에는 타입 추가
		std::shared_ptr<VFX_Effects> obj;
		obj = _vfxList.find(index)->second;

		reObj = std::make_shared< VFX_Effects>();
		*reObj = *obj;

		_effectList.push_back(reObj);
		
	}

	return reObj;
}

std::shared_ptr<KYS::VFX_Effects> KYS::VFX_ObjMgr::getEffect(VFX_EFFECT_TYPE type)
{
	std::shared_ptr<VFX_Effects> obj = nullptr;

	for (auto& iter : _effectList)
	{
		//if (!iter.unique())
		//	continue;
		if (iter->GetEffectType() == type && iter->GetActive() == false)
		{
			obj = iter;
			break;
		}		
	}

	return obj;
}

void KYS::VFX_ObjMgr::ClearVfxList()
{
	_vfxList.clear();
}

void KYS::VFX_ObjMgr::ClearEffectList()
{
	_effectList.clear();
}
