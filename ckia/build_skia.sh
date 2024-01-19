#!/bin/bash

set -euxo pipefail

echo "syncing git deps"
GIT_SYNC_DEPS_SHALLOW_CLONE=True GIT_SYNC_DEPS_SKIP_EMSDK=True python tools/git-sync-deps

echo "building skia libs"
./bin/gn gen out --args="$DEFAULT_ARGS $IS_OFFICIAL_BUILD $IS_COMPONENT_BUILD $USE_VULKAN $TARGET_ARGS"
./bin/gn args --list --short out
./bin/gn desc out :skia
ninja -C out

cd out || exit
if [[ "$IS_OFFICIAL_BUILD" == "is_official_build=true" ]]; then
    echo "packaging libs in an archive"
    if [[ "$IS_COMPONENT_BUILD" == "is_component_build=true" ]]; then 
        ZIP_NAME="shared_$TARGET.tar.gz"
        echo "zip name is $ZIP_NAME"
        if [[ "$TARGET" =~ "windows" ]]; then
            tar -czvf "$ZIP_NAME" ./*.dll icudtl.dat
        elif [[ "$TARGET" =~ "darwin" || "$TARGET" == "ios" ]]; then
            tar -czvf "$ZIP_NAME" ./*.dylib
        elif [[ "$TARGET" == "linux" || "$TARGET" == "android" ]]; then
            tar -czvf "$ZIP_NAME" ./*.so
        else
            echo "unknown platform $TARGET"
            tar -czvf "$ZIP_NAME" ./*.so
        fi
    else
        ZIP_NAME="static_$TARGET.tar.gz"
        echo "zip name is $ZIP_NAME"
        if [[ "$TARGET" =~ "windows" ]]; then
            tar -czvf "$ZIP_NAME" ./*.lib icudtl.dat
        elif [[ "$TARGET" =~ "darwin" || "$TARGET" =~ "linux" || "$TARGET" =~ "android" || "$TARGET" =~ "ios" ]]; then
            tar -czvf "$ZIP_NAME" ./*.a
        else
            echo "unknown platform $TARGET"
            tar -czvf "$ZIP_NAME" ./*.a
        fi
    fi
fi