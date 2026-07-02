// Credits to:
        // Mike Shah     -  https://youtu.be/yZl9X47cHi8
        // SDL examples  -  https://examples.libsdl.org/SDL3/renderer/08-rotating-textures/

// g++ demo.cpp -O3 -o rgb_demo `pkg-config --libs --cflags sdl3`

// .
// .
// .

// TODO: Handle folders/subdirectories (this might prove useful: https://wiki.libsdl.org/SDL3/CategoryFilesystem)

// .
// .
// .


#include <SDL3/SDL.h>
#include <string>
#include <cassert>
#include <queue>

#include "hexe_animation.h"


#define WITCH_ROTATION         20.0f
#define WITCH_FLOATING_SPEED   20           // The higher, the slower...

#define SNOW_AMOUNT            2           // The higher, the less snow...



// static int texture_width = 1280;
// static int texture_height = 720;

static int texture_width = 0;
static int texture_height = 0;


// Keeps track of all the existent snowflakes (that have not yet dispawned).
static std::queue<Snowflake> snowflakes = {};

struct SDL_Application{

    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;

    SDL_Texture* bg_texture;
    SDL_Texture* witch_texture_f1;      // Frame #1.
    SDL_Texture* witch_texture_f2;      // Frame #2.

    bool running = true;

