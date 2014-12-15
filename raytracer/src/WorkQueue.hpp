#include <deque>
#include <mutex>
#include <condition_variable>

namespace raytracer  {
namespace util {

	template <typename T>
	class WorkQueue
	{
	public:
		void pushBack(const T& t)
		{
			{
				std::unique_lock<std::mutex> lock(mutex_);
				queue_.push_front(t);
			}

			cv_.notify_one();
		}

		bool tryPop(T& t)
		{
			std::lock_guard<std::mutex> lock(mutex_);
			if (!queue_.empty())
			{
				t = queue_.back();
				queue_.pop_back();
				return true;
			}

			return false;
		}

		void waitPop(T& t)
		{
			std::unique_lock<std::mutex> lock(mutex_);
			cv_.wait(lock, []{ return !queue_.empty(); });
			t = queue_.back();
			queue_.pop_back();
		}

	private:
		std::deque<T> queue_;
		std::mutex mutex_;
		std::condition_variable cv_;
	};

} }
