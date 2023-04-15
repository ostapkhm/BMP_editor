#ifndef LAB_1_EDITOR_H
#define LAB_1_EDITOR_H

#include <cstdlib>
#include <ctime>
#include <random>

#include "../MyImage/MyImage.h"


class Editor {
public:
    Editor(MyImage* image): image_(image) {
        random_engine_ = std::default_random_engine(time(nullptr));
    }
    void PutPixel(Point point, Pixel pixel, int thickness);
    void DrawAxis();
    void DrawLine(Point p1, Point p2, Pixel pixel, int thickness = 1);
    void DrawRandomColouredLine(Point p1, Point p2, int thickness = 1);

    void Save(const std::string& filename);

private:
    void DrawLineHigh(Point p1, Point p2, int thickness, Pixel pixel);
    void DrawLineLow(Point p1, Point p2, int thickness, Pixel pixel);
    void DrawLineHighRandom(Point p1, Point p2, int thickness);
    void DrawLineLowRandom(Point p1, Point p2, int thickness);
    Pixel GetRandomPixel();

    std::default_random_engine random_engine_;
    MyImage* image_;
};


#endif //LAB_1_EDITOR_H
