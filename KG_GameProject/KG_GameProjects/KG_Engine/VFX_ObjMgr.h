#pragma once
#include <map>
#include <memory>
#include "VFX_EffectObj.h"
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
		void add(std::shared_ptr<VFX_EffectObj > effectObj);
		std::shared_ptr<VFX_EffectObj> find(int index);
		std::shared_ptr<VFX_EffectObj> getEffect(int type);
	public:
		void setVfxList(std::map<int, std::shared_ptr<VFX_EffectObj>> list) { _vfxList = list; }
		std::map<int, std::shared_ptr<VFX_EffectObj>> getVfxList() { return _vfxList; }

		void setDevice(ID3D11Device* device) { _device = device; }
		void setContext(ID3D11DeviceContext* context) { _context = context; }

	private:
		std::map<int, std::shared_ptr<VFX_EffectObj>> _vfxList;
		std::vector<std::shared_ptr<VFX_EffectObj>> _effectList;
		ID3D11Device* _device;
		ID3D11DeviceContext* _context;
	};

#define VFX_MGR KYS::VFX_ObjMgr::getInstance()
}


