//
// Created by martin on 18.05.2016.
//

#include <iostream>
#include "src/engine/Transformations.hpp"

BitMap* Transformations::Scale(BitMap *bitmap, int new_width, int new_height)
{
    BitMap *scaled = new BitMap(new_width, new_height);
    Pixel a, b, c, d;
    int x, y, index;
    float x_ratio = ((float)(bitmap->width - 1)) / (float)new_width;
    float y_ratio = ((float)(bitmap->height - 1))/ (float)new_height;
    float x_diff, y_diff, blue, red, green, alpha;

    for (int i = 0; i < new_height; i++)
    {
        for (int j = 0; j < new_width; j++)
        {
            x = (int)(x_ratio * j);
            y = (int)(y_ratio * i);
            x_diff = (x_ratio * j) - x;
            y_diff = (y_ratio * i) - y;
            index = (y * bitmap->width + x);
            a = (*bitmap->buffer)[index];
            b = (*bitmap->buffer)[index + 1];
            c = (*bitmap->buffer)[index + bitmap->width];
            d = (*bitmap->buffer)[index + bitmap->width + 1];

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

            // also interpolate alpha channel
            alpha = a.A * (1 - x_diff) * (1 - y_diff) + b.A * (x_diff) * (1 - y_diff) +
                    c.A * (y_diff) * (1 - x_diff) + d.A * (x_diff * y_diff);

            (*scaled->buffer)[i * new_width + j] = { (unsigned char)red, (unsigned char)green, (unsigned char)blue, (unsigned char)alpha };
        }
    }
    return scaled;
}

BitMap* Transformations::ChangeToWhite(BitMap *bitmap)
{
    BitMap *changed = new BitMap(bitmap->width, bitmap->height);

    for (int y = 0; y < bitmap->height; y++)
    {
        for (int x = 0; x < bitmap->width; x++)
        {
            if ((*bitmap->buffer)[y * bitmap->width + x].A == 0)
                (*changed->buffer)[y * bitmap->width + x] = (*bitmap->buffer)[y * bitmap->width + x];
            else
            {
                (*changed->buffer)[y * bitmap->width + x].R = 255;
                (*changed->buffer)[y * bitmap->width + x].G = 255;
                (*changed->buffer)[y * bitmap->width + x].B = 255;
            }
        }
    }

    return changed;
}

BitMap* Transformations::Concat(BitMap *background, BitMap *foreground, PicturePosition position)
{
    switch (position)
    {
        case PicturePosition::Center:
            return Transformations::Center(background, foreground);
    }

    return nullptr;
}

BitMap* Transformations::Center(BitMap *background, BitMap *foreground)
{
    int top_margin = ((background->height - foreground->height) / 2) * background->width;
    int left_margin = (background->width - foreground->width) / 2;
    int offset = 0;

    for (int y = 0; y < foreground->height; y++)
    {
        for (int x = 0; x < foreground->width; x++)
        {
            (*background->buffer)[top_margin + y * foreground->width + x + left_margin + offset] = (*foreground->buffer)[y * foreground->width + x];
        }

        offset += 2 * left_margin;
    }

    return background;
}
