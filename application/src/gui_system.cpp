//
// Created by naszly on 8/28/22.
//

#include "gui_system.h"
#include "imgui_impl_opengl3.h"
#include "core/mouse_event.h"
#include "core/key_event.h"

static ImGuiKey keyCodeToImGuiKey(KeyCode keyCode);

GuiSystem::GuiSystem(Context &context, Input &input) : System(context, input) {
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    ImGuiStyle &style = ImGui::GetStyle();
    style.Alpha = 0.9f;
    style.Colors[ImGuiCol_WindowBg].w = 0.5f;

    ImGui_ImplOpenGL3_Init("#version 330");
}

void GuiSystem::render() {
    ImGuiIO &io = ImGui::GetIO();
    int width, height;
    context.getSize(&width, &height);
    io.DisplaySize = ImVec2(static_cast<float>(width), static_cast<float>(height));

    setMouseCursorShape(ImGui::GetMouseCursor());

    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui::NewFrame();


    ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(),
                                 ImGuiDockNodeFlags_PassthruCentralNode | ImGuiDockNodeFlags_NoDockingInCentralNode);

    ImGui::ShowDemoWindow();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

}

void GuiSystem::onEvent(Event &event) {
    EventDispatcher dispatcher(event);
    ImGuiIO &io = ImGui::GetIO();

    dispatcher.dispatch<KeyPressedEvent>([&](KeyPressedEvent &event) {
        auto key = keyCodeToImGuiKey(event.getKeyCode());
        io.AddKeyEvent(key, true);
        return io.WantCaptureKeyboard;
    });

    dispatcher.dispatch<KeyReleasedEvent>([&](KeyReleasedEvent &event) {
        auto key = keyCodeToImGuiKey(event.getKeyCode());
        io.AddKeyEvent(key, false);
        return io.WantCaptureKeyboard;
    });

    dispatcher.dispatch<MouseMovedEvent>([&](MouseMovedEvent &event) {
        io.AddMousePosEvent(event.getX(), event.getY());
        return false;
    });

    dispatcher.dispatch<MouseButtonPressedEvent>([&](MouseButtonPressedEvent &event) {
        io.AddMouseButtonEvent(static_cast<int>(event.getMouseButton()), true);
        return io.WantCaptureMouse;
    });

    dispatcher.dispatch<MouseButtonReleasedEvent>([&](MouseButtonReleasedEvent &event) {
        io.AddMouseButtonEvent(static_cast<int>(event.getMouseButton()), false);
        return io.WantCaptureMouse;
    });

    dispatcher.dispatch<MouseScrolledEvent>([&](MouseScrolledEvent &event) {
        io.AddMouseWheelEvent(event.getXOffset(), event.getYOffset());
        return io.WantCaptureMouse;
    });

    dispatcher.dispatch<KeyTypedEvent>([&](KeyTypedEvent &event) {
        io.AddInputCharacter(static_cast<unsigned int>(event.getKeyCode()));
        return io.WantCaptureKeyboard;
    });
}

void GuiSystem::setMouseCursorShape(ImGuiMouseCursor cursorShape) {
    switch (cursorShape) {
        case ImGuiMouseCursor_Arrow:
            input.setCursorShape(CursorShape::Arrow);
            break;
        case ImGuiMouseCursor_TextInput:
            input.setCursorShape(CursorShape::IBeam);
            break;
        case ImGuiMouseCursor_ResizeAll:
            input.setCursorShape(CursorShape::ResizeAll);
            break;
        case ImGuiMouseCursor_ResizeNS:
            input.setCursorShape(CursorShape::ResizeNorthSouth);
            break;
        case ImGuiMouseCursor_ResizeEW:
            input.setCursorShape(CursorShape::ResizeEastWest);
            break;
        case ImGuiMouseCursor_ResizeNESW:
            input.setCursorShape(CursorShape::ResizeNorthEastSouthWest);
            break;
        case ImGuiMouseCursor_ResizeNWSE:
            input.setCursorShape(CursorShape::ResizeNorthWestSouthEast);
            break;
        case ImGuiMouseCursor_Hand:
            input.setCursorShape(CursorShape::Hand);
            break;
        case ImGuiMouseCursor_NotAllowed:
            input.setCursorShape(CursorShape::NotAllowed);
            break;
        default:
            input.setCursorShape(CursorShape::Arrow);
            break;
    }
}

