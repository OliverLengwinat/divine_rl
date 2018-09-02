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

#ifndef _ANTENNA_OBSERVER_H_
#define _ANTENNA_OBSERVER_H_

#include <functional>
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/geometries/box.hpp>
#include "src/environment/observers/observer.h"

namespace environment {
namespace observers {
namespace bg = boost::geometry;

class AntennaObserver : public BaseObserver {
public:
    AntennaObserver() {};

    Linestring_t<double, 2> create_antenna(Matrix_t<double> vehicle_state, double angle_offset){
        Linestring_t<double, 2> antenna;
        PointNd_t<double, 2> p_start(vehicle_state(0,0), vehicle_state(0,1));
        double dx = 150.0*cos(vehicle_state(0,2) + angle_offset);
        double dy = 150.0*sin(vehicle_state(0,2) + angle_offset);
        PointNd_t<double, 2> p_end(vehicle_state(0,0) + dx, vehicle_state(0,1) + dy);
        bg::append(antenna, p_start);
        bg::append(antenna, p_end);
    }

    Matrix_t<double> convert_state(std::shared_ptr<Agent> a, std::shared_ptr<World> w){
        Matrix_t<double> vehicle_state = a->get_kinematic_model()->get_state();
        PointNd_t<double, 2> center_point(vehicle_state(0,0), vehicle_state(0,1));

        std::vector<Linestring_t<double, 2>> antennas;
        for(float angle = -3.14; angle < 3.14; angle+=0.25){
            Linestring_t<double, 2> local_antenna = create_antenna(vehicle_state, angle);
            double min_dist = 10000;
            /*
            if(environment::commons::collides<double, 2>(this->get_bounding_box(), local_antenna)){
                
            }
            */
        }

    }

    void convert_reward(StepReturn& step_return, std::shared_ptr<Agent> a, std::shared_ptr<World> w){
        //step_return.reward;
    }
};


} // observers
} // environment
#endif