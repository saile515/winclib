#pragma once

#include "window.hpp"
#include <memory>
#include <string>
#include <vector>

class WindowManager {
public:
    WindowManager();

    const std::string &output_buffer() const { return _output_buffer; };

    std::shared_ptr<Window> create_window(int x, int y, int width, int height, WindowFeatures features);
    int update();
    int update_screen_size();

private:
    std::vector<std::shared_ptr<Window>> _windows;
    std::string _output_buffer;
    int _screen_width;
    int _screen_height;
};
