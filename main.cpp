#include "Editor.h"

using namespace std;

int main() {
    srand(time(nullptr));

    MyImage image(1503, 1003, "new.bmp");

    Editor editor(&image);
    editor.DrawAxis();

    editor.DrawLine({-50, -150}, {100, -102}, {123, 0, 123}, 3);
    editor.DrawLine({50, 250}, {-100, -102}, {13, 213, 13}, 3);
    editor.DrawLine({-50, 150}, {-100, -102}, {0, 13, 93}, 6);
    editor.DrawLine({50, -150}, {100, 102},{113, 255, 73}, 3);


    editor.DrawRandomColouredLine({-350, -340}, {360, 490}, 5);
    editor.Save();

    return 0;
}
