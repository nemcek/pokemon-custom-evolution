//
// Created by martin on 31.05.2016.
//


#include <objects/EvolutionParticle.hpp>
#include <engine/animation/animations/ParticleAnimation.hpp>
#include <objects/EvolutionParticleGenerator.hpp>
#include "Scene.hpp"

namespace Scenes
{
    Scene::Scene(InputManagerPtr inputManager)
            : _inputManager(inputManager) {
        Init();
    }

    Scene::~Scene() {
//    delete _renderManager;
//    delete _evolution;
//    delete _background;
//    delete _startEvolutionTextFirstPart;
//    delete _startEvolutionTextSecondPart;
        _quads.clear();
        _texts.clear();
    }

    void Scene::Init() {
        _projection = glm::ortho(0.0f, static_cast<GLfloat>(Constants::WINDOW_WIDTH), 0.0f,
                                 static_cast<GLfloat>(Constants::WINDOW_HEIGHT));

        _mainQuadPos = glm::vec2(Constants::WINDOW_WIDTH / 2, Constants::WINDOW_HEIGHT / 2 + Constants::WINDOW_HEIGHT / 6);
        PngImagePtr png_image = std::make_shared<PngImage>("_data/github.png");
        PngImagePtr backgroundImage = std::make_shared<PngImage>("data/evolution_background.png");
        PngImagePtr arrow = std::make_shared<PngImage>("data/evolution_arrow.png");
        PngImagePtr googleImage = std::make_shared<PngImage>("_data/google.png");
        PngImagePtr particleCircleImage = std::make_shared<PngImage>("data/evolution_particle_circle.png");
        PngImagePtr particleCrossImage = std::make_shared<PngImage>("data/evolution_particle_cross.png");
        PngImagePtr particleQuadImage = std::make_shared<PngImage>("data/evolution_particle_quad.png");

        TextShaderPtr textShader = std::make_shared<TextShader>();
        TextRendererPtr textRenderer = std::make_shared<TextRenderer>(textShader);
        StaticRendererPtr staticRenderer = std::make_shared<StaticRenderer>(std::make_shared<StaticShader>());
        _renderManager = std::make_shared<RenderManager>(textRenderer, staticRenderer);
        _loader = std::make_shared<Loader>(staticRenderer->shader->programId);
        _evolution = std::make_shared<EvolutionQuad>(_loader, _mainQuadPos, 0.5f, png_image->bitmap, googleImage->bitmap);
        _background = std::make_shared<EvolutionQuad>(_loader, glm::vec2(Constants::WINDOW_WIDTH / 2,
                                                                        Constants::WINDOW_HEIGHT / 2), 1.0f,
                                                      backgroundImage->bitmap, nullptr);
        QuadPtr arrowQuad = std::make_shared<Quad>(_loader, glm::vec2(900.0f, 50.0f), 0.04f, arrow->bitmap);
        EvolutionParticlePtr particleCircle = std::make_shared<EvolutionParticle>(_loader,
                                                                                  glm::vec2(Constants::WINDOW_WIDTH / 2,
                                                                                            Constants::WINDOW_HEIGHT / 2),
                                                                                  0.05f,
                                                                                  particleCircleImage->bitmap,
                                                                                  particleQuadImage->bitmap,
                                                                                  particleCrossImage->bitmap, 0.0f);

        _renderManager->ProcessProjection(_projection);

        textShader->Start();
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        FontPtr font = std::make_shared<Font>("data/Pokemon.ttf", 48);
        std::string str1("What?!");
        TextPtr text1 = std::make_shared<Text>(glm::vec2(55.0f, 190.0f), 1.0f, glm::vec3(0, 0, 0), font);
        std::string str2("Your Martin Nemcek");
        _startEvolutionTextFirstPart = std::make_shared<Text>(glm::vec2(55.0f, 120.0f), 1.0f, glm::vec3(0, 0, 0), font);
        std::string str3("is evolving!");
        _startEvolutionTextSecondPart = std::make_shared<Text>(glm::vec2(55.0f, 50.0f), 1.0f, glm::vec3(0, 0, 0), font);

        this->_texts.push_back(text1);
        this->_texts.push_back(_startEvolutionTextFirstPart);
        this->_texts.push_back(_startEvolutionTextSecondPart);

        PointCompound4 pointCompound = {{475, 950},
                                        {250, 922},
                                        {0, 621},
                                        {120, 354}};

        PointCompound4 pointCompound2 = {{475, 950},
                                         {306, 922},
                                         {119, 621},
                                         {208, 354}};

        PointCompound4 pointCompound3 = {{691, 801},
                                         {534, 854},
                                         {515, 922},
                                         {514, 957}};
//
//
        particleCircle->animation = std::make_shared<ParticleAnimation>(particleCircle->bitMap);
        particleCircle->animation->enabled = true;
        particleCircle->animation->Add(std::make_shared<ParticleKeyFrame>(0.0f, particleCircle->position, 1.0f,
                                                                             pointCompound));
        particleCircle->animation->Add(std::make_shared<ParticleKeyFrame>(5.0f, particleCircle->position, .66f,
                                                                          pointCompound2, true));
        particleCircle->animation->Add(std::make_shared<ParticleKeyFrame>(9.0f, particleCircle->position, .33f,
                                                                          pointCompound3, true));
        particleCircle->animation->Add(std::make_shared<ParticleKeyFrame>(12.33f, particleCircle->position, .1f,
                                                                          pointCompound3, true));

        _evolution->animation = std::make_shared<EvolutionAnimation>(_evolution->bitMap);
        _evolution->animation->enabled = false;
        _evolution->animation->repeat = false;
        _evolution->animation->Add(std::make_shared<EvolutionKeyFrame>(0.0f, _mainQuadPos, 1.0f));
        _evolution->animation->Add(std::make_shared<EvolutionKeyFrame>(1.0f, _mainQuadPos, 1.0f, glm::vec3(255.0, 255.0, 255.0), 0,
                                                                       false, true));
        _evolution->animation->Add(std::make_shared<EvolutionKeyFrame>(2.0f, _mainQuadPos, 0.0f, true));
        _evolution->animation->Add(std::make_shared<EvolutionKeyFrame>(3.0f, _mainQuadPos, 1.0f));
        _evolution->animation->Add(std::make_shared<EvolutionKeyFrame>(4.0f, _mainQuadPos, 0.0f, true));
        _evolution->animation->Add(std::make_shared<EvolutionKeyFrame>(5.0f, _mainQuadPos, 1.0f));
        _evolution->animation->Add(std::make_shared<EvolutionKeyFrame>(6.0f, _mainQuadPos, 0.0f, true));
        _evolution->animation->Add(std::make_shared<EvolutionKeyFrame>(7.0f, _mainQuadPos, 1.0f));
        _evolution->animation->Add(std::make_shared<EvolutionKeyFrame>(8.0f, _mainQuadPos, 0.0f, true));
        _evolution->animation->Add(std::make_shared<EvolutionKeyFrame>(9.0f, _mainQuadPos, 1.0f));
        _evolution->animation->Add(std::make_shared<EvolutionKeyFrame>(10.0f, _mainQuadPos, 0.0f, true));
        _evolution->animation->Add(std::make_shared<EvolutionKeyFrame>(11.0f, _mainQuadPos, 1.0f, std::bind(&Scene::EvolutionSceneEvolutionCompletedCallback, this)));

        arrowQuad->animation = std::make_shared<Animation>();
        arrowQuad->animation->Add(std::make_shared<KeyFrame>(0.0f, arrowQuad->position, 1.0f));
        arrowQuad->animation->Add(std::make_shared<KeyFrame>(0.5f, arrowQuad->position, 1.0f));
        arrowQuad->animation->Add(std::make_shared<KeyFrame>(0.5f, arrowQuad->position, 0.0f));
        arrowQuad->animation->Add(std::make_shared<KeyFrame>(1.0f, arrowQuad->position, 0.0f));

        std::string empty("");
        text1->animation = std::make_shared<TextAnimation>(false);
        text1->animation->SetDelay(1.0f);
        text1->animation->Add(std::make_shared<TextKeyFrame>(0.0f, text1->position, text1->scale, empty));
        text1->animation->Add(std::make_shared<TextKeyFrame>(.65f, text1->position, text1->scale, str1,
                                                             std::bind(&Scene::WhatTextDrawFinishedCallback, this)));

        _startEvolutionTextFirstPart->animation = std::make_shared<TextAnimation>(false);
        _startEvolutionTextFirstPart->animation->enabled = false;
        _startEvolutionTextFirstPart->animation->Add(
                std::make_shared<TextKeyFrame>(0.0f, _startEvolutionTextFirstPart->position, 1.0f, empty));
        _startEvolutionTextFirstPart->animation->Add(
                std::make_shared<TextKeyFrame>(2.0f, _startEvolutionTextFirstPart->position, 1.0f, str2,
                                               std::bind(&Scene::StartEvolutionTextFirstPartDrawFinishedCallback,
                                                         this)));

        _startEvolutionTextSecondPart->animation = std::make_shared<TextAnimation>(false);
        _startEvolutionTextSecondPart->animation->enabled = false;
        _startEvolutionTextSecondPart->animation->Add(
                std::make_shared<TextKeyFrame>(0.0f, _startEvolutionTextSecondPart->position, 1.0f, empty));
        _startEvolutionTextSecondPart->animation->Add(
                std::make_shared<TextKeyFrame>(1.5f, _startEvolutionTextSecondPart->position, 1.0f, str3,
                                               std::bind(&Scene::StartEvolutionTextDrawFinishedCallback, this)));

        _background->animation = std::make_shared<EvolutionAnimation>(_background->bitMap);
        _background->animation->enabled = false;
        _background->animation->repeat = false;
        _background->animation->Add(
                std::make_shared<EvolutionKeyFrame>(0.0f, _background->position, _background->scale));
        _background->animation->Add(std::make_shared<EvolutionKeyFrame>(1.0f, _background->position, _background->scale,
                                                                        glm::vec3(0.0, 0.0, 0.0), 286,
                                                                        std::bind(
                                                                                &Scene::EvolutionSceneFadeCompletedCallback,
                                                                                this)));

        EvolutionQuadPtr particle;
        PngImagePtr img = std::make_shared<PngImage>("data/evolution_circle.png");
        particle = std::make_shared<EvolutionQuad>(_loader, _mainQuadPos,
                                                   1.0f, img->bitmap, nullptr);

//        particle->renderDelay = renderDelay;
        particle->animation = std::make_shared<EvolutionAnimation>(particle->bitMap);
        particle->animation->enabled = true;
        particle->animation->repeat = false;
        particle->animation->Add(std::make_shared<EvolutionKeyFrame>(0.0f, particle->position, particle->scale));
        particle->animation->Add(std::make_shared<EvolutionKeyFrame>(1.5f, particle->position, 0.0f));


        this->_quads.push_back(_background);
        this->_quads.push_back(_evolution);
        this->_quads.push_back(arrowQuad);
        this->_quads.push_back(particle);

//        std::vector<EvolutionParticlePtr> *particles = EvolutionParticleGenerator::GenerateFlyArounds(loader);
//        std::vector<EvolutionParticlePtr> *particles = EvolutionParticleGenerator::GenerateRain(_loader);
//
//        for (EvolutionParticlePtr particle : *particles) {
//            _quads.push_back(particle);
//        }

        for (QuadPtr quad : this->_quads)
            _renderManager->ProcessQuad(quad);

        for (TextPtr text : this->_texts)
            _renderManager->ProcessText(text);
    }

