#pragma once

#include <Graphics/Spatial.h>
#include <boost/shared_ptr.hpp>

namespace baselib 
{
	namespace graphics
	{
		class Material;
		class Geometry;
	}
}

namespace baselib 
{
	namespace graphics
	{
		/*! @brief A Visual is Spatial object that can be rendered.
		 *
		 *  A Visual contains everything required to perform a single draw call (i.e. Some kind of Geometry and a Material).
		 */
		class Visual : public Spatial
		{
		public:
			//! Creates a Visual.
			static boost::shared_ptr<Visual> create(const boost::shared_ptr<Geometry>& spGeometry, const boost::shared_ptr<Material>& spMaterial);

			//! Creates a new Visual that references the same geometry and material as this one.
			boost::shared_ptr<Visual> shallowCopy();

			//! Destructor.
			virtual ~Visual();


			//! Getter for setMaterial().
			boost::shared_ptr<Material> getMaterial() const { return m_spMaterial; }
			//! Getter for setGeometry().
			boost::shared_ptr<Geometry> getGeometry() const { return m_spGeometry; }

		protected:
			//! Protected constructor - must be created by static create().
			Visual(const boost::shared_ptr<Geometry>& spGeometry, const boost::shared_ptr<Material>& spMaterial);

		private:
			//! Update the visual - material parameters, dynamic geometry etc.
			virtual void onUpdate(const Mat4& mParent);

			boost::shared_ptr<Material> m_spMaterial;  //!< The material associated with this visual.
			boost::shared_ptr<Geometry> m_spGeometry;  //!< The geometry associated with this visual.

		};
	}
}