#include "RemoveTargetDialog.h"
#include <QObject>
#include "Mat2QImage.h"


RemoveTargetDialog::RemoveTargetDialog(const FaceDetector_Surf::Targets& targets, QWidget* parent) :
    QDialog(parent){
    size_t i = 0;
    if(!targets.empty()){
        for(const FaceDetector_Surf::Target& target : targets){


            QLabel* preview = new QLabel(this);
            preview->setPixmap(QPixmap::fromImage(Mat2QImage::exec(target.picture)));
            QLabel* name = new QLabel(target.name.c_str(), this);
            _inputs.push_back(new QCheckBox());

            this->_layout->addWidget(_inputs.at(_inputs.size()-1),0,i+1,1,2);
            this->_layout->addWidget(preview,1,i,1,2);
            this->_layout->addWidget(name,2,i,1,2);
            i += 2;
        }
        i-=2;
        CustomButton* confirmButton = new CustomButton("Supprimer");
        CustomButton* cancelButton = new CustomButton("Annuler");
        this->_layout->addWidget(confirmButton,3,i,1,1);
        this->_layout->addWidget(cancelButton,3,i+1,1,1);
        QObject::connect(confirmButton, SIGNAL(clicked()), this, SLOT(accept()));
        QObject::connect(cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
    }
    else{
        QLabel* msg = new QLabel(this);
        msg->setText("Aucune cible à supprimer.");
		this->_layout->addWidget(msg,0,0,1,3);
        CustomButton* closeButton = new CustomButton("Ok");
		this->_layout->addWidget(closeButton,1,1,1,1);
		this->resize(this->width(), 100);
        QObject::connect(closeButton, SIGNAL(clicked()), this, SLOT(reject()));
    }
	this->setWindowTitle("Facetube - Supprimer une cible");
}


void RemoveTargetDialog::accept(){
    this->_actions.resize(_inputs.size(), false);
    for(size_t i = 0; i < _inputs.size(); ++i){
        this->_actions.at(i) = _inputs.at(i)->isChecked();
    }
    QDialog::accept();
}
