find_package(Chemkit)
include_directories(${CHEMKIT_INCLUDE_DIRS})

find_package(Qt4 4.6 COMPONENTS QtCore QtTest REQUIRED)
set(QT_DONT_USE_QTGUI TRUE)
set(QT_USE_QTTEST TRUE)
include(${QT_USE_FILE})

add_subdirectory(sdf-cml)
add_subdirectory(sdf-mol2)
add_subdirectory(smiles-inchi)
add_subdirectory(smiles-sdf)
