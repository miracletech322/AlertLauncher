#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QProcess>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    killAlertApp();
    runAlertApp();
    QTimer::singleShot(1000, this, SLOT(slt_timeout()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::killAlertApp()
{
    QProcess taskkill;
    taskkill.start("taskkill", QStringList() << "/F" << "/IM" << "AlertApp.exe");
    taskkill.waitForFinished();
    QString output = taskkill.readAllStandardOutput();
    QString errorOutput = taskkill.readAllStandardError();
    if (!output.isEmpty()) {
        qDebug() << "taskkill output:" << output;
    }
    if (!errorOutput.isEmpty()) {
        qDebug() << "taskkill error:" << errorOutput;
    }
}

void MainWindow::runAlertApp()
{
    QProcess::startDetached("AlertApp.exe");
}

void MainWindow::slt_timeout()
{
    close();
}
