#pragma once
//#include <iostream>
#include "GameObject.h"

namespace dae {
	class Command
	{
	public:
		virtual ~Command() {}
		virtual void Execute(std::shared_ptr<GameObject>& object) = 0;
	};
}
