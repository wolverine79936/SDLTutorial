#include "SDL2/SDL.h"

#ifndef __Game__
#define __Game__

class Game
{
    public:

        Game() {};
        ~Game() {};

        // simply set the running variable to true
        bool init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

        void render();
        void update();
        void handleEvents();
        void clean();

        // a function to access the private running variable
        bool running() { return m_bRunning; }

    private:

        SDL_Window* m_pWindow;
        SDL_Renderer* m_pRenderer;

        SDL_Texture* m_pTexture; // the new SDL_texture variable
        SDL_Rect m_sourceRectangle; // the first rectangle
        SDL_Rect m_destinationRectangle; // another rectangle

        bool m_bRunning;
};

#endif /* defined(__Game__) */