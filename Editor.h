#ifndef LAB_1_EDITOR_H
#define LAB_1_EDITOR_H

#include <cstdlib>
#include <ctime>

#include "MyImage.h"


class Editor {
public:
    Editor(MyImage* image): image_(image) {    }
    void PutPixel(Point point, Pixel pixel, int thickness);
    void DrawAxis();
    void DrawLine(Point p1, Point p2, Pixel pixel, int thickness = 1);
    void DrawRandomColouredLine(Point p1, Point p2, int thickness = 1);

    void Save();

private:
    void DrawLineHigh(Point p1, Point p2, int thickness, Pixel pixel);
    void DrawLineLow(Point p1, Point p2, int thickness, Pixel pixel);
    void DrawLineHighRandom(Point p1, Point p2, int thickness);
    void DrawLineLowRandom(Point p1, Point p2, int thickness);

    MyImage* image_;
};


#endif //LAB_1_EDITOR_H
