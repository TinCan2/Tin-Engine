#pragma once
#include "DllMacro.hpp"
#include <vector>

namespace Tin {
	class FunctionalObject {
		public:
		FunctionalObject();
		virtual ~FunctionalObject();

		virtual void OnUpdate() = 0;

		private:
		static void UpdateObjects();

		friend class GameManager;

		static std::vector<FunctionalObject*> updateList;
	};
}