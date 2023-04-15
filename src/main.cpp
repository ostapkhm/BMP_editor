#include <memory>

#include "Editor/Editor.h"

using namespace std;

int main() {
    srand(time(nullptr));

    std::unique_ptr<MyImage> image(MyImage::CreateBlank(2045, 2056));

    Editor editor(image.get());
    editor.DrawAxis();
    //editor.DrawRandomColouredLine({-205, -180}, {200, 100});
    editor.DrawRandomColouredLine({-300, -340}, {-360, 490}, 2);
    editor.Save("new.bmp");

    return 0;
}
