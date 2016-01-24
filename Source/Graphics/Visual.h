#pragma once

#include <Graphics/Spatial.h>
#include <memory>

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
			static std::shared_ptr<Visual> create(const std::shared_ptr<Geometry>& spGeometry, const std::shared_ptr<Material>& spMaterial);

			//! Creates a new Visual that references the same geometry and material as this one.
			std::shared_ptr<Visual> shallowCopy();

			//! Destructor.
			virtual ~Visual();


			//! Getter for setMaterial().
			std::shared_ptr<Material> getMaterial() const { return m_spMaterial; }
			//! Getter for setGeometry().
			std::shared_ptr<Geometry> getGeometry() const { return m_spGeometry; }

		protected:
			//! Protected constructor - must be created by static create().
			Visual(const std::shared_ptr<Geometry>& spGeometry, const std::shared_ptr<Material>& spMaterial);

		private:
			//! Update the visual - material parameters, dynamic geometry etc.
			virtual void onUpdate(const Mat4& mParent);

			std::shared_ptr<Material> m_spMaterial;  //!< The material associated with this visual.
			std::shared_ptr<Geometry> m_spGeometry;  //!< The geometry associated with this visual.

		};
	}
}