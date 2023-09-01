#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

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

void TextureManager::loadText(const char* text, SDL_Renderer*& renderer, int x, int y, int w, int h) {

	TTF_Font* Sans = TTF_OpenFont("res/static/OpenSans-Bold.ttf", 24);


	SDL_Color White = {255, 255, 255};


	SDL_Surface* surfaceMessage =
	    TTF_RenderText_Solid(Sans, text, White); 

	SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

	SDL_Rect Message_rect; //create a rect
	Message_rect.x = x;  //controls the rect's x coordinate 
	Message_rect.y = y; // controls the rect's y coordinte
	Message_rect.w = w; // controls the width of the rect
	Message_rect.h = h; // controls the height of the rect

	SDL_RenderCopy(renderer, Message, NULL, &Message_rect);

	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(Message);
}
