#pragma once
#include "KG_Std.h"
#include "KG_ObjStd.h"

struct ParticleInfo
{
	float _lifeTime;
	float _lifeTimeLimit;
	float _gravity;
	float _radius;
	float _radiusSpeed;
	bool _activeLifeTime;
	bool _activeGravity;
	bool _active;
	D3DXVECTOR3 _direction;
	D3DXVECTOR3 _initDirection;
	D3DXVECTOR3 _pos;
	D3DXVECTOR3 _initPos;
	D3DXVECTOR3 _scale;
	D3DXVECTOR3 _rotate;
	D3DXMATRIX _matWorld;
	float _moveSpeed;

	ParticleInfo()
	{
		_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		_initPos = _pos;
		_moveSpeed = 0.0f;
		_direction = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		_initDirection = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		_active = true;
		_lifeTime = 5.0f;
		_activeLifeTime = false;
		_activeGravity = false;
		_gravity = 0.0f;
		_radius = _radiusSpeed = 0.0f;
		D3DXMatrixIdentity(&_matWorld);
	}
};


class MyParticle
{
private:
	ParticleInfo _info;
	ParticleInfo _initInfo;
	float _time;
	float _gravity;
	float _gravitySpeed;
	float _radian;
	float _elapseTick;

	CScene _sceneInfo;

	std::vector<CAnimationTrack> _posTrackList;
	std::vector<CAnimationTrack> _rotateTrackList;
	std::vector<CAnimationTrack> _scaleTrackList;
public:
	bool frame();

public:
	void matUpdate();
	void resetState();
private:
	void update(int frameStart, int frameEnd, float elapseTick, D3DXMATRIX* matWorld);

public:
	void setInfo(ParticleInfo info) { _info = info; }
	ParticleInfo getInfo() { return _info; }

	void setInitInfo(ParticleInfo info) { _initInfo = info; }
	ParticleInfo getInitInfo() { return _initInfo; }

	void setSceneInfo(CScene info) { _sceneInfo = info; }
	CScene getSceneInfo() { return _sceneInfo; }

	void setPosTrack(std::vector<CAnimationTrack> track) { _posTrackList = track; }
	std::vector<CAnimationTrack>& getPosTrack() { return _posTrackList; }

	void setRotateTrack(std::vector<CAnimationTrack> track) { _rotateTrackList = track; }
	std::vector<CAnimationTrack>& getRotateTrack() { return _rotateTrackList; }

	void setScaleTrack(std::vector<CAnimationTrack> track) { _scaleTrackList = track; }
	std::vector<CAnimationTrack>& getScaleTrack() { return _scaleTrackList; }
public:
	MyParticle();
	virtual ~MyParticle();
};

