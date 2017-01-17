project(alpha)

cmake_minimum_required(VERSION 2.8.11)


set(CMAKE_INCLUDE_CURRENT_DIR ON)

if(POLICY CMP0043)
    cmake_policy( SET CMP0043  OLD )
endif()

# Include this package's headers first
include_directories( BEFORE ./ ./include ../../include )

# Add specific Find.cmake modules 
set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules ) 

find_package(CGAL COMPONENTS Qt5)
include( ${CGAL_USE_FILE} )

find_package(Qt5 QUIET COMPONENTS Xml Script OpenGL Gui Svg)
find_package(OpenGL)


    find_package(QGLViewer)

add_definitions(-DBOOST_NO_CXX11_TEMPLATE_ALIASES)


set( HDRS dt3.h include/types.h options.h viewer.h scene.h window.h )

set( SRCS viewer.cpp main.cpp scene.cpp window.cpp)

set( MOCS moc_window.cxx 
          moc_options.cxx 
          moc_viewer.cxx )

if( OPENGL_FOUND AND QGLVIEWER_FOUND )

    include_directories( ${QGLVIEWER_INCLUDE_DIR} )

    # UI files (Qt Designer files)
    Qt5_wrap_ui( DT_UI_FILES alpha.ui options.ui)

    include(AddFileDependencies)

    # qrc files (resources files, that contain icons, at least)
    Qt5_add_resources( DT_RESOURCE_FILES alpha.qrc )
  
    # use the Qt MOC preprocessor on classes that derives from QObject
    Qt5_generate_moc( window.h moc_window.cxx )
    Qt5_generate_moc( viewer.h moc_viewer.cxx )
    Qt5_generate_moc( options.h moc_options.cxx )

    # The executable itself.
    add_executable( alpha ${SRCS} ${MOCS} ${DT_UI_FILES} ${DT_RESOURCE_FILES} )

    qt5_use_modules(alpha Gui OpenGL Xml Script Svg )

    # Link with Qt libraries
    target_link_libraries( alpha ${QT_LIBRARIES} )
    
    # Link with CGAL
    target_link_libraries( alpha ${CGAL_LIBRARIES} ${CGAL_3RD_PARTY_LIBRARIES})

    # Link with libQGLViewer, OpenGL
    target_link_libraries( alpha ${QGLVIEWER_LIBRARIES} ${OPENGL_gl_LIBRARY} ${OPENGL_glu_LIBRARY} )
    
    add_to_cached_list( CGAL_EXECUTABLE_TARGETS alpha )

else()
    
    message(STATUS "NOTICE: This demo requires ${OT_MISSING_DEPS} and will not be compiled.")

endif()
