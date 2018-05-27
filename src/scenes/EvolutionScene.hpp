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
#include <scenes/Scene.hpp>

using namespace Engine;
using namespace Objects;
using namespace Engine::Rendering;
using namespace Engine::Texts;
using namespace Shaders;
using namespace Engine::nsAnimation::Animations;
using namespace Engine::nsAnimation::KeyFrames;

namespace Scenes
{
    class EvolutionScene : public Scene
    {
    private:
        std::vector<QuadPtr> _quads;
        std::vector<TextPtr> _texts;
        RenderManagerPtr _renderManager;
        glm::mat4 _projection;
        InputManagerPtr _inputManager;
        TextPtr _whatText;
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
        pid_t _evolutionSoundPID;
        std::vector<BitMapPtr> _cachedFirstStageFadeBitMaps;
        std::vector<BitMapPtr> _cachedSecondStageFadeBitMaps;
        std::vector<BitMapPtr> _cachedBackGroundFadeBitMaps;
        QuadPtr _arrow;

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
        void EvolutionSceneFadeBackCompletedCallback();
        void EvolutionCongratsTextDrawnCallback();

        bool _startEvolutionTextDrawEnabled = false;
        bool _flyAroundsActivated = false;
        bool _rainActivated = false;
        bool _circlesActivated = false;
        bool _fadeToWhiteCompleted = false;
        bool _evolutionMainAnimationEnabled = false;
        bool _evolutionFadeToWhiteEnabled = false;
        bool _evolutionLastMessageDrawEnabled = false;
        void Init();
        void PlayEvolutionSound();
        void GenerateCache();

    public:
        EvolutionScene(InputManagerPtr inputManager);
        ~EvolutionScene();
        void Animate(float delta);
        void Render();
        void Update(float delta);
        void Clean();
    };

    typedef std::shared_ptr<EvolutionScene> EvolutionScenePtr;
}
#endif //POKEMON_CUSTOM_EVOLUTION_SCENE_HPP
