#!/bin/python

sources_to_remove = """
./site
./resources/images
./resources/fonts
./resources/sksl
./resources/rivs
./resources/skottie
./infra
./dm
./tests
./fuzz
./bench
./demos.skia.org
./docs
./modules/canvaskit
./modules/pathkit
./tools/skqp
./tools/fiddle
./tools/flags
./tools/skiaserve
./tools/skpbench
./tools/unicode_comparison
./tools/doxygen
./tools/debugger
./tools/sk_app
./tools/testrunners
./tools/skp
./tools/window
./tools/gpu
./tools/viewer
./tools/fonts
./tools/perf-canvaskit-puppeteer
"""
from pathlib import Path
import shutil

# hack to preserve canvaskit.gni, which is imported by Build.gn via gn/toolchain/wasm.gni
canvaskit_gni_path = Path('./modules/canvaskit/canvaskit.gni')
canvaskit_gni_contents = canvaskit_gni_path.read_text()
for line in sources_to_remove.splitlines():
    shutil.rmtree(line)
canvaskit_gni_path.write_text(canvaskit_gni_contents)