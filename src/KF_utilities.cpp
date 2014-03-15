#include "KF_utilities.hpp"

using std::chrono::system_clock;

static int increment = 0;
guidType generateGUID() {
    std::default_random_engine rEngine;
    
    rEngine.seed(time(NULL) + increment++);

    stringType hexChars = "0123456789ABCDEF";

    //hex values from 0 to 16
    std::uniform_int_distribution<int> rCharDistribution(0, 15);

    guidType guid = ""; 

    for (int i = 0; i < 4 * 2; i++) {
	guid += hexChars[rCharDistribution(rEngine)];
    }
    
    guid += "-";

    for (int i = 0; i < 2 * 2; i++) {
	guid += hexChars[rCharDistribution(rEngine)];
    }

    guid += "-";

    for (int i = 0; i < 4 * 2; i++) {
	guid += hexChars[rCharDistribution(rEngine)];
    }

    guid +=  "-";
    
    for (int i = 0; i < 8 * 2; i++) {
	guid += hexChars[rCharDistribution(rEngine)];
    }

    return guid;
}
