#ifndef HEXE_ANIMATION_H
#define HEXE_ANIMATION_H



#define WINDOW_WIDTH     1280
#define WINDOW_HEIGHT     720


class Snowflake {
    public:

        float random_size           = SDL_randf() * 5;
        float random_starting_pos_x = SDL_randf() * SDL_rand(WINDOW_WIDTH);


        // C++ struct (not C-styled).
        SDL_FRect snowflake_rect{

            snowflake_rect.x = (float) random_starting_pos_x,
            snowflake_rect.y = (float) 30.0f,
            snowflake_rect.w = (float) {random_size},    // How to render in pixels...???
            snowflake_rect.h = (float) {random_size}     // How to render in pixels...???
    };
};


#endif
