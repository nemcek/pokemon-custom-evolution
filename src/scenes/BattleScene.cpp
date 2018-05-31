//
// Created by nemcek on 5/27/18.
//

#include <images/PngImage.hpp>
#include <objects/EvolutionQuad.hpp>
#include <engine/Transformations.hpp>
#include <engine/animation/keyframes/TextKeyFrame.hpp>
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

        PngImagePtr backgroundImage = std::make_shared<PngImage>("data/battle_scene.png");
        QuadPtr background = std::make_shared<Quad>(_loader, glm::vec2(Constants::WINDOW_WIDTH / 2,
                                                                         Constants::WINDOW_HEIGHT / 2), 1.0f,
                                                      backgroundImage->bitmap);

        PngImagePtr playerImage = std::make_shared<PngImage>("_data/first_evo.png");
        QuadPtr player = std::make_shared<Quad>(_loader, glm::vec2(0.0f, 0.0f), 0.4f, playerImage->bitmap);

        player->animation = std::make_shared<Animation>(false);
        player->animation->Add(std::make_shared<KeyFrame>(0.0f, glm::vec2(0.0f, 400), 1.0f));
        player->animation->Add(std::make_shared<KeyFrame>(1.5f, glm::vec2(240, 400), 1.0f));

        PngImagePtr enemyGuiImage = std::make_shared<PngImage>("data/pokemon_gui_enemy.png");
        QuadPtr enemyGui = std::make_shared<Quad>(_loader, glm::vec2(Constants::WINDOW_WIDTH * 0.25f, Constants::WINDOW_HEIGHT * 0.83f), 0.4f, 0.13f, enemyGuiImage->bitmap);

        BitMapPtr blackBitmap = std::make_shared<BitMap>(Constants::WINDOW_WIDTH * 0.25f, Constants::WINDOW_HEIGHT * 0.25f, Pixel{85, 85, 85, 255});
        QuadPtr enemyGuiBackgroud = std::make_shared<Quad>(_loader, glm::vec2(Constants::WINDOW_WIDTH * 0.25f, Constants::WINDOW_HEIGHT * 0.82f), 0.3f, 0.05f, blackBitmap);
        PngImagePtr enemyHealthbarImage = std::make_shared<PngImage>("data/pokemon_gui_healthbar.png");
        QuadPtr enemyHealthbar = std::make_shared<Quad>(_loader, glm::vec2(Constants::WINDOW_WIDTH * 0.3f, Constants::WINDOW_HEIGHT * 0.81f), 0.2f, 0.02f, enemyHealthbarImage->bitmap);
        enemyHealthbar->animation = std::make_shared<Animation>(false);
        enemyHealthbar->animation->Add(std::make_shared<KeyFrame>(0.0f, enemyHealthbar->position, 1.0f));
        enemyHealthbar->animation->Add(std::make_shared<KeyFrame>(2.0f, glm::vec2(enemyHealthbar->position.x - enemyHealthbar->bitMap->width * 0.09f, enemyHealthbar->position.y), glm::vec2(1.0f, 0.7f)));
        enemyHealthbar->animation->Add(std::make_shared<KeyFrame>(4.0f, glm::vec2(enemyHealthbar->position.x - enemyHealthbar->bitMap->width * 0.305f, enemyHealthbar->position.y), glm::vec2(1.0f, 0.0f)));

        PngImagePtr playerGuiImage = std::make_shared<PngImage>("data/pokemon_gui_player.png");
        QuadPtr playerGui = std::make_shared<Quad>(_loader, glm::vec2(Constants::WINDOW_WIDTH * 0.75f, Constants::WINDOW_HEIGHT * 0.4f), 0.47f, 0.2f, playerGuiImage->bitmap);
        QuadPtr playerGuiBackgroud = std::make_shared<Quad>(_loader, glm::vec2(Constants::WINDOW_WIDTH * 0.82f, Constants::WINDOW_HEIGHT * 0.4f), 0.3f, 0.05f, blackBitmap);
        QuadPtr playerHealthbar = std::make_shared<Quad>(_loader, glm::vec2(Constants::WINDOW_WIDTH * 0.84f, Constants::WINDOW_HEIGHT * 0.4f), 0.225f, 0.02f, enemyHealthbarImage->bitmap);

        playerHealthbar->animation = std::make_shared<Animation>(false);
        playerHealthbar->animation->Add(std::make_shared<KeyFrame>(0.0f, playerHealthbar->position, 1.0f));
        playerHealthbar->animation->Add(std::make_shared<KeyFrame>(2.0f, glm::vec2(playerHealthbar->position.x - playerHealthbar->bitMap->width * 0.03f, playerHealthbar->position.y), glm::vec2(1.0f, 0.9f)));

        PngImagePtr enemyImage = std::make_shared<PngImage>("_data/first_evo.png");
        QuadPtr enemy = std::make_shared<Quad>(_loader, glm::vec2(0.0f, 0.0f), 0.4f, enemyImage->bitmap);

        enemy->animation = std::make_shared<Animation>(false);
        enemy->animation->Add(std::make_shared<KeyFrame>(0.0f, glm::vec2(960, 800), 1.0f));
        enemy->animation->Add(std::make_shared<KeyFrame>(1.5f, glm::vec2(720, 800), 1.0f));

        textShader->Start();
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        FontPtr font = std::make_shared<Font>("data/Pokemon.ttf", 48);
        TextPtr enemyNameText = std::make_shared<Text>(std::string("FIIT"), glm::vec2(Constants::WINDOW_WIDTH * 0.08f, Constants::WINDOW_HEIGHT * 0.835f), 0.7f, glm::vec3(0, 0, 0), font);
        TextPtr enemyLevelText = std::make_shared<Text>(std::string("Lv:"), glm::vec2(Constants::WINDOW_WIDTH * 0.25f, Constants::WINDOW_HEIGHT * 0.835f), 0.4f, glm::vec3(0, 0, 0), font);
        TextPtr enemyLevelValueText = std::make_shared<Text>(std::string("100"), glm::vec2(Constants::WINDOW_WIDTH * 0.31f, Constants::WINDOW_HEIGHT * 0.835f), 0.6f, glm::vec3(0, 0, 0), font);
        TextPtr playerNameText = std::make_shared<Text>(std::string("Bc.Nemcek"), glm::vec2(Constants::WINDOW_WIDTH * 0.575f, Constants::WINDOW_HEIGHT * 0.44f), 0.6f, glm::vec3(0, 0, 0), font);
        TextPtr playerLevelText = std::make_shared<Text>(std::string("Lv:"), glm::vec2(Constants::WINDOW_WIDTH * 0.86f, Constants::WINDOW_HEIGHT * 0.44f), 0.3f, glm::vec3(0, 0, 0), font);
        TextPtr playerLevelValueText = std::make_shared<Text>(std::string("99"), glm::vec2(Constants::WINDOW_WIDTH * 0.905f, Constants::WINDOW_HEIGHT * 0.44f), 0.5f, glm::vec3(0, 0, 0), font);
        TextPtr playerHealthActualText = std::make_shared<Text>(std::string("250"), glm::vec2(Constants::WINDOW_WIDTH * 0.69f, Constants::WINDOW_HEIGHT * 0.34f), 0.6f, glm::vec3(0, 0, 0), font);
        TextPtr playerHealthMaxText = std::make_shared<Text>(std::string("/ 250"), glm::vec2(Constants::WINDOW_WIDTH * 0.80f, Constants::WINDOW_HEIGHT * 0.34f), 0.6f, glm::vec3(0, 0, 0), font);

        playerHealthActualText->animation = std::make_shared<TextAnimation>(false);
        playerHealthActualText->animation->Add(std::make_shared<TextKeyFrame>(0.0f, playerHealthActualText->position, playerHealthActualText->scale, playerHealthActualText->text));
        playerHealthActualText->animation->Add(std::make_shared<TextKeyFrame>(.5f, playerHealthActualText->position, playerHealthActualText->scale, std::string("248")));
        playerHealthActualText->animation->Add(std::make_shared<TextKeyFrame>(1.0f, playerHealthActualText->position, playerHealthActualText->scale, std::string("246")));
        playerHealthActualText->animation->Add(std::make_shared<TextKeyFrame>(1.5f, playerHealthActualText->position, playerHealthActualText->scale, std::string("244")));
        playerHealthActualText->animation->Add(std::make_shared<TextKeyFrame>(2.0f, playerHealthActualText->position, playerHealthActualText->scale, std::string("242")));

        this->_quads.push_back(background);
        this->_quads.push_back(player);
        this->_quads.push_back(enemy);
        this->_quads.push_back(enemyGuiBackgroud);
        this->_quads.push_back(enemyHealthbar);
        this->_quads.push_back(enemyGui);
        this->_quads.push_back(playerGuiBackgroud);
        this->_quads.push_back(playerHealthbar);
        this->_quads.push_back(playerGui);

        this->_texts.push_back(enemyNameText);
        this->_texts.push_back(enemyLevelText);
        this->_texts.push_back(enemyLevelValueText);
        this->_texts.push_back(playerNameText);
        this->_texts.push_back(playerLevelText);
        this->_texts.push_back(playerLevelValueText);
        this->_texts.push_back(playerHealthActualText);
        this->_texts.push_back(playerHealthMaxText);

        for (QuadPtr quad : this->_quads)
            _renderManager->ProcessQuad(quad);

        for (TextPtr text : this->_texts)
            _renderManager->ProcessText(text);
    }

    void BattleScene::Animate(float delta) {
        for (QuadPtr quad : this->_quads) {
            quad->Animate(delta);
        }

        for (TextPtr text : this->_texts) {
            text->Animate(delta);
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