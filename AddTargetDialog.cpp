#include <QObject>
#include "AddTargetDialog.h"


AddTargetDialog::AddTargetDialog(const QPixmap& img, QWidget *parent) :
	QDialog(parent){
	this->_layout->addWidget(this->_preview,0,0,1,2);
	this->_layout->addWidget(this->_targetName,1,0,1,2);
	this->_layout->addWidget(this->_confirmButton,2,0,1,1);
	this->_layout->addWidget(this->_cancelButton,2,1,1,1);
	this->_preview->setPixmap(img);
	this->_targetName->setPlaceholderText("Nom de la cible");
    QObject::connect(this->_confirmButton, SIGNAL(clicked()), this, SLOT(accept()));
    QObject::connect(this->_cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
}

QString AddTargetDialog::getResult(){
    return this->_result;
}


void AddTargetDialog::accept(){
    QString targetName = this->_targetName->text();
	this->_result = targetName;
    std::string name = targetName.toUtf8().constData();
    std::ofstream target("data/target.txt");
    if (target){
        target << name;
        target.close();
    }else{
        std::cerr<<"\nFile data/target.txt not open\n";
    }
    QDialog::accept();
}
