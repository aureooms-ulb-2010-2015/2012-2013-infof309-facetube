#include <QObject>
#include "AddTargetDialog.h"
#include "Mat2QImage.h"


AddTargetDialog::AddTargetDialog(const FaceDetector_Surf::DetectedFaces &faces, QWidget *parent) :
    QDialog(parent), _faces(faces){
    size_t i = 0;
    if(!faces.empty()){
        for(const FaceDetector_Surf::DetectedFace& face : faces){


            QLabel* preview = new QLabel(this);
            _inputs.push_back(new CustomTextInput());

            this->_layout->addWidget(preview,0,i,1,2);
            this->_layout->addWidget(_inputs.at(_inputs.size()-1),1,i,1,2);
            preview->setPixmap(QPixmap::fromImage(Mat2QImage::exec(face.target.picture)));
            _inputs.at(_inputs.size()-1)->setPlaceholderText("Nom de la cible");

            if(face.isRecognized){
                _inputs.at(_inputs.size()-1)->setText(QString(face.target.name.c_str()));
            }
            i += 2;
        }
        i-=2;
        CustomButton* confirmButton = new CustomButton("Ajouter");
        CustomButton* cancelButton = new CustomButton("Annuler");
        this->_layout->addWidget(confirmButton,2,i,1,1);
        this->_layout->addWidget(cancelButton,2,i+1,1,1);
        QObject::connect(confirmButton, SIGNAL(clicked()), this, SLOT(accept()));
        QObject::connect(cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
    }
    else{
        QLabel* msg = new QLabel(this);
        msg->setText("Aucun visage détecté.");
        this->_layout->addWidget(msg,0,0,1,1);
        CustomButton* closeButton = new CustomButton("Ok");
        this->_layout->addWidget(closeButton,1,0,1,1);
        QObject::connect(closeButton, SIGNAL(clicked()), this, SLOT(reject()));
    }
}


void AddTargetDialog::accept(){
    for(size_t i = 0; i < _faces.size(); ++i){
        _faces.at(i).target.name = _inputs.at(i)->text().toStdString();
    }
    QDialog::accept();
}
