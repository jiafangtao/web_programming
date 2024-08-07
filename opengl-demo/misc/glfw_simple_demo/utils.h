#pragma once

#include <cassert>
#include <cstdio>
#include "linmath.h"


namespace util {
    void bbox(const Vertex* vertices, unsigned int size, float* bb)
    {
        assert(vertices != nullptr);
        assert(size > 0);

        // z is not considered in this case.
        float xmin, xmax, ymin, ymax;
        xmin = xmax = vertices[0].x;
        ymin = ymax = vertices[0].y;

        for (unsigned int i = 1; i < size; i++)
        {
            float x = vertices[i].x;
            float y = vertices[i].y;

            if (x < xmin) { xmin = x; }
            if (y < ymin) { ymin = y; }
            if (x > xmax) { xmax = x; }
            if (y > ymax) { ymax = y; }
        }

        bb[0] = xmin;
        bb[1] = ymin;
        bb[2] = xmax;
        bb[3] = ymax;
    }
}
