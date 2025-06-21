# Header-only library - collect all headers
file(GLOB_RECURSE FLINTXX_HEADERS
    "flintxx/*.h"
    "*.h"
)

# Create header-only library
add_library(flintxx INTERFACE)

# Set include directories for header-only library
target_include_directories(flintxx
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/flintxx>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
        ${GMP_INCLUDE_DIRS}
        ${MPFR_INCLUDE_DIRS}
        ${FLINT_INCLUDE_DIR}
)

# Link dependencies for header-only library
target_link_libraries(flintxx
    INTERFACE
        ${GMP_LIBRARIES}
        ${MPFR_LIBRARIES}
        ${PThreads_LIBRARIES}
)

# Link with system FLINT library
find_library(FLINT_LIBRARY NAMES flint libflint
    PATHS 
        /opt/homebrew/lib
        /usr/local/lib
        /usr/lib
)

if(FLINT_LIBRARY)
    target_link_libraries(flintxx INTERFACE ${FLINT_LIBRARY})
    message(STATUS "Found FLINT library: ${FLINT_LIBRARY}")
    
    # Find FLINT headers
    find_path(FLINT_INCLUDE_DIR NAMES flint/flint.h
        PATHS
            /opt/homebrew/include
            /usr/local/include
            /usr/include
    )
    
    if(FLINT_INCLUDE_DIR)
        target_include_directories(flintxx INTERFACE ${FLINT_INCLUDE_DIR})
        message(STATUS "Found FLINT headers: ${FLINT_INCLUDE_DIR}")
    else()
        message(WARNING "FLINT headers not found")
    endif()
else()
    message(FATAL_ERROR "FLINT library not found. Please install FLINT.")
endif()

if(FLINT_USES_BLAS)
    target_link_libraries(flintxx INTERFACE ${CBLAS_LIBRARIES})
    target_include_directories(flintxx INTERFACE ${CBLAS_INCLUDE_DIRS})
endif()

if(WITH_NTL)
    target_link_libraries(flintxx INTERFACE ${NTL_LIBRARIES})
    target_include_directories(flintxx INTERFACE ${NTL_INCLUDE_DIRS})
endif()

# Set properties - INTERFACE libraries don't support VERSION/SOVERSION
set_target_properties(flintxx PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

# Export all symbols on Windows when building shared libs
if(BUILD_SHARED_LIBS AND MSVC)
    set_target_properties(flintxx PROPERTIES 
        WINDOWS_EXPORT_ALL_SYMBOLS ON
    )
    target_compile_definitions(flintxx 
        PRIVATE "FLINT_BUILD_DLL"
        PUBLIC "MSC_USE_DLL"
    )
endif()

# Add math library on non-MSVC platforms
if(NOT MSVC)
    target_link_libraries(flintxx INTERFACE m)
endif()

# Add subdirectories for examples and tests
add_subdirectory(flintxx/examples)
add_subdirectory(flintxx/test) 