#include "ckia/include/paragraph.h"
#include "ckia/src/sk_types_priv.h"
#include "include/core/SkRefCnt.h"
#include "include/core/SkString.h"
#include "modules/skparagraph/include/FontArguments.h"
#include "modules/skparagraph/include/FontCollection.h"
#include "modules/skparagraph/include/ParagraphBuilder.h"
#include "modules/skparagraph/include/ParagraphPainter.h"
#include "modules/skparagraph/include/ParagraphStyle.h"
#include "modules/skparagraph/include/TextStyle.h"

tl_font_arguments_t* tl_font_arguments_from_sk_fontarguments(const sk_fontarguments_t* args) {
    return ToTlFontArguments(new skia::textlayout::FontArguments(*AsSkFontArguments(args)));
}
void tl_font_arguments_delete(tl_font_arguments_t* args) { delete AsTlFontArguments(args); }

// text style
tl_text_style_t* tl_text_style_new() { return ToTlTextStyle(new skia::textlayout::TextStyle()); }
void tl_text_style_delete(tl_text_style_t* ts) { delete AsTlTextStyle(ts); }
sk_color_t tl_text_style_get_color(const tl_text_style_t* cts) {
    return AsTlTextStyle(cts)->getColor();
}
void tl_text_style_set_color(tl_text_style_t* ts, sk_color_t color) {
    AsTlTextStyle(ts)->setColor(color);
}
bool tl_text_style_has_foreground(const tl_text_style_t* cts) {
    return AsTlTextStyle(cts)->hasForeground();
}
sk_paint_t* tl_text_style_get_foreground(const tl_text_style_t* cts) {
    SkPaint* paint = new SkPaint();
    *paint = AsTlTextStyle(cts)->getForeground();  // how do you allocate the paint on heap w
    return ToPaint(paint);
}
void tl_text_style_set_foreground_paint(tl_text_style_t* ts, const sk_paint_t* cpaint) {
    AsTlTextStyle(ts)->setForegroundPaint(*AsPaint(cpaint));
}

// paragraph painter
// tl_paragraph_painter_t* tl_paragraph_painter_new() {
//     return ToTlParagraphPainter(new skia::textlayout::ParagraphPainter());
// }
// void tl_paragraph_painter_delete(tl_paragraph_painter_t* pp) {
//     delete AsTlParagraphPainter(pp);
// }
// tl_paragraph_painter_t* tl_paragraph_painter_new_args(sk_color_t color, float stroke_width, const
// tl_dash_path_effect* cdash_path_effect) {

// }
// sk_color_t tl_paragraph_painter_get_color(const tl_paragraph_painter_t* cparagraph_painter) {

// }
// float tl_paragraph_painter_get_stroke_width(const tl_paragraph_painter_t* cparagraph_painter) {

// }
// bool tl_paragraph_painter_get_dash_path_effect(const tl_paragraph_painter_t* cparagraph_painter)
// {

// }

