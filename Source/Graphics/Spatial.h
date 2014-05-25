#pragma once

#include <string>
#include <Math/Math.h>

namespace baselib 
{
	namespace graphics
	{
		class Spatial
		{
		public:
			//! Constructor
			Spatial();
			//! Destructor
			~Spatial();

			//! Update the world transform
			void update(const Mat4& mParent);

			//! Set spatial name.
			void setName(const std::string& sName) { m_sName = sName; }
			//! Get spatial name.
			std::string getName() const { return m_sName; }

			//! Modify the world transform
			Mat4& modifyWorld() { return m_mWorld; }
			//! Get the world transform
			const Mat4& getWorld() const { return m_mWorld; }
			
			//! Modify the local transform
			Mat4& modifyLocal() { return m_mLocal; }
			//! Get the local transform
			const Mat4& getLocal() const { return m_mWorld; }

			//! Set spatial to ignore parent and use local transform as world transform.
			void setUseLocalAsWorld(bool b) { m_bUseLocalAsWorld = b; }
			//! Getter for setUseLocalAsWorld()
			bool getUseLocalAsWorld() const { return m_bUseLocalAsWorld; }

		private:
			std::string m_sName;		//!< Spatial name.
			Mat4 m_mLocal;				//!< Local space transform.
			Mat4 m_mWorld;				//!< World space transform.
			bool m_bUseLocalAsWorld;	//!< If true the local transform is assigned directly to the world transform during update.
		};
	}
}