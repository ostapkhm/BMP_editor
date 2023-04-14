#include "Editor.h"

using namespace std;

int main() {
    srand(time(nullptr));

    MyImage image(1503, 1003);

    Editor editor(&image);
    editor.DrawAxis();

//    editor.DrawLine({-200, 0}, {200, 200}, {113, 155, 173}, 1);
//    editor.DrawLine({200, 100}, {-20, -102}, {44, 15, 13}, 2);
//    editor.DrawLine({250, 0}, {20, -10}, {244, 55, 73}, 1);
//    editor.DrawLine({200, 0}, {200, -150}, {244, 245, 173}, 3);
//    editor.DrawLine({-200, 0}, {-200, 0}, {24, 245, 173}, 3);
    editor.DrawRandomColouredLine({-205, -180}, {-200, 100});

//    editor.DrawRandomColouredLine({-350, -340}, {360, 490}, 2);
    editor.Save("new.bmp");

    return 0;
}
