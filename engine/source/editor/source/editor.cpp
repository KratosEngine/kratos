#include "editor/include/editor.h"

#include "runtime/engine.h"

namespace Kratos
{
	KratosEditor::KratosEditor()
	{
	}

	KratosEditor::~KratosEditor() {}

	void KratosEditor::initialize(KratosEngine* engine_runtime)
	{
		assert(engine_runtime);

		m_engine_runtime = engine_runtime;

	}

	void KratosEditor::run()
	{
		assert(m_engine_runtime);
		while (true)
		{

		}
	}

	void KratosEditor::clear()
	{

	}
}