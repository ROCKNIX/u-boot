#ifndef __ODROID_PMIC
#define __ODROID_PMIC

#include <aml_i2c.h>

#define RK818_CHIP_ADDR		0x1c
#define RK817_CHIP_ADDR		0x20

#define RK818_I2C_BUS		AML_I2C_MASTER_AO
#define RK817_I2C_BUS		AML_I2C_MASTER_D

#define RK818_BUCK1_ON_VSEL	0x2f
#define RK818_BUCK2_ON_VSEL	0x33
#define RK818_BUCK4_ON_VSEL	0x38
#define RK818_LDO9_ON_VSEL	0x54
#define RK818_DCDC_EN_REG	0x23
#define RK818_LDO_EN_REG	0x24

#define RK817_BUCK2_ON_VSEL	0xbe
#define RK817_BUCK3_ON_VSEL	0xc1
#define RK817_LDO8_ON_VSEL	0xda

#define RK817_POWER_EN0		0xb1
#define RK817_POWER_EN1		0xb2
#define RK817_POWER_EN2		0xb3
#define RK817_POWER_EN3		0xb4

#define RK817_SYS_CFG(i)	(0xf1 + (i))

#define RK817_INT_STS_REG0	0xf8
#define RK817_INT_STS_MSK_REG0	0xf9
/* power key is active low: press = falling edge, release = rising edge */
#define RK817_PWRON_FALL	0x01
#define RK817_PWRON_RISE	0x02
#define RK817_PWRON_IRQS	(RK817_PWRON_FALL | RK817_PWRON_RISE)

#define KEY_MENU_LEFT	GPIOEE(GPIOX_17)
#define KEY_MENU_RIGHT	GPIOEE(GPIOX_16)

enum pwron_src {
	PWRON_KEY = 0,
	PWRON_USB,
	PWRON_RTC,
	PWRON_RESET,
	PWRON_KEY_LP,
	PWRON_RECOVER,
};

void odroid_pmic_init(void);
int board_check_power(void);

#endif
