#include "ckia/include/paragraph.h"
#include <memory>
#include <optional>
#include "ckia/src/sk_types_priv.h"
#include "include/core/SkRefCnt.h"
#include "include/core/SkString.h"
#include "include/core/SkTypeface.h"
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
void tl_text_style_clear_foreground_color(tl_text_style_t* ts) {
    AsTlTextStyle(ts)->clearForegroundColor();
}
bool tl_text_style_has_background(const tl_text_style_t* ts) {
    return AsTlTextStyle(ts)->hasBackground();
}
sk_paint_t* tl_text_style_get_background(const tl_text_style_t* ts) {
    SkPaint* paint = new SkPaint();
    *paint = AsTlTextStyle(ts)->getBackground();  // how do you allocate the paint on heap w
    return ToPaint(paint);
}
void tl_text_style_set_background_paint(tl_text_style_t* ts, const sk_paint_t* cpaint) {
    AsTlTextStyle(ts)->setBackgroundPaint(*AsPaint(cpaint));
}
void tl_text_style_clear_background_color(tl_text_style_t* ts) {
    AsTlTextStyle(ts)->clearBackgroundColor();
}
void tl_text_style_get_decoration(const tl_text_style_t* ts, tl_decoration_t* result) {
    auto dec = AsTlTextStyle(ts)->getDecoration();
    result->fColor = dec.fColor;
    result->fMode = (tl_text_decoration_mode_t)dec.fMode;
    result->fStyle = (tl_text_decoration_style_t)dec.fStyle;
    result->fThicknessMultiplier = dec.fThicknessMultiplier;
    result->fType = (tl_text_decoration_t)dec.fType;
}
tl_text_decoration_t tl_text_style_get_decoration_type(const tl_text_style_t* ts) {
    return (tl_text_decoration_t)AsTlTextStyle(ts)->getDecorationType();
}
tl_text_decoration_mode_t tl_text_style_get_decoration_mode(const tl_text_style_t* ts) {
    return (tl_text_decoration_mode_t)AsTlTextStyle(ts)->getDecorationMode();
}
sk_color_t tl_text_style_get_decoration_color(const tl_text_style_t* ts) {
    return AsTlTextStyle(ts)->getDecorationColor();
}
tl_text_decoration_style_t tl_text_style_get_decoration_style(const tl_text_style_t* ts) {
    return (tl_text_decoration_style_t)AsTlTextStyle(ts)->getDecorationStyle();
}
float tl_text_style_get_decoration_thickness_multiplier(const tl_text_style_t* ts) {
    return AsTlTextStyle(ts)->getDecorationThicknessMultiplier();
}
sk_fontstyle_t* tl_text_style_get_font_style(const tl_text_style_t* ts) {
    return ToFontStyle(new SkFontStyle(AsTlTextStyle(ts)->getFontStyle()));
}
size_t tl_text_style_get_shadow_number(const tl_text_style_t* ts) {
    return AsTlTextStyle(ts)->getShadowNumber();
}
size_t tl_text_style_get_font_feature_number(const tl_text_style_t* ts) {
    return AsTlTextStyle(ts)->getFontFeatureNumber();
}
float tl_text_style_get_font_size(const tl_text_style_t* ts) {
    return AsTlTextStyle(ts)->getFontSize();
}
float tl_text_style_get_baseline_shift(const tl_text_style_t* ts) {
    return AsTlTextStyle(ts)->getBaselineShift();
}
float tl_text_style_get_height(const tl_text_style_t* ts) { return AsTlTextStyle(ts)->getHeight(); }
bool tl_text_style_get_height_override(const tl_text_style_t* ts) {
    return AsTlTextStyle(ts)->getHeightOverride();
}
bool tl_text_style_get_half_leading(const tl_text_style_t* ts) {
    return AsTlTextStyle(ts)->getHalfLeading();
}
float tl_text_style_get_letter_spacing(const tl_text_style_t* ts) {
    return AsTlTextStyle(ts)->getLetterSpacing();
}
float tl_text_style_get_word_spacing(const tl_text_style_t* ts) {
    return AsTlTextStyle(ts)->getWordSpacing();
}
sk_typeface_t* tl_text_style_get_typeface(const tl_text_style_t* ts) {
    return ToTypeface(AsTlTextStyle(ts)->refTypeface().release());
}
sk_string_t* tl_text_style_get_locale(const tl_text_style_t* ts) {
    return ToString(new SkString(AsTlTextStyle(ts)->getLocale()));
}
tl_text_baseline_t tl_text_style_get_text_baseline(const tl_text_style_t* ts) {
    return (tl_text_baseline_t)AsTlTextStyle(ts)->getTextBaseline();
}
void tl_text_style_set_decoration_type(tl_text_style_t* ts, tl_text_decoration_t value) {
    AsTlTextStyle(ts)->setDecoration((skia::textlayout::TextDecoration)value);
}
void tl_text_style_set_decoration_mode(tl_text_style_t* ts, tl_text_decoration_mode_t value) {
    AsTlTextStyle(ts)->setDecorationMode(skia::textlayout::TextDecorationMode(value));
}
void tl_text_style_set_decoration_color(tl_text_style_t* ts, sk_color_t value) {
    AsTlTextStyle(ts)->setDecorationColor(value);
}
void tl_text_style_set_decoration_style(tl_text_style_t* ts, tl_text_decoration_style_t value) {
    AsTlTextStyle(ts)->setDecorationStyle(skia::textlayout::TextDecorationStyle(value));
}
void tl_text_style_set_decoration_thickness_multiplier(tl_text_style_t* ts, float value) {
    AsTlTextStyle(ts)->setDecorationThicknessMultiplier(value);
}
void tl_text_style_set_font_style(tl_text_style_t* ts, const sk_fontstyle_t* value) {
    AsTlTextStyle(ts)->setFontStyle(*AsFontStyle(value));
}
void tl_text_style_add_shadow(tl_text_style_t* ts, tl_text_shadow_t* shadow) {
    skia::textlayout::TextShadow s;
    s.fBlurSigma = shadow->fBlurSigma;
    s.fColor = shadow->fColor;
    s.fOffset.fX = shadow->fOffset.x;
    s.fOffset.fY = shadow->fOffset.y;
    AsTlTextStyle(ts)->addShadow(s);
}
void tl_text_style_add_font_feature(tl_text_style_t* ts,
                                    const sk_string_t* font_feature,
                                    size_t value) {
    AsTlTextStyle(ts)->addFontFeature(*AsString(font_feature), value);
}
void tl_text_style_set_font_size(tl_text_style_t* ts, float value) {
    AsTlTextStyle(ts)->setFontSize(value);
}
void tl_text_style_set_baseline_shift(tl_text_style_t* ts, float value) {
    AsTlTextStyle(ts)->setBaselineShift(value);
}
void tl_text_style_set_height(tl_text_style_t* ts, float value) {
    AsTlTextStyle(ts)->setHeight(value);
}
void tl_text_style_set_height_override(tl_text_style_t* ts, bool value) {
    AsTlTextStyle(ts)->setHeightOverride(value);
}
void tl_text_style_set_half_leading(tl_text_style_t* ts, bool value) {
    AsTlTextStyle(ts)->setHalfLeading(value);
}
void tl_text_style_set_letter_spacing(tl_text_style_t* ts, float value) {
    AsTlTextStyle(ts)->setLetterSpacing(value);
}
void tl_text_style_set_word_spacing(tl_text_style_t* ts, float value) {
    AsTlTextStyle(ts)->setWordSpacing(value);
}
void tl_text_style_set_typeface(tl_text_style_t* ts, const sk_typeface_t* value) {
    AsTlTextStyle(ts)->setTypeface(sk_ref_sp(AsTypeface(value)));
}
void tl_text_style_set_locale(tl_text_style_t* ts, const sk_string_t* value) {
    AsTlTextStyle(ts)->setLocale(*AsString(value));
}
void tl_text_style_set_text_baseline(tl_text_style_t* ts, tl_text_baseline_t value) {
    AsTlTextStyle(ts)->setTextBaseline((skia::textlayout::TextBaseline)value);
}

