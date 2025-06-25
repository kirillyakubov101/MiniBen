#include "EventBus.h"

EventBus& EventBus::GetInst()
{
	static EventBus Instance;
	return Instance;
}
