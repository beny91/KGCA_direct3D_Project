#pragma once
#include "MyEffectParser.h"
#include "KG_DxHeper.h"
#include "VFX_ObjMgr.h"
#include "VFX_EffectObj.h"


KYS::MyEffectParser::MyEffectParser()
{
}

KYS::MyEffectParser::~MyEffectParser()
{
}

void KYS::MyEffectParser::createEffectDataFromFile(const wchar_t * fileName, ID3D11Device * device, ID3D11DeviceContext* context)
{

	_device = device;
	_context = context;

	std::stringstream dataList;
	LoadFile(fileName, &dataList);

	while (dataList)
	{
		std::stringstream data;
		char	name[256] = { 0 };
		wchar_t loadFIleName[256] = { 0 };

		dataList >> name;

		int len = MultiByteToWideChar(CP_ACP, 0, name, strlen(name), NULL, NULL);
		MultiByteToWideChar(CP_ACP, 0, name, strlen(name), loadFIleName, len);


		LoadFile(loadFIleName, &data);
		createEffectObj(&data);
	
	}
	

	//VFX_MGR->add();
}

void KYS::MyEffectParser::createEffectObj(std::stringstream * destData)
{
	KYS::VFX_EFFECT_INFO info;
	std::shared_ptr<VFX_EffectObj> vfxObj;
	KYS::VFX_EffectObj* obj;
	Sprite_Info spriteInfo;
	SpriteTexture sprite;
	D3DXVECTOR3 pos;
	D3DXVECTOR3 dir;
	D3DXVECTOR3 initPos;
	D3DXVECTOR3 scale;
	D3DXMATRIX mat;
	D3DXVECTOR3 rotate;
	std::vector<MyParticle> particleList;
	std::map<int, std::shared_ptr<VFX_EffectObj>> vfxList;

	int size = 0;
	char token;

	*destData >> size;
	

	for (int count = 0; count < size; count++)
	{
		vfxObj = std::make_shared<VFX_EffectObj>();
		obj = vfxObj.get();
	

		*destData >> info._blendType >> token;
		*destData >> info._billboard >> token;
		*destData >> info._active >> token;
		*destData >> info._activeLifeTime >> token;
		*destData >> info._lifeTimeLimit >> token;
		*destData >> info._activeInterval >> token;
		*destData >> info._interval;

		obj->setInfo(info);
		obj->setInitInfo(info);

		*destData >> pos.x >> token;
		*destData >> pos.y >> token;
		*destData >> pos.z >> token;

		*destData >> rotate.x >> token;
		*destData >> rotate.y >> token;
		*destData >> rotate.z >> token;
		obj->setPos(pos);
		obj->setRotate(rotate);

		*destData >> spriteInfo._animType >> token;
		*destData >> spriteInfo._animTime >> token;
		*destData >> spriteInfo._renderTime >> token;
		*destData >> spriteInfo._widthCount >> token;
		*destData >> spriteInfo._heightCount >> token;
		*destData >> spriteInfo._widthSize >> token;
		*destData >> spriteInfo._heightSize >> token;
		*destData >> spriteInfo._textureCount >> token;

		*destData >> size;
		spriteInfo._textureList.resize(size);
		char name[256] = { 0 };
		wchar_t trans[256] = { 0 };
		for (auto& iter : spriteInfo._textureList)
		{
			ZeroMemory(name, sizeof(name));
			ZeroMemory(trans, sizeof(trans));

			*destData >> name;

			int len = MultiByteToWideChar(CP_ACP, 0, name, strlen(name), NULL, NULL);
			MultiByteToWideChar(CP_ACP, 0, name, strlen(name), trans, len);

			iter = trans;

			int index = I_Texture.Add(_device, trans);
			spriteInfo._textureIndexList.push_back(index);
		}

		if (!spriteInfo._animType)
		{
			*destData >> size;
			spriteInfo._uvList.resize(size);
			for (auto& iter : spriteInfo._uvList)
			{
				MyUV uv;
				uv = iter;
				*destData >> uv._uv[0].x >> token;
				*destData >> uv._uv[0].y >> token;

				*destData >> uv._uv[1].x >> token;
				*destData >> uv._uv[1].y >> token;

				*destData >> uv._uv[2].x >> token;
				*destData >> uv._uv[2].y >> token;

				*destData >> uv._uv[3].x >> token;
				*destData >> uv._uv[3].y >> token;
				iter = uv;
			}

		}
		sprite.setSpriteInfo(spriteInfo);
		obj->setSprite(sprite);

		*destData >> size;
		particleList.resize(size);

		for (auto& iter : particleList)
		{
			ParticleInfo info;

			*destData >> info._lifeTime >> token;
			*destData >> info._lifeTimeLimit >> token;
			*destData >> info._gravity >> token;
			*destData >> info._radius >> token;
			*destData >> info._radiusSpeed >> token;
			*destData >> info._activeLifeTime >> token;
			*destData >> info._activeGravity >> token;
			*destData >> info._active >> token;

			*destData >> info._initPos.x >> token;
			*destData >> info._initPos.y >> token;
			*destData >> info._initPos.z >> token;
			*destData >> info._pos.x >> token;
			*destData >> info._pos.y >> token;
			*destData >> info._pos.z >> token;
			*destData >> info._scale.x >> token;
			*destData >> info._scale.y >> token;
			*destData >> info._scale.z >> token;
			*destData >> info._rotate.x >> token;
			*destData >> info._rotate.y >> token;
			*destData >> info._rotate.z >> token;

			*destData >> info._direction.x >> token;
			*destData >> info._direction.y >> token;
			*destData >> info._direction.z >> token;

			*destData >> info._initDirection.x >> token;
			*destData >> info._initDirection.y >> token;
			*destData >> info._initDirection.z >> token;

			*destData >> info._matWorld._11 >> token;
			*destData >> info._matWorld._12 >> token;
			*destData >> info._matWorld._13 >> token;
			*destData >> info._matWorld._14 >> token;
			*destData >> info._matWorld._21 >> token;
			*destData >> info._matWorld._22 >> token;
			*destData >> info._matWorld._23 >> token;
			*destData >> info._matWorld._24 >> token;
			*destData >> info._matWorld._31 >> token;
			*destData >> info._matWorld._32 >> token;
			*destData >> info._matWorld._33 >> token;
			*destData >> info._matWorld._34 >> token;
			*destData >> info._matWorld._41 >> token;
			*destData >> info._matWorld._42 >> token;
			*destData >> info._matWorld._43 >> token;
			*destData >> info._matWorld._44 >> token;
			iter.setInfo(info);
			iter.setInitInfo(info);
		}
		obj->setParticleList(particleList);

		obj->Create(_device, _context, L"../../data/shader/effectShader.hlsl", trans, "VS", "PS");
		VFX_MGR->add(vfxObj);
	}
	
	return ;
}
