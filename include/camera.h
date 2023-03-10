#pragma once
/**
 *
 *Filename: camera.h
 *created in 2023/01/05 20:57:32
 *By tabbleman
 *
 */
#ifndef CAMERA_H
#define CAMERA_H
#include "common.h"
namespace coolslam{
class Camera{
public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW
    typedef std::shared_ptr<Camera> Ptr;

    double  fx_ = 517.306408,
            fy_ = 516.469215,
            cx_ = 318.643040,
            cy_ = 255.313989,
            baseline_ = 0;

    SE3 pose_;
    SE3 pose_inv_;

    Camera();
    Camera(double fx, double fy, double cx, double cy, double baseline
            ,const SE3 &pose):fx_(fx), fy_(fy), cx_(cx), cy_(cy), baseline_(baseline), pose_(pose)
            {pose_inv_ = pose.inverse();}
    SE3 Pose(){return pose_;}
    Mat33 K() const {
        Mat33 k;
        k <<    fx_ , 0    , cx_ 
          ,    0   , fy_  , cy_  
          ,    0   , 0    , 1;
        return k; 
    }
    Vec3 world2camera(const Vec3 &p_w, const SE3 &T_c_w);

    Vec3 camera2world(const Vec3 &p_c, const SE3 &T_c_w);

    Vec2 camera2pixel(const Vec3 &p_c);

    Vec3 pixel2camera(const Vec2 &p_p, double depth = 1);

    Vec3 pixel2world(const Vec2 &p_p, const SE3 &T_c_w, double depth = 1);

    Vec2 world2pixel(const Vec3 &p_w, const SE3 &T_c_w);

};

}
#endif //camera.h