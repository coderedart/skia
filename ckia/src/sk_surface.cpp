/*
 * Copyright 2014 Google Inc.
 * Copyright 2015 Xamarin Inc.
 * Copyright 2017 Microsoft Corporation. All rights reserved.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#include "include/core/SkCanvas.h"
#include "include/core/SkData.h"
#include "include/core/SkImage.h"
#include "include/core/SkMaskFilter.h"
#include "include/core/SkMatrix.h"
#include "include/core/SkPaint.h"
#include "include/core/SkPath.h"
#include "include/core/SkPictureRecorder.h"
#include "include/core/SkSurface.h"
#include "include/gpu/GpuTypes.h"
#include "include/gpu/ganesh/SkSurfaceGanesh.h"
#include "ckia/include/sk_canvas.h"
#include "ckia/include/sk_data.h"
#include "ckia/include/sk_image.h"
#include "ckia/include/sk_paint.h"
#include "ckia/include/sk_path.h"
#include "ckia/include/sk_picture.h"
#include "ckia/include/sk_surface.h"

#include "ckia/src/sk_types_priv.h"
#if SK_METAL
#include "include/gpu/ganesh/mtl/SkSurfaceMetal.h"
#endif
// surface

sk_surface_t* sk_surface_new_null(int width, int height) {
    return ToSurface(SkSurfaces::Null(width, height).release());
}

sk_surface_t* sk_surface_new_raster(const sk_imageinfo_t* cinfo,
                                    size_t rowBytes,
                                    const sk_surfaceprops_t* props) {
    return ToSurface(
            SkSurfaces::Raster(AsImageInfo(cinfo), rowBytes, AsSurfaceProps(props)).release());
}

sk_surface_t* sk_surface_new_raster_direct(const sk_imageinfo_t* cinfo,
                                           void* pixels,
                                           size_t rowBytes,
                                           const sk_surface_raster_release_proc releaseProc,
                                           void* context,
                                           const sk_surfaceprops_t* props) {
    return ToSurface(SkSurfaces::WrapPixels(AsImageInfo(cinfo),
                                            pixels,
                                            rowBytes,
                                            releaseProc,
                                            context,
                                            AsSurfaceProps(props))
                             .release());
}

void sk_surface_unref(sk_surface_t* csurf) { SkSafeUnref(AsSurface(csurf)); }

sk_canvas_t* sk_surface_get_canvas(sk_surface_t* csurf) {
    return ToCanvas(AsSurface(csurf)->getCanvas());
}

sk_image_t* sk_surface_new_image_snapshot(sk_surface_t* csurf) {
    return ToImage(AsSurface(csurf)->makeImageSnapshot().release());
}

sk_image_t* sk_surface_new_image_snapshot_with_crop(sk_surface_t* surface,
                                                    const sk_irect_t* bounds) {
    return ToImage(AsSurface(surface)->makeImageSnapshot(*AsIRect(bounds)).release());
}

sk_surface_t* sk_surface_new_backend_render_target(gr_recording_context_t* context,
                                                   const gr_backendrendertarget_t* target,
                                                   gr_surfaceorigin_t origin,
                                                   sk_colortype_t colorType,
                                                   sk_colorspace_t* colorspace,
                                                   const sk_surfaceprops_t* props) {
    return ToSurface(SkSurfaces::WrapBackendRenderTarget(AsGrRecordingContext(context),
                                                         *AsGrBackendRenderTarget(target),
                                                         (GrSurfaceOrigin)origin,
                                                         (SkColorType)colorType,
                                                         sk_ref_sp(AsColorSpace(colorspace)),
                                                         AsSurfaceProps(props))
                             .release());
}

sk_surface_t* sk_surface_new_backend_texture(gr_recording_context_t* context,
                                             const gr_backendtexture_t* texture,
                                             gr_surfaceorigin_t origin,
                                             int samples,
                                             sk_colortype_t colorType,
                                             sk_colorspace_t* colorspace,
                                             const sk_surfaceprops_t* props) {
    return ToSurface(SkSurfaces::WrapBackendTexture(AsGrRecordingContext(context),
                                                    *AsGrBackendTexture(texture),
                                                    (GrSurfaceOrigin)origin,
                                                    samples,
                                                    (SkColorType)colorType,
                                                    sk_ref_sp(AsColorSpace(colorspace)),
                                                    AsSurfaceProps(props))
                             .release());
}

sk_surface_t* sk_surface_new_render_target(gr_recording_context_t* context,
                                           bool budgeted,
                                           const sk_imageinfo_t* cinfo,
                                           int sampleCount,
                                           gr_surfaceorigin_t origin,
                                           const sk_surfaceprops_t* props,
                                           bool shouldCreateWithMips) {
    return ToSurface(SkSurfaces::RenderTarget(AsGrRecordingContext(context),
                                              (skgpu::Budgeted)budgeted,
                                              AsImageInfo(cinfo),
                                              sampleCount,
                                              (GrSurfaceOrigin)origin,
                                              AsSurfaceProps(props),
                                              shouldCreateWithMips)
                             .release());
}

sk_surface_t* sk_surface_new_metal_layer(gr_recording_context_t* context,
                                         gr_mtl_handle_t layer,
                                         gr_surfaceorigin_t origin,
                                         int sampleCount,
                                         sk_colortype_t colorType,
                                         sk_colorspace_t* colorspace,
                                         const sk_surfaceprops_t* props,
                                         gr_mtl_handle_t* drawable) {
    return SK_ONLY_METAL(
            ToSurface(SkSurfaces::WrapCAMetalLayer(AsGrRecordingContext(context),
                                                      layer,
                                                      (GrSurfaceOrigin)origin,
                                                      sampleCount,
                                                      (SkColorType)colorType,
                                                      sk_ref_sp(AsColorSpace(colorspace)),
                                                      AsSurfaceProps(props),
                                                      drawable)
                              .release()),
            nullptr);
}

sk_surface_t* sk_surface_new_metal_view(gr_recording_context_t* context,
                                        gr_mtl_handle_t mtkView,
                                        gr_surfaceorigin_t origin,
                                        int sampleCount,
                                        sk_colortype_t colorType,
                                        sk_colorspace_t* colorspace,
                                        const sk_surfaceprops_t* props) {
    return SK_ONLY_METAL(ToSurface(SkSurfaces::WrapMTKView(AsGrRecordingContext(context),
                                                              mtkView,
                                                              (GrSurfaceOrigin)origin,
                                                              sampleCount,
                                                              (SkColorType)colorType,
                                                              sk_ref_sp(AsColorSpace(colorspace)),
                                                              AsSurfaceProps(props))
                                           .release()),
                         nullptr);
}

void sk_surface_draw(
        sk_surface_t* surface, sk_canvas_t* canvas, float x, float y, const sk_paint_t* paint) {
    AsSurface(surface)->draw(AsCanvas(canvas), x, y, AsPaint(paint));
}

bool sk_surface_peek_pixels(sk_surface_t* surface, sk_pixmap_t* pixmap) {
    return AsSurface(surface)->peekPixels(AsPixmap(pixmap));
}

bool sk_surface_read_pixels(sk_surface_t* surface,
                            sk_imageinfo_t* dstInfo,
                            void* dstPixels,
                            size_t dstRowBytes,
                            int srcX,
                            int srcY) {
    return AsSurface(surface)->readPixels(AsImageInfo(dstInfo), dstPixels, dstRowBytes, srcX, srcY);
}

const sk_surfaceprops_t* sk_surface_get_props(sk_surface_t* surface) {
    return ToSurfaceProps(&AsSurface(surface)->props());
}

gr_recording_context_t* sk_surface_get_recording_context(sk_surface_t* surface) {
    return ToGrRecordingContext(AsSurface(surface)->recordingContext());
}

// surface props

sk_surfaceprops_t* sk_surfaceprops_new(uint32_t flags, sk_pixelgeometry_t geometry) {
    return ToSurfaceProps(new SkSurfaceProps(flags, (SkPixelGeometry)geometry));
}

void sk_surfaceprops_delete(sk_surfaceprops_t* props) { delete AsSurfaceProps(props); }

uint32_t sk_surfaceprops_get_flags(sk_surfaceprops_t* props) {
    return AsSurfaceProps(props)->flags();
}

sk_pixelgeometry_t sk_surfaceprops_get_pixel_geometry(sk_surfaceprops_t* props) {
    return (sk_pixelgeometry_t)AsSurfaceProps(props)->pixelGeometry();
}
