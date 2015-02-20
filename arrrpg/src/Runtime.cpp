// arrrpg - Runtime.cpp
// Copyright (C) 2015 Ole Diederich <ole@schwarzekiste.info>
// This file is part of arrrpg.
// arrrpg is free software; you can redistribute it and/or modify it
// under the terms of the GNU Affero General Public License as
// published by the Free Software Foundation; either version 3 of the
// License, or (at your option) any later version.
//
// arrrpg is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include "Runtime.h"
#include "stdinc.h"
#include <SDL2/SDL.h>

//---------------------------------------------------------------------------------------------------------------------

namespace arrrpg {

//---------------------------------------------------------------------------------------------------------------------

Runtime::Runtime()
    :
    m_window( NULL )
{
    SDL_Init(SDL_INIT_VIDEO);              // Initialize SDL2

    m_window = SDL_CreateWindow(
                "arrrpg",                          // window title
                SDL_WINDOWPOS_UNDEFINED,           // initial x position
                SDL_WINDOWPOS_UNDEFINED,           // initial y position
                1280,                              // width, in pixels
                720,                               // height, in pixels
                SDL_WINDOW_OPENGL                  // flags - see below
                );

    if (m_window == NULL) {
        printf("Could not create window: %s\n", SDL_GetError());
        ARRRPG_ASSERT( false );
    }
}

//---------------------------------------------------------------------------------------------------------------------

Runtime::~Runtime()
{
    if (m_window)
        SDL_DestroyWindow(m_window);

    SDL_Quit();
}

//---------------------------------------------------------------------------------------------------------------------

void
Runtime::start()
{
    SDL_Event event;
    int end = 0;

    while (!end)
    {
        if (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                end = 1;
                break;

            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                case SDLK_q:
                    end = 1;
                    break;
                }
                break;
            }
        }
    }
}

//---------------------------------------------------------------------------------------------------------------------

} // namespace arrrpg
