#pragma config(Sensor, S1,     sensorDireito,         sensorLightActive)
#pragma config(Sensor, S2,     sensorEsquerdo,         sensorLightActive)
#pragma config(Motor,  motorB,          MotorDireito,    tmotorNXT, PIDControl, driveRight, encoder)
#pragma config(Motor,  motorC,          MotorEsquerdo,     tmotorNXT, PIDControl, driveLeft, encoder)

// Definições dos reflexões, velocidade padrão e a mudança para as curvas
#define ReflexoLuz 50
#define VelocidadeBase 90
#define MudancaVel 40

task main(){
	while(true){
		//Leitura dos sensores
		int LeituraEsquerdo = SensorValue[sensorEsquerdo];
		int LeituraDireito = SensorValue[sensorDireito];

		//Condição para os motores
		if (LeituraEsquerdo < ReflexoLuz && LeituraDireito >= ReflexoLuz){
			// Ajusta para a esquerda
			motor[MotorEsquerdo] = VelocidadeBase - MudancaVel;
			motor[MotorDireito] = VelocidadeBase + MudancaVel;}
		else if (LeituraDireito < ReflexoLuz && LeituraEsquerdo >= ReflexoLuz) {
			// Ajusta para a direita
			motor[MotorEsquerdo] = VelocidadeBase + MudancaVel;
			motor[MotorDireito] = VelocidadeBase - MudancaVel;}
		else if (LeituraEsquerdo < ReflexoLuz && LeituraDireito < ReflexoLuz) {
			// Mantenha em frente
			motor[MotorEsquerdo] = VelocidadeBase;
			motor[MotorDireito] = VelocidadeBase;}
		else {
			// Parar ou ajustar o percurso
			motor[MotorEsquerdo] = 0;
			motor[MotorDireito] = 0;}

		// Atraso para evitar sobrecarga
		wait1Msec(25);
	}
}
