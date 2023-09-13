# CMakeList.txt : CMake project for Chansaren, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("Chansaren")

# Add source to this project's executable.
add_executable (Chansaren "Chansaren.cpp" "Chansaren.h" "Kaart.h" "Kaart.cpp" "Table.h" "Table.cpp" "Player.cpp" "Player.h" "logic.cpp" "logic.h" "tests.h" "tests.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Chansaren PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
