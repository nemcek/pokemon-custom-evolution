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

using namespace Engine;
using namespace Objects;
using namespace Engine::Rendering;
using namespace Engine::Texts;
using namespace Shaders;
using namespace Engine::nsAnimation::Animations;
using namespace Engine::nsAnimation::KeyFrames;

namespace Scenes
{
    class Scene
    {
    private:
        std::vector<QuadPtr> _quads;
        std::vector<TextPtr> _texts;
        RenderManagerPtr _renderManager;
        glm::mat4 _projection;
        InputManagerPtr _inputManager;
        TextPtr _startEvolutionTextFirstPart;
        TextPtr _startEvolutionTextSecondPart;
        EvolutionQuadPtr _background;
        EvolutionQuadPtr _evolution;
        LoaderPtr _loader;
        glm::vec2 _mainQuadPos;
        PngImagePtr _backgroundImage;
        PngImagePtr _evolutionFirstStageImg;
        PngImagePtr _evolutionSecondStageImg;
        PngImagePtr _evolutionSecondStageImg2;

        // callbacks
        void WhatTextDrawFinishedCallback();
        void StartEvolutionTextFirstPartDrawFinishedCallback();
        void StartEvolutionTextDrawFinishedCallback();
        void EvolutionSceneFadeCompletedCallback();
        void EvolutionSceneFlyAroundsCompletedCallBack();
        void EvolutionSceneRainCompleted();
        void EvolutionSceneEvolutionCompletedCallback();
        void EvolutionSceneCirclesCompletedCallback();
        void EvolutionSceneFadeToWhiteCompletedCallback();
        bool _startEvolutionTextDrawEnabled = false;
        bool _flyAroundsActivated = false;
        bool _rainActivated = false;
        bool _circlesActivated = false;
        bool _fadeToWhiteCompleted = false;
        void Init();

    public:
        Scene(InputManagerPtr inputManager);
        ~Scene();
        void Animate(float delta);
        void Render();
        void Update(float delta);
        void Clean();
    };

    typedef std::shared_ptr<Scene> ScenePtr;
}
#endif //POKEMON_CUSTOM_EVOLUTION_SCENE_HPP
