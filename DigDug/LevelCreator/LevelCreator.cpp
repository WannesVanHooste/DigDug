// LevelCreator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <vector>
#include "BinaryWriter.h"
#include "BinaryReader.h"

std::vector<bool> m_Blocks;
int mapRows{};
int mapCols{};

void AddTunnel(int col, int row, int size, bool isHorizontal) {
	if (isHorizontal) {
		if (row * mapCols + col + size <= int(m_Blocks.size()))
		{
			for (int i{ 0 }; i < size; ++i) {
				m_Blocks[row * 14 + col + i] = true;
			}
		}
	}
	else {
		if (row * mapCols + col + (size * mapCols) <= int(m_Blocks.size()))
		{
			for (int i{ 0 }; i < size; ++i) {
				m_Blocks[row * 14 + col + (i * 14)] = true;
			}
		}
	}
}

int main()
{

    std::cout << "Give map rows: ";
	std::cin >> mapRows;
	std::cout << "Give map cols: ";
	std::cin >> mapCols;
	for(int i{}; i < mapRows * mapCols; ++i) {
		m_Blocks.push_back(false);
	}

	//add tunnels for the game here
	AddTunnel(4, 0, 11, false);
	AddTunnel(4, 5, 7, true);
	AddTunnel(0, 10, 7, true);

	BinaryWriter writer{ "../Data/Levels/level1.bin" };
	for (unsigned int i{}; i < m_Blocks.size(); ++i)
	{
		writer.Write<bool>(m_Blocks[i]);
	}
	writer.CloseFile();

	//BinaryReader reader{ "level1.bin" };
	//for(unsigned int i{}; i < m_Blocks.size(); ++i) {
	//	std::cout << reader.Read<bool>() << "\n";
	//}
	//reader.CloseFile();
}
