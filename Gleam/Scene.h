#pragma once

#include <vector>

#include "Renderable.h"
#include "Light.h"

class Scene {
private:
	std::vector<Renderable*> _renderables;
	std::vector<Light*> _lights

public:
	Scene();

	void addRenderable(Renderable* renderable);
	void removeRenderable(Renderable* renderable);
	std::vector<Renderable*>& getRenderables() const;

	void addLight(Light* light);
	void removeLight(Light* light);
	std::vector<Light*> getLights() const;
};