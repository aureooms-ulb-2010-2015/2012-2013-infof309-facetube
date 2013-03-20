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
#include "CustomButton.h"

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
	FaceDetector_Surf* _frameProcessor;
    StreamDisplayer* _displayer;

    VideoPlayControlsWidget* _videoControls;
    ImageDisplayerWidget* _videoFrame;
    QWidget* _upperBar;
	InputChoiceWidget* _inputChoice;
	QPushButton* _addButton = new CustomButton("+");
	QPushButton* _removeButton = new CustomButton("-");
    int _frameProcessorId;

    void sourceReady();
    FaceDetector_Surf* generateProcessor();
    void centerWindow();
	void reloadStream();
	void playPauseToggle();

	int lastDevice;
	QString lastPath;
	int whichLast = -1;

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

    void addTargetPopUpSLOT();
    void removeTargetPopUpSLOT();

};

#endif // MAINWINDOW_H
