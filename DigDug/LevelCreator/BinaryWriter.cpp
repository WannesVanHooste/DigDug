#include "pch.h"
#include "BinaryWriter.h"
#include <iostream>
#include <string>
#include <cstring>

BinaryWriter::BinaryWriter(const std::string& filepath)
	:m_Exists(false)
	,m_Writer(std::ofstream(filepath.c_str(), std::ios::out | std::ios::binary))
{
	if (m_Writer.is_open()) m_Exists = true;
	else
	{
		std::cout << "[WRITE] Failed to open file: " << filepath << std::endl;
	}
}

bool BinaryWriter::GetExist()
{
	return m_Exists;
}

void BinaryWriter::WriteString(const std::string stringtowrite)
{
	if (m_Exists)
	{
		/*int length{ (int)stringtowrite.length() };
		char* toWrite = new char[length];
		for (int i{}; i != length; ++i)
		{
			toWrite[i] = stringtowrite[i];
		}
		toWrite[length] = '\0';
		m_Writer.write(toWrite, strlen(toWrite));*/
		m_Writer.write(stringtowrite.c_str(), stringtowrite.size());
	}
}

void BinaryWriter::CloseFile()
{
	m_Exists = false;
	m_Writer.close();
}
/*void BinaryWriter::writeHighScore(std::string name, int score)
{
	highScore ToWrite;
	ToWrite.score = score;
	ToWrite.name = new char[name.size()];
	for (int i{}; i != name.size(); ++i)
	{
		ToWrite.name[i] = name[i];
	}
	ToWrite.name[name.size()] = '\0';
	if (!m_Writer.is_open())
	{
		m_Writer.open(m_filepath, std::ios::out | std::ios::binary);
	}
	if (m_Writer.is_open())
	{
		m_Writer.write((const char*)&ToWrite.score, sizeof(ToWrite.score));
		m_Writer.write(ToWrite.name, strlen(ToWrite.name));
	}
}*/

