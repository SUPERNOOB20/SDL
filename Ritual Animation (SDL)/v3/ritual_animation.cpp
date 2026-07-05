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

// Size of the asset for the 1024x768 osu!taiko video...
#define WINDOW_WIDTH   1024
#define WINDOW_HEIGHT   680

// #define CANDLE_ANIMATION_SPEED     1500         // In miliseconds.
#define CANDLE_ANIMATION_SPEED     350         // In miliseconds.
#define PENTAGRAM_ANIMATION_SPEED  6000

// Eyeballed candle positions... e.e
#define ANCHOR1X 120
#define ANCHOR1Y 20
#define ANCHOR2X 815
#define ANCHOR2Y 450

static int texture_width = 0;
static int texture_height = 0;

static int pentagram_texture_width = 0;
static int pentagram_texture_height = 0;


struct SDL_Application{

    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;

    SDL_Texture* candleTexture1;
    SDL_Texture* candleTexture2;
    SDL_Texture* candleTexture3;

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

	    SDL_Surface* surfaceCandle1 = SDL_LoadPNG("./candle_f1.png");
	    SDL_Surface* surfaceCandle2 = SDL_LoadPNG("./candle_f2.png");
	    SDL_Surface* surfaceCandle3 = SDL_LoadPNG("./candle_f3.png");

	    SDL_Surface* surfacePentagram = SDL_LoadPNG("./pentagram_v1_cropped.png");

	    if ((surfaceCandle1 == nullptr) || (surfaceCandle2 == nullptr) || (surfaceCandle3 == nullptr)) {
		    assert(0 && "ERROR 1: Candle images files not found :c");
	    }

	    if (surfacePentagram == nullptr) {
		    assert(0 && "ERROR 2: Pentagram image file not found :c");
	    }

	    candleTexture1 = SDL_CreateTextureFromSurface(mRenderer, surfaceCandle1);
	    candleTexture2 = SDL_CreateTextureFromSurface(mRenderer, surfaceCandle2);
	    candleTexture3 = SDL_CreateTextureFromSurface(mRenderer, surfaceCandle3);

        pentagramTexture = SDL_CreateTextureFromSurface(mRenderer, surfacePentagram);

        //  All candles have the same resolution so I don't really care about assigning the same w and h to all of them.
        texture_width  = surfaceCandle1 -> w;
        texture_height = surfaceCandle1 -> h;

        pentagram_texture_width  = surfacePentagram -> w;
        pentagram_texture_height = surfacePentagram -> h;


        SDL_DestroySurface(surfaceCandle1);
        SDL_DestroySurface(surfaceCandle2);
        SDL_DestroySurface(surfaceCandle3);

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

                // SDL_Log("CONGRATULA!!! You pressed the %d key :3)7", event.button.button);

