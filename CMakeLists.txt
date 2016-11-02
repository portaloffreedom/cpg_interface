cmake_minimum_required(VERSION 2.8.11)
project(cpg_interface)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

# Find the QtWidgets library
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Charts REQUIRED)
find_package(Qt5Multimedia REQUIRED)

# add revolve neat
add_subdirectory(../revolve-brain/cpp revolve-brain)
include_directories(../revolve-brain/cpp)

set(cpg_interface_SRC
  src/main.cpp
  src/cpg_interface.cpp
  src/chart.cpp
  src/xyseriesiodevice.cpp
  src/rythmgeneratortimed.cpp
  src/rythmtochart.cpp
)

# Create code from a list of Qt designer ui files.
#set(CMAKE_AUTOUIC ON) # use this if you have CMake 3.x instead of the following
qt5_wrap_ui(cpg_interface_SRC src/cpg_interface.ui)

# Tell CMake to create the helloworld executable
add_executable(cpg_interface ${cpg_interface_SRC})

# Use the Widgets module from Qt 5.
target_link_libraries(cpg_interface cpg Qt5::Widgets Qt5::Charts Qt5::Multimedia)

# Install the executable
install(TARGETS cpg_interface DESTINATION bin)
