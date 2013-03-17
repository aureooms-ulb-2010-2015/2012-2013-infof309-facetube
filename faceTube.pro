#-------------------------------------------------
#
# Project created by QtCreator 2012-12-13T11:16:05
#
#-------------------------------------------------

QT       += core gui opengl
ICON = img/play_icon.png

#for c++ 11 support
QMAKE_CXXFLAGS += -std=c++0x

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = faceTube
TEMPLATE = app

CONFIG += link_pkgconfig
PKGCONFIG += opencv
LIBS += -lv4l2 -lX11
#LIBS += -lwavelet2d -Lwavelet2s

INCLUDEPATH += /usr/local/lib/

SOURCES += \
    MainWindow.cpp \
    Main.cpp \
    TimeControlWidget.cpp \
    VideoPlayControlsWidget.cpp \
    PlayPauseButtonWidget.cpp \
    SwaperWidget.cpp \
    TimeDisplayerWidget.cpp \
    InputChoiceWidget.cpp \
    NetworkStreamInputDialog.cpp \
    CustomButton.cpp \
    CustomTextInput.cpp \
    CustomComboBox.cpp \
    ProcessingChoiceWidget.cpp \
    VideoStreamProcessor.cpp \
    Mat2QImage.cpp \
    Algorithm_NoProcessing.cpp \
    ImageDisplayerWidgetImpl.cpp \
    ImageDisplayerWidgetImpl2.cpp \
    OpenCV_GLWidget.cpp \
    ImageDisplayerWidgetImpl3.cpp \
    OpenCV_SynchronizedGLWidget.cpp \
    GLWidgetRenderingThread.cpp \
    Algorithm_FaceDetector_Surf.cpp \
    RobustMatcher.cpp \
    AddTargetDialog.cpp

HEADERS += \
    MainWindow.h \
    VideoStreamReader.h \
    Stream.h \
    VideoStreamInfo.h \
    TimeControlWidget.h \
    VideoPlayControlsWidget.h \
    PlayPauseButtonWidget.h \
    SwaperWidget.h \
    TimeDisplayerWidget.h \
    StreamDisplayer.h \
    InputChoiceWidget.h \
    NetworkStreamInputDialog.h \
    CustomButton.h \
    CustomTextInput.h \
    CustomComboBox.h \
    ProcessingChoiceWidget.h \
    ImageDisplayerWidget.h \
    FrameProcessor.h \
    VideoStreamProcessor.h \
    Mat2QImage.h \
    Algorithm_NoProcessing.h \
    ImageDisplayerWidgetImpl.h \
    ImageDisplayerWidgetImpl2.h \
    OpenCV_GLWidget.h \
    ImageDisplayerWidgetImpl3.h \
    OpenCV_SynchronizedGLWidget.h \
    GLWidgetRenderingThread.h \
    VideoCaptureDeviceDetectorForLinux.h \
    VideoCaptureDeviceDetector.h \
    Algorithm_FaceDetector_Surf.h \
    RobustMatcher.h \
    AddTargetDialog.h

RESOURCES += img.qrc \
    img.qrc

OTHER_FILES += \
    qss/timeControlSlider.qss\
    qss/QComboBox.qss\
    img/play_icon.png\
    img/pause_icon.png \
    qss/QComboBoxDropDown.qss \
    xml/facedata.xml \
    xml/haarcascade_frontalface_alt.xml \
    xml/haarcascade_frontalface_default.xml \
    xml/lpbcascade_frontalface.xml \
    xml/haarcascade_eye_tree_eyeglasses.xml \
    data/greyfish.png \
    utils/sample.py \
    data/bigfish.png \
    data/yellowfish.png \
    data/target.txt
