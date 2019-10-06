#include "MiniginPCH.h"
#include "BinaryReader.h"

BinaryReader::BinaryReader(const std::string& readfile)
	:m_Exists(false)
	,m_Reader{std::ifstream(readfile.c_str(), std::ios::in | std::ios::binary)}
{
	if (m_Reader.is_open()) m_Exists = true;
	else
	{

		std::cout << "[READ] Failed to open file: " << readfile << std::endl;
	}
}

std::string BinaryReader::ReadString()
{
	std::stringstream ss;

	if (m_Exists)
	{
		int stringLength = (int)Read<char>();

		for (int i{ 0 }; i < stringLength; ++i)
		{
			ss << Read<char>();
		}
	}
	return ss.str();

}

void BinaryReader::CloseFile()
{
	m_Reader.close();
}



