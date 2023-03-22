#include "Editor.h"

using namespace std;

int main() {
    MyImage image(35, 25, "new.bmp");

    Editor editor(&image);
    editor.DrawAxis();

    editor.DrawLine({-1, -1}, {13, -2});

    editor.Save();

    return 0;
}
