//
// Created by nemcek on 5/27/18.
//

#include <images/PngImage.hpp>
#include <objects/EvolutionQuad.hpp>
#include <engine/Transformations.hpp>
#include <engine/animation/keyframes/TextKeyFrame.hpp>
#include <objects/BattleQuad.hpp>
#include <csignal>
#include "BattleScene.hpp"

namespace Scenes {
    BattleScene::BattleScene(InputManagerPtr inputManager) : _inputManager(inputManager) {
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
        _player = std::make_shared<Quad>(_loader, glm::vec2(-1000.0f, -1000.0f), 0.4f, playerImage->bitmap);

        _player->animation = std::make_shared<Animation>(false);
        _player->animation->Add(std::make_shared<KeyFrame>(0.0f, glm::vec2(0.0f, 400), 1.0f));
        _player->animation->Add(std::make_shared<KeyFrame>(1.5f, glm::vec2(240, 400), 1.0f));

        PngImagePtr enemyGuiImage = std::make_shared<PngImage>("data/pokemon_gui_enemy.png");
        QuadPtr enemyGui = std::make_shared<Quad>(_loader, glm::vec2(Constants::WINDOW_WIDTH * 0.25f, Constants::WINDOW_HEIGHT * 0.83f), 0.4f, 0.13f, enemyGuiImage->bitmap);

        BitMapPtr blackBitmap = std::make_shared<BitMap>(Constants::WINDOW_WIDTH * 0.25f, Constants::WINDOW_HEIGHT * 0.25f, Pixel{85, 85, 85, 255});
        QuadPtr enemyGuiBackgroud = std::make_shared<Quad>(_loader, glm::vec2(Constants::WINDOW_WIDTH * 0.25f, Constants::WINDOW_HEIGHT * 0.82f), 0.3f, 0.05f, blackBitmap);
        PngImagePtr enemyHealthbarImage = std::make_shared<PngImage>("data/pokemon_gui_healthbar.png");
        _enemyHealthbar = std::make_shared<Quad>(_loader, glm::vec2(Constants::WINDOW_WIDTH * 0.3f, Constants::WINDOW_HEIGHT * 0.81f), 0.2f, 0.02f, enemyHealthbarImage->bitmap);

        PngImagePtr playerGuiImage = std::make_shared<PngImage>("data/pokemon_gui_player.png");
        QuadPtr playerGui = std::make_shared<Quad>(_loader, glm::vec2(Constants::WINDOW_WIDTH * 0.75f, Constants::WINDOW_HEIGHT * 0.4f), 0.47f, 0.2f, playerGuiImage->bitmap);
        QuadPtr playerGuiBackgroud = std::make_shared<Quad>(_loader, glm::vec2(Constants::WINDOW_WIDTH * 0.82f, Constants::WINDOW_HEIGHT * 0.4f), 0.3f, 0.05f, blackBitmap);
        _playerHealthbar = std::make_shared<Quad>(_loader, glm::vec2(Constants::WINDOW_WIDTH * 0.84f, Constants::WINDOW_HEIGHT * 0.4f), 0.225f, 0.02f, enemyHealthbarImage->bitmap);

        PngImagePtr enemyImage = std::make_shared<PngImage>("_data/first_evo.png");
        _enemy = std::make_shared<BattleQuad>(_loader, glm::vec2(-1000, -1000), 0.4f, enemyImage->bitmap);

        _enemy->animation = std::make_shared<BattleAnimation>(_enemy->bitMap);
        _enemy->animation->Add(std::make_shared<BattleKeyFrame>(0.0f, glm::vec2(960, 800), 1.0f, 100.0f));
        _enemy->animation->Add(std::make_shared<BattleKeyFrame>(1.5f, glm::vec2(720, 800), 1.0f, 100.0f));
        _enemy->animation->repeat = false;

        PngImagePtr guiMenuImage = std::make_shared<PngImage>("data/pokemon_gui_menu.png");
        _guiMenu = std::make_shared<Quad>(_loader, glm::vec2(Constants::WINDOW_WIDTH * 0.775f, Constants::WINDOW_HEIGHT * 0.1475f), 0.45f, 0.3f, guiMenuImage->bitmap);

        PngImagePtr guiSelectorImage = std::make_shared<PngImage>("data/pokemon_gui_selector.png");
        _guiSelector = std::make_shared<Quad>(_loader, glm::vec2(Constants::WINDOW_WIDTH * 0.695f, Constants::WINDOW_HEIGHT * 0.197f), 0.22f, 0.06f, guiSelectorImage->bitmap);

        _guiSelector2 = std::make_shared<Quad>(_loader, glm::vec2(Constants::WINDOW_WIDTH * 0.21f, Constants::WINDOW_HEIGHT * 0.197f), 0.35f, 0.06f, guiSelectorImage->bitmap);
        _guiSelector3 = std::make_shared<Quad>(_loader, glm::vec2(Constants::WINDOW_WIDTH * 0.21f, Constants::WINDOW_HEIGHT * 0.0975f), 0.35f, 0.06f, guiSelectorImage->bitmap);

        PngImagePtr guiBattleMenuImage = std::make_shared<PngImage>("data/pokemon_gui_battle_menu.png");
        _guiBattleMenu = std::make_shared<Quad>(_loader, glm::vec2(Constants::WINDOW_WIDTH * 0.5f, Constants::WINDOW_HEIGHT * 0.1475f), 1.0f, 0.3f, guiBattleMenuImage->bitmap);

        PngImagePtr playerExpImage = std::make_shared<PngImage>("data/pokemon_gui_expbar.png");
        _playerExpbar = std::make_shared<Quad>(_loader, glm::vec2(Constants::WINDOW_WIDTH * 0.677f, Constants::WINDOW_HEIGHT * 0.3115f), 0.04f, 0.012f, playerExpImage->bitmap);

        PngImagePtr playerAttack1Image = std::make_shared<PngImage>("data/player_attack1.png");
        _playerAttack1 = std::make_shared<Quad>(_loader, glm::vec2(Constants::WINDOW_WIDTH * 0.4f, Constants::WINDOW_HEIGHT * 0.5f), 0.2f, playerAttack1Image->bitmap);

        PngImagePtr playerAttack2Image = std::make_shared<PngImage>("data/player_attack2.png");
        _playerAttack2 = std::make_shared<Quad>(_loader, glm::vec2(Constants::WINDOW_WIDTH * 0.4f, Constants::WINDOW_HEIGHT * 0.5f), 0.2f, playerAttack2Image->bitmap);

        PngImagePtr enemyAttackImage = std::make_shared<PngImage>("data/enemy_attack1.png");
        _enemyAttack = std::make_shared<Quad>(_loader, glm::vec2(Constants::WINDOW_WIDTH * 0.7f, Constants::WINDOW_HEIGHT * 0.7f), 0.2f, enemyAttackImage->bitmap);

        PngImagePtr guiMenuLevelUp = std::make_shared<PngImage>("data/pokemon_gui_level_up.png");
        _guiLevelUp = std::make_shared<Quad>(_loader, glm::vec2(Constants::WINDOW_WIDTH * 0.775f, Constants::WINDOW_HEIGHT * 0.5f), 0.45f, 0.5f, guiMenuLevelUp->bitmap);

        BitMapPtr foregroundBitmap = std::make_shared<BitMap>(960, 960, Pixel{0, 0, 0, 0});
        _foreground = std::make_shared<EvolutionQuad>(_loader, glm::vec2(Constants::WINDOW_WIDTH / 2, Constants::WINDOW_HEIGHT  / 2), 1.0f, foregroundBitmap, foregroundBitmap);

        textShader->Start();
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        FontPtr font = std::make_shared<Font>("data/Pokemon.ttf", 48);
        TextPtr enemyNameText = std::make_shared<Text>(std::string("FIIT"), glm::vec2(Constants::WINDOW_WIDTH * 0.08f, Constants::WINDOW_HEIGHT * 0.835f), 0.7f, glm::vec3(0, 0, 0), font);
        TextPtr enemyLevelText = std::make_shared<Text>(std::string("Lv:"), glm::vec2(Constants::WINDOW_WIDTH * 0.25f, Constants::WINDOW_HEIGHT * 0.835f), 0.4f, glm::vec3(0, 0, 0), font);
        TextPtr enemyLevelValueText = std::make_shared<Text>(std::string("100"), glm::vec2(Constants::WINDOW_WIDTH * 0.31f, Constants::WINDOW_HEIGHT * 0.835f), 0.6f, glm::vec3(0, 0, 0), font);
        _playerNameText = std::make_shared<Text>(std::string("Bc.Nemcek"), glm::vec2(Constants::WINDOW_WIDTH * 0.575f, Constants::WINDOW_HEIGHT * 0.44f), 0.6f, glm::vec3(0, 0, 0), font);
        _playerLevelText = std::make_shared<Text>(std::string("Lv:"), glm::vec2(Constants::WINDOW_WIDTH * 0.86f, Constants::WINDOW_HEIGHT * 0.44f), 0.3f, glm::vec3(0, 0, 0), font);
        _playerLevelValueText = std::make_shared<Text>(std::string("90"), glm::vec2(Constants::WINDOW_WIDTH * 0.905f, Constants::WINDOW_HEIGHT * 0.44f), 0.5f, glm::vec3(0, 0, 0), font);
        _playerHealthActualText = std::make_shared<Text>(std::string("250"), glm::vec2(Constants::WINDOW_WIDTH * 0.69f, Constants::WINDOW_HEIGHT * 0.34f), 0.6f, glm::vec3(0, 0, 0), font);
        _playerHealthMaxText = std::make_shared<Text>(std::string("/ 250"), glm::vec2(Constants::WINDOW_WIDTH * 0.80f, Constants::WINDOW_HEIGHT * 0.34f), 0.6f, glm::vec3(0, 0, 0), font);
        _menuPart1Text = std::make_shared<Text>(std::string("FIGHT BAG"), glm::vec2(Constants::WINDOW_WIDTH * 0.6f, Constants::WINDOW_HEIGHT * 0.18f), 0.8f, glm::vec3(0, 0, 0), font);
        _menuPart2Text = std::make_shared<Text>(std::string("PKMN  RUN"), glm::vec2(Constants::WINDOW_WIDTH * 0.6f, Constants::WINDOW_HEIGHT * 0.08f), 0.8f, glm::vec3(0, 0, 0), font);
        _battleMenuPart1Text = std::make_shared<Text>(std::string("DIPLOMKA  REST"), glm::vec2(Constants::WINDOW_WIDTH * 0.05f, Constants::WINDOW_HEIGHT * 0.18f), 0.8f, glm::vec3(0, 0, 0), font);
        _battleMenuPart2Text = std::make_shared<Text>(std::string("OBHAJOBA  FART"), glm::vec2(Constants::WINDOW_WIDTH * 0.05f, Constants::WINDOW_HEIGHT * 0.08f), 0.8f, glm::vec3(0, 0, 0), font);
        _battleMenuPart3Text = std::make_shared<Text>(std::string("PP 20/20"), glm::vec2(Constants::WINDOW_WIDTH * 0.7f, Constants::WINDOW_HEIGHT * 0.18f), 0.7f, glm::vec3(0, 0, 0), font);
        _battleMenuPart4Text = std::make_shared<Text>(std::string("NORMAL"), glm::vec2(Constants::WINDOW_WIDTH * 0.7f, Constants::WINDOW_HEIGHT * 0.08f), 0.8f, glm::vec3(0, 0, 0), font);
        _battleStartText1 = std::make_shared<Text>(glm::vec2(Constants::WINDOW_WIDTH * 0.05f, Constants::WINDOW_HEIGHT * 0.18f), 1.0f, glm::vec3(0, 0, 0), font);
        _battleStartText2 = std::make_shared<Text>(glm::vec2(Constants::WINDOW_WIDTH * 0.05f, Constants::WINDOW_HEIGHT * 0.08f), 1.0f, glm::vec3(0, 0, 0), font);
        _battleShoudlText1 = std::make_shared<Text>(glm::vec2(Constants::WINDOW_WIDTH * 0.05f, Constants::WINDOW_HEIGHT * 0.18f), 1.0f, glm::vec3(0, 0, 0), font);
        _battleShoudlText2 = std::make_shared<Text>(glm::vec2(Constants::WINDOW_WIDTH * 0.05f, Constants::WINDOW_HEIGHT * 0.08f), 1.0f, glm::vec3(0, 0, 0), font);
        _battleShoudlText3 = std::make_shared<Text>(glm::vec2(Constants::WINDOW_WIDTH * 0.05f, Constants::WINDOW_HEIGHT * 0.18f), 1.0f, glm::vec3(0, 0, 0), font);
        _battleShoudlText4 = std::make_shared<Text>(glm::vec2(Constants::WINDOW_WIDTH * 0.05f, Constants::WINDOW_HEIGHT * 0.08f), 1.0f, glm::vec3(0, 0, 0), font);
        _attack1Text1 = std::make_shared<Text>(glm::vec2(Constants::WINDOW_WIDTH * 0.05f, Constants::WINDOW_HEIGHT * 0.18f), 1.0f, glm::vec3(0, 0, 0), font);
        _attack1Text2 = std::make_shared<Text>(glm::vec2(Constants::WINDOW_WIDTH * 0.05f, Constants::WINDOW_HEIGHT * 0.08f), 1.0f, glm::vec3(0, 0, 0), font);
        _attack2Text1 = std::make_shared<Text>(glm::vec2(Constants::WINDOW_WIDTH * 0.05f, Constants::WINDOW_HEIGHT * 0.18f), 1.0f, glm::vec3(0, 0, 0), font);
        _attack2Text2 = std::make_shared<Text>(glm::vec2(Constants::WINDOW_WIDTH * 0.05f, Constants::WINDOW_HEIGHT * 0.08f), 1.0f, glm::vec3(0, 0, 0), font);
        _attack3Text1 = std::make_shared<Text>(glm::vec2(Constants::WINDOW_WIDTH * 0.05f, Constants::WINDOW_HEIGHT * 0.18f), 1.0f, glm::vec3(0, 0, 0), font);
        _attack3Text2 = std::make_shared<Text>(glm::vec2(Constants::WINDOW_WIDTH * 0.05f, Constants::WINDOW_HEIGHT * 0.08f), 1.0f, glm::vec3(0, 0, 0), font);
        _notVeryEffictiveText1 = std::make_shared<Text>(glm::vec2(Constants::WINDOW_WIDTH * 0.05f, Constants::WINDOW_HEIGHT * 0.18f), 1.0f, glm::vec3(0, 0, 0), font);
        _notVeryEffictiveText2 = std::make_shared<Text>(glm::vec2(Constants::WINDOW_WIDTH * 0.05f, Constants::WINDOW_HEIGHT * 0.08f), 1.0f, glm::vec3(0, 0, 0), font);
        _supperEffectiveText = std::make_shared<Text>(glm::vec2(Constants::WINDOW_WIDTH * 0.05f, Constants::WINDOW_HEIGHT * 0.18f), 1.0f, glm::vec3(0, 0, 0), font);
        _faintedText = std::make_shared<Text>(glm::vec2(Constants::WINDOW_WIDTH * 0.05f, Constants::WINDOW_HEIGHT * 0.18f), 1.0f, glm::vec3(0, 0, 0), font);
        _grewText1 = std::make_shared<Text>(glm::vec2(Constants::WINDOW_WIDTH * 0.05f, Constants::WINDOW_HEIGHT * 0.18f), 1.0f, glm::vec3(0, 0, 0), font);
        _grewText2 = std::make_shared<Text>(glm::vec2(Constants::WINDOW_WIDTH * 0.05f, Constants::WINDOW_HEIGHT * 0.08f), 1.0f, glm::vec3(0, 0, 0), font);

        _levelUpText1 = std::make_shared<Text>(std::string("TIME  +100"), glm::vec2(Constants::WINDOW_WIDTH * 0.575f, Constants::WINDOW_HEIGHT * 0.675f), 0.8f, glm::vec3(0,0,0), font);
        _levelUpText2 = std::make_shared<Text>(std::string("ENERGY +17"), glm::vec2(Constants::WINDOW_WIDTH * 0.575f, Constants::WINDOW_HEIGHT * 0.6f), 0.8f, glm::vec3(0,0,0), font);
        _levelUpText3 = std::make_shared<Text>(std::string("SKILLS +12"), glm::vec2(Constants::WINDOW_WIDTH * 0.575f, Constants::WINDOW_HEIGHT * 0.525f), 0.8f, glm::vec3(0,0,0), font);
        _levelUpText4 = std::make_shared<Text>(std::string("CHARM  +90"), glm::vec2(Constants::WINDOW_WIDTH * 0.575f, Constants::WINDOW_HEIGHT * 0.45f), 0.8f, glm::vec3(0,0,0), font);
        _levelUpText5 = std::make_shared<Text>(std::string("SOCIAL -21"), glm::vec2(Constants::WINDOW_WIDTH * 0.575f, Constants::WINDOW_HEIGHT * 0.375f), 0.8f, glm::vec3(0,0,0), font);
        _levelUpText6 = std::make_shared<Text>(std::string("INTLCT  +9"), glm::vec2(Constants::WINDOW_WIDTH * 0.575f, Constants::WINDOW_HEIGHT * 0.3f), 0.8f, glm::vec3(0,0,0), font);

        _battleStartText1->animation = std::make_shared<TextAnimation>(false);
        _battleStartText1->animation->Add(std::make_shared<TextKeyFrame>(0.0f, _battleStartText1->position, 1.0f, std::string("")));
        _battleStartText1->animation->Add(std::make_shared<TextKeyFrame>(0.5f, _battleStartText1->position, 1.0f, std::string("FIIT would like"),
                                                                         std::bind(&BattleScene::BattleStartTextFirtPartFinishedCallback, this)));
        _battleStartText1->animation->SetDelay(2.0);

        _battleStartText2->animation = std::make_shared<TextAnimation>(false);
        _battleStartText2->animation->enabled = false;
        _battleStartText2->animation->Add(std::make_shared<TextKeyFrame>(0.0f, _battleStartText2->position, 1.0f, std::string("")));
        _battleStartText2->animation->Add(std::make_shared<TextKeyFrame>(0.5f, _battleStartText2->position, 1.0f, std::string("to battle!")));
        _battleStartText2->animation->Add(std::make_shared<TextKeyFrame>(1.3f, _battleStartText2->position, 1.0f, std::string("to battle!"),
                                                                         std::bind(&BattleScene::BattleStartTextFinishedCallback, this)));
        _battleStartText2->animation->SetDelay(0.2f);

        _menuPart1Text->StopRendering();
        _menuPart2Text->StopRendering();

        _guiMenu->renderStoped = true;

        _guiSelector->animation = std::make_shared<Animation>(true);
        _guiSelector->animation->enabled = false;
        _guiSelector->animation->Add(std::make_shared<KeyFrame>(0.0f, _guiSelector->position, 1.0f));
        _guiSelector->animation->Add(std::make_shared<KeyFrame>(0.7f, _guiSelector->position, 1.0f));
        _guiSelector->animation->Add(std::make_shared<KeyFrame>(0.7f, _guiSelector->position, 0.0f));
        _guiSelector->animation->Add(std::make_shared<KeyFrame>(1.0f, _guiSelector->position, 0.0f));
        _guiSelector->renderStoped = true;

        _battleShoudlText1->animation = std::make_shared<TextAnimation>(false);
        _battleShoudlText1->animation->enabled = false;
        _battleShoudlText1->animation->Add(std::make_shared<TextKeyFrame>(0.0f, _battleShoudlText1->position, 0.8f, std::string("")));
        _battleShoudlText1->animation->Add(std::make_shared<TextKeyFrame>(0.5f, _battleShoudlText1->position, 0.8f, std::string("What should"),
                                                                         std::bind(&BattleScene::BattleShouldTextFirstPartFinishedCallback, this)));

        _battleShoudlText2->animation = std::make_shared<TextAnimation>(false);
        _battleShoudlText2->animation->enabled = false;
        _battleShoudlText2->animation->SetDelay(0.2f);
        _battleShoudlText2->animation->Add(std::make_shared<TextKeyFrame>(0.0f, _battleShoudlText2->position, 0.7f, std::string("")));
        _battleShoudlText2->animation->Add(std::make_shared<TextKeyFrame>(0.7f, _battleShoudlText2->position, 0.7f, std::string("Bc.Nemcek do?")));
        _battleShoudlText2->animation->Add(std::make_shared<TextKeyFrame>(1.7f, _battleShoudlText2->position, 0.7f, std::string("Bc.Nemcek do?"),
                                                                          std::bind(&BattleScene::BattleShouldTextFinishedCallback, this)));

        _battleShoudlText3->animation = std::make_shared<TextAnimation>(false);
        _battleShoudlText3->animation->enabled = false;
        _battleShoudlText3->animation->Add(std::make_shared<TextKeyFrame>(0.0f, _battleShoudlText3->position, 0.8f, std::string("")));
        _battleShoudlText3->animation->Add(std::make_shared<TextKeyFrame>(0.5f, _battleShoudlText3->position, 0.8f, std::string("What should"),
                                                                          std::bind(&BattleScene::BattleShouldText3FinishedCallback, this)));

        _battleShoudlText4->animation = std::make_shared<TextAnimation>(false);
        _battleShoudlText4->animation->enabled = false;
        _battleShoudlText4->animation->SetDelay(0.2f);
        _battleShoudlText4->animation->Add(std::make_shared<TextKeyFrame>(0.0f, _battleShoudlText4->position, 0.7f, std::string("")));
        _battleShoudlText4->animation->Add(std::make_shared<TextKeyFrame>(0.7f, _battleShoudlText4->position, 0.7f, std::string("Bc.Nemcek do?")));
        _battleShoudlText4->animation->Add(std::make_shared<TextKeyFrame>(1.7f, _battleShoudlText4->position, 0.7f, std::string("Bc.Nemcek do?"),
                                                                          std::bind(&BattleScene::BattleShouldText4FinishedCallback, this)));

        _battleMenuPart1Text->StopRendering();
        _battleMenuPart2Text->StopRendering();
        _battleMenuPart3Text->StopRendering();
        _battleMenuPart4Text->StopRendering();

        _guiBattleMenu->renderStoped = true;
        _guiSelector2->renderStoped = true;
        _guiSelector2->animation = std::make_shared<Animation>(false);
        _guiSelector2->animation->enabled = false;
        _guiSelector2->animation->Add(std::make_shared<KeyFrame>(0.0f, _guiSelector2->position, 1.0f));
        _guiSelector2->animation->Add(std::make_shared<KeyFrame>(0.5f, _guiSelector2->position, 1.0f));
        _guiSelector2->animation->Add(std::make_shared<KeyFrame>(0.5f, _guiSelector2->position, 0.0f));
        _guiSelector2->animation->Add(std::make_shared<KeyFrame>(0.7f, _guiSelector2->position, 0.0f));
        _guiSelector2->animation->Add(std::make_shared<KeyFrame>(0.7f, _guiSelector2->position, 1.0f));
        _guiSelector2->animation->Add(std::make_shared<KeyFrame>(1.2f, _guiSelector2->position, 1.0f));
        _guiSelector2->animation->Add(std::make_shared<KeyFrame>(1.2f, _guiSelector2->position, 0.0f));
        _guiSelector2->animation->Add(std::make_shared<KeyFrame>(1.3f, _guiSelector2->position, 0.0f,
                                                                 std::bind(&BattleScene::BattleAttack1ChosenCallback, this)));

        _attack1Text1->StopRendering();
        _attack1Text1->animation = std::make_shared<TextAnimation>(false);
        _attack1Text1->animation->enabled = false;
        _attack1Text1->animation->Add(std::make_shared<TextKeyFrame>(0.0f, _attack1Text1->position, 1.0f, std::string("")));
        _attack1Text1->animation->Add(std::make_shared<TextKeyFrame>(0.7f, _attack1Text1->position, 1.0f, std::string("Bc.Nemcek used"),
                                                                         std::bind(&BattleScene::BattleAttack1Text1FinishedCallback, this)));

        _attack1Text2->StopRendering();
        _attack1Text2->animation = std::make_shared<TextAnimation>(false);
        _attack1Text2->animation->enabled = false;
        _attack1Text2->animation->Add(std::make_shared<TextKeyFrame>(0.0f, _attack1Text2->position, 1.0f, std::string("")));
        _attack1Text2->animation->Add(std::make_shared<TextKeyFrame>(0.5f, _attack1Text2->position, 1.0f, std::string("DIPLOMOVKA!")));
        _attack1Text2->animation->Add(std::make_shared<TextKeyFrame>(0.8f, _attack1Text2->position, 1.0f, std::string("DIPLOMOVKA!"),
                                                                         std::bind(&BattleScene::BattleAttack1Text2FinishedCallback, this)));

        _playerAttack1->renderStoped = true;
        _playerAttack1->animation = std::make_shared<Animation>(false);
        _playerAttack1->animation->enabled = false;
        _playerAttack1->animation->Add(std::make_shared<KeyFrame>(0.0f, _playerAttack1->position, 1.0f));
        _playerAttack1->animation->Add(std::make_shared<KeyFrame>(1.5f, glm::vec2(Constants::WINDOW_WIDTH * 0.8f, Constants::WINDOW_HEIGHT * 0.8f), 0.3f,
                                                                  std::bind(&BattleScene::BattleAttack1HitCallback, this)));

        _enemyHealthbar->animation = std::make_shared<Animation>(false);
        _enemyHealthbar->animation->enabled = false;
        _enemyHealthbar->animation->SetDelay(1.3f);
        _enemyHealthbar->animation->Add(std::make_shared<KeyFrame>(0.0f, _enemyHealthbar->position, 1.0f));
        _enemyHealthbar->animation->Add(std::make_shared<KeyFrame>(1.3f, glm::vec2(_enemyHealthbar->position.x - _enemyHealthbar->bitMap->width * 0.09f, _enemyHealthbar->position.y), glm::vec2(1.0f, 0.7f)));
        _enemyHealthbar->animation->Add(std::make_shared<KeyFrame>(1.6f, glm::vec2(_enemyHealthbar->position.x - _enemyHealthbar->bitMap->width * 0.09f, _enemyHealthbar->position.y), glm::vec2(1.0f, 0.7f),
                                                                   std::bind(&BattleScene::BattleAttack1HealthCallback, this)));

        _attack2Text1->StopRendering();
        _attack2Text1->animation = std::make_shared<TextAnimation>(false);
        _attack2Text1->animation->enabled = false;
        _attack2Text1->animation->Add(std::make_shared<TextKeyFrame>(0.0f, _attack2Text1->position, 1.0f, std::string("")));
        _attack2Text1->animation->Add(std::make_shared<TextKeyFrame>(0.7f, _attack2Text1->position, 1.0f, std::string("FIIT used"),
                                                                     std::bind(&BattleScene::BattleAttack2Text1FinishedCallback, this)));

        _attack2Text2->StopRendering();
        _attack2Text2->animation = std::make_shared<TextAnimation>(false);
        _attack2Text2->animation->enabled = false;
        _attack2Text2->animation->Add(std::make_shared<TextKeyFrame>(0.0f, _attack2Text2->position, 1.0f, std::string("")));
        _attack2Text2->animation->Add(std::make_shared<TextKeyFrame>(0.5f, _attack2Text2->position, 1.0f, std::string("OPONENT!")));
        _attack2Text2->animation->Add(std::make_shared<TextKeyFrame>(0.8f, _attack2Text2->position, 1.0f, std::string("OPONENT!"),
                                                                     std::bind(&BattleScene::BattleAttack2Text2FinishedCallback, this)));

        _enemyAttack->renderStoped = true;
        _enemyAttack->animation = std::make_shared<Animation>(false);
        _enemyAttack->animation->enabled = false;
        _enemyAttack->animation->Add(std::make_shared<KeyFrame>(0.0f, _enemyAttack->position, 1.0f));
        _enemyAttack->animation->Add(std::make_shared<KeyFrame>(1.5f, glm::vec2(Constants::WINDOW_WIDTH * 0.3f, Constants::WINDOW_HEIGHT * 0.4f), 0.3f,
                                                                std::bind(&BattleScene::BattleAttack2HitCallback, this)));

        _playerHealthbar->animation = std::make_shared<Animation>(false);
        _playerHealthbar->animation->enabled = false;
        _playerHealthbar->animation->Add(std::make_shared<KeyFrame>(0.0f, _playerHealthbar->position, 1.0f));
        _playerHealthbar->animation->Add(std::make_shared<KeyFrame>(1.2f, glm::vec2(_playerHealthbar->position.x - _playerHealthbar->bitMap->width * 0.03f, _playerHealthbar->position.y), glm::vec2(1.0f, 0.9f)));

        _notVeryEffictiveText1->StopRendering();
        _notVeryEffictiveText1->animation = std::make_shared<TextAnimation>(false);
        _notVeryEffictiveText1->animation->enabled = false;
        _notVeryEffictiveText1->animation->Add(std::make_shared<TextKeyFrame>(0.0f, _notVeryEffictiveText1->position, 1.0f, std::string("")));
        _notVeryEffictiveText1->animation->Add(std::make_shared<TextKeyFrame>(0.7f, _notVeryEffictiveText1->position, 1.0f, std::string("It's not very"),
                                                                     std::bind(&BattleScene::BattleEffectiveText1Callback, this)));

        _notVeryEffictiveText2->StopRendering();
        _notVeryEffictiveText2->animation = std::make_shared<TextAnimation>(false);
        _notVeryEffictiveText2->animation->enabled = false;
        _notVeryEffictiveText2->animation->Add(std::make_shared<TextKeyFrame>(0.0f, _notVeryEffictiveText2->position, 1.0f, std::string("")));
        _notVeryEffictiveText2->animation->Add(std::make_shared<TextKeyFrame>(0.5f, _notVeryEffictiveText2->position, 1.0f, std::string("effective!")));
        _notVeryEffictiveText2->animation->Add(std::make_shared<TextKeyFrame>(1.3f, _notVeryEffictiveText2->position, 1.0f, std::string("effective!"),
                                                                     std::bind(&BattleScene::BattleEffectiveText2Callback, this)));

        _guiSelector3->renderStoped = true;
        _guiSelector3->animation = std::make_shared<Animation>(false);
        _guiSelector3->animation->enabled = false;
        _guiSelector3->animation->Add(std::make_shared<KeyFrame>(0.0f, _guiSelector2->position, 1.0f));
        _guiSelector3->animation->Add(std::make_shared<KeyFrame>(0.5f, _guiSelector2->position, 1.0f));
        _guiSelector3->animation->Add(std::make_shared<KeyFrame>(0.5f, _guiSelector3->position, 1.0f));
        _guiSelector3->animation->Add(std::make_shared<KeyFrame>(0.7f, _guiSelector3->position, 1.0f));
        _guiSelector3->animation->Add(std::make_shared<KeyFrame>(0.7f, _guiSelector3->position, 0.0f));
        _guiSelector3->animation->Add(std::make_shared<KeyFrame>(1.0f, _guiSelector3->position, 0.0f));
        _guiSelector3->animation->Add(std::make_shared<KeyFrame>(1.0f, _guiSelector3->position, 1.0f));
        _guiSelector3->animation->Add(std::make_shared<KeyFrame>(1.7f, _guiSelector3->position, 1.0f));
        _guiSelector3->animation->Add(std::make_shared<KeyFrame>(1.7f, _guiSelector3->position, 0.0f));
        _guiSelector3->animation->Add(std::make_shared<KeyFrame>(1.8f, _guiSelector3->position, 0.0f,
                                                                 std::bind(&BattleScene::BattleAttack3ChosenCallback, this)));

        _attack3Text1->StopRendering();
        _attack3Text1->animation = std::make_shared<TextAnimation>(false);
        _attack3Text1->animation->enabled = false;
        _attack3Text1->animation->Add(std::make_shared<TextKeyFrame>(0.0f, _attack3Text1->position, 1.0f, std::string("")));
        _attack3Text1->animation->Add(std::make_shared<TextKeyFrame>(0.7f, _attack3Text1->position, 1.0f, std::string("Bc.Nemcek used"),
                                                                     std::bind(&BattleScene::BattleAttack3Text1FinishedCallback, this)));

        _attack3Text2->StopRendering();
        _attack3Text2->animation = std::make_shared<TextAnimation>(false);
        _attack3Text2->animation->enabled = false;
        _attack3Text2->animation->Add(std::make_shared<TextKeyFrame>(0.0f, _attack3Text2->position, 1.0f, std::string("")));
        _attack3Text2->animation->Add(std::make_shared<TextKeyFrame>(0.5f, _attack3Text2->position, 1.0f, std::string("OBHAJOBA!")));
        _attack3Text2->animation->Add(std::make_shared<TextKeyFrame>(0.8f, _attack3Text2->position, 1.0f, std::string("OBHAJOBA!"),
                                                                     std::bind(&BattleScene::BattleAttack3Text2FinishedCallback, this)));

        _playerAttack2->renderStoped = true;
        _playerAttack2->animation = std::make_shared<Animation>(false);
        _playerAttack2->animation->enabled = false;
        _playerAttack2->animation->Add(std::make_shared<KeyFrame>(0.0f, _playerAttack2->position, 1.0f));
        _playerAttack2->animation->Add(std::make_shared<KeyFrame>(1.5f, glm::vec2(Constants::WINDOW_WIDTH * 0.8f, Constants::WINDOW_HEIGHT * 0.8f), 0.3f,
                                                                  std::bind(&BattleScene::BattleAttack3HitCallback, this)));

        _supperEffectiveText->animation = std::make_shared<TextAnimation>(false);
        _supperEffectiveText->animation->enabled = false;
        _supperEffectiveText->animation->Add(std::make_shared<TextKeyFrame>(0.0f, _supperEffectiveText->position, 0.8f, std::string("")));
        _supperEffectiveText->animation->Add(std::make_shared<TextKeyFrame>(0.7f, _supperEffectiveText->position, 0.8f, std::string("It's super effective!")));
        _supperEffectiveText->animation->Add(std::make_shared<TextKeyFrame>(1.0f, _supperEffectiveText->position, 0.8f, std::string("It's super effective!"),
                                                                            std::bind(&BattleScene::BattleSupefEffectiveTextFinishedCallback, this)));

        _faintedText->StopRendering();
        _faintedText->animation = std::make_shared<TextAnimation>(false);
        _faintedText->animation->enabled = false;
        _faintedText->animation->Add(std::make_shared<TextKeyFrame>(0.0f, _faintedText->position, 1.0f, std::string("")));
        _faintedText->animation->Add(std::make_shared<TextKeyFrame>(0.7f, _faintedText->position, 1.0f, std::string("FIIT fainted!")));
        _faintedText->animation->Add(std::make_shared<TextKeyFrame>(1.0f, _faintedText->position, 1.0f, std::string("FIIT fainted!"),
                                                                            std::bind(&BattleScene::BattleFaintedTextFinishedCallback, this)));

        _playerExpbar->renderStoped = true;
        _playerExpbar->animation = std::make_shared<Animation>(false);
        _playerExpbar->animation->enabled = false;
        _playerExpbar->animation->Add(std::make_shared<KeyFrame>(0.0f, _playerExpbar->position, 1.0f));
        _playerExpbar->animation->Add(std::make_shared<KeyFrame>(1.0f, glm::vec2(Constants::WINDOW_WIDTH * 0.802f, _playerExpbar->position.y), glm::vec2(1.0f, 7.25f),
                                                                 std::bind(&BattleScene::BattlePlayerGainedExpCallback, this)));

        _grewText1->StopRendering();
        _grewText1->animation = std::make_shared<TextAnimation>(false);
        _grewText1->animation->enabled = false;
        _grewText1->animation->Add(std::make_shared<TextKeyFrame>(0.0f, _grewText1->position, 1.0f, std::string("")));
        _grewText1->animation->Add(std::make_shared<TextKeyFrame>(0.7f, _grewText1->position, 1.0f, std::string("Bc.Nemcek grew to"),
                                                                              std::bind(&BattleScene::BattleGrewText1FinishedCallback, this)));

        _grewText2->StopRendering();
        _grewText2->animation = std::make_shared<TextAnimation>(false);
        _grewText2->animation->enabled = false;
        _grewText2->animation->Add(std::make_shared<TextKeyFrame>(0.0f, _grewText2->position, 1.0f, std::string("")));
        _grewText2->animation->Add(std::make_shared<TextKeyFrame>(0.5f, _grewText2->position, 1.0f, std::string("LV.100!")));
        _grewText2->animation->Add(std::make_shared<TextKeyFrame>(1.0f, _grewText2->position, 1.0f, std::string("LV.100!"),
                                                                              std::bind(&BattleScene::BattleGrewText2FinishedCallback, this)));

        _guiLevelUp->renderStoped = true;
        _levelUpText1->StopRendering();
        _levelUpText2->StopRendering();
        _levelUpText3->StopRendering();
        _levelUpText4->StopRendering();
        _levelUpText5->StopRendering();
        _levelUpText6->StopRendering();

        _levelUpText1->animation = std::make_shared<TextAnimation>(false);
        _levelUpText1->animation->enabled = false;
        _levelUpText1->animation->Add(std::make_shared<TextKeyFrame>(0.0f, _levelUpText1->position, 0.8f, _levelUpText1->text));
        _levelUpText1->animation->Add(std::make_shared<TextKeyFrame>(2.0f, _levelUpText1->position, 0.8f, _levelUpText1->text));
        _levelUpText1->animation->Add(std::make_shared<TextKeyFrame>(2.0f, _levelUpText1->position, 0.8f, std::string("TIME   100")));

        _levelUpText2->animation = std::make_shared<TextAnimation>(false);
        _levelUpText2->animation->enabled = false;
        _levelUpText2->animation->Add(std::make_shared<TextKeyFrame>(0.0f, _levelUpText2->position, 0.8f, _levelUpText2->text));
        _levelUpText2->animation->Add(std::make_shared<TextKeyFrame>(2.0f, _levelUpText2->position, 0.8f, _levelUpText2->text));
        _levelUpText2->animation->Add(std::make_shared<TextKeyFrame>(2.0f, _levelUpText2->position, 0.8f, std::string("ENERGY 100")));

        _levelUpText3->animation = std::make_shared<TextAnimation>(false);
        _levelUpText3->animation->enabled = false;
        _levelUpText3->animation->Add(std::make_shared<TextKeyFrame>(0.0f, _levelUpText3->position, 0.8f, _levelUpText3->text));
        _levelUpText3->animation->Add(std::make_shared<TextKeyFrame>(2.0f, _levelUpText3->position, 0.8f, _levelUpText3->text));
        _levelUpText3->animation->Add(std::make_shared<TextKeyFrame>(2.0f, _levelUpText3->position, 0.8f, std::string("SKILLS 100")));

        _levelUpText4->animation = std::make_shared<TextAnimation>(false);
        _levelUpText4->animation->enabled = false;
        _levelUpText4->animation->Add(std::make_shared<TextKeyFrame>(0.0f, _levelUpText4->position, 0.8f, _levelUpText4->text));
        _levelUpText4->animation->Add(std::make_shared<TextKeyFrame>(2.0f, _levelUpText4->position, 0.8f, _levelUpText4->text));
        _levelUpText4->animation->Add(std::make_shared<TextKeyFrame>(2.0f, _levelUpText4->position, 0.8f, std::string("CHARM  100")));

        _levelUpText5->animation = std::make_shared<TextAnimation>(false);
        _levelUpText5->animation->enabled = false;
        _levelUpText5->animation->Add(std::make_shared<TextKeyFrame>(0.0f, _levelUpText5->position, 0.8f, _levelUpText5->text));
        _levelUpText5->animation->Add(std::make_shared<TextKeyFrame>(2.0f, _levelUpText5->position, 0.8f, _levelUpText5->text));
        _levelUpText5->animation->Add(std::make_shared<TextKeyFrame>(2.0f, _levelUpText5->position, 0.8f, std::string("SOCIAL   9")));

        _levelUpText6->animation = std::make_shared<TextAnimation>(false);
        _levelUpText6->animation->enabled = false;
        _levelUpText6->animation->Add(std::make_shared<TextKeyFrame>(0.0f, _levelUpText6->position, 0.8f, _levelUpText6->text));
        _levelUpText6->animation->Add(std::make_shared<TextKeyFrame>(2.0f, _levelUpText6->position, 0.8f, _levelUpText6->text));
        _levelUpText6->animation->Add(std::make_shared<TextKeyFrame>(2.0f, _levelUpText6->position, 0.8f, std::string("INTLCT 100")));
        _levelUpText6->animation->Add(std::make_shared<TextKeyFrame>(4.0f, _levelUpText6->position, 0.8f, std::string("INTLCT 100"),
                                                                     std::bind(&BattleScene::BattleGrewFinishedCallback, this)));

//        BitMapPtr blackForegroundBitmap = std::make_shared<BitMap>(_foreground->bitMap->width, _foreground->bitMap->height, Pixel{255, 255, 255, 255});
//        _foreground->animation = std::make_shared<EvolutionAnimation>(_foreground->bitMap);
//        _foreground->animation->Add(std::make_shared<EvolutionKeyFrame>(0.0f, _foreground->position, 1.0f, _foreground->bitMap, 0, false, false));
//        _foreground->animation->Add(std::make_shared<EvolutionKeyFrame>(3.0f, _foreground->position, 1.0f, blackForegroundBitmap, 0, false, true));

        this->_quads.push_back(background);
        this->_quads.push_back(_enemyAttack);
        this->_quads.push_back(_player);
        this->_quads.push_back(_enemy);
        this->_quads.push_back(enemyGuiBackgroud);
        this->_quads.push_back(_enemyHealthbar);
        this->_quads.push_back(enemyGui);
        this->_quads.push_back(playerGuiBackgroud);
        this->_quads.push_back(_playerHealthbar);
        this->_quads.push_back(playerGui);
        this->_quads.push_back(_guiMenu);
        this->_quads.push_back(_guiBattleMenu);
        this->_quads.push_back(_guiSelector);
        this->_quads.push_back(_guiSelector2);
        this->_quads.push_back(_playerExpbar);
        this->_quads.push_back(_playerAttack1);
        this->_quads.push_back(_guiSelector3);
        this->_quads.push_back(_playerAttack2);
        this->_quads.push_back(_guiLevelUp);
//        this->_quads.push_back(_foreground);

        this->_texts.push_back(enemyNameText);
        this->_texts.push_back(enemyLevelText);
        this->_texts.push_back(enemyLevelValueText);
        this->_texts.push_back(_playerNameText);
        this->_texts.push_back(_playerLevelText);
        this->_texts.push_back(_playerLevelValueText);
        this->_texts.push_back(_playerHealthActualText);
        this->_texts.push_back(_playerHealthMaxText);
        this->_texts.push_back(_menuPart1Text);
        this->_texts.push_back(_menuPart2Text);
        this->_texts.push_back(_battleMenuPart1Text);
        this->_texts.push_back(_battleMenuPart2Text);
        this->_texts.push_back(_battleMenuPart3Text);
        this->_texts.push_back(_battleMenuPart4Text);
        this->_texts.push_back(_levelUpText1);
        this->_texts.push_back(_levelUpText2);
        this->_texts.push_back(_levelUpText3);
        this->_texts.push_back(_levelUpText4);
        this->_texts.push_back(_levelUpText5);
        this->_texts.push_back(_levelUpText6);
        this->_texts.push_back(_battleStartText1);
        this->_texts.push_back(_battleStartText2);
        this->_texts.push_back(_battleShoudlText1);
        this->_texts.push_back(_battleShoudlText2);
        this->_texts.push_back(_battleShoudlText3);
        this->_texts.push_back(_battleShoudlText4);
        this->_texts.push_back(_attack1Text1);
        this->_texts.push_back(_attack1Text2);
        this->_texts.push_back(_attack2Text1);
        this->_texts.push_back(_attack2Text2);
        this->_texts.push_back(_attack3Text1);
        this->_texts.push_back(_attack3Text2);
        this->_texts.push_back(_notVeryEffictiveText1);
        this->_texts.push_back(_notVeryEffictiveText2);
        this->_texts.push_back(_supperEffectiveText);
        this->_texts.push_back(_faintedText);
        this->_texts.push_back(_grewText1);
        this->_texts.push_back(_grewText2);

        for (QuadPtr quad : this->_quads)
            _renderManager->ProcessQuad(quad);

        for (TextPtr text : this->_texts)
            _renderManager->ProcessText(text);
    }

