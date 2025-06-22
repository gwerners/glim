#!/bin/bash

argc=$#

#https://vaneyckt.io/posts/safer_bash_scripts_with_set_euxo_pipefail/
set -euo pipefail

#show commands (for debuging)
#set -x

#move to script dir 
cd "$(dirname "${0}")"

#save current dir as base dir
ROOT=$(pwd)

#where to store/get tar.gz / tar.bz2
DEPENDENCIES=../dependencies

#avoid rm error if file doesn't exists
function safeRM {
  for file in ${@} ; do
    if [[ -f "${file}" ]]; then
      rm "${file}"
    fi
  done
}
#avoid rm error if directory doesn't exists
function safeRMDIR {
  for dir in ${@} ; do
    if [[ -d "${dir}" ]]; then
      rm -rf "${dir}"
    fi
  done
}
function safeMKDIR {
  if [ ! -d "$1" ]; then
    mkdir "$1"
  fi
}
function TAR {
  safeMKDIR "${DEPENDENCIES}"
  if [[ -f "${DEPENDENCIES}/$1.tar.gz" ]]; then
    echo "skipped"
    return
  else
    tar -cjf $1.tar.bz2 $1
    mv $1.tar.bz2 ${DEPENDENCIES}/
    echo "done"
    return
  fi
}
function UNTAR {
  if [[ ! -d "$1" ]]; then
    if [[ ! -f "${DEPENDENCIES}/$1.tar.gz" ]] && [[ ! -f "${DEPENDENCIES}/$1.tar.bz2" ]]; then
      echo "skipped"
      return
    else
      tar -xf ${DEPENDENCIES}/$1.tar.*
      echo "done"
      return
    fi
  fi
}
#check for dependency
function CheckNeeded {
  NEEDED=$(which ${1})
  if [ ! -f "${NEEDED}" ]; then
    echo "${1} is a dependency, you must install it first!"
    exit 0
  fi
}
function get {
  untarResult=$(UNTAR "$1")
  if [[ "${untarResult}"  == "skipped" ]]; then
    if [[ ! -d "$1" ]]; then
      git clone "$2"
      TAR "$1"
      cd ${ROOT}
    fi
  fi
}
function getAll {
  get fmt https://github.com/fmtlib/fmt.git
  get json https://github.com/nlohmann/json.git
  get lucy-clownfish https://github.com/apache/lucy-clownfish.git
  get lucy https://github.com/apache/lucy.git
}

function cleanOldBuild {
  ./clean.bash build
}
function buildClownfish {
  safeMKDIR "$ROOT/env"
  pushd lucy-clownfish
    if [[ ! -f "$ROOT/env/lib/libclownfish.so.0.6.0" ]]; then
      pushd runtime/c
        ./configure --prefix="$ROOT/env"
        make
        make install
      popd
    fi
    if [[ ! -f "$ROOT/env/bin/cfc" ]]; then
      pushd compiler/c
        ./configure --prefix="$ROOT/env"
        make
        make install
      popd
    fi
  popd
}
function buildLucy {
  if [[ ! -f "$ROOT/env/lib/liblucy.so.0.6.0" ]]; then
    safeMKDIR "$ROOT/env"
    pushd lucy
      pushd c
        export PATH="$PATH:$ROOT/env/bin"
        ./configure --clownfish-prefix="$ROOT/env"  --prefix="$ROOT/env"
        make
        make install
        cp -R autogen/include "$ROOT/env"
      popd
    popd
  fi
}
function build {
  buildClownfish
  buildLucy
  safeMKDIR build
  pushd build
    cmake ..
    make all
  popd
}
function run {
  #./build/work/glim -d /home/gwerners/projects/glim/lucy 
  #./build/work/glim -s index
  ./build/work/glim -d /home/gwerners/projects/glim/lucy  -s index -r "float(\d)" -o out.json
}

###############################################################################
#script main:
CheckNeeded g++ || exit 1
CheckNeeded cmake || exit 1
CheckNeeded git  || exit 1
getAll

build
run

###############################################################################
