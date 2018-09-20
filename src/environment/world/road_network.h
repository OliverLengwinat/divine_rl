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

    /**
     * @brief Create a line object
     * 
     * @param p0 Starting vector
     * @param p1 Ending vector
     * @return Linestring_t<double, 2> returns boost linestring
     */
    Linestring_t<double, 2> create_line(PointNd_t<double, 2> p0, PointNd_t<double, 2> p1){
        Linestring_t<double, 2> line;
        bg::append(line, p0);
        bg::append(line, p1);
        return line;
    };

    /**
     * @brief Create a bezier object
     * 
     * @param p0 Starting vector
     * @param p1 Starting-Handle vector 
     * @param p2 Ending-Handle Vector
     * @param p3 Ending vector
     * @return Linestring_t<double, 2> 
     */
    Linestring_t<double, 2> create_bezier(PointNd_t<double, 2> p0, PointNd_t<double, 2> p1, PointNd_t<double, 2> p2, PointNd_t<double, 2> p3){
        Linestring_t<double, 2> line;
        for(float t = 0; t < 1.0; t+=0.01){
            float p_x = std::pow(1-t, 3) * bg::get<0>(p0) + 3*t*std::pow(1-t, 2)*bg::get<0>(p1) + 3*std::pow(t, 2)*(1-t)*bg::get<0>(p2) + std::pow(t, 3)*bg::get<0>(p3);
            float p_y = std::pow(1-t, 3) * bg::get<1>(p0) + 3*t*std::pow(1-t, 2)*bg::get<1>(p1) + 3*std::pow(t, 2)*(1-t)*bg::get<1>(p2) + std::pow(t, 3)*bg::get<1>(p3);
            bg::append(line, PointNd_t<double, 2>(p_x, p_y));
        }
        return line;
    }


    //! Setter
    /**
     * @brief Set the line segment object
     * 
     * @param idx Id of line
     * @param line geometric definition
     */
    void set_line_segment(int idx, const Linestring_t<double, 2> line) { line_segments_[idx] = line;}

    /**
     * @brief Adds reference road to the network
     * 
     * @param id Id of the reference road
     * @param ref_road Ids of multiple roads that will define the ref.-road
     */
    void add_reference_road(int id, std::vector<int> ref_road){ reference_roads_[id] = ref_road; }

    
    //! Getter
    /**
     * @brief Get the reference road object
     * 
     * @param id 
     * @return std::vector<int> 
     */
    std::vector<int> get_reference_road(int id) const { return reference_roads_.at(id); }

    /**
     * @brief Get the reference roads object
     * 
     * @return std::map<int, std::vector<int>> 
     */
    std::map<int, std::vector<int>> get_reference_roads() const { return reference_roads_; }

    /**
     * @brief Matches a s-value on segments defined in ids
     * 
     * @param ids Road ids
     * @param s arclength on road
     * @return std::pair<int, double> Segment-Id and matched s-value
     */
    std::pair<int, double> get_segment_id(const std::vector<int>& ids, double s) const {
        double s_ = 0.0;
        double s_old = s_;

        for(int id : ids){
            s_old = s_;
            s_ += bg::length(line_segments_.at(id));
            if ( s <= s_)
                return std::make_pair(id, s_old);
        }
        
        return std::make_pair(ids[ids.size()-1], s_old);
    }

    /**
     * @brief Get the line segment object
     * 
     * @param idx 
     * @return Linestring_t<double, 2> 
     */
    Linestring_t<double, 2> get_line_segment(int idx) const { return line_segments_.at(idx); }

    /**
     * @brief Get the line segments object
     * 
     * @return std::map<int, Linestring_t<double, 2>> 
     */
    std::map<int, Linestring_t<double, 2>> get_line_segments() const { return line_segments_; }

private:
    std::map<int, Linestring_t<double, 2>> line_segments_;
    std::map<int, std::vector<int>> reference_roads_;
};

}
}
#endif