//
// Created by martin on 31.05.2016.
//


#include <objects/EvolutionParticle.hpp>
#include <engine/animation/animations/ParticleAnimation.hpp>
#include <objects/EvolutionParticleGenerator.hpp>
#include <signal.h>
#include "EvolutionScene.hpp"

namespace Scenes
{
    EvolutionScene::EvolutionScene(InputManagerPtr inputManager)
            : _inputManager(inputManager) {
        Init();
    }

    EvolutionScene::~EvolutionScene() {
        _quads.clear();
        _texts.clear();
    }

    void EvolutionScene::Init() {
        _projection = glm::ortho(0.0f, static_cast<GLfloat>(Constants::WINDOW_WIDTH), 0.0f,
                                 static_cast<GLfloat>(Constants::WINDOW_HEIGHT));

        _mainQuadPos = glm::vec2(Constants::WINDOW_WIDTH / 2, Constants::WINDOW_HEIGHT / 2 + Constants::WINDOW_HEIGHT / 6);
        _evolutionFirstStageImg = std::make_shared<PngImage>("_data/first_evo.png");
        _backgroundImage = std::make_shared<PngImage>("data/evolution_background.png");
        PngImagePtr arrow = std::make_shared<PngImage>("data/evolution_arrow.png");
        _evolutionSecondStageImg = std::make_shared<PngImage>("_data/second_evo.png");
        _evolutionSecondStageImg2 = std::make_shared<PngImage>("_data/second_evo.png");
        PngImagePtr particleCircleImage = std::make_shared<PngImage>("data/evolution_particle_circle.png");
        PngImagePtr particleCrossImage = std::make_shared<PngImage>("data/evolution_particle_cross.png");
        PngImagePtr particleQuadImage = std::make_shared<PngImage>("data/evolution_particle_quad.png");

        TextShaderPtr textShader = std::make_shared<TextShader>();
        TextRendererPtr textRenderer = std::make_shared<TextRenderer>(textShader);
        StaticRendererPtr staticRenderer = std::make_shared<StaticRenderer>(std::make_shared<StaticShader>());
        _renderManager = std::make_shared<RenderManager>(textRenderer, staticRenderer);
        _loader = std::make_shared<Loader>(staticRenderer->shader->programId);

        _evolutionSecondStageImg->bitmap = Transformations::Scale(_evolutionSecondStageImg->bitmap, _evolutionFirstStageImg->bitmap->width, _evolutionFirstStageImg->bitmap->height);
        _evolutionSecondStageImg2->bitmap = Transformations::Scale(_evolutionSecondStageImg->bitmap, _evolutionFirstStageImg->bitmap->width, _evolutionFirstStageImg->bitmap->height);

        _evolution = std::make_shared<EvolutionQuad>(_loader, _mainQuadPos, 0.466552734f, 0.70f, _evolutionFirstStageImg->bitmap, _evolutionSecondStageImg->bitmap);
        _background = std::make_shared<EvolutionQuad>(_loader, glm::vec2(Constants::WINDOW_WIDTH / 2,
                                                                        Constants::WINDOW_HEIGHT / 2), 1.0f,
                                                      _backgroundImage->bitmap, nullptr);
        _arrow = std::make_shared<Quad>(_loader, glm::vec2(900.0f, 50.0f), 0.04f, arrow->bitmap);
        EvolutionParticlePtr particleCircle = std::make_shared<EvolutionParticle>(_loader,
                                                                                  glm::vec2(Constants::WINDOW_WIDTH / 2,
                                                                                            Constants::WINDOW_HEIGHT / 2),
                                                                                  0.05f,
                                                                                  particleCircleImage->bitmap,
                                                                                  particleQuadImage->bitmap,
                                                                                  particleCrossImage->bitmap, 0.0f);

        _renderManager->ProcessProjection(_projection);
        GenerateCache();

        textShader->Start();
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        FontPtr font = std::make_shared<Font>("data/Pokemon.ttf", 48);
        std::string str1("What?!");
        _whatText = std::make_shared<Text>(glm::vec2(55.0f, 190.0f), 1.0f, glm::vec3(0, 0, 0), font);
        std::string str2("Martin Nemcek is");
        _startEvolutionTextFirstPart = std::make_shared<Text>(glm::vec2(55.0f, 120.0f), 1.0f, glm::vec3(0, 0, 0), font);
        std::string str3("evolving!");
        _startEvolutionTextSecondPart = std::make_shared<Text>(glm::vec2(55.0f, 50.0f), 1.0f, glm::vec3(0, 0, 0), font);

        this->_texts.push_back(_whatText);
        this->_texts.push_back(_startEvolutionTextFirstPart);
        this->_texts.push_back(_startEvolutionTextSecondPart);

        _arrow->animation = std::make_shared<Animation>();
        _arrow->animation->enabled = false;
        _arrow->animation->Add(std::make_shared<KeyFrame>(0.0f, _arrow->position, 1.0f));
        _arrow->animation->Add(std::make_shared<KeyFrame>(0.5f, _arrow->position, 1.0f));
        _arrow->animation->Add(std::make_shared<KeyFrame>(0.5f, _arrow->position, 0.0f));
        _arrow->animation->Add(std::make_shared<KeyFrame>(1.0f, _arrow->position, 0.0f));

        std::string empty("");
        _whatText->animation = std::make_shared<TextAnimation>(false);
        _whatText->animation->enabled = false;
        _whatText->animation->Add(std::make_shared<TextKeyFrame>(0.0f, _whatText->position, _whatText->scale, empty));
        _whatText->animation->Add(std::make_shared<TextKeyFrame>(.65f, _whatText->position, _whatText->scale, str1,
                                                             std::bind(&EvolutionScene::WhatTextDrawFinishedCallback, this)));

        _startEvolutionTextFirstPart->animation = std::make_shared<TextAnimation>(false);
        _startEvolutionTextFirstPart->animation->enabled = false;
        _startEvolutionTextFirstPart->animation->Add(
                std::make_shared<TextKeyFrame>(0.0f, _startEvolutionTextFirstPart->position, 1.0f, empty));
        _startEvolutionTextFirstPart->animation->Add(
                std::make_shared<TextKeyFrame>(1.0f, _startEvolutionTextFirstPart->position, 1.0f, str2,
                                               std::bind(&EvolutionScene::StartEvolutionTextFirstPartDrawFinishedCallback,
                                                         this)));

        _startEvolutionTextSecondPart->animation = std::make_shared<TextAnimation>(false);
        _startEvolutionTextSecondPart->animation->enabled = false;
        _startEvolutionTextSecondPart->animation->Add(
                std::make_shared<TextKeyFrame>(0.0f, _startEvolutionTextSecondPart->position, 1.0f, empty));
        _startEvolutionTextSecondPart->animation->Add(
                std::make_shared<TextKeyFrame>(0.65f, _startEvolutionTextSecondPart->position, 1.0f, str3,
                                               std::bind(&EvolutionScene::StartEvolutionTextDrawFinishedCallback, this)));

        _background->animation = std::make_shared<EvolutionAnimation>(_background->bitMap);
        _background->animation->enabled = false;
        _background->animation->repeat = false;
        _background->animation->Add(
                std::make_shared<EvolutionKeyFrame>(0.0f, _background->position, _background->scaleX));
        _background->animation->Add(std::make_shared<EvolutionKeyFrame>(1.0f, _background->position, _background->scaleX,
                                                                        glm::vec3(0.0, 0.0, 0.0), 286));
        _background->animation->Add(std::make_shared<EvolutionKeyFrame>(3.0f, _background->position, _background->scaleX,
                                                                        std::bind(
                                                                                &EvolutionScene::EvolutionSceneFadeCompletedCallback,
                                                                                this)));

        this->_quads.push_back(_background);
        this->_quads.push_back(_evolution);
        this->_quads.push_back(_arrow);

        for (QuadPtr quad : this->_quads)
            _renderManager->ProcessQuad(quad);

        for (TextPtr text : this->_texts)
            _renderManager->ProcessText(text);
    }