    void BattleScene::Animate(float delta) {
        if (_inputManager->IsEnterPressed()) {
            PlayBattleMusic();
            this->enabled = true;
        }

        if (!this->enabled)
            return;

        for (QuadPtr quad : this->_quads) {
            quad->Animate(delta);
        }

        for (TextPtr text : this->_texts) {
            text->Animate(delta);
        }
    }

    void BattleScene::Update(float delta) {
        if (!this->enabled)
            return;

        for (QuadPtr quad : this->_quads) {
            quad->Update(delta);
        }
    }

    void BattleScene::Render() {
        _renderManager->Prepare();
        _renderManager->Render(this->_projection);
    }

    void BattleScene::BattleStartTextFirtPartFinishedCallback() {
        _battleStartText2->animation->enabled = true;
    }

    void BattleScene::BattleStartTextFinishedCallback() {
        _battleStartText1->StopRendering();
        _battleStartText2->StopRendering();

        _menuPart1Text->StartRendering();
        _menuPart2Text->StartRendering();
        _guiMenu->renderStoped = false;
        _guiSelector->renderStoped = false;
        _guiSelector->animation->enabled = true;
        _battleShoudlText1->animation->enabled = true;
    }

    void BattleScene::BattleShouldTextFirstPartFinishedCallback() {
        _battleShoudlText2->animation->enabled = true;
    }

