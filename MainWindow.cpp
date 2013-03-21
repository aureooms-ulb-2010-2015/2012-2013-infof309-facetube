#include "MainWindow.h"

#include "AddTargetDialog.h"
#include "RemoveTargetDialog.h"

#include "Algorithm_FaceDetector_Surf.h"

FrameProcessor* MainWindow::generateProcessor(){
    return new FaceDetector_Surf();
}


MainWindow::MainWindow(QWidget *parent) : BasicWindow(parent){

    this->setWindowTitle("FaceTube");

	QGridLayout* upperBarLayout = new QGridLayout(this->_upperBar);
	upperBarLayout->addWidget(this->_inputChoice,0,0,1,2);
	upperBarLayout->addWidget(this->_addButton,0,2,1,1);
	upperBarLayout->addWidget(this->_removeButton,0,3,1,1);

	this->_addButton->setFixedHeight(23);
	this->_addButton->setFont(QFont("Times", 16, QFont::Bold));
	this->_removeButton->setFixedHeight(23);
	this->_removeButton->setFont(QFont("Times", 16, QFont::Bold));
	upperBarLayout->setContentsMargins(0,0,0,0);
	//---------------------------------------

    QObject::connect(this->_addButton, SIGNAL(clicked()), this, SLOT(addTargetPopUpSLOT()));
    QObject::connect(this->_removeButton, SIGNAL(clicked()), this, SLOT(removeTargetPopUpSLOT()));
}

MainWindow::~MainWindow(){}

void MainWindow::keyPressEvent(QKeyEvent* event){

	if(event->key() == Qt::Key_F7){
		return this->addTargetPopUpSLOT();
	}

	else if(event->key() == Qt::Key_F8){
		return this->removeTargetPopUpSLOT();
	}

	return BasicWindow::keyPressEvent(event);
}


void MainWindow::addTargetPopUpSLOT() {
	if(this->getSurfProcessor() == NULL) return;

	FaceDetector_Surf::DetectedFaces faces = this->getSurfProcessor()->getCurrentFaces();
    AddTargetDialog* dialog = new AddTargetDialog(faces,this);

    if (dialog->exec() == QDialog::Accepted) {
        for(size_t i = 0; i < faces.size(); ++i){
            std::cout << faces.at(i).target.name << ", " <<  dialog->faces().at(i).target.name << std::cout;
            if(faces.at(i).target.name != dialog->faces().at(i).target.name && dialog->faces().at(i).target.name != ""){
                if(faces.at(i).isRecognized){
					this->getSurfProcessor()->editTarget(dialog->faces().at(i));
                }
                else{
					this->getSurfProcessor()->addTarget(dialog->faces().at(i).target);
                }
            }
        }
    }
}

void MainWindow::removeTargetPopUpSLOT(){
	if(this->getSurfProcessor() == NULL) return;
	FaceDetector_Surf::Targets targets = this->getSurfProcessor()->getTargets();
    RemoveTargetDialog* dialog = new RemoveTargetDialog(targets, this);
    if (dialog->exec() == QDialog::Accepted) {
        size_t j = 0;
        for(size_t i = 0; i < targets.size(); ++i){
            if(dialog->getActions().at(i)){
				this->getSurfProcessor()->removeTarget(i-j);
                ++j;
            }
        }
	}
}

FaceDetector_Surf* MainWindow::getSurfProcessor(){
	return (FaceDetector_Surf*)this->_frameProcessor;
}