// paragraph style
tl_strut_style_t* tl_strut_style_new() {
    return ToTlStrutStyle(new skia::textlayout::StrutStyle());
}
void tl_strut_style_delete(tl_strut_style_t* strut_style) { delete AsTlStrutStyle(strut_style); }
sk_fontstyle_t* tl_strut_get_font_style(const tl_strut_style_t* cstrut_style) {
    SkFontStyle* style = new SkFontStyle();
    *style = AsTlStrutStyle(cstrut_style)->getFontStyle();
    return ToFontStyle(style);
}
void tl_strut_set_font_style(tl_strut_style_t* strut_style, const sk_fontstyle_t* font_style) {
    AsTlStrutStyle(strut_style)->setFontStyle(*AsFontStyle(font_style));
}
float tl_strut_get_font_size(const tl_strut_style_t* cstrut_style) {
    return AsTlStrutStyle(cstrut_style)->getFontSize();
}
void tl_strut_set_font_size(tl_strut_style_t* strut_style, float font_size) {
    AsTlStrutStyle(strut_style)->setFontSize(font_size);
}
float tl_strut_get_height(const tl_strut_style_t* cstrut_style) {
    return AsTlStrutStyle(cstrut_style)->getHeight();
}
void tl_strut_set_height(tl_strut_style_t* strut_style, float height) {
    AsTlStrutStyle(strut_style)->setHeight(height);
}
float tl_strut_get_leading(const tl_strut_style_t* cstrut_style) {
    return AsTlStrutStyle(cstrut_style)->getLeading();
}
void tl_strut_set_leading(tl_strut_style_t* strut_style, float leading) {
    AsTlStrutStyle(strut_style)->setLeading(leading);
}
bool tl_strut_get_strut_enabled(const tl_strut_style_t* cstrut_style) {
    return AsTlStrutStyle(cstrut_style)->getStrutEnabled();
}
void tl_strut_set_strut_enabled(tl_strut_style_t* strut_style, bool enabled) {
    AsTlStrutStyle(strut_style)->setStrutEnabled(enabled);
}
bool tl_strut_get_force_strut_height(const tl_strut_style_t* cstrut_style) {
    return AsTlStrutStyle(cstrut_style)->getForceStrutHeight();
}
void tl_strut_set_force_strut_height(tl_strut_style_t* strut_style, bool force) {
    AsTlStrutStyle(strut_style)->setForceStrutHeight(force);
}
bool tl_strut_get_height_override(const tl_strut_style_t* cstrut_style) {
    return AsTlStrutStyle(cstrut_style)->getHeightOverride();
}
void tl_strut_set_height_override(tl_strut_style_t* strut_style, bool override_height) {
    AsTlStrutStyle(strut_style)->setHeightOverride(override_height);
}
bool tl_strut_get_half_leading(const tl_strut_style_t* cstrut_style) {
    return AsTlStrutStyle(cstrut_style)->getHalfLeading();
}
void tl_strut_set_half_leading(tl_strut_style_t* strut_style, bool half_leading) {
    AsTlStrutStyle(strut_style)->setHalfLeading(half_leading);
}

