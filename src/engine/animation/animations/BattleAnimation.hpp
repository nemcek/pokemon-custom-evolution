//
// Created by nemcek on 6/4/18.
//

#ifndef POKEMON_CUSTOM_EVOLUTION_BATTLEANIMATION_H
#define POKEMON_CUSTOM_EVOLUTION_BATTLEANIMATION_H


#include "Animation.hpp"
#include <engine/animation/keyframes/BattleKeyFrame.hpp>

namespace Engine {
    namespace nsAnimation {
        namespace Animations {
            class BattleAnimation : public Animations::Animation {
            private:
                BitMapPtr &originalBitMap;

            public:
                BattleAnimation(BitMapPtr &bitMap);
                virtual AnimationStatus Animate(float delta) override;

                BitMapPtr bitMap;
                bool useFaint = true;
            };

            typedef std::shared_ptr<BattleAnimation> BattleAnimationPtr;
        }
    }
}


#endif //POKEMON_CUSTOM_EVOLUTION_BATTLEANIMATION_H
