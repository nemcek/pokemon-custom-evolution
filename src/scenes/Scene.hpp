//
// Created by martin on 31.05.2016.
//

#ifndef POKEMON_CUSTOM_EVOLUTION_SCENE_HPP
#define POKEMON_CUSTOM_EVOLUTION_SCENE_HPP

#include <images/PngImage.hpp>
#include <engine/rendering/RenderManager.hpp>
#include <shaders/TextShader.hpp>
#include <objects/EvolutionQuad.hpp>
#include <engine/animation/keyframes/EvolutionKeyFrame.hpp>
#include <engine/animation/keyframes/TextKeyFrame.hpp>
#include <src/constants/Constants.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <objects/Quad.hpp>
#include <engine/text/Text.hpp>
#include <engine/InputManager.hpp>

class Scene
{
private:
    std::vector<Quad *> quads;
    std::vector<Text *> texts;
    RenderManager *renderManager;
    glm::mat4 projection;
    InputManager *inputManager;
    Text *startEvolutionTextFirstPart;
    Text *startEvolutionTextSecondPart;
    EvolutionQuad *background;
    EvolutionQuad *evolution;

    // callbacks
    void WhatTextDrawFinishedCallback();
    void StartEvolutionTextFirstPartDrawFinishedCallback();
    void StartEvolutionTextDrawFinishedCallback();
    void EvolutionSceneFadeCompletedCallback();
    bool startEvolutionTextDrawEnabled = false;

    void Init();
public:
    Scene(InputManager *inputManager);
    void Animate(float delta);
    void Render();
    void Update();
    void Clean();
};

#endif //POKEMON_CUSTOM_EVOLUTION_SCENE_HPP
