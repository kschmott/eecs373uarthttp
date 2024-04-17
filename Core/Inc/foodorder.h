

#include <stdint.h>
#define MAX_FOOD_ORDERS 4
int box_count;

typedef enum {
	Empty,
	OpenedDelivery,
	Occupied,
	OpenedQR
} DeliveryState;

typedef struct FoodOrder {
    char name[20];
    uint8_t valid;
    int id;
    int box; // 0 when it has not been delivered
    DeliveryState state;
} FoodOrder;
void FoodOrder_Init(FoodOrder* order) {
    order->valid = 0;
    order->box = 0;
    for(int i = 0; i < 20; ++i){
    	order->name[i] = '\0';
    }
}

int FoodOrder_Equal(FoodOrder* lhs, FoodOrder* rhs) {
	if (rhs->valid == 0 && lhs->valid == 0) return 1;
	if (rhs->valid == 0 || lhs->valid == 0) return 0;

	if (strcmp(lhs->name, rhs->name)) return 0;
	return lhs->id == rhs->id && lhs->valid == rhs->valid && lhs->box == rhs->box && lhs->state == rhs->state;
}

int FoodOrders_Equal(FoodOrder lhs[MAX_FOOD_ORDERS], FoodOrder rhs[MAX_FOOD_ORDERS]) {
	for (int i = 0; i < MAX_FOOD_ORDERS; i++) {
		if (!FoodOrder_Equal(&lhs[i], &rhs[i])) return 0;
	}
	return 1;
}

void FoodOrders_Copy(FoodOrder dest[MAX_FOOD_ORDERS], FoodOrder src[MAX_FOOD_ORDERS]){
	for (int i = 0; i < MAX_FOOD_ORDERS; i++) {
			dest[i] = src[i];
		}
}

int FoodOrders_FindEmpty(FoodOrder orders[MAX_FOOD_ORDERS]) {
	int boxes[MAX_FOOD_ORDERS] = {1, 1, 1, 1};

	for (int i = 0; i < MAX_FOOD_ORDERS; i++) {
		if (orders[i].box) {
			boxes[orders[i].box - 1] = 0;
		}
	}

	for (int i = 0; i < box_count; i++) {
		if (boxes[i]) return i + 1;
	}

	printf("Find empty: failed to find an empty box.\r\n");
	return -1;
}

int FoodOrder_FindIndex(int id, FoodOrder orders[MAX_FOOD_ORDERS]) {
	for (int i = 0; i < MAX_FOOD_ORDERS; i++) {
		if (orders[i].id == id) return i;
	}

	printf("Find index: failed to find button corresponding to a given id.\r\n");
	return -1;
}


