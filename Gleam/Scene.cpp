#include "Scene.h"

Scene::Scene() : _renderables(), _lights() {

}

void Scene::addRenderable(Renderable* renderable) {
	_renderables.push_back(renderable);
}

void Scene::removeRenderable(Renderable* renderable) {
	auto itr = std::find(_renderables.begin(), _renderables.end(), renderable);
	if (itr != _renderables.end()) {
		_renderables.erase(itr);
	}
}

std::vector<Renderable*>& Scene::getRenderables() {
	return _renderables;
}

void Scene::addLight(Light* light) {
	_lights.push_back(light);
}

void Scene::removeLight(Light* light) {
	auto itr = std::find(_lights.begin(), _lights.end(), light);
	if (itr != _lights.end()) {
		_lights.erase(itr);
	}
}

std::vector<Light*>& Scene::getLights() {
	return _lights;
}