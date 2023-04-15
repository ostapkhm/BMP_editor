#include <memory>

#include "Editor/Editor.h"

using namespace std;

int main() {
    std::unique_ptr<MyImage> image(MyImage::CreateBlank(545, 556));

    Editor editor(image.get());
    editor.DrawAxis();
    editor.DrawLine({100, 100}, {-40, 40}, {123, 213, 134});
    editor.DrawRandomColouredLine({-100, -120}, {-160, -190});
    editor.Save("new.bmp");

    return 0;
}
