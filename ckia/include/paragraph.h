#ifndef paragraph_DEFINED
#define paragraph_DEFINED

#include "ckia/include/sk_types.h"

SK_C_PLUS_PLUS_BEGIN_GUARD

// FontArguments
SK_C_API tl_font_arguments_t* tl_font_arguments_from_sk_fontarguments(
        const sk_fontarguments_t* args);
SK_C_API void tl_font_arguments_delete(tl_font_arguments_t* args);
// paragraph painter
// SK_C_API tl_paragraph_painter_t* tl_paragraph_painter_new();
// SK_C_API void tl_paragraph_painter_delete(tl_paragraph_painter_t* pp);

// SK_C_API tl_paragraph_painter_t* tl_paragraph_painter_new_args(sk_color_t color, float
// stroke_width, const tl_dash_path_effect* cdash_path_effect); SK_C_API sk_color_t
// tl_paragraph_painter_get_color(const tl_paragraph_painter_t* cparagraph_painter); SK_C_API float
// tl_paragraph_painter_get_stroke_width(const tl_paragraph_painter_t* cparagraph_painter); SK_C_API
// bool tl_paragraph_painter_get_dash_path_effect(const tl_paragraph_painter_t* cparagraph_painter);

// text style
SK_C_API tl_text_style_t* tl_text_style_new();
SK_C_API void tl_text_style_delete(tl_text_style_t* ts);
SK_C_API sk_color_t tl_text_style_get_color(const tl_text_style_t* ts);
SK_C_API void tl_text_style_set_color(tl_text_style_t* ts, sk_color_t color);
SK_C_API bool tl_text_style_has_foreground(const tl_text_style_t* ts);
SK_C_API sk_paint_t* tl_text_style_get_foreground(const tl_text_style_t* ts);
SK_C_API void tl_text_style_set_foreground_paint(const tl_text_style_t* ts,
                                                 const sk_paint_t* cpaint);
// paragraph style
SK_C_API tl_strut_style_t* tl_strut_style_new();
SK_C_API void tl_strut_style_delete(tl_strut_style_t* strut_style);
SK_C_API sk_fontstyle_t* tl_strut_get_font_style(const tl_strut_style_t* cstrut_style);
SK_C_API void tl_strut_set_font_style(tl_strut_style_t* strut_style,
                                      const sk_fontstyle_t* font_style);
SK_C_API float tl_strut_get_font_size(const tl_strut_style_t* cstrut_style);
SK_C_API void tl_strut_set_font_size(tl_strut_style_t* strut_style, float font_size);
SK_C_API float tl_strut_get_height(const tl_strut_style_t* cstrut_style);
SK_C_API void tl_strut_set_height(tl_strut_style_t* strut_style, float height);
SK_C_API float tl_strut_get_leading(const tl_strut_style_t* cstrut_style);
SK_C_API void tl_strut_set_leading(tl_strut_style_t* strut_style, float leading);
SK_C_API bool tl_strut_get_strut_enabled(const tl_strut_style_t* cstrut_style);
SK_C_API void tl_strut_set_strut_enabled(tl_strut_style_t* strut_style, bool enabled);
SK_C_API bool tl_strut_get_force_strut_height(const tl_strut_style_t* cstrut_style);
SK_C_API void tl_strut_set_force_strut_height(tl_strut_style_t* strut_style, bool force);
SK_C_API bool tl_strut_get_height_override(const tl_strut_style_t* cstrut_style);
SK_C_API void tl_strut_set_height_override(tl_strut_style_t* strut_style, bool override_height);

SK_C_API tl_paragraph_style_t* tl_paragraph_style_new();
SK_C_API void tl_paragraph_style_delete(tl_paragraph_style_t* paragraph_style);
SK_C_API tl_strut_style_t* tl_paragraph_style_get_strut_style(
        const tl_paragraph_style_t* cparagraph_style);
SK_C_API void tl_paragraph_style_set_strut_style(tl_paragraph_style_t* cparagraph_style,
                                                 const tl_strut_style_t* cstrut_style);
SK_C_API tl_text_style_t* tl_paragraph_style_get_text_style(
        const tl_paragraph_style_t* cparagraph_style);
SK_C_API void tl_paragraph_style_set_text_style(tl_paragraph_style_t* cparagraph_style,
                                                const tl_text_style_t* ctext_style);
SK_C_API tl_text_direction_t
tl_paragraph_style_get_text_direction(const tl_paragraph_style_t* cparagraph_style);
SK_C_API void tl_paragraph_style_set_text_direction(tl_paragraph_style_t* cparagraph_style,
                                                    tl_text_direction_t text_direction);
