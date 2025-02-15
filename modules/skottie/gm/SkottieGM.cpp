/*
 * Copyright 2017 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#include "gm/gm.h"
#include "include/codec/SkCodec.h"
#include "include/codec/SkGifDecoder.h"
#include "include/core/SkColor.h"
#include "include/core/SkStream.h"
#include "modules/skottie/include/Skottie.h"
#include "modules/skottie/include/SkottieProperty.h"
#include "modules/skottie/utils/SkottieUtils.h"
#include "modules/skresources/include/SkResources.h"
#include "tools/Resources.h"
#include "tools/fonts/FontToolUtils.h"

#include <cmath>
#include <vector>

namespace {

static constexpr char kWebFontResource[] = "fonts/Roboto-Regular.ttf";
static constexpr char kSkottieResource[] = "skottie/skottie_sample_webfont.json";

// Mock web font loader which serves a single local font (checked in under resources/).
class FakeWebFontProvider final : public skresources::ResourceProvider {
public:
    FakeWebFontProvider() : fTypeface(ToolUtils::CreateTypefaceFromResource(kWebFontResource)) {}

    sk_sp<SkTypeface> loadTypeface(const char[], const char[]) const override {
        return fTypeface;
    }

private:
    sk_sp<SkTypeface> fTypeface;

    using INHERITED = skresources::ResourceProvider;
};

} // namespace

class SkottieWebFontGM : public skiagm::GM {
public:
protected:
    SkString getName() const override { return SkString("skottie_webfont"); }

    SkISize getISize() override { return SkISize::Make(kSize, kSize); }

    void onOnceBeforeDraw() override {
        if (auto stream = GetResourceAsStream(kSkottieResource)) {
            fAnimation = skottie::Animation::Builder()
                            .setFontManager(ToolUtils::TestFontMgr())
                            .setResourceProvider(sk_make_sp<FakeWebFontProvider>())
                            .make(stream.get());
        }
    }

    DrawResult onDraw(SkCanvas* canvas, SkString* errorMsg) override {
        if (!fAnimation) {
            *errorMsg = "No animation";
            return DrawResult::kFail;
        }

        auto dest = SkRect::MakeWH(kSize, kSize);
        fAnimation->render(canvas, &dest);
        return DrawResult::kOk;
    }

    bool onAnimate(double nanos) override {
        if (!fAnimation) {
            return false;
        }

        const auto duration = fAnimation->duration();
        fAnimation->seek(std::fmod(1e-9 * nanos, duration) / duration);
        return true;
    }

private:
    inline static constexpr SkScalar kSize = 800;

    sk_sp<skottie::Animation> fAnimation;

    using INHERITED = skiagm::GM;
};

DEF_GM(return new SkottieWebFontGM;)

class SkottieColorizeGM : public skiagm::GM {
public:
    SkottieColorizeGM(const char* name, const char* resource)
        : fName(name)
        , fResource(resource)
    {}

protected:
    SkString getName() const override { return SkStringPrintf("skottie_colorize_%s", fName); }

    SkISize getISize() override { return SkISize::Make(kSize, kSize); }

    void onOnceBeforeDraw() override {
        if (auto stream = GetResourceAsStream(fResource)) {
            fPropManager = std::make_unique<skottie_utils::CustomPropertyManager>();
            fAnimation   = skottie::Animation::Builder()
                              .setFontManager(ToolUtils::TestFontMgr())
                              .setPropertyObserver(fPropManager->getPropertyObserver())
                              .make(stream.get());
            fColorProps  = fPropManager->getColorProps();
            fTextProps   = fPropManager->getTextProps();
        }
    }

    DrawResult onDraw(SkCanvas* canvas, SkString* errorMsg) override {
        if (!fAnimation) {
            *errorMsg = "No animation";
            return DrawResult::kFail;
        }

        auto dest = SkRect::MakeWH(kSize, kSize);
        fAnimation->render(canvas, &dest);
        return DrawResult::kOk;
    }

    bool onAnimate(double nanos) override {
        if (!fAnimation) {
            return false;
        }

        const auto duration = fAnimation->duration();
        fAnimation->seek(std::fmod(1e-9 * nanos, duration) / duration);
        return true;
    }

    bool onChar(SkUnichar uni) override {
        static constexpr SkColor kColors[] = {
            SK_ColorBLACK,
            SK_ColorRED,
            SK_ColorGREEN,
            SK_ColorYELLOW,
            SK_ColorCYAN,
        };

        if (uni == 'c') {
            fColorIndex = (fColorIndex + 1) % std::size(kColors);
            for (const auto& prop : fColorProps) {
                fPropManager->setColor(prop, kColors[fColorIndex]);
            }
            for (const auto& prop : fTextProps) {
                auto txtval = fPropManager->getText(prop);
                txtval.fFillColor = kColors[fColorIndex];
                fPropManager->setText(prop, txtval);
            }
            return true;
        }

        return false;
    }

private:
    inline static constexpr SkScalar kSize = 800;

    const char*                                                fName;
    const char*                                                fResource;

    sk_sp<skottie::Animation>                                  fAnimation;
    std::unique_ptr<skottie_utils::CustomPropertyManager>      fPropManager;
    std::vector<skottie_utils::CustomPropertyManager::PropKey> fColorProps,
                                                               fTextProps;
    size_t                                                     fColorIndex = 0;

    using INHERITED = skiagm::GM;
};

DEF_GM(return new SkottieColorizeGM("color", "skottie/skottie_sample_search.json");)
DEF_GM(return new SkottieColorizeGM("text" , "skottie/skottie-text-animator-5.json");)

class SkottieMultiFrameGM : public skiagm::GM {
public:
protected:
    SkString getName() const override { return SkString("skottie_multiframe"); }

    SkISize getISize() override { return SkISize::Make(kSize, kSize); }

    void onOnceBeforeDraw() override {
        if (auto stream = GetResourceAsStream("skottie/skottie_sample_multiframe.json")) {
            fAnimation = skottie::Animation::Builder()
                            .setResourceProvider(sk_make_sp<MultiFrameResourceProvider>())
                            .make(stream.get());
            fAnimation->seek(0);
        }
    }

    DrawResult onDraw(SkCanvas* canvas, SkString* errorMsg) override {
        if (!fAnimation) {
            *errorMsg = "No animation";
            return DrawResult::kFail;
        }

        auto dest = SkRect::MakeWH(kSize, kSize);
        fAnimation->render(canvas, &dest);
        return DrawResult::kOk;
    }

    bool onAnimate(double nanos) override {
        if (!fAnimation) {
            return false;
        }

        const auto duration = fAnimation->duration();
        fAnimation->seek(std::fmod(1e-9 * nanos, duration) / duration);
        return true;
    }

private:
    class MultiFrameResourceProvider final : public skresources::ResourceProvider {
    public:
        sk_sp<skresources::ImageAsset> loadImageAsset(const char[], const char[],
                                                      const char[]) const override {
            sk_sp<SkData> data = GetResourceAsData("images/flightAnim.gif");
            SkASSERT(data);
            std::unique_ptr<SkCodec> codec = SkGifDecoder::Decode(data, nullptr);
            SkASSERT(codec);
            return skresources::MultiFrameImageAsset::Make(std::move(codec));
        }
    };

    inline static constexpr SkScalar kSize = 800;

    sk_sp<skottie::Animation> fAnimation;

    using INHERITED = skiagm::GM;
};

DEF_GM(return new SkottieMultiFrameGM;)
