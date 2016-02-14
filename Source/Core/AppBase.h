#pragma once

#include <GLFWApp/GLFWApp.h>
#include <memory>

namespace baselib
{
	class ResourceLoader;

	namespace graphics
	{
		class Renderer;
	}
}

namespace baselib
{
	/*! @brief Application base manages all baselib components.
	 *
	 */
	class AppBase : public GLFWApp
	{
	public:
		//! Constructor.
		AppBase();
		//! Destructor.
		virtual ~AppBase();

	protected:
		std::shared_ptr<ResourceLoader> GetResourceLoader() const { return m_spResourceLoader; }

	private:
		void onInit(int iWidth, int iHeight);
		void onDestroy();
		void onUpdate(double dDeltaTime);
		void onRender();
		void onWindowResize(int iWidth, int iHeight);

		virtual void onAppInit() {}
		virtual void onAppDestroy() {}
		virtual void onAppUpdate(double dDeltaTime) {}

		std::shared_ptr<ResourceLoader> m_spResourceLoader;
	};
}