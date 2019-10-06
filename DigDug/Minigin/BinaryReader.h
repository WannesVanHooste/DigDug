#pragma once
#include <type_traits>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

//this class comes from Programming 3 and might be the same as some students

class BinaryReader
{
public:
	BinaryReader(const std::string& readfile);
	~BinaryReader() = default;

	template<typename T>
	T Read()
	{
		T value{};
		if (m_Exists)
		{
			m_Reader.read((char*)&value, sizeof(T));
		}
		return value;
	}

	std::string ReadString();
	void CloseFile();
private:
	bool m_Exists;
	std::ifstream m_Reader;
};

