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
#include <QMutex>

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

	typedef std::vector<size_t> RemovedTargets;

private:
    cv::CascadeClassifier _classifier;
    DetectedFaces _currentFaces;
    Targets _allTargets;
    AvailableFlags _availableFlags;
    TrackedFaces _trackedFaces;

    RobustMatcher rmatcher;

	QMutex _currentFacesLock;
	QMutex _allTargetsLock;
	QMutex _trackedFacesLock;

	RemovedTargets _removedDuringProcessing;


	DetectedFace recognize(const cv::Mat& , cv::Rect, const Targets &targets, const TrackedFaces& lastlyTrackedFaces);

public:
    FaceDetector_Surf();
    void process(const cv::Mat &in, cv::Mat &out);

    DetectedFaces getCurrentFaces(){
        this->_currentFacesLock.lock();
        DetectedFaces detectedFaces = this->_currentFaces;
        this->_currentFacesLock.unlock();
        return detectedFaces;
    }

    Targets getTargets(){
        this->_allTargetsLock.lock();
        Targets targets = this->_allTargets;
        this->_allTargetsLock.unlock();
        return targets;
    }

    void addTarget(const Target& target){
        this->_allTargetsLock.lock();
        this->_allTargets.push_back(target);
        this->_allTargetsLock.unlock();
    }

    void removeTarget(size_t index){
        this->_allTargetsLock.lock();
		this->_allTargets.erase(this->_allTargets.begin()+index);
		size_t j = 0;
		this->_trackedFacesLock.lock();
        for(size_t i = 0; i < this->_trackedFaces.size(); ++i){
            if(this->_trackedFaces.at(i-j).index == index){
                this->_trackedFaces.erase(this->_trackedFaces.begin()+i-j);
                ++j;
            }
		}
		this->_removedDuringProcessing.push_back(index);
		this->_trackedFacesLock.unlock();
		this->_allTargetsLock.unlock();
    }

    void editTarget(const DetectedFace& face){
        this->_allTargetsLock.lock();
        this->_allTargets.at(face.index) = face.target;
        this->_allTargetsLock.unlock();
    }

};

#endif // ALGORITHM_FACEDETECTOR_SURF_H