    // Constructor
    SDL_Application(const char* title){
	    SDL_Init(SDL_INIT_VIDEO);
	    mWindow = SDL_CreateWindow(title, 1280, 720, SDL_WINDOW_RESIZABLE);    
	    mRenderer = SDL_CreateRenderer(mWindow, nullptr);
	    if (mRenderer == nullptr){
		    assert (0 && "ERROR: Hardware acceleration not supported :c");
	    } else {
		    SDL_Log("Current renderer: %s", SDL_GetRendererName(mRenderer));
		    SDL_Log("Available renderer drivers:");
		    for (int i = 0; i > SDL_GetNumRenderDrivers(); i++) {
			    SDL_Log("%d, %s", i + 1, SDL_GetRenderDriver(i));
		    }
	    }

        // SDL_SetRenderLogicalPresentation(mRenderer, 16, 9, SDL_LOGICAL_PRESENTATION_LETTERBOX);
        SDL_SetRenderLogicalPresentation(mRenderer, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_LOGICAL_PRESENTATION_LETTERBOX);

	    // SDL_Surface* surface = SDL_LoadPNG("./Assets/f1.png");       // TODO.
        SDL_Surface* surface    = SDL_LoadPNG("./f1.png");
        SDL_Surface* bg_surface = SDL_LoadPNG("./back.png");

	    if ((surface == nullptr) || (bg_surface == nullptr)){
		    assert(0 && "ERROR: File not found :c");        // Error handling.
	    }
        
	    witch_texture_f1 = SDL_CreateTextureFromSurface(mRenderer, surface);

        texture_width  = surface -> w;
        texture_height = surface -> h;

        SDL_DestroySurface(surface);



        bg_texture = SDL_CreateTextureFromSurface(mRenderer, bg_surface);
        
        // bg_texture_width  = bg_surface -> w;
        // bg_texture_height = bg_surface -> h;

        SDL_DestroySurface(bg_surface);
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

                // SDL_Log("CONGRATULA!!! You pressed the %d key :3)7", event.button.button);

                if (event.button.button == 41){     // 41 is the escape button (you can remap it if you want :3)
                    SDL_Quit();
                } else if (event.button.button == 80){

                    SDL_Log("Amount of snowflakes (currently active) #2: %ld", snowflakes.size());

                    /*
                    SDL_Log("\n");
                    SDL_Log("Snowflakes queue: ");
                    std::queue<Snowflake> printable_queue(snowflakes);

                    while (printable_queue.empty() == false){
                        Snowflake current_snowflake = snowflakes.front();
                        SDL_Log("    current snowflake: (%f, %f)", current_snowflake.snowflake_rect.x, current_snowflake.snowflake_rect.y);
                        snowflakes.pop();
                    }
                    SDL_Log("\n");
                    */
                }
            }
		}
	}

   
	void Update(int currentFrame){


        // Adds a new snowflake every SNOW_AMOUNT frames! :3
        if ((currentFrame % SNOW_AMOUNT) == 0){
            // SDL_Log("Amount of snowflakes (currently active) #1: %ld", snowflakes.size());
            Snowflake mySnowflake;
            snowflakes.push(mySnowflake);
        }
        
        // SDL_Log("Amount of snowflakes (currently active) #1: %ld", snowflakes.size());

        // Snowflakes rendering queue.
        std::queue<Snowflake> snowflakes_update_queue(snowflakes);

        // Empty the snowflakes queue.
        while (snowflakes.empty() == false){
            snowflakes.pop();
        }

        // Lots of snowflakes!!! 0 - 99999... snowflakes :3
        unsigned long long int current_amount_of_snowflakes = snowflakes_update_queue.size();

        for (int i = 0; i < current_amount_of_snowflakes; i++) {

            Snowflake currentSnowflake = snowflakes_update_queue.front();

            currentSnowflake.snowflake_rect.x += 0.4f;
            currentSnowflake.snowflake_rect.y += 1.0f;

            // Fill up the snowflakes queue again.
            snowflakes.push(currentSnowflake);

            snowflakes_update_queue.pop();
            // x
        }
        // SDL_Log("Amount of snowflakes (currently active) #1: %ld", snowflakes.size());
	}


    // SDL_Init
    // (only runs on frame #0).
    void my_init() {
    }


    void render_snowflakes(int currentFrame){

        // Snowflakes rendering queue.
        std::queue<Snowflake> snowflakes_rendering_queue(snowflakes);

        for (int i = 0; i < snowflakes_rendering_queue.size(); i++){

            Snowflake currentSnowflake = snowflakes_rendering_queue.front();
            SDL_RenderFillRect(mRenderer, &currentSnowflake.snowflake_rect);

            snowflakes_rendering_queue.pop();
        }
    }

    void render_witch(int currentFrame){

        // Vertical offset (gives the impression that the witch is flying).
        double floating_offset = SDL_sin( ((double) currentFrame) / ((double) WITCH_FLOATING_SPEED) );

        float  x_offset = 380.0f;
        double y_offset = 20.0f + floating_offset;

        SDL_FRect dst_rect;

        dst_rect.x = ((float) (WINDOW_WIDTH - texture_width)) / 2.0f + x_offset;
        dst_rect.y = ((double) (WINDOW_HEIGHT - texture_height)) / 2.0f - (y_offset * 5);
        dst_rect.w = (float) texture_width;
        dst_rect.h = (float) texture_height;

        SDL_FPoint center;
        center.x = texture_width / 2.0f;
        center.y = texture_height / 2.0f;

        // assert(0 && (SDL_RenderTextureRotated(mRenderer, witch_texture_f1, NULL, &dst_rect, WITCH_ROTATION, &center, SDL_FLIP_NONE)));
        // SDL_RenderTextureRotated(mRenderer, witch_texture_f1, NULL, &dst_rect, WITCH_ROTATION, &center, SDL_FLIP_NONE);
        // SDL_RenderTextureRotated(mRenderer, witch_texture_f1, nullptr, nullptr, WITCH_ROTATION, nullptr, SDL_FLIP_NONE);
        SDL_RenderTextureRotated(mRenderer, witch_texture_f1, nullptr, &dst_rect, WITCH_ROTATION, &center, SDL_FLIP_NONE);

        // SDL_RenderTexture(mRenderer, witch_texture_f1, nullptr, nullptr);

    }

	void Render(int currentFrame){

		SDL_SetRenderDrawColor(mRenderer, 0x00, 0x00, 0x00, 0xFF);      // Black letterbox.
		SDL_RenderClear(mRenderer);

        SDL_RenderTexture(mRenderer, bg_texture, nullptr, nullptr);

        render_witch(currentFrame);

		SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0xFF, 0xFF);      // Snowflakes are white... for now :3
        render_snowflakes(currentFrame);
        
        if (currentFrame == 0){
            my_init();
        }
        
		// draw other things here ...

		SDL_RenderPresent(mRenderer);
	}

    // Every tick is one iteration of the game loop.
	void Tick(int currentFrame){
		Input();
		Update(currentFrame);
		Render(currentFrame);
	}

	void MainLoop(){
		Uint64 fps = 0;
		Uint64 lastTime = 0;
        Uint64 currentFrame = 0;
        
        // Main loop.
		while(running){
			Uint64 currentTick = SDL_GetTicks();
			Tick(currentFrame);
            currentFrame++;
			fps++;

			Uint64 deltaTime = SDL_GetTicks() - currentTick;
            
            SDL_Delay(16.666666 - deltaTime);       // Homemade VSync...            

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
	SDL_Application app("FPS test! Current FPS: ");
	app.MainLoop();
	return 0;
}

