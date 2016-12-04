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
        switch (notification.type) {
            case kE::Event::Type::HumanInteraction::KEY_PRESSED:
                switch (notification.key.key) {
                    case GLFW_KEY_ESCAPE :
                        exit(EXIT_SUCCESS);
                    default:
                        break;
                }
                break;
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

        kE::Scene::Level level(new kE::Scene::Entity);
        kE::Primitive::FPSCamera camera(glm::vec3(1.f, 1.f, 1.f), glm::vec3(0.f, 1.f, 0.f));
        kE::Primitive::FPSCameraEventListener cameraListener(&camera);

        _hid->bind(&cameraListener);

//        kE::Renderer::Material chien_de_prairie(
//                loader.createTexture(kE::Asset::Loader::Target::FLAT, "./Assets/textures/prairie-dog.jpg"));
//
//        kE::Renderer::Material ponpon(loader.createTexture(
//                kE::Asset::Loader::Target::FLAT,
//                "./Assets/textures/ponpon.png"),
//                                      kE::Renderer::Material::Type::TEST);
//
//        kE::Renderer::Material crate(loader.createTexture(
//                kE::Asset::Loader::Target::FLAT,
//                "./Assets/textures/container.jpg"),
//                                      kE::Renderer::Material::Type::TEST);
//
//        _creator.createLevelFromConfig(Kiwi::Core::JSONConfig("./Assets/levels/test.json"));
//
//        kE::Renderer::Material basic_light(kE::Renderer::Material::Type::BASIC_LIGHTING);
//
        kE::Primitive::Mesh cube = loader.createDefaultMesh(kE::Asset::Loader::Type::CUBE);
//        kE::Primitive::Mesh plane = loader.createDefaultMesh(kE::Asset::Loader::Type::PLANE);
//        kE::Scene::Entity mitsuba = loader.createEntityFromModel("./Assets/models/mitsuba/mitsuba.obj");
//                kE::Scene::Entity sponza = loader.createEntityFromModel("./Assets/models/crytek-sponza/sponza-fix.obj");
//        kE::Scene::Entity sibenik = loader.createEntityFromModel("./Assets/models/sibenik/sibenik.obj");
//
//        level.getScene()->addChild(mitsuba);
//            level.getScene()->addChild(sponza);
//        level.getScene()->addChild(sibenik);

        kE::Renderer::PhongMaterial red_phong;
        red_phong.setColor(glm::vec3(1.0f, 0.f, 0.f));
        red_phong.setParameter("shininess", glm::vec3(1.0f, 0.f, 0.f));

        kE::Renderer::PhongMaterial green_phong;
        green_phong.setColor(glm::vec3(0.0f, 1.f, 0.f));

        kE::Renderer::PhongMaterial blue_phong;
        blue_phong.setColor(glm::vec3(0.0f, 0.f, 1.f));

        kE::Renderer::PhongMaterial phong;

        level.getScene()->addChild(kE::Scene::Entity(cube, &red_phong, glm::vec3(-1.f, 0.f, 1.f)));
        level.getScene()->addChild(kE::Scene::Entity(cube, &green_phong, glm::vec3(1.f, 0.f, -1.f)));
        level.getScene()->addChild(kE::Scene::Entity(cube, &blue_phong, glm::vec3(1.f, 0.f, 1.f)));
        level.getScene()->addChild(kE::Scene::Entity(cube, &phong, glm::vec3(-1.f, 0.f, -1.f)));

        _renderer.bindLevel(level);
        _renderer.bindCamera(&camera);
        _renderer.bindTarget(kE::Renderer::Target(1280, 800));

        while (1) {
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