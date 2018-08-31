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

#include "world_bindings.h"
#include "src/environment/world/base_type.h"
#include "src/environment/world/object.h"
#include "src/environment/world/agent.h"
#include "src/environment/world/world.h"
#include "src/environment/world/road_network.h"
#include "src/environment/observers/observer.h"
#include "src/environment/observers/kin_observer.h"

namespace py = pybind11;


void world_bindings(py::module m)
{
    using namespace environment::world;
    using namespace environment::observers;

    py::class_<World, std::shared_ptr<World>>(m, "World")
        .def(py::init<>())
        .def("add_object", &environment::world::World::add_object)
        .def("get_agents", &environment::world::World::get_agents)
        .def("collides", &environment::world::World::collides)
        .def("reset", &environment::world::World::reset)
        .def("set_bounding_box", &environment::world::World::set_bounding_box)
        .def("get_bounding_box", &environment::world::World::get_bounding_box)
        .def("get_objects", &environment::world::World::get_objects);

    py::class_<RoadNetwork, std::shared_ptr<RoadNetwork>>(m, "RoadNetwork")
        .def(py::init<>())
        .def("create_line", &environment::world::RoadNetwork::create_line)
        .def("create_bezier", &environment::world::RoadNetwork::create_bezier);

    py::class_<BaseType, std::shared_ptr<BaseType>>(m, "BaseType")
        .def(py::init<>())
        .def("set_shape", &environment::world::BaseType::set_shape)
        .def("set_shape_offset", &environment::world::BaseType::set_shape_offset)
        .def("get_shape", &environment::world::BaseType::get_shape)
        .def("set_type", &environment::world::BaseType::set_type)
        .def("get_type", &environment::world::BaseType::get_type);

    py::class_<Agent, BaseType, std::shared_ptr<Agent>>(m, "Agent")
        .def(py::init<>())
        .def("set_pose", &environment::world::Agent::set_pose)
        .def("get_pose", &environment::world::Agent::get_pose)
        .def("step", &environment::world::Agent::step)
        .def("get_transformed_shape", &environment::world::Agent::get_transformed_shape)
        .def("get_kinematic_model", &environment::world::Agent::get_kinematic_model)
        .def("set_kinematic_model", &environment::world::Agent::set_kinematic_model);

    py::class_<Object, BaseType, std::shared_ptr<Object>>(m, "Object")
        .def(py::init<>());

    py::class_<StateHistory, std::shared_ptr<StateHistory>>(m, "StateHistory")
        .def(py::init<>())
        .def("is_final", [](const StateHistory& s)
        {
            return s.is_final;
        });

    py::class_<ReplayMemory, std::shared_ptr<ReplayMemory>>(m, "ReplayMemory")
        .def(py::init<>())
        .def("push_back", &environment::observers::ReplayMemory::push_back)
        .def("sample", &environment::observers::ReplayMemory::sample);

    py::class_<BaseObserver, std::shared_ptr<BaseObserver>>(m, "BaseObserver")
        .def("set_world", &environment::observers::BaseObserver::set_world)
        .def_property("memory", &environment::observers::BaseObserver::get_replay_memory, &environment::observers::BaseObserver::set_replay_memory)
        .def("get_world", &environment::observers::BaseObserver::get_world);

    py::class_<KinematicObserver, BaseObserver, std::shared_ptr<KinematicObserver>>(m, "KinematicObserver")
        .def(py::init<>())
        .def("observe", &environment::observers::KinematicObserver::observe);

    
}
