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

namespace py = pybind11;


void commons_bindings(py::module m)
{
    using namespace simulation::commons;
    
    py::class_<PointNd_t<double, 2>>(m, "Point2d")
        .def(py::init<double, double>());

    //m.def("to_numpy", [](PointNd_t<double, 3> p) { return get_matrix<double,3>(p); } );

    py::class_<PointNd_t<double, 3>>(m, "Point3d")
        .def(py::init<double, double, double>())
        
        .def("__repr__", [](const PointNd_t<double, 3>& p)
        {
            return "content";
        });

}

