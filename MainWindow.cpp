#include "MainWindow.h"

#include <QApplication>
#include <QVBoxLayout>
#include <QDesktopWidget>
#include "Algorithm_NoProcessing.h"
#include "ImageDisplayerWidgetImpl.h"
#include "ImageDisplayerWidgetImpl2.h"
#include "ImageDisplayerWidgetImpl3.h"
#include "AddTargetDialog.h"


#include <stdio.h>

#include "Algorithm_FaceDetector_Surf.h"

//===================================================
// Le seul code auquel il faut toucher pour rajouter des algos à pouvoir exécuter, attention à respecter l'ordre!!

FaceDetector_Surf* MainWindow::generateProcessor(){
    return new FaceDetector_Surf();
}

//===================================================
//Ne pas toucher plus bas si c'est pour rajouter un algo.



void MainWindow::centerWindow(){
    this->show();
    QRect r(this->frameGeometry());
    r.moveCenter(QApplication::desktop()->availableGeometry().center());
    this->move(r.topLeft());
}


MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),_frameProcessorId(0){

    this->setWindowTitle("FaceTube");

    this->_wraper = new QWidget(this);
    this->_wraper->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);


    //--------------------------------------------------------------------
    this->_inputChoice = new InputChoiceWidget();
    this->_upperBar = new QWidget();
	QGridLayout* upperBarLayout = new QGridLayout(this->_upperBar);
	upperBarLayout->addWidget(this->_inputChoice,0,0,1,2);
	upperBarLayout->addWidget(this->_addButton,0,2,1,1);
	upperBarLayout->addWidget(this->_removeButton,0,3,1,1);
    this->_upperBar->setFixedWidth(640);
	this->_upperBar->setFixedHeight(30);
	this->_addButton->setFixedHeight(23);
	this->_addButton->setFont(QFont("Times", 16, QFont::Bold));
	this->_removeButton->setFixedHeight(23);
	this->_removeButton->setFont(QFont("Times", 16, QFont::Bold));
	upperBarLayout->setContentsMargins(0,0,0,0);
    //--------------------------------------------------------------------
    this->_videoFrame = new ImageDisplayerWidgetImpl();
    //--------------------------------------------------------------------
    this->_videoControls = new VideoPlayControlsWidget();
    this->_videoControls->setFixedWidth(640);
    //--------------------------------------------------------------------

    this->_layout = new QGridLayout(this->_wraper);
    this->_layout->addWidget(this->_upperBar,0,0,1,1);
    this->_layout->addWidget(this->_videoFrame,1,0,1,1);
    this->_layout->addWidget(this->_videoControls,2,0,1,1);

    //--------------------------------------------------------------------

    //=================

    this->_streamReader = new VideoStreamReader();
    this->_frameProcessor = NULL;
    this->_streamProcessor = new VideoStreamProcessor(this->_streamReader,this->_frameProcessor);
    this->_displayer = new StreamDisplayer(this->_streamProcessor);


    QObject::connect(this->_inputChoice, SIGNAL(currentSourceChanged(int)), this, SLOT(requestChangeSourceSLOT(int)));
    QObject::connect(this->_inputChoice, SIGNAL(currentSourceChanged(QString)), this, SLOT(requestChangeSourceSLOT(QString)));

    QObject::connect(this->_displayer, SIGNAL(displaySIGNAL(QImage)), this->_videoFrame, SLOT(displayImageSLOT(QImage)));
    QObject::connect(this->_displayer, SIGNAL(posSIGNAL(int)), this, SLOT(posChangedSLOT(int)));


    QObject::connect(this->_videoControls, SIGNAL(pause()), this->_displayer, SLOT(pause()));
    QObject::connect(this->_videoControls, SIGNAL(play()), this->_displayer, SLOT(play()));
    QObject::connect(this->_videoControls, SIGNAL(timeChanged(int)), this, SLOT(timeChangedSLOT(int)));

    QObject::connect(this->_addButton, SIGNAL(clicked()), this, SLOT(addTargetPopUpSLOT()));
    QObject::connect(this->_removeButton, SIGNAL(clicked()), this, SLOT(removeTargetPopUpSLOT()));


    this->setLayout(this->_layout);
    this->_streamProcessor->start();
    this->_displayer->start();


    this->centerWindow();
}

MainWindow::~MainWindow(){
    delete this->_streamReader;
    delete this->_streamProcessor;
    delete this->_frameProcessor;
    delete this->_displayer;
}

