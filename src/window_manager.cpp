#include "window_manager.hpp"
#include "window.hpp"
#include <algorithm>
#include <cmath>
#include <iostream>

#ifdef WIN32
#include <windows.h>
#else
#include <sys/ioctl.h>
#include <unistd.h>
#endif

WindowManager::WindowManager() {}

std::shared_ptr<Window> WindowManager::create_window(int x, int y, int width, int height, WindowFeatures features) {
    std::shared_ptr<Window> window = std::make_shared<Window>(Window(x, y, width, height, features));
    _windows.push_back(window);
    return window;
}

bool compare_z_index(std::shared_ptr<Window> window1, std::shared_ptr<Window> window2) {
    return window1->z_index() < window2->z_index();
}

int WindowManager::update() {
    std::string new_output_buffer = _output_buffer;

    std::sort(_windows.begin(), _windows.end(), compare_z_index);

    for (std::shared_ptr<Window> window : _windows) {
        int index = 0;

        while (index < window->output_buffer().size() && index < window->width() * window->height()) {
            int x = index % window->width() + window->x();
            int y = std::floor(index / window->width()) + window->y();
            int global_index = x + y * _screen_height;

            new_output_buffer[global_index] = window->output_buffer()[index];
            index++;
        }
    }

    _output_buffer = new_output_buffer;

    std::cout << "\033[1;1H" << _output_buffer;

    return 0;
}

int WindowManager::update_screen_size() {
#ifdef WIN32
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    _screen_width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    _screen_height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
#else
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

    _screen_width = w.ws_col;
    _screen_height = w.ws_row;
#endif

    _output_buffer.resize(_screen_width * _screen_height, ' ');

    return 0;
}
