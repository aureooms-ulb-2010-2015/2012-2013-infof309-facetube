#ifndef ALGORITHM_FACEDETECTOR_SURF_H
#define ALGORITHM_FACEDETECTOR_SURF_H
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/contrib/detection_based_tracker.hpp>
#include <iostream>
#include <fstream>
#include "FrameProcessor.h"
#include "RobustMatcher.h"
#include <map>

class FaceDetector_Surf : public FrameProcessor {
public:

    typedef struct{
        cv::Mat picture;
        std::string name;
    } Target;

    typedef std::vector<Target> Targets;


    typedef struct{
        Target target;
        bool isRecognized;
        size_t index;
    } DetectedFace;

    typedef std::vector<DetectedFace> DetectedFaces;

    typedef struct{
        Target target;
        cv::Rect rect;
        size_t index;
    } TrackedFace;

    typedef std::vector<TrackedFace> TrackedFaces;

    typedef std::map<size_t, size_t> Scores;
    typedef std::pair<size_t, size_t> Score;
    typedef std::vector<bool> AvailableFlags;

private:
    cv::CascadeClassifier _classifier;
    DetectedFaces _currentFaces;
    Targets _allTargets;
    AvailableFlags _availableFlags;
    TrackedFaces _trackedFaces;

    RobustMatcher rmatcher;


    DetectedFace recognize(const cv::Mat& , cv::Rect);

public:
    FaceDetector_Surf();
    void process(const cv::Mat &in, cv::Mat &out);

    const DetectedFaces& getCurrentFaces(){
        return this->_currentFaces;
    }

    void addTarget(const Target& target){
        this->_allTargets.push_back(target);
    }

    void removeTarget(size_t index){
        this->_allTargets.erase(this->_allTargets.begin()+index);
    }

    void editTarget(const DetectedFace& face){
        this->_allTargets.at(face.index) = face.target;
    }

};

#endif // ALGORITHM_FACEDETECTOR_SURF_H
