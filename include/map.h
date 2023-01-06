#pragma once
/**
 *
 *Filename: map.h
 *created in 2023/01/06 01:06:41
 *Author: tabbleman
 *
 */
#ifndef MAP_H
#define MAP_H
#include "common.h"
#include "frame.h"
#include "mappoint.h"

namespace coolslam{
class Map{
public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW
    typedef std::shared_ptr<Map> Ptr;
    typedef std::unordered_map<size_t, MapPoint::Ptr> LandmarksType;
    typedef std::unordered_map<size_t, Frame::Ptr> KeyframeType;


    Map(){}
    //insert keyframe
    void InsertKeyFrame(Frame::Ptr frame);

    void InsertMapPoint(MapPoint::Ptr mappoint);

    LandmarksType GetAllMapPoints(){
        std::unique_lock<std::mutex> lck(data_mutex_);
        return landmarks_;
    }

    KeyframeType GetAllFrames(){
        std::unique_lock<std::mutex> lck(data_mutex_);
        return keyframes_;
    }

    LandmarksType GetActivateMapPoints(){
        std::unique_lock<std::mutex> lck(data_mutex_);
        return activate_landmarks_;
    }

    KeyframeType GetActivateKeyframes(){
        std::unique_lock<std::mutex> lck(data_mutex_);
        return activate_keyframes_;
    }
    
    void CleanMap();


private:
    void RemoveOldKeyframe();

    std::mutex data_mutex_;
    LandmarksType landmarks_;
    LandmarksType activate_landmarks_;
    KeyframeType keyframes_;
    KeyframeType activate_keyframes_;

    Frame::Ptr current_frame_ = nullptr;

    int num_activate_keyframes_ = 1;//

};

}
#endif //map.h