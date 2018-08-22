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

#include "gtest/gtest.h"
#include "src/simulation/commons/common.h"


//! test point method and numpy conversion
TEST(geometry, point) {
	using namespace simulation::commons;
	PointNd_t<double, 3> p(1.0, 2.0, 3.0);

	
	State_t<double, 3> p_eigen;
	p_eigen.row(0) << 1.0, 2.0, 3.0;
	
	
	State_t<double, 3> p_eigen2;
	p_eigen2 = get_matrix<double, 3>(p);

	EXPECT_EQ(p_eigen2, p_eigen) << "Points did not match";

	PointNd_t<double, 3> p_from_eigen = create_point<double, 3>(p_eigen2);

	State_t<double, 3> p_converted_back_from_eigen = get_matrix<double, 3>(p_from_eigen);


	EXPECT_EQ(p_converted_back_from_eigen, p_eigen) << "Eigen conversion did fail.";
	
}


TEST(geometry, line) {
	using namespace simulation::commons;
	PointNd_t<double, 3> p0(0.0, 0.0, 3.0);
	PointNd_t<double, 3> p1(5.0, 0.0, 3.0);
	PointNd_t<double, 3> p2(3.0, 4.0, 3.0);

	Linestring_t<double, 3> line;
	bg::append(line, p0);
	bg::append(line, p1);

	double d = distance<double, 3>(line, p2);

	EXPECT_NEAR(d, 4.0, 0.1);

	
	Matrix_t<double> eigen_ref_line(2,3);
	eigen_ref_line << 0,0,0,5,0,0;

	Linestring_t<double, 3> line_from_eigen = create_line<double, 3>(eigen_ref_line);

	Matrix_t<double> linestring_from_eigen_converted_back = get_matrix<double, 3>(line_from_eigen);

	EXPECT_EQ(linestring_from_eigen_converted_back, eigen_ref_line) << "Linestrings did not match";
	
}


TEST(geometry, shape) {
	using namespace simulation::commons;

	PointNd_t<double, 3> p0(0.0, 0.0, 0.0);
	PointNd_t<double, 3> p1(1.0, 0.0, 0.0);
	PointNd_t<double, 3> p2(1.0, 1.0, 0.0);
	PointNd_t<double, 3> p3(0.0, 1.0, 0.0);


	PointNd_t<double, 3> translation_vector(1.0, 1.0, 0.0);


	Polygon_t<double, 3> poly;
	bg::append(poly, p0);
	bg::append(poly, p1);
	bg::append(poly, p2);
	bg::append(poly, p3);

	Matrix_t<double> ref_matrix(4, 3);
	ref_matrix << 1.0, 1.0, 0.0, 2.0, 1.0, 0.0, 2.0, 2.0, 0.0, 1.0, 2.0, 0.0;

	//! translation and rotation
	poly = translate<double, 3>(poly, translation_vector);
	Matrix_t<double> poly_translated = get_matrix<double, 3>(poly);

	EXPECT_EQ(ref_matrix, poly_translated) << "Translation of polygon failed.";


	// TODO: finish test

	poly = rotate<double, 3>(poly, 0.78);
	std::cout << get_matrix<double, 3>(poly) << std::endl;

	//! distance: shape to shape, point to shape, shape to line

	//! collision: shape to shape, shape to point


}