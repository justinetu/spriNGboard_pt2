#include <catch2/catch_test_macros.hpp>

#include <iomanip>
#include <iostream>

using namespace std;

class Tracker
{
  public:
    Tracker ()
    {sm_N_default_ctors++;}
 
    Tracker (Tracker const &)
    { sm_N_copy_ctors++; }
    Tracker (Tracker &&) noexcept
    { sm_N_move_ctors++; }

    Tracker & operator= ([[maybe_unused]] Tracker const & orig)
    { sm_N_copy_assigns++; return *this; }
    Tracker & operator= ([[maybe_unused]] Tracker && orig) noexcept
    { sm_N_move_assigns++; return *this; }

    ~Tracker ()
    { sm_N_dtors++; }

  public:
    static void reset_counts ()
    {
      sm_N_default_ctors = 0;
      sm_N_copy_ctors    = 0;
      sm_N_move_ctors    = 0;
      sm_N_copy_assigns  = 0;
      sm_N_move_assigns  = 0;
      sm_N_dtors         = 0;
    }

  public:
    static int32_t sm_N_default_ctors;
    static int32_t sm_N_copy_ctors;
    static int32_t sm_N_move_ctors;
    static int32_t sm_N_copy_assigns;
    static int32_t sm_N_move_assigns;
    static int32_t sm_N_dtors;
};

int32_t Tracker::sm_N_default_ctors = 0;
int32_t Tracker::sm_N_copy_ctors    = 0;
int32_t Tracker::sm_N_move_ctors    = 0;
int32_t Tracker::sm_N_copy_assigns  = 0;
int32_t Tracker::sm_N_move_assigns  = 0;
int32_t Tracker::sm_N_dtors         = 0;

