#include "ModelViewer.h"

#include <Logging/Log.h>

#include <Core/ResourceLoader.h>
#include <Core/NullPtr.h>
#include <boost/filesystem.hpp>

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
