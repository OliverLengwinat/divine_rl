filegroup(
   name="world_test_data",
   srcs=["unstructured_world.pb.txt", "structured_world.pb.txt"],
   visibility = ["//visibility:public"],
)

py_test(
  name = "geometry_tests",
  srcs = ["geometry_tests.py"],
  data = ['//src/python_bindings:divine_rl.so'],
  imports = ['../../src/python_bindings/'],
  deps = [],
)

py_test(
  name = "kinematics_tests",
  srcs = ["kinematics_tests.py"],
  data = ['//src/python_bindings:divine_rl.so'],
  imports = ['../../src/python_bindings/'],
  deps = [],
)

py_test(
  name = "world_tests",
  srcs = ["world_tests.py"],
  data = ['//src/python_bindings:divine_rl.so'],
  imports = ['../../src/python_bindings/'],
  deps = ["//src/proto:py_commons"],
)

py_test(
  name = "road_tests",
  srcs = ["road_tests.py"],
  data = ['//src/python_bindings:divine_rl.so'],
  imports = ['../../src/python_bindings/'],
  deps = ["//src/proto:py_commons"],
)