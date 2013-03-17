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



class AddTargetDialog : public QDialog {
    Q_OBJECT

private:
    QGridLayout* _layout  = new QGridLayout(this);
    QWidget* _firstLine = new QWidget();

    QHBoxLayout* _firstLineLayout = new QHBoxLayout(this->_firstLine);
    //CustomComboBox* _protocol = new CustomComboBox();
    CustomTextInput* _targetName = new CustomTextInput();
    //CustomTextInput* _port = new CustomTextInput();
    CustomButton* _confirmButton = new CustomButton("Ajouter");
    CustomButton* _cancelButton = new CustomButton("Annuler");

    QString _result;


public:
    explicit AddTargetDialog(QWidget *parent = 0);
    virtual QString getResult();
    virtual void accept();
    
signals:
    
public slots:
    
};

#endif // ADDTARGETDIALOG_H
