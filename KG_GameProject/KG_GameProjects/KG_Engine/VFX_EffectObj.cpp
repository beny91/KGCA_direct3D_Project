#include "VFX_EffectObj.h"

KYS::VFX_EffectObj::VFX_EffectObj()
{
	_animationSRV = nullptr;
}

KYS::VFX_EffectObj::~VFX_EffectObj()
{
}

bool KYS::VFX_EffectObj::Init()
{
	return false;
}

bool KYS::VFX_EffectObj::Frame()
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

		//createParticle();
		_info._activeLifeTime = true;
		_info._lifeTime = _info._lifeTimeLimit;
	}


	return false;
}

bool KYS::VFX_EffectObj::Render()
{
	m_obj.PrePender();

	if (_animationSRV != nullptr)
		m_obj.m_pContext->PSSetShaderResources(0, 1, &_animationSRV);

	m_obj.PostPender();
	return false;
}

bool KYS::VFX_EffectObj::Release()
{
	return false;
}

void KYS::VFX_EffectObj::Execute(D3DXVECTOR3 pos, D3DXVECTOR3 dir)
{

	resetState();

	m_vPos = pos;

	ParticleInfo info;
	for (auto& obj : _particleList)
	{
		info = obj.getInfo();
		info._direction += dir;

		obj.setInfo(info);
		obj.matUpdate();
	}

	_sprite.resetState();


}

void KYS::VFX_EffectObj::shutdown()
{
	_info._active = false;

	for (auto& obj : _particleList)
	{
		obj.resetState();
	}
}

void KYS::VFX_EffectObj::resetState()
{
	_info = _initInfo;
}

void KYS::VFX_EffectObj::setParticleScale(D3DXVECTOR3 scale)
{
	ParticleInfo info;
	for (auto& obj : _particleList)
	{
		info = obj.getInfo();
		info._scale = scale;
		obj.setInfo(info);
		obj.matUpdate();
	}
}

D3DXVECTOR3 KYS::VFX_EffectObj::getParticleScale()
{
	return D3DXVECTOR3();
}
