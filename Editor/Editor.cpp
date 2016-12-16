//
// Created by Raphael DANTZER on 12/15/16.
//

#include "Editor.h"
#include "GlobalInstance.h"
#include "LevelPropertyWindow.h"

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

namespace Kiwi {
    namespace Editor {
        Editor::Editor() : kE::App() {

        }

        void Editor::init() {
            start();

            kE::Asset::Loader loader;

            UserInputListener *mainListener = new UserInputListener;
            kE::Primitive::FPSCamera *camera = new kE::Primitive::FPSCamera(glm::vec3(1.f, 1.f, 1.f),
                                                                            glm::vec3(0.f, 1.f, 0.f));
            kE::Primitive::FPSCameraEventListener *cameraListener = new kE::Primitive::FPSCameraEventListener(camera);
            kE::GUI::ImGuiListener *imGuiListener = new kE::GUI::ImGuiListener;

            _hid->bind(cameraListener);
            _hid->bind(mainListener);
            _hid->bind(imGuiListener);


            kE::Primitive::Mesh cube = loader.createDefaultMesh(kE::Asset::Loader::Type::CUBE);

            kE::Scene::Entity skybox(cube,
                                     new kE::Renderer::CubeMaterial(loader.createCubeMap({
                                                                                                 "./Assets/textures/skybox/right.jpg",
                                                                                                 "./Assets/textures/skybox/left.jpg",
                                                                                                 "./Assets/textures/skybox/top.jpg",
                                                                                                 "./Assets/textures/skybox/bottom.jpg",
                                                                                                 "./Assets/textures/skybox/back.jpg",
                                                                                                 "./Assets/textures/skybox/front.jpg",

                                                                                         })));

            kE::Scene::Actuator skybox_actor;
            skybox.bindActuator(&skybox_actor);

            skybox_actor.setScale(glm::vec3(10.f, 10.f, 10.f))->update();

            kE::Scene::Entity root;

            _level = kE::Scene::Level(root);
            _level.setSkybox(skybox);

            _renderer.bindLevel(_level);
            _renderer.bindCamera(camera);

            _windows.push_back(new EditorWindow);
            _windows.push_back(new LevelPropertyWindow);
        }

        void Editor::loop() {
            _graphics->Update();
            processEvent();
            ImGui_ImplGlfwGL3_NewFrame();

            std::for_each(_windows.begin(), _windows.end(), [](WindowInterface *window){
                window->render();
            });

//            ImGui::ShowTestWindow();

            run();
        }

        void Editor::processEvent() {

            switch (g_globalInstance.state) {
                case State::SCENE_OPENED:
                kE::Scene::Creator creator;
                    g_globalInstance.world = creator.createLevelFromConfig(g_globalInstance.levelConfig);
                    g_globalInstance.state = State::SCENE_LOADED;
                    break;
                default:
                    break;
            }
        }

    }
}
