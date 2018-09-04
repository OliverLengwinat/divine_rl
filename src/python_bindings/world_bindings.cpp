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
        .def("set_road_network", &environment::world::World::set_road_network)
        .def("get_road_network", &environment::world::World::get_road_network)
        .def("collides", &environment::world::World::collides)
        .def("reset", &environment::world::World::reset)
        .def("set_bounding_box", &environment::world::World::set_bounding_box)
        .def("get_bounding_box", &environment::world::World::get_bounding_box)
        .def("get_objects", &environment::world::World::get_objects);

    py::class_<RoadNetwork, std::shared_ptr<RoadNetwork>>(m, "RoadNetwork")
        .def(py::init<>())
        .def("create_line", &environment::world::RoadNetwork::create_line)
        .def("set_line_segment", &environment::world::RoadNetwork::set_line_segment)
        .def("get_line_segment", &environment::world::RoadNetwork::get_line_segment)
        .def("get_line_segments", &environment::world::RoadNetwork::get_line_segments)
        .def("add_reference_road", &environment::world::RoadNetwork::add_reference_road)
        .def("get_reference_road", &environment::world::RoadNetwork::get_reference_road)
        .def("create_bezier", &environment::world::RoadNetwork::create_bezier);

    py::class_<BaseType, std::shared_ptr<BaseType>>(m, "BaseType")
        .def(py::init<>())
        .def("set_shape", &environment::world::BaseType::set_shape)
        .def("set_shape_offset", &environment::world::BaseType::set_shape_offset)
        .def("get_shape_offset", &environment::world::BaseType::get_shape_offset)
        .def("get_shape", &environment::world::BaseType::get_shape)
        .def("set_id", &environment::world::Agent::set_id)
        .def("get_id", &environment::world::Agent::get_id)
        .def("set_reward", &environment::world::Agent::set_reward)
        .def("set_type", &environment::world::BaseType::set_type)
        .def("set_properties", &environment::world::BaseType::set_properties)
        .def("get_properties", &environment::world::BaseType::get_properties)
        .def("get_type", &environment::world::BaseType::get_type);

    py::class_<Agent, BaseType, std::shared_ptr<Agent>>(m, "Agent")
        .def(py::init<>())
        .def("get_pose", &environment::world::Agent::get_pose)
        .def("step", &environment::world::Agent::step)
        .def("set_reference_line_id", &environment::world::Agent::set_reference_line_id)
        .def("get_reference_line_id", &environment::world::Agent::get_reference_line_id)
        .def("get_transformed_shape", &environment::world::Agent::get_transformed_shape)
        .def("get_kinematic_model", &environment::world::Agent::get_kinematic_model)
        .def("set_kinematic_model", &environment::world::Agent::set_kinematic_model);

    py::class_<Object, BaseType, std::shared_ptr<Object>>(m, "Object")
        .def(py::init<>());

    py::class_<Memory, std::shared_ptr<Memory>>(m, "Memory")
        .def(py::init<>())
        .def_property_readonly("states", [](const Memory& s)
        {
            return s.states;
        })
        .def_property_readonly("is_final", [](const Memory& s)
        {
            return s.is_final;
        })
        .def_property_readonly("next_states", [](const Memory& s)
        {
            return s.next_states;
        })
        .def_property_readonly("rewards", [](const Memory& s)
        {
            return s.rewards;
        })
        .def_property_readonly("actions", [](const Memory& s)
        {
            return s.actions;
        });

    py::class_<StepReturn, std::shared_ptr<StepReturn>>(m, "StepReturn")
        .def(py::init<>())
        .def_property_readonly("state", [](const StepReturn& s)
        {
            return s.state;
        })
        .def_property_readonly("next_state", [](const StepReturn& s)
        {
            return s.next_state;
        })
        .def_property_readonly("reward", [](const StepReturn& s)
        {
            return s.reward;
        })
        .def_property_readonly("action", [](const StepReturn& s)
        {
            return s.action;
        })
        .def_property_readonly("is_final", [](const StepReturn& s)
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
        .def("get_world", &environment::observers::BaseObserver::get_world)
        .def("get_state", &environment::observers::BaseObserver::convert_state)
        .def("observe", &environment::observers::KinematicObserver::observe);

    py::class_<KinematicObserver, BaseObserver, std::shared_ptr<KinematicObserver>>(m, "KinematicObserver")
        .def(py::init<>());

}
