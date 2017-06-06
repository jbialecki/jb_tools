
SOURCE_PATH=$PWD
NINJA_PATH="C:/Users/bialecki_j/Downloads/ninja-win/ninja.exe"
BUILD_DIR=../build
BUILD_SUBDIR=log_convert


echo $SOURCE_PATH

mkdir $BUILD_DIR
mkdir $BUILD_DIR/$BUILD_SUBDIR
cd $BUILD_DIR/$BUILD_SUBDIR
cmake $SOURCE_PATH -G Ninja -DCMAKE_MAKE_PROGRAM=$NINJA_PATH -DWORKSPACE_ROOT=$SOURCE_PATH -DCMAKE_CXX_COMPILER=g++ -DCMAKE_C_COMPILER=gcc
