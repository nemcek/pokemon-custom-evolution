//
// Created by nemcek on 5/27/18.
//

#ifndef POKEMON_CUSTOM_EVOLUTION_BATTLESCENE_H
#define POKEMON_CUSTOM_EVOLUTION_BATTLESCENE_H

#include "Scene.hpp"
#include "objects/Quad.hpp"
#include "engine/rendering/RenderManager.hpp"
#include <constants/Constants.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Scenes
{
    class BattleScene : public Scene {
    private:
        std::vector<QuadPtr> _quads;
        Rendering::RenderManagerPtr _renderManager;
        glm::mat4 _projection;
        LoaderPtr _loader;

        void Init();
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
