#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QResizeEvent>
#include <QDebug>
#include <cmath>

#define DEFAULT_IMAGE_RATIO 1
#define DEFAULT_PROGRESS_BAR_W 873
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
    if (oldSize.width() == -1 || oldSize.height() == -1) {
        return;
    }
    auto newSize = event->size();
    double currentRatio = 1.0;
    if (oldSize.width() != newSize.width()) {
        currentRatio = (double) newSize.width() / DEFAULT_IMAGE_W;
    } else if (oldSize.height() != newSize.height()) {
        currentRatio = (double) newSize.height() / DEFAULT_IMAGE_H;
    } else return;

    resizeText(currentRatio);
    resizeProgressBar(currentRatio);
    resize((int) (currentRatio * DEFAULT_IMAGE_W), (int) (currentRatio * DEFAULT_IMAGE_H));
}

void MainWindow::resizeText(double ratio) {
    auto font = ui->progressText->font();
    font.setPointSize(DEFAULT_TEXT_SIZE * ratio);
    ui->progressText->setFont(font);
}

void MainWindow::resizeProgressBar(double ratio) {
    auto parentView = ui->progressBar->parent();
    if (!parentView->inherits("QFrame")) {
        return;
    }
    int parentWidth = ((QFrame *) parentView)->size().width();
    int progressBarWidth = (int) (ratio * DEFAULT_PROGRESS_BAR_W);
    auto leftOffset = (parentWidth - progressBarWidth) / 2;
    auto geometry = ui->progressBar->geometry();
    auto newGeometry = QRect(leftOffset, geometry.y(), progressBarWidth, geometry.height());
    ui->progressBar->setGeometry(newGeometry);
}

MainWindow::~MainWindow() {
    delete ui;
}

