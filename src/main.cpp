#include <iostream>
#include "SDL2/SDL.h"
#include "../hdrs/Game.h"

// our Game object
Game* g_game = 0;

SDL_Window* g_pWindow = 0;
SDL_Renderer* g_pRenderer = 0;

static const char* version = "v0.0.1";

bool Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
    int flags = 0;

    if(fullscreen)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    // attempt to initalize SDL
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        std::cout << "SDL init success\n";
        // init the window
        m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

        if(m_pWindow != 0) // window init success
        {
            std::cout << "window creation success\n";
            m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);

            if(m_pRenderer != 0) // renderer init success
            {
                std::cout << "renderer creation success\n";
                SDL_SetRenderDrawColor(m_pRenderer,0,0,0,255);
            }
            else
            {
                std::cout << "renderer init fail\n";
                return false; // renderer init fail
            }
        }
        else
        {
            std::cout << "window init fail\n";
            return false; // window init fail
        }
    }
    else
    {
        std::cout << "SDL init fail\n";
        return false; // SDL init fail
    }

    SDL_Surface* pTempSurface = SDL_LoadBMP("assets/rider.bmp");

    m_pTexture = SDL_CreateTextureFromSurface(m_pRenderer, pTempSurface);

    SDL_FreeSurface(pTempSurface);

    SDL_QueryTexture(m_pTexture, NULL, NULL, &m_sourceRectangle.w, &m_sourceRectangle.h);

    m_destinationRectangle.x = m_sourceRectangle.x = 0;
    m_destinationRectangle.y = m_sourceRectangle.y = 0;
    m_destinationRectangle.w = m_sourceRectangle.w;
    m_destinationRectangle.h = m_sourceRectangle.h;

    std::cout << "init success\n";
    m_bRunning = true; // everything init'd successfully, start the main loop;

    return true;
}

void Game::render()
{
    SDL_RenderClear(m_pRenderer); // clear the renderer to the draw color

    SDL_RenderCopy(m_pRenderer, m_pTexture, 0, 0);

    SDL_RenderPresent(m_pRenderer); // draw to the screen
}

void Game::handleEvents()
{
    SDL_Event event;
    if(SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
                m_bRunning = false;
            break;

            default:
            break;
        }
    }
}

void Game::clean()
{
    std::cout << "cleaning game\n";
    SDL_DestroyWindow(m_pWindow);
    SDL_DestroyRenderer(m_pRenderer);
    SDL_Quit();
}

int main(int argc, char* argv[])
{
     g_game = new Game();

     g_game->init("SDL Tutorial v0.0.1", 100, 100, 640, 480, false);

    while(g_game->running())
    {
        g_game->handleEvents();
        g_game->update();
        g_game->render();
    }
     g_game->clean();

    return 0;
}