#include <iostream>
#include <array>
#include "Engine/App.h"
#include "Engine/Event/Type.h"
#include "Engine/Event/Listener.h"
#include "Engine/Event/Dispatcher.h"
#include "Engine/Event/GLFWNotifier.h"
#include "Engine/Event/CoreNotifier.h"
#include "Engine/Primitives/Mesh.h"
#include "Engine/Assets/Loader.h"
#include "Engine/Scene/Level.h"
#include "Engine/Assets/Storage.h"
#include "Engine/Renderer/PhongMaterial.h"
#include "Engine/Renderer/PhongTexturedMaterial.h"
#include "Engine/Renderer/CubeMaterial.h"
#include "Engine/Scene/Actuator.h"


namespace kE = Kiwi::Engine;

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
//        std::cout << type_str[static_cast<int>(notification.type)] << std::endl;
    }
};

class Game : public kE::App {
public:
    Game() : kE::App() {}

    void loop(void) {
        start();

        UserInputListener dummyListener;
        DebugInputListener debugListener;
        kE::Asset::Loader loader;

        _hid->bind(&debugListener);
        _hid->bind(&dummyListener);


        kE::Asset::Storage storage;

        kE::Scene::Entity root;
        kE::Primitive::FPSCamera camera(glm::vec3(1.f, 1.f, 1.f), glm::vec3(0.f, 1.f, 0.f));
        kE::Primitive::FPSCameraEventListener cameraListener(&camera);

        _hid->bind(&cameraListener);

        kE::Primitive::Mesh cube = loader.createDefaultMesh(kE::Asset::Loader::Type::CUBE);
        kE::Scene::Entity coin = loader.createEntityFromModel("./Assets/models/coin/Coin.obj");
        kE::Scene::Entity test_area = loader.createEntityFromModel("./Assets/models/scene.obj");
//        kE::Scene::Entity sponza = loader.createEntityFromModel("./Assets/models/crytek-sponza/sponza-fix.obj");
//        kE::Scene::Entity sibenik = loader.createEntityFromModel("./Assets/models/sibenik/sibenik.obj");
//        kE::Scene::Entity zelda = loader.createEntityFromModel("./Assets/models/twin_house/Inside.obj");
//        kE::Scene::Entity bunny = loader.createEntityFromModel("./Assets/models/stanford_bunny.obj");
//
        kE::Scene::Entity scene;

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

//        sponza.addChild(bunny);

        test_area.addChild(scene);

        kE::Scene::Entity brick_cube = kE::Scene::Entity(cube, &brick);
        kE::Scene::Actuator brick_actuator, coin_actuator;

        brick_cube.bindActuator(&brick_actuator);
        coin.bindActuator(&coin_actuator);

        scene.addChild(brick_cube);
        scene.addChild(coin.getChildren()[0]);

        kE::Scene::Entity skybox = kE::Scene::Entity(loader.createMeshFromVertices({-10.0f, 10.0f, -10.0f,
                                                                                    -10.0f, -10.0f, -10.0f,
                                                                                    10.0f, -10.0f, -10.0f,
                                                                                    10.0f, -10.0f, -10.0f,
                                                                                    10.0f, 10.0f, -10.0f,
                                                                                    -10.0f, 10.0f, -10.0f,

                                                                                    -10.0f, -10.0f, 10.0f,
                                                                                    -10.0f, -10.0f, -10.0f,
                                                                                    -10.0f, 10.0f, -10.0f,
                                                                                    -10.0f, 10.0f, -10.0f,
                                                                                    -10.0f, 10.0f, 10.0f,
                                                                                    -10.0f, -10.0f, 10.0f,

                                                                                    10.0f, -10.0f, -10.0f,
                                                                                    10.0f, -10.0f, 10.0f,
                                                                                    10.0f, 10.0f, 10.0f,
                                                                                    10.0f, 10.0f, 10.0f,
                                                                                    10.0f, 10.0f, -10.0f,
                                                                                    10.0f, -10.0f, -10.0f,

                                                                                    -10.0f, -10.0f, 10.0f,
                                                                                    -10.0f, 10.0f, 10.0f,
                                                                                    10.0f, 10.0f, 10.0f,
                                                                                    10.0f, 10.0f, 10.0f,
                                                                                    10.0f, -10.0f, 10.0f,
                                                                                    -10.0f, -10.0f, 10.0f,

                                                                                    -10.0f, 10.0f, -10.0f,
                                                                                    10.0f, 10.0f, -10.0f,
                                                                                    10.0f, 10.0f, 10.0f,
                                                                                    10.0f, 10.0f, 10.0f,
                                                                                    -10.0f, 10.0f, 10.0f,
                                                                                    -10.0f, 10.0f, -10.0f,

                                                                                    -10.0f, -10.0f, -10.0f,
                                                                                    -10.0f, -10.0f, 10.0f,
                                                                                    10.0f, -10.0f, -10.0f,
                                                                                    10.0f, -10.0f, -10.0f,
                                                                                    -10.0f, -10.0f, 10.0f,
                                                                                    10.0f, -10.0f, 10.0f}),
                                                     new kE::Renderer::CubeMaterial(loader.createCubeMap({
                                                                                                                 "./Assets/textures/skybox/right.jpg",
                                                                                                                 "./Assets/textures/skybox/left.jpg",
                                                                                                                 "./Assets/textures/skybox/top.jpg",
                                                                                                                 "./Assets/textures/skybox/bottom.jpg",
                                                                                                                 "./Assets/textures/skybox/back.jpg",
                                                                                                                 "./Assets/textures/skybox/front.jpg",

                                                                                                         })));

        kE::Scene::Level l(scene);

        l.setSkybox(skybox);

        _renderer.bindLevel(l);
        _renderer.bindCamera(&camera);
        _renderer.bindTarget(kE::Renderer::Target(1280, 800));

        glEnable(GL_MULTISAMPLE);

        while (1) {
            brick_actuator
                    .position(glm::vec3(0.f, 1.f, 0.f))
                    ->rotate(glm::vec3(0.f, 1.0f, 0.f), 45)
                    ->update();
            coin_actuator
                    .position(glm::vec3(0.f, 2.f, 0.f))
                    ->setScale(glm::vec3(2.f))
                    ->rotate(glm::vec3(0.f, 1.f, 0.f), glfwGetTime())
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