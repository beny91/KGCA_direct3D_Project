#pragma once
#include "KG_ShapeObject.h"
#include "SpriteTexture.h"
#include "MyParticle.h"

enum BLEND_TYPE
{
	BLEND_ALPHA = 0,
	BLEND_DUAL_SOURCE,
	BLEND_NONE
};

struct Effect_info
{
	int _blendType;
	int _min;
	int _max;
	int _particleCount;
	float _lifeTime;
	float _lifeTimeLimit;
	float _interval;
	float _moveSpeed;
	float _radius;
	float _radiusSpeed;
	float _gravity;
	bool _active;
	D3DXVECTOR3 _direction;
	D3DXVECTOR3 _position;
	D3DXVECTOR3 _scale;
	D3DXVECTOR3 _rotation;

	bool	_activeLifeTime;
	bool	_activeInterval;
	bool	_activeGravity;
	bool	_posRandom;
	bool	_dirRandom;
	bool	_scaleRandom;
	bool	_billboard;
	bool	_activeRadius;
	Effect_info()
	{
		 _blendType  = _min = _max = _particleCount = 0;
		 _lifeTimeLimit = _lifeTime = _interval = _moveSpeed = _radius = _radiusSpeed = _gravity = 0.0f;
		 _direction = _position = _scale  = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		  _activeLifeTime = _activeInterval = _posRandom =	_dirRandom = _scaleRandom =	_billboard = _activeRadius = _activeGravity = false;
		  _active = true;
	}

};
//tool에서 사용할 effectObj
class MyEffectObj : public KG_ShapeObject
{
private:
	Effect_info _info;
	std::vector<int> _textureIndexList;
	ID3D11ShaderResourceView* _animationSRV;
	SpriteTexture _sprite;
	CScene _sceneInfo;
	int _curTextureIndex;
	float _time;
	float _curRadian;

	float _createInterval;
	D3DXVECTOR3 _rotation;
	std::vector<MyParticle> _particleList;
public:
	virtual bool Init()override;
	virtual bool Frame()override;
	virtual bool Render()override;
	virtual bool Release()override;
public:
	void createSpriteInfo();
	void createParticle();
public:
	void setEffectInfo(Effect_info info) { _info = info; }
	Effect_info getEffectInfo() { return _info; }

public:
	

public:
	void setSpriteInfo(Sprite_Info info) { _sprite.setSpriteInfo(info); }
	Sprite_Info getSpriteInfo() { return _sprite.getSpriteInfo(); }

	void setSceneInfo(CScene info) { _sceneInfo = info; }
	CScene getSceneInfo() { return _sceneInfo; }

	void setParticleList(std::vector<MyParticle> list) { _particleList = list; }
	std::vector<MyParticle>& getParticleList() { return _particleList; }

	std::vector<int>& getTextureIndexList() { return _textureIndexList; }

	void setCreateInterval(float interval) { _createInterval = interval; }
	float getCreateInterval() { return _createInterval; }

	void setPos(D3DXVECTOR3 pos) { m_vPos = pos; }
	D3DXVECTOR3 getPos() { return m_vPos; }

	void setRotate(D3DXVECTOR3 rotate) { _rotation = rotate; }
	D3DXVECTOR3 getRotate() { return _rotation; }

	void setRadian(float rotate) { _curRadian = rotate; }
	float getRadian() { return _curRadian; }
public:
	MyEffectObj();
	virtual ~MyEffectObj();
};