    void Scene::Animate(float delta) {
        for (QuadPtr quad : this->_quads)
            quad->Animate(delta);

        for (TextPtr text : this->_texts)
            text->Animate(delta);
    }

    void Scene::Render() {
//    for (Quad *quad : this->_quads)
//        _renderManager->ProcessQuad(quad);
//
//    for (Text *text : this->_texts)
//        _renderManager->ProcessText(text);

        _renderManager->Prepare();
        _renderManager->Render(this->_projection);
    }

    void Scene::Update(float delta) {
        for (QuadPtr quad : this->_quads) {
            quad->Update(delta);
        }

        if (_inputManager->IsAPressed() && _startEvolutionTextDrawEnabled)
            _startEvolutionTextFirstPart->animation->enabled = true;

        if (_flyAroundsActivated) {
            std::vector<EvolutionParticlePtr> *particles;
            particles = EvolutionParticleGenerator::GenerateFlyArounds(_loader,
                                                                       std::bind(&Scene::EvolutionSceneFlyAroundsCompletedCallBack,
                                                                                 this));
            for (EvolutionParticlePtr particle : *particles) {
                _renderManager->ProcessQuad(particle);
                _quads.push_back(particle);
            }
            _flyAroundsActivated = false;
        }

        if (_rainActivated) {
            std::vector<EvolutionParticlePtr> *particles;
            particles = EvolutionParticleGenerator::GenerateRain(_loader,
                                                                       std::bind(&Scene::EvolutionSceneRainCompleted,
                                                                                 this));
            for (EvolutionParticlePtr particle : *particles) {
                _renderManager->ProcessQuad(particle);
                _quads.push_back(particle);
            }
            _rainActivated = false;
        }

        if (_circlesActivated) {
            std::vector<EvolutionQuadPtr> *particles;
            particles = EvolutionParticleGenerator::GenerateCircles(_loader, _mainQuadPos, nullptr);
            for (EvolutionQuadPtr particle : *particles) {
                _renderManager->ProcessQuad(particle);
                _quads.push_back(particle);
            }
            _circlesActivated = false;
        }
    }

    void Scene::Clean() {
        this->_renderManager->Clean();
    }

    void Scene::WhatTextDrawFinishedCallback() {
        _startEvolutionTextDrawEnabled = true;
        _circlesActivated = true;
    }

    void Scene::StartEvolutionTextFirstPartDrawFinishedCallback() {
        _startEvolutionTextSecondPart->animation->enabled = true;
        _startEvolutionTextSecondPart->animation->SetDelay(0.3f);
    }

    void Scene::StartEvolutionTextDrawFinishedCallback() {
        _background->animation->enabled = true;
    }


    void Scene::EvolutionSceneFadeCompletedCallback() {
        _flyAroundsActivated = true;
    }

    void Scene::EvolutionSceneFlyAroundsCompletedCallBack() {
        _rainActivated = true;
    }

    void Scene::EvolutionSceneRainCompleted() {
        _evolution->animation->SetDelay(0.5f);
        _evolution->animation->enabled = true;
    }

    void Scene::EvolutionSceneEvolutionCompletedCallback() {
        _circlesActivated = true;
    }
}