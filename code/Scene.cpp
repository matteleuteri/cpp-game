#include "Scene.h"
// todo organize to iterate first over pen, then over corresponding shapes associated with the pens (players)
void render(game_offscreen_buffer *Buffer, Player* player)
{

    uint8_t *Row = (uint8_t *)Buffer->Memory;    
    for(int Y = 0; Y < Buffer->Height; ++Y)
    {
        uint32_t *Pixel = (uint32_t *)Row;
        for(int X = 0; X < Buffer->Width; ++X)
        {
            // uint8_t Blue = X;
            // uint8_t Green = Y;
            // uint8_t Red = ()
            // *Pixel = RGB(255,0,0); // blue
            // *Pixel = RGB(0,255,0); // green
            // *Pixel = RGB(0,0,255); // red
            // *Pixel = RGB(255,100,255); pink
            
            // red line on Y = 200
                
            if(player->isActive && abs(Y - player->y) < 20 && abs(X - player->x) < 20)
                *Pixel = RGB(0,0,255);
            else
                *Pixel = RGB(0,0,0);

            *Pixel++;

            // if(X < 100)
            //     *Pixel = Blue;
            // else if(X < 200)
            //     *Pixel = Green;
            // else 
            //     *Pixel = Blue;


        }
        
        Row += (Buffer->Pitch);
    }
}





void updatePlayer(Player* player, int64_t elapsed)
{
    // elapsed /= 1000;
    // (player->x) = (player->x) + ((elapsed * player->xSpeed));
    // (player->y) = (player->y) + ((elapsed * player->ySpeed)); 

    // (player->x) = (player->x + 1) % 700;
    // (player->y) = (player->y + 1) % 500;

    player->x += (elapsed/10000 * player->xSpeed);
    player->y += (elapsed/10000 * player->ySpeed);


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


}