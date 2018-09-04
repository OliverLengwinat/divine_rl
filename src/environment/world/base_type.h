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

#ifndef _WORLD_BASE_TYPE_H_
#define _WORLD_BASE_TYPE_H_

#include "src/environment/commons/common.h"

namespace environment {
namespace world {

using namespace environment::commons;

class BaseType {
public:
    BaseType() : shape_offset_(PointNd_t<double, 2>(0,0)), id_(0), reward_(0.0) {};
    
    virtual ~BaseType() = default;

    //! Setter
    void set_id(int id){id_=id;};

    void set_type(int type){ type_=type; };

    void set_reward(double reward){reward_=reward;};

    void set_shape(const Polygon_t<double, 2>& s){ shape_ = s; };

    void set_shape_offset(const PointNd_t<double, 2>& s){ shape_offset_ = s; };

    //! Getter
    double get_reward() const { return reward_; };

    int get_type() const { return type_; };

    int get_id() const { return id_; };

    Polygon_t<double, 2> get_shape() const { return shape_; };

    PointNd_t<double, 2> get_shape_offset() const { return shape_offset_; };

private:
    Polygon_t<double, 2> shape_;
    PointNd_t<double, 2> shape_offset_;
    int id_;
    double reward_;
    int type_;
};

} // environment
} // world

#endif // _WORLD_BASE_TYPE_H_