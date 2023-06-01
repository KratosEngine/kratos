#pragma once

#include <assert.h>
#include <memory>

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
		std::shared_ptr<EditorUI> m_editor_ui;
		KratosEngine *m_engine_runtime{nullptr};
	};

}
