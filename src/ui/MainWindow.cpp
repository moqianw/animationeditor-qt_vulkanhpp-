#include "MainWindow.hpp"
#include <QMdiSubWindow>

MainWindow::MainWindow(QWidget* parent)
{
	try {
		resize(1080, 960);

		vulkanarea = new QMdiArea(this);
		vulkancontaxt = std::make_shared<VulkanContaxt>();
		setCentralWidget(vulkanarea);
		addVulkanWindow();

			

	}
	catch (std::exception e) {
		qDebug() << e.what();
	}

}

MainWindow::~MainWindow()
{
	vulkanwindows.clear();
	
	vulkancontaxt.reset();
}

void MainWindow::addVulkanWindow()
{
	std::unique_ptr<VulkanWindow> window = std::make_unique<VulkanWindow>(vulkancontaxt->getVulkanInstance(), this);
	
	connect(window.get(), &VulkanWindow::surfaceReady, this, [this, win = window.get()](vk::SurfaceKHR surface) {
		vulkancontaxt->initDevice(win->getSurfaceKHR());
		win->setDevice(vulkancontaxt->device).setPhysicalDevice(vulkancontaxt->physicaldevice);
		win->createSwapChain(vulkancontaxt->queuefamilyindices);
		win->createImageView();
		win->createCommandPool();
		});
	QMdiSubWindow* subwindow = new QMdiSubWindow;
	subwindow->setWidget(QWidget::createWindowContainer(window.get()));
	subwindow->setWindowTitle("new1");
	subwindow->resize(800, 600);
	
	vulkanarea->addSubWindow(subwindow);
	subwindow->show();
	vulkanwindows.push_back(std::move(window));
}
