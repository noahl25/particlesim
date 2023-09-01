#pragma once

#include <vector>

class UIElement;

class UI {

public:


	UI();

	void update(int x, int y);
	void draw(SDL_Renderer*& renderer);
	inline const auto getElements() {return UIelements;}

	template <typename T, typename ...TArgs> UIElement* addUIElement(TArgs...args) {
		T* c(new T((args)...));

		UIelements.emplace_back(c);

		return c;
	}


private:

	std::vector<UIElement*> UIelements;


	 

};