#include "Algorithm_FaceDetector_Surf.h"
#include <opencv2/objdetect/objdetect.hpp>
#include <string>
#include <ostream>
#include <iostream>

FaceDetector_Surf::FaceDetector_Surf() {
    std::string filename = "xml/lpbcascade_frontalface.xml";
    if (!this->_classifier.load(filename)) std::cout << "can't load file : " << filename << std::endl;

    // Prepare the matcher
    rmatcher.setConfidenceLevel(0.98);
    rmatcher.setMinDistanceToEpipolar(1.0);
    rmatcher.setRatio(0.65f);

    cv::Ptr<cv::FeatureDetector> pfd = new cv::SurfFeatureDetector(10);
    rmatcher.setFeatureDetector(pfd);
}



void FaceDetector_Surf::process(const cv::Mat &in, cv::Mat &out) {
    this->_allTargetsLock.lock();
    Targets targets = this->_allTargets;
    std::cout << this->_allTargets.size() << std::endl;
    this->_allTargetsLock.unlock();

    _availableFlags.clear();
    _availableFlags.resize(targets.size(), true);

    // Create a new image based on the input image
    out = in.clone();

    // There can be more than one face in an image
    std::vector<cv::Rect> faces;

    // Detect the objects and store them in the sequence
    this->_classifier.detectMultiScale(out, faces, 1.2, 3, CV_HAAR_DO_CANNY_PRUNING, cv::Size(25, 25));

    // Loop the number of faces found.
    for( size_t i = 0; i < faces.size(); ++i )  {
        // Draw the rectangle in the input image
        cv::rectangle( out, faces.at(i), cv::Scalar(255,0,0), 3, 8, 0);
    }

    cv::Point point;
    point.x = 20;
    point.y = 20;

    std::ostringstream faces_;
    faces_ << "Number of Faces : " << faces.size();

    cv::putText(out, faces_.str(), point, cv::FONT_HERSHEY_COMPLEX_SMALL, 0.8, cv::Scalar(255,0,0), 1, CV_AA);

    DetectedFaces detectedFaces;
    TrackedFaces trackedFaces;
    for (const cv::Rect& face : faces){

        DetectedFace detectedFace = recognize(in, face, targets);

        detectedFaces.push_back(detectedFace);
        if(detectedFace.isRecognized){
            cv::Point label;
            label.x = face.tl().x + face.width/2 - detectedFace.target.name.size()*10/2;
            label.y = face.br().y + 10;
            cv::putText(out, detectedFace.target.name, label, cv::FONT_HERSHEY_COMPLEX_SMALL, 0.8, cv::Scalar(255,0,0), 1, CV_AA);

            TrackedFace trackedFace;
            trackedFace.rect = face;
            trackedFace.target = detectedFace.target;
            trackedFace.index = detectedFace.index;

            trackedFaces.push_back(trackedFace);
        }
    }

    this->_currentFacesLock.lock();
    this->_currentFaces = detectedFaces;
    this->_currentFacesLock.unlock();
    this->_trackedFaces = trackedFaces;

    return;
}




FaceDetector_Surf::DetectedFace FaceDetector_Surf::recognize(const cv::Mat &in, cv::Rect roi, const Targets& targets) {


    cv::Point center;
    center.x = roi.x + roi.width/2;
    center.y = roi.y + roi.height/2;

    for(size_t i = 0; i < _trackedFaces.size(); ++i){
        std::cout << "tracking" << std::endl;
        TrackedFace* trackedFace = &_trackedFaces.at(i);
        cv::Point previousCenter;
        previousCenter.x = trackedFace->rect.x + trackedFace->rect.width/2;
        previousCenter.y = trackedFace->rect.y + trackedFace->rect.height/2;

        if(abs(center.x - previousCenter.x) <= 50 && abs(center.y - previousCenter.y) <= 50){
            std::cout << "tracked" << std::endl;
            DetectedFace detectedFace;
            detectedFace.isRecognized = true;
            detectedFace.target = trackedFace->target;
            detectedFace.index = trackedFace->index;
            _availableFlags.at(detectedFace.index) = false;
            return detectedFace;
        }
    }


    Score bestMatch;
    cv::Mat face = in(roi);

    for(size_t i = 0; i < targets.size(); ++i){
        std::cout << "surf[" << i << "]" << std::endl;
        if(!_availableFlags.at(i)) continue;
        std::cout << "available" << std::endl;

        const Target* target =  &targets.at(i);
        cv::Mat model = target->picture;


        // Match the two images
        std::vector<cv::DMatch> matches;
        std::vector<cv::KeyPoint> keypoints1, keypoints2;
        rmatcher.match(model, face ,matches, keypoints1, keypoints2);


        // draw the matches
        /*cv::Mat imageMatches;
        cv::drawMatches(model,keypoints1,          // 1st image and its keypoints
                        face,keypoints2,            // 2nd image and its keypoints
                        matches,                    // the matches
                        imageMatches,               // the image produced
                        cv::Scalar(255,255,255));   // color of the lines*/

        if(matches.size() > bestMatch.first){
            bestMatch = Score(matches.size(), i);
        }
    }

    DetectedFace detectedFace;
    detectedFace.isRecognized = bestMatch.first > 13;
    if(detectedFace.isRecognized){
        detectedFace.target = targets.at(bestMatch.second);
        detectedFace.index = bestMatch.second;
        _availableFlags.at(detectedFace.index) = false;
    }
    else{
        Target target;
        target.picture = face;
        target.name = "Inconnu";
        detectedFace.target = target;
    }

    return detectedFace;
}

