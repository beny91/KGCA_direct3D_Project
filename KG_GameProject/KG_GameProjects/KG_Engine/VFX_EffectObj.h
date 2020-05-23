#pragma once
#include "KG_ShapeObject.h"
#include "SpriteTexture.h"
#include "MyParticle.h"
enum VFX_EFFECT
{
	VFX_EFFECT_START = 1000,
	VFX_EFFECT_GUN_SHOT,
	VFX_EFFECT_GUN_SHOT_EXPLOSION,
	VFX_EFFECT_DAMAGED,
	VFX_EFFECT_END
};
namespace KYS
{
	struct VFX_EFFECT_INFO
	{
		D3DXVECTOR3 _direction;
		D3DXVECTOR3 _position;
		D3DXVECTOR3 _scale;
		D3DXVECTOR3 _rotation;

		int			_blendType;
		float		_lifeTime;
		float		_lifeTimeLimit;
		float		_interval;

		bool		_active;
		bool		_activeLifeTime;
		bool		_activeInterval;
		bool		_billboard;
		
		VFX_EFFECT_INFO()
		{
			_blendType  = 0;
			_lifeTimeLimit = _lifeTime = _interval =  0.0f;
			_direction = _position = _scale = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			_activeLifeTime = _activeInterval = _billboard = _active = false;
		}

	};
}

namespace KYS
{
	class VFX_EffectObj : public KG_ShapeObject
	{
	public:
		VFX_EffectObj();
		virtual ~VFX_EffectObj();

	public:
		virtual bool Init()override;
		virtual bool Frame()override;
		virtual bool Render()override;
		virtual bool Release()override;

	public:
		void Execute(D3DXVECTOR3 pos, D3DXVECTOR3 dir = D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		void shutdown();
		void resetState();

	protected:
		VFX_EFFECT_INFO _info;
		VFX_EFFECT_INFO _initInfo;
		SpriteTexture _sprite;
		ID3D11ShaderResourceView* _animationSRV;
		float _time;
		D3DXVECTOR3 _rotate;

	protected:
		std::vector<MyParticle> _particleList;


	public:

		void setInfo(VFX_EFFECT_INFO info) { _info = info; }
		VFX_EFFECT_INFO getInfo() { return _info; }

		void setInitInfo(VFX_EFFECT_INFO info) { _initInfo = info; }
		VFX_EFFECT_INFO getInitInfo() { return _initInfo; }

		void setSprite(SpriteTexture sprite) { _sprite = sprite; }
		SpriteTexture getSprite() { return _sprite; }

		void setParticleList(std::vector<MyParticle> list) { _particleList = list; }
		std::vector<MyParticle> getParticleList() { return _particleList; }

		void setPos(D3DXVECTOR3 pos) { m_vPos = pos; }
		D3DXVECTOR3 getPos() { return m_vPos; }

		void setRotate(D3DXVECTOR3 rotate) { _rotate = rotate; }
		D3DXVECTOR3 getRotate() { return _rotate; }

		void setParticleScale(D3DXVECTOR3 scale);
		D3DXVECTOR3 getParticleScale();

		
	};
}


