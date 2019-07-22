# cityscape
> City-scale Graph - Spatial - Agent framework

[![License](https://img.shields.io/badge/license-Apache--2.0-blue.svg)](https://raw.githubusercontent.com/cityscapelabs/cityscape/develop/LICENSE)
[![CircleCI](https://circleci.com/gh/cityscapelabs/cityscape.svg?style=svg)](https://circleci.com/gh/cityscapelabs/cityscape)
[![codecov](https://codecov.io/gh/cityscapelabs/cityscape/branch/develop/graph/badge.svg)](https://codecov.io/gh/cityscapelabs/cityscape)
[![](https://img.shields.io/github/issues-raw/cityscapelabs/cityscape.svg)](https://github.com/cityscapelabs/cityscape/issues)
[![Project management](https://img.shields.io/badge/projects-view-ff69b4.svg)](https://github.com/cityscapelabs/cityscape/projects/)


### Prerequisite packages
> The following prerequisite packages can be found in the docker image:

* [Boost](http://www.boost.org/)


## Compile
0. Run `mkdir build && cd build && cmake -DCMAKE_CXX_COMPILER=g++ ..`.

1. Run `make clean && make -jN` (where N is the number of cores).


### Run tests

0. After compilation, run `./cityscapetest -s` (for a verbose output) or `ctest -VV`.