tl_paragraph_style_t* tl_paragraph_style_new() {
    return ToTlParagraphStyle(new skia::textlayout::ParagraphStyle());
}
void tl_paragraph_style_delete(tl_paragraph_style_t* paragraph_style) {
    delete AsTlParagraphStyle(paragraph_style);
}
tl_strut_style_t* tl_paragraph_style_get_strut_style(const tl_paragraph_style_t* cparagraph_style) {
    auto style_ref = AsTlParagraphStyle(cparagraph_style)->getStrutStyle();
    return ToTlStrutStyle(new skia::textlayout::StrutStyle(style_ref));
}
void tl_paragraph_style_set_strut_style(tl_paragraph_style_t* cparagraph_style,
                                        const tl_strut_style_t* cstrut_style) {
    AsTlParagraphStyle(cparagraph_style)->setStrutStyle(*AsTlStrutStyle(cstrut_style));
}
tl_text_style_t* tl_paragraph_style_get_text_style(const tl_paragraph_style_t* cparagraph_style) {
    skia::textlayout::TextStyle* ts = new skia::textlayout::TextStyle();
    *ts = AsTlParagraphStyle(cparagraph_style)->getTextStyle();
    return ToTlTextStyle(ts);
}
void tl_paragraph_style_set_text_style(tl_paragraph_style_t* cparagraph_style,
                                       const tl_text_style_t* ctext_style) {
    AsTlParagraphStyle(cparagraph_style)->setTextStyle(*AsTlTextStyle(ctext_style));
}
tl_text_direction_t tl_paragraph_style_get_text_direction(
        const tl_paragraph_style_t* cparagraph_style) {
    return (tl_text_direction_t)AsTlParagraphStyle(cparagraph_style)->getTextDirection();
}
void tl_paragraph_style_set_text_direction(tl_paragraph_style_t* paragraph_style,
                                           tl_text_direction_t text_direction) {
    AsTlParagraphStyle(paragraph_style)
            ->setTextDirection((skia::textlayout::TextDirection)text_direction);
}
tl_text_align_t tl_paragraph_style_get_text_align(const tl_paragraph_style_t* cparagraph_style) {
    return (tl_text_align_t)AsTlParagraphStyle(cparagraph_style)->getTextAlign();
}
void tl_paragraph_style_set_text_align(tl_paragraph_style_t* paragraph_style,
                                       tl_text_align_t text_align) {
    AsTlParagraphStyle(paragraph_style)->setTextAlign((skia::textlayout::TextAlign)text_align);
}
size_t tl_paragraph_style_get_max_lines(const tl_paragraph_style_t* cparagraph_style) {
    return AsTlParagraphStyle(cparagraph_style)->getMaxLines();
}
void tl_paragraph_style_set_max_lines(tl_paragraph_style_t* paragraph_style, size_t max_lines) {
    AsTlParagraphStyle(paragraph_style)->setMaxLines(max_lines);
}
sk_string_t* tl_paragraph_style_get_ellipsis(const tl_paragraph_style_t* cparagraph_style) {
    return ToString(new SkString(AsTlParagraphStyle(cparagraph_style)->getEllipsis()));
}
void tl_paragraph_style_set_ellipsis(tl_paragraph_style_t* paragraph_style,
                                     const sk_string_t* ellipsis) {
    AsTlParagraphStyle(paragraph_style)->setEllipsis(*AsString(ellipsis));
}
float tl_paragraph_style_get_height(const tl_paragraph_style_t* cparagraph_style) {
    return AsTlParagraphStyle(cparagraph_style)->getHeight();
}
void tl_paragraph_style_set_height(tl_paragraph_style_t* paragraph_style, float height) {
    AsTlParagraphStyle(paragraph_style)->setHeight(height);
}
tl_text_height_behavior_t tl_paragraph_style_get_text_height_behavior(
        const tl_paragraph_style_t* cparagraph_style) {
    return (tl_text_height_behavior_t)AsTlParagraphStyle(cparagraph_style)->getTextHeightBehavior();
}
void tl_paragraph_style_set_text_height_behavior(tl_paragraph_style_t* paragraph_style,
                                                 tl_text_height_behavior_t text_height_behavior) {
    AsTlParagraphStyle(paragraph_style)
            ->setTextHeightBehavior((skia::textlayout::TextHeightBehavior)text_height_behavior);
}
bool tl_paragraph_style_get_replace_tab_characters(const tl_paragraph_style_t* cparagraph_style) {
    return AsTlParagraphStyle(cparagraph_style)->getReplaceTabCharacters();
}
void tl_paragraph_style_set_replace_tab_characters(tl_paragraph_style_t* paragraph_style,
                                                   bool value) {
    AsTlParagraphStyle(paragraph_style)->setReplaceTabCharacters(value);
}
bool tl_paragraph_style_get_apply_rounding_hack(const tl_paragraph_style_t* cparagraph_style) {
    return AsTlParagraphStyle(cparagraph_style)->getApplyRoundingHack();
}
void tl_paragraph_style_set_apply_rounding_hack(tl_paragraph_style_t* paragraph_style, bool value) {
    AsTlParagraphStyle(paragraph_style)->setApplyRoundingHack(value);
}
bool tl_paragraph_style_hinting_is_on(const tl_paragraph_style_t* cparagraph_style) {
    return AsTlParagraphStyle(cparagraph_style)->hintingIsOn();
}
void tl_paragraph_style_turn_hinting_off(tl_paragraph_style_t* paragraph_style) {
    AsTlParagraphStyle(paragraph_style)->turnHintingOff();
}
bool tl_paragraph_style_unlimited_lines(const tl_paragraph_style_t* cparagraph_style) {
    return AsTlParagraphStyle(cparagraph_style)->unlimited_lines();
}
bool tl_paragraph_style_ellipsized(const tl_paragraph_style_t* cparagraph_style) {
    return AsTlParagraphStyle(cparagraph_style)->ellipsized();
}
tl_text_align_t tl_paragraph_style_effective_align(const tl_paragraph_style_t* cparagraph_style) {
    return (tl_text_align_t)AsTlParagraphStyle(cparagraph_style)->effective_align();
}

