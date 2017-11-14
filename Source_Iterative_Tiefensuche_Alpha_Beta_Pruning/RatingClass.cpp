#include <math.h>
#include "RatingClass.h"
#include "GameStateClass.h"
#include "FieldClass.h"

RatingClass::RatingClass(GameStateClass *_gameState) : gameState(_gameState){
}
/* V26
int32_t RatingClass::GetRating(int playerId) {
    int32_t rating = 0;
    int32_t MaxblockRating = 1;
    int32_t NegblockRating = -1;
    int32_t MaxfourInARow = 0;
    int32_t NegfourInARow = 0;
    //   ||||||||
    for(int x = 0 ; x < gameState->fieldRows-3 && MaxfourInARow != 4 && NegfourInARow != 4; x++){
        for(int y = 0 ; y < gameState->fieldColumns && MaxfourInARow != 4 && NegfourInARow != 4; y++){
            MaxblockRating = 1;
            NegblockRating = -1;
            MaxfourInARow = 0;
            NegfourInARow = 0;
            for(int i = 0; (i < 4) && !((NegfourInARow > 0) && (MaxfourInARow > 0)); i++){
                if(gameState->field->GetCellValue(x+i,y) == playerId){
                    MaxblockRating = MaxblockRating * 10;
                    MaxfourInARow++;
                }
                if(gameState->field->GetCellValue(x+i,y) == -playerId){
                    NegblockRating = NegblockRating * 10;
                    NegfourInARow++;
                }
            }
            //ToDo senkrechte Linien sollen weniger wert sein als waagrechte
            if(!((NegfourInARow > 0) && (MaxfourInARow > 0))) rating = rating + (MaxblockRating + NegblockRating); //Interessiert mich nur wenn 4 zu vervollständigen möglich ist
        }
    }
    //   -------
    for(int x = 0 ; x < gameState->fieldRows && MaxfourInARow != 4 && NegfourInARow != 4; x++){
        for(int y = 0 ; y < gameState->fieldColumns-3 && MaxfourInARow != 4 && NegfourInARow != 4; y++){
            MaxblockRating = 1;
            NegblockRating = -1;
            MaxfourInARow = 0;
            NegfourInARow = 0;
            for(int i = 0; (i < 4) && !((NegfourInARow > 0) && (MaxfourInARow > 0)); i++){
                if(gameState->field->GetCellValue(x,y+i) == playerId){
                    MaxblockRating = MaxblockRating * 10;
                    MaxfourInARow++;
                }
                if(gameState->field->GetCellValue(x,y+i) == -playerId){
                    NegblockRating = NegblockRating * 10;
                    NegfourInARow++;
                }
            }
            if(!((NegfourInARow > 0) && (MaxfourInARow > 0))) rating = rating + MaxblockRating + NegblockRating;
        }
    }
    //         ``````
    for(int x = 0 ; x < gameState->fieldRows-3 && MaxfourInARow != 4 && NegfourInARow != 4; x++){
        for(int y = 0 ; y < gameState->fieldColumns-3 && MaxfourInARow != 4 && NegfourInARow != 4; y++){
            MaxblockRating = 1;
            NegblockRating = -1;
            MaxfourInARow = 0;
            NegfourInARow = 0;
            for(int i = 0; (i < 4) && !((NegfourInARow > 0) && (MaxfourInARow > 0)); i++){
                if(gameState->field->GetCellValue(x+i,y+i) == playerId){
                    MaxblockRating = MaxblockRating * 10;
                    MaxfourInARow++;
                }
                if(gameState->field->GetCellValue(x+i,y+i) == -playerId){
                    NegblockRating = NegblockRating * 10;
                    NegfourInARow++;
                }
            }
            if(!((NegfourInARow > 0) && (MaxfourInARow > 0))) rating = rating + MaxblockRating + NegblockRating;
        }
    }
    //      ///////
    for(int x = 0 ; x < gameState->fieldRows-3 && MaxfourInARow != 4 && NegfourInARow != 4; x++){
        for(int y = 3 ; y < gameState->fieldColumns && MaxfourInARow != 4 && NegfourInARow != 4; y++){
            MaxblockRating = 1;
            NegblockRating = -1;
            MaxfourInARow = 0;
            NegfourInARow = 0;
            for(int i = 0; (i < 4) && !((NegfourInARow > 0) && (MaxfourInARow > 0)); i++){
                if(gameState->field->GetCellValue(x+i,y-i) == playerId){
                    MaxblockRating = MaxblockRating * 10;
                    MaxfourInARow++;
                }
                if(gameState->field->GetCellValue(x+i,y-i) == -playerId){
                    NegblockRating = NegblockRating * 10;
                    NegfourInARow++;
                }
            }
            if(!((NegfourInARow > 0) && (MaxfourInARow > 0))) rating = rating + MaxblockRating + NegblockRating;
        }
    }
    if(MaxfourInARow == 4){
#ifdef DEBUG
cout << "-------------- " << playerId << " won ---------------" << endl;
#endif
        return WINNIG_VALUE;
    }
    else if(NegfourInARow == 4){
#ifdef DEBUG
cout << "-------------- " <<-playerId << " won ---------------" << endl;
#endif
        return -WINNIG_VALUE;
    }
    else return rating;
}
*/
int32_t RatingClass::GetRating(int playerId) {
    int32_t rating = 0;
    int32_t max_max,count_max,a_max,b_max,c_max,d_max,e_max,f_max,g_max;
    int32_t max_neg,count_neg,a_neg,b_neg,c_neg,d_neg,e_neg,f_neg,g_neg;
    int32_t a2_max,b2_max,c2_max,d2_max,e2_max,f2_max,g2_max;
    int32_t a2_neg,b2_neg,c2_neg,d2_neg,e2_neg,f2_neg,g2_neg;
    max_max = max_neg = 0;

    for(int y = 0 ; y < gameState->fieldColumns; y++){
        count_max = 0;
        count_neg = 0;
        for(int x = gameState->fieldRows-1 ; x >= 0; x--){
            a_max = b_max = c_max = d_max = e_max = f_max = g_max = 0;
            a_neg = b_neg = c_neg = d_neg = e_neg = f_neg = g_neg = 0;
            a2_max = b2_max = c2_max = d2_max = e2_max = f2_max = g2_max = 0;
            a2_neg = b2_neg = c2_neg = d2_neg = e2_neg = f2_neg = g2_neg = 0;
            if(gameState->field->GetCellValue(x,y) == 0){
                for(int i = 1; i < 4; i++){
                    if(x < gameState->fieldRows-3){
                        if(gameState->field->GetCellValue(x+i,y) == playerId) a_max++;
                        if(gameState->field->GetCellValue(x+i,y) == -playerId) a_neg++;
                    }
                    if(x >= 3 && y < gameState->fieldColumns-3){
                        if(gameState->field->GetCellValue(x-i,y+i) == playerId) b_max++;
                        if(gameState->field->GetCellValue(x-i,y+i) == -playerId) b_neg++;
                    }
                    if(y >= 3){
                        if(gameState->field->GetCellValue(x,y-i) == playerId) c_max++;
                        if(gameState->field->GetCellValue(x,y-i) == -playerId) c_neg++;
                    }
                    if(y < gameState->fieldColumns-3){
                        if(gameState->field->GetCellValue(x,y+i) == playerId) d_max++;
                        if(gameState->field->GetCellValue(x,y+i) == -playerId) d_neg++;
                    }
                    if(x >= 3 && y >= 3){
                        if(gameState->field->GetCellValue(x-i,y-i) == playerId) e_max++;
                        if(gameState->field->GetCellValue(x-i,y-i) == -playerId) e_neg++;
                    }
                    if(y < gameState->fieldColumns-3 && x < gameState->fieldRows-3){
                        if(gameState->field->GetCellValue(x+i,y+i) == playerId) f_max++;
                        if(gameState->field->GetCellValue(x+i,y+i) == -playerId) f_neg++;
                    }
                    if(y >= 3 && x < gameState->fieldRows-3){
                        if(gameState->field->GetCellValue(x+i,y-i) == playerId) g_max++;
                        if(gameState->field->GetCellValue(x+i,y-i) == -playerId) g_neg++;
                    }
                }
                for(int i = -1; i < 3; i++){
                    if(i != 0)
                    {
                        if(x >= 1 && x < gameState->fieldRows-2){
                            if(gameState->field->GetCellValue(x+i,y) == playerId) a2_max++;
                            if(gameState->field->GetCellValue(x+i,y) == -playerId) a2_neg++;
                        }
                        if(x >= 2 && x < gameState->fieldRows-1 && y < gameState->fieldColumns-2 && y >= 1){
                            if(gameState->field->GetCellValue(x-i,y+i) == playerId) b2_max++;
                            if(gameState->field->GetCellValue(x-i,y+i) == -playerId) b2_neg++;
                         }
                        if(y >= 2 && y < gameState->fieldColumns-1){
                            if(gameState->field->GetCellValue(x,y-i) == playerId) c2_max++;
                            if(gameState->field->GetCellValue(x,y-i) == -playerId) c2_neg++;
                        }
                        if(y < gameState->fieldColumns-2 && y >= 1){
                            if(gameState->field->GetCellValue(x,y+i) == playerId) d2_max++;
                            if(gameState->field->GetCellValue(x,y+i) == -playerId) d2_neg++;
                        }
                        if(x >= 2 && x < gameState->fieldRows-1 && y >= 2 && y < gameState->fieldColumns-1){
                            if(gameState->field->GetCellValue(x-i,y-i) == playerId) e2_max++;
                            if(gameState->field->GetCellValue(x-i,y-i) == -playerId) e2_neg++;
                        }
                        if(y < gameState->fieldColumns-2  && y >= 1 && x < gameState->fieldRows-2 && x >= 1 ){
                            if(gameState->field->GetCellValue(x+i,y+i) == playerId) f2_max++;
                            if(gameState->field->GetCellValue(x+i,y+i) == -playerId) f2_neg++;
                        }
                        if(y >= 2 && y < gameState->fieldColumns-1 && x < gameState->fieldRows-2 && x >= 1){
                            if(gameState->field->GetCellValue(x+i,y-i) == playerId) g2_max++;
                            if(gameState->field->GetCellValue(x+i,y-i) == -playerId) g2_neg++;
                        }
                    }
                }

                //only add to rating if there are 4 in a row possible->
                if(a_max > 0 && a_neg > 0 ) a_max = a_neg = 0;
                if(b_max > 0 && b_neg > 0 ) b_max = b_neg = 0;
                if(c_max > 0 && c_neg > 0 ) c_max = c_neg = 0;
                if(d_max > 0 && d_neg > 0 ) d_max = d_neg = 0;
                if(e_max > 0 && e_neg > 0 ) e_max = e_neg = 0;
                if(f_max > 0 && f_neg > 0 ) f_max = f_neg = 0;
                if(g_max > 0 && g_neg > 0 ) g_max = g_neg = 0;

                if(a2_max > 0 && a2_neg > 0 ) a2_max = a2_neg = 0;
                if(b2_max > 0 && b2_neg > 0 ) b2_max = b2_neg = 0;
                if(c2_max > 0 && c2_neg > 0 ) c2_max = c2_neg = 0;
                if(d2_max > 0 && d2_neg > 0 ) d2_max = d2_neg = 0;
                if(e2_max > 0 && e2_neg > 0 ) e2_max = e2_neg = 0;
                if(f2_max > 0 && f2_neg > 0 ) f2_max = f2_neg = 0;
                if(g2_max > 0 && g2_neg > 0 ) g2_max = g2_neg = 0;

                max_max = max(max(max(max(max(max(a_max,b_max),c_max),d_max),e_max),f_max),g_max);
                max_neg = max(max(max(max(max(max(a_neg,b_neg),c_neg),d_neg),e_neg),f_neg),g_neg);

                max_max = max(max(max(max(max(max(max(a2_max,b2_max),c2_max),d2_max),e2_max),f2_max),g2_max),max_max);
                max_neg = max(max(max(max(max(max(max(a2_neg,b2_neg),c2_neg),d2_neg),e2_neg),f2_neg),g2_neg),max_neg);

                if(max_max == 3){
                    count_max++;
                    count_neg = 0;
                    rating = rating + pow(10,count_max + 3) * x; //4 in a lower line are more importend
                }
                else{
                    rating = rating + pow(10,max_max) * x; //4 in a lower line are more importend
                }

                if(max_neg == 3){
                    count_neg++;
                    count_max = 0;
                    rating = rating - pow(10,count_neg + 3) * x; //4 in a lower line are more importend
                }
                else{
                    rating = rating - pow(10,max_neg) * x; //4 in a lower line are more importend
                }
            }
        }
    }
    /*
    if(rating >= WINNIG_VALUE || rating <=-WINNIG_VALUE){
//#ifdef DEBUG
        cout << "Error to large rating value" << endl;
//#endif
        if(rating>0) return WINNIG_VALUE-1;
        else return -WINNIG_VALUE+1;
    }*/
    return rating;
}

