cmake_minimum_required ( VERSION 2.8.8 )
project ( moaiios )

message("Building for architecture: ${CMAKE_OSX_ARCHITECTURES}")

set ( SQB_BUILD_DIR ${CMAKE_BINARY_DIR}/../../build)


add_subdirectory( "${CMAKE_CURRENT_BINARY_DIR}/../bundle_res" "bundle_res")

set ( INCLUDES_MOAIIOS
  "${MOAI_ROOT}/src/"
  "${MOAI_ROOT}/src/config-default/"
  "${MOAI_ROOT}/src/host-glut"
)

set ( IOS_HOST "${MOAI_ROOT}/src/host-ios")

include_directories (
    ${INCLUDES_MOAIIOS}
)

file ( GLOB_RECURSE MOAIIOS_SOURCES
  "${IOS_HOST}/*.cpp"
  "${IOS_HOST}/*.mm"
  "${IOS_HOST}/*.h"
  "${MOAI_ROOT}/src/host-modules/*.cpp"
  "${MOAI_ROOT}/src/host-modules/*.h"
  "${MOAI_ROOT}/src/host-glut/ParticlePresets.cpp"
  "${MOAI_ROOT}/src/host-glut/ParticlePresets.h"
)

if( SQUIRREL_AND_BAER )

file( GLOB MOAIIOS_RESOURCES
  "${CMAKE_BINARY_DIR}/resources/*"
)

list( APPEND MOAIIOS_RESOURCES
  "${SQB_BUILD_DIR}/anims"
  "${SQB_BUILD_DIR}/fonts"
  "${SQB_BUILD_DIR}/img-hd-iOS"
  "${SQB_BUILD_DIR}/img-sd-iOS"
  "${SQB_BUILD_DIR}/levels-json"
  "${SQB_BUILD_DIR}/mo"
  "${SQB_BUILD_DIR}/snd-ogg"
)

else()

file ( GLOB MOAIIOS_RESOURCES ${IOS_HOST}/*.png)

endif()

SET_SOURCE_FILES_PROPERTIES (
  ${MOAIIOS_RESOURCES}
  PROPERTIES
  MACOSX_PACKAGE_LOCATION Resources
)


SET_SOURCE_FILES_PROPERTIES (
  ${PROJECT_RESOURCES}
  PROPERTIES
  MACOSX_PACKAGE_LOCATION moai.app/lua
)

add_executable ( moai MACOSX_BUNDLE ${MOAIIOS_SOURCES} ${MOAIIOS_RESOURCES} ${PROJECT_RESOURCES})

target_link_libraries ( moai
  host-modules
  moai-sim
  moai-util
  moai-iphone
  moai-audiosampler
  moai-core
  zlcore
  tge-extensions
)

set_target_properties( moai PROPERTIES
   XCODE_ATTRIBUTE_INSTALL_PATH "$(LOCAL_APPS_DIR)"
   XCODE_ATTRIBUTE_SKIP_INSTALL "NO"
   XCODE_ATTRIBUTE_IPHONEOS_DEPLOYMENT_TARGET "5.1.1"
   XCODE_ATTRIBUTE_TARGETED_DEVICE_FAMILY "1,2"
   XCODE_ATTRIBUTE_COMBINE_HIDPI_IMAGES "NO"
)

macro(ADD_FRAMEWORKS appname fwnames)
  FOREACH(FW ${fwnames})
    TARGET_LINK_LIBRARIES( ${appname} "-framework ${FW}")
  ENDFOREACH(FW)
endmacro(ADD_FRAMEWORKS)

if (SQUIRREL_AND_BAER)
set( FWORKS
  AdSupport
  AudioToolbox
  CoreAudio
  CoreGraphics
  CoreLocation
  CoreTelephony
  CoreMotion
  CFNetwork
  Foundation
  GameKit
  EventKit
  MediaPlayer
  MobileCoreServices
  MessageUI
  OpenGLES
  QuartzCore
  StoreKit
  SystemConfiguration
  UIKit
)
else()
set( FWORKS
  AdSupport
  AudioToolbox
  CoreAudio
  CoreGraphics
  CoreLocation
  CoreTelephony
  CoreMotion
  CFNetwork
  Foundation
  GameKit
  EventKit
  MediaPlayer
  MobileCoreServices
  MessageUI
  OpenGLES
  QuartzCore
  StoreKit
  Social
  SystemConfiguration
  Twitter
  UIKit
)
endif()

ADD_FRAMEWORKS(moai "${FWORKS}")

set_target_properties(moai PROPERTIES XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY "${SIGN_IDENTITY}")
set_target_properties(moai PROPERTIES MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_BINARY_DIR}/../Info.plist)

 
