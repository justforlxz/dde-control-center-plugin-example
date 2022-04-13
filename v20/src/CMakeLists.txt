find_package(Qt5 COMPONENTS REQUIRED Core Widgets)
find_package(PkgConfig REQUIRED)
find_package(DdeControlCenter REQUIRED)

pkg_search_module(Dtk REQUIRED IMPORTED_TARGET dtkwidget)

set(SRCS
    module.h
    module.cpp
)

set(QRCS
  module.qrc
)

add_library(${PROJECT_NAME} SHARED ${SRCS} ${QRCS})
target_include_directories(${PROJECT_NAME}
    ${DdeControlCenter_INCLUDE_DIR}
)
target_link_libraries(${PROJECT_NAME}
PRIVATE
    Qt5::Core
    Qt5::Widgets
    PkgConfig::Dtk
    ${DdeControlCenter_LIBRARIES}
)
