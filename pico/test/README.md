# pico-w blink project

```
# edit the CMakeList.txt according to how you want it.

# copy the pico_sdk_import.cmake from the pico-sdk installation to your project folder.
cp <pico-sdk>/external/pico_sdk_import.cmake <project-directory>

(replace <""> with the path)

# make a build directory and change to that directory
mkdir build
cd build

# export sdk-path if you havnt done that already
export PICO_SDK_PATH=<path-to-sdk>

# build
cmake ..
make

# to load and run the .uf2 file (mac users)
# make sure you connected your pico with boolset button pressed

cp <filename>.uf2 /Volumes/RPI-RP2

# done
```
