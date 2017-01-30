project(alpha)

cmake_minimum_required(VERSION 2.4.5)

set( CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS true )

if( COMMAND cmake_policy )
    cmake_policy( SET CMP0003 NEW )
endif()

# Include this package's headers first
include_directories( BEFORE ./ ./include ../../include )

# Add specific Find.cmake modules 
set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules ) 


# temporary flags for easier debug (julie)
if( NOT WIN32 )
	SET(CMAKE_CXX_FLAGS  "-fopenmp -Wfatal-errors")
endif()
if( WIN32 )
	#SET(CMAKE_CXX_FLAGS  "-fopenmp")
endif()


find_package(CGAL COMPONENTS Qt4)
include( ${CGAL_USE_FILE} )

file(GLOB "GC" "${CMAKE_SOURCE_DIR}/gco/*.cpp")
source_group("GC" FILES ${GC})
include_directories(${CMAKE_SOURCE_DIR}/gco) 

set( QT_USE_QTXML    TRUE )
set( QT_USE_QTMAIN   TRUE )
set( QT_USE_QTalphaRIPT  TRUE )
set( QT_USE_QTOPENGL  TRUE )
find_package(Qt4)
find_package(OpenGL)

if( QT4_FOUND )
    include( ${QT_USE_FILE} )
    find_package(QGLViewer)
endif()

set( HDRS dt3.h include/types.h options.h viewer.h scene.h window.h )

set( SRCS viewer.cpp main.cpp scene.cpp window.cpp)

set( MOCS moc_window.cxx 
          moc_options.cxx 
          moc_viewer.cxx )

if( CGAL_Qt4_FOUND AND QT4_FOUND AND OPENGL_FOUND AND QGLVIEWER_FOUND )
    include_directories( ${QGLVIEWER_INCLUDE_DIR} )

    # UI files (Qt Designer files)
    qt4_wrap_ui( DT_UI_FILES alpha.ui options.ui)

    include(AddFileDependencies)

    # qrc files (resources files, that contain icons, at least)
    qt4_add_resources( DT_RESOURCE_FILES alpha.qrc )
  
    # use the Qt MOC preprocessor on classes that derives from QObject
    qt4_generate_moc( window.h moc_window.cxx )
    qt4_generate_moc( viewer.h moc_viewer.cxx )
    qt4_generate_moc( options.h moc_options.cxx )

    # The executable itself.
    add_executable( alpha ${SRCS} ${MOCS} ${DT_UI_FILES} ${DT_RESOURCE_FILES} ${GC})

    # Link with Qt libraries
    target_link_libraries( alpha ${QT_LIBRARIES} )
    
    # Link with CGAL
    target_link_libraries( alpha ${CGAL_LIBRARIES} ${CGAL_3RD_PARTY_LIBRARIES})

    # Link with libQGLViewer, OpenGL
    target_link_libraries( alpha ${QGLVIEWER_LIBRARIES} ${OPENGL_gl_LIBRARY} ${OPENGL_glu_LIBRARY} )
    
    add_to_cached_list( CGAL_EXECUTABLE_TARGETS alpha )

else()
    
    set(OT_MISSING_DEPS "")

    if(NOT OPENGL_FOUND)
        set(OT_MISSING_DEPS "OpenGL, ${OT_MISSING_DEPS}")
    endif()

    if(NOT QT4_FOUND)
        set(OT_MISSING_DEPS "Qt4, ${OT_MISSING_DEPS}")
    endif()

    if(NOT QGLVIEWER_FOUND)
        set(OT_MISSING_DEPS "QGLViewer, ${OT_MISSING_DEPS}")
    endif()

    if(NOT CGAL_FOUND)
        set(OT_MISSING_DEPS "the CGAL library, ${OT_MISSING_DEPS}")
    endif()

    if(NOT CGAL_Qt4_FOUND)
        set(OT_MISSING_DEPS "the CGAL Qt4 library, ${OT_MISSING_DEPS}")
    endif()

    message(STATUS "NOTICE: This demo requires ${OT_MISSING_DEPS} and will not be compiled.")

endif()
