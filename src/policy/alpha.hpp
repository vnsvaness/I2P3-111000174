#pragma once
#include "../state/state.hpp"


/**
 * @brief Policy class for random policy, 
 * your policy class should have get_move method
 */
class alphabeta{
public:
  static Move get_move(State *state, int depth);
  static int makechild(State* state,int depth,int player,int alpha,int beta);
  static int evalstate(State* state);
 // State* evaluatetree(State* state,int depth);
};