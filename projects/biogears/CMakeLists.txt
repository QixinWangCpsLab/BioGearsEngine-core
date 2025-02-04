###############################################################################
# Policy adjustments
###############################################################################

###############################################################################
# Options
###############################################################################

option (Biogears_BUILD_IO_LIBRARY "When enabled an extra IO Library will be built allowing BioGears to fall back to embeded versions of resource files " ON)

option (Biogears_THROW_READONLY_EXCEPTIONS "Toggle the throwing CommonDataModelExceptions when a ReadOnly SEScalar is Modified." ON)
option (Biogears_THROW_NAN_EXCEPTIONS "Toggle the throwing CommonDataModelExceptions when an  SEScalar is NaNExceptions." ON)
option (Biogears_USE_OVERRIDE_CONTROL       "When enabled Biogears will control the ranges of override"  OFF)
option (Biogears_BUILD_CIRCUIT_TESTS       "Toggle on the Circuit Test Library which is a dependeny of libbiogears_jni"  OFF)

option (Biogears_BUILD_SWIG_BINDINGS       "Toggle the Genearting of languge bindings using SWIG (Experimental)"  OFF)

###############################################################################
# Base Variables
###############################################################################
set(BIO_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libBiogears/include" )
set(BIO_CDM_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libCDM/include/")
set(BIO_IO_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libIO/include" )
set(BIO_IO_GENERATED_INCLUDE_DIR "${CMAKE_CURRENT_BINARY_DIR}/generated/" )
set(BIO_IO_EMBEDED_INCLUDE_DIR "${CMAKE_CURRENT_BINARY_DIR}/generated/c_encoded/${Biogears_LIB_VERSION}" )
set(BIO_CIRCUIT_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libCircuitTest/include" )
set(BIO_PRIVATE_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libBiogears/src" )
set(BIO_GENERATED_INCLUDE_DIR "${CMAKE_CURRENT_BINARY_DIR}/generated/" )
set(BIO_UNIT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/unit" PARENT_SCOPE)

###############################################################################
# Requirments
###############################################################################
set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
if(WIN32)
  set(Boost_USE_STATIC_LIBS ON) 
endif()

verify_package(Threads REQUIRED)
verify_package(Eigen3 REQUIRED)
verify_package(CodeSynthesis REQUIRED)
verify_package(Protobuf QUIET)

if(Biogears_BUILD_PYTHON_BINDINGS)
  verify_package(pybind11 REQUIRED)
endif()
###############################################################################
#Code Generation
###############################################################################

## Code Synthesis XSD
file(GLOB_RECURSE biogears_xsd_list "${PROJECT_SOURCE_DIR}/share/xsd/biogears/*.xsd")
file(GLOB_RECURSE cdm_xsd_list "${PROJECT_SOURCE_DIR}/share/xsd/cdm/*.xsd")

set (BIOGEARS_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set (BIOGEARS_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/generated/$<CONFIG>)
set (BIOGEARS_BINARY_BARE_DIR ${CMAKE_CURRENT_BINARY_DIR}/generated/)


REGISTER_XSD_DIR( "${PROJECT_SOURCE_DIR}/share/xsd/"
                    CONFIG "${PROJECT_SOURCE_DIR}/share/xsd/BioGearsDataModel.cfg"
                    PROJECT "generated/$<CONFIG>/biogears" COMPONENT "schema" RESOURCE_FOLDER "resources/schema"
                    NO_TARGETS SOURCES_VAR XSD_SRCS HEADERS_VAR XSD_HDRS VERBOSITY 1)


file(GLOB_RECURSE XSD_FILES CMAKE_CONFIGURE_DEPENDS  ${PROJECT_SOURCE_DIR}/share/xsd/*.xsd )

add_custom_target(xsd_bindings 
  COMMENT "Generates XML Bindings from XSD Files" 
  SOURCES ${XSD_FILES}
  DEPENDS ${XSD_SRCS} ${XSD_HDRS}
)

source_group( TREE  ${PROJECT_SOURCE_DIR}/share/xsd/ PREFIX schema FILES ${XSD_FILES})
set_source_files_properties(${XSD_FILES} PROPERTIES 
                HEADER_FILE_ONLY 
                TRUE FOLDER schema
)


option(Biogears_USE_PROTO "Enable very experimental PROTOBUFF Support [DEVELOPER ONLY]" OFF)
if (Biogears_USE_PROTO)
# Proto Buffs
file(GLOB_RECURSE PROTO_FILES CMAKE_CONFIGURE_DEPENDS  ${PROJECT_SOURCE_DIR}/share/proto/*.proto)

protobuf_generate(
 LANGUAGE cpp
 OUT_VAR  PROTO_SOURCES
 PROTOC_OUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/generated/biogears/schema/proto
 EXPORT_MACRO BIOGEARS_CDM_API 
 IMPORT_DIRS "${CMAKE_SOURCE_DIR}/share/proto"
 PROTOS ${PROTO_FILES})

add_custom_target(proto_bindings 
  COMMENT "Generates XML Bindings from Proto Files" 
  SOURCES ${PROTO_FILES}
  DEPENDS ${PROTO_SOURCES}
)

set_target_properties(proto_bindings
                    PROPERTIES
                    FOLDER "Code Generators/")

source_group( TREE  ${PROJECT_SOURCE_DIR}/share/proto/ PREFIX schema FILES ${PROTO_FILES})
set_source_files_properties(${PROTO_FILES} PROPERTIES 
                HEADER_FILE_ONLY 
                TRUE FOLDER schema)

endif()
# Version Source Code
set_target_properties(xsd_bindings PROPERTIES FOLDER "Code Generators")

file(READ  ${BIOGEARS_SOURCE_DIR}/libBiogears/src/version.cpp.in contents)
string(CONFIGURE "${contents}" contents )
FILE(GENERATE OUTPUT ${BIOGEARS_BINARY_DIR}/libBiogears/src/version.cpp 
  CONTENT "${contents}"
  NEWLINE_STYLE LF)
###############################################################################
#Sorce and Header Defines
###############################################################################
message(STATUS "Configuring biogears")

###############################################################################
# libBiogears_io
###############################################################################
if(Biogears_BUILD_IO_LIBRARY)
  add_subdirectory(libIO)
endif()

###############################################################################
#Define Logic
###############################################################################
if(Biogears_BUILD_STATIC)
  ###############################################################################
  # libBiogears_st
  ###############################################################################
  add_subdirectory(libBiogears)
else()
  ###############################################################################
  # libBiogears_cdm
  ###############################################################################
  add_subdirectory(libCDM)

  ###############################################################################
  # libBiogears
  ###############################################################################
  add_subdirectory(libBiogears)
  
  ###############################################################################
  # libBiogears_circuit_test
  ###############################################################################
  if( Biogears_BUILD_CIRCUIT_TESTS)
    add_subdirectory(libCircuitTest)
  endif()
endif() #Biogears_BUILD_STATIC

###############################################################################
# libBiogears_circuit_test
###############################################################################
add_subdirectory(swig_bindings)

######################################################################################################
# INSTALL LOGIC
######################################################################################################
if(NOT  Biogears_BUILD_IO_LIBRARY)
  install(DIRECTORY 
      ${PROJECT_SOURCE_DIR}/share/xsd 
      DESTINATION share/biogears/${Biogears_VERSION_TAG}
      FILE_PERMISSIONS OWNER_READ GROUP_READ WORLD_READ
  )
  
  install(DIRECTORY 
      ${PROJECT_SOURCE_DIR}/share/data
      DESTINATION share/biogears/${Biogears_VERSION_TAG}
      FILE_PERMISSIONS OWNER_READ GROUP_READ WORLD_READ
      FILES_MATCHING 
      PATTERN "*.xml"
      PATTERN "*.csv"
      PATTERN "*.xlsx"
  )
  
  install(DIRECTORY 
      ${PROJECT_SOURCE_DIR}/share/Scenarios
      DESTINATION share/biogears/${Biogears_VERSION_TAG}/data/
      FILE_PERMISSIONS OWNER_READ GROUP_READ WORLD_READ
      FILES_MATCHING 
      PATTERN "*.xml"
  )
endif()
message(STATUS "")
