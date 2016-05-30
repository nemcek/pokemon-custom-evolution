//
// Created by martin on 26.05.2016.
//

#include "EvolutionQuad.hpp"

EvolutionQuad::EvolutionQuad(Loader *loader, glm::vec2 position, float scale, BitMap *firstStageOfEvolution,
                             BitMap *secondStageOfEvolution)
    : Quad(loader, position, scale, firstStageOfEvolution)
{
    this->firstStageOfEvolution = firstStageOfEvolution;
    this->secondStageOfEvolution = secondStageOfEvolution;
    firstStageOfEvolutionIsActive = true;
    secondStageOfEvolutionIsActive = false;
}

void EvolutionQuad::Animate(float delta)
{
    if (this->animation != nullptr)
    {
        this->animation->Animate(delta);

        if (this->animation->swap)
        {
            if (firstStageOfEvolutionIsActive)
            {
                this->bitMap = secondStageOfEvolution;
                this->secondStageOfEvolutionIsActive = true;
                this->firstStageOfEvolutionIsActive = false;
            }
            else if (secondStageOfEvolutionIsActive)
            {
                this->bitMap = firstStageOfEvolution;
                this->secondStageOfEvolutionIsActive = false;
                this->firstStageOfEvolutionIsActive = true;
            }

            this->animation->swap = false;
        }

        this->position = this->animation->position;
        this->Scale(this->animation->scale);
    }
}
