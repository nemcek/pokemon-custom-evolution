//
// Created by martin on 23.05.2016.
//

#include "src/engine/rendering/TextRenderer.hpp"

TextRenderer::TextRenderer(TextShader *shader)
{
    this->shader = shader;
    Initialize();
}

void TextRenderer::Initialize()
{
    // Configure VAO/VBO for texture quads
    shader->Start();
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    shader->Stop();
}

void TextRenderer::Render(std::vector<Text *> texts, glm::mat4 projection)
{
    for ( std::vector<Text *>::iterator it = texts.begin(); it != texts.end(); it++ ) {
        Render(*it, projection);
    }
}

void TextRenderer::Render(Text *text, glm::mat4 projection)
{
    shader->Start();
    shader->LoadTextColor(text->color);
    shader->LoadProjection(projection);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(vao);

    GLfloat x = text->position.x;
    GLfloat y = text->position.y;

    // Iterate through all characters
    std::string::const_iterator c;
    for (c = text->text.begin(); c != text->text.end(); c++)
    {
        Character ch = text->font->characters[*c];

        GLfloat xpos = x + ch.Bearing.x * text->scale;
        GLfloat ypos = y - (ch.Size.y - ch.Bearing.y) * text->scale;

        GLfloat w = ch.Size.x * text->scale;
        GLfloat h = ch.Size.y * text->scale;
        // Update VBO for each character
        GLfloat vertices[6][4] = {
                { xpos,     ypos + h,   0.0, 0.0 },
                { xpos,     ypos,       0.0, 1.0 },
                { xpos + w, ypos,       1.0, 1.0 },

                { xpos,     ypos + h,   0.0, 0.0 },
                { xpos + w, ypos,       1.0, 1.0 },
                { xpos + w, ypos + h,   1.0, 0.0 }
        };
        // Render glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
        // Update content of VBO memory
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // Be sure to use glBufferSubData and not glBufferData

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        // Render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        x += (ch.Advance >> 6) * text->scale; // Bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
    }
//    glBindVertexArray(0);
//    glBindTexture(GL_TEXTURE_2D, 0);
}
