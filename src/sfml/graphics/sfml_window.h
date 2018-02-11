///****************************************************************************
// * Copyright (c) 2018 P. Higgins
// *
// * This software is provided 'as-is', without any express or implied
// * warranty. In no event will the authors be held liable for any damages
// * arising from the use of this software.
// *
// * Permission is granted to anyone to use this software for any purpose,
// * including commercial applications, and to alter it and redistribute it
// * freely, subject to the following restrictions:
// *
// * 1. The origin of this software must not be misrepresented; you must not
// *    claim that you wrote the original software. If you use this software
// *    in a product, an acknowledgment in the product documentation would be
// *    appreciated but is not required.
// * 2. Altered source versions must be plainly marked as such, and must not be
// *    misrepresented as being the original software.
// * 3. This notice may not be removed or altered from any source distribution.
// ****************************************************************************/
///**
// * @file sfml_window
// * @author Paul Higgins <paul.samuel.higgins@gmail.com>
// * @date 2018
// * @brief description
// */
//#pragma once
//#include "../../graphics/window.h"

// namespace GameLib {

// class SFML_Window : public Window {
//  public:
//    /**
//     * @brief SFML_Window
//     */
//    SFML_Window(const std::string &title, unsigned int x, unsigned int y, unsigned int w, unsigned int h, bool fullsscreen);

//    /**
//      @brief destructor
//     */
//    ~SFML_Window();

//    /**
//     * @brief PollEvent
//     * @param wnd_event
//     * @return
//     */
//    virtual WindowEvent PollEvent(WindowEvent &wnd_event) override;

//    /**
//     * @brief clear window
//     */
//    virtual void Clear() override;

//    /**
//     * @brief flip back buffer
//     */
//    virtual void Present() override;

//    /**
//     * @brief is window still open
//     */
//    virtual bool IsOpen() override;

//    /**
//     * @brief show cursor
//     */
//    virtual void ShowCursor() override;

//    /**
//     * @brief hide cursor
//     */
//    virtual void HideCursor() override;

//    /**
//     * @brief SetIcon
//     * @param filename
//     */
//    virtual void SetIcon(const std::string &filename) override;

//    /**
//     * @brief Draw
//     * @param r
//     */
//    virtual void Draw(Renderable &r) override;

//    /**
//     * @brief Draw
//     * @param d
//     */
//    virtual void Draw(sf::Drawable &d) override;

//    /**
//     * @brief get position of window
//     */
//    Vector3 GetPosition() override {
//        return Vector3(window.getPosition().x, window.getPosition().y);
//    }

//    /**
//     * @brief get size of window
//     */
//    Vector3 GetSize() override {
//        return Vector3(window.getSize().x, window.getSize().y);
//    }

//    /**
//     * @brief VSync
//     * @param on
//     */
//    void VSync(bool on) override {
//        window.setVerticalSyncEnabled(on);
//    }

//    /**
//     * @brief set the viewport
//     * @param  v view to set
//     */
//    virtual void SetView(sf::View v) override;

//    /**
//     * @brief close the window
//     */
//    virtual void Close() override;

//  protected:
//    /// sfml window
//    sf::RenderWindow window;
//};

//} // namespace GameLib
