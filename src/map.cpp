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
    if(landmarks_.find(map_point->id_) == landmarks_.end()){
        landmarks_.insert(std::make_pair(map_point->id_, map_point));
        activate_landmarks_.insert(std::make_pair(map_point->id_, map_point));

    }
    else {
        landmarks_[map_point->id_] = map_point;
        activate_keyframes_[map_point->id_] = map_point;
    }

}

void Map::RemoveOldKeyframe(){
    if(current_frame_ == nullptr) return ;
    
    double mindis       = 1<<20 , maxdis    = 0;
    double min_kf_id    = 0     , max_kf_id = 0;
    auto Twc = current_frame_->Pose().inverse();
    
    for(auto &kf: keyframes_){
        if(kf.second == current_frame_)continue;
        auto dis = (kf.second->Pose() * Twc).log().norm();
        if(dis > maxdis){
            maxdis = dis;
            max_kf_id = kf.first;
        }
        if(dis < mindis){
            mindis = dis;
            min_kf_id = kf.first;
        }
    }
    const double min_dis_th = 0.2;
    Frame::Ptr frame_to_remove = nullptr;
    if(mindis < min_dis_th){
        frame_to_remove = keyframes_.at(min_kf_id);

    }
    else {
        frame_to_remove = keyframes_.at(max_kf_id);
    }
    LOG(INFO) << "remove keyframe " << frame_to_remove->keyframe_id_;
    
    activate_keyframes_.erase(frame_to_remove->keyframe_id_);
    for(auto feature: frame_to_remove->features){
        auto mp = feature->map_point_.lock();
        if(mp){
            mp->RemoveObservation(feature);
        }
    }
    CleanMap();

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