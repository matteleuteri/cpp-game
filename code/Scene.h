#include <windows.h>
#include <stdint.h>
#include <math.h>

#include "Player.h"


// struct game_offscreen_buffer
// {
//     // NOTE(casey): Pixels are alwasy 32-bits wide, Memory Order BB GG RR XX
//     void *Memory;
//     int Width;
//     int Height;
//     int Pitch;
// };
struct game_offscreen_buffer
{
    // NOTE(casey): Pixels are alwasy 32-bits wide, Memory Order BB GG RR XX
    BITMAPINFO Info;
    void *Memory;
    int Width;
    int Height;
    int Pitch;
};
struct win32_window_dimension
{
    int Width;
    int Height;
};


// void render(HWND hwnd, Player* player);
void updateState(Player* player, int64_t elapsed);
void renderState(game_offscreen_buffer *Buffer, Player* player);
