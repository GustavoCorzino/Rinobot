#pragma config(Sensor, S1,     sensorCentral,  sensorLightActive)
#pragma config(Motor,  motorB,          MotorDireito,  tmotorNXT, PIDControl, driveRight, encoder)
#pragma config(Motor,  motorC,          MotorEsquerdo, tmotorNXT, PIDControl, driveLeft, encoder)

// Definicoes dos reflexoes, velocidade padrao e a mudanca para as curvas
#define ReflexoLuz 15
#define VelocidadeBase 90
#define MudancaVel 40

task main(){
	// Vari�vel para guardar a ultima direcao (1 = esquerda, -1 = direita, 0 = reto)
	int ultimaDirecao = 0;

	while(true){
		// Leitura do sensor central
		int LeituraSensor = SensorValue[sensorCentral];

		// Condicao para os motores
		if (LeituraSensor >= ReflexoLuz) {
			// Linha detectada (segue reto)
			motor[MotorEsquerdo] = VelocidadeBase;
			motor[MotorDireito] = VelocidadeBase;
			ultimaDirecao = 0; // Atualiza direcao para "reto"

			// Exibir mensagem
			nxtDisplayCenteredTextLine(1, "Status: Reto");
			} else {
			// Linha perdida (corrigir com base na ultima direcao)
			if (ultimaDirecao <= 0) {
				// Girar para direita (se estava reto ou virando para direita)
				motor[MotorEsquerdo] = VelocidadeBase;
				motor[MotorDireito] = -MudancaVel;
				ultimaDirecao = -1; // Atualiza para direita

				// Exibir mensagem
				nxtDisplayCenteredTextLine(1, "Status: Direita");
				} else {
				// Girar � esquerda
				motor[MotorEsquerdo] = -MudancaVel;
				motor[MotorDireito] = VelocidadeBase;
				ultimaDirecao = 1; // Atualiza para esquerda

				// Exibir mensagem
				nxtDisplayCenteredTextLine(1, "Status: Esquerda");
			}
		}

		// Exibir a velocidade na tela
		nxtDisplayCenteredTextLine(2, "Velocidade: %d", VelocidadeBase);

		// Atraso para evitar sobrecarga
		wait1Msec(25);
	}
}
