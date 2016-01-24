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

		std::shared_ptr<graphics::Renderer> m_spRenderer;
		std::shared_ptr<graphics::RenderJob> m_spMainRenderJob;
		std::shared_ptr<graphics::Node> m_spMainScene;
		std::shared_ptr<graphics::Node> m_spLightScene;
		std::shared_ptr<graphics::Shader> m_spLightVolumeShader;
		std::shared_ptr<graphics::Shader> m_spLightAmbientShader;
		std::shared_ptr<graphics::VisualCollector> m_spVisualCollector;
		std::shared_ptr<graphics::Camera> m_spMainCamera;
		std::shared_ptr<graphics::CameraController> m_spCameraController;
		std::shared_ptr<graphics::FrameBuffer> m_spGBuffer;
		std::shared_ptr<graphics::Shader> m_spGBufferShader;
		std::shared_ptr<graphics::Texture> m_spColourTarget1;
		std::shared_ptr<graphics::Texture> m_spColourTarget2;
		std::shared_ptr<graphics::Texture> m_spColourTarget3;
		std::shared_ptr<graphics::Texture> m_spColourTarget4;
		std::shared_ptr<graphics::Texture> m_spDepthTarget;
		std::shared_ptr<graphics::StaticGeometry> m_spQuadGeometry;

		struct LightInfo
		{
			LightInfo(const Vec3& _vColour, float _fSize, const std::shared_ptr<graphics::Visual>& _spVisual)
				: vColour(_vColour)
				, fSize(_fSize)
				, spVisual(_spVisual) {}

			Vec3 vColour;
			float fSize;
			std::shared_ptr<graphics::Visual> spVisual;
		};

		std::vector<LightInfo> m_aLights;

		float m_fAnimSpeed;
		float m_fAmbient;
		int m_iPointLightCount;
	};
}