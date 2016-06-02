//
// Created by martin on 26.05.2016.
//

#ifndef POKEMON_CUSTOM_EVOLUTION_KEYFRAME_HPP
#define POKEMON_CUSTOM_EVOLUTION_KEYFRAME_HPP

#include <glm/vec2.hpp>
#include <functional>
#include <glm/vec3.hpp>
#include <memory>

class KeyFrame
{
private:
    void Init(float time, glm::vec2 pos, float scale);

public:
    glm::vec2 position;
    float time;
    float scale;
    std::function<void (void)> callback;

    KeyFrame(float time, glm::vec2 pos, float scale);
    KeyFrame(float time, glm::vec2 pos, float scale, std::function<void (void)> callback);
    virtual ~KeyFrame();
};

typedef std::shared_ptr<KeyFrame> KeyFramePtr;

#endif //POKEMON_CUSTOM_EVOLUTION_KEYFRAME_HPP
