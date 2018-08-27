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

#include <functional>
#include "gtest/gtest.h"
#include "src/environment/world/agent.h"
#include "src/environment/observers/observer.h"
#include "src/environment/observers/kin_observer.h"
#include "src/environment/commons/utilities.h"
#include "src/environment/commons/kinematics.h"
#include "src/proto/object.pb.h"


TEST(observer, init) {
    using namespace environment::world;
    using namespace environment::observers;
    using namespace environment::commons;
    using namespace environment::kinematics;

    std::shared_ptr<World> w(new World());
    std::shared_ptr<Agent> a(new Agent());
    std::shared_ptr<Agent> b(new Agent());
    std::shared_ptr<KinematicObserver> o(new KinematicObserver());
    o->set_world(w);

    Matrix_t<double> m(1,4);
    m << 0,0,0,5;
    std::shared_ptr<SingleTrackModel<double>> kin(new SingleTrackModel<double>());
    a->set_state(m);
    PointNd_t<double, 3> p(0,0,0);
    a->set_pose(p);
    a->set_kinematic_model(kin);

    b->set_state(m);
    b->set_pose(p);
    b->set_kinematic_model(kin);

    w->add_object(a);
    w->add_object(b);

    Matrix_t<double> u(1,2);
    u << 0,0;

    std::cout << a->get_state() << std::endl;


    std::pair<int, Agent::StateHistory> h = o->observe( a->step(u, 0.15) );
    std::pair<int, Agent::StateHistory> hb = o->observe( b->step(u, 0.15) );
    std::cout << h.first << std::endl;
    std::cout << hb.first << std::endl;
    std::cout << h.second.state << std::endl;

    

    std::cout << a->get_state() << std::endl;

    ASSERT_TRUE(true);
    //a.step(u, 0.15);
}
