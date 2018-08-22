/*
 * MIT License
 *
 * Copyright (c) 2018 Patrick Hart
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the
 * Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
 * AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH
 * THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
#ifndef _WORLD_AGENT_H_
#define _WORLD_AGENT_H_

#include "src/simulation/commons/common.h"
#include "src/simulation/commons/kinematics.h"
#include "src/simulation/world/base_type.h"

namespace simulation {
namespace world {

using namespace simulation::kinematics;

class Agent : public BaseType {
public:
    Agent(int id) : BaseType(id) {};

    void step(const Matrix_t<double>& u, double dt){
        state_ = this->kinematic_model_->step(state_, u, dt);
        pose_ = this->kinematic_model_->get_pose(state_);
    }

    //! setter
    void set_pose(const PointNd_t<double, 3>& p){ pose_ = p; }

    void set_state(const Matrix_t<double>& s){ state_ = s; }

    void set_kinematic_model(SingleTrackModel<double> * model){
        kinematic_model_ = model;
    }

    //! getter
    PointNd_t<double, 3> get_pose() const { return pose_; }
    Matrix_t<double> get_state() const { return state_; }
    Polygon_t<double, 2> get_transformed_shape() const {
        PointNd_t<double, 2> p_t;
        bg::set<0>(p_t, bg::get<0>(pose_));
        bg::set<1>(p_t, bg::get<1>(pose_));
        return translate<double, 2>(rotate<double, 2>(this->get_shape(), bg::get<2>(pose_)), p_t);
    }

private:
    PointNd_t<double, 3> pose_;
    Matrix_t<double> state_;
    KinematicModel<double> * kinematic_model_;
};

} // simulation
} // world

#endif //_WORLD_AGENT_H_