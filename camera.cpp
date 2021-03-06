#include "camera.h"
#include <QCameraViewfinder>
#include <QMediaRecorder>
#include <QCamera>
#include <QCameraImageCapture>
#include <MapGraphicsView.h>
#include <QStackedWidget>
#include <QStackedLayout>
#include <QGraphicsProxyWidget>
#include <QTimer>
#include <QLabel>
//#include <QApplication>


namespace AutoGPSNAMESPACE{

using namespace EsriRuntimeQt;
Camera::Camera(MapGraphicsView*view) :
    mapGraphicsView(view),
    proxyWidget(NULL),
    captureLabel(NULL),
    stackedWidget(NULL),
    currentIndex(0),
    timer(NULL)
  //    widget(NULL)
{

    proxyWidget = new QGraphicsProxyWidget();

    QWidget *widget = new QWidget();
    proxyWidget->setVisible(false);
    //    widget->setVisible(false);
    QList<QByteArray> devices = QCamera::availableDevices();

    widget->setContentsMargins(0,0,0,0);
    stackedWidget = new QStackedWidget(widget);
    //    stackedWidget->setVisible(false);
    stackedWidget->setContentsMargins(0,0,0,0);

    captureLabel = new QLabel(widget);
    captureLabel->setContentsMargins(0,0,0,0);
    captureLabel->setVisible(false);
    //  QPixmap pix;
    //  pix.load("camera-0-00-18-55");
    //  this->captureLabel->setPixmap(pix);
    foreach(QByteArray byteArray, devices)
    {
        QCameraViewfinder *viewfinder = new QCameraViewfinder(stackedWidget);
        stackedWidget->layout()->addWidget(viewfinder);
        QString description = QCamera::deviceDescription(byteArray);
        cameraDescriptionList.append(description);
        QCamera * camera = new QCamera(byteArray, this);
        camera->setViewfinder(viewfinder);
        camera->setCaptureMode(QCamera::CaptureStillImage);
        this->cameraList.append(camera);
        qDebug()<<"cameraList append"<<this->cameraList.size();
        QCameraImageCapture* imageCapture = new QCameraImageCapture(camera);
        cameraImageCaptureList.append(imageCapture);

        connect(imageCapture, SIGNAL(imageCaptured(int,QImage)), this, SLOT(processCapturedImage(int,QImage)));

    }
    proxyWidget->setWidget(widget);

    proxyWidget->setContentsMargins(0,0,0,0);
    mapGraphicsView->scene()->addItem(proxyWidget);

    if (this->cameraList.size() != 0)
    {
        qDebug()<<"!=0";
        timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), this, SLOT(onTimeout()));
    }
}

Camera::~Camera()
{
    qDebug()<<"~Camera";
    qDeleteAll(cameraList);
    cameraList.clear();
    qDeleteAll(cameraImageCaptureList);
    cameraImageCaptureList.clear();
    map.clear();
}

void Camera::onTimeout()
{

    //    qDebug()<<"onTimeout"<<cameraImageCaptureList.size();
    QTime time = QTime::currentTime();
    QString timeString = time.toString("hh-mm-ss");
    QString dirPath = QCoreApplication::applicationDirPath();
    QDir dir(dirPath);
    if (!dir.exists("cameraFile"))
    {
        dir.mkdir("cameraFile");
    }
    //requestId 每次timeout总是相同，导致无法区分，暂时只能只捕捉当前页面的。

    QCameraImageCapture* capture = cameraImageCaptureList.at(currentIndex);
    QString file = dirPath + "/cameraFile/" + QString::number(currentIndex) + "-" + timeString;
    capture->capture(file);
    //    for (int i = 0; i < cameraImageCaptureList.size(); ++i)
    //    {
    //        QCameraImageCapture* capture = cameraImageCaptureList.at(i);
    //         QString file = "camera-" + QString::number(i) + "-" + timeString;
    //         qDebug()<<"file"<<file;
    //         qDebug()<<"captur4e"<<capture;
    //        int requestId = capture->capture(file);
    //         qDebug()<<"requestId"<<requestId << "currentIdex"<<currentIndex;
    //        map[i] = requestId;
    //    }
    //--------------------------------------------
}

QStringList Camera::getCameraDescriptionList()
{
    return this->cameraDescriptionList;
}

void Camera::setGeometry(const QRectF& rectf )
{

    qDebug()<<"rectf x"<<rectf.height()<<rectf.width();
    this->proxyWidget->setGeometry(rectf);
    QRect rect = rectf.toRect();
    this->stackedWidget->setGeometry(rect);
    this->captureLabel->setGeometry(0,0, rect.width()/2, rect.height() / 2);
}

void Camera::setVisible(bool state)
{
    this->proxyWidget->setVisible(state);
}

void Camera::handleCameraIndexChanged(int  index)
{
    currentIndex = index;
    this->stackedWidget->	setCurrentIndex(index);
}

void Camera::processCapturedImage(int requestId, QImage img)
{
    //    qDebug()<<"processCapturedImage"<<requestId;
    //    int id = map.key(requestId, -1);
    //    if (id == -1)
    //        return;
    //    qDebug()<<"label size"<<captureLabel->size();
    //    qDebug()<<"widget size"<<stackedWidget->size();

    QImage scaledImage = img.scaled(stackedWidget->size()/2,
                                    Qt::KeepAspectRatio,
                                    Qt::SmoothTransformation);
    this->captureLabel->setPixmap(QPixmap::fromImage(scaledImage));
}

void Camera::handleCaptureDisplay(bool state)
{
    this->captureLabel->setVisible(state);
}

void Camera::handleCaptureStart(bool state)
{
    qDebug()<<"handleCaptureStart"<<state;
    if (state)
    {
        qDebug()<<"handleCaptureStart"<<cameraList.size();
        if (cameraList.size() != 0)
        {
            foreach(QCamera* camera, cameraList)
            {
                camera->start();
            }
            timer->start(2000);
        }
    }
    else
    {
        qDebug()<<"handleCaptureStart false";
        if (cameraList.size() != 0)
        {
            foreach(QCamera* camera, cameraList)
            {
                camera->stop();
            }
            timer->stop();
        }
    }
}


}
