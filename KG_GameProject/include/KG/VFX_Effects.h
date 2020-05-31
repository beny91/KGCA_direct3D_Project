#pragma once
#include "VFX_EffectObj.h"

enum class VFX_EFFECT_TYPE
{
	VFX_EFFECT_NONE = 0,
	VFX_EFFECT_GUN1_SHOT,
	VFX_EFFECT_GUN2_SHOT,
	VFX_EFFECT_GUN3_SHOT,
	VFX_EFFECT_GUN_IMPACT,
	VFX_EFFECT_CHAR_IMPACT,
	VFX_EFFECT_COUNT
};

class KG_Camera;
namespace KYS
{
	class VFX_Effects
	{
	public: // construct

		VFX_Effects();
		virtual ~VFX_Effects();

	public: // interface func and base func

		bool Init();
		bool Frame();
		bool Render(KG_Camera* camera, ID3D11Device* _device, ID3D11DeviceContext* _context);
		bool Release();

	public: //virtual

	public: //own func

		int Add(std::shared_ptr<VFX_EffectObj> obj);
		std::shared_ptr<VFX_EffectObj> GetEffectObj(int index);
		int GetEffectObj(std::shared_ptr<VFX_EffectObj> obj);

		void Execute(D3DXVECTOR3 pos, D3DXVECTOR3 dir = D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		void UpdateState();
		void ResetState();

	public: //getter, setter

		void SetObjList(std::map<int, std::shared_ptr<VFX_EffectObj>> list) { _objList = list; }
		std::map<int, std::shared_ptr<VFX_EffectObj>> GetObjList() { return _objList; }

		void SetEffectType(VFX_EFFECT_TYPE type) { _type = type; }
		VFX_EFFECT_TYPE GetEffectType() { return _type; }

		void SetActive(bool active) { _active = active; }
		bool GetActive() { return _active; }

		void SetScale(D3DXVECTOR3 scale);
		D3DXVECTOR3 GetScale();

	private: //member

		std::map<int, std::shared_ptr<VFX_EffectObj>> _objList;
		VFX_EFFECT_TYPE _type;
		bool _active;
	};

}