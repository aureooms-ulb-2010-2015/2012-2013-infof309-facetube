#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "VideoStreamReader.h"
#include "TimeControlWidget.h"
#include "VideoPlayControlsWidget.h"
#include "StreamDisplayer.h"
#include "InputChoiceWidget.h"
#include "ProcessingChoiceWidget.h"
#include "ImageDisplayerWidget.h"
#include "FrameProcessor.h"
#include "VideoStreamProcessor.h"
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
    ProcessingChoiceWidget* _processingChoice;
    int _frameProcessorId;

    void sourceReady();
    FrameProcessor* generateProcessor(int);
    void initProcessingChoices();
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
    void changeFrameProcessorSLOT(int);
    void requestEnterFullScreenSLOT();
    void requestExitFullScreenSLOT();

};

#endif // MAINWINDOW_H
