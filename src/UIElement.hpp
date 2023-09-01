#pragma once

#include "TextureManager.hpp"

struct UIElement {

	UIElement(const char* name, SDL_Rect* loc, SDL_Texture* texture) : name(name), destRect(std::move(*loc)), texture(texture) {alive = true;}

	const char* name;

	SDL_Texture* texture;
	SDL_Rect srcRect;
	SDL_Rect destRect;
	bool hovering;

	bool alive;

	virtual void update(int xMousPos, int yMousPos);
	virtual void draw(SDL_Renderer*& renderer);

protected:

	bool isHovering(int xMousPos, int yMousPos) {

		if (

			xMousPos >= destRect.x && xMousPos <= destRect.x + destRect.w &&
			yMousPos >= destRect.y && yMousPos <= destRect.y + destRect.h

			) {return true;}

		return false;

	}



};



struct UIElementCursorSize : public UIElement {

	SDL_RendererFlip flip;
	UIElementCursorSize(const char* name, SDL_Rect* loc, SDL_Texture* texture, SDL_RendererFlip flip) : UIElement(name, loc, texture) {
		srcRect.y = 0;
		srcRect.w = 32;
		srcRect.h = 32;
		hovering = false;
		this->flip = flip;
	}

	virtual void update(int xMousPos, int yMousPos) override {

		if (isHovering(xMousPos, yMousPos)) {

			srcRect.x = 32;
			hovering = true;

		}

		else {srcRect.x = 0; hovering = false;}


	}

	virtual void draw(SDL_Renderer*& renderer) override {

		TextureManager::draw(texture, renderer, &srcRect, &destRect, flip);

	}



};