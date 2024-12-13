#pragma config(Sensor, S1,     sensorEsquerdo, sensorLightActive)
#pragma config(Sensor, S2,     sensorDireito,  sensorLightActive)
#pragma config(Motor,  motorB,          MotorDireito,  tmotorNXT, PIDControl, driveRight, encoder)
#pragma config(Motor,  motorC,          MotorEsquerdo, tmotorNXT, PIDControl, driveLeft, encoder)

// Definições
#define ReflexoLuz 30 
#define VelocidadeBase 50
#define MudancaVel 20

task main() {
    while (true) {
        // Leituras dos sensores
        int LeituraEsquerdo = SensorValue[sensorEsquerdo];
        int LeituraDireito = SensorValue[sensorDireito];

        if (LeituraEsquerdo < ReflexoLuz && LeituraDireito < ReflexoLuz) {
            // Ambos sensores na linha (segue reto)
            motor[MotorEsquerdo] = VelocidadeBase;
            motor[MotorDireito] = VelocidadeBase;
            nxtDisplayCenteredTextLine(1, "Status: Reto");

        } else if (LeituraEsquerdo < ReflexoLuz && LeituraDireito >= ReflexoLuz) {
            // Linha à direita (gira para a direita)
            motor[MotorEsquerdo] = VelocidadeBase + MudancaVel;
            motor[MotorDireito] = -MudancaVel;
            nxtDisplayCenteredTextLine(1, "Status: Direita");

        } else if (LeituraEsquerdo >= ReflexoLuz && LeituraDireito < ReflexoLuz) {
            // Linha à esquerda (gira para a esquerda)
            motor[MotorEsquerdo] = -MudancaVel;
            motor[MotorDireito] = VelocidadeBase + MudancaVel;
            nxtDisplayCenteredTextLine(1, "Status: Esquerda");

        } else {
            // Nenhum sensor detecta a linha (girar sobre o eixo para procurar)
            motor[MotorEsquerdo] = VelocidadeBase / 2;
            motor[MotorDireito] = -VelocidadeBase / 2;
            nxtDisplayCenteredTextLine(1, "Status: Perdido");
        }

        nxtDisplayCenteredTextLine(2, "Esq: %d", LeituraEsquerdo);
        nxtDisplayCenteredTextLine(3, "Dir: %d", LeituraDireito);

        // Atraso para evitar sobrecarga
        wait1Msec(50);
    }
}
