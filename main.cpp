#include <iostream>
#include <array>
#include <glm/gtc/type_ptr.hpp>
#include "Engine/App.h"
#include "Engine/Assets/Loader.h"
#include "Engine/Renderer/PhongMaterial.h"
#include "Engine/Renderer/PhongTexturedMaterial.h"
#include "Engine/Renderer/CubeMaterial.h"


namespace kE = Kiwi::Engine;

#define IM_ARRAYSIZE(_ARR)  ((int)(sizeof(_ARR)/sizeof(*_ARR)))

std::array<const char *, 20> type_str = {
        "NONE",
        "WINDOW_MOVED",
        "WINDOW_RESIZED",
        "WINDOW_CLOSED",
        "WINDOW_FOCUSED",
        "WINDOW_DEFOCUSED",
        "WINDOW_ICONIFIED",
        "WINDOW_RESTORED",
        "FRAMEBUFFER_RESIZED",
        "BUTTON_PRESSED",
        "BUTTON_RELEASED",
        "CURSOR_MOVED",
        "CURSOR_ENTERED",
        "CURSOR_LEFT",
        "SCROLLED",
        "KEY_PRESSED",
        "KEY_REPEATED",
        "KEY_RELEASED",
        "CHARACTER_INPUT",
        "FILE_DROPPED"
};

class UserInputListener : public kE::Event::Listener<kE::Event::Type::GLFWEvent> {
public:
    void update(Kiwi::Engine::Event::Type::GLFWEvent &notification) override {
        static bool wireframe = false;

        switch (notification.type) {
            case kE::Event::Type::HumanInteraction::KEY_PRESSED:
                switch (notification.key.key) {
                    case GLFW_KEY_ESCAPE :
                        exit(EXIT_SUCCESS);
                    case GLFW_KEY_1: {
                        if (wireframe)
                            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                        else
                            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                        wireframe = !wireframe;
                    }
                    default:
                        break;
                }
                break;
            case kE::Event::Type::HumanInteraction::FRAMEBUFFER_RESIZED:
                glViewport(0, 0, notification.size.width, notification.size.height);
            default:
                break;
        }
    }
};

class DebugInputListener : public kE::Event::Listener<kE::Event::Type::GLFWEvent> {
public:
    void update(Kiwi::Engine::Event::Type::GLFWEvent &notification) override {
//        ImGui::Text("Event : %s", type_str[static_cast<int>(notification.type)]);
    }
};

class Game : public kE::App {
public:
    Game() : kE::App() {}

