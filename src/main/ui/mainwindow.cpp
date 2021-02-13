#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QResizeEvent>
#include <QDebug>

#define DEFAULT_IMAGE_RATION 0.6
#define DEFAULT_IMAGE_H (540*DEFAULT_IMAGE_RATION)
#define DEFAULT_IMAGE_W (960*DEFAULT_IMAGE_RATION)

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MainWindow) {
    setBaseSize(DEFAULT_IMAGE_W, DEFAULT_IMAGE_H);
    ui->setupUi(this);
}

void MainWindow::resizeEvent(QResizeEvent *event) {
    event->accept();

    auto oldSize = event->oldSize();
    auto newSize = event->size();
    if (oldSize.width() != newSize.width()) {
        auto currentRatio = (double) newSize.width() / DEFAULT_IMAGE_W;
        auto newHeight = DEFAULT_IMAGE_H * currentRatio;
        QWidget::resize(newSize.width(), newHeight);
    } else if (oldSize.height() != newSize.height()) {
        auto currentRatio = (double) newSize.height() / DEFAULT_IMAGE_H;
        auto newWidth = DEFAULT_IMAGE_W * currentRatio;
        QWidget::resize(newWidth, newSize.height());
    } else {
        qDebug() << "MainWindow: Window not changed";
    }
}

MainWindow::~MainWindow() {
    delete ui;
}