    void EvolutionScene::GenerateCache() {
        for (float i = 0.0f; i < 1.0f; i += 0.1f) {
            BitMapPtr bitMap = Transformations::Fade(_evolutionFirstStageImg->bitmap, glm::vec3(255.0, 255.0, 255.0), 0, i);
            _cachedFirstStageFadeBitMaps.push_back(bitMap);
        }
        BitMapPtr bitMap = Transformations::Fade(_evolutionFirstStageImg->bitmap, glm::vec3(255.0, 255.0, 255.0), 0, 1.0f);
        _cachedFirstStageFadeBitMaps.push_back(bitMap);

        BitMapPtr white = Transformations::ChangeToWhite(_evolutionSecondStageImg2->bitmap);
        for (float i = 0.0f; i < 1.0f; i += 0.1f) {
            BitMapPtr bitMapSecond = Transformations::Fade(white, _evolutionSecondStageImg2->bitmap, 0, i);
            _cachedSecondStageFadeBitMaps.push_back(bitMapSecond);
        }
        BitMapPtr bitMapSecond = Transformations::Fade(white, _evolutionSecondStageImg2->bitmap, 0, 1.0f);
        _cachedSecondStageFadeBitMaps.push_back(bitMapSecond);
    }

    void EvolutionScene::Animate(float delta) {
        for (QuadPtr quad : this->_quads)
            quad->Animate(delta);

        for (TextPtr text : this->_texts)
            text->Animate(delta);
    }