    void BattleScene::BattleShouldTextFinishedCallback() {
        _guiMenu->renderStoped = true;
        _menuPart1Text->StopRendering();
        _menuPart2Text->StopRendering();
        _guiSelector->renderStoped = true;
        _battleShoudlText1->StopRendering();
        _battleShoudlText2->StopRendering();

        _battleMenuPart1Text->StartRendering();
        _battleMenuPart2Text->StartRendering();
        _battleMenuPart3Text->StartRendering();
        _battleMenuPart4Text->StartRendering();
        _guiBattleMenu->renderStoped = false;
        _guiSelector2->renderStoped = false;
        _guiSelector2->animation->enabled = true;
    }

    void BattleScene::BattleAttack1ChosenCallback() {
        _battleMenuPart1Text->StopRendering();
        _battleMenuPart2Text->StopRendering();
        _battleMenuPart3Text->StopRendering();
        _battleMenuPart4Text->StopRendering();
        _guiBattleMenu->renderStoped = true;
        _guiSelector2->renderStoped = true;

        _attack1Text1->StartRendering();
        _attack1Text1->animation->enabled = true;
    }

    void BattleScene::BattleAttack1Text1FinishedCallback() {
        _attack1Text2->StartRendering();
        _attack1Text2->animation->enabled = true;
    }

