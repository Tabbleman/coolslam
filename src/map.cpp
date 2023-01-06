/**
 *
 *Filename: map.cpp
 *created in 2023/01/06 09:16:31
 *Author: tabbleman
 *
 */
#include "map.h"
#include "feature.h"
namespace coolslam{
void Map::InsertKeyFrame(Frame::Ptr frame){
    current_frame_ = frame;
    if(keyframes_.find(frame->keyframe_id_) == keyframes_.end()){
        keyframes_.insert(std::make_pair(frame->keyframe_id_, frame));
        activate_keyframes_.insert(std::make_pair(frame->keyframe_id_, frame));
    }
    else {
        keyframes_[frame->keyframe_id_] = frame;
        activate_keyframes_[frame->keyframe_id_] = frame;
    }
    
    if(activate_keyframes_.size() > num_activate_keyframes_){
        RemoveOldKeyframe();
    }
}

void Map::InsertMapPoint(MapPoint::Ptr map_point){


}

void Map::CleanMap(){
    int cnt_land_mark_removed = 0;
    for(auto iter = activate_landmarks_.begin(); iter != activate_landmarks_.end(); ){
        if(iter->second->observed_times_ == 0){
            iter = activate_landmarks_.erase(iter);
            cnt_land_mark_removed++;
        }
        else iter++;

    }
    LOG(INFO) << "Removed " << cnt_land_mark_removed << " activate landmarks";
}

}//end map.cpp