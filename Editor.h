#ifndef LAB_1_EDITOR_H
#define LAB_1_EDITOR_H

#include "MyImage.h"

class Editor {
public:
    Editor(MyImage* image): image_(image) {    }
    void PutPixel(Point point, Pixel pixel);
    void Save();

private:
    MyImage* image_;
};


#endif //LAB_1_EDITOR_H
