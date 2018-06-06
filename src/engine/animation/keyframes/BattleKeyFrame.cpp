//
// Created by nemcek on 6/4/18.
//

#include "BattleKeyFrame.hpp"

Engine::nsAnimation::KeyFrames::BattleKeyFrame::BattleKeyFrame(float time, const glm::vec2 &pos, float scale)
        : KeyFrame(time, pos, scale) {}

Engine::nsAnimation::KeyFrames::BattleKeyFrame::BattleKeyFrame(float time, const glm::vec2 &pos, float scale,
                                                               float faint)
        : KeyFrame(time, pos, scale), faint(faint) {

}

Engine::nsAnimation::KeyFrames::BattleKeyFrame::BattleKeyFrame(float time, const glm::vec2 &pos, float scale,
                                                               float faint, std::function<void(void)> callback)
        : KeyFrame(time, pos, scale)
        , faint(faint)
{
    this->callback = callback;
}