                if (event.button.button == 41){          // 41 is the escape key       (you can remap it if you want :3)
                    SDL_Quit();
                }
            }
		}
	}
    

   
	void Update(int currentTick){
	}


	void Render(int currentTick){

		SDL_SetRenderDrawColor(mRenderer, 0x00, 0x00, 0x00, 0xFF);
		SDL_RenderClear(mRenderer);


        SDL_FRect dst_rect_candle1;

        dst_rect_candle1.x = ANCHOR1X;
        dst_rect_candle1.y = ANCHOR1Y;
        dst_rect_candle1.w = (float) texture_width;
        dst_rect_candle1.h = (float) texture_height;



        SDL_FRect dst_rect_candle2;

        dst_rect_candle2.x = ANCHOR2X;
        dst_rect_candle2.y = ANCHOR1Y;
        dst_rect_candle2.w = (float) texture_width;
        dst_rect_candle2.h = (float) texture_height;



        SDL_FRect dst_rect_candle3;

        dst_rect_candle3.x = ANCHOR1X;
        dst_rect_candle3.y = ANCHOR2Y;
        dst_rect_candle3.w = (float) texture_width;
        dst_rect_candle3.h = (float) texture_height;



        SDL_FRect dst_rect_candle4;

        dst_rect_candle4.x = ANCHOR2X;
        dst_rect_candle4.y = ANCHOR2Y;
        dst_rect_candle4.w = (float) texture_width;
        dst_rect_candle4.h = (float) texture_height;


        // Array of textures for all candle frames.
        SDL_Texture* candle_textures[] = {candleTexture1, candleTexture2, candleTexture3};
        int number_of_candle_textures = 3;      // Array size.    
        
        
        // Array of dst_rect pointers for all candles.
        SDL_FRect* candles[] = {&dst_rect_candle1, &dst_rect_candle2, &dst_rect_candle3, &dst_rect_candle4};
        int number_of_candles = 4;              // Array size.    



        int current_anim_frame = -1;

        if ((currentTick % ((int) (CANDLE_ANIMATION_SPEED))) < ((int) (CANDLE_ANIMATION_SPEED / 3.0f))) {

            current_anim_frame = 0;

        } else if ((currentTick % ((int) (CANDLE_ANIMATION_SPEED))) < ((int) (CANDLE_ANIMATION_SPEED * 2.0f / 3.0f))) {
	    	current_anim_frame = 1;

        } else {           // if ((currentTick % ((int) (CANDLE_ANIMATION_SPEED))) < ((int) (CANDLE_ANIMATION_SPEED * 3.0f / 3.0f)))
            current_anim_frame = 2;
        }

       for (int i = 0; i < number_of_candles; i++){
    		SDL_RenderTexture(mRenderer, candle_textures[current_anim_frame], nullptr, candles[i]); 
            // SDL_RenderTexture(mRenderer, candleTexture1, nullptr, candles[i]); 
        }




        SDL_FPoint pentagram_center;
        SDL_FRect p_dst_rect;

        /* we'll have a texture rotate around over 15 seconds (15,000 milliseconds). 360 degrees in a circle! */
        const float rotation = (((float) ((int) (currentTick % PENTAGRAM_ANIMATION_SPEED))) / ((float) PENTAGRAM_ANIMATION_SPEED)) * 360.0f;


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





        SDL_FRect pentagram_shade_dst_rect;

        pentagram_shade_dst_rect.x = (float) WINDOW_WIDTH / 5.10f;
        pentagram_shade_dst_rect.y = (float) 0;
        pentagram_shade_dst_rect.w = (float) WINDOW_WIDTH / 1.65f;
        pentagram_shade_dst_rect.h = (float) WINDOW_HEIGHT;


        SDL_SetRenderDrawBlendMode(mRenderer, SDL_BLENDMODE_MUL);
		// SDL_RenderPresent(mRenderer);

        // short int pentagram_opacity = 255 - (currentTick % 255);
        int pentagram_opacity = 255.0f - ((((SDL_sin(((float) (currentTick)) / 500.0f)) * 255.0f) / 2) + 127.5f);
        
        // SDL_Log("huh   %f", 255.0f - ((((SDL_sin(((float) (currentTick)) / 500.0f)) * 255.0f) / 2) + 127.5f));

		SDL_SetRenderDrawColor(mRenderer, 0x00, 0x00, 0x00, pentagram_opacity);
		SDL_RenderFillRect(mRenderer, &pentagram_shade_dst_rect);

		// draw other things here ...
		


        // SDL_SetTextureScaleMode(mTexture, SDL_SCALEMODE_NEAREST);              // For pixel-art textures (no interpolation or antialiasing).
        // SDL_SetTextureScaleMode(candleTexture1, SDL_SCALEMODE_LINEAR);            // For high definition textures (features interpolation and antialiasing).
        // SDL_SetTextureScaleMode(candleTexture2, SDL_SCALEMODE_LINEAR);            // For high definition textures (features interpolation and antialiasing).
        // SDL_SetTextureScaleMode(candleTexture3, SDL_SCALEMODE_LINEAR);            // For high definition textures (features interpolation and antialiasing).



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


