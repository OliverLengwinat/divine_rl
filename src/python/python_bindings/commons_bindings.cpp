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

#include "commons_bindings.h"
#include "src/simulation/commons/common.h"
#include "src/simulation/commons/kinematics.h"

namespace py = pybind11;


void commons_bindings(py::module m)
{
    using namespace simulation::commons;
    using namespace simulation::kinematics;
    
    py::class_<PointNd_t<double, 3>>(m, "Pose")
        .def(py::init<double, double, double>())
        .def("__repr__", [](const PointNd_t<double, 3>& p)
        {
            return "Point3d";
        });

    py::class_<PointNd_t<double, 2>>(m, "Point")
        .def(py::init<double, double>())
        .def("to_numpy", [](const PointNd_t<double, 2>& p)
        {
            return get_matrix<double, 2>(p);
        })
        .def("is_colliding", [](const PointNd_t<double, 2>& p, const Polygon_t<double, 2>& poly)
        {
            return collides<double, 2>(poly, p);
        })
        .def("distance", [](const PointNd_t<double, 2>& p, const Linestring_t<double, 2>& l)
        {
            return distance<double, 2>(l, p);
        })
        .def("distance", [](const PointNd_t<double, 2>& p, const Polygon_t<double, 2>& poly)
        {
            return distance<double, 2>(poly, p);
        })
        .def("distance", [](const PointNd_t<double, 2>& p0, const PointNd_t<double, 2>& p1)
        {
            return distance<double, 2>(p0, p1);
        })
        .def("__repr__", [](const PointNd_t<double, 2>& p)
        {
            return "Point";
        });


    py::class_<Linestring_t<double, 2>>(m, "Line")
        .def(py::init<>())
        .def("append", [](Linestring_t<double, 2>& l, const PointNd_t<double, 2>& p)
        {
            return bg::append(l, p);
        })
        .def("to_numpy", [](const Linestring_t<double, 2>& l)
        {
            return get_matrix<double, 2>(l);
        })
        .def("distance", [](const Linestring_t<double, 2>& l, const PointNd_t<double, 2>& p)
        {
            return distance<double, 2>(l, p);
        })
        .def("distance", [](const Linestring_t<double, 2>& l, const Polygon_t<double, 2>& poly)
        {
            return distance<double, 2>(l, poly);
        })
        .def("__repr__", [](const Linestring_t<double, 2>& p)
        {
            return "Line";
        });

    py::class_<Polygon_t<double, 2>>(m, "Polygon")
        .def(py::init<>())
        .def("append", [](Polygon_t<double, 2>& l, const PointNd_t<double, 2>& p)
        {
            return bg::append(l, p);
        })
        .def("to_numpy", [](const Polygon_t<double, 2>& l)
        {
            return get_matrix<double, 2>(l);
        })
        .def("distance", [](const Polygon_t<double, 2>& poly, const PointNd_t<double, 2>& p)
        {
            return distance<double, 2>(poly, p);
        })
        .def("translate", [](const Polygon_t<double, 2>& poly, const PointNd_t<double, 2>& p)
        {
            return translate<double, 2>(poly, p);
        })
        .def("rotate", [](const Polygon_t<double, 2>& poly, double angle)
        {
            return rotate<double, 2>(poly, angle);
        })
        .def("collides", [](const Polygon_t<double, 2>& poly0, const Polygon_t<double, 2>& poly1)
        {
            return collides<double, 2>(poly0, poly1);
        })
        .def("__repr__", [](const Polygon_t<double, 2>& p)
        {
            return "Polygon";
        });

    py::class_<KinematicModel<double>, std::shared_ptr<KinematicModel<double>>>(m, "KinematicModel")
        .def(py::init<>())
        .def("__repr__", [](const KinematicModel<double>& k)
        {
            return "KinematicModel";
        });

    py::class_< SingleTrackModel<double>, KinematicModel<double>, std::shared_ptr<SingleTrackModel<double>>>(m, "SingleTrackModel")
        .def(py::init<>())
        .def("step", &SingleTrackModel<double>::step)
        .def("get_pose", &SingleTrackModel<double>::get_pose)
        .def("__repr__", [](const SingleTrackModel<double>& k)
        {
            return "SingleTrackModel";
        });
}

