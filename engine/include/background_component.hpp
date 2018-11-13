/**
* @file background_component.hpp
* @brief Purpose: Defines the general scope of background.
*
* GPL v3.0 License
* Copyright (c) 2017 Azo
*
* Notice: TheAzo, TheAzoTeam
* https://github.com/TecProg2018-2/Azo
*
* This file implements the main background component its declaration and state.
*/
#ifndef BACKGROUND_COMPONENT_HPP
#define BACKGROUND_COMPONENT_HPP

#include <string>
#include <iostream>
#include "input_manager.hpp"
#include "component.hpp"
#include "sdl2include.h"
#include "log.h"

namespace engine {

  class BackgroundComponent : public Component {
  protected:
    std::string imagePath;
    SDL_Texture *imageTexture;
    SDL_Rect renderQuad;
    int componentWidth;
    int componentHeight;

  public:
    BackgroundComponent();
    BackgroundComponent(std::string imagePath);
    BackgroundComponent(GameObject &gameObject, std::string imagePath);
    ~BackgroundComponent();

    void init();
    void shutdown();
    void draw();
    inline std::string getClassName(){
      return "BackgroundComponent";
    }
  };
}

#endif
