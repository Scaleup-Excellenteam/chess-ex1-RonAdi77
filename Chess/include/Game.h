#pragma once

#include "Chess.h"
#include "Board.h"
#include "Move.h"
#include "PriorityAlgo.h"
#include "MyExceptions.h"
#include "ThreadManger.h"
#include <chrono>


void autoPlayGame(const std::string&, COLOR, int, int);
void userPlayGame(const std::string&, COLOR, int, int);