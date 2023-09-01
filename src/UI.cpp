#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "UI.hpp"
#include "UIElement.hpp"

UI::UI() {

	

}

void UI::update(int x, int y) {

	for (auto& element : UIelements) {

		element->update(x, y);


	}

}

void UI::draw(SDL_Renderer*& renderer) {


	for (auto& element : UIelements) {

		element->draw(renderer);


	}


}
 