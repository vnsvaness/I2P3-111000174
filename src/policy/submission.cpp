#include <cstdlib>
#include <climits>

#include "../state/state.hpp"
#include "./alphabeta.hpp"


/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */

Move alphabeta::get_best_move(State* state, int depth){
  if(!state->legal_actions.size())
    state->get_legal_actions();
  
  auto actions = state->legal_actions;
  int bestVal = state->player==0?INT_MIN:INT_MAX;
  Move bestMove;
  int alpha = INT_MIN;
  int beta = INT_MAX;
  for(auto action : actions){
    State* child = state->next_state(action);
    int value = minimax(child, depth-1,state->player ,alpha, beta);
    delete child;
    if(state->player==0 && value > bestVal){
      bestVal = value;
      bestMove = action;
    }
    else if(state->player==1 && value < bestVal){
      bestVal = value;
      bestMove = action;
    }
  }
  return bestMove;
}

int alphabeta::minimax(State* state, int depth, bool isMax, int alpha, int beta){
  if(!state->legal_actions.size())
    state->get_legal_actions();
  if(depth == 0 || !state->legal_actions.size()){
    return state->evaluate();
  }

  if(isMax){
    int bestVal = INT_MIN;
    for(auto action : state->legal_actions){
      State* child = state->next_state(action);
      int value = minimax(child, depth-1, false, alpha, beta);
      delete child;
      bestVal = std::max(bestVal, value);
      alpha = std::max(alpha, bestVal);
      if(beta <= alpha){
        break;
      }
    }
    return bestVal;
  }
  else{
    int bestVal = INT_MAX;
    for(auto action : state->legal_actions){
      State* child = state->next_state(action);
      int value = minimax(child, depth-1, true, alpha, beta);
      delete child;
      bestVal = std::min(bestVal, value);
      beta = std::min(beta, bestVal);
      if(beta <= alpha){
        break;
      }
    }
    return bestVal;
  }
}
