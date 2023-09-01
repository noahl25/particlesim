#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "TextureManager.hpp"
#include "Debug.hpp"

SDL_Texture* TextureManager::loadTexture(const char* fileName, SDL_Renderer* renderer) {

	SDL_Surface* tmpSurface = IMG_Load(fileName);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);

	if (tex == NULL) { _ASSERT(std::string("FAILED TO LOAD TEXTURE: ") + fileName);}
	else { _ASSERT(std::string("TEXTURE LOADED: ") + fileName);}

	return tex;

}

void TextureManager::draw(SDL_Texture* texture, SDL_Renderer* renderer, SDL_Rect* src, SDL_Rect* dest, SDL_RendererFlip flip = SDL_FLIP_NONE) {

	SDL_RenderCopyEx(renderer, texture, src, dest, NULL, NULL, flip);


}