#include <cstdlib>
#include <iostream>
#include "../state/state.hpp"
#include "./alpha.hpp"

/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 * 
 */
int queenpos[6][5] = {
        { 0,  0,  0,  0,  0 },
        { 0,  0,  0,  0,  0 },
        { 0,  0,  0,  0,  0 },
        { 0,  0,  0,  0,  0 },
        { 0,  0,  0,  0,  40 },
        { 0,  0,  0,  0,  0 }
};
int horsepos[6][5] = {
        { 0,  0,  0,  0,  0 },
        { 0,  0,  0,  0,  0 },
        { 0,  0,  0,  0,  0 },
        { 3,  0,  100000,  0,  0 },
        { 0,  0,  0,  0,  0 },
        { 0,  0,  0,  0,  0 }
};
int pawnspos[6][5] = {
        { 0,  0,  0,  0,  0 },
        { 0,  0,  0,  0,  0 },
        { 0,  0,  5,  0,  0 },
        { 0,  5,  10,  0,  10 },
        { 0,  0,  0,  5,  0 },
        { 0,  0,  0,  0,  0 }
};
int pos[6][5] = {
        { 0,  0,  0,  0,  0 },
        { 0,  0,  0,  0,  0 },
        { 0,  0,  0,  0,  0 },
        { 0,  0,  0,  0,  0 },
        { 0,  0,  0,  0,  0 },
        { 0,  0,  0,  0,  0 }
};
int bispos[6][5] = {
        { 0,  0,  0,  0,  0 },
        { 0,  0,  0,  0,  0 },
        { 0,  0,  0,  0,  0 },
        { 0,  0,  0,  0,  0 },
        { 0,  10,  0,  10,  0 },
        { 0,  0,  0,  0,  0 }
};
int kingpos[6][5] = {
        { 0,  0,  0,  0,  0 },
        { 0,  0,  0,  0,  0 },
        { 0,  0,  0,  0,  0 },
        { 0,  0,  0,  -50,  -50 },
        { 0,  0,  0,  -50,  -50 },
        { 0,  0,  0,  0,  0 }
};
int playertemp;
int alphabeta::evalstate(State *state){
  int whitevalue=0;
  int blackvalue=0;
  for(int i=0;i<2;i++){
    for(int j=0;j<BOARD_H;j++ ){
      for(int k=0;k<BOARD_W;k++){
        int currval=0;
        switch (state->board.board[i][j][k])
        {
        case 1:
        // std::cout << "halo" << std::endl;
          currval=2;
          //currval+=pawnspos[j][k];
          break;
        case 2:
          currval=6;
          break;
        case 3:
          currval=7;
         // currval+=horsepos[j][k];
          break;
        case 4:
          currval=8;
         // currval+=bispos[j][k];
          break;
        case 5:
          currval=20;
         // currval+=queenpos[j][k];
          break;
        case 6:
        if(playertemp==0)
            currval=10000000;
        default:
          break;
        }
        if(i==0){
          whitevalue+=currval;
        }
        else blackvalue+=currval;
      }
    }
    
  }
  //state->statevalue=state->player==1?blackvalue-whitevalue:whitevalue-blackvalue;
  state->statevalue=whitevalue-blackvalue;
  return state->statevalue;
  
}
Move alphabeta::get_move(State *state, int depth){
  if(!state->legal_actions.size())
    state->get_legal_actions();
   // int val=makechild(state,depth,0);
    depth=4;
 //   std::cout << "Depth: " << depth << std::endl;
  // std::cout << "PLAYER "<< state->player << std::endl;
    playertemp=state->player;
    makechild(state,depth,state->player,-10000000,10000000);
   // std::cout << "STATE VALUE: "<<state->statevalue << std::endl;
   // std::cout<<"WOW: " << wow << std::endl;
    return state->subtree->curr;
}

int alphabeta::makechild(State *state, int depth, int player,int alpha,int beta) {
    //std::cout << "ASMDFSDF" << std::endl;
   // wow++;
   
    if (state->legal_actions.size()<=0)
        state->get_legal_actions();
    if (state->legal_actions.size() == 0) return alphabeta::evalstate(state);

    if(state->game_state==WIN){
      //  std::cout << "KALAH COKK" << std::endl;
        if(playertemp!=player)
        return player==0 ? 10000000:-10000000;

    }
     if (depth == 0){
        int eval=alphabeta::evalstate(state);
         return eval;
    }
    if (player == 0) {
        int max = -10000000;
        for (auto i : state->legal_actions) {

            State* tmp = state->next_state(i);
            tmp->player=1;
            int val = makechild(tmp, depth - 1, 1,alpha,beta);
            if (val > max){ 
               // std::cout << "val: "<< val  << " depth: "<< depth  << " player: " << player<< std::endl;
                if(state->subtree)delete state->subtree;
                max = val;
                state->subtree=tmp;
                state->statevalue = max;
                             //   std::cout << "max: " << max << std::endl;


            }else{
               delete tmp;

            }
            if(val > alpha){
                alpha=val;
            }
            if(alpha>=beta){
              //  std::cout << "alpha>=beta" << std::endl;
                break;
            }
        }
       

        return max;
    } else {
        int min = 10000000;
        for (auto i : state->legal_actions) {
            State* tmp = state->next_state(i);
            tmp->player=0;
            int val = makechild(tmp, depth - 1, 0,alpha,beta);
            if (val < min) {
            //   std::cout << "val: "<< val  << " depth: "<< depth  << " player: " << player<< std::endl;
                if(state->subtree)delete state->subtree;
                min = val;
                state->subtree=tmp;
                state->statevalue = min;
              //  std::cout << "min: " << min << std::endl;


            }else{
                delete tmp;
            }
            if(val < beta)beta=val;
            if(beta <=alpha){
                //std::cout << "beta <=alpha" << std::endl;
                break;
            }
        }
                
        return min;
    }
}
  