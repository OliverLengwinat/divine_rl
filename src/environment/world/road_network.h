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

    std::pair<int, double> get_segment_id(std::vector<int> ids, double s){
        double s_ = 0.0;
        for(int id : ids){
            double s_old = s_;
            s_ += bg::length(line_segments_[id]);
            if ( s <= s_)
                return std::make_pair(id, s_old);
        }
        return std::make_pair(0, 0.0);
    }

    void set_line_segment(int idx, const Linestring_t<double, 2> line) { line_segments_[idx] = line;}
    Linestring_t<double, 2> get_line_segment(int idx) const { return line_segments_.at(idx); }
    std::map<int, Linestring_t<double, 2>> get_line_segments() const { return line_segments_; }

    void add_reference_road(int id, std::vector<int> ref_road){ reference_roads_[id] = ref_road; }
    std::vector<int> get_reference_road(int id) { return reference_roads_[id]; }
    std::map<int, std::vector<int>> get_reference_roads() { return reference_roads_; }

private:
    std::map<int, Linestring_t<double, 2>> line_segments_;
    std::map<int, std::vector<int>> reference_roads_;
};

}
}
#endif