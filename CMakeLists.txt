cmake_minimum_required(VERSION 3.5)

project(StrainGaugePi LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Проверка наличия библиотеки wiringPi
find_library(WIRINGPI_LIBRARIES wiringPi)
if(NOT WIRINGPI_LIBRARIES)
    message(FATAL_ERROR "wiringPi library not found!")
endif()

add_executable(StrainGaugePi main.cpp)

target_link_libraries(StrainGaugePi PRIVATE
    ${WIRINGPI_LIBRARIES}
)

include(GNUInstallDirs)
install(TARGETS StrainGaugePi
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
