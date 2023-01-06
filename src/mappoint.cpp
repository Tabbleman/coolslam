/**
 *
 *Filename: mappoint.cpp
 *created in 2023/01/06 00:46:15
 *Author: tabbleman
 *
 */
#include "mappoint.h"
#include "feature.h"
namespace coolslam{

MapPoint::MapPoint(size_t id, Vec3 position)
    :id_(id), pos_(position){}

MapPoint::Ptr MapPoint::CreateNewMappoint(){
    static size_t factory_id = 0;
    MapPoint::Ptr new_mappoint(new MapPoint);
    new_mappoint->id_ = factory_id++;
    return new_mappoint;
}

void MapPoint::RemoveObservation(std::shared_ptr<Feature> feature){
    std::unique_lock<std::mutex> lck(data_mutex_);
    for(auto iter = observations_.begin(); iter != observations_.end(); i ++){
        if(iter->lock() == feature){
            observations_.erase(iter);
            feature->map_point_.reset();
            observed_times_ --;
            break;
        }
    }
}

}//end mappoint.cpp