SK_C_API tl_text_align_t
tl_paragraph_style_get_text_align(const tl_paragraph_style_t* cparagraph_style);
SK_C_API void tl_paragraph_style_set_text_align(tl_paragraph_style_t* cparagraph_style,
                                                tl_text_align_t text_align);
SK_C_API size_t tl_paragraph_style_get_max_lines(const tl_paragraph_style_t* cparagraph_style);
SK_C_API void tl_paragraph_style_set_max_lines(tl_paragraph_style_t* cparagraph_style,
                                               size_t max_lines);
SK_C_API sk_string_t* tl_paragraph_style_get_ellipsis(const tl_paragraph_style_t* cparagraph_style);
SK_C_API void tl_paragraph_style_set_ellipsis(tl_paragraph_style_t* cparagraph_style,
                                              const sk_string_t* ellipsis);
SK_C_API float tl_paragraph_style_get_height(const tl_paragraph_style_t* cparagraph_style);
SK_C_API void tl_paragraph_style_set_height(tl_paragraph_style_t* cparagraph_style, float height);
SK_C_API tl_text_height_behavior_t
tl_paragraph_style_get_text_height_behavior(const tl_paragraph_style_t* cparagraph_style);
SK_C_API void tl_paragraph_style_set_text_height_behavior(
        tl_paragraph_style_t* cparagraph_style, tl_text_height_behavior_t text_height_behavior);
SK_C_API bool tl_paragraph_style_get_replace_tab_characters(
        const tl_paragraph_style_t* cparagraph_style);
SK_C_API void tl_paragraph_style_set_replace_tab_characters(tl_paragraph_style_t* cparagraph_style,
                                                            bool value);
SK_C_API bool tl_paragraph_style_get_apply_rounding_hack(
        const tl_paragraph_style_t* cparagraph_style);
SK_C_API void tl_paragraph_style_set_apply_rounding_hack(tl_paragraph_style_t* cparagraph_style,
                                                         bool value);
SK_C_API bool tl_paragraph_style_hinting_is_on(const tl_paragraph_style_t* cparagraph_style);
SK_C_API void tl_paragraph_style_turn_hinting_off(tl_paragraph_style_t* cparagraph_style);
SK_C_API bool tl_paragraph_style_unlimited_lines(const tl_paragraph_style_t* cparagraph_style);
SK_C_API bool tl_paragraph_style_ellipsized(const tl_paragraph_style_t* cparagraph_style);
SK_C_API tl_text_align_t
tl_paragraph_style_effective_align(const tl_paragraph_style_t* cparagraph_style);

// font collection
SK_C_API void tl_font_collection_ref(tl_font_collection_t* font_collection);
SK_C_API void tl_font_collection_unref(tl_font_collection_t* font_collection);
SK_C_API tl_font_collection_t* tl_font_collection_new();

SK_C_API void tl_font_collection_set_asset_font_manager(tl_font_collection_t* font_collection,
                                                        const sk_fontmgr_t* cfontmgr);
SK_C_API void tl_font_collection_set_dynamic_font_manager(tl_font_collection_t* font_collection,
                                                          const sk_fontmgr_t* cfontmgr);
SK_C_API void tl_font_collection_set_test_font_manager(tl_font_collection_t* font_collection,
                                                       const sk_fontmgr_t*);
SK_C_API void tl_font_collection_set_default_font_manager(tl_font_collection_t*,
                                                          const sk_fontmgr_t* cfontmgr);
SK_C_API void tl_font_collection_set_default_font_manager_with_family_name(
        tl_font_collection_t* font_collection,
        const sk_fontmgr_t* cfontmgr,
        const char* default_family_name);
SK_C_API sk_fontmgr_t* tl_font_collection_get_fallback_font_manager(const tl_font_collection_t*);
SK_C_API void tl_font_collection_disable_font_fallback(tl_font_collection_t* font_collection);
SK_C_API void tl_font_collection_enable_font_fallback(tl_font_collection_t* font_collection);
SK_C_API bool tl_font_collection_font_fallback_enabled(tl_font_collection_t* font_collection);

// paragraph builder
SK_C_API tl_paragraph_builder_t* tl_paragraph_builder_new(
        const tl_paragraph_style_t* paragraph_style, const tl_font_collection_t* font_collection);
SK_C_API void tl_paragraph_builder_push_style(tl_paragraph_builder_t* paragraph_builder,
                                              const tl_text_style_t* text_style);
