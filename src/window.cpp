#include "window.hpp"

Window::Window(int x, int y, int width, int height, WindowFeatures features) : _output_buffer(width * height, ' ') {
    _x = x;
    _y = y;
    _width = width;
    _height = height;
    _inner_width = width;
    _inner_height = height;
}

int Window::set_char(int x, int y, char value) {
    _change_buffer.push_back(CharChange(x, y, value));
    return 0;
}

int Window::set(std::string value) {
    _output_buffer = value;
    _output_buffer.resize(_width * _height, ' ');

    return 0;
}

int Window::flush_change_buffer() {
    std::string new_output_buffer = _output_buffer;

    for (CharChange &change : _change_buffer) {
        new_output_buffer[change.x + change.y * _width] = change.value;
    }

    _change_buffer.clear();

    _output_buffer = new_output_buffer;

    return 0;
}
