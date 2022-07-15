/****************************************************************************
 Copyright (c) 2014-2016 Chukong Technologies Inc.
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
#pragma once

/// @cond DO_NOT_SHOW

#include "ui/UIWebView/UIWebView.h"
#include "platform/CCGLView.h"
#include "base/CCDirector.h"
#include "platform/CCFileUtils.h"

NS_AX_BEGIN
namespace ui
{
WebView::WebView() : _impl(new WebViewImpl(this)) {}

WebView::~WebView()
{
    AX_SAFE_DELETE(_impl);
}

WebView* WebView::create()
{
    auto webView = new WebView();
    if (webView->init())
    {
        webView->autorelease();
        return webView;
    }
    AX_SAFE_DELETE(webView);
    return nullptr;
}

void WebView::setJavascriptInterfaceScheme(std::string_view scheme)
{
    _impl->setJavascriptInterfaceScheme(scheme);
}

void WebView::loadData(const axis::Data& data,
                       std::string_view MIMEType,
                       std::string_view encoding,
                       std::string_view baseURL)
{
    _impl->loadData(data, MIMEType, encoding, baseURL);
}

void WebView::loadHTMLString(std::string_view string, std::string_view baseURL)
{
    _impl->loadHTMLString(string, baseURL);
}

void WebView::loadURL(std::string_view url)
{
    this->loadURL(url, false);
}

void WebView::loadURL(std::string_view url, bool cleanCachedData)
{
    _impl->loadURL(url, cleanCachedData);
}

void WebView::loadFile(std::string_view fileName)
{
    _impl->loadFile(fileName);
}

void WebView::stopLoading()
{
    _impl->stopLoading();
}

void WebView::reload()
{
    _impl->reload();
}

bool WebView::canGoBack()
{
    return _impl->canGoBack();
}

bool WebView::canGoForward()
{
    return _impl->canGoForward();
}

void WebView::goBack()
{
    _impl->goBack();
}

void WebView::goForward()
{
    _impl->goForward();
}

void WebView::evaluateJS(std::string_view js)
{
    _impl->evaluateJS(js);
}

void WebView::setScalesPageToFit(bool const scalesPageToFit)
{
    _impl->setScalesPageToFit(scalesPageToFit);
}

void WebView::draw(axis::Renderer* renderer, axis::Mat4 const& transform, uint32_t flags)
{
    axis::ui::Widget::draw(renderer, transform, flags);
    _impl->draw(renderer, transform, flags);
}

void WebView::setVisible(bool visible)
{
    Node::setVisible(visible);
    if (!visible || isRunning())
    {
        _impl->setVisible(visible);
    }
}

void WebView::setOpacityWebView(float opacity)
{
    _impl->setOpacityWebView(opacity);
}

float WebView::getOpacityWebView() const
{
    return _impl->getOpacityWebView();
}

void WebView::setBackgroundTransparent()
{
    _impl->setBackgroundTransparent();
};

void WebView::onEnter()
{
    Widget::onEnter();
    if (isVisible())
    {
        _impl->setVisible(true);
    }
}

void WebView::onExit()
{
    Widget::onExit();
    _impl->setVisible(false);
}

void WebView::setBounces(bool bounces)
{
    _impl->setBounces(bounces);
}

axis::ui::Widget* WebView::createCloneInstance()
{
    return WebView::create();
}

void WebView::copySpecialProperties(Widget* model)
{
    WebView* webView = dynamic_cast<WebView*>(model);
    if (webView)
    {
        this->_impl                 = webView->_impl;
        this->_onShouldStartLoading = webView->_onShouldStartLoading;
        this->_onDidFinishLoading   = webView->_onDidFinishLoading;
        this->_onDidFailLoading     = webView->_onDidFailLoading;
        this->_onJSCallback         = webView->_onJSCallback;
    }
}

void WebView::setOnDidFailLoading(const ccWebViewCallback& callback)
{
    _onDidFailLoading = callback;
}

void WebView::setOnDidFinishLoading(const ccWebViewCallback& callback)
{
    _onDidFinishLoading = callback;
}

void WebView::setOnShouldStartLoading(const std::function<bool(WebView* sender, std::string_view url)>& callback)
{
    _onShouldStartLoading = callback;
}

void WebView::setOnJSCallback(const ccWebViewCallback& callback)
{
    _onJSCallback = callback;
}

std::function<bool(WebView* sender, std::string_view url)> WebView::getOnShouldStartLoading() const
{
    return _onShouldStartLoading;
}

WebView::ccWebViewCallback WebView::getOnDidFailLoading() const
{
    return _onDidFailLoading;
}

WebView::ccWebViewCallback WebView::getOnDidFinishLoading() const
{
    return _onDidFinishLoading;
}

WebView::ccWebViewCallback WebView::getOnJSCallback() const
{
    return _onJSCallback;
}

}  // namespace ui
NS_AX_END  // namespace axis

/// @endcond
