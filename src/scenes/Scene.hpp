//
// Created by nemcek on 5/27/18.
//

#ifndef POKEMON_CUSTOM_EVOLUTION_SCENE_H
#define POKEMON_CUSTOM_EVOLUTION_SCENE_H

#include <memory>

namespace Scenes
{
    class Scene {
    public:
        virtual void Animate(float delta) = 0;

        virtual void Render() = 0;

        virtual void Update(float delta) = 0;
    };

    typedef std::shared_ptr<Scene> ScenePtr;
}

#endif //POKEMON_CUSTOM_EVOLUTION_SCENE_H
