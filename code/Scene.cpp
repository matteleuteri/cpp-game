#include "Scene.h"
// todo organize to iterate first over pen, then over corresponding shapes associated with the pens (players)
void renderState(game_offscreen_buffer *Buffer, Player* player)
{
    uint8_t *Row = (uint8_t *)Buffer->Memory;

    int numRows = Buffer->Height;
    int numCols = Buffer->Width;



    for(int i = 0; i < numRows; i++)
    {
        uint32_t *Pixel = (uint32_t *)Row;
        for(int j = 0; j < numCols; j++)
        {
            // if(i < 100)         *Pixel = RGB(0,255,255);
            // else if(i < 200)    *Pixel = RGB(255,0,255);
            // else if(i < 300)    *Pixel = RGB(127,0,127);
            // if(/*player->isActive && */abs(i - player->y) < 20 && abs(j - player->x) < 20)
            //     *Pixel = RGB(255,0,127);
            // else
            //     *Pixel = RGB(0,0,0);


            // int ie = labs(sin(j) + 20) * 20;

            // if(ie - i < 3)
            //     *Pixel = RGB(0,0,255);
            // else
            //     *Pixel = RGB(0,0,0);

            // if(i == 2 * j)
            //     *Pixel = RGB(0,0,255);
            // else
            //     *Pixel = RGB(100,200,76);

            //draw one cycle of fractal borde


            bool b = labs(i - 40 * (sin(j / 50) + 5)) < 2;




            if(b)
            {
                *Pixel = RGB(0,0,255);
            }
            else
            {
                *Pixel = RGB(0,0,0);
            }






            *Pixel++;
        }
        Row += (Buffer->Pitch);
    }
}

void updateState(Player* player, int64_t elapsed)
{
    // coordinates used here refer to the game state coordinates, not window coordinates
    player->x += (player->xSpeed * (elapsed/10000));
    player->y += (player->ySpeed * (elapsed/10000));

    if(player->x > 500)
    {
        player->x = 0;
    }
    else if(player->x < 0)
    {
        player->x = 500;
    }
    if(player->y > 500)
    {
        player->y = 0;
    }
    else if(player->y < 0)
    {
        player->y = 500;
    }
    // map coordinates from some game world onto the canvas, at a dimension the window can handle
}
