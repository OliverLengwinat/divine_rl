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
#include <Eigen/Dense>
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/geometries/box.hpp>
#include <boost/geometry/index/rtree.hpp>
#include <vector>
#include <iostream>
#include <boost/foreach.hpp>

namespace simulation {
namespace commons {

namespace bg = boost::geometry;
namespace bgi = boost::geometry::index;

//! points
template<typename T, int N>
using PointNd_t = bg::model::point<T, N, bg::cs::cartesian>;

//! linestring
template<typename T, int N>
using Linestring_t = bg::model::linestring<PointNd_t<T, N>>;

//! polygon
template<typename T, int N>
using Polygon_t = bg::model::polygon<PointNd_t<T,N>>;

//! State
template<typename T, int N>
using State_t = Eigen::Matrix<T, 1, N>; 

//! Trajectory
template<typename T>
using Matrix_t = Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>; 

//! distance: line to point
template<typename T, int N>
T distance(const Linestring_t<T, N>& l, const PointNd_t<T, N>& p) {
	return bg::distance(p, l);
}

//! distance: shape to point
template<typename T, int N>
T distance(const Polygon_t<T, N>& s, const PointNd_t<T, N>& p) {
	return bg::distance(p, s);
}

//! distance: shape to line
template<typename T, int N>
T distance(const Linestring_t<T, N>& l, const Polygon_t<T, N>& s) {
	return bg::distance(l, s);
}

//! distance: shape to shape
template<typename T, int N>
T distance(const Polygon_t<T, N>& s0, const Polygon_t<T, N>& s1) {
	return bg::distance(s0, s1);
}

//! collison: shape to shape
template<typename T, int N>
bool distance(const Polygon_t<T, N>& s0, const Polygon_t<T, N>& s1) {
	return boost::geometry::intersects(s0, s1);
}

//! collision: point in shape
template<typename T, int N>
bool distance(const Polygon_t<T, N>& s0, const PointNd_t<T, N>& p) {
	return boost::geometry::intersects(s0, p);
}

//! translate polygon
template<typename T, int N>
Polygon_t<T, N> translate(const Polygon_t<T, N>& poly, const PointNd_t<T, N>& p){
 	namespace trans = boost::geometry::strategy::transform;
  using boost::geometry::dsv;

	Polygon_t<T, N> poly_new;
	if (N == 2){
		trans::translate_transformer<T, 2, 2> translate(bg::get<0>(p), bg::get<1>(p));
		boost::geometry::transform(poly, poly_new, translate);
	}
	else if (N == 3) {
		trans::translate_transformer<T, 3, 3> translate(bg::get<0>(p), bg::get<1>(p), bg::get<2>(p));
		boost::geometry::transform(poly, poly_new, translate);
	}

	return poly_new;
}

//! rotate polygon
// TODO: cannot handle 3d rotations yet. Use quaternions?
template<typename T, int N>
Polygon_t<T, N> rotate(const Polygon_t<T, N>& poly, const PointNd_t<T, N>& p){
	Polygon_t<T, N> poly_new;


	return poly;
}


//! Conversion functions to Eigen

//! Point to Eigen
template<typename T, int N>
Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic> get_matrix(const PointNd_t<T, N>& p){
	Eigen::Matrix<T, 1, N> ret;
	if (N == 2){
		ret.row(0) << bg::get<0>(p), bg::get<1>(p);
	} else if (N == 3){
		ret.row(0) << bg::get<0>(p), bg::get<1>(p), bg::get<2>(p);
	}
	return ret;
}

//! Line to Eigen
template<typename T, int N>
Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic> get_matrix(const Linestring_t<T, N>& l){
	Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic> ret(l.size(), N);

	for(uint32_t i = 0; i < l.size(); i++){
		ret.row(i) << get_matrix<T, N>(l[i]);
	}

	return ret;
}

//! Shape to Eigen
template<typename T, int N>
Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic> get_matrix(const Polygon_t<T, N>& p){
	Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic> ret(bg::num_points(p), N);
	int i = 0;
	for(auto it = boost::begin(boost::geometry::exterior_ring(p)); it != boost::end(boost::geometry::exterior_ring(p)); ++it)
	{
		ret.row(i) << get_matrix<T, N>(*it);
		i++;
	}
	return ret;
}

//! Conversion functions from Eigen

//! point
template<typename T, int N>
PointNd_t<T,N> create_point(const State_t<T, N>& p_eigen){
	PointNd_t<T,N> p_ret;
	bg::set<0>(p_ret, p_eigen(0));
	bg::set<1>(p_ret, p_eigen(1));
	if ( N == 3 ){
		bg::set<2>(p_ret, p_eigen(2));
	}
	return p_ret;
}

//! line
template<typename T, int N>
Linestring_t<T,N> create_line(const Matrix_t<T>& line_eigen){
	Linestring_t<T,N> line_ret;
	for (int i = 0; i < line_eigen.rows(); i++)
		bg::append(line_ret, create_point<T, N>(line_eigen.row(i)));
	return line_ret;
}

//! polygon
template<typename T, int N>
Polygon_t<T,N> create_polygon(const Matrix_t<T>& poly_eigen){
	Polygon_t<T,N> poly_ret;
	for (int i = 0; i < poly_eigen.rows(); i++)
		bg::append(poly_ret, create_point<T, N>(poly_eigen.row(i)));
	return poly_ret;
}

} // simulation
} // commons
