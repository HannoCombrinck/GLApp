#pragma once

#include <Core/AppBase.h>
#include <memory>

class ModelViewer : public baselib::AppBase
{
public:
	ModelViewer();
	virtual ~ModelViewer();

private:
	void onAppInit() override;
	void onAppDestroy() override;
	void onAppUpdate(double dDeltaTime) override;

	void onKeyPress(int iKey) override;

	void onFileDrop(const std::vector<std::string>& asPaths) override;

};
