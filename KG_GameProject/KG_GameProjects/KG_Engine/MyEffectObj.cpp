#include "pch.h"
#include <random>
#include "MyEffectObj.h"
#include "KG_TextureMgr.h"


bool MyEffectObj::Init()
{
	createSpriteInfo();
	createParticle();

	return false;
}

bool MyEffectObj::Frame()
{

	_time += g_SecondTime;

	_sprite.Frame();
	if (_sprite.getSpriteInfo()._animType)
	{
		int index = _sprite.getSpriteInfo()._textureIndexList[_sprite.getSpriteInfo()._curTextureIndex];
		CTexture* tempTexture = I_Texture.GetPtr(index);
		if (tempTexture != nullptr)
			_animationSRV = tempTexture->m_pTextureRV;
	}
	else
	{
		MyUV uvPos;
		uvPos = _sprite.getTextureUv(_sprite.getSpriteInfo()._curTextureIndex);

		for (int index = 0; index < 4; index++)
		{
			m_VerTex[index].t = uvPos._uv[index];
		}
		m_obj.m_pContext->UpdateSubresource(
			m_obj.m_pVertexBuffer.Get(),
			0, nullptr,
			&m_VerTex.at(0), 0, 0);
	}

	for (auto& iter : _particleList)
	{
		iter.frame();
	}

	if (_info._activeLifeTime)
	{
		_time = g_SecondTime;
		_info._lifeTime += _time;
		if (_info._lifeTime >= _info._lifeTimeLimit)
		{
			_info._active = false;
			_info._activeLifeTime = false;
		}
	}
	
	

	if (!_info._activeInterval) return true;

	if (_time > _info._interval)
	{
		_time = 0.0f;

		createParticle();
		_info._activeLifeTime = true;
		_info._lifeTime = _info._lifeTimeLimit;
	}


	return false;
}

bool MyEffectObj::Render()
{

	m_obj.PrePender();

	if (_animationSRV != nullptr)
		m_obj.m_pContext->PSSetShaderResources(0, 1, &_animationSRV);

	m_obj.PostPender();

	return true;
}

bool MyEffectObj::Release()
{
	return false;
}

void MyEffectObj::createSpriteInfo()
{
	_sprite.createTextureAnimInfo();
}

void MyEffectObj::createParticle()
{
	ParticleInfo particleInfo;

	particleInfo._direction = _info._direction;
	particleInfo._initDirection = particleInfo._direction;
	particleInfo._pos = _info._position;
	particleInfo._scale = _info._scale;


	particleInfo._activeLifeTime = _info._activeLifeTime;
	particleInfo._lifeTime = _info._lifeTime;
	particleInfo._lifeTimeLimit = _info._lifeTime;
	particleInfo._activeGravity = _info._activeGravity;
	particleInfo._gravity = _info._gravity;
	particleInfo._moveSpeed = _info._moveSpeed;
	particleInfo._radius = _info._radius;
	particleInfo._radiusSpeed = _info._radiusSpeed;
	particleInfo._rotate = _info._rotation;

	//_particleList.resize(_info._particleCount);
	//난수 발생하여 위치 정하기.
	MyParticle particle;
	for (int count = 0; count < _info._particleCount; count++)
	{
		std::random_device rd;

		// random_device 를 통해 난수 생성 엔진을 초기화 한다.
		std::mt19937 gen(rd());

		// 0 부터 99 까지 균등하게 나타나는 난수열을 생성하기 위해 균등 분포 정의.


		if (_info._posRandom == true)
		{
			std::uniform_real_distribution<float> dis(_info._min, _info._max);
			particleInfo._pos.x = dis(gen);
			particleInfo._pos.y = dis(gen);
			particleInfo._pos.z = dis(gen);
			particleInfo._initPos = particleInfo._pos;
		}
		if (_info._scaleRandom == true)
		{
			std::uniform_real_distribution<float> disDir(5, 10);
			particleInfo._scale.x = disDir(gen);
			particleInfo._scale.y = particleInfo._scale.x;
			particleInfo._scale.z = 1.0f;

		}
		if (_info._dirRandom == true)
		{
			std::uniform_real_distribution<float> dis1(-1, 1);
			particleInfo._direction.x = dis1(gen);
			particleInfo._direction.y = dis1(gen);
			particleInfo._direction.z = dis1(gen);
		}

		particleInfo._initPos = particleInfo._pos;
		particleInfo._initDirection = particleInfo._direction;

		particleInfo._matWorld._11 = particleInfo._scale.x;
		particleInfo._matWorld._22 = particleInfo._scale.y;
		particleInfo._matWorld._41 = particleInfo._pos.x;
		particleInfo._matWorld._42 = particleInfo._pos.y;
		particleInfo._matWorld._43 = particleInfo._pos.z;

		particle.setInfo(particleInfo);

		// animTrack
		//_particleList[count].setInfo(particleInfo);

		//CScene scene;
		//scene.iTickPerFrame = 160;
		//scene.iFirstFrame = 0;
		//scene.iLastFrame = scene.iTickPerFrame * _info._lifeTime;
		//scene.iFrameSpeed = 30;

		//particle.setSceneInfo(scene);
		//
		//D3DXVECTOR3 totalValue = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		//D3DXVECTOR3 valuePerFrame = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		//int trackCount = 0;
		//CAnimationTrack track;
		//std::vector<CAnimationTrack> trackList;

		////총 이동량
		//totalValue.x = (particleInfo._direction.x * particleInfo._moveSpeed) * particleInfo._lifeTime;
		//totalValue.y = (particleInfo._direction.y * particleInfo._moveSpeed) * particleInfo._lifeTime;
		//totalValue.z = (particleInfo._direction.z * particleInfo._moveSpeed) * particleInfo._lifeTime;
		////총 트랙
		//trackCount = scene.iTickPerFrame * particleInfo._lifeTime;
		////프레임당 이동값
		//valuePerFrame = totalValue / (scene.iTickPerFrame * particleInfo._lifeTime);

		//trackList.resize(trackCount);
		//track.p = particleInfo._pos;
		//for (int count = 0; count < trackCount; count++)
		//{
		//	track.iTick = count * scene.iTickPerFrame;
		//	track.p += valuePerFrame ;
		//	trackList[count] = track;
		//}

		//float totalRadian = (D3DX_PI * 2) * particleInfo._lifeTime;
		//float accumulatedRadian = 0.0f;
		//float valuePerFrame2;
		//D3DXVECTOR3 totalValue2;
		//valuePerFrame2 = totalRadian / (scene.iTickPerFrame * particleInfo._lifeTime)* (D3DX_PI * 2);

		//for (int count = 0; count < trackCount; count++)
		//{
		//	accumulatedRadian += valuePerFrame2;
		//	track = trackList[count];
		//	track.iTick = count * scene.iTickPerFrame;
		//	track.p.x += (cosf(accumulatedRadian * particleInfo._radiusSpeed) * particleInfo._radius);
		//	track.p.z += (sinf(accumulatedRadian * particleInfo._radiusSpeed) * particleInfo._radius);
		//	trackList[count] = track;
		//}

		//particle.setPosTrack(trackList);

		_particleList.push_back(particle);
	}





}


MyEffectObj::MyEffectObj()
{
	_animationSRV = nullptr;
	_curTextureIndex = 0;
	_time = 0.0f;
	_curRadian = 0.0f;
}

MyEffectObj::~MyEffectObj()
{

}
