#include "Editor.h"

using namespace std;

int main() {
    MyImage image(15, 15, "new.bmp");

    Editor editor(&image);
    editor.DrawAxis();

    editor.PutPixel({2, 5}, {255, 0, 0});

    editor.Save();

    return 0;
}
