#pragma once

#include <memory>

namespace baselib 
{
	class NullPtr
	{
	public:
		template<class T>
		operator std::shared_ptr<T>() { return std::shared_ptr<T>(); }
	} 
	
	extern null_ptr;
}