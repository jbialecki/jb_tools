
SOURCE_PATH=$PWD
BUILD_DIR=../build
BUILD_SUBDIR=cmd_2_csv


echo $SOURCE_PATH

mkdir $BUILD_DIR
mkdir $BUILD_DIR/$BUILD_SUBDIR
cd $BUILD_DIR/$BUILD_SUBDIR
cmake $SOURCE_PATH -G Ninja -DWORKSPACE_ROOT=$SOURCE_PATH -DCMAKE_CXX_COMPILER=g++ -DCMAKE_C_COMPILER=gcc