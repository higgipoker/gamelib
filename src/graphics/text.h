#pragma once

#include "renderable.h"

#include "color.h"
#include "window.h"
#include <SFML/Graphics.hpp>

namespace GameLib {

class Text : public Renderable {

  public:
    /**
     * @brief construct
     * @param fontfile path to font file on disk
     * @param label text to show
     */
    explicit Text(const std::string &fontfile);

    /**
     * @brief construct
     * @param fontfile path to font file on disk
     * @param label text to show
     */
    Text(const std::string &fontfile, const std::string &label);

    /**
     * @brief render
     * @param window window to render to
     */
    virtual void Render(Window &window) override;

    /**
     * @brief get a drawable context
     */
    virtual const sf::Drawable &Get() override;

    /**
     * @brief set text
     * @param label string to set
     */
    void SetText(const std::string &label);

    /**
     * @brief GetText
     * @return
     */
    std::string GetText();

    /**
     * @brief set font color
     * @param c color to set
     */
    void SetColor(const Color &c);

    /**
     * @brief get text width
     */
    Dimension GetSize() override;

  protected:
    /// an sfml font
    sf::Font font;

    /// sfml text object
    sf::Text text;
};

} // GameLib
