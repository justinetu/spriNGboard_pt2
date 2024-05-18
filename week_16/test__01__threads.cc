#include <catch2/catch_test_macros.hpp>

///////////////////////////
//                       //
// BEGIN MODIFYABLE CODE //
//                       //
///////////////////////////

#include <iostream>
#include <sstream>
#include <string>
#include <thread>
#include <vector>
#include <mutex>

using namespace std;

TEST_CASE("each thread output appears exactly once and intact")
{
  //
  // Launch N_threads threads and collect their outputs.
  //
 
  int32_t const N_threads = 10;
  vector<thread> threads;

  ostringstream ostr;
  mutex ostr_mutex;
  for (int32_t idx=0; idx<N_threads; ++idx)
  {


threads.push_back(
      thread(
        [&ostr, idx, &ostr_mutex] () {
          lock_guard<mutex> guard(ostr_mutex);
          ostr << "This is the output for thread idx=" << idx << endl;
        }
      )
    );
  }

  //
  // LOOP A
  // LOOP A creates an object of type thread used to reference each 
  // thread in the vector. This variable, t, holds the current thread
  // at the point of its call until the current thread finishes its
  // execution.
  // LOOP A is necessary because without joining the threads, the 
  // program will terminate abruptly.
   for (auto & t : threads) {
    t.join();
  }
 
  string program_output_str = ostr.str();

  /////////////////////////
  //                     //
  // END MODIFYABLE CODE //
  //                     //
  /////////////////////////

  //
  // Verify that the output for each thread appears
  // exactly once and intact.
  //
  for (int32_t idx=0; idx<N_threads; ++idx)
  {
    ostringstream target_ostr;
    target_ostr << "This is the output for thread idx=" << idx << endl;
    auto target_str = target_ostr.str();
    //
    // LOOP B
    // LOOP B continues to run as long as pos is not string::npos 
    // (another occurence of target_str was found)
    // it counts how many times the substring target_str appears 
    // in the string program_output_str. It initializes the counter
    // and finds the first occurence of the substring, and then 
    // continues to find subsequent occurences by updating the search
    // position until no more occurences are found
    int32_t N_matches = 0;
    size_t pos = program_output_str.find(target_str, 0);
    cout << pos << endl;
    while (pos != string::npos) {
      ++N_matches;
      pos = program_output_str.find(target_str, pos+1);
    }
    // LINE C checks if N_matches is 1 which in this case means that
    // each thread's output should appear exactly onc in the final output
    // The issue with this code was that there was no agreed upon 
    // ordering for which thread gets to write to ostr. This could
    // cause a data race and undefined behavior.

    // What I did to fix the code is I used a mutex to protect access
    // to the shared ostringstream ostr. Additionally, I captured the 
    // idx by value instead of reference within the lambda, I also 
    // captured the mutex by reference within the lambda.
    // In the lambda, I create a created a lock_guard for the mutex
    // to ensure that before a thread writes to ostr, the mutex is locked    // and when the lock_guard is released when it goes out of scope.
    CHECK(N_matches == 1); // LINE C
  }

}
 

