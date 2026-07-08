#ifndef WHEEL_SPIN_HEADER_FILE
#define WHEEL_SPIN_HEADER_FILE


// Attempt #2...

// They say that:
// [1]  a = (v1 - v0) / (θ1 - θ0)
// [2]  v = (θ1 - θ0) / (t1 - t0)

// ... or something like that...


// Vamos a averiguar primero cómo calcular la rotación (θ1), dada la velocidad.
// Despejando de [2]:
//   v * (t1 - t0)         =   (θ1 - θ0)
//  (v * (t1 - t0)) + θ0   =    θ1
// 
// Es decir:
// rotation = velocity * (deltaTime) + rotation


// Ahora vamos a averiguar cómo calcular la velocidad (v1), dada la aceleración.
// Despejando de [1]:
//   a * (θ1 - θ0)            =   (v1  -  v0)
//  (a * (θ1 - θ0))  +  v0    =    v1
// 
// Es decir:
// velocity = acceleration * (deltaTime) + velocity




// Size of the asset for the 1024x768 osu!taiko video...
#define WINDOW_WIDTH   1024
#define WINDOW_HEIGHT   680


#define WHEEL_SENSITIVITY 0.3f     // the higher, the more sensible...
// #define ANIMATION_SPEED     1500         // In miliseconds.
// #define ANIMATION_SPEED     500         // In miliseconds.

// acceleration =                 4
// velocity =              4t  +  3
// rotation =      2t²  +  3t  +  7

// rotation = accel / 2 * t * t + 3*t + 7


double acceleration = 0.0f;
double velocity     = 0.0f;




#endif
