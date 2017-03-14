////////////
//    created by ÀÔ«Ï∫≈
////////////

#ifndef __EVENT_H__
#define  __EVENT_H__
#include <functional>
#include <map>
#include <mutex>
#include <utility>
#include <vector>
#include "assert.h"
#include "InstanceFunction.h"
#include "IEvent.h"

namespace core
{
	template<class _Func>
	class Event :public IEvent<_Func>
	{
	public:
		typedef InstanceFunction<_Func> EventType;
		typedef std::function<_Func> EventBaseType;
		EventBaseType _eventType;

		Event()
		{
			m_traversing = false;
		}

		~Event()
		{
			m_events.clear();
		}

		static Event<_Func> Empty;


		void operator+=(EventType& func) {
			std::string key = func.getKey();
			if (m_traversing)
			{
				m_toBeAdd.push_back(func);
			}
			else
			{
				m_lock.lock();
				m_events[key] = func.getFunc();
				m_lock.unlock();
			}
		}


		void operator-=(FunctionKey& func) {

			std::string key = func.getKey();
			if (m_traversing)
			{
				m_toBeDel.push_back(key);
			}
			else
			{
				m_lock.lock();
				auto it = m_events.find(key);
				if (it != m_events.end())
					m_events.erase(it);

				m_lock.unlock();
			}
		}


		void for_each(std::function<void(EventBaseType)> func)
		{
			if (m_traversing)
			{
				//assert(false);
				return;
			}

			m_lock.lock();
			m_traversing = true;
			m_lock.unlock();

			for (auto iter = m_events.begin(); iter != m_events.end(); iter++)
			{
				func(iter->second);
			}

			if (m_toBeDel.size() > 0)
			{
				m_lock.lock();
				for (auto iter = m_toBeDel.begin(); iter != m_toBeDel.end(); iter++)
				{
					auto it = m_events.find(*iter);
					if (it != m_events.end())
						m_events.erase(it);
				}
				m_toBeDel.clear();
				m_lock.unlock();
			}

			if (m_toBeAdd.size() > 0)
			{
				m_lock.lock();
				for (auto iter = m_toBeAdd.begin(); iter != m_toBeAdd.end(); iter++)
				{
					m_events[iter->getKey()] = iter->getFunc();
				}
				m_toBeAdd.clear();
				m_lock.unlock();
			}

			m_lock.lock();
			m_traversing = false;
			m_lock.unlock();

		}



	protected:
		std::map<std::string, EventBaseType> m_events;
		std::vector<std::string> m_toBeDel;
		std::vector<EventType> m_toBeAdd;
		std::mutex m_lock;
		volatile bool m_traversing;
	};

	template<class _Func>
	core::Event<_Func> core::Event<_Func>::Empty = core::Event<_Func>();

}
#endif // __EVENT_H__