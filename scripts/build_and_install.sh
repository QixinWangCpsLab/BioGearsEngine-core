# Accept Parameters: Release or Debug
BUILD_TYPE=$1

rm -rf /opt/biogears/core/build
rm -rf /root/biogears
rm -rf /usr/include/biogears
rm /usr/lib/*biogears*
rm -rf /usr/bin/howtos/
rm /usr/bin/bg-*

mkdir -p ../build && cd ../build && sudo cmake   \
    -DCMAKE_BUILD_TYPE=${BUILD_TYPE} \
    -DCMAKE_INSTALL_PREFIX=/root/biogears \
    -DCMAKE_CXX_STANDARD=20 \
    -DCMAKE_CXX_FLAGS="-g -fsanitize=leak -O0 -fsanitize=address"    \
    -DBiogears_BUILD_JAVATOOLS=OFF  \
    -DBiogears_SWIG_PYTHON_BINDINGS=OFF \
    -DBiogears_BUILD_SWIG_BINDINGS=OFF  \
    -DBiogears_SWIG_CSHARP_BINDINGS=OFF \
    -DBOOST_ROOT=/usr   \
    -DBoost_USE_STATIC_LIBS=ON  \
    -DBoost_USE_MULTITHREADED=ON    \
    -DBoost_USE_STATIC_RUNTIME=OFF  \
    -DBoost_NO_SYSTEM_PATHS=ON  \
    -DBoost_INCLUDE_DIR=/usr/include    \
    -DBoost_LIBRARY_DIRS=/usr/lib/x86_64-linux-gnu  \
    ..

# make some preparations to make up for the cmake bugs
mkdir -p /opt/biogears/core/build/projects/biogears/generated/Release/biogears/schema/cdm && \
mkdir -p /opt/biogears/core/build/projects/biogears/generated/Release/biogears/schema/biogears \
mkdir -p /opt/biogears/core/build/projects/biogears/generated/Debug/biogears/schema/cdm/ && \
mkdir -p /opt/biogears/core/build/projects/biogears/generated/Debug/biogears/schema/biogears

# Then build and install
cd ../build && cmake --build . -j 18 && cmake --install .

# move the folders of biogears to usr
cp -r /root/biogears/* /usr && rm -rf /root/biogears