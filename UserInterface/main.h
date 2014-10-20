#pragma once
#include <iostream>
#include <vector>
#include <string>

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/gregorian_calendar.hpp>

#include "CommandAdd.h"
#include "CommandDelete.h"
#include "CommandEdit.h"
#include "CommandDone.h"
#include "CommandSearch.h"
#include "CommandClear.h"
#include "CommandUndo.h"
#include "CommandRedo.h"
#include "LogicData.h"
#include "State.h"
#include "Task.h"

#include "MainWindow.h"

using namespace std;
using namespace boost::posix_time;
using namespace boost::gregorian;

