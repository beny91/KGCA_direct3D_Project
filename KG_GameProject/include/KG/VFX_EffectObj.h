#pragma once
#include "KG_ShapeObject.h"
#include "SpriteTexture.h"
#include "MyParticle.h"



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
		float _fadeInOutWeight;
		float _scaleRepeatWeight;

		bool		_active;
		bool		_activeLifeTime;
		bool		_activeInterval;
		bool		_activeFadeInOut;
		bool		_activeScaleRepeat;
		bool		_billboard;
		int			_effectType;
		
		VFX_EFFECT_INFO()
		{
			_effectType = _blendType  = 0;
			_scaleRepeatWeight = _fadeInOutWeight = _lifeTimeLimit = _lifeTime = _interval =  0.0f;
			_direction = _position = _scale = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			_activeScaleRepeat = _activeFadeInOut = _activeLifeTime = _activeInterval = _billboard = _active = false;
		}

	};
	struct ConstantBuffer_Effect
	{
		//hlsl에서 bool은 int와 같은 4바이트
		int	_activeFadeInOut;
		int	_activeScaleRepeat;

		float _fadeInOutWeight;
		float _scaleRepeatWeight;

		ConstantBuffer_Effect()
		{
			_activeFadeInOut = _activeScaleRepeat = false;
			_fadeInOutWeight = _scaleRepeatWeight = 0.0f;
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

		virtual void SetMatrix(D3DXMATRIX* world, D3DXMATRIX* view, D3DXMATRIX* proj) override;

		
	public:
		void Execute(D3DXVECTOR3 pos, D3DXVECTOR3 dir = D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		void shutdown();
		void resetState();
		void createConstantBuffer();
		void updateConstantBuffer();

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


	protected:
		VFX_EFFECT_INFO _info;
		VFX_EFFECT_INFO _initInfo;
		SpriteTexture _sprite;
		ID3D11ShaderResourceView* _animationSRV;
		D3DXVECTOR3 _rotate;
		float _time;
		float _accScale;
		float _accFade;

		Microsoft::WRL::ComPtr<ID3D11Buffer> _effectConstantBuffer;
		ConstantBuffer_Effect _effectConstantData;

	protected:
		std::vector<MyParticle> _particleList;
	
	};
}