static ImGuiKey keyCodeToImGuiKey(KeyCode keyCode) {
    switch (keyCode) {
        case KeyCode::Tab:
            return ImGuiKey_Tab;
        case KeyCode::Left:
            return ImGuiKey_LeftArrow;
        case KeyCode::Right:
            return ImGuiKey_RightArrow;
        case KeyCode::Up:
            return ImGuiKey_UpArrow;
        case KeyCode::Down:
            return ImGuiKey_DownArrow;
        case KeyCode::PageUp:
            return ImGuiKey_PageUp;
        case KeyCode::PageDown:
            return ImGuiKey_PageDown;
        case KeyCode::Home:
            return ImGuiKey_Home;
        case KeyCode::End:
            return ImGuiKey_End;
        case KeyCode::Insert:
            return ImGuiKey_Insert;
        case KeyCode::Delete:
            return ImGuiKey_Delete;
        case KeyCode::Backspace:
            return ImGuiKey_Backspace;
        case KeyCode::Space:
            return ImGuiKey_Space;
        case KeyCode::Enter:
            return ImGuiKey_Enter;
        case KeyCode::Escape:
            return ImGuiKey_Escape;
        case KeyCode::Apostrophe:
            return ImGuiKey_Apostrophe;
        case KeyCode::Comma:
            return ImGuiKey_Comma;
        case KeyCode::Minus:
            return ImGuiKey_Minus;
        case KeyCode::Period:
            return ImGuiKey_Period;
        case KeyCode::Slash:
            return ImGuiKey_Slash;
        case KeyCode::Semicolon:
            return ImGuiKey_Semicolon;
        case KeyCode::Equal:
            return ImGuiKey_Equal;
        case KeyCode::LeftBracket:
            return ImGuiKey_LeftBracket;
        case KeyCode::Backslash:
            return ImGuiKey_Backslash;
        case KeyCode::RightBracket:
            return ImGuiKey_RightBracket;
        case KeyCode::GraveAccent:
            return ImGuiKey_GraveAccent;
        case KeyCode::CapsLock:
            return ImGuiKey_CapsLock;
        case KeyCode::ScrollLock:
            return ImGuiKey_ScrollLock;
        case KeyCode::NumLock:
            return ImGuiKey_NumLock;
        case KeyCode::PrintScreen:
            return ImGuiKey_PrintScreen;
        case KeyCode::Pause:
            return ImGuiKey_Pause;
        case KeyCode::KP0:
            return ImGuiKey_Keypad0;
        case KeyCode::KP1:
            return ImGuiKey_Keypad1;
        case KeyCode::KP2:
            return ImGuiKey_Keypad2;
        case KeyCode::KP3:
            return ImGuiKey_Keypad3;
        case KeyCode::KP4:
            return ImGuiKey_Keypad4;
        case KeyCode::KP5:
            return ImGuiKey_Keypad5;
        case KeyCode::KP6:
            return ImGuiKey_Keypad6;
        case KeyCode::KP7:
            return ImGuiKey_Keypad7;
        case KeyCode::KP8:
            return ImGuiKey_Keypad8;
        case KeyCode::KP9:
            return ImGuiKey_Keypad9;
        case KeyCode::KPDecimal:
            return ImGuiKey_KeypadDecimal;
        case KeyCode::KPDivide:
            return ImGuiKey_KeypadDivide;
        case KeyCode::KPMultiply:
            return ImGuiKey_KeypadMultiply;
        case KeyCode::KPSubtract:
            return ImGuiKey_KeypadSubtract;
        case KeyCode::KPAdd:
            return ImGuiKey_KeypadAdd;
        case KeyCode::KPEnter:
            return ImGuiKey_KeypadEnter;
        case KeyCode::KPEqual:
            return ImGuiKey_KeypadEqual;
        case KeyCode::LeftShift:
            return ImGuiKey_LeftShift;
        case KeyCode::LeftControl:
            return ImGuiKey_LeftCtrl;
        case KeyCode::LeftAlt:
            return ImGuiKey_LeftAlt;
        case KeyCode::LeftSuper:
            return ImGuiKey_LeftSuper;
        case KeyCode::RightShift:
            return ImGuiKey_RightShift;
        case KeyCode::RightControl:
            return ImGuiKey_RightCtrl;
        case KeyCode::RightAlt:
            return ImGuiKey_RightAlt;
        case KeyCode::RightSuper:
            return ImGuiKey_RightSuper;
        case KeyCode::Menu:
            return ImGuiKey_Menu;
        case KeyCode::N0:
            return ImGuiKey_0;
        case KeyCode::N1:
            return ImGuiKey_1;
        case KeyCode::N2:
            return ImGuiKey_2;
        case KeyCode::N3:
            return ImGuiKey_3;
        case KeyCode::N4:
            return ImGuiKey_4;
        case KeyCode::N5:
            return ImGuiKey_5;
        case KeyCode::N6:
            return ImGuiKey_6;
        case KeyCode::N7:
            return ImGuiKey_7;
        case KeyCode::N8:
            return ImGuiKey_8;
        case KeyCode::N9:
            return ImGuiKey_9;
        case KeyCode::A:
            return ImGuiKey_A;
        case KeyCode::B:
            return ImGuiKey_B;
        case KeyCode::C:
            return ImGuiKey_C;
        case KeyCode::D:
            return ImGuiKey_D;
        case KeyCode::E:
            return ImGuiKey_E;
        case KeyCode::F:
            return ImGuiKey_F;
        case KeyCode::G:
            return ImGuiKey_G;
        case KeyCode::H:
            return ImGuiKey_H;
        case KeyCode::I:
            return ImGuiKey_I;
        case KeyCode::J:
            return ImGuiKey_J;
        case KeyCode::K:
            return ImGuiKey_K;
        case KeyCode::L:
            return ImGuiKey_L;
        case KeyCode::M:
            return ImGuiKey_M;
        case KeyCode::N:
            return ImGuiKey_N;
        case KeyCode::O:
            return ImGuiKey_O;
        case KeyCode::P:
            return ImGuiKey_P;
        case KeyCode::Q:
            return ImGuiKey_Q;
        case KeyCode::R:
            return ImGuiKey_R;
        case KeyCode::S:
            return ImGuiKey_S;
        case KeyCode::T:
            return ImGuiKey_T;
        case KeyCode::U:
            return ImGuiKey_U;
        case KeyCode::V:
            return ImGuiKey_V;
        case KeyCode::W:
            return ImGuiKey_W;
        case KeyCode::X:
            return ImGuiKey_X;
        case KeyCode::Y:
            return ImGuiKey_Y;
        case KeyCode::Z:
            return ImGuiKey_Z;
        case KeyCode::F1:
            return ImGuiKey_F1;
        case KeyCode::F2:
            return ImGuiKey_F2;
        case KeyCode::F3:
            return ImGuiKey_F3;
        case KeyCode::F4:
            return ImGuiKey_F4;
        case KeyCode::F5:
            return ImGuiKey_F5;
        case KeyCode::F6:
            return ImGuiKey_F6;
        case KeyCode::F7:
            return ImGuiKey_F7;
        case KeyCode::F8:
            return ImGuiKey_F8;
        case KeyCode::F9:
            return ImGuiKey_F9;
        case KeyCode::F10:
            return ImGuiKey_F10;
        case KeyCode::F11:
            return ImGuiKey_F11;
        case KeyCode::F12:
            return ImGuiKey_F12;
        default:
            return ImGuiKey_None;
    }
}