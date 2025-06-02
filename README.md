# QuatreFoil Engine ⚙️

Welcome to the **QuatreFoil Engine**, a modular 2D game engine built with OpenGL and C++ using modern programming practices for my own education.

This branch contains the full source code for the engine, and example code on how to get up and runninng.

---

## 🧰 Requirements

Make sure you have the following installed:

| Dependency     | Version / Notes                        |
|----------------|----------------------------------------|
| 🛠️ CMake        | v3.15+ (for building the project)       |
| 💻 OpenGL       | 3.3+ Core profile                       |


Below are already packed within the release, so no extra resources required.
| Dependency     | Version / Notes                        |
|----------------|----------------------------------------|
| 🖼️ GLFW        | Provided via `/externals`               |
| ⚙️ GLAD         | Included in the project                 |
| 💼 ImGui        | Already integrated                      |
| 🧠 EnTT         | Header-only ECS, included               |
| 🐧 OS Support   | Only windows has been tested                |

---

## To get started

- Download the **latest** release of the engine.
- Current latest release: [V1.0-alpha](https://github.com/FruitMix22/QuatreFoil/releases/tag/Engine-V1.0_alpha)  
- **Unzip** the zippped folder where you would like your engine to be.

- Run `RunCmake.bat` to build the solution for visual studio.

---

## Requirements to render something
 In the example code it will show how to render a simple rectangle to the screen.
 It also shows the use of shaders, uniforms, and how to use ImGui.

 At minimum to render something you will need:
 - An entry point that creates an instance of the engine, and your game layer.
 - An entity registry.
 - An entity with a renderable component and an RenderLayer component.
   - Attatch a VAO and Shader to this renderable component.
   - The renderlayer component just orders in which entites shoould be rendered.
 - In the render function in your game layer, run the Rendender.

The renderer renders entities by obtaining all entites with a renderable component.

⚠️ ***WARNING***
- All folders are in the correct place, if moved, CMakeLists.txt will need to be updated.

