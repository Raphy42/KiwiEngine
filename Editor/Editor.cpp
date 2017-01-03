//
// Created by Raphael DANTZER on 12/15/16.
//

#include "Editor.h"
#include "LevelPropertyWindow.h"
#include "ToolsWindow.h"
#include <boost/archive/binary_oarchive.hpp>

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

            _renderer.bindCamera(camera);

            _windows.push_back(new EditorWindow);
            _windows.push_back(new LevelPropertyWindow);
            _windows.push_back(new ToolsWindow(camera));
        }

        void Editor::loop() {
            _graph = GlobalInstance::get().graph;
            _graphics->Update();
            processEvent();
            ImGui_ImplGlfwGL3_NewFrame();
            ImGuizmo::BeginFrame();
            ImGui::GetIO().MouseDrawCursor = true;

            std::for_each(_windows.begin(), _windows.end(), [](WindowInterface *window) {
                window->render();
            });

            _renderer.updateGraphMaterials(_graph); //todo extract to Engine::run
            _renderer.renderGraph(_graph);
            run();
        }

        void Editor::processEvent() {

            switch (GlobalInstance::get().state) {
                case State::SCENE_OPENED:
                    kE::Scene::Creator creator;
                    GlobalInstance::get().world = creator.createLevelFromConfig(GlobalInstance::get().levelConfig);
                    GlobalInstance::get().state = State::SCENE_LOADED;
                    _renderer.bindLevel(GlobalInstance::get().world);
                    break;
                default:
                    break;
            }
        }

    }
}
