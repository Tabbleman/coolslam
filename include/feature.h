#pragma once
/**
 *
 *Filename: feature.h
 *created in 2023/01/06 00:18:05
 *Author: tabbleman
 *
 */
#ifndef FEATURE_H
#define FEATURE_H
#include "common.h"
#include <memory>
#include <opencv2/features2d.hpp>

namespace coolslam{

struct Frame;
struct MapPoint;

struct Feature{

public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW

    typedef std::shared_ptr<Feature> Ptr;   //frame that hold this feature
    std::weak_ptr<Frame> frame_;            //associate mappoint
    cv::KeyPoint position_;                 //2d extract position
    bool is_outer_ = false;                 //weather this keypoint was abnormal

public:
    Feature(){}
    Feature(std::shared_ptr<Frame> &frame, const cv::KeyPoint &keypoint)
        :frame_(frame), position_(keypoint){}

};

}


#endif //feature.h