TEST_CASE("lifecycle events")
{
  Tracker::reset_counts();

  SECTION("scenario 1")
  {
    Tracker t_1;

    // sm_N_default_ctors is  being incremented so it was failing
    // The assertion now accounts for that increment
    CHECK(Tracker::sm_N_default_ctors == 1); // FIX THIS AND EXPLAIN WHY
    // The assertion has its passing value because sm_N_copy_ctors
    // is being incremented in the copy ctor but default ctor is used
    CHECK(Tracker::sm_N_copy_ctors    == 0); // FIX THIS AND EXPLAIN WHY
    // The assertion has its passing value because the defauly ctor is
    // being used
    CHECK(Tracker::sm_N_move_ctors    == 0); // FIX THIS AND EXPLAIN WHY
    // The assertion has its passing value because sm_N_copy_assigns
    // is set to a default value of 0
    CHECK(Tracker::sm_N_copy_assigns  == 0); // FIX THIS AND EXPLAIN WHY
    // Default ctor is used so sm_N_move_assigns is not modified
    CHECK(Tracker::sm_N_move_assigns  == 0); // FIX THIS AND EXPLAIN WHY
    // When new Tracker object t_1 is created, default ctor is used
    // so sm_N_dtors remains 0
    CHECK(Tracker::sm_N_dtors         == 0); // FIX THIS AND EXPLAIN WHY
  }

  SECTION("scenario 2")
  {
    {
      Tracker t_1;
      Tracker t_2 = t_1;
    }
    // When t_1 is created, the default ctor is called where 
    // sm_N_default_ctors is incremented equaling 1
    CHECK(Tracker::sm_N_default_ctors == 1); // FIX THIS AND EXPLAIN WHY
    // sm_N_copy_ctors is 1 because the copy ctor is called when t_2 
    // obtains t_1's resources so sm_N_copy_ctors is incremented
    CHECK(Tracker::sm_N_copy_ctors    == 1); // FIX THIS AND EXPLAIN WHY
    // Move ctor is not called so sm_N_move_ctors remains 0
    CHECK(Tracker::sm_N_move_ctors    == 0); // FIX THIS AND EXPLAIN WHY
    CHECK(Tracker::sm_N_copy_assigns  == 0); // FIX THIS AND EXPLAIN WHY
    CHECK(Tracker::sm_N_move_assigns  == 0); // FIX THIS AND EXPLAIN WHY
    // sm_N_dtors is 2 because each two Tracker objects are created. 
    // sm_N_dtors will be decremented each time an object is deleted
    CHECK(Tracker::sm_N_dtors         == 2); // FIX THIS AND EXPLAIN WHY
  }

  SECTION("scenario 3")
  {
    {
      Tracker t_1 = Tracker();
      Tracker t_2(t_1);
    }
    // sm_N_default_ctors is 1 because a Tracker object t_1, is created
    // which calls the default ctor which increments sm_N_default_ctors
    CHECK(Tracker::sm_N_default_ctors == 1); // FIX THIS AND EXPLAIN WHY
    // sm_N_copy_ctors is 1 because upon the creation of t_2, the copy
    // ctor is used giving t_2 t_1's contents. sm_N_copy_ctors is incre
    CHECK(Tracker::sm_N_copy_ctors    == 1); // FIX THIS AND EXPLAIN WHY
    CHECK(Tracker::sm_N_move_ctors    == 0); // FIX THIS AND EXPLAIN WHY
    CHECK(Tracker::sm_N_copy_assigns  == 0); // FIX THIS AND EXPLAIN WHY
    CHECK(Tracker::sm_N_move_assigns  == 0); // FIX THIS AND EXPLAIN WHY
    // Because two Tracker objects are created, sm_N_dtors is incremented    // each time
    CHECK(Tracker::sm_N_dtors         == 2); // FIX THIS AND EXPLAIN WHY
  }

  SECTION("scenario 4")
  {
    {
      Tracker t_1;
      Tracker t_2 = std::move(t_1);
      t_1 = Tracker();
    }
    // sm_N_default_ctors is 2 here because the default ctor is called
    // when t_1 is created and after t_1's move assignment takes place
    CHECK(Tracker::sm_N_default_ctors == 2); // FIX THIS AND EXPLAIN WHY
    CHECK(Tracker::sm_N_copy_ctors    == 0); // FIX THIS AND EXPLAIN WHY
    // sm_N_move_ctors is 1 because the move ctor is called because 
    // when t_2 is created, it takes the resources from t_1
    CHECK(Tracker::sm_N_move_ctors    == 1); // FIX THIS AND EXPLAIN WHY
    CHECK(Tracker::sm_N_copy_assigns  == 0); // FIX THIS AND EXPLAIN WHY
    // sm_N_move_assigns is 1 becuase the move assignment operator is
    // being used when t_1 is assigned the  default ctor so sm_N_move_
    // assigns gets incremented
    CHECK(Tracker::sm_N_move_assigns  == 1); // FIX THIS AND EXPLAIN WHY
    // sm_N_dtors is 3 because t_1 is created so its incremented, t_2 is
    // created which takes t_1's guts so sm_N_dtors is incremented again
    // t_1 gets new resources when the default ctor is called so again
    // sm_N_dtors is incremented
    CHECK(Tracker::sm_N_dtors         == 3); // FIX THIS AND EXPLAIN WHY
  }

  SECTION("scenario 5")
  {
    {
      Tracker t_1 = Tracker();
      Tracker t_2 = std::move(t_1);
      Tracker t_3 = t_1;
    }
    // sm_N_default_ctors is 1 because once t_1 is created, the default
    // ctor is called which increments it
    CHECK(Tracker::sm_N_default_ctors == 1); // FIX THIS AND EXPLAIN WHY
    // sm_N_copy_ctors is 1 because t_3 uses the copy ctor
    CHECK(Tracker::sm_N_copy_ctors    == 1); // FIX THIS AND EXPLAIN WHY
    // sm_N_ctors is 1 because the move ctor is called upon the creation
    // of t_2 since t_1's resources are given to t_2
    CHECK(Tracker::sm_N_move_ctors    == 1); // FIX THIS AND EXPLAIN WHY
    // I believe the reason sm_N_copy_assigns is 0 is because there is no    // copy assignment taking place. t_3 wants is getting the empty
    // resources of t_1
    CHECK(Tracker::sm_N_copy_assigns  == 0); // FIX THIS AND EXPLAIN WHY
    CHECK(Tracker::sm_N_move_assigns  == 0); // FIX THIS AND EXPLAIN WHY
    // sm_N_dtors is 3 because 3 objects are created
    CHECK(Tracker::sm_N_dtors         == 3); // FIX THIS AND EXPLAIN WHY
  }

  SECTION("scenario 6")
  {
    {
      Tracker t_1 = Tracker();
      Tracker t_2 = t_1;
      t_2 = std::move(t_1);
    }
    // sm_N_default_ctors is 1 because the default ctor is called
    CHECK(Tracker::sm_N_default_ctors == 1); // FIX THIS AND EXPLAIN WHY
    // copy ctor is called because t_2 copies t_1's contents
    CHECK(Tracker::sm_N_copy_ctors    == 1); // FIX THIS AND EXPLAIN WHY
    // There is no move constructing happenin so sm_N_move_ctors = 0
    CHECK(Tracker::sm_N_move_ctors    == 0); // FIX THIS AND EXPLAIN WHY
    // No copy assignment taking place
    CHECK(Tracker::sm_N_copy_assigns  == 0); // FIX THIS AND EXPLAIN WHY
    // sm_N_move_assigns is 1 because the last line moves t_1's contents
    // and assigns it to t_2
    CHECK(Tracker::sm_N_move_assigns  == 1); // FIX THIS AND EXPLAIN WHY
    // Since 2 objects are constructed, sm_N_dtors is 2
    CHECK(Tracker::sm_N_dtors         == 2); // FIX THIS AND EXPLAIN WHY
  }
}


