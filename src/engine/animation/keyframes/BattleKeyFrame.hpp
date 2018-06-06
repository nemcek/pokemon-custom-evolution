//
// Created by nemcek on 6/4/18.
//

#ifndef POKEMON_CUSTOM_EVOLUTION_BATTLEKEYFRAME_H
#define POKEMON_CUSTOM_EVOLUTION_BATTLEKEYFRAME_H


#include "KeyFrame.hpp"

namespace Engine {
    namespace nsAnimation {
        namespace KeyFrames {
            class BattleKeyFrame : public KeyFrames::KeyFrame {
            public:
                BattleKeyFrame(float time, const glm::vec2 &pos, float scale);
                BattleKeyFrame(float time, const glm::vec2 &pos, float scale, float faint);
                BattleKeyFrame(float time, const glm::vec2 &pos, float scale, float faint, std::function<void(void)> callback);

                float faint;
            };

            typedef std::shared_ptr<BattleKeyFrame> BattleKeyFramePtr;
        }
    }
}


#endif //POKEMON_CUSTOM_EVOLUTION_BATTLEKEYFRAME_H
