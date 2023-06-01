#include "editor/include/editor.h"

#include "runtime/engine.h"
#include "runtime/function/global/global_context.h"

#include "editor/include/editor_global_context.h"
#include "editor/include/editor_ui.h"

using namespace Kratos;
KratosEditor::KratosEditor()
{
}

KratosEditor::~KratosEditor() {}

void KratosEditor::initialize(KratosEngine *engine_runtime)
{
	assert(engine_runtime);

	g_is_editor_mode = true;
	m_engine_runtime = engine_runtime;

	EditorGlobalContextInitInfo init_info = {g_runtime_global_context.m_window_system.get(),
											 engine_runtime};
	g_editor_global_context.initialize(init_info);

	m_editor_ui = std::make_shared<EditorUI>();
	ApplicationUIInitInfo ui_init_info = {
		g_runtime_global_context.m_window_system,
	};
	m_editor_ui->initialize(ui_init_info);
}

void KratosEditor::run()
{
	assert(m_engine_runtime);
	assert(m_editor_ui);
	float delta_time;
	while (true)
	{
		delta_time = m_engine_runtime->calculateDeltaTime();
		if (!m_engine_runtime->tickOneFrame(delta_time))
		{
			return;
		}
	}
}

void KratosEditor::clear()
{
	g_editor_global_context.clear();
}