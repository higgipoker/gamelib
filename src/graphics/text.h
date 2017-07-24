#pragma once

#include "renderable.h"

#include <SFML/Graphics.hpp>
#include "window.h"
#include "color.h"

namespace GameLib {

class Text : public Renderable {

public:

	/**
     * \brief construct
     * \param fontfile path to font file on disk
     * \param label text to show
     */
    Text( const std::string &fontfile);

    /**
     * \brief construct
     * \param fontfile path to font file on disk
     * \param label text to show
     */
    Text( const std::string &fontfile, const std::string &label);

    /**
     * \brief render
     * \param window window to render to
     */
    virtual void Render(Window &window) override;

    /**
     * \brief get a drawable context
     */
    virtual const sf::Drawable &get() override;

	/**
	 * \brief set text
	 * \param label string to set
	 */
	void SetText(const std::string &label);

	/**
	 * \brief set font color
	 * \param c color to set
	 */
	void SetColor(const Color &c);


protected:
    /// an sfml font
    sf::Font font;

    /// sfml text object
    sf::Text text;
};

/** \brief special kind of text with just one line */
class Label : public Text {
public:

	/**
     * \brief construct
     * \param fontname path to font file on disk
	 * \param fontheight font size
     */
    Label( const std::string &fontname, int fontheight );

    /**
     * \brief construct
     * \param fontname path to font file on disk
	 * \param fontheight font size
     * \param label text to show
     */
    Label( const std::string &fontname, int fontheight, const std::string &label );

	/**
     * \brief get current dimensions
     */
    virtual inline float GetHeight() override {
        return text.getCharacterSize();
    }
};

}// GameLib
