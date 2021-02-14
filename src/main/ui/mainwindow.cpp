#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QResizeEvent>
#include <QDebug>
#include <cmath>

#define DEFAULT_IMAGE_RATIO 1
#define DEFAULT_IMAGE_H 680
#define DEFAULT_IMAGE_W 960
#define DEFAULT_TEXT_SIZE 28

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MainWindow) {
    setBaseSize(DEFAULT_IMAGE_W * DEFAULT_IMAGE_RATIO,
                DEFAULT_IMAGE_H * DEFAULT_IMAGE_RATIO);
    ui->setupUi(this);
    ui->progressBar->setMaximum(0);
    ui->progressBar->setMinimum(0);
    ui->progressBar->setValue(0);
    //auto flags = windowFlags();
    //setWindowFlags(flags | Qt::FramelessWindowHint);
    //ui->progressBar->setContentsMargins(100, 100, 100, 100);
}


bool areDoubleSame(double dFirstVal, double dSecondVal, double maxDiff) {
    return std::fabs(dFirstVal - dSecondVal) < maxDiff;
}

void MainWindow::resizeEvent(QResizeEvent *event) {
    event->accept();

    auto oldSize = event->oldSize();
    auto newSize = event->size();
    double currentRatio = 1.0;
    bool isSizeChanged = false;
    if (oldSize.width() != newSize.width()) {
        currentRatio = (double) newSize.width() / DEFAULT_IMAGE_W;
        auto newHeight = DEFAULT_IMAGE_H * currentRatio;
        QWidget::resize(newSize.width(), newHeight);
        isSizeChanged = true;
    } else if (oldSize.height() != newSize.height()) {
        currentRatio = (double) newSize.height() / DEFAULT_IMAGE_H;
        auto newWidth = DEFAULT_IMAGE_W * currentRatio;
        QWidget::resize(newWidth, newSize.height());
        isSizeChanged = true;
    }

    if (!isSizeChanged) {
        return;
    }

    resizeText(currentRatio);
    resizeProgressBar();
}

void MainWindow::resizeText(double ratio) {
    auto font = ui->progressText->font();
    font.setPointSize(DEFAULT_TEXT_SIZE * ratio);
    ui->progressText->setFont(font);
}

void MainWindow::resizeProgressBar() {

}

MainWindow::~MainWindow() {
    delete ui;
}

