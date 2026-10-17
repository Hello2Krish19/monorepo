#include "g4_testing.h"
#if (G4_TESTING_CHOSEN == TEST_ONBOARDING_2027)

#include <stdint.h>

#include "common/phal_G4/gpio/gpio.h"
#include "common/phal_G4/rcc/rcc.h"
#include "common/utils/countof.h"
#include "common/rtos/rtos.h"
#include "common/phal_G4/fdcan/fdcan.h"
#include "can_library/can_common.h"
#include "common/phal_G4/pin_defs/g474ret6.h"

#include "main.h"


// Hmmm... something may go here
#define LED_USER_PORT GPIOA
#define LED_USER_PIN  5


PHAL_GPIO_InitConfig_t gpio_config[] = {
    PHAL_GPIO_INIT_OUTPUT(LED_USER_PORT, LED_USER_PIN, GPIO_OUTPUT_LOW_SPEED),
};

void HardFault_Handler();

// Hmmm... something(s) may go here

static void ledblink1(void);
RTOS_DEFINE_TASK(ledblink1, 500, TASK_PRIORITY_NORMAL, 256);


int main() {
    
    // NUCLEO-G474RE does not have an external oscillator so use the internal 16MHz HSI clock
    PHAL_RCC_init(PHAL_RCC_HSI_16MHZ);

    if (!PHAL_GPIO_init(gpio_config, countof(gpio_config))) {
        HardFault_Handler();
    }

    PHAL_GPIO_write(LED_USER_PORT, LED_USER_PIN, 1);

    // while (1) {
    //     __asm__("nop");
    // }

    // Hmmm... something(s) may go here
     RTOS_START_TASK(ledblink1);

    vTaskStartScheduler();

       while (1) {
        __asm__("nop");
    }

    return 0;
}

static void ledblink1(void) {
    while(1) {
        vTaskDelay(500);
        PHAL_GPIO_toggle(LED_USER_PORT, LED_USER_PIN);
    }

}


void HardFault_Handler() {
    while (1) {
        __asm__("nop");
    }
}

#endif // G4_TESTING_CHOSEN == TEST_ONBOARDING_2027
