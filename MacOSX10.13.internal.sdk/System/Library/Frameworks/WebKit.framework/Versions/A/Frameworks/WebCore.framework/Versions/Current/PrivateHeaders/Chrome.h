/*
 * Copyright (C) 2006-2017 Apple Inc. All rights reserved.
 * Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
 * Copyright (C) 2012, Samsung Electronics. All rights reserved.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#pragma once

#include "Cursor.h"
#include "FocusDirection.h"
#include "HostWindow.h"
#include <wtf/Forward.h>
#include <wtf/RefPtr.h>

#if PLATFORM(COCOA)
OBJC_CLASS NSView;
#endif

namespace WebCore {

class ChromeClient;
class ColorChooser;
class ColorChooserClient;
class DateTimeChooser;
class DateTimeChooserClient;
class FileChooser;
class FileIconLoader;
class FloatRect;
class FrameLoadRequest;
class Element;
class Frame;
class Geolocation;
class HitTestResult;
class IntPoint;
class IntRect;
class NavigationAction;
class Page;
class PopupMenu;
class PopupMenuClient;
class PopupOpeningObserver;
class SearchPopupMenu;

struct DateTimeChooserParameters;
struct ViewportArguments;
struct WindowFeatures;
    
class Chrome : public HostWindow {
public:
    Chrome(Page&, ChromeClient&);
    virtual ~Chrome();

    ChromeClient& client() { return m_client; }

    // HostWindow methods.
    void invalidateRootView(const IntRect&) override;
    void invalidateContentsAndRootView(const IntRect&) override;
    void invalidateContentsForSlowScroll(const IntRect&) override;
    void scroll(const IntSize&, const IntRect&, const IntRect&) override;
#if USE(COORDINATED_GRAPHICS)
    void delegatedScrollRequested(const IntPoint& scrollPoint) override;
#endif
    IntPoint screenToRootView(const IntPoint&) const override;
    IntRect rootViewToScreen(const IntRect&) const override;
#if PLATFORM(IOS)
    IntPoint accessibilityScreenToRootView(const IntPoint&) const override;
    IntRect rootViewToAccessibilityScreen(const IntRect&) const override;
#endif
    PlatformPageClient platformPageClient() const override;
    void scrollbarsModeDidChange() const override;
    void setCursor(const Cursor&) override;
    void setCursorHiddenUntilMouseMoves(bool) override;

    void scheduleAnimation() override { }

    PlatformDisplayID displayID() const override;
    void windowScreenDidChange(PlatformDisplayID) override;

    FloatSize screenSize() const override;
    FloatSize availableScreenSize() const override;

    void scrollRectIntoView(const IntRect&) const;

    void contentsSizeChanged(Frame&, const IntSize&) const;

    WEBCORE_EXPORT void setWindowRect(const FloatRect&) const;
    WEBCORE_EXPORT FloatRect windowRect() const;

    FloatRect pageRect() const;

    void focus() const;
    void unfocus() const;

    bool canTakeFocus(FocusDirection) const;
    void takeFocus(FocusDirection) const;

    void focusedElementChanged(Element*) const;
    void focusedFrameChanged(Frame*) const;

    WEBCORE_EXPORT Page* createWindow(Frame&, const FrameLoadRequest&, const WindowFeatures&, const NavigationAction&) const;
    WEBCORE_EXPORT void show() const;

    bool canRunModal() const;
    void runModal() const;

    void setToolbarsVisible(bool) const;
    bool toolbarsVisible() const;

    void setStatusbarVisible(bool) const;
    bool statusbarVisible() const;

    void setScrollbarsVisible(bool) const;
    bool scrollbarsVisible() const;

    void setMenubarVisible(bool) const;
    bool menubarVisible() const;

    void setResizable(bool) const;

    bool canRunBeforeUnloadConfirmPanel();
    bool runBeforeUnloadConfirmPanel(const String& message, Frame&);

    void closeWindowSoon();

    void runJavaScriptAlert(Frame&, const String&);
    bool runJavaScriptConfirm(Frame&, const String&);
    bool runJavaScriptPrompt(Frame&, const String& message, const String& defaultValue, String& result);
    WEBCORE_EXPORT void setStatusbarText(Frame&, const String&);

    void mouseDidMoveOverElement(const HitTestResult&, unsigned modifierFlags);

    void setToolTip(const HitTestResult&);

    WEBCORE_EXPORT void print(Frame&);

    WEBCORE_EXPORT void enableSuddenTermination();
    WEBCORE_EXPORT void disableSuddenTermination();

#if ENABLE(INPUT_TYPE_COLOR)
    std::unique_ptr<ColorChooser> createColorChooser(ColorChooserClient&, const Color& initialColor);
#endif

    void runOpenPanel(Frame&, FileChooser&);
    void loadIconForFiles(const Vector<String>&, FileIconLoader&);

    void dispatchViewportPropertiesDidChange(const ViewportArguments&) const;

    bool requiresFullscreenForVideoPlayback();

#if PLATFORM(COCOA)
    WEBCORE_EXPORT void focusNSView(NSView*);
#endif

    bool selectItemWritingDirectionIsNatural();
    bool selectItemAlignmentFollowsMenuWritingDirection();
    bool hasOpenedPopup() const;
    RefPtr<PopupMenu> createPopupMenu(PopupMenuClient&) const;
    RefPtr<SearchPopupMenu> createSearchPopupMenu(PopupMenuClient&) const;

#if PLATFORM(IOS)
    // FIXME: Can we come up with a better name for this setter?
    void setDispatchViewportDataDidChangeSuppressed(bool dispatchViewportDataDidChangeSuppressed) { m_isDispatchViewportDataDidChangeSuppressed = dispatchViewportDataDidChangeSuppressed; }
#endif

    void didReceiveDocType(Frame&);

    void registerPopupOpeningObserver(PopupOpeningObserver&);
    void unregisterPopupOpeningObserver(PopupOpeningObserver&);

private:
    void notifyPopupOpeningObservers() const;

    Page& m_page;
    ChromeClient& m_client;
    PlatformDisplayID m_displayID { 0 };
    Vector<PopupOpeningObserver*> m_popupOpeningObservers;
#if PLATFORM(IOS)
    bool m_isDispatchViewportDataDidChangeSuppressed { false };
#endif
};

} // namespace WebCore
