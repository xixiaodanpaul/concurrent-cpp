//
//  main.cpp
//  concurrent_cpp
//
//  Created by Xiaodan on 2/7/21.
//

#include <iostream>
#include <thread>
#include <iostream>
#include <fstream>
#include <mutex>

using namespace std;

// // First example:
// void thread1() {
//    std::cout << "Hello, Worlds" << std::endl;
// }

// int main() {
//    std::thread t1(thread1);
//    t1.join();   // main thread wait for t1 to finish
//    //t1.detach();  // main thread let t1 to run on its own: t1 is a daemon process.
//                   // C++ runtime library is responsible returning t1's resources
//                   // and main thread may finish before t2 prints "Hello"

//    return 0;
// }
// // If neither detach nor join is called, terminate() will be called for the t1.
// // A thread can only be joined once or detached once. After it is joined on detached
// // it becomes unjoinable ( t.joinable() returns false )

// // Second Example: Racing condition
// class Fctor {
//     ofstream& m_str;
// public:
//     Fctor(ofstream& s) : m_str(s) {}   // Reference member can only be initialized
//     void operator()() {
//         for (int i=0; i>-100; i--)
//             m_str << "from t1: " << i << endl;
//     }
// };

// int main() {
//     cout << "Hello Bo" << endl;
//     ofstream f;
//     f.open("./log.txt");

//     Fctor fctor(f);
//     std::thread t1(fctor);

//     for (int i=0; i<100; i++)
//         f << "from main: " << i << endl;

//     t1.join();
//     f.close();

//     return 0;
// }

/* Using mutex to synchronize threads */
std::mutex m_mutex;

void shared_print(string id, int value) {
	std::lock_guard<std::mutex> locker(m_mutex);
    //m_mutex.lock();
    // if (m_mutex.trylock()) {...}
	cout << "From " << id << ": " << value << endl;
    //m_mutex.unlock();
}

class Fctor {
public:
	void operator()() {
		for (int i=0; i>-100; i--) 
			shared_print("t1", i);
	}
};

int main() {
	Fctor fctor;
	std::thread t1(fctor);

	for (int i=0; i<100; i++)
		shared_print("main", i);

	t1.join();

	return 0;
}