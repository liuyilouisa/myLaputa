#include "blockcloud.h"

BlockCloud::BlockCloud() {
    name = "BlockCloud";
    hp = lifetime = 5000;
}

void BlockCloud::advance(int phase){
    if (!phase)
        return;
    update();
    hp -= 1;
    if (hp <= 0)
        delete this;
}