    void BattleScene::BattleAttack1Text2FinishedCallback() {
        _playerAttack1->renderStoped = false;
        _playerAttack1->animation->enabled = true;

    }

    void BattleScene::BattleAttack1HitCallback() {
        _playerAttack1->renderStoped = true;
        _enemyHealthbar->animation->enabled = true;

        _enemy->animation = std::make_shared<BattleAnimation>(_enemy->bitMap);
        _enemy->animation->Add(std::make_shared<BattleKeyFrame>(0.0f, _enemy->position, 1.0f, 100.0f));
        _enemy->animation->Add(std::make_shared<BattleKeyFrame>(0.2f, _enemy->position, 1.0f, 100.0f));
        _enemy->animation->Add(std::make_shared<BattleKeyFrame>(0.2f, _enemy->position, 0.0f, 100.0f));
        _enemy->animation->Add(std::make_shared<BattleKeyFrame>(0.3f, _enemy->position, 0.0f, 100.0f));
        _enemy->animation->Add(std::make_shared<BattleKeyFrame>(0.3f, _enemy->position, 1.0f, 100.0f));
        _enemy->animation->Add(std::make_shared<BattleKeyFrame>(0.5f, _enemy->position, 1.0f, 100.0f));
        _enemy->animation->Add(std::make_shared<BattleKeyFrame>(0.5f, _enemy->position, 0.0f, 100.0f));
        _enemy->animation->Add(std::make_shared<BattleKeyFrame>(0.6f, _enemy->position, 0.0f, 100.0f));
        _enemy->animation->Add(std::make_shared<BattleKeyFrame>(0.6f, _enemy->position, 1.0f, 100.0f));
        _enemy->animation->Add(std::make_shared<BattleKeyFrame>(0.8f, _enemy->position, 1.0f, 100.0f));
        _enemy->animation->Add(std::make_shared<BattleKeyFrame>(0.8f, _enemy->position, 0.0f, 100.0f));
        _enemy->animation->Add(std::make_shared<BattleKeyFrame>(0.9f, _enemy->position, 0.0f, 100.0f));
        _enemy->animation->Add(std::make_shared<BattleKeyFrame>(0.9f, _enemy->position, 1.0f, 100.0f));
        _enemy->animation->repeat = false;
        _enemy->animation->useFaint = false;

        PlayAttackImpactSound();
    }

