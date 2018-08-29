# divine_rl
**Div**e **in**to r**e**inforcement learning

## Installation
Before you get started, make sure to have Python3, virtualenv as well as bazel installed.
If these prequesites have been met, you can start by executing `bash install.sh` which will create a virtual python environment.
In order to activate it, run `source dev_into.sh`.

## Build Process
This library is completely built using the bazel build system. So all tests, python scripts as well as c++ code can be ran using bazel commands.
Here is an overview of the most important ones:

* Build everything: `bazel build //...`
* Test everything: `bazel test //src/python:environment`
* Run the environment: `bazel run //src/environment:environment`
