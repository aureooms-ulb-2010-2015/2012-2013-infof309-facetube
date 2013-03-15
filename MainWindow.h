#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "VideoStreamReader.h"
#include "TimeControlWidget.h"
#include "VideoPlayControlsWidget.h"
#include "StreamDisplayer.h"
#include "InputChoiceWidget.h"
#include "ImageDisplayerWidget.h"
#include "VideoStreamProcessor.h"
#include "Algorithm_FaceDetector_Surf.h"
#include <QKeyEvent>

namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget{
    Q_OBJECT

private:

    VideoStreamInfo _streamInfo;

    QWidget* _wraper;
    QGridLayout* _layout;

    VideoStreamReader* _streamReader;
    VideoStreamProcessor* _streamProcessor;
    FrameProcessor* _frameProcessor;
    StreamDisplayer* _displayer;

    VideoPlayControlsWidget* _videoControls;
    ImageDisplayerWidget* _videoFrame;
    QWidget* _upperBar;
    InputChoiceWidget* _inputChoice;
    QWidget* _rightCorner = new QWidget();
    QPushButton* _addButton = new QPushButton("+");
    QPushButton* _removeButton = new QPushButton("-");
    int _frameProcessorId;

    void sourceReady();
    FaceDetector_Surf* generateProcessor();
    void centerWindow();

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    virtual void keyPressEvent(QKeyEvent *);

public slots:
    void requestChangeSourceSLOT(int);
    void requestChangeSourceSLOT(QString);
    void posChangedSLOT(int);
    void timeChangedSLOT(int);
    void requestEnterFullScreenSLOT();
    void requestExitFullScreenSLOT();

    void addTargetSLOT(const QImage& img, const QString& name);
    void removeTargetSLOT(int id);
    void addTargetPopUpSLOT();
    void removeTargetPopUpSLOT();

};

#endif // MAINWINDOW_H
