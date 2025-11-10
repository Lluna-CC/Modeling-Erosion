#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "scenebase.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->actionCameraReset, SIGNAL(triggered()), ui->openGLWidget, SLOT(resetCamera()));
    connect(ui->actionCameraX, SIGNAL(triggered()), ui->openGLWidget, SLOT(cameraViewX()));
    connect(ui->actionCameraY, SIGNAL(triggered()), ui->openGLWidget, SLOT(cameraViewY()));
    connect(ui->actionCameraZ, SIGNAL(triggered()), ui->openGLWidget, SLOT(cameraViewZ()));

    connect(ui->actionSceneBase,   &QAction::triggered, this, [=](void){ changeScene(new SceneBase()); });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeScene(Scene* sc)
{
    // First set scene to glwidget. This will trigger deleting old scene and its associated widget.
    // Otherwise, qDeleteAll deletes the widget first, and then the scene destructor crashes
    ui->openGLWidget->setScene(sc);
    qDeleteAll(ui->controlsScene->findChildren<QWidget *>(QString(), Qt::FindDirectChildrenOnly));
    ui->controlsScene->layout()->addWidget(sc->sceneUI());
}
