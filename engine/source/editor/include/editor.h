#pragma once

#include <assert.h>
#include <memory>

namespace Kratos
{
	class KratosEngine;
	
	class KratosEditor
	{
	public:
		KratosEditor();
		virtual ~KratosEditor();

		void initialize(KratosEngine* engine_runtime);

		void run();
		void clear();
	protected:
		KratosEngine* m_engine_runtime{ nullptr };
	 
	};

}