    void BattleScene::BattleAttack1HealthCallback() {
        _attack1Text1->StopRendering();
        _attack1Text1->animation->enabled = false;
        _attack1Text2->StopRendering();

        _attack2Text1->StartRendering();
        _attack2Text1->animation->enabled = true;
    }

    void BattleScene::BattleAttack2Text1FinishedCallback() {
        _attack2Text2->StartRendering();
        _attack2Text2->animation->enabled = true;
    }

    void BattleScene::BattleAttack2Text2FinishedCallback() {
        _enemyAttack->renderStoped = false;
        _enemyAttack->animation->enabled = true;
    }

    void BattleScene::BattleAttack2HitCallback() {
        _enemyAttack->renderStoped = true;
        _playerHealthbar->animation->enabled = true;

        _player->animation = std::make_shared<Animation>(false);
        _player->animation->Add(std::make_shared<KeyFrame>(0.0f, _player->position, 1.0f));
        _player->animation->Add(std::make_shared<KeyFrame>(0.2f, _player->position, 1.0f));
        _player->animation->Add(std::make_shared<KeyFrame>(0.2f, _player->position, 0.0f));
        _player->animation->Add(std::make_shared<KeyFrame>(0.3f, _player->position, 0.0f));
        _player->animation->Add(std::make_shared<KeyFrame>(0.3f, _player->position, 1.0f));
        _player->animation->Add(std::make_shared<KeyFrame>(0.5f, _player->position, 1.0f));
        _player->animation->Add(std::make_shared<KeyFrame>(0.5f, _player->position, 0.0f));
        _player->animation->Add(std::make_shared<KeyFrame>(0.6f, _player->position, 0.0f));
        _player->animation->Add(std::make_shared<KeyFrame>(0.6f, _player->position, 1.0f));
        _player->animation->Add(std::make_shared<KeyFrame>(0.8f, _player->position, 1.0f));
        _player->animation->Add(std::make_shared<KeyFrame>(0.8f, _player->position, 0.0f));
        _player->animation->Add(std::make_shared<KeyFrame>(0.9f, _player->position, 0.0f));
        _player->animation->Add(std::make_shared<KeyFrame>(0.9f, _player->position, 1.0f));

        _playerHealthActualText->animation = std::make_shared<TextAnimation>(false);
//        _playerHealthActualText->animation->SetDelay(1.3f);
        _playerHealthActualText->animation->Add(std::make_shared<TextKeyFrame>(0.0f, _playerHealthActualText->position, _playerHealthActualText->scale, std::string("250")));
        _playerHealthActualText->animation->Add(std::make_shared<TextKeyFrame>(.3f, _playerHealthActualText->position, _playerHealthActualText->scale, std::string("248")));
        _playerHealthActualText->animation->Add(std::make_shared<TextKeyFrame>(.6f, _playerHealthActualText->position, _playerHealthActualText->scale, std::string("246")));
        _playerHealthActualText->animation->Add(std::make_shared<TextKeyFrame>(.9f, _playerHealthActualText->position, _playerHealthActualText->scale, std::string("244")));
        _playerHealthActualText->animation->Add(std::make_shared<TextKeyFrame>(1.2f, _playerHealthActualText->position, _playerHealthActualText->scale, std::string("242"),
                                                                               std::bind(&BattleScene::BattleAttack2HealthCallback, this)));

        PlayAttackImpactSound();
    }

