/*
Code running on MISC Viking 3 - T1's MR02-Manipulator module.

descr...


Authors: Rein Åsmund Torsvik & Jonas Haldorsen, MISC 2018-07-06
*/

#include "_methods_motors.h"

void motor_setup()
{
	pinMode(PIN_SH_ROT_EN, OUTPUT);
	pinMode(PIN_SH_ROT_IN1, OUTPUT);
	pinMode(PIN_SH_ROT_IN2, OUTPUT);
	pinMode(PIN_SH_ROT_ADC, INPUT);

	pinMode(PIN_SH_EXT_EN, OUTPUT);
	pinMode(PIN_SH_EXT_IN1, OUTPUT);
	pinMode(PIN_SH_EXT_IN2, OUTPUT);
	pinMode(PIN_SH_EXT_ADC, INPUT);

	pinMode(PIN_EL_EXT_EN, OUTPUT);
	pinMode(PIN_EL_EXT_IN1, OUTPUT);
	pinMode(PIN_EL_EXT_IN2, OUTPUT);
	pinMode(PIN_EL_EXT_ADC, INPUT);

	pinMode(PIN_WR_ROT_EN, OUTPUT);
	pinMode(PIN_WR_ROT_IN1, OUTPUT);
	pinMode(PIN_WR_ROT_IN2, OUTPUT);
	pinMode(PIN_WR_ROT_ADC, INPUT);

	pinMode(PIN_WR_EXT_EN, OUTPUT);
	pinMode(PIN_WR_EXT_IN1, OUTPUT);
	pinMode(PIN_WR_EXT_IN2, OUTPUT);
	pinMode(PIN_WR_EXT_ADC, INPUT);

}

void motor_run(byte PIN, int ControlValue) {
	motor_set_dir(PIN, ControlValue);
	if (ControlValue < 0) { ControlValue = -ControlValue; }

	analogWrite(PIN, ControlValue);

}

void motor_set_dir(byte PIN, int ControlValue) {

	if (ControlValue >= 0) {
		switch (PIN)
		{
		case PIN_SH_ROT_EN: SH_ROT_dir_pos();
		case PIN_SH_EXT_EN: SH_EXT_dir_pos();
		case PIN_EL_EXT_EN: EL_EXT_dir_pos();
		case PIN_WR_ROT_EN:	WR_ROT_dir_pos();
		case PIN_WR_EXT_EN: WR_EXT_dir_pos();
		default:
			break;
		}
	}

	if (ControlValue < 0) {
		switch (PIN)
		{
		case PIN_SH_ROT_EN: SH_ROT_dir_neg();
		case PIN_SH_EXT_EN: SH_EXT_dir_neg();
		case PIN_EL_EXT_EN: EL_EXT_dir_neg();
		case PIN_WR_ROT_EN:	WR_ROT_dir_neg();
		case PIN_WR_EXT_EN: WR_EXT_dir_neg();
		default:
			break;
		}
	}

}



