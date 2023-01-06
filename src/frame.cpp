/**
 *
 *Filename: frame.cpp
 *created in 2023/01/05 21:06:45
 *Author: tabbleman
 *
 */
#include "frame.h"
namespace coolslam{
Frame::Frame(size_t id, double time_stamp, const SE3 &pose, const Mat &color, const Mat &depth)
    :id_(id), time_stamp_(time_stamp), pose_(pose), color_img_(color), depth_img_(depth) {}

Frame::Ptr Frame::CreateFrame(){
    static size_t factory_id = 0;
    Frame::Ptr new_frame(new Frame);
    new_frame->id_ = factory_id++;
    return new_frame;
}

void Frame::SetKeyFrame(){
    static size_t keyframe_factory_id = 0;
    is_keyframe_ = true;
    keyframe_id_ = keyframe_factory_id ++;
}



}//end frame.cpp