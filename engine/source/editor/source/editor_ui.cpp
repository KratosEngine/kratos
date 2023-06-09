
#include "editor/include/editor_ui.h"

#include "runtime/function/application/window_system.h"
#include "editor/include/editor_global_context.h"

#include <imgui.h>
#include <imgui_internal.h>
// #include <stb_image.h>

namespace Kratos
{

    inline void windowContentScaleUpdate(float scale)
    {
#if defined(__GNUC__) && defined(__MACH__)
        float font_scale = fmaxf(1.0f, scale);
        ImGui::GetIO().FontGlobalScale = 1.0f / font_scale;
#endif
        // TOOD: Reload fonts if DPI scale is larger than previous font loading DPI scale
    }

    inline void windowContentScaleCallback(GLFWwindow *window, float x_scale, float y_scale)
    {
        windowContentScaleUpdate(fmaxf(x_scale, y_scale));
    }

    EditorUI::EditorUI()
    {
    }
    EditorUI::~EditorUI()
    {
    }

    void EditorUI::initialize(ApplicationUIInitInfo init_info)
    {
        // create imgui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();

        // set ui content scale
        float x_scale, y_scale;
        glfwGetWindowContentScale(init_info.window_system->getWindow(), &x_scale, &y_scale);
        float content_scale = fmaxf(1.0f, fmaxf(x_scale, y_scale));
        windowContentScaleUpdate(content_scale);
        glfwSetWindowContentScaleCallback(init_info.window_system->getWindow(), windowContentScaleCallback);

        // load font for imgui
        // todo zxs

        ImGuiStyle &style = ImGui::GetStyle();
        style.WindowPadding = ImVec2(1.0, 0);
        style.FramePadding = ImVec2(14.0, 2.0f);
        style.ChildBorderSize = 0.0f;
        style.FrameRounding = 5.0f;
        style.FrameBorderSize = 1.5f;

        // set imgui color style
        setUIColorStyle();

        // setup window icon
        // todo zxs

    }

    void EditorUI::preRender()
    {
        showEditorUI();
    }

