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
			//! Creates a VisualCollector.
			static boost::shared_ptr<VisualCollector> create();

			//! Destructor.
			virtual ~VisualCollector();

			//! Collect visuals from Node hierarchy 
			void collect(const boost::shared_ptr<Node>& spNode);
			//! Clear the list of collected visuals
			void clear();

			//! Get the sorted list of visuals.
			const std::vector<Visual*>& getVisuals() const { return m_apVisuals; }

		protected:
			//! Protected constructor - must be created by static create().
			VisualCollector();

		private:
			//! List of Visuals sorted according to rendering order
			std::vector<Visual*> m_apVisuals; // Using a normal pointer to avoid overhead of locking a weak_ptr for every draw call - look at boost::intrusive as alternative

		};
	}
}