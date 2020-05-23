#pragma once
#include "Sprite.h"



bool Sprite::Init()
{
	return true;
}

bool Sprite::Frame()
{
	/*if (_lifeTime <= 0.0f) return true;
	_lifeTime -= g_secondPerFrame;*/
	//_elapseTime += g_secondPerFrame;
	//if (_elapseTime >= _secondPerRender)
	//{
	//	_index++;
	//	_elapseTime -= _secondPerRender;
	//	if (_index >= _spriteCount) 
	//	{
	//		if (_repeat)
	//		{
	//			_index = 0;
	//		}
	//		else
	//		{
	//			_active = false;
	//			_index = 0;
	//		}
	//	}
	//}
	return true;
}

bool Sprite::Render()
{
	return true;
}

bool Sprite::Release()
{
	return true;
}

bool Sprite::setAnimation(float lifeTime, float animationTime, int row, int col)
{
	return false;
}

Sprite::Sprite()
{
	 //_index = 0;
	 //_spriteCount = 0;
	 //_lifeTime = 0.0f;
	 //_secondPerRender = 0.0f;
	 //_elapseTime = 0.0f;
	 ////left
	 //_dir = DIR_LEFT;
	 ////수동조작 여부
	 //_manual = false;
	 //_device = nullptr;
	 //_deviceContext = nullptr;
	 //_repeat = false;
	 //_active = true;
}


Sprite::~Sprite()
{
}
