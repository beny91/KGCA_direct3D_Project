#pragma once
#include "Myparser.h"

struct ID3D11Device;
struct ID3D11DeviceContext;
class VFX_EffectObj;

namespace KYS
{

	class MyEffectParser : public Myparser
	{
	public:
		static MyEffectParser* getParser()
		{
			static MyEffectParser parser;
			return &parser;
		}
	private:
		MyEffectParser();
	public:
		virtual~MyEffectParser();
	private:
		ID3D11Device* _device;
		ID3D11DeviceContext* _context;

	public:
		 void createEffectDataFromFile(const wchar_t* fileName, ID3D11Device* device, ID3D11DeviceContext* context);
		 void createEffectObj(std::stringstream* destData);
	};

#define EFFECT_PARSER KYS::MyEffectParser::getParser()

}


