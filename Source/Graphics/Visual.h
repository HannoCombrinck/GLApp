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
		class Visual : public Spatial
		{
		public:
			//! Constructor.
			Visual();
			//! Destructor.
			~Visual();

			//! Set the material for this visual.
			void setMaterial(const boost::shared_ptr<Material>& spMaterial) { m_spMaterial = spMaterial; }
			//! Getter for setMaterial().
			boost::shared_ptr<Material> getMaterial() const { return m_spMaterial; }

			//! Set the geometry for this visual.
			void setGeometry(const boost::shared_ptr<Geometry>& spGeometry) { m_spGeometry = spGeometry; }
			//! Getter for setGeometry().
			boost::shared_ptr<Geometry> getGeometry() const { return m_spGeometry; }

		private:
			boost::shared_ptr<Material> m_spMaterial;  //!< The material associated with this visual.
			boost::shared_ptr<Geometry> m_spGeometry;  //!< The geometry associated with this visual.

		};
	}
}