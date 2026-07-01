#ifndef HEXE_ANIMATION_H
#define HEXE_ANIMATION_H



#define WINDOW_WIDTH     1280
#define WINDOW_HEIGHT     720


class Snowflake {
    public:

        float random_size            =  1 + SDL_randf() * 5;                                                  // Each snowflake is between 1px and 6px of width and height.

        float random_pos_x           =  SDL_randf() * SDL_rand(WINDOW_WIDTH);                                 // Each snowflake spawns between 0px and WINDOW_WIDTHpx horizontally.
        float random_starting_pos_x  =  random_pos_x                            - (WINDOW_WIDTH / 8);         // Eye-balled adjustment for horizontal movement...



        // C++ struct (not C-styled).
        SDL_FRect snowflake_rect{

            snowflake_rect.x = (float) random_starting_pos_x,
            snowflake_rect.y = (float) 1.0f,                                               // Spawn the snowflakes near the top of the screen.
            snowflake_rect.w = (float) {random_size},
            snowflake_rect.h = (float) {random_size}
    };
};


#endif
