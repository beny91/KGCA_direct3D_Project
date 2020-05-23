#pragma once
#include "KG_Std.h"
class Sprite
{
public:
	int _index;
	int _spriteCount;
	float _lifeTime;
	float _secondPerRender;
	float _elapseTime;
	//스프라이트 수동조작
	bool _manual;
	//반복
	bool _repeat;
	bool _active;
	int _dir;

public:
	virtual bool Init();
	virtual bool Frame();
	virtual bool Render();
	virtual bool Release();
public:
	virtual bool setAnimation(float lifeTime, float animationTime, int row=0, int col=0);
public:
	virtual void setIndex(int index) { _index = index; }
	virtual int getIndex() { return _index; }

	virtual void setManual(bool value) { _manual = value; }
	virtual bool getManual() { return _manual; }

	virtual void setSpriteCount(int count) { _spriteCount = count; }
	virtual int getSpriteCount() { return _spriteCount; }

	void setDir(int dir) { _dir = dir; };
	int getDir() { return _dir; };

	virtual void setRepeat(bool value) { _repeat = value; };
	virtual bool getRepeat() { return _repeat; };

	virtual void setActive( bool value) { _active = value; };
	virtual bool getActive() { return _active; };
public:
	Sprite();
	virtual ~Sprite();
};

