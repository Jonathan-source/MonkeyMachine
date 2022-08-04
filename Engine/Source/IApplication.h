#pragma once

#include <iostream>

namespace MonkeyMachine
{
	class ENGINE_API IApplication
	{
	public:
		void Print() { std::cout << "Hello World!" << std::endl; }
	};

} // end of namespace