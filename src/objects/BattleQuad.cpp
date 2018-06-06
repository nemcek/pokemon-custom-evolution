//
// Created by nemcek on 6/4/18.
//

#include "BattleQuad.hpp"

BattleQuad::BattleQuad(const LoaderPtr &loader, const glm::vec2 &position, float scale, const BitMapPtr &bitMap) : Quad(
        loader, position, scale, bitMap) {}

void BattleQuad::Animate(float delta) {
    if (this->animation != nullptr) {
        this->animation->Animate(delta);

        if (this->animation->bitMap != nullptr) {
            this->bitMap = this->animation->bitMap;
            this->animation->bitMap = nullptr;
        }

        this->position = this->animation->position;
        this->Scale(this->animation->scale);
    }
}
