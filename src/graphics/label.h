#pragma once
#include "text.h"
namespace GameLib {

/** @brief special kind of text with just one line */
class Label : public Text {
  public:
    /**
     * @brief construct
     * @param fontname path to font file on disk
     * @param fontheight font size
     */
    Label(const std::string &fontname, unsigned int fontheight);

    /**
     * @brief construct
     * @param fontname path to font file on disk
     * @param fontheight font size
     * @param label text to show
     */
    Label(const std::string &fontname, unsigned int fontheight,
          const std::string &label);

    /**
     * @brief get current dimensions
     */
    virtual inline Dimension GetSize() override {
        return Dimension(text.getGlobalBounds().width,
                         text.getLocalBounds().height);
    }
};

} // namespace GameLib
