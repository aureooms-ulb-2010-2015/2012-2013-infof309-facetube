#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "BasicWindow.h"
#include "Algorithm_FaceDetector_Surf.h"
#include "CustomButton.h"


class MainWindow : public BasicWindow{
    Q_OBJECT

private:


	FaceDetector_Surf* getSurfProcessor();

	QPushButton* _addButton = new CustomButton("+");
	QPushButton* _removeButton = new CustomButton("-");

	virtual FrameProcessor* generateProcessor();

public:
    explicit MainWindow(QWidget *parent = 0);
	virtual ~MainWindow();
    virtual void keyPressEvent(QKeyEvent *);

public slots:
    void addTargetPopUpSLOT();
    void removeTargetPopUpSLOT();

};

#endif // MAINWINDOW_H
