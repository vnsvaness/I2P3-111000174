#pragma once
#include "../state/state.hpp"


/**
 * @brief Policy class for random policy, 
 * your policy class should have get_move method
 */
class alphabeta{
public:
  static int minimax(State* state, int depth, bool isMax, int alpha, int beta);
  static Move get_best_move(State* state, int depth);
};