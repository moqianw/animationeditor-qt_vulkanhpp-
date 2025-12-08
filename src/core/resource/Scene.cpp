#include "Scene.hpp"

RS::Scene::Scene() :
	pipelinemanager(*this),
	shadermanager(*this),
	descriptorsetmanager(*this)
{
}
RS::Scene& RS::Scene::setDevice(const vk::Device& device)
{
	this->device = device;
	emit deviceready(device);
	return *this;
}
void RS::Scene::destroy()
{
	descriptorsetmanager.destroy();
	pipelinemanager.destroy();
	shadermanager.destroy();
}

