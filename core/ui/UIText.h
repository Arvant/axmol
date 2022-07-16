/****************************************************************************
Copyright (c) 2013-2016 Chukong Technologies Inc.
Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

https://axis-project.github.io/

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#ifndef __UILABEL_H__
#define __UILABEL_H__

#include "ui/UIWidget.h"
#include "ui/GUIExport.h"
#include "base/ccTypes.h"

/**
 * @addtogroup ui
 * @{
 */

NS_AX_BEGIN

class Label;
class Sprite;

namespace ui
{

/**
 *  For creating a system font or a TTF font Text
 */
class AX_GUI_DLL Text : public Widget, public axis::BlendProtocol
{

    DECLARE_CLASS_GUI_INFO

public:
    /** Type Text type.
     */
    enum class Type
    {
        SYSTEM,
        TTF
    };
    /**
     * Default constructor.
     * @js ctor
     * @lua new
     */
    Text();

    /**
     * Default destructor.
     * @js NA
     * @lua NA
     */
    virtual ~Text();

    /**
     * Create a Text object.
     *
     * @return An autoreleased Text object.
     */
    static Text* create();

    /**
     *  Create a Text object with textContent, fontName and fontSize.
     *  The fontName could be a system font name or a TTF file path.
     *  Usage:
     *  @code
     *       //create a system font UIText.
     *       Text *text = Text::create("Hello", "Arial", 20);
     *       //create a TTF font UIText.
     *       Text *text = Text::create("Hello", "xxx\xxx.ttf", 20);
     *  @endcode
     *
     * @param textContent Text content string.
     * @param fontName A given font name.
     * @param fontSize A given font size.
     * @return An autoreleased Text object.
     */
    static Text* create(std::string_view textContent, std::string_view fontName, float fontSize);

    /**
     * Changes the string value of label.
     *
     * @param text  String value.
     */
    void setString(std::string_view text);

    /**
     * Gets the string value of label.
     *
     * @return String value.
     */
    std::string_view getString() const;

    /**
     * Gets the string length of the label.
     * Note: This length will be larger than the raw string length,
     * if you want to get the raw string length,
     * you should call this->getString().size() instead.
     *
     * @return  String length.
     */
    ssize_t getStringLength() const;

    /**
     * Sets the font size of label.
     *
     * @param size The font size.
     */
    void setFontSize(float size);

    /**
     * Gets the font size of label.
     *
     * @return The font size.
     */
    float getFontSize() const;

    /**
     * Sets the font name of label.
     *  If you are trying to use a system font, you could just pass a font name
     * If you are trying to use a TTF, you should pass a file path to the TTF file
     * Usage:
     * @code
     *          //create a system font UIText
     *         Text *text = Text::create("Hello", "Arial", 20);
     *         // it will change the font to system font no matter the previous font type is TTF or system font
     *         text->setFontName("Marfelt");
     *         //it will change the font to TTF font no matter the previous font type is TTF or system font
     *         text->setFontName("xxxx/xxx.ttf");
     * @endcode
     * @param name Font name.
     */
    void setFontName(std::string_view name);

    /** Gets the font name.
     *
     * @return Font name.
     */
    std::string_view getFontName() const;

    /** Gets the font type.
     * @return The font type.
     */
    Type getType() const;

    /**
     * Sets the touch scale enabled of label.
     *
     * @param enabled Touch scale enabled of label.
     */
    void setTouchScaleChangeEnabled(bool enabled);

    /**
     * Gets the touch scale enabled of label.
     *
     * @return  Touch scale enabled of label.
     */
    bool isTouchScaleChangeEnabled() const;

    // override "getVirtualRendererSize" method of widget.
    virtual Vec2 getVirtualRendererSize() const override;

    // override "getVirtualRenderer" method of widget.
    virtual Node* getVirtualRenderer() override;

    /** Gets the render size in auto mode.
     *
     * @return The size of render size in auto mode.
     */
    virtual Vec2 getAutoRenderSize();

    /**
     * Returns the "class name" of widget.
     */
    virtual std::string getDescription() const override;

    /**
     * Sets the rendering size of the text, you should call this method
     * along with calling `ignoreContentAdaptWithSize(false)`, otherwise the text area
     * size is calculated by the real size of the text content.
     *
     * @param size The text rendering area size.
     *
     */
    void setTextAreaSize(const Vec2& size);

    /** Return the text rendering area size.
     *
     * @return The text rendering area size.
     */
    const Vec2& getTextAreaSize() const;