    void BattleScene::BattleAttack2HealthCallback() {
        _attack2Text1->StopRendering();
        _attack2Text2->StopRendering();

        _notVeryEffictiveText1->StartRendering();
        _notVeryEffictiveText1->animation->enabled = true;
    }

    void BattleScene::BattleEffectiveText1Callback() {
        _notVeryEffictiveText2->StartRendering();
        _notVeryEffictiveText2->animation->enabled = true;
    }

    void BattleScene::BattleEffectiveText2Callback() {
        _notVeryEffictiveText1->StopRendering();
        _notVeryEffictiveText2->StopRendering();

        _battleShoudlText3->animation->enabled = true;
        _battleShoudlText3->StartRendering();
        _guiMenu->renderStoped = false;
        _menuPart1Text->StartRendering();
        _menuPart2Text->StartRendering();
        _guiSelector->renderStoped = false;
    }

    void BattleScene::BattleShouldText3FinishedCallback() {
        _battleShoudlText4->animation->enabled = true;
    }

    void BattleScene::BattleShouldText4FinishedCallback() {
        _battleShoudlText3->StopRendering();
        _battleShoudlText4->StopRendering();
        _menuPart1Text->StopRendering();
        _menuPart2Text->StopRendering();
        _guiSelector->renderStoped = true;
        _guiMenu->renderStoped = true;

        _guiBattleMenu->renderStoped = false;
        _battleMenuPart1Text->StartRendering();
        _battleMenuPart2Text->StartRendering();
        _battleMenuPart3Text->StartRendering();
        _battleMenuPart3Text->SetText(std::string("PP 19/20"));
        _battleMenuPart4Text->StartRendering();
        _guiSelector3->renderStoped = false;
        _guiSelector3->animation->enabled = true;

        _battleMenuPart3Text->animation = std::make_shared<TextAnimation>(false);
        _battleMenuPart3Text->animation->Add(std::make_shared<TextKeyFrame>(0.0f, _battleMenuPart3Text->position, 0.7f, std::string("PP 19/20")));
        _battleMenuPart3Text->animation->Add(std::make_shared<TextKeyFrame>(0.5f, _battleMenuPart3Text->position, 0.7f, std::string("PP 19/20")));
        _battleMenuPart3Text->animation->Add(std::make_shared<TextKeyFrame>(0.5f, _battleMenuPart3Text->position, 0.7f, std::string("PP 20/20")));

        _battleMenuPart4Text->animation = std::make_shared<TextAnimation>(false);
        _battleMenuPart4Text->animation->Add(std::make_shared<TextKeyFrame>(0.0f, _battleMenuPart4Text->position, 0.8f, std::string("NORMAL")));
        _battleMenuPart4Text->animation->Add(std::make_shared<TextKeyFrame>(0.5f, _battleMenuPart4Text->position, 0.8f, std::string("NORMAL")));
        _battleMenuPart4Text->animation->Add(std::make_shared<TextKeyFrame>(0.5f, _battleMenuPart4Text->position, 0.8f, std::string("PSYCHIC")));
    }