SK_C_API void tl_paragraph_builder_pop(tl_paragraph_builder_t* paragraph_builder);
SK_C_API tl_text_style_t* tl_paragraph_builder_peek_style(
        tl_paragraph_builder_t* paragraph_builder);
SK_C_API void tl_paragraph_builder_add_text(tl_paragraph_builder_t* paragraph_builder,
                                            const char* text,
                                            size_t len);
SK_C_API void tl_paragraph_builder_add_place_holder(
        tl_paragraph_builder_t* paragraph_builder,
        const tl_placeholder_style_t* place_holder_style);
SK_C_API tl_paragraph_t* tl_paragraph_builder_build(tl_paragraph_builder_t* paragraph_builder);
/*
We return the pointer and set the length to size_t. DO NOT CALL ANY OTHER FN WHILE HOLDING ON TO
THIS PTR.
*/
SK_C_API char* tl_paragraph_builder_get_text(tl_paragraph_builder_t* paragraph_builder,
                                             size_t* len);
// reset everything except intiial paragraph style
SK_C_API void tl_paragraph_builder_reset(tl_paragraph_builder_t* paragraph_builder);

// paragraph
SK_C_API float tl_paragraph_get_max_width(tl_paragraph_t* paragraph);
SK_C_API float tl_paragraph_get_height(tl_paragraph_t* paragraph);
SK_C_API float tl_paragraph_get_min_intrinsic_width(tl_paragraph_t* paragraph);
SK_C_API float tl_paragraph_get_max_intrinsic_width(tl_paragraph_t* paragraph);
SK_C_API float tl_paragraph_get_alphabetic_baseline(tl_paragraph_t* paragraph);
SK_C_API float tl_paragraph_get_ideographic_baseline(tl_paragraph_t* paragraph);
SK_C_API float tl_paragraph_get_longest_line(tl_paragraph_t* paragraph);
SK_C_API bool tl_paragraph_get_did_exceed_max_lines(tl_paragraph_t* paragraph);
SK_C_API void tl_paragraph_layout(tl_paragraph_t* paragraph, float width);
SK_C_API void tl_paragraph_paint(tl_paragraph_t* paragraph, sk_canvas_t* canvas, float x, float y);
SK_C_API void tl_paragraph_get_glyph_position_at_coordinate(tl_paragraph_t* paragraph,
                                                            float dx,
                                                            float dy,
                                                            tl_position_with_affinity_t* result);
SK_C_API void tl_paragraph_get_word_boundary(tl_paragraph_t* paragraph,
                                             uint32_t offset,
                                             size_t* start,
                                             size_t* end);
SK_C_API size_t tl_paragraph_line_number(tl_paragraph_t* paragraph);
SK_C_API void tl_paragraph_mark_dirty(tl_paragraph_t* paragraph);
SK_C_API int32_t tl_paragraph_unresolved_glyphs(tl_paragraph_t* paragraph);
SK_C_API void tl_paragraph_update_text_align(tl_paragraph_t* paragraph, tl_text_align_t text_align);
SK_C_API void tl_paragraph_update_font_size(tl_paragraph_t* paragraph,
                                            size_t from,
                                            size_t to,
                                            float font_size);
SK_C_API void tl_paragraph_update_foreground_paint(tl_paragraph_t* paragraph,
                                                   size_t from,
                                                   size_t to,
                                                   const sk_paint_t* cpaint);
SK_C_API void tl_paragraph_update_background_paint(tl_paragraph_t* paragraph,
                                                   size_t from,
                                                   size_t to,
                                                   const sk_paint_t* cpaint);
SK_C_API int tl_paragraph_get_path(tl_paragraph_t* paragraph, int line_number, sk_path_t* dest);
SK_C_API sk_path_t* tl_paragraph_get_path_text_blob(sk_textblob_t* blob);
SK_C_API bool tl_paragraph_contains_emoji(tl_paragraph_t* paragraph, sk_textblob_t* blob);
SK_C_API bool tl_paragraph_contains_color_font_or_bitmap(tl_paragraph_t* paragraph, sk_textblob_t* blob);

// editing api
SK_C_API int tl_paragraph_get_line_number_at(tl_paragraph_t* paragraph, size_t index);
SK_C_API void tl_paragraph_get_actual_text_range(tl_paragraph_t* paragraph, int line_number, bool include_spaces, size_t* start, size_t* end);





SK_C_PLUS_PLUS_END_GUARD

#endif
