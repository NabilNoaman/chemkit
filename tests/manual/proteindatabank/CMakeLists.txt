if(NOT ${CHEMKIT_WITH_WEB})
  return()
endif()

find_package(Chemkit COMPONENTS io web)
include_directories(${CHEMKIT_INCLUDE_DIRS})

find_package(Qt4 4.6 COMPONENTS QtCore QtNetwork QtTest REQUIRED)
set(QT_USE_QTNETWORK TRUE)
set(QT_USE_QTTEST TRUE)
include(${QT_USE_FILE})

qt4_wrap_cpp(MOC_SOURCES proteindatabanktest.h)
add_executable(proteindatabanktest proteindatabanktest.cpp ${MOC_SOURCES})
target_link_libraries(proteindatabanktest ${CHEMKIT_LIBRARIES} ${QT_LIBRARIES})