void MainWindow::keyPressEvent(QKeyEvent* event){

    if(event->key() == Qt::Key_F11){
        if (!this->isFullScreen()){
            return this->requestEnterFullScreenSLOT();
        }
        else{
            return this->requestExitFullScreenSLOT();
        }
    }
    //DOESNT WORK, DUNNO Y
    else if((event->key() == Qt::Key_F4 && QApplication::keyboardModifiers() == Qt::AltModifier)
            || (event->key() == Qt::Key_W && QApplication::keyboardModifiers() == Qt::ControlModifier)){
        return QCoreApplication::quit();
    }

    return QWidget::keyPressEvent(event);
}

void MainWindow::requestChangeSourceSLOT(int device){
    this->_displayer->pause();
    this->_streamProcessor->stop();
    this->_streamReader->open(device);
    this->sourceReady();
}

void MainWindow::requestChangeSourceSLOT(QString filename){
    this->_displayer->pause();
    this->_streamProcessor->stop();
    this->_streamReader->open(filename);
    this->sourceReady();
}

void MainWindow::sourceReady(){
    delete this->_frameProcessor;
    this->_frameProcessor = this->generateProcessor();
    this->_streamProcessor->reset(this->_streamReader, this->_frameProcessor);
    this->_streamInfo = this->_streamReader->getSourceInfo();
    int totalTime = 0, elapsedTime = 0;
    this->_displayer->setFrameLength((this->_streamInfo.getFps() <= 0)? 40 : 1000/this->_streamInfo.getFps());

    if(this->_streamInfo.isOpen()){
        if(this->_streamInfo.getFps() > 0 && this->_streamInfo.getNumberOfFrames() > 0 && this->_streamInfo.getActualFrameNumber() >= 0){
            totalTime = this->_streamInfo.getNumberOfFrames()/this->_streamInfo.getFps();
            elapsedTime = this->_streamInfo.getActualFrameNumber()/this->_streamInfo.getFps();
        }
    }
    this->_videoControls->setTotalTime(totalTime);
    this->_videoControls->setElapsedTime(elapsedTime);
    this->_videoFrame->reset();
    this->_videoFrame->setDimensions(this->_streamInfo.getFrameHeight(), this->_streamInfo.getFrameWidth());
    this->_displayer->play();
    this->_videoControls->setPlaying();
}


void MainWindow::posChangedSLOT(int pos){
    int elapsedTime = 0;
    if(this->_streamInfo.getFps() > 0 && this->_streamInfo.getNumberOfFrames() > 0 && pos >= 0){
        elapsedTime = pos/this->_streamInfo.getFps();
    }
    this->_videoControls->setElapsedTime(elapsedTime);
}

void MainWindow::timeChangedSLOT(int time){
    this->_streamProcessor->jumpTo(time*this->_streamInfo.getFps());
}

void MainWindow::requestEnterFullScreenSLOT(){
    bool wasPlaying = this->_videoControls->isPlaying();
    if(wasPlaying){
        this->_displayer->pause();
    }
    this->_streamProcessor->stop();
    this->_videoFrame->reset();

    this->_upperBar->hide();
    this->_videoControls->hide();
    this->showFullScreen();
    this->_videoFrame->setMinimumSize(0,0);
    this->_videoFrame->setMaximumSize(QWIDGETSIZE_MAX,QWIDGETSIZE_MAX);
    this->_layout->setContentsMargins(0,0,0,0);

    this->_streamProcessor->reset(this->_streamReader, this->_frameProcessor);
    if(wasPlaying){
        this->_displayer->play();
        this->_videoControls->setPlaying();
    }
}

void MainWindow::requestExitFullScreenSLOT(){
    bool wasPlaying = this->_videoControls->isPlaying();
    if(wasPlaying){
        this->_displayer->pause();
    }
    this->_streamProcessor->stop();
    this->_videoFrame->reset();

    this->showNormal();
    this->_upperBar->show();
    this->_videoControls->show();
    this->_videoFrame->setFixedSize(640,480);
    this->_layout->setContentsMargins(10,10,10,10);

    this->_streamProcessor->reset(this->_streamReader, this->_frameProcessor);
    if(wasPlaying){
        this->_displayer->play();
        this->_videoControls->setPlaying();
    }
}

void MainWindow::addTargetSLOT(const QImage &img, const QString &name)
{
}


void MainWindow::removeTargetSLOT(int id)
{
}

void MainWindow::addTargetPopUpSLOT() {
    /*
    cvNamedWindow( "mywindow", CV_WINDOW_AUTOSIZE );
    IplImage* frame ;//  this->_streamProcessor->getOutPut()[0] ;
    cvShowImage( "mywindow", frame );
    */
	cv::Mat face = this->_frameProcessor->getCurrentFace();
	QImage temp = Mat2QImage::exec(face);
	cv::imwrite("data/target.png", face);
	AddTargetDialog* dialog = new AddTargetDialog(QPixmap::fromImage(temp),this);
	dialog->exec() ;
}

void MainWindow::removeTargetPopUpSLOT()
{
}
