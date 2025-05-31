#include <gtest/gtest.h>
#include "Core/include/EngineCore.hpp"
#include "Core/include/Layer.hpp"

class MyTestLayer : public Layer {
public:
    void OnAttach() override { std::cout << "Layer Attached\n"; }

    void OnStart() override { std::cout << "Layer Started\n"; }

    void OnUpdate() override {}

    void OnRender() override 
    {
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void OnImGuiRender() override
    {
        ImGui::Begin("Debug Window");
        ImGui::Text("Hello from ImGui!");
        ImGui::End();
    }
};

TEST(EngineCoreTest, testLayer)
{
    EngineCore engine("Engine");

    std::shared_ptr<MyTestLayer> testLayer = std::make_shared <MyTestLayer>();
    engine.SetLayer(testLayer);

    // Only gets to here if doesnt crash
    EXPECT_TRUE(true);
}

TEST(EngineCoreTest, loadEngine)
{
    EngineCore engine("Test");

    EXPECT_TRUE(engine.getWindow() != nullptr);
}

TEST(EngineCoreTest, doesUnloadWork)
{
    EngineCore engine("Test");

    engine.unloadEngine();

    // Expect the window to be null
    EXPECT_TRUE(engine.getWindow() == nullptr);
}

