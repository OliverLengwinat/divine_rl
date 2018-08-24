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

namespace py = pybind11;


void world_bindings(py::module m)
{
    using namespace environment::world;

    py::class_<World, std::shared_ptr<World>>(m, "World")
        .def(py::init<>())
        .def("add_object", &environment::world::World::add_object)
        .def("get_agents", &environment::world::World::get_agents)
        .def("collides", &environment::world::World::collides)
        .def("load_proto", &environment::world::World::load_proto)
        .def("get_objects", &environment::world::World::get_objects);


    py::class_<BaseType, std::shared_ptr<BaseType>>(m, "BaseType")
        .def(py::init<>());

    py::class_<Agent, BaseType, std::shared_ptr<Agent>>(m, "Agent")
        .def(py::init<>())
        .def("set_state", &environment::world::Agent::set_state)
        .def("set_shape", &environment::world::Agent::set_shape)
        .def("set_pose", &environment::world::Agent::set_pose)
        .def("get_pose", &environment::world::Agent::get_pose)
        .def("get_state", &environment::world::Agent::get_state)
        .def("step", &environment::world::Agent::step)
        .def("get_transformed_shape", &environment::world::Agent::get_transformed_shape)
        .def("set_kinematic_model", &environment::world::Agent::set_kinematic_model);

    py::class_<Object, BaseType, std::shared_ptr<Object>>(m, "Object")
        .def(py::init<>())
        .def("set_shape", &environment::world::Object::set_shape)
        .def("get_shape", &environment::world::Object::get_shape);
}
