//
// Created by martin on 26.05.2016.
//

#include <engine/Transformations.hpp>
#include "EvolutionQuad.hpp"

namespace Objects
{
    EvolutionQuad::EvolutionQuad(LoaderPtr loader, glm::vec2 position, float scale, BitMapPtr firstStageOfEvolution,
                                 BitMapPtr secondStageOfEvolution)
            : Quad(loader, position, scale, firstStageOfEvolution) {
        this->_firstStageOfEvolution = firstStageOfEvolution;
        this->_secondStageOfEvolution = secondStageOfEvolution;
        _firstStageOfEvolutionIsActive = true;
        _secondStageOfEvolutionIsActive = false;
    }

    EvolutionQuad::~EvolutionQuad() { }

    void EvolutionQuad::Animate(float delta) {
        if (this->animation != nullptr) {
            this->animation->Animate(delta);

            if (this->animation->changeToWhite) {
                this->_firstStageOfEvolution = Transformations::ChangeToWhite(this->_firstStageOfEvolution);
                this->_secondStageOfEvolution = Transformations::ChangeToWhite(this->_secondStageOfEvolution);

                this->animation->changeToWhite = false;
            }

            if (this->animation->swap) {
                if (_firstStageOfEvolutionIsActive) {
                    this->bitMap = _secondStageOfEvolution;
                    this->_secondStageOfEvolutionIsActive = true;
                    this->_firstStageOfEvolutionIsActive = false;
                }
                else if (_secondStageOfEvolutionIsActive) {
                    this->bitMap = _firstStageOfEvolution;
                    this->_secondStageOfEvolutionIsActive = false;
                    this->_firstStageOfEvolutionIsActive = true;
                }

                this->animation->swap = false;
            }
            else if (this->animation->bitMap != nullptr) {
                this->bitMap = this->animation->bitMap;
                this->animation->bitMap = nullptr;
            }

            this->position = this->animation->position;
            this->Scale(this->animation->scale);
        }
    }
}