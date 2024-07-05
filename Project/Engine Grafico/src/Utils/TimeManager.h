#ifndef TIME_MANAGER_H
#define TIME_MANAGER_H

#include "Export.h"

using namespace std;

namespace Engine {
	class ENGINE_API Time {
	public:
		Time();
		~Time();
		static float GetDeltaTime();
		void UpdateDeltaTime(float currentTime);

	private:
		static float _deltaTime;
		float _previousDeltaTime;
	};
}

#endif // !TIME_MANAGER_H