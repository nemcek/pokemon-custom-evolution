//
// Created by nemcek on 5/27/18.
//

#include <images/PngImage.hpp>
#include <objects/EvolutionQuad.hpp>
#include "BattleScene.hpp"

namespace Scenes {
    BattleScene::BattleScene() {
        Init();
    }

    BattleScene::~BattleScene() {
        this->_quads.clear();
    }

    void BattleScene::Init() {
        TextShaderPtr textShader = std::make_shared<TextShader>();
        Rendering::TextRendererPtr textRenderer = std::make_shared<Rendering::TextRenderer>(textShader);
        Rendering::StaticRendererPtr staticRenderer = std::make_shared<Rendering::StaticRenderer>(std::make_shared<StaticShader>());
        _renderManager = std::make_shared<Rendering::RenderManager>(textRenderer, staticRenderer);
        _loader = std::make_shared<Loader>(staticRenderer->shader->programId);

        _projection = glm::ortho(0.0f, static_cast<GLfloat>(Constants::WINDOW_WIDTH), 0.0f,
                                 static_cast<GLfloat>(Constants::WINDOW_HEIGHT));
        _renderManager->ProcessProjection(_projection);

        PngImagePtr backgroundImage = std::make_shared<PngImage>("data/evolution_background.png");
        QuadPtr background = std::make_shared<Quad>(_loader, glm::vec2(Constants::WINDOW_WIDTH / 2,
                                                                         Constants::WINDOW_HEIGHT / 2), 1.0f,
                                                      backgroundImage->bitmap);

        PngImagePtr playerImage = std::make_shared<PngImage>("_data/first_evo.png");
        QuadPtr player = std::make_shared<Quad>(_loader, glm::vec2(0.0f, 0.0f), 0.4f, playerImage->bitmap);

        player->animation = std::make_shared<Animation>(false);
        player->animation->Add(std::make_shared<KeyFrame>(0.0f, glm::vec2(0.0f, 400), 1.0f));
        player->animation->Add(std::make_shared<KeyFrame>(1.5f, glm::vec2(240, 400), 1.0f));

        PngImagePtr enemyImage = std::make_shared<PngImage>("_data/first_evo.png");
        QuadPtr enemy = std::make_shared<Quad>(_loader, glm::vec2(0.0f, 0.0f), 0.4f, enemyImage->bitmap);

        enemy->animation = std::make_shared<Animation>(false);
        enemy->animation->Add(std::make_shared<KeyFrame>(0.0f, glm::vec2(960, 800), 1.0f));
        enemy->animation->Add(std::make_shared<KeyFrame>(1.5f, glm::vec2(720, 800), 1.0f));

        this->_quads.push_back(background);
        this->_quads.push_back(player);
        this->_quads.push_back(enemy);

        for (QuadPtr quad : this->_quads)
            _renderManager->ProcessQuad(quad);
    }

    void BattleScene::Animate(float delta) {
        for (QuadPtr quad : this->_quads) {
            quad->Animate(delta);
        }
    }

    void BattleScene::Update(float delta) {
        for (QuadPtr quad : this->_quads) {
            quad->Update(delta);
        }
    }

    void BattleScene::Render() {
        _renderManager->Prepare();
        _renderManager->Render(this->_projection);
    }
}