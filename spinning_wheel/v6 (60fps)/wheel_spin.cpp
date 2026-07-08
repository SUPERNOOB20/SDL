// Credits to Mike Shah:  https://youtu.be/yZl9X47cHi8
// Credits to SDL3 source code: 08-rotating-textures/rotating-textures.c

// .

// g++ ritual_animation.cpp -O3 -o anim `pkg-config --libs --cflags sdl3`

// .
// .
// .

#include <SDL3/SDL.h>
#include <string>
#include <cassert>


#include "wheel_spin.h"


static int texture_width = 0;
static int texture_height = 0;

static int pentagram_texture_width = 0;
static int pentagram_texture_height = 0;


struct SDL_Application{

    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;


    SDL_Texture* pentagramTexture;

    
    bool running = true;

    // SDL_Surface* mSurface;

    // Constructor
    SDL_Application(const char* title){
	    SDL_Init(SDL_INIT_VIDEO);
	    mWindow = SDL_CreateWindow(title, WINDOW_WIDTH, WINDOW_HEIGHT, 0);    
	    mRenderer = SDL_CreateRenderer(mWindow, nullptr);
	    if (mRenderer == nullptr){
		    assert (0 && "ERROR 0: Hardware acceleration not supported :c");
	    } else {
		    SDL_Log("Current renderer: %s", SDL_GetRendererName(mRenderer));
		    SDL_Log("Available renderer drivers:");
		    for (int i = 0; i > SDL_GetNumRenderDrivers(); i++) {
			    SDL_Log("%d, %s", i + 1, SDL_GetRenderDriver(i));
		    }
    
            //  I don't want stretched assets!!!  3:<
            SDL_SetRenderLogicalPresentation(mRenderer, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_LOGICAL_PRESENTATION_DISABLED);
	    }


	    SDL_Surface* surfacePentagram = SDL_LoadPNG("./pentagram_v1_cropped.png");

	    if (surfacePentagram == nullptr) {
		    assert(0 && "ERROR 2: Pentagram image file not found :c");
	    }

        pentagramTexture = SDL_CreateTextureFromSurface(mRenderer, surfacePentagram);

        pentagram_texture_width  = surfacePentagram -> w;
        pentagram_texture_height = surfacePentagram -> h;

        SDL_DestroySurface(surfacePentagram);
    }

	// Destructor
	~SDL_Application(){
		SDL_Quit();
	}



		
	void Input(){
		SDL_Event event;

		while (SDL_PollEvent(&event)){
			if (event.type == SDL_EVENT_QUIT) {
				running = false;
			} else if (event.type == SDL_EVENT_KEY_DOWN) {

                // SDL_Log("CONGRATULA!!! You pressed the %d key :3)7", event.button.button);       // Useful to log stuff.

                if (event.button.button == 41){          // 41 is the escape key       (you can remap it if you want :3)
                    SDL_Quit();
                }

                switch (event.button.button) {

	            	case 79:
	            		// Wheel go to the right :3
	            		acceleration += 0.05f;
	            		break;
	            		
            		case 80:
                       	// Wheel go to the left :3
            			acceleration -= 0.05f;
    			}
            }
		}
	}
    

   

	void Update(int currentTick){
	}


	void Render(int currentTick){

		SDL_SetRenderDrawColor(mRenderer, 0x00, 0x00, 0x00, 0xFF);
		SDL_RenderClear(mRenderer);


        SDL_FPoint pentagram_center;
        SDL_FRect p_dst_rect;

        // float rotation = velocity * ((float) (deltaTime)) + rotation;

        // Assume a constant deltaTime of like 1ms...
        velocity       = acceleration * ((float) 1.0f) + velocity;
        float rotation = velocity     * ((float) 1.0f) + rotation;
        



        // SDL_Log("velocity: %f", velocity);

        /* Center this one, and draw it with some rotation so it spins! */
        p_dst_rect.x = ((float) (WINDOW_WIDTH  - pentagram_texture_width))  / 2.0f;
        p_dst_rect.y = ((float) (WINDOW_HEIGHT - pentagram_texture_height)) / 2.0f;
        p_dst_rect.w = (float)   pentagram_texture_width;
        p_dst_rect.h = (float)   pentagram_texture_height;

        /* rotate it around the center of the texture; you can rotate it from a different point, too! */
        pentagram_center.x = pentagram_texture_width  / 2.0f;
        pentagram_center.y = pentagram_texture_height / 2.0f;


        // TODO: Make a black rectangle on top and animate opacity for brightness effect.
        SDL_RenderTextureRotated(mRenderer, pentagramTexture, NULL, &p_dst_rect, rotation, &pentagram_center, SDL_FLIP_NONE);




		// draw other things here ...
		


        // SDL_SetTextureScaleMode(mTexture, SDL_SCALEMODE_NEAREST);            // For pixel-art textures (no interpolation or antialiasing).
        // SDL_SetTextureScaleMode(mTexture, SDL_SCALEMODE_LINEAR);            //  For high definition textures (features interpolation and antialiasing).

		SDL_RenderPresent(mRenderer);
	}

    // Every tick is one iteration of the game loop.
	void Tick(int currentTick){
		Input();
		Update(currentTick);
		Render(currentTick);
	}

	void MainLoop(){
		Uint64 fps = 0;
		Uint64 lastTime = 0;
		while(running){
			Uint64 currentTick = SDL_GetTicks();        // In miliseconds (I think/hope e.e)
			Tick(currentTick);
			fps++;


			Uint64 deltaTime = SDL_GetTicks() - currentTick;

            // Should be quite safe to assume deltaTime >= 0...
            if (deltaTime < 16.666666){    
                SDL_Delay(16.666666 - deltaTime);       // Homemade VSync...            
            }


			if (currentTick > lastTime + 1000) {
				lastTime = currentTick;
				std::string title;
				title += "Current FPS: " + std::to_string(fps);
				SDL_SetWindowTitle(mWindow, title.c_str());
				fps = 0;
			}
		}
	}
};


// Entry Point
int main(int argc, char* argv[]){
    // SDL_Log("anim speed / 3.0f (int): %d", (int) (ANIMATION_SPEED / 3.0f));
	SDL_Application app("FPS test! Current FPS: ");
	app.MainLoop();
	return 0;
}


