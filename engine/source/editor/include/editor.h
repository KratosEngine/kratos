#pragma once

#include <assert.h>

#include <EASTL/shared_ptr.h>

namespace Kratos
{
	class EditorUI;
	class KratosEngine;

	class KratosEditor
	{
	public:
		KratosEditor();
		virtual ~KratosEditor();

		void initialize(KratosEngine *engine_runtime);

		void run();
		void clear();

	protected:
	protected:
		eastl::shared_ptr<EditorUI> m_editor_ui;
		KratosEngine *m_engine_runtime{nullptr};
	};

}
