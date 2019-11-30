#pragma config(Sensor, S2,     ReverseBtn,     sensorEV3_Touch)
#pragma config(Sensor, S3,     Gyro,           sensorEV3_Gyro)
#pragma config(Sensor, S4,     Eyes,           sensorEV3_Ultrasonic)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

typedef enum moveMode
{
	mmFwd = 0,
	mmBwd = 1,
	mmLft = 2,
	mmRit = 3,
	mmStp = 4

} moveMode;

typedef struct InstructionSet
{
	short movementMode;
	int countOfUses;
	InstructionSet* nextInstructionSet;
}

void DriveMotors();
void RegisterButtons();
const float maxFwdSpeed = 20;
const float maxTrnSpeed = 15;
const float maxBwdSpeed = 15;

float fwdSpeed = maxFwdSpeed;
float trnSpeed = maxTrnSpeed;
float bwdSpeed = maxBwdSpeed;
short movementMode = mmStp;
InstructionSet instructions;

task main()
{
	resetGyro(S3);
	while(true)
	{
		float dist = getUSDistance(S4);
		if(dist < 15)
			fwdSpeed = maxFwdSpeed * 0.2;
		else
			fwdSpeed = maxFwdSpeed;

		DriveMotors();
		RegisterButtons();
	}
}

void DriveMotors()
{
		switch(movementMode)
		{
			case (short)mmFwd:
				setMultipleMotors(fwdSpeed, 0, 1);
			break;
			case (short)mmBwd:
				setMultipleMotors(bwdSpeed, 0, 1);
			break;
			case (short)mmLft:
				setMotor(0, -trnSpeed);
				setMotor(1, trnSpeed);
			break;
			case (short)mmRit:
				setMotor(0, trnSpeed);
				setMotor(1, -trnSpeed);
			break;
			case (short)mmStp:
				setMultipleMotors(0, 0, 1);
			break;
		}
}

void RegisterButtons()
{
		if(getButtonPress(buttonLeft) == 1)
			movementMode = (short)mmLft;
		else if(getButtonPress(buttonRight) == 1)
			movementMode = (short)mmRit;
		else if(getButtonPress(buttonUp) == 1)
			movementMode = (short)mmFwd;
		else if(getButtonPress(buttonDown) == 1)
			movementMode = (short)mmBwd;
		else if(getButtonPress(buttonEnter) == 1)
			movementMode = (short)mmStp;
}
