#include <QObject>
#include "AddTargetDialog.h"
#include "Mat2QImage.h"


AddTargetDialog::AddTargetDialog(const FaceDetector_Surf::DetectedFaces &faces, QWidget *parent) :
    QDialog(parent), _faces(faces){
    size_t i = 0;
    for(const FaceDetector_Surf::DetectedFace& face : faces){


        QLabel* preview = new QLabel(this);
        _inputs.push_back(new CustomTextInput());

        this->_layout->addWidget(preview,0,i,1,2);
        this->_layout->addWidget(_inputs.at(_inputs.size()-1),1,i+1,1,2);
        preview->setPixmap(QPixmap::fromImage(Mat2QImage::exec(face.target.picture)));
        _inputs.at(_inputs.size()-1)->setPlaceholderText("Nom de la cible");

        if(face.isRecognized){
            _inputs.at(_inputs.size()-1)->setText(QString(face.target.name.c_str()));
        }
        i += 2;
    }

    this->_layout->addWidget(this->_confirmButton,2,i,1,1);
    this->_layout->addWidget(this->_cancelButton,2,i+1,1,1);
    QObject::connect(this->_confirmButton, SIGNAL(clicked()), this, SLOT(accept()));
    QObject::connect(this->_cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
}

QString AddTargetDialog::getResult(){
    return this->_result;
}


void AddTargetDialog::accept(){
    for(size_t i = 0; i < _faces.size(); ++i){
        _faces.at(i).target.name = _inputs.at(i)->text().toStdString();
    }
    QDialog::accept();
}
