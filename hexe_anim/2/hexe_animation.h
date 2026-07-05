#ifndef HEXE_ANIMATION_H
#define HEXE_ANIMATION_H



#define WINDOW_WIDTH     1280
#define WINDOW_HEIGHT     720


class Snowflake {
    private:

        float random_size            =  1 + SDL_randf() * 5;                                                  // Each snowflake is between 1px and 6px of width and height.

        float random_pos_x           =  SDL_randf() * SDL_rand(WINDOW_WIDTH) * 2.0f;                                 // Each snowflake spawns between 0px and WINDOW_WIDTHpx horizontally.
        float random_starting_pos_x  =  random_pos_x                                 - (WINDOW_WIDTH / 2);           // Eye-balled adjustment for horizontal movement...
        // ^  Essentially these two lines make it so that the snowfall is twice as wide as your window width, and also centered on your window.



        // C++ struct (not C-styled).
        SDL_FRect snowflake_rect{

            snowflake_rect.x = {},
            snowflake_rect.y = {},                                               // Spawn the snowflakes near the top of the screen.
            snowflake_rect.w = {},
            snowflake_rect.h = {}
        };



    public:
        Snowflake(float altitude = 1.0f): // constructors must be non-const
        snowflake_rect {random_starting_pos_x, altitude, random_size, random_size}        


        // okay to modify members in non-const constructor
               
        // snowflake_rect.x { random_starting_pos_x },
        // snowflake_rect.y { altitude },                                               // Spawn the snowflakes near the top of the screen.
        // snowflake_rect.w { random_size },
        // snowflake_rect.h { random_size }


        {
        }

         // Setters
        void set_x_pos(float horizontal_pos) {
            snowflake_rect.x = horizontal_pos;
        }

        void set_y_pos(float vertical_pos) {
            snowflake_rect.y = vertical_pos;
        }


        // Getters
        float get_x_pos() const {
            return snowflake_rect.x;
        }

        float get_y_pos() const {
            return snowflake_rect.y;
        }

        SDL_FRect* const get_rect_addr(){
            return &snowflake_rect;
        }
};


#endif
