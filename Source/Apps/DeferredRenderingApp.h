#pragma once

#include <GLFWApp/GLFWApp.h>

namespace baselib
{
	namespace graphics
	{
		class Renderer;
		class RenderJob;
		class Node;
		class VisualCollector;
		class Visual;
		class Shader;
		class Camera;
		class CameraController;
		class FrameBuffer;
		class Texture;
		class StaticGeometry;
	}
}

namespace baselib
{
	//! @brief Basic deferred rendering test application
	class DeferredRenderingApp : public GLFWApp
	{
	public:
		DeferredRenderingApp();
		virtual ~DeferredRenderingApp();

	private:
		void onInit(int iWidth, int iHeight);
		void onDestroy();
		void onUpdate(double dDeltaTime);
		void onRender();
		void onWindowResize(int iWidth, int iHeight);

		void onKeyPress(int iKey);
		void onKeyRelease(int iKey);
		void onMouseMoveRel(int iDX, int iDY);

		boost::shared_ptr<graphics::Renderer> m_spRenderer;
		boost::shared_ptr<graphics::RenderJob> m_spMainRenderJob;
		boost::shared_ptr<graphics::Node> m_spMainScene;
		boost::shared_ptr<graphics::Node> m_spLightScene;
		boost::shared_ptr<graphics::Shader> m_spLightVolumeShader;
		boost::shared_ptr<graphics::Shader> m_spLightAmbientShader;
		boost::shared_ptr<graphics::VisualCollector> m_spVisualCollector;
		boost::shared_ptr<graphics::Camera> m_spMainCamera;
		boost::shared_ptr<graphics::CameraController> m_spCameraController;
		boost::shared_ptr<graphics::FrameBuffer> m_spGBuffer;
		boost::shared_ptr<graphics::Shader> m_spGBufferShader;
		boost::shared_ptr<graphics::Texture> m_spColourTarget1;
		boost::shared_ptr<graphics::Texture> m_spColourTarget2;
		boost::shared_ptr<graphics::Texture> m_spColourTarget3;
		boost::shared_ptr<graphics::Texture> m_spColourTarget4;
		boost::shared_ptr<graphics::Texture> m_spDepthTarget;
		boost::shared_ptr<graphics::StaticGeometry> m_spQuadGeometry;

		struct LightInfo
		{
			LightInfo(const Vec3& _vColour, float _fSize, const boost::shared_ptr<graphics::Visual>& _spVisual)
				: vColour(_vColour)
				, fSize(_fSize)
				, spVisual(_spVisual) {}

			Vec3 vColour;
			float fSize;
			boost::shared_ptr<graphics::Visual> spVisual;
		};

		std::vector<LightInfo> m_aLights;

		float m_fAnimSpeed;
		float m_fAmbient;
	};
}