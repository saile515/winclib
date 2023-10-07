#pragma once

#include <string>
#include <vector>

struct CharChange {
    int x;
    int y;
    char value;
};

struct WindowFeatures {};

class Window {
public:
    Window(int x, int y, int width, int height, WindowFeatures features);

    const int &width() const { return _width; };
    const int &height() const { return _height; };
    const int &inner_width() const { return _inner_width; };
    const int &inner_height() const { return _inner_height; }
    const int &x() const { return _x; };
    const int &y() const { return _y; };
    const int &z_index() const { return _z_index; };
    const std::string &output_buffer() const { return _output_buffer; };

    int set_char(int x, int y, char value);
    int set(std::string value);
    int flush_change_buffer();

private:
    std::string _output_buffer;
    std::vector<CharChange> _change_buffer;
    int _width;
    int _height;
    int _inner_width;
    int _inner_height;
    int _x;
    int _y;
    int _z_index;
};
