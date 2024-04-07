

#include <stdint.h>

typedef struct FoodOrder {
    char name[20];
    uint8_t valid;
    int id;
    int box; // 0 when it has not been delivered
} FoodOrder;
void FoodOrder_Init(FoodOrder* order) {
    order->valid = 0;
    order->box = 0;
    for(int i = 0; i < 20; ++i){
    	order->name[i] = '\0';
    }
}
