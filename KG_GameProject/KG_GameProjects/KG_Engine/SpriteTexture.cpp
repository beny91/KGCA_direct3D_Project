
#include "SpriteTexture.h"
#include "KG_TextureMgr.h"


void SpriteTexture::createTextureAnimInfo()
{
	if (_spriteInfo._animType)
	{
		setTextureAnimInfo(_spriteInfo._animTime, _spriteInfo._textureCount, _spriteInfo._animType);
	}
	else
	{
		setTextureUvInfo(_spriteInfo._widthCount, _spriteInfo._heightCount,
						_spriteInfo._widthSize, _spriteInfo._heightSize,
						_spriteInfo._animTime, _spriteInfo._animType);
	}

}


bool SpriteTexture::setTextureAnimInfo(float animTime, float textureCount, bool animType)
{
	_spriteInfo._animType = animType;
	_spriteInfo._animTime = animTime;
	_spriteInfo._renderTime = animTime / textureCount;
	return true;
}

bool SpriteTexture::setTextureUvInfo(UINT widthCount, UINT heightCount, UINT widthSize, UINT heightSize
	, float animTime, bool animType)
{
	_spriteInfo._animType = animType;
	_spriteInfo._widthCount = widthCount;
	_spriteInfo._heightCount = heightCount;
	_spriteInfo._widthSize = widthSize;
	_spriteInfo._heightSize = heightSize;
	_spriteInfo._textureCount = widthCount * heightCount;
	_spriteInfo._animTime = animTime;
	_spriteInfo._renderTime = animTime / _spriteInfo._textureCount;

	//한 칸 크기
	UINT width = widthSize / widthCount;
	UINT height = heightSize / heightCount;
	UINT rowCount = heightSize / height;
	UINT colCount = widthSize / width;

	MyUV uv;
	//uv 계산
	_spriteInfo._uvList.resize(_spriteInfo._textureCount);
	for (int row = 0; row < rowCount; row++)
	{
		for (int col = 0; col < colCount; col++)
		{
			uv._uv[0].x = (col * width) / static_cast<float>(widthSize);
			uv._uv[0].y = (row  * height) / static_cast<float>(heightSize);

			uv._uv[1].x = ((col + 1) * width) / static_cast<float>(widthSize);
			uv._uv[1].y = (row  * height) / static_cast<float>(heightSize);

			uv._uv[2].x = (col * width) / static_cast<float>(widthSize);
			uv._uv[2].y = ((row + 1) * height) / static_cast<float>(heightSize);

			uv._uv[3].x = ((col + 1) * width) / static_cast<float>(widthSize);
			uv._uv[3].y = ((row  + 1) * height) / static_cast<float>(heightSize);

			_spriteInfo._uvList[row * colCount + col] = uv;
		}
	}
	return true;
}

void SpriteTexture::resetState()
{
	_spriteInfo._curTextureIndex = 0;
	_time = 0.0f;
}

bool SpriteTexture::Init()
{
	return true;
}

bool SpriteTexture::Frame()
{
	_time += g_SecondTime;

	
	if (_time >= _spriteInfo._renderTime)
	{
		_spriteInfo._curTextureIndex++;

		if (_spriteInfo._curTextureIndex >= _spriteInfo._textureCount)
			_spriteInfo._curTextureIndex = 0;

		_time = 0.0f;
	}
	
	return true;
}

bool SpriteTexture::Render()
{
	/*_deviceContext->PSSetShaderResources(0, 1, _srvList[_index].GetAddressOf());
	_deviceContext->PSSetShaderResources(0, 1, _srvList[_index + 1].GetAddressOf());*/
	return true;
}

SpriteTexture::SpriteTexture()
{
	_time = 0.0f;
}


SpriteTexture::~SpriteTexture()
{
}
