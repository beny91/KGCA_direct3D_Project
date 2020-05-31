
#include "Myparser.h"
#include <string>
#include <fstream>
std::ofstream& operator<<(std::ofstream& o, std::stringstream& src)
{
	o << src.str();
	return o;
}

std::ifstream& operator>>(std::ifstream& istream, std::stringstream& dest)
{
	char data[256];
	while (istream)
	{
		istream.getline(data, sizeof(data));
		dest << data << std::endl;
	}
	return istream;
}

void KYS::Myparser::SaveFile(const wchar_t * fileName, std::stringstream * destData)
{
	std::ofstream of(fileName, std::ios::trunc);

	if (!of.is_open())
		return;
	
	of << *destData;
	

	of.close();
}

void KYS::Myparser::LoadFile(const wchar_t * fileName, std::stringstream * destData)
{
	std::ifstream inputStream(fileName);

	if (!inputStream.is_open())
		return;

	inputStream >> *destData;

	inputStream.close();
}

KYS::Myparser::Myparser()
{
}

KYS::Myparser::~Myparser()
{
}
