#pragma once
/**
 *
 *Filename: mappoint.h
 *created in 2023/01/06 00:43:04
 *Author: tabbleman
 *
 */
#ifndef MAPPOINT_H
#define MAPPOINT_H
#include "common.h"
namespace coolslam{

struct Frame;
struct Feature;

/**
 * @brief map point 
 * orb feature will be generate
 * 
 */

struct MapPoint
{
public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW

    typedef std::shared_ptr<MapPoint> Ptr;
    size_t id_ = 0;
    bool is_outer_ = false;
    Vec3 pos_ = Vec3::Zero();
    std::mutex data_mutex_;
    int observed_times_ = 0;
    std::list<std::weak_ptr<Feature>> observations_;

    MapPoint(){}
    MapPoint(size_t id, Vec3 position);

    Vec3 Position(){
        std::unique_lock<std::mutex> lck(data_mutex_);
        return pos_;
    }

    void SetPose(const Vec3 &pos){
        std::unique_lock<std::mutex> lck(data_mutex_);
        pos_ = pos;
    }

    void AddObservation(std::shared_ptr<Feature> feature){
        std::unique_lock<std::mutex> lck(data_mutex_);
        observations_.push_back(feature);
        observed_times_++;
    }

    void RemoveObservation(std::shared_ptr<Feature> &feature);

    std::list<std::weak_ptr<Feature>> GetObs(){
        std::unique_lock<std::mutex> lck(data_mutex_);
        return observations_;
    }

    static MapPoint::Ptr CreateNewMappoint();
};


}
#endif //namespace coolslam