#include "suncloud.h"

SunCloud::SunCloud() {
    name = "SunCloud";
    hp = lifetime = 2500;
    time = int(10.0 * 1000 / 33);
    product = 50;
}

void SunCloud::advance(int phase){
    if (!phase)
        return;
    update();
    hp -= 1;
    if (hp <= 0)
        delete this;
}
