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
    std::vector<Quad *> _quads;
    std::vector<Text *> _texts;
    RenderManager *_renderManager;
    glm::mat4 _projection;
    InputManager *_inputManager;
    Text *_startEvolutionTextFirstPart;
    Text *_startEvolutionTextSecondPart;
    EvolutionQuad *_background;
    EvolutionQuad *_evolution;

    // callbacks
    void WhatTextDrawFinishedCallback();
    void StartEvolutionTextFirstPartDrawFinishedCallback();
    void StartEvolutionTextDrawFinishedCallback();
    void EvolutionSceneFadeCompletedCallback();
    bool _startEvolutionTextDrawEnabled = false;

    void Init();
public:
    Scene(InputManager *inputManager);
    ~Scene();
    void Animate(float delta);
    void Render();
    void Update();
    void Clean();
};

typedef std::shared_ptr<Scene> ScenePtr;

#endif //POKEMON_CUSTOM_EVOLUTION_SCENE_HPP
