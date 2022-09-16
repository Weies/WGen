//#include"WGen.h"
//#include<condition_variable>
//#include<atomic>
//#include<cstdarg>
//using namespace std;
//
//using ull = unsigned long long;
//
//deque<int> good;
//condition_variable cond;
//mutex con_loc; mutex loc2; mutex mut;
////unique_lock<mutex> loc_full(con_loc);
////unique_lock<mutex> loc_emp(con_loc);
//int gid = 0;
//
//
//void producer(int i) {
//	while (true) {
//		this_thread::sleep_for(chrono::milliseconds(Rand() % 100 + 10));
//		while (good.size() == 10) {//没有剩余空间，等待
//			//cond.wait(loc_full);
//		}
//		mut.lock();
//
//		good.push_back(++gid);
//		debug << "producer " << i << " put [" << gid << "] in the queue at time[" << clock() << "]." << endl;
//
//		mut.unlock();
//		cond.notify_one();
//
//	}
//}
//
//void consumer(int i) {
//	while (true) {
//		this_thread::sleep_for(chrono::milliseconds(Rand() % 1000 + 10));
//		while (good.empty()) {
//			//cond.wait(loc_full);
//		}
//		mut.lock();
//		//InterLock
//		//atomic_
//		//atomic_compare_exchange_weak();
//		//atomic_compare_exchange_weak()
//		int cur = good.front(); good.pop_front();
//		debug << "consumer " << i << " get [" << cur << "] from the queue at time[" << clock() << "]." << endl;
//
//		mut.unlock();
//		cond.notify_one();
//
//	}
//}
//
//class A {
//public:
//	virtual void pp() = 0;
//};
//class B :public A {
//public:
//	//virtual B() {};
//	inline virtual void pt(){}
//	virtual void pp() { debug(1); };
//};
////void* operator new(size_t size) {
////
////}
//int main() {
//	/*for (int i = 0; i < 5; ++i) {
//		auto p = new thread(producer, i); p->detach();
//	}
//	for (int i = 0; i < 5; ++i) {
//		auto p = new thread(consumer, i); p->detach();
//	}
//
//	while (true) {
//		this_thread::sleep_for(1s);
//	}*/
//	B b;
//	
//	//b.A::pp();
//}
