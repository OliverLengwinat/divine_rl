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

namespace simulation {
namespace world {

using namespace simulation::kinematics;

class Agent {
public:
    Agent(int id) : id_(id){};

    //! setter
    void set_shape();
    
    void set_pose();

    void set_state();

    void set_kinematic_model(KinematicModel<double> * model){
        kinematic_model_ = model;
    };

    //! getter
    PointNd_t<double, 3> get_pose() const { return pose_; }
    Matrix_t<double> get_state() const { return state_; }
    Polygon_t<double, 2> get_transformed_shape() const { return shape_; }

private:
    PointNd_t<double, 3> pose_;
    Matrix_t<double> state_;
    Polygon_t<double, 2> shape_;
    int id_;
    KinematicModel<double> * kinematic_model_;
};

} // simulation
} // world

#endif //_WORLD_AGENT_H_