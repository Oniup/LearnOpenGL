# Learning OpenGL

Followed [LearnOpenGL](https://learnopengl.com) tutorial by [Joey de Vries](http://joeydevries.com/#home)

## Template

```cpp
#include "Common/Context.h"
#include <glad/glad.h>
#include <glm/glm.hpp>

int main()
{
    Context context("Title Name", false);

    // Prep ...

    context.Update([](float delta_time) {
        glClearColor(0.2f, 0.5f, 0.9f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Runtime update ...
    });
}
```
