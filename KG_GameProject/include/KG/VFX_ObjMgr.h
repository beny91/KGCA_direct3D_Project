#pragma once
#include <map>
#include <memory>
#include "VFX_Effects.h"
#include "KG_Camera.h"

namespace KYS
{
	class VFX_ObjMgr
	{
	private:
		VFX_ObjMgr();
	public:
		virtual ~VFX_ObjMgr();

	public:
		static VFX_ObjMgr* getInstance()
		{
			static VFX_ObjMgr mgr;
			return &mgr;
		}
	public:
		bool Init();
		bool Frame();
		bool Render(KG_Camera* camera);
		bool Release();
	
	public:
		void add(std::shared_ptr<VFX_Effects > effectObj, bool typeUse = true);
		std::shared_ptr<VFX_Effects> find(VFX_EFFECT_TYPE index);
		std::shared_ptr<VFX_Effects> getEffect(VFX_EFFECT_TYPE type);
		void ClearVfxList();
		void ClearEffectList();
	public:
		void setVfxList(std::map<VFX_EFFECT_TYPE, std::shared_ptr<VFX_Effects>> list) { _vfxList = list; }
		std::map<VFX_EFFECT_TYPE, std::shared_ptr<VFX_Effects>> getVfxList() { return _vfxList; }

		std::vector<std::shared_ptr<VFX_Effects>> getEffectList() { return _effectList; }

		void setDevice(ID3D11Device* device) { _device = device; }
		void setContext(ID3D11DeviceContext* context) { _context = context; }

	private:
		//데이터
		std::map<VFX_EFFECT_TYPE, std::shared_ptr<VFX_Effects>> _vfxList;
		//실행되는 데이터
		std::vector<std::shared_ptr<VFX_Effects>> _effectList;
		ID3D11Device* _device;
		ID3D11DeviceContext* _context;
	};

#define VFX_MGR KYS::VFX_ObjMgr::getInstance()
}


