//
// Created by naszly on 8/28/22.
//

#ifndef APPLICATION_SRC_GUI_SYSTEM_H
#define APPLICATION_SRC_GUI_SYSTEM_H

#include <ecs/system.h>
#include <imgui.h>

class GuiSystem : public System {
public:
    GuiSystem(Context &context, Input &input);

    ~GuiSystem() override = default;

    void render() override;

    //void update(float deltaTime) override;

    void onEvent(Event &event) override;
private:
    void setMouseCursorShape(ImGuiMouseCursor cursorShape);
};


#endif //APPLICATION_SRC_GUI_SYSTEM_H
