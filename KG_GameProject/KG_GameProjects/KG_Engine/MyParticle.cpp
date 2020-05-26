#include "MyParticle.h"


bool MyParticle::frame()
{
	D3DXVECTOR3 calDir = (_info._direction *_info._moveSpeed) * g_SecondTime;
	_info._pos.x += calDir.x;
	_info._pos.y += calDir.y;
	_info._pos.z += calDir.z;

	if (_info._activeGravity )
	{
		_gravitySpeed += _info._gravity * g_SecondTime;
		_gravity = _info._gravity * g_SecondTime + _gravitySpeed;
		_info._moveSpeed -= _info._gravity * g_SecondTime;
		_info._pos.y -= _gravity;
	}

	if (_info._moveSpeed <= 0.0f)
		_info._moveSpeed = 0.0f;
	if (_gravitySpeed >= 50.0f)
		_gravitySpeed = 50.0f;
		
	if (_info._radius > 0.0f)
	{
		
		//1초당 1회전
		float speed = 6 / _info._radiusSpeed;
		_radian += ((D3DX_PI / speed) * g_SecondTime);
		_info._pos.x = (cosf(_radian) * _info._radius);
		_info._pos.z = (sinf(_radian) * _info._radius);
	}

	//if (!_info._activeLifeTime) return true;

	//_time = g_SecondTime;
	//_info._lifeTime -= _time;

	//if (_info._lifeTime <= 0)
	//{
	//	_info._active = false;
	//	_info._activeLifeTime = false;
	//}
		


	//float fTime = 0;
	//fTime = 1.0f*g_SecondTime *
	//	_sceneInfo.iTickPerFrame * _sceneInfo.iFrameSpeed;
	//if (fTime >= _sceneInfo.iTickPerFrame)
	//{
	//	fTime = _sceneInfo.iTickPerFrame;
	//}

	//_elapseTick += fTime;
	//if (_elapseTick >=
	//	_sceneInfo.iLastFrame * _sceneInfo.iTickPerFrame)
	//	//m_Loader.m_Scene.iLastFrame * m_Loader.m_Scene.iTickPerFrame)
	//{
	//	_elapseTick = _sceneInfo.iLastFrame * _sceneInfo.iTickPerFrame;
	//}
	//
	//update(0, 0, _elapseTick, &_info._matWorld);
	//_info._pos.x = _info._matWorld._41;
	//_info._pos.y = _info._matWorld._42;
	//_info._pos.z = _info._matWorld._43;

	
	return true;
}

void MyParticle::update(int frameStart, int frameEnd, float elapseTick, D3DXMATRIX * matWorld)
{
	D3DXVECTOR3 vPos;

	if (_posTrackList.size() > 0)
	{
		CAnimationTrack start;
		CAnimationTrack end = _posTrackList[_posTrackList.size() - 1];
		start.iTick = 0;
		for (int tick = 0; tick < _posTrackList.size();
			tick++)
		{
			if (_posTrackList[tick].iTick <=
				elapseTick)
			{
				start = _posTrackList[tick];
			}
			if (_posTrackList[tick].iTick >
				elapseTick)
			{
				end = _posTrackList[tick];
				break;
			}
		}

		//	//start <= m_fElapseTick < end
		//	// 0   <=   x   < 160
		float fStep = end.iTick - start.iTick;
		//	//0 ~ 1
		float t = 0.0f;
		if (fStep > 0.0f)
		{
			t = (elapseTick - start.iTick) / fStep;
		}
		D3DXVec3Lerp(&vPos, &start.p, &end.p, t);
	}
	matWorld->_41 = vPos.x;
	matWorld->_42 = vPos.y;
	matWorld->_43 = vPos.z;

}

void MyParticle::matUpdate()
{
	_info._matWorld._11 = _info._scale.x;
	_info._matWorld._22 = _info._scale.y;
	_info._matWorld._33 = _info._scale.z;
}

void MyParticle::resetState()
{
	D3DXVECTOR3 scale;
	scale = _info._scale;
	_info = _initInfo;
	_info._scale = scale;
	_gravitySpeed = 0.0f;
	_gravity = 0.0f;
}


MyParticle::MyParticle()
{
	_info._active = true;
	_info._lifeTime = -999;
	_gravity = 0.0f;
	_gravitySpeed = 0.0f;
	_radian = 0.0f;
	_elapseTick = 0.0f;
}

MyParticle::~MyParticle()
{
}
