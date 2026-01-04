/**********************************************************************************************
*
*   raylib - Advance Game template
*
*   Title Screen Functions Definitions (Init, Update, Draw, Unload)
*
*   Copyright (c) 2014-2022 Ramon Santamaria (@raysan5)
*
*   This software is provided "as-is", without any express or implied warranty. In no event
*   will the authors be held liable for any damages arising from the use of this software.
*
*   Permission is granted to anyone to use this software for any purpose, including commercial
*   applications, and to alter it and redistribute it freely, subject to the following restrictions:
*
*     1. The origin of this software must not be misrepresented; you must not claim that you
*     wrote the original software. If you use this software in a product, an acknowledgment
*     in the product documentation would be appreciated but is not required.
*
*     2. Altered source versions must be plainly marked as such, and must not be misrepresented
*     as being the original software.
*
*     3. This notice may not be removed or altered from any source distribution.
*
**********************************************************************************************/

#include "raylib.h"
#include "screens.h"
#include "raymath.h" 

//----------------------------------------------------------------------------------
// Module Variables Definition (local)
//----------------------------------------------------------------------------------
#define STAR_COUNT 420

static int framesCounter = 0;
static int finishScreen = 0;
static float star_speed;
Vector3 stars[STAR_COUNT] = { 0 };
Vector2 starsScreenPos[STAR_COUNT] = { 0 };
Color bgColor;

//----------------------------------------------------------------------------------
// Title Screen Functions Definition
//----------------------------------------------------------------------------------

// Title Screen Initialization logic
void InitTitleScreen(void)
{
    // TODO: Initialize TITLE screen variables here!
    framesCounter = 0;
    finishScreen = 0;
    star_speed = 1.0/10.0f;
    bgColor = ColorLerp(DARKBLUE, BLACK, 0.69f);

    // Setup the stars with a random position
    for (int i = 0; i < STAR_COUNT; i++)
    {
        stars[i].x = GetRandomValue(-GetScreenWidth()*0.5f, GetScreenWidth()*0.5f);
        stars[i].y = GetRandomValue(-GetScreenHeight()*0.5f, GetScreenHeight()*0.5f);
        stars[i].z = 1.0f;
    }
}

// Title Screen Update logic
void UpdateTitleScreen(void)
{
    // TODO: Update TITLE screen variables here!

    // Press enter or tap to change to GAMEPLAY screen
    if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
    {
        //finishScreen = 1;   // OPTIONS
        finishScreen = 2;   // GAMEPLAY
        PlaySound(fxMouseClick);
    }


    float dt = GetFrameTime();
    for (int i = 0; i < STAR_COUNT; i++)
        {
            // Update star's timer
            stars[i].z -= dt*star_speed;

            // Calculate the screen position
            starsScreenPos[i] = (Vector2){
                GetScreenWidth()*0.5f + stars[i].x/stars[i].z,
                GetScreenHeight()*0.5f + stars[i].y/stars[i].z,
            };

            // If the star is too old, or offscreen, it dies and we make a new random one
            if ((stars[i].z < 0.0f) || (starsScreenPos[i].x < 0) || (starsScreenPos[i].y < 0.0f) ||
                (starsScreenPos[i].x > GetScreenWidth()) || (starsScreenPos[i].y > GetScreenHeight()))
            {
                stars[i].x = GetRandomValue(-GetScreenWidth()*0.5f, GetScreenWidth()*0.5f);
                stars[i].y = GetRandomValue(-GetScreenHeight()*0.5f, GetScreenHeight()*0.5f);
                stars[i].z = 1.0f;
            }
        }
}

// Title Screen Draw logic
void DrawTitleScreen(void)
{
    // // TODO: Draw TITLE screen here!
    // DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), GREEN);
    // Vector2 pos = { 20, 10 };
    // DrawTextEx(font, "TITLE SCREEN", pos, font.baseSize*3.0f, 4, DARKGREEN);
    // DrawText("PRESS ENTER or TAP to JUMP to GAMEPLAY SCREEN", 120, 220, 20, DARKGREEN);
    
    ClearBackground(bgColor);
    for (int i = 0; i < STAR_COUNT; i++)
    {
            // Get the time a little while ago for this star, but clamp it
        float t = Clamp(stars[i].z + 1.0f/32.0f, 0.0f, 1.0f);

        // If it's different enough from the current time, we proceed
        if ((t - stars[i].z) > 1e-3)
        {
            // Calculate the screen position of the old point
            Vector2 startPos = (Vector2){
                GetScreenWidth()*0.5f + stars[i].x/t,
                GetScreenHeight()*0.5f + stars[i].y/t,
            };
            // Draw a line connecting the old point to the current point
            DrawLineV(startPos, starsScreenPos[i], RAYWHITE);
        }
    }
}

// Title Screen Unload logic
void UnloadTitleScreen(void)
{
    // TODO: Unload TITLE screen variables here!
}

// Title Screen should finish?
int FinishTitleScreen(void)
{
    return finishScreen;
}