// font collection
void tl_font_collection_ref(tl_font_collection_t* font_collection) {
    AsTlFontCollection(font_collection)->ref();
}
void tl_font_collection_unref(tl_font_collection_t* font_collection) {
    AsTlFontCollection(font_collection)->unref();
}
tl_font_collection_t* tl_font_collection_new() {
    return ToTlFontCollection(sk_make_sp<skia::textlayout::FontCollection>().release());
}

void tl_font_collection_set_asset_font_manager(tl_font_collection_t* font_collection,
                                               const sk_fontmgr_t* cfontmgr) {
    AsTlFontCollection(font_collection)->setAssetFontManager(sk_ref_sp(AsFontMgr(cfontmgr)));
}
void tl_font_collection_set_dynamic_font_manager(tl_font_collection_t* font_collection,
                                                 const sk_fontmgr_t* cfontmgr) {
    AsTlFontCollection(font_collection)->setDynamicFontManager(sk_ref_sp(AsFontMgr(cfontmgr)));
}
void tl_font_collection_set_test_font_manager(tl_font_collection_t* font_collection,
                                              const sk_fontmgr_t* cfontmgr) {
    AsTlFontCollection(font_collection)->setTestFontManager(sk_ref_sp(AsFontMgr(cfontmgr)));
}
void tl_font_collection_set_default_font_manager(tl_font_collection_t* font_collection,
                                                 const sk_fontmgr_t* cfontmgr) {
    AsTlFontCollection(font_collection)->setDefaultFontManager(sk_ref_sp(AsFontMgr(cfontmgr)));
}
void tl_font_collection_set_default_font_manager_with_family_name(
        tl_font_collection_t* font_collection,
        const sk_fontmgr_t* cfontmgr,
        const char* default_family_name) {
    AsTlFontCollection(font_collection)
            ->setDefaultFontManager(sk_ref_sp(AsFontMgr(cfontmgr)), default_family_name);
}
sk_fontmgr_t* tl_font_collection_get_fallback_font_manager(
        const tl_font_collection_t* cfont_collection) {
    return ToFontMgr(AsTlFontCollection(cfont_collection)->getFallbackManager().release());
}
void tl_font_collection_disable_font_fallback(tl_font_collection_t* font_collection) {
    AsTlFontCollection(font_collection)->disableFontFallback();
}
void tl_font_collection_enable_font_fallback(tl_font_collection_t* font_collection) {
    AsTlFontCollection(font_collection)->enableFontFallback();
}
bool tl_font_collection_font_fallback_enabled(tl_font_collection_t* font_collection) {
    return AsTlFontCollection(font_collection)->fontFallbackEnabled();
}

