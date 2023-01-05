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
    size_t id = 0;          //id of the frame
    size_t keyframe_id = 0;
    bool is_keyframe = false;
    double time_stamp = 0.0d;


public:
    Frame(){}



};


}
#endif //frame.h