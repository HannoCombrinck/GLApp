#pragma once

#include <boost/shared_ptr.hpp>

namespace baselib 
{
	class NullPtr
	{
	public:
		template<class T>
		operator boost::shared_ptr<T>() { return boost::shared_ptr<T>(); }
	} 
	
	extern null_ptr;
}