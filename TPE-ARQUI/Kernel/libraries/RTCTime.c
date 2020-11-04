#include <RTCTime.h>
#include <lib.h>
#include <utils.h>

uint8_t getDecimalTimeInfo(t_timeInfo info){
      if (info != HOURS && info != MINUTES && info != SECONDS && info != DAY && info != MONTH && info != YEAR)
            return 0;

      return BSDToInt(getBSDTimeInfo(info));
}
