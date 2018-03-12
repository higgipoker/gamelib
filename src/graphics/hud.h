/****************************************************************************
 * Copyright (c) 2018 P. Higgins
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 ****************************************************************************/
/**
 * @file hud.h
 * @author Paul Higgins <paul.samuel.higgins@gmail.com>
 * @date 2018
 * @brief description
 */
#include "renderable.h"

namespace GameLib {

/**
 * @brief like a "window" in widget systems but called hud to avoid confusion
 */
class Hud : public Renderable {
  public:
    /**
     * @brief Hud
     */
    Hud();

    /**
     * @brief ~Hud
     */
    virtual ~Hud();

    /**
     * @brief Render
     * @param window
     */
    virtual void Render(Window &window) = 0;

    /**
     * @brief Hide
     */
    virtual void Hide();

    /**
     * @brief Show
     */
    virtual void Show();

    /**
     * @brief to control widgets
     * @param msg
     */
    virtual void Send(const std::string &msg);
    virtual void Send(const std::string &msg, std::vector<std::string> params);
    virtual void Send(const std::string &msg, std::vector<int> params);

    /// like the old standard windowing widgety system, each window(hud) can have children
    std::vector<Hud *> children;

    /// convenient access to parent
    Hud *parent = nullptr;
};

} // namespace GameLib
