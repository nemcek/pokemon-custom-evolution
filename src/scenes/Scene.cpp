//
// Created by martin on 31.05.2016.
//


#include "Scene.hpp"

Scene::Scene(InputManager *inputManager)
    : inputManager(inputManager)
{
    Init();
}

void Scene::Init()
{
    projection = glm::ortho(0.0f, static_cast<GLfloat>(Constants::WINDOW_WIDTH), 0.0f, static_cast<GLfloat>(Constants::WINDOW_HEIGHT));

    glm::vec2 mainQuadPos(Constants::WINDOW_WIDTH / 2, Constants::WINDOW_HEIGHT/ 2 + Constants::WINDOW_HEIGHT / 6);
    PngImage *png_image = new PngImage("_data/github.png");
    PngImage *backgroundImage = new PngImage("data/evolution_background.png");
    PngImage *arrow = new PngImage("data/evolution_arrow.png");
    PngImage *googleImage = new PngImage("_data/google.png");

    TextShader *textShader = new TextShader();
    TextRenderer *textRenderer = new TextRenderer(textShader);
    StaticRenderer *staticRenderer = new StaticRenderer(new StaticShader());
    renderManager = new RenderManager(textRenderer, staticRenderer);
    Loader *loader = new Loader(staticRenderer->shader->programId);
    evolution = new EvolutionQuad(loader, mainQuadPos, 0.5f, png_image->bitmap, googleImage->bitmap);
    background = new EvolutionQuad(loader, glm::vec2(Constants::WINDOW_WIDTH / 2, Constants::WINDOW_HEIGHT / 2), 1.0f, backgroundImage->bitmap, nullptr);
    Quad *arrowQuad = new Quad(loader, glm::vec2(900.0f, 50.0f), 0.04f, arrow->bitmap);

    renderManager->ProcessProjection(projection);

    textShader->Start();
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    Font *font = new Font("data/Pokemon.ttf", 48);
    std::string str1 ("What?!");
    Text *text1 = new Text(glm::vec2(55.0f, 190.0f), 1.0f, glm::vec3(0, 0, 0), font);
    std::string str2 ("Your Martin Nemcek");
    startEvolutionTextFirstPart = new Text(glm::vec2(55.0f, 120.0f), 1.0f, glm::vec3(0, 0, 0), font);
    std::string str3 ("is evolving!");
    startEvolutionTextSecondPart = new Text(glm::vec2(55.0f, 50.0f), 1.0f, glm::vec3(0, 0, 0), font);

    this->texts.push_back(text1);
    this->texts.push_back(startEvolutionTextFirstPart);
    this->texts.push_back(startEvolutionTextSecondPart);

    evolution->animation = new EvolutionAnimation(*evolution->bitMap);
    evolution->animation->enabled = false;
    evolution->animation->Add(new EvolutionKeyFrame(0.0f, mainQuadPos, 1.0f));
    evolution->animation->Add(new EvolutionKeyFrame(1.0f, mainQuadPos, .0f, true));
    evolution->animation->Add(new EvolutionKeyFrame(2.0f, mainQuadPos, 1.0f));

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

    startEvolutionTextFirstPart->animation = new TextAnimation(false);
    startEvolutionTextFirstPart->animation->enabled = false;
    startEvolutionTextFirstPart->animation->Add(new TextKeyFrame(0.0f, startEvolutionTextFirstPart->position, 1.0f, empty));
    startEvolutionTextFirstPart->animation->Add(new TextKeyFrame(2.0f, startEvolutionTextFirstPart->position, 1.0f, str2,
                                                                 std::bind(&Scene::StartEvolutionTextFirstPartDrawFinishedCallback, this)));

    startEvolutionTextSecondPart->animation = new TextAnimation(false);
    startEvolutionTextSecondPart->animation->enabled = false;
    startEvolutionTextSecondPart->animation->Add(new TextKeyFrame(0.0f, startEvolutionTextSecondPart->position, 1.0f, empty));
    startEvolutionTextSecondPart->animation->Add(new TextKeyFrame(1.5f, startEvolutionTextSecondPart->position, 1.0f, str3,
                                                                  std::bind(&Scene::StartEvolutionTextDrawFinishedCallback, this)));

    background->animation = new EvolutionAnimation(*background->bitMap);
    background->animation->enabled = false;
    background->animation->repeat = false;
    background->animation->Add(new EvolutionKeyFrame(0.0f, background->position, background->scale));
    background->animation->Add(new EvolutionKeyFrame(1.0f, background->position, background->scale, glm::vec3(0.0, 0.0, 0.0),
                               std::bind(&Scene::EvolutionSceneFadeCompletedCallback, this)));

    this->quads.push_back(background);
    this->quads.push_back(evolution);
    this->quads.push_back(arrowQuad);

    for (Quad *quad : this->quads)
        renderManager->ProcessQuad(quad);

    for (Text *text : this->texts)
        renderManager->ProcessText(text);
}

void Scene::Animate(float delta)
{
    for (Quad *quad : this->quads)
        quad->Animate(delta);

    for (Text *text : this->texts)
        text->Animate(delta);
}

void Scene::Render()
{
//    for (Quad *quad : this->quads)
//        renderManager->ProcessQuad(quad);
//
//    for (Text *text : this->texts)
//        renderManager->ProcessText(text);

    renderManager->Prepare();
    renderManager->Render(this->projection);
}

void Scene::Update()
{
    if (inputManager->IsAPressed() && startEvolutionTextDrawEnabled)
        startEvolutionTextFirstPart->animation->enabled = true;
}

void Scene::Clean()
{
    this->renderManager->Clean();
}

void Scene::WhatTextDrawFinishedCallback()
{
    startEvolutionTextDrawEnabled = true;
}

void Scene::StartEvolutionTextFirstPartDrawFinishedCallback()
{
    startEvolutionTextSecondPart->animation->enabled = true;
    startEvolutionTextSecondPart->animation->SetDelay(0.3f);
}

void Scene::StartEvolutionTextDrawFinishedCallback()
{
    background->animation->enabled = true;
}


void Scene::EvolutionSceneFadeCompletedCallback()
{
    evolution->animation->enabled = true;
}