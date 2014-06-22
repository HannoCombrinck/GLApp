#pragma once

#include <boost/shared_ptr.hpp>
#include <vector>

namespace baselib 
{
	namespace graphics
	{
		class Node;
		class Visual;
	}
}

namespace baselib 
{
	namespace graphics
	{
		/*! @brief VisualCollector 
		 *
		 */
		class VisualCollector
		{
		public:
			//! Constructor.
			VisualCollector();
			//! Destructor.
			virtual ~VisualCollector();

			//! Collect visuals from Node hierarchy 
			void collect(const boost::shared_ptr<Node>& spNode);

			//! Get the sorted list of visuals.
			const std::vector<Visual*>& getVisuals() const { return m_apVisuals; }

		private:
			//! List of Visuals sorted according to rendering order
			std::vector<Visual*> m_apVisuals; // Using a normal pointer to avoid overhead of locking a weak_ptr for every draw call - look at boost::intrusive as alternative

		};
	}
}