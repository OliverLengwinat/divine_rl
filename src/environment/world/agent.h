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

#include "src/environment/commons/utilities.h"
#include "src/environment/commons/common.h"
#include "src/environment/dynamics/kinematics.h"
#include "src/environment/world/base_type.h"
#include "src/proto/object.pb.h"

namespace environment {
namespace observers {
    class BaseObserver;
}
namespace world {

using namespace environment::kinematics;
using namespace environment::commons;
using namespace environment::observers;

class Agent : public BaseType {
public:
    Agent() {};

    StepReturn exec_step(const Matrix_t<double>& u, double dt){
        StepReturn sr;
        sr.state = kinematic_model_->get_state();
        sr.action = u;
        kinematic_model_->step(u, dt);
        sr.next_state = kinematic_model_->get_state();
        sr.agent_id = get_id();
        return sr;
    }
    
    std::pair<int, std::function<StepReturn()>> step(const Matrix_t<double>& u, double dt){
        return std::make_pair<int, std::function<StepReturn()>>(get_id(), std::bind(&Agent::exec_step, this, u, dt));
    }

    //! Setter
    void set_kinematic_model(std::shared_ptr<KinematicModel<double>> model){
        kinematic_model_ = model;
    }

    void set_reference_line_id(int id){reference_line_id_=id;}

    //! Getter
    PointNd_t<double, 3> get_pose() const { return kinematic_model_->get_pose(); }

    std::shared_ptr<KinematicModel<double>> get_kinematic_model(){
        return kinematic_model_;
    }

    int get_reference_line_id() const {return reference_line_id_;}

    Polygon_t<double, 2> get_transformed_shape() const {
        PointNd_t<double, 2> p_t;
        bg::set<0>(p_t, bg::get<0>(this->get_pose()));
        bg::set<1>(p_t, bg::get<1>(this->get_pose()));
        Polygon_t<double, 2> tmp_poly = translate<double, 2>(this->get_shape(), this->get_shape_offset());
        return translate<double, 2>(rotate<double, 2>(tmp_poly, bg::get<2>(this->get_pose())), p_t);
    }

private:
    std::shared_ptr<KinematicModel<double>> kinematic_model_;
    int reference_line_id_;
};

} // environment
} // world

#endif //_WORLD_AGENT_H_