//
// Created by martin on 18.05.2016.
//

#include "src/engine/Manipulations.hpp"

std::vector<Pixel>* Manipulations::Scale(std::vector <Pixel> *buffer, int width, int height, int new_width, int new_height)
{
    std::vector<Pixel> *framebuffer = new std::vector<Pixel>((unsigned long) (width * height), {0, 0, 0, 0});
    Pixel a, b, c, d;
    int x, y, index;
    float x_ratio = ((float)(width - 1)) / new_width;
    float y_ratio = ((float)(height - 1))/ new_height;
    float x_diff, y_diff, blue, red, green;
    int offset = 0 ;

    for (int i = 0; i < new_height; i++)
    {
        for (int j = 0; j < new_width; j++)
        {
            x = (int) (x_ratio * j);
            y = (int) (y_ratio * i);
            x_diff = (x_ratio * j) - x;
            y_diff = (y_ratio * i) - y;
            index = (y * width + x);
            a = (*buffer)[index];
            b = (*buffer)[index + 1];
            c = (*buffer)[index + width];
            d = (*buffer)[index + width + 1];

            // blue element
            // Yb = Ab(1-w)(1-h) + Bb(w)(1-h) + Cb(h)(1-w) + Db(wh)
            blue = a.B * (1 - x_diff) * (1 - y_diff) + b.B * (x_diff) * (1 - y_diff) +
                   c.B * (y_diff) * (1 - x_diff) + d.B * (x_diff * y_diff);

            // green element
            // Yg = Ag(1-w)(1-h) + Bg(w)(1-h) + Cg(h)(1-w) + Dg(wh)
            green = a.G * (1 - x_diff) * (1 - y_diff) + b.G * (x_diff) * (1 - y_diff) +
                    c.G * (y_diff) * (1 - x_diff) + d.G * (x_diff * y_diff);

            // red element
            // Yr = Ar(1-w)(1-h) + Br(w)(1-h) + Cr(h)(1-w) + Dr(wh)
            red = a.R * (1 - x_diff) * (1 - y_diff) + b.R * (x_diff) * (1 - y_diff) +
                  c.R * (y_diff) * (1 - x_diff) + d.R * (x_diff * y_diff);

            (*framebuffer)[i * new_width + j] = { red, green, blue, (*buffer)[i * new_width + j].A };
        }
    }

    return framebuffer;
}
