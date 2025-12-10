#include "ResourceManager.hpp"

RS::ResourceManager::ResourceManager() :
	renderpassmanager(*this),
	pipelinelayoutmanager(*this),
	pipelinemanager(*this),
	shadermanager(*this),
	descriptorsetmanager(*this),
	framebuffermanager(*this),
	materialmanager(*this)
{
}
RS::ResourceManager& RS::ResourceManager::setDevice(const vk::Device& device)
{
	this->device = device;
	emit deviceready(device);
	return *this;
}
void RS::ResourceManager::destroy()
{
	descriptorsetmanager.destroy();
	pipelinemanager.destroy();
	pipelinelayoutmanager.destroy();
	shadermanager.destroy();
	renderpassmanager.destroy();
	framebuffermanager.destroy();
}

