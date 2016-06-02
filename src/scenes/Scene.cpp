//
// Created by martin on 31.05.2016.
//


#include "Scene.hpp"

Scene::Scene(InputManager *inputManager)
    : _inputManager(inputManager)
{
    Init();
}

Scene::~Scene()
{
    delete _renderManager;
    delete _evolution;
    delete _background;
    delete _startEvolutionTextFirstPart;
    delete _startEvolutionTextSecondPart;
}

void Scene::Init()
{
    _projection = glm::ortho(0.0f, static_cast<GLfloat>(Constants::WINDOW_WIDTH), 0.0f, static_cast<GLfloat>(Constants::WINDOW_HEIGHT));

    glm::vec2 mainQuadPos(Constants::WINDOW_WIDTH / 2, Constants::WINDOW_HEIGHT/ 2 + Constants::WINDOW_HEIGHT / 6);
    PngImage *png_image = new PngImage("_data/github.png");
    PngImage *backgroundImage = new PngImage("data/evolution_background.png");
    PngImage *arrow = new PngImage("data/evolution_arrow.png");
    PngImage *googleImage = new PngImage("_data/google.png");

    TextShader *textShader = new TextShader();
    TextRenderer *textRenderer = new TextRenderer(textShader);
    StaticRenderer *staticRenderer = new StaticRenderer(new StaticShader());
    _renderManager = new RenderManager(textRenderer, staticRenderer);
    Loader *loader = new Loader(staticRenderer->shader->programId);
    _evolution = new EvolutionQuad(loader, mainQuadPos, 0.5f, png_image->bitmap, googleImage->bitmap);
    _background = new EvolutionQuad(loader, glm::vec2(Constants::WINDOW_WIDTH / 2, Constants::WINDOW_HEIGHT / 2), 1.0f, backgroundImage->bitmap, nullptr);
    Quad *arrowQuad = new Quad(loader, glm::vec2(900.0f, 50.0f), 0.04f, arrow->bitmap);

    _renderManager->ProcessProjection(_projection);

    textShader->Start();
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    Font *font = new Font("data/Pokemon.ttf", 48);
    std::string str1 ("What?!");
    Text *text1 = new Text(glm::vec2(55.0f, 190.0f), 1.0f, glm::vec3(0, 0, 0), font);
    std::string str2 ("Your Martin Nemcek");
    _startEvolutionTextFirstPart = new Text(glm::vec2(55.0f, 120.0f), 1.0f, glm::vec3(0, 0, 0), font);
    std::string str3 ("is evolving!");
    _startEvolutionTextSecondPart = new Text(glm::vec2(55.0f, 50.0f), 1.0f, glm::vec3(0, 0, 0), font);

    this->_texts.push_back(text1);
    this->_texts.push_back(_startEvolutionTextFirstPart);
    this->_texts.push_back(_startEvolutionTextSecondPart);

    _evolution->animation = new EvolutionAnimation(*_evolution->bitMap);
    _evolution->animation->enabled = false;
    _evolution->animation->Add(new EvolutionKeyFrame(0.0f, mainQuadPos, 1.0f));
    _evolution->animation->Add(new EvolutionKeyFrame(1.0f, mainQuadPos, .0f, true));
    _evolution->animation->Add(new EvolutionKeyFrame(2.0f, mainQuadPos, 1.0f));

    arrowQuad->animation = new Animation();
    arrowQuad->animation->Add(new KeyFrame(0.0f, arrowQuad->position, 1.0f));
    arrowQuad->animation->Add(new KeyFrame(0.5f, arrowQuad->position, 1.0f));
    arrowQuad->animation->Add(new KeyFrame(0.5f, arrowQuad->position, 0.0f));
    arrowQuad->animation->Add(new KeyFrame(1.0f, arrowQuad->position, 0.0f));

    std::string empty("");
    text1->animation = new TextAnimation(false);
    text1->animation->SetDelay(1.0f);
    text1->animation->Add(new TextKeyFrame(0.0f, text1->position, text1->scale, empty));
    text1->animation->Add(new TextKeyFrame(.65f, text1->position, text1->scale, str1, std::bind(&Scene::WhatTextDrawFinishedCallback, this)));

    _startEvolutionTextFirstPart->animation = new TextAnimation(false);
    _startEvolutionTextFirstPart->animation->enabled = false;
    _startEvolutionTextFirstPart->animation->Add(new TextKeyFrame(0.0f, _startEvolutionTextFirstPart->position, 1.0f, empty));
    _startEvolutionTextFirstPart->animation->Add(new TextKeyFrame(2.0f, _startEvolutionTextFirstPart->position, 1.0f, str2,
                                                                 std::bind(&Scene::StartEvolutionTextFirstPartDrawFinishedCallback, this)));

    _startEvolutionTextSecondPart->animation = new TextAnimation(false);
    _startEvolutionTextSecondPart->animation->enabled = false;
    _startEvolutionTextSecondPart->animation->Add(new TextKeyFrame(0.0f, _startEvolutionTextSecondPart->position, 1.0f, empty));
    _startEvolutionTextSecondPart->animation->Add(new TextKeyFrame(1.5f, _startEvolutionTextSecondPart->position, 1.0f, str3,
                                                                  std::bind(&Scene::StartEvolutionTextDrawFinishedCallback, this)));

    _background->animation = new EvolutionAnimation(*_background->bitMap);
    _background->animation->enabled = false;
    _background->animation->repeat = false;
    _background->animation->Add(new EvolutionKeyFrame(0.0f, _background->position, _background->scale));
    _background->animation->Add(new EvolutionKeyFrame(1.0f, _background->position, _background->scale, glm::vec3(0.0, 0.0, 0.0),
                               std::bind(&Scene::EvolutionSceneFadeCompletedCallback, this)));

    this->_quads.push_back(_background);
    this->_quads.push_back(_evolution);
    this->_quads.push_back(arrowQuad);

    for (Quad *quad : this->_quads)
        _renderManager->ProcessQuad(quad);

    for (Text *text : this->_texts)
        _renderManager->ProcessText(text);
}

void Scene::Animate(float delta)
{
    for (Quad *quad : this->_quads)
        quad->Animate(delta);

    for (Text *text : this->_texts)
        text->Animate(delta);
}

void Scene::Render()
{
//    for (Quad *quad : this->_quads)
//        _renderManager->ProcessQuad(quad);
//
//    for (Text *text : this->_texts)
//        _renderManager->ProcessText(text);

    _renderManager->Prepare();
    _renderManager->Render(this->_projection);
}

void Scene::Update()
{
    if (_inputManager->IsAPressed() && _startEvolutionTextDrawEnabled)
        _startEvolutionTextFirstPart->animation->enabled = true;
}

void Scene::Clean()
{
    this->_renderManager->Clean();
}

void Scene::WhatTextDrawFinishedCallback()
{
    _startEvolutionTextDrawEnabled = true;
}

void Scene::StartEvolutionTextFirstPartDrawFinishedCallback()
{
    _startEvolutionTextSecondPart->animation->enabled = true;
    _startEvolutionTextSecondPart->animation->SetDelay(0.3f);
}

void Scene::StartEvolutionTextDrawFinishedCallback()
{
    _background->animation->enabled = true;
}


void Scene::EvolutionSceneFadeCompletedCallback()
{
    _evolution->animation->enabled = true;
}