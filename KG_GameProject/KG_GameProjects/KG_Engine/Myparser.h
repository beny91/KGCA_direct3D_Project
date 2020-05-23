#pragma once
#include "KG_Std.h"

namespace KYS
{
	class Myparser
	{
	public:
		virtual void SaveFile(const wchar_t* fileName, std::stringstream* destData);
		virtual void LoadFile(const wchar_t* fileName, std::stringstream* destData);
	public:
		Myparser();
		virtual~Myparser();
	};
}

