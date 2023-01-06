#pragma once
/**
 *
 *Filename: frame.h
 *created in 2023/01/05 21:06:59
 *Author: tabbleman
 *
 */
#ifndef FRAME_H
#define FRAME_H
#include "common.h"
#include "camera.h"

namespace coolslam{
struct MapPoint;
struct Feature;

struct Frame
{
public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW
    typedef std::shared_ptr<Frame> Ptr;
    size_t id_ = 0;              //id of the frame
    size_t keyframe_id_ = 0;
    bool is_keyframe_ = false;
    double time_stamp_ = 0.0d;
    SE3 pose_;                  //T cw format
    std::mutex pose_mutex_;
    cv::Mat color_img_, depth_img_;
    std::vector<std::shared_ptr<Feature>> features;

public:
    Frame(){}
    Frame(size_t id, double time_stamp, const SE3 &pose, const Mat &color, const Mat &depth);
    SE3 Pose(){
        std::unique_lock<std::mutex> lck(pose_mutex_);
        return pose_;
    }
    void SetPose(const SE3 &pose){
        std::unique_lock<std::mutex> lck(pose_mutex_);
        pose_ = pose;

    }

    void SetKeyFrame();
    static std::shared_ptr<Frame> CreateFrame();


};


}
#endif //frame.h