    void BattleScene::BattleAttack3ChosenCallback() {
        _guiBattleMenu->renderStoped = true;
        _battleMenuPart1Text->StopRendering();
        _battleMenuPart2Text->StopRendering();
        _battleMenuPart3Text->StopRendering();
        _battleMenuPart4Text->StopRendering();
        _guiSelector3->renderStoped = true;

        _attack3Text1->StartRendering();
        _attack3Text1->animation->enabled = true;
    }

    void BattleScene::BattleAttack3Text1FinishedCallback() {
        _attack3Text2->StartRendering();
        _attack3Text2->animation->enabled = true;
    }

    void BattleScene::BattleAttack3Text2FinishedCallback() {
        _playerAttack2->renderStoped = false;
        _playerAttack2->animation->enabled = true;
    }

    void BattleScene::BattleAttack3HitCallback() {
        _playerAttack2->renderStoped = true;

        _enemy->animation = std::make_shared<BattleAnimation>(_enemy->bitMap);
        _enemy->animation->Add(std::make_shared<BattleKeyFrame>(0.0f, _enemy->position, 1.0f, 100.0f));
        _enemy->animation->Add(std::make_shared<BattleKeyFrame>(0.2f, _enemy->position, 1.0f, 100.0f));
        _enemy->animation->Add(std::make_shared<BattleKeyFrame>(0.2f, _enemy->position, 0.0f, 100.0f));
        _enemy->animation->Add(std::make_shared<BattleKeyFrame>(0.3f, _enemy->position, 0.0f, 100.0f));
        _enemy->animation->Add(std::make_shared<BattleKeyFrame>(0.3f, _enemy->position, 1.0f, 100.0f));
        _enemy->animation->Add(std::make_shared<BattleKeyFrame>(0.5f, _enemy->position, 1.0f, 100.0f));
        _enemy->animation->Add(std::make_shared<BattleKeyFrame>(0.5f, _enemy->position, 0.0f, 100.0f));
        _enemy->animation->Add(std::make_shared<BattleKeyFrame>(0.6f, _enemy->position, 0.0f, 100.0f));
        _enemy->animation->Add(std::make_shared<BattleKeyFrame>(0.6f, _enemy->position, 1.0f, 100.0f));
        _enemy->animation->Add(std::make_shared<BattleKeyFrame>(0.8f, _enemy->position, 1.0f, 100.0f));
        _enemy->animation->Add(std::make_shared<BattleKeyFrame>(0.8f, _enemy->position, 0.0f, 100.0f));
        _enemy->animation->Add(std::make_shared<BattleKeyFrame>(0.9f, _enemy->position, 0.0f, 100.0f));
        _enemy->animation->Add(std::make_shared<BattleKeyFrame>(0.9f, _enemy->position, 1.0f, 100.0f));
        _enemy->animation->repeat = false;
        _enemy->animation->useFaint = false;

        _enemyHealthbar->animation = std::make_shared<Animation>(false);
        _enemyHealthbar->animation->SetDelay(1.3f);
        _enemyHealthbar->animation->Add(std::make_shared<KeyFrame>(0.0f, _enemyHealthbar->position, glm::vec2(1.0f, 0.7f)));
        _enemyHealthbar->animation->Add(std::make_shared<KeyFrame>(1.6f, glm::vec2(_enemyHealthbar->position.x - _enemyHealthbar->bitMap->width * 0.305f, _enemyHealthbar->position.y), glm::vec2(1.0f, 0.0f),
                                                                   std::bind(&BattleScene::BattleAttack3HealthCallback, this)));

        PlayAttackImpactSound();
    }

