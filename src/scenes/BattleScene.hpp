//
// Created by nemcek on 5/27/18.
//

#ifndef POKEMON_CUSTOM_EVOLUTION_BATTLESCENE_H
#define POKEMON_CUSTOM_EVOLUTION_BATTLESCENE_H

#include "Scene.hpp"
#include "objects/Quad.hpp"
#include "objects/BattleQuad.hpp"
#include "engine/rendering/RenderManager.hpp"
#include <constants/Constants.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <engine/InputManager.hpp>

namespace Scenes
{
    class BattleScene : public Scene {
    private:
        std::vector<QuadPtr> _quads;
        std::vector<TextPtr> _texts;
        Rendering::RenderManagerPtr _renderManager;
        glm::mat4 _projection;
        LoaderPtr _loader;

        TextPtr _battleStartText1;
        TextPtr _battleStartText2;
        TextPtr _menuPart1Text;
        TextPtr _menuPart2Text;
        QuadPtr _guiMenu;
        QuadPtr _guiSelector;
        QuadPtr _guiSelector2;
        TextPtr _battleShoudlText1;
        TextPtr _battleShoudlText2;
        TextPtr _battleMenuPart1Text;
        TextPtr _battleMenuPart2Text;
        TextPtr _battleMenuPart3Text;
        TextPtr _battleMenuPart4Text;
        QuadPtr _guiBattleMenu;
        TextPtr _attack1Text1;
        TextPtr _attack1Text2;
        QuadPtr _playerAttack1;
        QuadPtr _enemyHealthbar;
        TextPtr _attack2Text1;
        TextPtr _attack2Text2;
        QuadPtr _enemyAttack;
        QuadPtr _playerHealthbar;
        TextPtr _playerHealthActualText;
        TextPtr _notVeryEffictiveText1;
        TextPtr _notVeryEffictiveText2;
        BattleQuadPtr _enemy;
        QuadPtr _player;
        TextPtr _battleShoudlText3;
        TextPtr _battleShoudlText4;
        QuadPtr _guiSelector3;
        TextPtr _attack3Text1;
        TextPtr _attack3Text2;
        QuadPtr _playerAttack2;
        TextPtr _supperEffectiveText;
        TextPtr _faintedText;
        QuadPtr _playerExpbar;
        TextPtr _grewText1;
        TextPtr _grewText2;
        QuadPtr _guiLevelUp;
        TextPtr _levelUpText1;
        TextPtr _levelUpText2;
        TextPtr _levelUpText3;
        TextPtr _levelUpText4;
        TextPtr _levelUpText5;
        TextPtr _levelUpText6;
        TextPtr _playerLevelValueText;
        TextPtr _playerNameText;
        TextPtr _playerLevelText;
        TextPtr _playerHealthMaxText;
        EvolutionQuadPtr _foreground;

        void Init();
        void BattleStartTextFirtPartFinishedCallback();
        void BattleStartTextFinishedCallback();
        void BattleShouldTextFirstPartFinishedCallback();
        void BattleShouldTextFinishedCallback();
        void BattleAttack1ChosenCallback();
        void BattleAttack1Text1FinishedCallback();
        void BattleAttack1Text2FinishedCallback();
        void BattleAttack1HitCallback();
        void BattleAttack1HealthCallback();
        void BattleAttack2Text1FinishedCallback();
        void BattleAttack2Text2FinishedCallback();
        void BattleAttack2HitCallback();
        void BattleAttack2HealthCallback();
        void BattleEffectiveText1Callback();
        void BattleEffectiveText2Callback();
        void BattleShouldText3FinishedCallback();
        void BattleShouldText4FinishedCallback();
        void BattleAttack3ChosenCallback();
        void BattleAttack3Text1FinishedCallback();
        void BattleAttack3Text2FinishedCallback();
        void BattleAttack3HitCallback();
        void BattleAttack3HealthCallback();
        void BattleSupefEffectiveTextFinishedCallback();
        void BattleEnemyFainted();
        void BattleFaintedTextFinishedCallback();
        void BattlePlayerGainedExpCallback();
        void BattleGrewText1FinishedCallback();
        void BattleGrewText2FinishedCallback();
        void BattleGrewFinishedCallback();

        InputManagerPtr _inputManager;
        bool enabled = false;
        pid_t _musicPID;

        void PlayBattleMusic();
        void PlayAttackImpactSound();
    public:
        BattleScene(InputManagerPtr inputManager);
        ~BattleScene();
        void Animate(float delta);
        void Render();
        void Update(float delta);
        void Clean();
    };

    typedef std::shared_ptr<BattleScene> BattleScenePtr;
}


#endif //POKEMON_CUSTOM_EVOLUTION_BATTLESCENE_H
