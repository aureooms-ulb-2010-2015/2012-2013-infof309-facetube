#ifndef ADDTARGETDIALOG_H
#define ADDTARGETDIALOG_H

#include <QDialog>
#include <QGridLayout>
#include <QLabel>
#include <iostream>
#include <ostream>
#include <fstream>
#include "CustomButton.h"
#include "CustomTextInput.h"
#include "CustomComboBox.h"
#include <QPixmap>
#include "Algorithm_FaceDetector_Surf.h"



class AddTargetDialog : public QDialog {
    Q_OBJECT

private:
    QGridLayout* _layout  = new QGridLayout(this);
    CustomButton* _confirmButton = new CustomButton("Ajouter");
    CustomButton* _cancelButton = new CustomButton("Annuler");
    std::vector<CustomTextInput*> _inputs;
    QString _result;
    FaceDetector_Surf::DetectedFaces _faces;


public:
    explicit AddTargetDialog(const FaceDetector_Surf::DetectedFaces &faces, QWidget *parent = 0);
    virtual QString getResult();
    virtual void accept();
    virtual const FaceDetector_Surf::DetectedFaces& faces(){return _faces;}
    
signals:
    
public slots:
    
};

#endif // ADDTARGETDIALOG_H