    void EditorUI::setUIColorStyle()
    {
        ImGuiStyle *style = &ImGui::GetStyle();
        ImVec4 *colors = style->Colors;

        colors[ImGuiCol_Text] = ImVec4(0.4745f, 0.4745f, 0.4745f, 1.00f);
        colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
        colors[ImGuiCol_WindowBg] = ImVec4(0.0078f, 0.0078f, 0.0078f, 1.00f);
        colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
        colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
        colors[ImGuiCol_Border] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
        colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
        colors[ImGuiCol_FrameBg] = ImVec4(0.047f, 0.047f, 0.047f, 0.5411f);
        colors[ImGuiCol_FrameBgHovered] = ImVec4(0.196f, 0.196f, 0.196f, 0.40f);
        colors[ImGuiCol_FrameBgActive] = ImVec4(0.294f, 0.294f, 0.294f, 0.67f);
        colors[ImGuiCol_TitleBg] = ImVec4(0.0039f, 0.0039f, 0.0039f, 1.00f);
        colors[ImGuiCol_TitleBgActive] = ImVec4(0.0039f, 0.0039f, 0.0039f, 1.00f);
        colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.50f);
        colors[ImGuiCol_MenuBarBg] = ImVec4(0.0f, 0.0f, 0.0f, 1.00f);
        colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
        colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
        colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
        colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
        colors[ImGuiCol_CheckMark] = ImVec4(93.0f / 255.0f, 10.0f / 255.0f, 66.0f / 255.0f, 1.00f);
        colors[ImGuiCol_SliderGrab] = colors[ImGuiCol_CheckMark];
        colors[ImGuiCol_SliderGrabActive] = ImVec4(0.3647f, 0.0392f, 0.2588f, 0.50f);
        colors[ImGuiCol_Button] = ImVec4(0.0117f, 0.0117f, 0.0117f, 1.00f);
        colors[ImGuiCol_ButtonHovered] = ImVec4(0.0235f, 0.0235f, 0.0235f, 1.00f);
        colors[ImGuiCol_ButtonActive] = ImVec4(0.0353f, 0.0196f, 0.0235f, 1.00f);
        colors[ImGuiCol_Header] = ImVec4(0.1137f, 0.0235f, 0.0745f, 0.588f);
        colors[ImGuiCol_HeaderHovered] = ImVec4(5.0f / 255.0f, 5.0f / 255.0f, 5.0f / 255.0f, 1.00f);
        colors[ImGuiCol_HeaderActive] = ImVec4(0.0f, 0.0f, 0.0f, 1.00f);
        colors[ImGuiCol_Separator] = ImVec4(0.0f, 0.0f, 0.0f, 0.50f);
        colors[ImGuiCol_SeparatorHovered] = ImVec4(45.0f / 255.0f, 7.0f / 255.0f, 26.0f / 255.0f, 1.00f);
        colors[ImGuiCol_SeparatorActive] = ImVec4(45.0f / 255.0f, 7.0f / 255.0f, 26.0f / 255.0f, 1.00f);
        colors[ImGuiCol_ResizeGrip] = ImVec4(0.26f, 0.59f, 0.98f, 0.20f);
        colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
        colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
        colors[ImGuiCol_Tab] = ImVec4(6.0f / 255.0f, 6.0f / 255.0f, 8.0f / 255.0f, 1.00f);
        colors[ImGuiCol_TabHovered] = ImVec4(45.0f / 255.0f, 7.0f / 255.0f, 26.0f / 255.0f, 150.0f / 255.0f);
        colors[ImGuiCol_TabActive] = ImVec4(47.0f / 255.0f, 6.0f / 255.0f, 29.0f / 255.0f, 1.0f);
        colors[ImGuiCol_TabUnfocused] = ImVec4(45.0f / 255.0f, 7.0f / 255.0f, 26.0f / 255.0f, 25.0f / 255.0f);
        colors[ImGuiCol_TabUnfocusedActive] = ImVec4(6.0f / 255.0f, 6.0f / 255.0f, 8.0f / 255.0f, 200.0f / 255.0f);
        colors[ImGuiCol_DockingPreview] = ImVec4(47.0f / 255.0f, 6.0f / 255.0f, 29.0f / 255.0f, 0.7f);
        colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.20f, 0.20f, 0.20f, 0.00f);
        colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
        colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
        colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
        colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
        colors[ImGuiCol_TableHeaderBg] = ImVec4(0.0f, 0.0f, 0.0f, 1.00f);
        colors[ImGuiCol_TableBorderStrong] = ImVec4(2.0f / 255.0f, 2.0f / 255.0f, 2.0f / 255.0f, 1.0f);
        colors[ImGuiCol_TableBorderLight] = ImVec4(0.23f, 0.23f, 0.25f, 1.00f);
        colors[ImGuiCol_TableRowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
        colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
        colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
        colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
        colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
        colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
        colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
        colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
    }

    void EditorUI::showEditorUI()
    {
        showEditorMenu(&m_editor_menu_window_open);
    }

    void EditorUI::showEditorMenu(bool *p_open)
    {
        ImGuiDockNodeFlags dock_flags = ImGuiDockNodeFlags_DockSpace;
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoTitleBar |
                                        ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize |
                                        ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBackground |
                                        ImGuiConfigFlags_NoMouseCursorChange | ImGuiWindowFlags_NoBringToFrontOnFocus;

        const ImGuiViewport *main_viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(main_viewport->WorkPos, ImGuiCond_Always);
        std::array<int, 2> window_size = g_editor_global_context.m_window_system->getWindowSize();
        ImGui::SetNextWindowSize(ImVec2((float)window_size[0], (float)window_size[1]), ImGuiCond_Always);

        ImGui::SetNextWindowViewport(main_viewport->ID);

        ImGui::Begin("Editor menu", p_open, window_flags);

        ImGuiID main_docking_id = ImGui::GetID("Main Docking");
        if (ImGui::DockBuilderGetNode(main_docking_id) == nullptr)
        {
            ImGui::DockBuilderRemoveNode(main_docking_id);

            ImGui::DockBuilderAddNode(main_docking_id, dock_flags);
            ImGui::DockBuilderSetNodePos(main_docking_id,
                                         ImVec2(main_viewport->WorkPos.x, main_viewport->WorkPos.y + 18.0f));
            ImGui::DockBuilderSetNodeSize(main_docking_id,
                                          ImVec2((float)window_size[0], (float)window_size[1] - 18.0f));

            ImGuiID center = main_docking_id;
            ImGuiID left;
            ImGuiID right = ImGui::DockBuilderSplitNode(center, ImGuiDir_Right, 0.25f, nullptr, &left);

            ImGuiID left_other;
            ImGuiID left_file_content = ImGui::DockBuilderSplitNode(left, ImGuiDir_Down, 0.30f, nullptr, &left_other);

            ImGuiID left_game_engine;
            ImGuiID left_asset =
                ImGui::DockBuilderSplitNode(left_other, ImGuiDir_Left, 0.30f, nullptr, &left_game_engine);

            ImGui::DockBuilderDockWindow("World Objects", left_asset);
            ImGui::DockBuilderDockWindow("Components Details", right);
            ImGui::DockBuilderDockWindow("File Content", left_file_content);
            ImGui::DockBuilderDockWindow("Game Engine", left_game_engine);

            ImGui::DockBuilderFinish(main_docking_id);
        }
        ImGui::DockSpace(main_docking_id);

        ImGui::End();
    }

}
