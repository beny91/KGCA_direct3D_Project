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
	
	public:
		 void LoadEffectDataFromFile(const wchar_t* fileName, ID3D11Device* device, ID3D11DeviceContext* context);
		 void CreateEffectObj(std::stringstream* destData);

	private:
		ID3D11Device* _device;
		ID3D11DeviceContext* _context;
	};

#define EFFECT_PARSER KYS::MyEffectParser::getParser()

}


