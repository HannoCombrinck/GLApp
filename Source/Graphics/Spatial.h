#pragma once

#include <string>
#include <Math/Math.h>
#include <boost/function.hpp>
#include <boost/enable_shared_from_this.hpp>

namespace baselib 
{
	namespace graphics
	{
		/*! @brief Base class for any object that has spatial information (i.e. any object that has a position and orientation).
		 *
		 *  Spatials have local and world transformations so they can be organized into a spatial hierarchy.
		 */
		class Spatial : public boost::enable_shared_from_this<Spatial>
		{
		public:
			//! Constructor.
			Spatial();
			//! Destructor.
			virtual ~Spatial();

			//! Update the world transform
			void update(const Mat4& mParent);

			//! Set spatial name.
			void setName(const std::string& sName) { m_sName = sName; }
			//! Get spatial name.
			std::string getName() const { return m_sName; }

			//! Modify the world transform
			Mat4& modifyWorldTransform() { return m_mWorld; }
			//! Get the world transform
			const Mat4& getWorldTransform() const { return m_mWorld; }
			
			//! Modify the local transform
			Mat4& modifyLocalTransform() { return m_mLocal; }
			//! Get the local transform
			const Mat4& getLocalTransform() const { return m_mWorld; }

			//! Set spatial to ignore parent and use local transform as world transform.
			void setUseLocalAsWorld(bool b) { m_bUseLocalAsWorld = b; }
			//! Getter for setUseLocalAsWorld()
			bool getUseLocalAsWorld() const { return m_bUseLocalAsWorld; }

			//! Apply function f to this spatial.
			virtual void traverse(const boost::function<void(const boost::shared_ptr<Spatial>&)>& f);

		private:
			//! Called from update().
			virtual void onUpdate(const Mat4& mParent) {}

			std::string m_sName;		//!< Spatial name.
			Mat4 m_mLocal;				//!< Local space transform.
			Mat4 m_mWorld;				//!< World space transform.
			bool m_bUseLocalAsWorld;	//!< If true the local transform is assigned directly to the world transform during update.
		};
	}
}