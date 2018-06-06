//
// Created by nemcek on 6/4/18.
//

#ifndef POKEMON_CUSTOM_EVOLUTION_BATTLEQUAD_H
#define POKEMON_CUSTOM_EVOLUTION_BATTLEQUAD_H


#include <engine/animation/animations/BattleAnimation.hpp>
#include "Quad.hpp"

namespace Objects {
    class BattleQuad : public Quad {
    public:
        BattleAnimationPtr animation;

        BattleQuad(const LoaderPtr &loader, const glm::vec2 &position, float scale, const BitMapPtr &bitMap);
        void Animate(float delta) override;
    };

    typedef std::shared_ptr<BattleQuad> BattleQuadPtr;
}

#endif //POKEMON_CUSTOM_EVOLUTION_BATTLEQUAD_H
