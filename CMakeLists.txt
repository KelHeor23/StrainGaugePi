cmake_minimum_required(VERSION 3.5)

project(StrainGaugePi LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Проверка наличия библиотеки wiringPi
find_library(WIRINGPI_LIBRARIES wiringPi)
if(NOT WIRINGPI_LIBRARIES)
    message(FATAL_ERROR "wiringPi library not found!")
endif()

add_executable(StrainGaugePi main.cpp
    hx711/AbstractScale.cpp hx711/AbstractScale.h hx711/AdvancedHX711.cpp hx711/AdvancedHX711.h   hx711/common.h hx711/GpioException.h hx711/HX711.cpp hx711/HX711.h hx711/IntegrityException.h hx711/Mass.cpp hx711/Mass.h hx711/SimpleHX711.cpp hx711/SimpleHX711.h   hx711/TimeoutException.h hx711/Utility.cpp hx711/Utility.h hx711/Value.cpp hx711/Value.h hx711/ValueStack.cpp hx711/ValueStack.h hx711/Watcher.cpp hx711/Watcher.h)

target_link_libraries(StrainGaugePi PRIVATE
    ${WIRINGPI_LIBRARIES}
)

include(GNUInstallDirs)
install(TARGETS StrainGaugePi
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
