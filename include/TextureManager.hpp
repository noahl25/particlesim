#pragma once


class TextureManager {

public:
	static SDL_Texture* loadTexture(const char* fileName, SDL_Renderer* renderer);
	static void draw(SDL_Texture* texture, SDL_Renderer* renderer, SDL_Rect* src, SDL_Rect* dest, SDL_RendererFlip flip);

};
