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

#include "src/simulation/commons/common.h"

namespace simulation {
namespace world {

using namespace simulation::commons;

class BaseType {
public:
    BaseType() : status_(Status::NEUTRAL){};
    void set_shape(const Polygon_t<double, 2>& s){ shape_ = s; };
    Polygon_t<double, 2> get_shape() const { return shape_; };
    virtual ~BaseType() = default;

    enum Status {
        NEUTRAL = 0,
        BAD = 1,
        FATAL = 2,
        GOOD = 3,
        AWESOME = 4
    };
    
    Status status_;


private:
    Polygon_t<double, 2> shape_;
};

} // simulation
} // world

#endif // _WORLD_BASE_TYPE_H_