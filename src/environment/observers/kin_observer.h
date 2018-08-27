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
#include "src/environment/observers/observer.h"

namespace environment {
namespace observers {

class KinematicObserver : public BaseObserver {
public:
    KinematicObserver() {};

    // is_final, reward
    std::pair<int, StateHistory> observe(std::pair<int, StateHistory> s){
        std::shared_ptr<Agent> agent = get_world()->get_agent(s.first);
        std::pair<bool, double> status = get_world()->collides(agent);
        s.second.reward = status.second;
        s.second.is_final = status.first;
        memorize(s.second);
        return s;
    }

};


} // observers
} // environment
#endif