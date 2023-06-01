#pragma once

#include "runtime/function/application/application.h"

namespace Kratos
{
    class EditorUI : KSApplication
    {
    public:
        EditorUI();
        ~EditorUI();

        virtual void initialize(ApplicationUIInitInfo init_info) override final;
        virtual void preRender() override final;

    private:
        void showEditorUI();
        void showEditorMenu(bool *p_open);

        void setUIColorStyle();

        bool m_editor_menu_window_open = true;
        bool m_asset_window_open = true;
        bool m_game_engine_window_open = true;
        bool m_detail_window_open = true;
        bool m_scene_lights_window_open = true;
        bool m_scene_lights_data_window_open = true;
    };
}