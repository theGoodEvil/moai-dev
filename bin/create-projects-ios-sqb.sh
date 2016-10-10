#!/bin/bash

APP_NAME='Moai App'
APP_ID='com.getmoai.moaiapp'
APP_VERSION='1.0'


# check for command line switches
usage="usage: $0  \
    [--use-untz true | false] [--disable-adcolony] [--disable-billing] \
    [--disable-chartboost] [--disable-crittercism] [--disable-facebook] [--disable-push] [--disable-tapjoy] \
    [--disable-twitter]  [--disable-playhaven] <lua_src_directory> [xcode_project_dir]"

use_untz="true"

adcolony_flags=
billing_flags=
chartboost_flags=
crittercism_flags=
facebook_flags=
push_flags=
tapjoy_flags=
twitter_flags=
playhaven_flags=
buildtype_flags="Release"
windows_flags=
simulator="false"

while [ $# -gt 1 ];	do
    case "$1" in
        --use-untz)  use_untz="$2"; shift;;
        --disable-adcolony)  adcolony_flags="-DDISABLE_ADCOLONY=1";;
        --disable-billing)  billing_flags="-DDISABLE_BILLING=1";;
        --disable-chartboost)  chartboost_flags="-DDISABLE_CHARTBOOST=1";;
        --disable-crittercism)  crittercism_flags="-DDISABLE_CRITTERCISM=1";;
        --disable-facebook)  facebook_flags="-DDISABLE_FACEBOOK=1";;
        --disable-push)  push_flags="-DDISABLE_NOTIFICATIONS=1";;
        --disable-tapjoy)  tapjoy_flags="-DDISABLE_TAPJOY=1";;
        --disable-twitter)  twitter_flags="-DDISABLE_TWITTER=1";;
        --disable-playhaven) playhaven_flags="-DDISABLE_PLAYHAVEN=1";;
        --disable-mobileapptracker) mobileapptracker_flags="-DDISABLE_MOBILEAPPTRACKER=1";;
        
        -*)
            echo >&2 \
                $usage
            exit 1;;
        *)  break;;	# terminate while loop
    esac
    shift
done

#this is the directory where this file is located
BASE_DIR=`pwd`/`dirname $0`
#sdk root
MOAI_DIR=$BASE_DIR/..

#get absolute path of lua src dir
SRCPARAM=`dirname $0`/../samples/hello-moai
if [ x != x"$1" ]; then
   SRCPARAM=$1 
fi
#LUASRC=$(ruby -e 'puts File.expand_path(ARGV.first)' "$SRCPARAM")
LUASRC=`pwd`/$SRCPARAM

#get absolute path of build dir
BUILDPARAM=`dirname $0`/../cmake/projects/moai-ios
if [ x != x"$2" ]; then
   BUILDPARAM=$2 
fi
BUILD_DIR=`pwd`/$BUILDPARAM

#navigate into the moai root dir
cd $MOAI_DIR

if [ ! -f "${LUASRC}/main.lua" ]; then
  echo "Could not find main.lua in specified lua source directory [${LUASRC}]"
  exit 1
fi

if [ x"$use_untz" != xtrue ] && [ x"$use_untz" != xfalse ]; then
    echo $usage
    exit 1		
fi

#get some required variables
XCODEPATH=$(xcode-select --print-path)

if [ x"$simulator" == xtrue ]; then
# echo "RUNNING SIMULATOR $simulator"
# PLATFORM_PATH=${XCODEPATH}/Platforms/iPhoneSimulator.platform/Developer
# PLATFORM=SIMULATOR
# SDK=iphonesimulator
# ARCH="i386x64"
#else
PLATFORM_PATH=${XCODEPATH}/Platforms/iPhone.platform/Developer
PLATFORM=OS
SDK=iphoneos
ARCH="armv7;armv64"
fi

SIGN_IDENTITY='iPhone Developer'

# echo message about what we are doing
echo "Building moai.app via CMAKE"

disabled_ext=
    
if [ x"$use_untz" != xtrue ]; then
    echo "UNTZ will be disabled"
    untz_param='-DMOAI_UNTZ=0'
else
    untz_param='-DMOAI_UNTZ=1'
fi 

if [ x"$adcolony_flags" != x ]; then
    echo "AdColony will be disabled"
    disabled_ext="${disabled_ext}ADCOLONY;"
fi 

if [ x"$billing_flags" != x ]; then
    echo "Billing will be disabled"
    disabled_ext="${disabled_ext}BILLING;"
fi 

if [ x"$chartboost_flags" != x ]; then
    echo "ChartBoost will be disabled"
    disabled_ext="${disabled_ext}CHARTBOOST;"
fi 

if [ x"$crittercism_flags" != x ]; then
    echo "Crittercism will be disabled"
    disabled_ext="${disabled_ext}CRITTERCISM;"
fi 

if [ x"$facebook_flags" != x ]; then
    echo "Facebook will be disabled"
    disabled_ext="${disabled_ext}FACEBOOK;"
fi 

if [ x"$push_flags" != x ]; then
    echo "Push Notifications will be disabled"
    disabled_ext="${disabled_ext}NOTIFICATIONS;"
fi 

if [ x"$tapjoy_flags" != x ]; then
    echo "Tapjoy will be disabled"
    disabled_ext="${disabled_ext}TAPJOY;"
fi 

if [ x"$twitter_flags" != x ]; then
    echo "Twitter will be disabled"
    disabled_ext="${disabled_ext}TWITTER;"
fi 

if [ x"$playhaven_flags" != x ]; then
    echo "Playhaven will be disabled"
    disabled_ext="${disabled_ext}PLAYHAVEN;"
fi 

if [ x"$mobileapptracker_flags" != x ]; then
    echo "MobileAppTracker will be disabled"
    disabled_ext="${disabled_ext}MOBILEAPPTRACKER;"
fi 
#enter build dir
mkdir -p $BUILD_DIR
cd $BUILD_DIR
 
echo "Building resource list from ${LUASRC}"
ruby $MOAI_DIR/cmake/host-ios/build_resources.rb "${LUASRC}"

echo "Creating xcode project in `pwd`"

echo "DISABLED_EXT=$disabled_ext"

#create our makefiles
cmake -DDISABLED_EXT="$disabled_ext" -DMOAI_BOX2D=1 \
-DMOAI_CHIPMUNK=1 -DMOAI_CURL=0 -DMOAI_CRYPTO=1 -DMOAI_EXPAT=1 -DMOAI_FREETYPE=1 \
-DMOAI_HTTP_CLIENT=1 -DMOAI_JSON=1 -DMOAI_JPG=1 -DMOAI_LUAEXT=1 \
-DMOAI_MONGOOSE=1 -DMOAI_OGG=1 -DMOAI_OPENSSL=1 -DMOAI_SQLITE3=1 \
-DMOAI_TINYXML=1 -DMOAI_PNG=1 -DMOAI_SFMT=1 -DMOAI_LUAJIT=0 -DMOAI_VORBIS=1 $untz_param \
-DBUILD_IOS=true \
-DSIGN_IDENTITY="${SIGN_IDENTITY}" \
-DCMAKE_BUILD_TYPE=$buildtype_flags \
-DSQUIRREL_AND_BAER=1 \
-DCMAKE_OSX_ARCHITECTURES="${ARCH}" \
$adcolony_flags \
$billing_flags \
$chartboostflags \
$crittercism_flags \
$facebook_flags \
$push_flags \
$tapjoy_flags \
$twitter_flags \
$playhaven_flags \
-G "Xcode" \
$MOAI_DIR/cmake
