Skia is a complete 2D graphic library for drawing Text, Geometries, and Images.

See full details, and build instructions, at https://skia.org.

This fork is basically the latest skia milestone + SkiaSharp's "C" bindings. 
The primary usecase is `ckia_sys` crate, but because skia's git repo is huge (hundreds of MB), i decided to keep the crate separate from the skia source.

To upgrade to a new milestone, just do the follow:
1. copy the following directories and install_files
  1. `ckia` directory which contains skiasharp's stable ABI headers/sources.
  2. this `README.md` file
  3. `.gitub/workspaces` which checks if our changes build properly for different targets. 
2. Add the following to `third_party/icu/SkLoadIcu.h` and `third_party/icu/SkLoadIcu.cpp`
  1. `SkLoadIcu.h`: 
    1. `bool SkLoadICUMemory(void*);` inside win32 def
    2. `static inline bool SkLoadICUMemory(void*) { return true; }` outside win32 def
  2. `SkLoadIcu.cpp`: 
  `bool SkLoadICUMemory(void* icudtl) { return init_icu(icudtl); }`
3. add the following to `BUILD.gn`.
```gn
# just above "skia_component("skia")" target declaration
ckia_public = [
  "ckia/include/gr_context.h",
  "ckia/include/paragraph.h",
  "ckia/include/sk_bitmap.h",
  "ckia/include/sk_canvas.h",
  "ckia/include/sk_codec.h",
  "ckia/include/sk_colorfilter.h",
  "ckia/include/sk_colorspace.h",
  "ckia/include/sk_data.h",
  "ckia/include/sk_document.h",
  "ckia/include/sk_drawable.h",
  "ckia/include/sk_font.h",
  "ckia/include/sk_general.h",
  "ckia/include/sk_graphics.h",
  "ckia/include/sk_imagefilter.h",
  "ckia/include/sk_image.h",
  "ckia/include/sk_maskfilter.h",
  "ckia/include/sk_matrix.h",
  "ckia/include/skottie_animation.h",
  "ckia/include/sk_paint.h",
  "ckia/include/sk_patheffect.h",
  "ckia/include/sk_path.h",
  "ckia/include/sk_picture.h",
  "ckia/include/sk_pixmap.h",
  "ckia/include/sk_region.h",
  "ckia/include/sk_rrect.h",
  "ckia/include/sk_runtimeeffect.h",
  "ckia/include/sksg_invalidation_controller.h",
  "ckia/include/sk_shader.h",
  "ckia/include/sk_stream.h",
  "ckia/include/sk_string.h",
  "ckia/include/sk_surface.h",
  "ckia/include/sk_svg.h",
  "ckia/include/sk_textblob.h",
  "ckia/include/sk_typeface.h",
  "ckia/include/sk_types.h",
  "ckia/include/sk_vertices.h",
]
ckia_sources = [
  "ckia/src/gr_context.cpp",
  "ckia/src/paragraph.cpp",
  "ckia/src/sk_all.c",
  "ckia/src/sk_bitmap.cpp",
  "ckia/src/sk_canvas.cpp",
  "ckia/src/sk_codec.cpp",
  "ckia/src/sk_colorfilter.cpp",
  "ckia/src/sk_colorspace.cpp",
  "ckia/src/sk_data.cpp",
  "ckia/src/sk_document.cpp",
  "ckia/src/sk_drawable.cpp",
  "ckia/src/sk_enums.cpp",
  "ckia/src/sk_font.cpp",
  "ckia/src/sk_general.cpp",
  "ckia/src/sk_graphics.cpp",
  "ckia/src/sk_image.cpp",
  "ckia/src/sk_imagefilter.cpp",
  "ckia/src/sk_maskfilter.cpp",
  "ckia/src/sk_matrix.cpp",
  "ckia/src/sk_paint.cpp",
  "ckia/src/sk_path.cpp",
  "ckia/src/sk_patheffect.cpp",
  "ckia/src/sk_picture.cpp",
  "ckia/src/sk_pixmap.cpp",
  "ckia/src/sk_region.cpp",
  "ckia/src/sk_rrect.cpp",
  "ckia/src/sk_runtimeeffect.cpp",
  "ckia/src/sk_shader.cpp",
  "ckia/src/sk_stream.cpp",
  "ckia/src/sk_string.cpp",
  "ckia/src/sk_structs.cpp",
  "ckia/src/sk_surface.cpp",
  "ckia/src/sk_svg.cpp",
  "ckia/src/sk_textblob.cpp",
  "ckia/src/sk_typeface.cpp",
  "ckia/src/sk_types_priv.h",
  "ckia/src/sk_vertices.cpp",
  "ckia/src/skottie_animation.cpp",
  "ckia/src/sksg_invalidation_controller.cpp",
]
# inside skia_component("skia") declaration, add these to the relevant sections
public += ckia_public  
sources += ckia_sources
defines += [ "SKIAC_IMPL=1" ]
```
4. skip cloning unused third party libs by commenting these in `DEPS`
  1. dawn
  2. jinja
  3. markupsafe
  4. abseil_cpp
  5. emsdk
  6. highway
  7. icu4x
  8. imgui
  9. libavif
  10. libgav1
  11. libgrapheme
  12. libjxl
  13. libyuv
  14. oboe
  15. opengl-registry
  16. swiftshader
  17. vello
  18. unicodetools