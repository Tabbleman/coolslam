#pragma once
/**
 *
 *Filename: frontend.h
 *created in 2023/01/06 11:44:46
 *Author: tabbleman
 *
 */
#ifndef FRONTEND_H
#define FRONTEND_H
#include "common.h"
#include "frame.h"
#include "map.h"
#include <opencv2/features2d.hpp>

namespace coolslam{
class Backend;
class Viewer;
enum class FrontendStatus {INITING, TRACKING_GOOD, TRACKING_BAD, LOST};
class Frontend{
public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW
    typedef std::shared_ptr<Frontend> Ptr;
    Frontend();
    bool AddFrame(Frame::Ptr);

    void SetMap(Map::Ptr &map){}


private:
    bool Track();

    bool Reset();

    int TrackLastFrame();

    int EstimateCurrentPose();

    bool InsertKeyframe();

    bool RGBDInit();

    int DetectFeatures();

    int FindFeatures();

    bool BuildInitMap();

    void SetObservationsForKeyFrame();

    FrontendStatus status_ = FrontendStatus::INITING;

    Frame::Ptr current_frame_ = nullptr;
    Frame::Ptr last_frame_ = nullptr;
    Camera

};

}
#endif //frontend.h