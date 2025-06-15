# `sw`

[中文](./README.md) | **English**

`sw`, short for `SimpleWindow`, is a C++ GUI framework for building Windows desktop applications. It provides object-oriented encapsulation of Windows standard controls and is suitable for creating simple desktop applications.

## Features

+ **Based on Windows API**:  
  SimpleWindow is a framework based on the Windows API with no additional dependencies.
+ **Supports Properties**:  
  It implements property syntax similar to C#, allowing for intuitive access and modification of object properties.
+ **High DPI Support**:  
  Native support for high DPI using DIP (Device Independent Pixels) as the default unit of measurement.
+ **Flexible Layout**:  
  Implements a layout system similar to WPF, supporting various layouts such as `GridLayout`, `StackLayout`, `DockLayout`, and more.
+ **Routed Events**:  
  Adopts a routed event mechanism, where events can bubble up from the source control to propagate upwards. Event handlers can be registered on controls at different levels.

## Usage

### Clone the Repository

First, clone this repository to your local machine:

```bash
git clone https://github.com/Mzying2001/sw.git
```

#### Method 1: Using Visual Studio

1. Add a reference to the `vs/sw.vcxproj` project in your solution.
2. In your project properties, add the path `sw/inc` to the **Additional Include Directories**.

#### Method 2: Using CMake

1. Add the following to your `CMakeLists.txt`:

    ```cmake
    add_subdirectory(path/to/sw)
    ```

2. Link the `sw` library, for example:

   ```cmake
   target_link_libraries(your_target PRIVATE sw)
   ```

## Quick Start

Here is a SimpleWindow HelloWorld program. For more examples, see [here](https://github.com/Mzying2001/sw/tree/main/examples).

```cpp
#include "SimpleWindow.h"

int wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, INT nCmdShow)
{
    // Window object
    sw::Window mainWindow;

    // Button object
    sw::Button button;

    // Modify the window layout to center the button
    mainWindow.SetLayout<sw::FillLayout>();

    // Modify the button text by assigning a value to the Text property
    button.Text = L"Click Me";

    // Add a button click event handler to show a message box when the button is clicked
    button.AddHandler(sw::ButtonBase_Clicked,
        [](sw::UIElement& sender, sw::RoutedEventArgs& e) {
            sw::MsgBox::Show(L"Hello, SimpleWindow!");
        });

    mainWindow.AddChild(button);
    mainWindow.Show();

    // Start the message loop
    return sw::App::MsgLoop();
}
```

## Documentation

For detailed documentation on SimpleWindow, please visit [mzying2001.github.io/sw](https://mzying2001.github.io/sw).

## License

The SimpleWindow framework is released under the MIT license, allowing you to freely use and modify it in your own projects.

## Contribution

Contributors are welcome to participate in the development and improvement of SimpleWindow. If you find bugs or have suggestions for improvements, please raise an issue or submit a pull request.

## Stargazers over time

[![Stargazers over time](https://starchart.cc/Mzying2001/sw.svg?variant=adaptive)](https://starchart.cc/Mzying2001/sw)
