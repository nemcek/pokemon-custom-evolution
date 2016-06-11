//
// Created by martin on 11.06.2016.
//

#include "EvolutionParticle.hpp"

namespace Objects
{
    EvolutionParticle::EvolutionParticle(LoaderPtr loader, glm::vec2 position, float scale,
                                         BitMapPtr firstStage, BitMapPtr secondStage,
                                         BitMapPtr thirdStage)
            : EvolutionQuad(loader, position, scale, firstStage, secondStage)
            , _thirdsStage(thirdStage) {
        this->_thirdStageIsActive = false;
    }

    void EvolutionParticle::Animate(float delta) {
        if (this->animation != nullptr) {
            this->animation->Animate(delta);

            if (this->animation->swap) {
                if (_firstStageOfEvolutionIsActive) {
                    this->bitMap = _secondStageOfEvolution;
                    this->_firstStageOfEvolutionIsActive = false;
                    this->_secondStageOfEvolutionIsActive = true;
                    this->_thirdStageIsActive = false;
                }
                else if (_secondStageOfEvolutionIsActive) {
                    this->bitMap = _thirdsStage;
                    this->_firstStageOfEvolutionIsActive = false;
                    this->_secondStageOfEvolutionIsActive = false;
                    this->_thirdStageIsActive = true;
                }
                else if (_thirdStageIsActive) {
                    this->bitMap = _firstStageOfEvolution;
                    this->_firstStageOfEvolutionIsActive = true;
                    this->_secondStageOfEvolutionIsActive = false;
                    this->_thirdStageIsActive = false;
                }

                this->animation->swap = false;
            }

            if (this->animation->bitMap != nullptr) {
                this->bitMap = this->animation->bitMap;
                this->animation->bitMap = nullptr;
            }

            this->position = this->animation->position;
            this->Scale(this->animation->scale);
        }
    }
}