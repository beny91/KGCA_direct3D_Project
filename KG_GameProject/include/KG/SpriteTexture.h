#pragma once
#include "Sprite.h"

struct MyUV
{
	D3DXVECTOR2 _uv[4];
};
struct Sprite_Info
{
	bool _animType;
	float _animTime;
	float _renderTime;
	UINT _curTextureIndex;
	UINT _textureCount;
	//uv
	UINT _widthSize;
	UINT _heightSize;
	UINT _widthCount;
	UINT _heightCount;

	std::vector<MyUV> _uvList;
	std::vector<int> _textureIndexList;
	std::vector<std::wstring> _textureList;

	Sprite_Info()
	{
		_animType = false;
		_animTime = 0.0f;
		_renderTime = 0.0f;
		_curTextureIndex = 0;
		_textureCount = 0;
		_widthSize = _heightSize = _widthCount = _heightCount = 0;
	}
};

class SpriteTexture :public Sprite
{
private:
	Sprite_Info _spriteInfo;
	float _time;
public:

	void createTextureAnimInfo();
	bool setTextureAnimInfo(float animTime, float textureCount, bool animType = true);
	bool setTextureUvInfo(UINT widthCount, UINT heightCount, UINT widthSize, UINT heightSize 
		,float animTime,bool animType = false);

	MyUV getTextureUv(UINT index) { return _spriteInfo._uvList[index]; }
	void resetState();

public:
	virtual bool Init() override;
	virtual bool Frame() override;
	virtual bool Render() override;
public:
	void setSpriteInfo(Sprite_Info info) { _spriteInfo = info; }
	Sprite_Info getSpriteInfo() { return _spriteInfo; }
public:
	SpriteTexture();
	virtual ~SpriteTexture();
};