int32_t RatingClass::HasWon(int playerId, int lastMove){
    int x,y;
    int32_t max_max,a_max,b_max,c_max,d_max,e_max,f_max,g_max;
    a_max = b_max = c_max = d_max = e_max = f_max = g_max = 0;
    y = lastMove;

    for(x = 0 ; x < gameState->fieldRows ; x++){
        if(gameState->field->GetCellValue(x,y) == playerId){
            break;
        }
    }

    for(int i = 1; i < 4; i++){
        if(x < gameState->fieldRows-3){
            if(gameState->field->GetCellValue(x+i,y) == playerId) a_max++;
        }
        if(x >= 3 && y < gameState->fieldColumns-3){
            if(gameState->field->GetCellValue(x-i,y+i) == playerId) b_max++;
         }
        if(y >= 3){
            if(gameState->field->GetCellValue(x,y-i) == playerId) c_max++;
        }
        if(y < gameState->fieldColumns-3){
            if(gameState->field->GetCellValue(x,y+i) == playerId) d_max++;
        }
        if(x >= 3 && y >= 3){
            if(gameState->field->GetCellValue(x-i,y-i) == playerId) e_max++;
        }
        if(y < gameState->fieldColumns-3 && x < gameState->fieldRows-3){
            if(gameState->field->GetCellValue(x+i,y+i) == playerId) f_max++;
        }
        if(y >= 3 && x < gameState->fieldRows-3){
            if(gameState->field->GetCellValue(x+i,y-i) == playerId) g_max++;
        }

        max_max = max(max(max(max(max(max(a_max,b_max),c_max),d_max),e_max),f_max),g_max);
        if(max_max == 3) return WINNIG_VALUE;
    }

    a_max = b_max = c_max = d_max = e_max = f_max = g_max = 0;
    max_max = 0;

    for(int i = -1; i < 3; i++){
        if(i != 0)
        {
            if(x >= 1 && x < gameState->fieldRows-2){
                if(gameState->field->GetCellValue(x+i,y) == playerId) a_max++;
            }
            if(x >= 2 && x < gameState->fieldRows-1 && y < gameState->fieldColumns-2 && y >= 1){
                if(gameState->field->GetCellValue(x-i,y+i) == playerId) b_max++;
             }
            if(y >= 2 && y < gameState->fieldColumns-1){
                if(gameState->field->GetCellValue(x,y-i) == playerId) c_max++;
            }
            if(y < gameState->fieldColumns-2 && y >= 1){
                if(gameState->field->GetCellValue(x,y+i) == playerId) d_max++;
            }
            if(x >= 2 && x < gameState->fieldRows-1 && y >= 2 && y < gameState->fieldColumns-1){
                if(gameState->field->GetCellValue(x-i,y-i) == playerId) e_max++;
            }
            if(y < gameState->fieldColumns-2  && y >= 1 && x < gameState->fieldRows-2 && x >= 1 ){
                if(gameState->field->GetCellValue(x+i,y+i) == playerId) f_max++;
            }
            if(y >= 2 && y < gameState->fieldColumns-1 && x < gameState->fieldRows-2 && x >= 1){
                if(gameState->field->GetCellValue(x+i,y-i) == playerId) g_max++;
            }

            max_max = max(max(max(max(max(max(a_max,b_max),c_max),d_max),e_max),f_max),g_max);
            if(max_max == 3){
#ifdef DEBUG
cout << "-------winning situation for playerid = " << playerId << ", after move = " << lastMove << "----------" << endl;
#endif
                return WINNIG_VALUE;
            }
        }
    }
    return 0;
}

void RatingClass::PrintDebug(){
    cout << "ToDo Raiting ausgabe";
}

