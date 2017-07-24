#include <iostream>

#include "renderable.h"
#include "window.h"
#include "primitives.h"
#include "sprite.h"

namespace GameLib {

int Renderable::shadow_z = 0;
static std::map<std::string, TextureTracker> texture_list;

// ------------------------------------------------------------
// constructor
// ------------------------------------------------------------
Renderable::Renderable() :
	z_order (0),
	shadow (nullptr),
	texture_filename ("[non-textured-renderable]") {
	texture = nullptr;
}

// ------------------------------------------------------------
// Constructor
// ------------------------------------------------------------
Renderable::Renderable (const std::string &filename) :
	z_order (0),
	shadow (nullptr),
	texture (nullptr),
	texture_filename (filename) {

	auto it = texture_list.find (filename);
	if (it != texture_list.end()) {

		texture = (*it).second.tex;
		(*it).second.ref_counter++;

	} else {

		texture = new  sf::Texture();
		if (!texture->loadFromFile (filename)) {
			std::cout << "Could not load image file: " << filename << std::endl;
		} else {
			texture_list.insert (std::make_pair (filename, TextureTracker (texture)));
		}
	}

	// set renderable texture for future use
	sprite.setTexture (*texture);

	geometry.w = texture->getSize().x;
	geometry.h = texture->getSize().y;
}

// ------------------------------------------------------------
// Constructor
// ------------------------------------------------------------
Renderable::Renderable (const GameLib::Renderable &other) :
	z_order (0),
	shadow (nullptr),
	texture (nullptr),
	texture_filename (other.texture_filename) {
}

// ------------------------------------------------------------
// Destructor
// ------------------------------------------------------------
Renderable::~Renderable() {

	// search for this texture in the list
	auto it = texture_list.find (texture_filename);
	if (it != texture_list.end()) {

		// decrement reference counter
		(*it).second.ref_counter -= 1;

		// if reference counter had become zero, delete the texture and remove from list
		if ( (*it).second.ref_counter == 0) {

			// free memory
			delete (*it).second.tex;

			// remove pointer from list
			texture_list.erase (it);
		}
	}
}

// ------------------------------------------------------------
// Render
// ------------------------------------------------------------
void Renderable::Render (GameLib::Window &window) {

	if (visible) {
		// shadow gets drawn first
		if (shadow) {
			shadow->Render (window);
		}

		window.Draw (*this);

#ifdef RENDER_DEBUG
		// outline
		Primitives::Rectangle (window, this->GetPosition().x, this->GetPosition().y, this->GetWidth(), this->GetHeight());
#endif
	}
}

// ------------------------------------------------------------
// count_renderables
// ------------------------------------------------------------
unsigned int Renderable::count_renderables() {
	unsigned int total = 0;
	for (auto it = texture_list.begin(); it != texture_list.end(); ++it) {
		total += (*it).second.ref_counter;
	}
	return total;
}

}//GameLib
