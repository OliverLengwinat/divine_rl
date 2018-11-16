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

#ifndef _KIN_OBSERVER_H_
#define _KIN_OBSERVER_H_

#include <functional>
#include <cmath>
#include "src/environment/observers/observer.h"
#include "src/environment/commons/common.h"


namespace environment {
namespace observers {

using namespace environment::commons;


class KinematicObserver : public BaseObserver {
public:
    KinematicObserver() {
        Matrix_t<int> mat(1, 1);
        mat << 3;
        this->set_shape(mat);
    };

    /**
     * @brief Overloaded state-converter
     * 
     * @param a agent we are planning for
     * @return Matrix_t<double> returns the concatenated states of all vehicles
     */
    Matrix_t<double> convert_state(std::shared_ptr<Agent> a){
        std::vector<std::shared_ptr<Agent>> agents = get_world()->get_agents();
        int total_cols = 0;
        for (auto agent : agents){
            total_cols += agent->get_kinematic_model()->get_state().cols();
        }
        Matrix_t<double> concatenated_state = Matrix_t<double>(1, total_cols);
        int running_idx = 0;
        for (auto agent : agents){
            Matrix_t<double> vehicle_state = agent->get_kinematic_model()->get_state();
            for(int i = 0; i < vehicle_state.cols(); i++){
                concatenated_state(running_idx) = vehicle_state(i);
                running_idx++;
            }
        }
        return concatenated_state;
    }

    /**
     * @brief Overloaded reward-converter
     * 
     * @param step_return 
     * @param a 
     */
    void convert_reward(StepReturn& step_return, std::shared_ptr<Agent> a, CollisionWith is_colliding){
        //! e.g. the deviation of the desired speed
        Matrix_t<double> vehicle_state = a->get_kinematic_model()->get_state();

        //! negative reward for hitting other objects
        if(is_colliding == CollisionWith::OBJECT || is_colliding == CollisionWith::AGENT){
            step_return.reward -= 1.0;
        }

        //! positive reward when goal is reached
        if(is_colliding == CollisionWith::GOAL)
            step_return.reward += 1.0;

        //! velocity bounds
        if(vehicle_state(1) < 0.0 || vehicle_state(1) > 20.0){
            step_return.reward -= 1.0;
        }

        //! deviation of desired speed
        double sq_v_dist = std::sqrt((vehicle_state(1) - 10.0)*(vehicle_state(1) - 10.0));
        if (sq_v_dist < 2.0){
            step_return.reward += 0.01;
        } else {
            step_return.reward -= 0.01;
        }
        
    }


};


} // observers
} // environment
#endif