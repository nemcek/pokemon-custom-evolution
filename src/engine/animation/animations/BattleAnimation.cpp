//
// Created by nemcek on 6/4/18.
//

#include <engine/Transformations.hpp>
#include "BattleAnimation.hpp"

Engine::nsAnimation::Animations::BattleAnimation::BattleAnimation(BitMapPtr &bitMap) : Animation(), originalBitMap(bitMap) {

}

Engine::nsAnimation::Animations::AnimationStatus
Engine::nsAnimation::Animations::BattleAnimation::Animate(float delta) {
    AnimationStatus status = Animation::Animate(delta);

    if (status == AnimationStatus::Default || status == AnimationStatus::MovedToNext) {
        if (currentKeyFrameIndex + 1 >= keyFrames.size())
            return AnimationStatus::Default;

        BattleKeyFramePtr battleKeyFrame = std::static_pointer_cast<BattleKeyFrame>(keyFrames[currentKeyFrameIndex + 1]);

        float t = GetAnimationTime(currentKeyFrameIndex);
        int faint = (int) Transformations::Lerp(std::static_pointer_cast<BattleKeyFrame>(keyFrames[currentKeyFrameIndex])->faint,
                              battleKeyFrame->faint, t);

        if (useFaint)
            bitMap = Transformations::Faint(originalBitMap, faint);

        return status;
    }

    return AnimationStatus::Default;
}