    void EvolutionScene::Render() {
        _renderManager->Prepare();
        _renderManager->Render(this->_projection);
    }

    void EvolutionScene::Update(float delta) {
        for (QuadPtr quad : this->_quads) {
            quad->Update(delta);
        }

        if (_inputManager->IsEnterPressed()) {
            _whatText->animation->enabled = true;
        }

        if (_inputManager->IsAPressed() && _startEvolutionTextDrawEnabled)
            _startEvolutionTextFirstPart->animation->enabled = true;

        if (_flyAroundsActivated) {
            std::vector<EvolutionParticlePtr> *particles;
            particles = EvolutionParticleGenerator::GenerateFlyArounds(_loader,
                                                                       std::bind(&EvolutionScene::EvolutionSceneFlyAroundsCompletedCallBack,
                                                                                 this));
            for (EvolutionParticlePtr particle : *particles) {
                _renderManager->ProcessQuad(particle);
                _quads.push_back(particle);
            }

            _evolution->animation = std::make_shared<EvolutionAnimation>(_evolution->bitMap);
            _evolution->animation->enabled = true;
            _evolution->animation->repeat = false;
            _evolution->animation->Add(std::make_shared<EvolutionKeyFrame>(0.0f, _mainQuadPos, 1.0f));
            _evolution->animation->Add(std::make_shared<EvolutionKeyFrame>(2.0f, _mainQuadPos, 1.0f, _cachedFirstStageFadeBitMaps));

            _flyAroundsActivated = false;
        }

        if (_rainActivated) {
            std::vector<EvolutionParticlePtr> *particles;
            particles = EvolutionParticleGenerator::GenerateRain(_loader,
                                                                       std::bind(&EvolutionScene::EvolutionSceneRainCompleted,
                                                                                 this));
            for (EvolutionParticlePtr particle : *particles) {
                _renderManager->ProcessQuad(particle);
                _quads.push_back(particle);
            }
            _rainActivated = false;
        }

        if (_circlesActivated) {
            PngImagePtr img = std::make_shared<PngImage>("data/evolution_circle.png");
            EvolutionQuadPtr particle;
            particle = std::make_shared<EvolutionQuad>(_loader, _mainQuadPos, 1.0f, img->bitmap, nullptr);

            particle->animation = std::make_shared<EvolutionAnimation>(particle->bitMap);
            particle->animation->enabled = true;
            particle->animation->repeat = false;
            particle->animation->Add(std::make_shared<EvolutionKeyFrame>(0.0f, particle->position, particle->scaleX));
            particle->animation->Add(std::make_shared<EvolutionKeyFrame>(0.5f, particle->position, 0.0f));
            particle->animation->Add(std::make_shared<EvolutionKeyFrame>(0.5f, particle->position, 1.0f));
            particle->animation->Add(std::make_shared<EvolutionKeyFrame>(1.0f, particle->position, 0.0f,
                                                                         std::bind(&EvolutionScene::EvolutionSceneCirclesCompletedCallback, this)));


            _renderManager->ProcessQuad(particle);
            _quads.push_back(particle);
            _circlesActivated = false;
        }

        if (_fadeToWhiteCompleted) {
            _background->animation = std::make_shared<EvolutionAnimation>(_background->bitMap);
            _background->animation->enabled = true;
            _background->animation->repeat = false;
            _background->animation->Add(std::make_shared<EvolutionKeyFrame>(0.0f, _background->position, _background->scaleX));
            _background->animation->Add(std::make_shared<EvolutionKeyFrame>(3.0f, _background->position, _background->scaleX,
                                                                            _backgroundImage->bitmap, 286));

            _evolution->ChangeToWhite();
            _evolution->animation = std::make_shared<EvolutionAnimation>(_evolution->bitMap);
            _evolution->animation->enabled = true;
            _evolution->animation->repeat = false;
            _evolution->animation->Add(std::make_shared<EvolutionKeyFrame>(0.0f, _mainQuadPos, 1.0f));
            _evolution->animation->Add(std::make_shared<EvolutionKeyFrame>(3.0f, _mainQuadPos, 1.0f,
                                                                           _cachedSecondStageFadeBitMaps));
            _evolution->animation->Add(std::make_shared<EvolutionKeyFrame>(3.0f, _mainQuadPos, 1.0f,
                                                                           std::bind(&EvolutionScene::EvolutionSceneFadeBackCompletedCallback, this)));

            _fadeToWhiteCompleted = false;
        }

        if (_evolutionMainAnimationEnabled) {
            _evolution->animation = std::make_shared<EvolutionAnimation>(_evolution->bitMap);
            _evolution->animation->enabled = true;
            _evolution->animation->repeat = false;
            _evolution->animation->Add(std::make_shared<EvolutionKeyFrame>(0.0f, _mainQuadPos, 1.0f));
            _evolution->animation->Add(std::make_shared<EvolutionKeyFrame>(1.0f, _mainQuadPos, 1.0f));
            _evolution->animation->Add(std::make_shared<EvolutionKeyFrame>(2.0f, _mainQuadPos, 0.0f, true));
            _evolution->animation->Add(std::make_shared<EvolutionKeyFrame>(3.0f, _mainQuadPos, 1.0f));
            _evolution->animation->Add(std::make_shared<EvolutionKeyFrame>(4.0f, _mainQuadPos, 0.0f, true));
            _evolution->animation->Add(std::make_shared<EvolutionKeyFrame>(5.0f, _mainQuadPos, 1.0f));
            _evolution->animation->Add(std::make_shared<EvolutionKeyFrame>(6.0f, _mainQuadPos, 0.0f, true));
            _evolution->animation->Add(std::make_shared<EvolutionKeyFrame>(7.0f, _mainQuadPos, 1.0f, std::bind(&EvolutionScene::EvolutionSceneEvolutionCompletedCallback, this)));

            _evolutionMainAnimationEnabled = false;
        }

        if (_evolutionFadeToWhiteEnabled) {
            _background->animation = std::make_shared<EvolutionAnimation>(_background->bitMap);
            _background->animation->enabled = true;
            _background->animation->repeat = false;
            _background->animation->Add(
                    std::make_shared<EvolutionKeyFrame>(0.0f, _background->position, _background->scaleX));
            _background->animation->Add(std::make_shared<EvolutionKeyFrame>(1.0f, _background->position, _background->scaleX,
                                                                            glm::vec3(255.0, 255.0, 255.0), 286,
                                                                            std::bind(&EvolutionScene::EvolutionSceneFadeToWhiteCompletedCallback, this)));

            _evolutionFadeToWhiteEnabled = false;
        }

        if (_evolutionLastMessageDrawEnabled) {
            FontPtr font = std::make_shared<Font>("data/Pokemon.ttf", 48);
            FontPtr fontS = std::make_shared<Font>("data/Pokemon.ttf", 40);
            std::string str1("Congratulations!");
            TextPtr congratsText = std::make_shared<Text>(glm::vec2(55.0f, 190.0f), 1.0f, glm::vec3(0, 0, 0), font);
            std::string str2("Martin Nemcek evolved");
            TextPtr lastMsgFirstPart = std::make_shared<Text>(glm::vec2(55.0f, 120.0f), 1.0f, glm::vec3(0, 0, 0), fontS);
            std::string str3("into Bc.Martin Nemcek!");
            TextPtr lastMsgSecondPart = std::make_shared<Text>(glm::vec2(55.0f, 50.0f), 1.0f, glm::vec3(0, 0, 0), fontS);

            this->_texts.push_back(congratsText);
            this->_texts.push_back(lastMsgFirstPart);
            this->_texts.push_back(lastMsgSecondPart);

            std::string empty("");
            congratsText->animation = std::make_shared<TextAnimation>(false);
            congratsText->animation->Add(std::make_shared<TextKeyFrame>(0.0f, congratsText->position, congratsText->scale, empty));
            congratsText->animation->Add(std::make_shared<TextKeyFrame>(.8f, congratsText->position, congratsText->scale, str1));

            lastMsgFirstPart->animation = std::make_shared<TextAnimation>(false);
            lastMsgFirstPart->animation->Add(std::make_shared<TextKeyFrame>(0.0f, congratsText->position, congratsText->scale, empty));
            lastMsgFirstPart->animation->Add(
                    std::make_shared<TextKeyFrame>(1.2f, lastMsgFirstPart ->position, 1.0f, empty));
            lastMsgFirstPart->animation->Add(
                    std::make_shared<TextKeyFrame>(2.4f, lastMsgFirstPart ->position, 1.0f, str2));

            lastMsgSecondPart->animation = std::make_shared<TextAnimation>(false);
            lastMsgSecondPart->animation->Add(std::make_shared<TextKeyFrame>(0.0f, congratsText->position, congratsText->scale, empty));
            lastMsgSecondPart->animation->Add(
                    std::make_shared<TextKeyFrame>(2.6f, _startEvolutionTextSecondPart->position, 1.0f, empty));
            lastMsgSecondPart->animation->Add(
                    std::make_shared<TextKeyFrame>(4.0f, _startEvolutionTextSecondPart->position, 1.0f, str3));

            _renderManager->ProcessText(congratsText);
            _renderManager->ProcessText(lastMsgFirstPart);
            _renderManager->ProcessText(lastMsgSecondPart);
            _arrow->animation->enabled = false;
            _arrow->Scale(glm::vec2(0.0f, 0.0f));

            _evolutionLastMessageDrawEnabled = false;
        }
    }

