#pragma once
#include "Singleton.h"

namespace dae {
	class Logger : public Singleton<Logger>
	{
	public:
		~Logger() = default;
		void LogError(const std::string& errorMsg);
	};
}

