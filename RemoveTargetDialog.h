#ifndef REMOVETARGETDIALOG_H
#define REMOVETARGETDIALOG_H

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
#include <QCheckBox>
#include "Algorithm_FaceDetector_Surf.h"



class RemoveTargetDialog : public QDialog {
    Q_OBJECT
public:

    typedef std::vector<bool> DeleteActions;

private:
    QGridLayout* _layout  = new QGridLayout(this);
    std::vector<QCheckBox*> _inputs;
    DeleteActions _actions;


public:
    explicit RemoveTargetDialog(const FaceDetector_Surf::Targets &targets, QWidget *parent = 0);
    virtual void accept();
    virtual const DeleteActions& getActions(){return _actions;}

signals:

public slots:

};

#endif // REMOVETARGETDIALOG_H
