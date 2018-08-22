"""
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
"""

from divine_rl.world import World
from divine_rl.commons import Point, Line, Polygon


# load everything into world
w = World()


p2 = Point(0.0, 2.0)
p3 = Point(1.0, 2.0)

line = Line()
line.append(p2)
line.append(p3)

poly = Polygon()
poly.append(p2)
poly.append(p3)
poly.append(p3)

print(poly.collides(poly))

print(line.to_numpy())
print(poly.to_numpy())

print(p2.to_numpy())
print(p2.distance(p3))

# TODO: simplify
# line = Line([[0,0], [1,0]])
# shape = Shape([[0,0], [1,0]])

print("hello world")