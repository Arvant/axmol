/****************************************************************************
 Copyright (c) 2013      Zynga Inc.
 Copyright (c) 2013-2016 Chukong Technologies Inc.
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 Copyright (c) 2019-present Axmol Engine contributors (see AUTHORS.md).

 https://axmolengine.github.io/

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
#pragma once

#include "2d/Font.h"
#include <string>

/* freetype fwd decls */

typedef struct FT_LibraryRec_* FT_Library;
typedef struct FT_StreamRec_* FT_Stream;
typedef struct FT_FaceRec_* FT_Face;
typedef struct FT_StrokerRec_* FT_Stroker;
typedef struct FT_BBox_ FT_BBox;

NS_AX_BEGIN

/**
 * @addtogroup _2d
 * @{
 */

/** @class FontFreeType
* @brief FontFreeType is a class of rendering ttf/ttc characters
*/
class AX_DLL FontFreeType : public Font
{
public:
    static const int DistanceMapSpread;
    static constexpr int DEFAULT_BASE_FONT_SIZE = 32;

     /**
     * @remark: if you want enable stream parsing, you need do one of follow steps
     *          a. disable .ttf compress on .apk, see:
     *             https://simdsoft.com/notes/#build-apk-config-nocompress-file-type-at-appbuildgradle
     *          b. uncomporess .ttf to disk by yourself.
     */
    static void setStreamParsingEnabled(bool bEnabled) { _streamParsingEnabled = bEnabled; }
    static bool isStreamParsingEnabled() { return _streamParsingEnabled; }

    /**
     * @brief Set the Missing Glyph Character, by default render square for missing characters
     *
     * @param charCode
     */
    static void setMissingGlyphCharacter(char32_t charCode) { _mssingGlyphCharacter = charCode; };

    /**
     * @brief Whether enable SDF font rendering globally, by default: disabled, since axmol-2.0.1
     *
     * @param enabled
     */
    static void setShareDistanceFieldEnabled(bool enabled) { _shareDistanceFieldEnabled = enabled; }
    static bool isShareDistanceFieldEnabled() { return _shareDistanceFieldEnabled; }

    /**
     * @brief TrueType fonts with native bytecode hinting * *
     *
     *   All applications that handle TrueType fonts with native hinting must
     *   be aware that TTFs expect different rounding of vertical font
     *   dimensions.  The application has to cater for this, especially if it
     *   wants to rely on a TTF's vertical data (for example, to properly align
     *   box characters vertically).
     *   - Since freetype-2.8.1 TureType matrics isn't sync to size_matrics
     *   - By default it's enabled for compatible with cocos2d-x-4.0 or older with freetype-2.5.5
     *   - Please see freetype.h
     */
    static void setNativeBytecodeHintingEnabled(bool bEnabled) { _doNativeBytecodeHinting = bEnabled; }
    static bool isNativeBytecodeHintingEnabled() { return _doNativeBytecodeHinting; }

    static FontFreeType* create(std::string_view fontPath,
                                int faceSize,
                                GlyphCollection glyphs,
                                std::string_view customGlyphs,
                                bool distanceFieldEnabled = false,
                                float outline             = 0);

    static void shutdownFreeType();

    bool isDistanceFieldEnabled() const { return _distanceFieldEnabled; }

    float getOutlineSize() const { return _outlineSize; }

    void renderCharAt(unsigned char* dest,
                      int posX,
                      int posY,
                      unsigned char* bitmap,
                      int bitmapWidth,
                      int bitmapHeight,
                      int atlasWidth,
                      int atlasHeight);

    int* getHorizontalKerningForTextUTF32(const std::u32string& text, int& outNumLetters) const override;

    unsigned char* getGlyphBitmap(char32_t charCode, int& outWidth, int& outHeight, Rect& outRect, int& xAdvance);

    int getFontAscender() const;
    const char* getFontFamily() const;
    std::string_view getFontName() const { return _fontName; }

    virtual FontAtlas* newFontAtlas() override;
    virtual int getFontMaxHeight() const override { return _lineHeight; }

    std::string_view getGlyphCollection() const;

    static void releaseFont(std::string_view fontName);

    static FT_Library getFTLibrary();

private:
    static FT_Library _FTlibrary;
    static bool _FTInitialized;
    static bool _streamParsingEnabled;
    static bool _doNativeBytecodeHinting;
    static bool _shareDistanceFieldEnabled;
    static char32_t _mssingGlyphCharacter;

    static bool initFreeType();

    FontFreeType(bool distanceFieldEnabled = false, float outline = 0);
    virtual ~FontFreeType();

    bool loadFontFace(std::string_view fontPath, int faceSize);

    int getHorizontalKerningForChars(uint64_t firstChar, uint64_t secondChar) const;
    unsigned char* getGlyphBitmapWithOutline(unsigned int glyphIndex, FT_BBox& bbox);

    void setGlyphCollection(GlyphCollection glyphs, std::string_view customGlyphs);

    FT_Face _fontFace;
    FT_Stream _fontStream;
    FT_Stroker _stroker;

    std::string _fontName;
    int _faceSize;
    bool _distanceFieldEnabled;
    float _outlineSize;
    int _ascender;
    int _descender;
    int _lineHeight;

    GlyphCollection _usedGlyphs;
    std::string _customGlyphs;
};

// end of _2d group
/// @}

NS_AX_END
