////////////
//    created by ÀÔ«Ï∫≈
////////////

#ifndef __I_EVENT_H__
#define __I_EVENT_H__
#include <functional>
#include "InstanceFunction.h"

namespace core
{
	template<class _Func>
	class IEvent
	{
	public:
		typedef InstanceFunction<_Func> EventType;
		typedef std::function<_Func> EventBaseType;
		EventBaseType _eventType;


		virtual void operator+=(EventType& func) = 0;


		virtual void operator-=(FunctionKey& func) = 0;


		virtual void for_each(std::function<void(EventBaseType)> func) = 0;

#define core_Event_Trigger(_event, ...) _event.for_each([&](decltype(_event._eventType) callback){callback(__VA_ARGS__);})

	};

}
#endif __I_EVENT_H__