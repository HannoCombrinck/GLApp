#include "ModelViewer.h"

#include <Logging/Log.h>

#include <Core/ResourceLoader.h>
#include <Core/NullPtr.h>
#include <boost/filesystem.hpp>

#include <Graphics/Node.h>

namespace fs = boost::filesystem;

using namespace baselib;

ModelViewer::ModelViewer()
{
	LOG_INFO << "ModelViewer constructor";
}

ModelViewer::~ModelViewer()
{
	LOG_INFO << "ModelViewer destructor";
}

void ModelViewer::onAppInit()
{
	LOG_INFO << "ModelViewer init";
}

void ModelViewer::onAppDestroy()
{
	LOG_INFO << "ModelViewer destroy";
}

void ModelViewer::onAppUpdate(double dDeltaTime)
{
	auto dt = dDeltaTime;
}

void ModelViewer::onKeyPress( int iKey )
{
	LOG_INFO << iKey;
}

void ModelViewer::onFileDrop(const std::vector<std::string>& asPaths)
{
	LOG_INFO << "Importing files:";
	for (auto i = asPaths.begin(); i != asPaths.end(); ++i)
	{
		LOG_INFO << "\t" << (*i);
		auto sModelPath = *i;
		auto spModel = getResourceLoader()->load<graphics::Node>(sModelPath);
	}
}