    void EvolutionScene::Clean() {
        this->_renderManager->Clean();
        kill(_evolutionSoundPID, SIGTERM);
    }

    void EvolutionScene::WhatTextDrawFinishedCallback() {
        _startEvolutionTextDrawEnabled = true;
        _arrow->animation->enabled = true;
    }

    void EvolutionScene::StartEvolutionTextFirstPartDrawFinishedCallback() {
        _startEvolutionTextSecondPart->animation->enabled = true;
        _startEvolutionTextSecondPart->animation->SetDelay(0.3f);
    }

    void EvolutionScene::StartEvolutionTextDrawFinishedCallback() {
        _background->animation->enabled = true;
        _background->animation->SetDelay(1.0f);
        PlayEvolutionSound();
    }


    void EvolutionScene::EvolutionSceneFadeCompletedCallback() {
        _flyAroundsActivated = true;
    }

    void EvolutionScene::EvolutionSceneFlyAroundsCompletedCallBack() {
        _rainActivated = true;
    }

    void EvolutionScene::EvolutionSceneRainCompleted() {
        _evolutionMainAnimationEnabled = true;
    }

    void EvolutionScene::EvolutionSceneEvolutionCompletedCallback() {
        _circlesActivated = true;
    }

    void EvolutionScene::EvolutionSceneCirclesCompletedCallback() {
        _evolutionFadeToWhiteEnabled = true;
    }

    void EvolutionScene::EvolutionSceneFadeToWhiteCompletedCallback() {
        _fadeToWhiteCompleted = true;
    }

    void EvolutionScene::EvolutionSceneFadeBackCompletedCallback() {
        _whatText->StopRendering();
        _startEvolutionTextFirstPart->StopRendering();
        _startEvolutionTextSecondPart->StopRendering();
        _evolutionLastMessageDrawEnabled = true;
    }

    void EvolutionScene::PlayEvolutionSound() {
        // quick and dirty way
        pid_t pid = fork();
        if (pid == 0) {
            _evolutionSoundPID = system("paplay \"/home/nemcek/dev/pokemon-custom-evolution/data/evolution_music.wav\"");
            exit(0);
        }
    }

}