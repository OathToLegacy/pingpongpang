#include <stdio.h>
#include <SDL.h>
#include <Windows.h> //Used for text displaying in SDL window

#include "gameObjects.h"

//DEFINE RESOLUTION
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
//Methods to draw the game objects
void drawBall(struct Ball ball, SDL_Renderer* renderer){
	SDL_Rect ballRect = {ball.x, ball.y, ball.radius *2, ball.radius * 2};
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(renderer, &ballRect);
}

void drawPaddle(struct Paddle paddle, SDL_Renderer* renderer){
	SDL_Rect paddleRect = {paddle.x, paddle.y, paddle.width, paddle.height};
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(renderer, &paddleRect);
}

//Draw text on the screen using windows GDI
void drawText(char* text, int x, int y, SDL_Renderer* renderer){
	HDC hdc = GetDC(NULL);
	TextOut(hdc, x, y, text, strlen(text));
	ReleaseDC(NULL, hdc);
}

//game loop
void gameLoop(SDL_Renderer* renderer) {
    //Print main menu text
    drawText("Welcome to Pong (With a twist!)\n press 'r' to begin the game", 100, 100, renderer);
    
}

//process input
void processInput(struct Paddle* paddleLeft, struct Paddle* paddleRight, struct Ball* ball, SDL_Renderer* renderer) {
    
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            
            exit(0);
        }
        else if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
            case SDLK_w:
                // Move the left paddle up
                paddleLeft->y -= 10;
                break;
            case SDLK_s:
                // Move the left paddle down
                paddleLeft->y += 10;
                break;
            case SDLK_UP:
                // Move the right paddle up
                paddleRight->y -= 10;
                break;
            case SDLK_DOWN:
                // Move the right paddle down
                paddleRight->y += 10;
                break;
            case SDLK_r:
                // Reset the the game
                drawBall(*ball, renderer);
                drawPaddle(*paddleLeft, renderer);
                drawPaddle(*paddleRight, renderer);
                // Add more case statements for other keys as needed
            }
        }
    }
    
}


int main(void){
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return -1; // Failure
        exit(-1);
    }

    // Create game window using SDL
    SDL_Window* window = SDL_CreateWindow("Ping Pong Pang", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return -2; // Failure
        exit(-1);
    }

    // TODO: create a renderer here, which you'll use later to draw your game objects.
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) {
        SDL_DestroyWindow(window);
        printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_Quit();
        return -3; // Failure
        exit(-1);
    }

    //Draw color for filling the window:
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    //Fill the window with the color:
    SDL_RenderClear(renderer);

    //Present renderer:
    SDL_RenderPresent(renderer);

    // Wait for 3 seconds to show the window
    SDL_Delay(3000);

    // Create game objects from structs in gameOjects.h
    struct Ball ball = {SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 15, 0, 0,};
    struct Paddle paddleLeft = {20, SCREEN_HEIGHT/2, 20, 100, 0};
    struct Paddle paddleRight = {SCREEN_WIDTH-40, SCREEN_HEIGHT/2, 20, 100, 0};
    //Draw the game objects
    drawBall(ball, renderer);
    drawPaddle(paddleLeft, renderer);
    drawPaddle(paddleRight, renderer);
    //Present renderer:
    SDL_RenderPresent(renderer);

    
    gameLoop(renderer);
    while (1){}
    return 1;
}