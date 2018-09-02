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

#ifndef _WORLD_ROAD_NETWORK_
#define _WORLD_ROAD_NETWORK_
#include <cmath>

#include "src/environment/commons/common.h"

namespace environment {
namespace world {

using namespace environment::commons;
using namespace boost; 

class RoadNetwork {
public:

    Linestring_t<double, 2> create_line(PointNd_t<double, 2> p0, PointNd_t<double, 2> p1){
        Linestring_t<double, 2> line;
        bg::append(line, p0);
        bg::append(line, p1);
        return line;
    };

    Linestring_t<double, 2> create_bezier(PointNd_t<double, 2> p0, PointNd_t<double, 2> p1, PointNd_t<double, 2> p2, PointNd_t<double, 2> p3){
        Linestring_t<double, 2> line;
        for(float t = 0; t < 1.0; t+=0.01){
            float p_x = std::pow(1-t, 3) * bg::get<0>(p0) + 3*t*std::pow(1-t, 2)*bg::get<0>(p1) + 3*std::pow(t, 2)*(1-t)*bg::get<0>(p2) + std::pow(t, 3)*bg::get<0>(p3);
            float p_y = std::pow(1-t, 3) * bg::get<1>(p0) + 3*t*std::pow(1-t, 2)*bg::get<1>(p1) + 3*std::pow(t, 2)*(1-t)*bg::get<1>(p2) + std::pow(t, 3)*bg::get<1>(p3);
            bg::append(line, PointNd_t<double, 2>(p_x, p_y));
        }
        return line;
    }

private:
    int road_graph_;

};

}
}
#endif