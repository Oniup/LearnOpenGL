# Learning OpenGL

Followed [LearnOpenGL](https://learnopengl.com) tutorial by [Joey de Vries](http://joeydevries.com/#home)

## Template every main executable file follows

```cpp
#include "Common/Context.h"
#include <glad/glad.h>
#include <glm/glm.hpp>

int main()
{
    Context context(EXEC_NAME, false);

    // Initialization Code...

    while (context.BeginFrame()) {
        glClearColor(0.2f, 0.5f, 0.9f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Graphics/Runtime Code..

        context.EndFrame();
    }
}
```
