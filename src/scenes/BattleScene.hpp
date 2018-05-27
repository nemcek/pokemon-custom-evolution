//
// Created by nemcek on 5/27/18.
//

#ifndef POKEMON_CUSTOM_EVOLUTION_BATTLESCENE_H
#define POKEMON_CUSTOM_EVOLUTION_BATTLESCENE_H

#include "Scene.hpp"

namespace Scenes
{
    class BattleScene : public Scene {
    public:
        BattleScene();
        ~BattleScene();
        void Animate(float delta);
        void Render();
        void Update(float delta);
    };

    typedef std::shared_ptr<BattleScene> BattleScenePtr;
}


#endif //POKEMON_CUSTOM_EVOLUTION_BATTLESCENE_H
