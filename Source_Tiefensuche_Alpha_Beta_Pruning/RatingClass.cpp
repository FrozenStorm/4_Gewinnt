#include <math.h>
#include "RatingClass.h"
#include "GameStateClass.h"
#include "FieldClass.h"

RatingClass::RatingClass(GameStateClass &_gameState) : gameState(_gameState){
}
//v26 in theaigames.com
int32_t RatingClass::GetRating(int playerId) {
    int32_t rating = 0;
    int32_t MaxblockRating = 1;
    int32_t NegblockRating = -1;
    int32_t MaxfourInARow = 0;
    int32_t NegfourInARow = 0;

    // 4-times the same for Loops, for all the four possible directions of 4 in a row.

    //   ||||||||
    for(int x = 0 ; x < gameState.fieldRows-3 && MaxfourInARow != 4 && NegfourInARow != 4; x++){
        for(int y = 0 ; y < gameState.fieldColumns && MaxfourInARow != 4 && NegfourInARow != 4; y++){
            MaxblockRating = 1;
            NegblockRating = -1;
            MaxfourInARow = 0;
            NegfourInARow = 0;
            for(int i = 0; (i < 4) && !((NegfourInARow > 0) && (MaxfourInARow > 0)); i++){
                if(gameState.field->GetCellValue(x+i,y) == playerId){
                    MaxblockRating = MaxblockRating * 10;                   // 10 ^ (number of stones in a row) for the rating
                    MaxfourInARow++;
                }
                if(gameState.field->GetCellValue(x+i,y) == -playerId){
                    NegblockRating = NegblockRating * 10;
                    NegfourInARow++;
                }
            }
            if(!((NegfourInARow > 0) && (MaxfourInARow > 0))) rating = rating + (MaxblockRating + NegblockRating); // Only add to rating if 4 in a row are possible in this block
        }
    }
    //   -------
    for(int x = 0 ; x < gameState.fieldRows && MaxfourInARow != 4 && NegfourInARow != 4; x++){
        for(int y = 0 ; y < gameState.fieldColumns-3 && MaxfourInARow != 4 && NegfourInARow != 4; y++){
            MaxblockRating = 1;
            NegblockRating = -1;
            MaxfourInARow = 0;
            NegfourInARow = 0;
            for(int i = 0; (i < 4) && !((NegfourInARow > 0) && (MaxfourInARow > 0)); i++){
                if(gameState.field->GetCellValue(x,y+i) == playerId){
                    MaxblockRating = MaxblockRating * 10;
                    MaxfourInARow++;
                }
                if(gameState.field->GetCellValue(x,y+i) == -playerId){
                    NegblockRating = NegblockRating * 10;
                    NegfourInARow++;
                }
            }
            if(!((NegfourInARow > 0) && (MaxfourInARow > 0))) rating = rating + MaxblockRating + NegblockRating;
        }
    }
    //         ``````
    for(int x = 0 ; x < gameState.fieldRows-3 && MaxfourInARow != 4 && NegfourInARow != 4; x++){
        for(int y = 0 ; y < gameState.fieldColumns-3 && MaxfourInARow != 4 && NegfourInARow != 4; y++){
            MaxblockRating = 1;
            NegblockRating = -1;
            MaxfourInARow = 0;
            NegfourInARow = 0;
            for(int i = 0; (i < 4) && !((NegfourInARow > 0) && (MaxfourInARow > 0)); i++){
                if(gameState.field->GetCellValue(x+i,y+i) == playerId){
                    MaxblockRating = MaxblockRating * 10;
                    MaxfourInARow++;
                }
                if(gameState.field->GetCellValue(x+i,y+i) == -playerId){
                    NegblockRating = NegblockRating * 10;
                    NegfourInARow++;
                }
            }
            if(!((NegfourInARow > 0) && (MaxfourInARow > 0))) rating = rating + MaxblockRating + NegblockRating;
        }
    }
    //      ///////
    for(int x = 0 ; x < gameState.fieldRows-3 && MaxfourInARow != 4 && NegfourInARow != 4; x++){
        for(int y = 3 ; y < gameState.fieldColumns && MaxfourInARow != 4 && NegfourInARow != 4; y++){
            MaxblockRating = 1;
            NegblockRating = -1;
            MaxfourInARow = 0;
            NegfourInARow = 0;
            for(int i = 0; (i < 4) && !((NegfourInARow > 0) && (MaxfourInARow > 0)); i++){
                if(gameState.field->GetCellValue(x+i,y-i) == playerId){
                    MaxblockRating = MaxblockRating * 10;
                    MaxfourInARow++;
                }
                if(gameState.field->GetCellValue(x+i,y-i) == -playerId){
                    NegblockRating = NegblockRating * 10;
                    NegfourInARow++;
                }
            }
            if(!((NegfourInARow > 0) && (MaxfourInARow > 0))) rating = rating + MaxblockRating + NegblockRating;
        }
    }

    // If one there was one time 4 in a row it's a winning node
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


/*
//V29 in theaigames.com
int32_t RatingClass::GetRating(int playerId) {
    const int SerieMultiplier = 5;
    int32_t rating = 0;
    int emptyRow = -1;
    int cellValue = 0;
    int32_t MaxblockRating = 1;
    int32_t NegblockRating = -1;
    int32_t MaxfourInARow = 0;
    int32_t NegfourInARow = 0;
    //   ||||||||
    for(int x = 0 ; x < gameState.fieldRows-3 && MaxfourInARow != 4 && NegfourInARow != 4; x++){
        for(int y = 0 ; y < gameState.fieldColumns && MaxfourInARow != 4 && NegfourInARow != 4; y++){
            emptyRow = -1;
            MaxblockRating = 1;
            NegblockRating = -1;
            MaxfourInARow = 0;
            NegfourInARow = 0;
            for(int i = 0; (i < 4) && !((NegfourInARow > 0) && (MaxfourInARow > 0)); i++){
                cellValue = gameState.field->GetCellValue(x+i,y);
                if(cellValue == 0){
                    emptyRow = x+i;
                }
                else if(cellValue == playerId){
                    MaxblockRating = MaxblockRating * SerieMultiplier;
                    MaxfourInARow++;
                }
                else {
                    NegblockRating = NegblockRating * SerieMultiplier;
                    NegfourInARow++;
                }
            }
            if((MaxfourInARow == 3) && (emptyRow != -1)) MaxblockRating = MaxblockRating * pow(10, emptyRow);
            if((NegfourInARow == 3) && (emptyRow != -1)) NegblockRating = NegblockRating * pow(10, emptyRow);
            if(!((NegfourInARow > 0) && (MaxfourInARow > 0))) rating = rating + (MaxblockRating + NegblockRating); //Interessiert mich nur wenn 4 zu vervollständigen möglich ist
        }
    }
    //   -------
    for(int x = 0 ; x < gameState.fieldRows && MaxfourInARow != 4 && NegfourInARow != 4; x++){
        for(int y = 0 ; y < gameState.fieldColumns-3 && MaxfourInARow != 4 && NegfourInARow != 4; y++){
            emptyRow = -1;
            MaxblockRating = 1;
            NegblockRating = -1;
            MaxfourInARow = 0;
            NegfourInARow = 0;
            for(int i = 0; (i < 4) && !((NegfourInARow > 0) && (MaxfourInARow > 0)); i++){
                cellValue = gameState.field->GetCellValue(x,y+i);
                if(cellValue == 0){
                    emptyRow = x;
                }
                else if(cellValue == playerId){
                    MaxblockRating = MaxblockRating * SerieMultiplier;
                    MaxfourInARow++;
                }
                else {
                    NegblockRating = NegblockRating * SerieMultiplier;
                    NegfourInARow++;
                }
            }
            if((MaxfourInARow == 3) && (emptyRow != -1)) MaxblockRating = MaxblockRating * pow(10, emptyRow);
            if((NegfourInARow == 3) && (emptyRow != -1)) NegblockRating = NegblockRating * pow(10, emptyRow);
            if(!((NegfourInARow > 0) && (MaxfourInARow > 0))) rating = rating + (MaxblockRating + NegblockRating); //Interessiert mich nur wenn 4 zu vervollständigen möglich ist
         }
    }
    //         ``````
    for(int x = 0 ; x < gameState.fieldRows-3 && MaxfourInARow != 4 && NegfourInARow != 4; x++){
        for(int y = 0 ; y < gameState.fieldColumns-3 && MaxfourInARow != 4 && NegfourInARow != 4; y++){
            emptyRow = -1;
            MaxblockRating = 1;
            NegblockRating = -1;
            MaxfourInARow = 0;
            NegfourInARow = 0;
            for(int i = 0; (i < 4) && !((NegfourInARow > 0) && (MaxfourInARow > 0)); i++){
                cellValue = gameState.field->GetCellValue(x+i,y+i);
                if(cellValue == 0){
                    emptyRow = x+i;
                }
                else if(cellValue == playerId){
                    MaxblockRating = MaxblockRating * SerieMultiplier;
                    MaxfourInARow++;
                }
                else {
                    NegblockRating = NegblockRating * SerieMultiplier;
                    NegfourInARow++;
                }
            }
            if((MaxfourInARow == 3) && (emptyRow != -1)) MaxblockRating = MaxblockRating * pow(10, emptyRow);
            if((NegfourInARow == 3) && (emptyRow != -1)) NegblockRating = NegblockRating * pow(10, emptyRow);
            if(!((NegfourInARow > 0) && (MaxfourInARow > 0))) rating = rating + (MaxblockRating + NegblockRating); //Interessiert mich nur wenn 4 zu vervollständigen möglich ist

        }
    }
    //      ///////
    for(int x = 0 ; x < gameState.fieldRows-3 && MaxfourInARow != 4 && NegfourInARow != 4; x++){
        for(int y = 3 ; y < gameState.fieldColumns && MaxfourInARow != 4 && NegfourInARow != 4; y++){
            emptyRow = -1;
            MaxblockRating = 1;
            NegblockRating = -1;
            MaxfourInARow = 0;
            NegfourInARow = 0;
            for(int i = 0; (i < 4) && !((NegfourInARow > 0) && (MaxfourInARow > 0)); i++){
                cellValue = gameState.field->GetCellValue(x+i,y-i);
                if(cellValue == 0){
                    emptyRow = x+i;
                }
                else if(cellValue == playerId){
                    MaxblockRating = MaxblockRating * SerieMultiplier;
                    MaxfourInARow++;
                }
                else {
                    NegblockRating = NegblockRating * SerieMultiplier;
                    NegfourInARow++;
                }
            }
            if((MaxfourInARow == 3) && (emptyRow != -1)) MaxblockRating = MaxblockRating * pow(10, emptyRow);
            if((NegfourInARow == 3) && (emptyRow != -1)) NegblockRating = NegblockRating * pow(10, emptyRow);
            if(!((NegfourInARow > 0) && (MaxfourInARow > 0))) rating = rating + (MaxblockRating + NegblockRating); //Interessiert mich nur wenn 4 zu vervollständigen möglich ist

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


void RatingClass::PrintDebug(){
    cout << "ToDo Raiting ausgabe";
}