    void BattleScene::BattleAttack3HealthCallback() {
        _attack3Text1->StopRendering();
        _attack3Text2->StopRendering();

        _supperEffectiveText->StartRendering();
        _supperEffectiveText->animation->enabled = true;
    }

    void BattleScene::BattleSupefEffectiveTextFinishedCallback() {
        _enemy->animation = std::make_shared<BattleAnimation>(_enemy->bitMap);
        _enemy->animation->Add(std::make_shared<BattleKeyFrame>(0.0f, _enemy->position, 1.0f, 100.0f));
        _enemy->animation->Add(std::make_shared<BattleKeyFrame>(1.0f, _enemy->position, 1.0f, 0.0f, std::bind(&BattleScene::BattleEnemyFainted, this)));
        _enemy->animation->repeat = false;
    }

    void BattleScene::BattleEnemyFainted() {
        _supperEffectiveText->StopRendering();

        _faintedText->StartRendering();
        _faintedText->animation->enabled = true;
    }

    void BattleScene::BattleFaintedTextFinishedCallback() {
        _playerExpbar->renderStoped = false;
        _playerExpbar->animation->enabled = true;
    }

    void BattleScene::BattlePlayerGainedExpCallback() {
        _faintedText->StopRendering();

        _grewText1->StartRendering();
        _grewText1->animation->enabled = true;
    }

    void BattleScene::BattleGrewText1FinishedCallback() {
        _grewText2->StartRendering();
        _grewText2->animation->enabled = true;
    }

    void BattleScene::BattleGrewText2FinishedCallback() {
        _playerNameText->StopRendering();
        _playerLevelText->StopRendering();
        _playerLevelValueText->StopRendering();
        _playerHealthMaxText->StopRendering();
        _playerHealthActualText->StopRendering();

        _guiLevelUp->renderStoped = false;
        _levelUpText1->StartRendering();
        _levelUpText2->StartRendering();
        _levelUpText3->StartRendering();
        _levelUpText4->StartRendering();
        _levelUpText5->StartRendering();
        _levelUpText6->StartRendering();

        _levelUpText1->animation->enabled = true;
        _levelUpText2->animation->enabled = true;
        _levelUpText3->animation->enabled = true;
        _levelUpText4->animation->enabled = true;
        _levelUpText5->animation->enabled = true;
        _levelUpText6->animation->enabled = true;
    }

    void BattleScene::BattleGrewFinishedCallback() {
        this->finished = true;
    }

    void BattleScene::PlayBattleMusic() {
        // quick and dirty way
        _musicPID = fork();

        if (_musicPID == 0) {
            system("paplay \"/home/nemcek/dev/pokemon-custom-evolution/data/pokemon_battle_music.wav\"");
            exit(0);
        }
    }

    void BattleScene::Clean() {
        this->_renderManager->Clean();
        kill(_musicPID + 2, SIGTERM);
    }

    void BattleScene::PlayAttackImpactSound() {
        // quick and dirty way
        pid_t pid = fork();

        if (pid == 0) {
            system("paplay \"/home/nemcek/dev/pokemon-custom-evolution/data/pokemon_attack_impact_sound.wav\"");
            exit(0);
        }
    }

}