void tl_text_style_reset_shadows(tl_text_style_t* ts) { AsTlTextStyle(ts)->resetShadows(); }
void tl_text_style_reset_font_features(tl_text_style_t* ts) {
    AsTlTextStyle(ts)->resetFontFeatures();
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

size_t tl_font_collection_find_typefaces(tl_font_collection_t* font_collection,
                                         const tl_vec_of_sk_strings_t* vec,
                                         const sk_fontstyle_t* fs,
                                         sk_typeface_t** vec_typeface_or_null,
                                         size_t vec_len) {
    auto typefaces = AsTlFontCollection(font_collection)
                             ->findTypefaces(*(std::vector<SkString>*)vec, *AsFontStyle(fs));
    if (typefaces.empty()) {
        return 0;
    }
    if (vec_typeface_or_null == nullptr) {
        return typefaces.size();
    }
    size_t copy_len = vec_len;
    if (typefaces.size() < vec_len) {
        copy_len = typefaces.size();
    }
    for (size_t i = 0; i < copy_len; i++) {
        vec_typeface_or_null[i] = ToTypeface(typefaces[i].release());
    }
    return copy_len;
}
size_t tl_font_collection_find_typefaces2(tl_font_collection_t* font_collection,
                                          const tl_vec_of_sk_strings_t* vec,
                                          const sk_fontstyle_t* fs,
                                          const tl_font_arguments_t* font_args_or_null,
                                          sk_typeface_t** vec_typeface_or_null,
                                          size_t vec_len) {
    std::optional<skia::textlayout::FontArguments> args = std::nullopt;
    if (font_args_or_null != nullptr) {
        args = std::make_optional<skia::textlayout::FontArguments>(
                skia::textlayout::FontArguments(*AsTlFontArguments(font_args_or_null)));
    }
    auto typefaces = AsTlFontCollection(font_collection)
                             ->findTypefaces(*(std::vector<SkString>*)vec, *AsFontStyle(fs), args);
    if (typefaces.empty()) {
        return 0;
    }
    if (vec_typeface_or_null == nullptr) {
        return typefaces.size();
    }
    size_t copy_len = vec_len;
    if (typefaces.size() < vec_len) {
        copy_len = typefaces.size();
    }
    for (size_t i = 0; i < copy_len; i++) {
        vec_typeface_or_null[i] = ToTypeface(typefaces[i].release());
    }
    return copy_len;
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
                                                 const tl_font_collection_t* font_collection) {
    return ToTlParagraphBuilder(
            skia::textlayout::ParagraphBuilder::make(*AsTlParagraphStyle(paragraph_style),
                                                     sk_ref_sp(AsTlFontCollection(font_collection)))
                    .release());
}
void tl_paragraph_builder_delete(tl_paragraph_builder_t* builder) {
    std::unique_ptr<skia::textlayout::ParagraphBuilder>(AsTlParagraphBuilder(builder));
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

void tl_paragraph_delete(tl_paragraph_t* paragraph) {
    std::unique_ptr<skia::textlayout::Paragraph>(AsTlParagraph(paragraph));
}

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
size_t tl_paragraph_get_rects_for_range(tl_paragraph_t* paragraph,
                                        uint32_t start,
                                        uint32_t end,
                                        tl_rect_height_style_t hstyle,
                                        tl_rect_width_style_t wstyle,
                                        tl_text_box_t* vec_text_box_or_null,
                                        size_t vec_len) {
    auto boxes =
            AsTlParagraph(paragraph)->getRectsForRange(start,
                                                       end,
                                                       skia::textlayout::RectHeightStyle(hstyle),
                                                       skia::textlayout::RectWidthStyle(wstyle));
    // if nullptr, return size so that they can allocate the buffer and retry
    if (vec_text_box_or_null == nullptr) {
        return boxes.size();
    }
    size_t copy_len = vec_len;
    if (boxes.size() < copy_len) {
        copy_len = boxes.size();
    }
    for (size_t i = 0; i < copy_len; i++) {
        auto rect = boxes[i].rect;
        vec_text_box_or_null[i].rect.left = rect.fLeft;
        vec_text_box_or_null[i].rect.top = rect.fTop;
        vec_text_box_or_null[i].rect.right = rect.fRight;
        vec_text_box_or_null[i].rect.bottom = rect.fBottom;
        vec_text_box_or_null[i].direction = (tl_text_direction_t)boxes[i].direction;
    }
    return copy_len;
}
size_t tl_paragraph_get_rects_for_placeholders(tl_paragraph_t* paragraph,
                                               tl_text_box_t* vec_text_box_or_null,
                                               size_t vec_len) {
    auto boxes = AsTlParagraph(paragraph)->getRectsForPlaceholders();
    // if nullptr, return size so that they can allocate the buffer and retry
    if (vec_text_box_or_null == nullptr) {
        return boxes.size();
    }
    size_t copy_len = vec_len;
    if (boxes.size() < copy_len) {
        copy_len = boxes.size();
    }
    for (size_t i = 0; i < copy_len; i++) {
        auto rect = boxes[i].rect;
        vec_text_box_or_null[i].rect.left = rect.fLeft;
        vec_text_box_or_null[i].rect.top = rect.fTop;
        vec_text_box_or_null[i].rect.right = rect.fRight;
        vec_text_box_or_null[i].rect.bottom = rect.fBottom;
        vec_text_box_or_null[i].direction = (tl_text_direction_t)boxes[i].direction;
    }
    return copy_len;
}
void tl_paragraph_get_glyph_position_at_coordinate(tl_paragraph_t* paragraph,
                                                   float dx,
                                                   float dy,
                                                   tl_position_with_affinity_t* result) {
    auto pa = AsTlParagraph(paragraph)->getGlyphPositionAtCoordinate(dx, dy);
    result->affinity = (tl_affinity_t)pa.affinity;
    result->position = pa.position;
}
void tl_paragraph_get_word_boundary(tl_paragraph_t* paragraph,
                                    uint32_t offset,
                                    size_t* start,
                                    size_t* end) {
    auto range = AsTlParagraph(paragraph)->getWordBoundary(offset);
    *start = range.start;
    *end = range.end;
}
size_t tl_paragraph_line_number(tl_paragraph_t* paragraph) {
    return AsTlParagraph(paragraph)->lineNumber();
}
void tl_paragraph_mark_dirty(tl_paragraph_t* paragraph) { AsTlParagraph(paragraph)->markDirty(); }
int32_t tl_paragraph_unresolved_glyphs(tl_paragraph_t* paragraph) {
    return AsTlParagraph(paragraph)->unresolvedGlyphs();
}
void tl_paragraph_update_text_align(tl_paragraph_t* paragraph, tl_text_align_t text_align) {
    AsTlParagraph(paragraph)->updateTextAlign(skia::textlayout::TextAlign(text_align));
}
void tl_paragraph_update_font_size(tl_paragraph_t* paragraph,
                                   size_t from,
                                   size_t to,
                                   float font_size) {
    AsTlParagraph(paragraph)->updateFontSize(from, to, font_size);
}
SK_C_API void tl_paragraph_update_foreground_paint(tl_paragraph_t* paragraph,
                                                   size_t from,
                                                   size_t to,
                                                   const sk_paint_t* cpaint) {
    AsTlParagraph(paragraph)->updateForegroundPaint(from, to, *AsPaint(cpaint));
}
SK_C_API void tl_paragraph_update_background_paint(tl_paragraph_t* paragraph,
                                                   size_t from,
                                                   size_t to,
                                                   const sk_paint_t* cpaint) {
    AsTlParagraph(paragraph)->updateBackgroundPaint(from, to, *AsPaint(cpaint));
}
SK_C_API int tl_paragraph_get_path(tl_paragraph_t* paragraph, int line_number, sk_path_t* dest) {
    return AsTlParagraph(paragraph)->getPath(line_number, AsPath(dest));
}
SK_C_API sk_path_t* tl_paragraph_get_path_text_blob(sk_textblob_t* blob) {
    return ToPath(new SkPath(skia::textlayout::Paragraph::GetPath(AsTextBlob(blob))));
}
SK_C_API bool tl_paragraph_contains_emoji(tl_paragraph_t* paragraph, sk_textblob_t* blob) {
    return AsTlParagraph(paragraph)->containsEmoji(AsTextBlob(blob));
}
SK_C_API bool tl_paragraph_contains_color_font_or_bitmap(tl_paragraph_t* paragraph,
                                                         sk_textblob_t* blob) {
    return AsTlParagraph(paragraph)->containsColorFontOrBitmap(AsTextBlob(blob));
}

// editing api
SK_C_API int tl_paragraph_get_line_number_at(tl_paragraph_t* paragraph, size_t index) {
    return AsTlParagraph(paragraph)->getLineNumberAt(index);
}
SK_C_API void tl_paragraph_get_actual_text_range(tl_paragraph_t* paragraph,
                                                 int line_number,
                                                 bool include_spaces,
                                                 size_t* start,
                                                 size_t* end) {
    auto range = AsTlParagraph(paragraph)->getActualTextRange(line_number, include_spaces);
    *start = range.start;
    *end = range.end;
}