    void loop(void) {
        start();

        UserInputListener dummyListener;
        DebugInputListener debugListener;
        kE::GUI::ImGuiListener imguiListener;

        kE::Asset::Loader loader;

        _hid->bind(&debugListener);
        _hid->bind(&dummyListener);
        _hid->bind(&imguiListener);


        kE::Asset::Storage storage;

        kE::Scene::Entity root;
        kE::Primitive::FPSCamera camera(glm::vec3(1.f, 1.f, 1.f), glm::vec3(0.f, 1.f, 0.f));
        kE::Primitive::FPSCameraEventListener cameraListener(&camera);

        _hid->bind(&cameraListener);

        kE::Primitive::Mesh cube = loader.createDefaultMesh(kE::Asset::Loader::Type::CUBE);
        kE::Scene::Entity hyrule = loader.createEntityFromModel("./Assets/models/hyrule_castle/hyrulecastle.obj");
        kE::Scene::Actuator hyrule_actuator;
        hyrule.bindActuator(&hyrule_actuator);
        hyrule_actuator.position(glm::vec3(0.f, 2.f, 0.f))->update();
        kE::Scene::Entity coin = loader.createEntityFromModel("./Assets/models/coin/Coin.obj");
        kE::Scene::Entity sponza = loader.createEntityFromModel("./Assets/models/crytek-sponza/sponza-fix.obj");
//        kE::Scene::Entity bunny = loader.createEntityFromModel("./Assets/models/stanford_bunny.obj");
//
        kE::Renderer::PhongMaterial red_phong;
        red_phong.setColor(glm::vec3(1.0f, 0.f, 0.f));

        kE::Renderer::PhongMaterial green_phong;
        green_phong.setColor(glm::vec3(0.0f, 1.f, 0.f));

        kE::Renderer::PhongMaterial blue_phong;
        blue_phong.setColor(glm::vec3(0.0f, 0.f, 1.f));

        kE::Renderer::PhongTexturedMaterial brick;

        brick.addMap(loader.createMap("./Assets/textures/brick-diffuse.jpg", kE::Renderer::Texture::Type::DIFFUSE));
        brick.addMap(loader.createMap("./Assets/textures/brick-normal.jpg", kE::Renderer::Texture::Type::NORMAL));
        brick.addMap(loader.createMap("./Assets/textures/brick-specular.jpg", kE::Renderer::Texture::Type::SPECULAR));

        kE::Renderer::PhongTexturedMaterial crate;

        crate.addMap(loader.createMap("./Assets/textures/container-diffuse.jpg", kE::Renderer::Texture::Type::DIFFUSE));
        brick.addMap(loader.createMap("./Assets/textures/container-normal.jpg", kE::Renderer::Texture::Type::NORMAL));
        brick.addMap(
                loader.createMap("./Assets/textures/container-specular.jpg", kE::Renderer::Texture::Type::SPECULAR));


        kE::Scene::Actuator coin_actuator;
        coin.bindActuator(&coin_actuator);

        sponza.addChild(coin.getChildren()[0]);
        hyrule.addChild(coin.getChildren()[0]);

        kE::Scene::Entity cube_test;
        cube_test.setChildren({
                                      kE::Scene::Entity(cube, &red_phong, glm::vec3(-1.f, 0.f, 1.f)),
                                      kE::Scene::Entity(cube, &green_phong, glm::vec3(1.f, 0.f, -1.f)),
                                      kE::Scene::Entity(cube, &blue_phong, glm::vec3(1.f, 0.f, 1.f)),
                                      kE::Scene::Entity(cube, &crate, glm::vec3(-1.f, 0.f, -1.f)),
                                      kE::Scene::Entity(cube, &brick, glm::vec3(0.f, 0.f, 0.f))
                              });

        kE::Scene::Actuator cube_mini_scene_actuator;
        cube_test.bindActuator(&cube_mini_scene_actuator);


        kE::Scene::Entity skybox = kE::Scene::Entity(cube,
                                                     new kE::Renderer::CubeMaterial(loader.createCubeMap({
                                                                                                                 "./Assets/textures/skybox/right.jpg",
                                                                                                                 "./Assets/textures/skybox/left.jpg",
                                                                                                                 "./Assets/textures/skybox/top.jpg",
                                                                                                                 "./Assets/textures/skybox/bottom.jpg",
                                                                                                                 "./Assets/textures/skybox/back.jpg",
                                                                                                                 "./Assets/textures/skybox/front.jpg",

                                                                                                         })));

        kE::Scene::Actuator skybox_actuator;
        skybox.bindActuator(&skybox_actuator);

        kE::Scene::Level sponza_level(sponza);
        kE::Scene::Level hyrule_level(hyrule);

        skybox_actuator
                .setScale(glm::vec3(100.f, 100.f, 100.f))
                ->update();

        hyrule_level.setSkybox(skybox);
        sponza_level.setSkybox(skybox);

        _renderer.bindLevel(hyrule_level);
        _renderer.bindCamera(&camera);
        _renderer.bindTarget(kE::Renderer::Target(1280, 800));

        float pos[3] = {0, 1, 0};
        float scale[3] = {1, 1, 1};
        bool rotate = false;

        glfwSwapInterval(1);

        while (1) {

            ImGui_ImplGlfwGL3_NewFrame();
            bool gui_open = true;

            ImGui::Begin("Tools", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.f / ImGui::GetIO().Framerate,
                        ImGui::GetIO().Framerate);

            ImGui::Separator();

            ImGui::Text("Camera position : %f %f %f", camera.getPosition().x, camera.getPosition().y,
                        camera.getPosition().z);
            if (ImGui::Button("Reset camera"))
                camera.setPosition(glm::vec3(1.f, 1.f, 1.f));

            ImGui::Separator();

            ImGui::Text("Actuator test - Coin");
            ImGui::DragFloat3("Position", pos, 0.f, -3.f, 3.f, "%.2f");
            ImGui::DragFloat3("Scale", scale, 1.f, 1.f, 5.f, "%.2f");

            ImGui::Checkbox("Rotate", &rotate);

            ImGui::Separator();

            ImGui::Text("Change scene");
            if (ImGui::Button("Hyrule"))
                _renderer.bindLevel(hyrule_level);
            ImGui::SameLine();
            if (ImGui::Button("Sponza"))
                _renderer.bindLevel(sponza_level);

            ImGui::Separator();

            ImGui::Text("Keys\n"
                                "1     - toggle wireframe\n"
                                "WASD  - move and strafe\n"
                                "Space - stop mouse tracking");

            ImGui::End();

            if (rotate)
                coin_actuator.rotate(glm::vec3(0.f, 1.f, 0.f), glfwGetTime());
            coin_actuator
                    .position(glm::vec3(pos[0], pos[1], pos[2]))
                    ->setScale(glm::vec3(scale[0] * 2, scale[1] * 2, scale[2] * 2))
                    ->update();

            run();
        }
    }

private:
    std::unique_ptr<VFS> _vfs;
};

int main(void) {
    Game *game = new Game();

    game->loop();
    return 0;
}