// paragraph builder
tl_paragraph_builder_t* tl_paragraph_builder_new(const tl_paragraph_style_t* paragraph_style,
                                                 tl_font_collection_t* font_collection) {
    return ToTlParagraphBuilder(
            skia::textlayout::ParagraphBuilder::make(*AsTlParagraphStyle(paragraph_style),
                                                     sk_ref_sp(AsTlFontCollection(font_collection)))
                    .release());
}
void tl_paragraph_builder_push_style(tl_paragraph_builder_t* paragraph_builder,
                                     const tl_text_style_t* text_style) {
    AsTlParagraphBuilder(paragraph_builder)->pushStyle(*AsTlTextStyle(text_style));
}
void tl_paragraph_builder_pop(tl_paragraph_builder_t* paragraph_builder) {
    AsTlParagraphBuilder(paragraph_builder)->pop();
}
tl_text_style_t* tl_paragraph_builder_peek_style(tl_paragraph_builder_t* paragraph_builder) {
    return ToTlTextStyle(
            new skia::textlayout::TextStyle(AsTlParagraphBuilder(paragraph_builder)->peekStyle()));
}
void tl_paragraph_builder_add_text(tl_paragraph_builder_t* paragraph_builder,
                                   const char* text,
                                   size_t len) {
    AsTlParagraphBuilder(paragraph_builder)->addText(text, len);
}
void tl_paragraph_builder_add_place_holder(tl_paragraph_builder_t* paragraph_builder,
                                           const tl_placeholder_style_t* place_holder_style) {
    auto style = skia::textlayout::PlaceholderStyle();
    style.fAlignment = (skia::textlayout::PlaceholderAlignment)place_holder_style->fAlignment;
    style.fBaseline = skia::textlayout::TextBaseline(place_holder_style->fBaseline);
    style.fBaselineOffset = place_holder_style->fBaselineOffset;
    style.fHeight = place_holder_style->fHeight;
    style.fWidth = place_holder_style->fWidth;
    AsTlParagraphBuilder(paragraph_builder)->addPlaceholder(style);
}
tl_paragraph_t* tl_paragraph_builder_build(tl_paragraph_builder_t* paragraph_builder) {
    return ToTlParagraph(AsTlParagraphBuilder(paragraph_builder)->Build().release());
}
/*
We return the pointer and set the length to size_t. DO NOT CALL ANY OTHER FN WHILE HOLDING ON TO
THIS PTR.
*/
SK_C_API char* tl_paragraph_builder_get_text(tl_paragraph_builder_t* paragraph_builder,
                                             size_t* len) {
    auto text = AsTlParagraphBuilder(paragraph_builder)->getText();
    *len = text.size();
    return text.data();
}
// reset everything except intiial paragraph style
SK_C_API void tl_paragraph_builder_reset(tl_paragraph_builder_t* paragraph_builder) {
    AsTlParagraphBuilder(paragraph_builder)->Reset();
}

// paragraph

float tl_paragraph_get_max_width(tl_paragraph_t* paragraph) {
    return AsTlParagraph(paragraph)->getMaxWidth();
}
float tl_paragraph_get_height(tl_paragraph_t* paragraph) {
    return AsTlParagraph(paragraph)->getHeight();
}
float tl_paragraph_get_min_intrinsic_width(tl_paragraph_t* paragraph) {
    return AsTlParagraph(paragraph)->getMinIntrinsicWidth();
}
float tl_paragraph_get_max_intrinsic_width(tl_paragraph_t* paragraph) {
    return AsTlParagraph(paragraph)->getMaxIntrinsicWidth();
}
float tl_paragraph_get_alphabetic_baseline(tl_paragraph_t* paragraph) {
    return AsTlParagraph(paragraph)->getAlphabeticBaseline();
}
float tl_paragraph_get_ideographic_baseline(tl_paragraph_t* paragraph) {
    return AsTlParagraph(paragraph)->getIdeographicBaseline();
}
float tl_paragraph_get_longest_line(tl_paragraph_t* paragraph) {
    return AsTlParagraph(paragraph)->getLongestLine();
}
bool tl_paragraph_get_did_exceed_max_lines(tl_paragraph_t* paragraph) {
    return AsTlParagraph(paragraph)->didExceedMaxLines();
}
void tl_paragraph_layout(tl_paragraph_t* paragraph, float width) {
    AsTlParagraph(paragraph)->layout(width);
}
void tl_paragraph_paint(tl_paragraph_t* paragraph, sk_canvas_t* canvas, float x, float y) {
    AsTlParagraph(paragraph)->paint(AsCanvas(canvas), x, y);
}