    /** Sets text horizontal alignment.
     *
     * @param alignment Horizontal text alignment type
     */
    void setTextHorizontalAlignment(TextHAlignment alignment);

    /** Gets text horizontal alignment.
     *
     * @return Horizontal text alignment type
     */
    TextHAlignment getTextHorizontalAlignment() const;

    /** Sets text vertical alignment.
     *
     * @param alignment vertical text alignment type
     */
    void setTextVerticalAlignment(TextVAlignment alignment);

    /** Gets text vertical alignment.
     *
     * @return Vertical text alignment type
     */
    TextVAlignment getTextVerticalAlignment() const;

    /** Sets text color.
     *
     * @param color Text color.
     */
    void setTextColor(const Color4B color);

    /** Gets text color.
     *
     * @return Text color.
     */
    const Color4B& getTextColor() const;

    /**
     * Enable shadow for the label.
     *
     * @todo support blur for shadow effect
     *
     * @param shadowColor The color of shadow effect.
     * @param offset The offset of shadow effect.
     * @param blurRadius The blur radius of shadow effect.
     */
    void enableShadow(const Color4B& shadowColor = Color4B::BLACK,
                      const Vec2& offset         = Vec2(2, -2),
                      int blurRadius             = 0);

    /**
     * Enable outline for the label.
     * It only works on IOS and Android when you use System fonts.
     *
     * @param outlineColor The color of outline.
     * @param outlineSize The size of outline.
     */
    void enableOutline(const Color4B& outlineColor, int outlineSize = 1);

    /** Only support for TTF.
     *
     * @param glowColor The color of glow.
     */
    void enableGlow(const Color4B& glowColor);

    /** Disable all text effects, including shadow, outline and glow.
     */
    void disableEffect();

    /**
     * Disable specific text effect.
     * Use LabelEffect parameter to specify which effect should be disabled.
     *
     * @see `LabelEffect`
     */
    void disableEffect(LabelEffect effect);

    /**
     * Return whether the shadow effect is enabled.
     */
    bool isShadowEnabled() const;
    /**
     * Return shadow effect offset value.
     */
    Vec2 getShadowOffset() const;
    /**
     * Return the shadow effect blur radius.
     */
    float getShadowBlurRadius() const;
    /**
     * Return the shadow effect color value.
     */
    Color4B getShadowColor() const;
    /**
     * Return the outline effect size value.
     */
    int getOutlineSize() const;
    /**
     * Return current effect type.
     */
    LabelEffect getLabelEffectType() const;
    /**
     * Return current effect color value.
     */
    Color4B getEffectColor() const;

    /**
     * Provides a way to treat each character like a Sprite.
     * @warning No support system font.
     */
    virtual Sprite* getLetter(int lettetIndex);

    /**
     * Sets the source blending function.
     *
     * @param blendFunc A structure with source and destination factor to specify pixel arithmetic. e.g.
     * {BlendFactor::ONE, BlendFactor::ONE}, {BlendFactor::SRC_ALPHA, BlendFactor::ONE_MINUS_SRC_ALPHA}.
     * @js NA
     * @lua NA
     */
    virtual void setBlendFunc(const BlendFunc& blendFunc) override;

    /**
     * Returns the blending function that is currently being used.
     *
     * @return A BlendFunc structure with source and destination factor which specified pixel arithmetic.
     * @js NA
     * @lua NA
     */
    virtual const BlendFunc& getBlendFunc() const override;

    virtual bool init() override;
    virtual bool init(std::string_view textContent, std::string_view fontName, float fontSize);

protected:
    virtual void initRenderer() override;
    virtual void onPressStateChangedToNormal() override;
    virtual void onPressStateChangedToPressed() override;
    virtual void onPressStateChangedToDisabled() override;
    virtual void onSizeChanged() override;

    void labelScaleChangedWithSize();
    virtual Widget* createCloneInstance() override;
    virtual void copySpecialProperties(Widget* model) override;
    virtual void adaptRenderers() override;

protected:
    bool _touchScaleChangeEnabled;
    float _normalScaleValueX;
    float _normalScaleValueY;
    std::string _fontName;
    float _fontSize;
    float _onSelectedScaleOffset;
    Label* _labelRenderer;
    bool _labelRendererAdaptDirty;
    Type _type;
};

}  // namespace ui

NS_AX_END

// end of ui group
/// @}

#endif /* defined(__CocoGUI__Label__) */
