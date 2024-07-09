#pragma once

#include <UIApplicationTools.h>

class #sceneName : public Scene
{
public:
	#sceneName() = default;
	#sceneName(const UIString& name) : Scene(name) {}
	virtual ~#sceneName() override = default;

	virtual void Init() override;
	virtual void Update() override;
};