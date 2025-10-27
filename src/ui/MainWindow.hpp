#pragma once

#include <QMainWindow>
#include <QMdiArea>
#include "../core/VulkanContaxt.hpp"

class MainWindow :public QMainWindow {
	Q_OBJECT
public:
	MainWindow(QWidget* parent = nullptr);
	~MainWindow();
private:
	std::shared_ptr<VulkanContaxt> vulkancontaxt;
	QMdiArea* vulkanarea;
	std::vector<std::unique_ptr<VulkanWindow>> vulkanwindows;
	void addVulkanWindow();
protected:
};