#pragma once
#include <type_traits>
#include <string>
#include <iostream>
#include <fstream>

//this class comes from Programming 3 and might be the same as some students

struct highScore
{
	char* name;
	int score;
};

class BinaryWriter
{
public:
	BinaryWriter(const std::string& filepath);
	~BinaryWriter() = default;

	template<typename T>
	void Write(T value)
	{
		m_Writer.write((char*)&value, sizeof(T));
	}

	bool GetExist();
	void WriteString(const std::string stringtowrite);
	void CloseFile();
private:
	std::ofstream m_Writer;
	bool m_Exists;

};

