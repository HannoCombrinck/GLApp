#pragma once

#include <Core/AppBase.h>
#include <memory>

namespace tetris
{
	class Tetris : public baselib::AppBase
	{
	public:
		Tetris();
		virtual ~Tetris();

	private:
		void onAppInit() override;
		void onAppUpdate(double dDeltaTime) override;

	};
}