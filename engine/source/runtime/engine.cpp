#include "runtime/engine.h"
#include "runtime/core/base/macro.h"

#include "runtime/function/global/global_context.h"
#include "runtime/function/application/window_system.h"

namespace Kratos
{
    bool g_is_editor_mode{false};
    std::unordered_set<std::string> g_editor_tick_component_types{};
    void KratosEngine::startEngine(const std::string &config_file_path)
    {
        g_runtime_global_context.startSystems(config_file_path);
        LOG_INFO("engine start");
    }

    void KratosEngine::shutdownEngine()
    {
        LOG_INFO("engine shutdown");
        g_runtime_global_context.shutdownSystems();
    }

    void KratosEngine::initialize()
    {
    }

    void KratosEngine::clear()
    {
    }

    void KratosEngine::run()
    {
        //实际运行游戏主入口逻辑（编辑器走的自己的run方法）
        eastl::shared_ptr<WindowSystem> window_system = g_runtime_global_context.m_window_system;
        KSMAC_ASSERT(window_system);
        while (!window_system->shouldClose())
        {
            const float delta_time = calculateDeltaTime();
            tickOneFrame(delta_time);
        }
    }

    bool KratosEngine::tickOneFrame(float delta_time)
    {
        logicalTick(delta_time);
        calculateFPS(delta_time);

        // single thread
        // exchange data between logic and render contexts
        // tood zxs

        rendererTick(delta_time);

        g_runtime_global_context.m_window_system->pollEvents();
        g_runtime_global_context.m_window_system->setTitle(
            std::string("Kratos - " + std::to_string(getFPS()) + " FPS").c_str());

        const bool should_window_close = g_runtime_global_context.m_window_system->shouldClose();
        return !should_window_close;
    }

    void KratosEngine::logicalTick(float delta_time)
    {
        // tood zxs
    }

    bool KratosEngine::rendererTick(float delta_time)
    {
        // todo zxs
        return true;
    }

    float KratosEngine::calculateDeltaTime()
    {
        float delta_time;
        {
            using namespace std::chrono;
            steady_clock::time_point tick_time_point = steady_clock::now();
            duration<float> time_span = duration_cast<duration<float>>(tick_time_point - m_last_tick_time_point);
            delta_time = time_span.count();

            m_last_tick_time_point = tick_time_point;
        }
        return delta_time;
    }

    const float KratosEngine::s_fps_alpha = 1.f / 100;
    void KratosEngine::calculateFPS(float delta_time)
    {
        m_frame_count++;

        if (m_frame_count == 1)
        {
            m_average_duration = delta_time;
        }
        else
        {
            m_average_duration = m_average_duration * (1 - s_fps_alpha) + delta_time * s_fps_alpha;
        }

        m_fps = static_cast<int>(1.f / m_average_duration);
    }
}