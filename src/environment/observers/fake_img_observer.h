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

#ifndef _FAKE_IMG_OBSERVER_H_
#define _FAKE_IMG_OBSERVER_H_

#include <functional>
#include "src/environment/observers/observer.h"
#include "src/environment/commons/common.h"

namespace environment {
namespace observers {

using namespace environment::commons;

class KinematicObserver : public BaseObserver {
public:
    KinematicObserver() {};

    Matrix_t<double> convert_state(std::shared_ptr<Agent> a){
		Matrix_t<double> mat(84,84);
        return mat;
    }

    void convert_reward(StepReturn& step_return, std::shared_ptr<Agent> a, CollisionWith is_colliding){
        //step_return.reward;
    }
};


} // observers
} // environment
#endif // _FAKE_IMG_OBSERVER_H_