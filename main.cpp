#include "Editor.h"

using namespace std;

int main() {
    MyImage image("new.bmp");

    Editor editor(&image);
    editor.PutPixel({2, 0}, {123, 221, 12});
    editor.PutPixel({1, 0}, {223, 11, 12});
    editor.PutPixel({3, 3}, {33, 221, 13});
    editor.PutPixel({3, 0}, {3, 21, 11});

    editor.Save();

    return 0;
}
