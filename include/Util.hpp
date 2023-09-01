#include <vector>


namespace Util {

	void drawCircle(SDL_Renderer*& renderer, int32_t centreX, int32_t centreY, int32_t radius)
	{
	   const int32_t diameter = (radius * 2);

	   int32_t x = (radius - 1);
	   int32_t y = 0;
	   int32_t tx = 1;
	   int32_t ty = 1;
	   int32_t error = (tx - diameter);

	   while (x >= y)
	   {
	      //  Each of the following renders an octant of the circle
	      SDL_RenderDrawPoint(renderer, centreX + x, centreY - y);
	      SDL_RenderDrawPoint(renderer, centreX + x, centreY + y);
	      SDL_RenderDrawPoint(renderer, centreX - x, centreY - y);
	      SDL_RenderDrawPoint(renderer, centreX - x, centreY + y);
	      SDL_RenderDrawPoint(renderer, centreX + y, centreY - x);
	      SDL_RenderDrawPoint(renderer, centreX + y, centreY + x);
	      SDL_RenderDrawPoint(renderer, centreX - y, centreY - x);
	      SDL_RenderDrawPoint(renderer, centreX - y, centreY + x);

	      if (error <= 0)
	      {
	         ++y;
	         error += ty;
	         ty += 2;
	      }

	      if (error > 0)
	      {
	         --x;
	         tx += 2;
	         error += (tx - diameter);
	      }
	   }
	}

	std::vector<Vec2D*> getPointsWithinCircle(uint32_t centerX, uint32_t centerY, uint32_t r) {

		std::vector<Vec2D*> temp;

		for (uint32_t x = centerX - r; x <= centerX; x++) {
			for (uint32_t y = centerY - r; y <= centerY; y++) {

				if ((x - centerX)*(x - centerX) + (y - centerY)*(y - centerY) <= r*r && x >= 0 && y >= 0 && x <= SCREEN_WIDTH && y <= SCREEN_HEIGHT) {	
	            	
	            	int xSym = centerX - (x - centerX);
            		int ySym = centerY - (y - centerY);
					temp.push_back(new Vec2D{x, y});
					temp.push_back(new Vec2D{x, ySym});
					temp.push_back(new Vec2D{xSym, y});
					temp.push_back(new Vec2D{xSym, ySym});

 


				}


			}


		}

		return temp;




	}

	/*
	from: https://stackoverflow.com/questions/15856411/finding-all-the-points-within-a-circle-in-2d-space

	for (x = xCenter - radius ; x <= xCenter; x++)
{
    for (y = yCenter - radius ; y <= yCenter; y++)
    {
        // we don't have to take the square root, it's slow
        if ((x - xCenter)*(x - xCenter) + (y - yCenter)*(y - yCenter) <= r*r) 
        {
            xSym = xCenter - (x - xCenter);
            ySym = yCenter - (y - yCenter);
            // (x, y), (x, ySym), (xSym , y), (xSym, ySym) are in the circle
        }
    }
}

	*/


};