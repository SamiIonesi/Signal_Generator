#include <msp430.h>
#include <stdbool.h>
#include <math.h>

//facem amprente pentru functiile noastre
void Init_GPIO();
void Software_Trim();
void Show_good_carachter();
void Clock_System();
void Pin66();
void PWM_P50();
void Button_P41();
void Button_P23();
void UART();
void DAC();
void Semnal_pin_message();
void Error_message();
void Semnal_pin_PWM_message();
void Question_Duty_Cicle_message();
void Duty_Cicle_message();
void Freq_modify_message();
void Choose_samples_message();
void Samples_modified_message();
void InfoMenu_message();

#define MCLK_FREQ_MHZ 24

unsigned int semnalSinusoidal[100]={2048, 2176, 2304, 2431, 2557, 2680, 2801, 2919, 3034, 3145, 3251, 3353, 3449, 3540, 3625, 3704, 3776, 3842, 3900, 3951,
                       3995, 4031, 4059, 4079, 4091, 4095, 4091, 4079, 4059, 4031, 3995, 3951, 3900, 3842, 3776, 3704, 3625, 3540, 3449, 3353,
                       3251, 3145, 3034, 2919, 2801, 2680, 2557, 2431, 2304, 2176, 2048, 1919, 1791, 1664, 1538, 1415, 1294, 1176, 1061, 950,
                       844, 742, 646, 555, 470, 391, 319, 253, 195, 144, 100, 64, 36, 16, 4, 0, 4, 16, 36, 64, 100, 144, 195, 253, 319, 391,
                       470, 555, 646, 742, 844, 950, 1061, 1176, 1294, 1415, 1538, 1664, 1791, 1919};

volatile unsigned char menu[] = {13 , 10, 'S', 'I', 'G', 'N', 'A', 'L', ' ', 'G', 'E', 'N', 'E', 'R', 'A', 'T', 'O', 'R', 13, 10, 13, 10,
                                 'A', 'l', 'e', 'g', 'e', ' ', 'm', 'o', 'd', 'u', 'l', ' ', 'd', 'e', ' ', 'l', 'u', 'c', 'r', 'u', ' ', '(', 'a', '-', 'i', ')', ':', 13, 10,
                                 9, 'a', '.', ' ', 'V', 'o', 'u', 't', ' ', 'c', 'o', 'n', 's', 't', 'a', 'n', 't', 'a', '.', 13, 10,
                                 9, 'b', '.', ' ', 'S', 'e', 'm', 'n', 'a', 'l', ' ', 's', 'i', 'n', 'u', 's', 'o', 'i', 'd', 'a', 'l', '.', 13, 10,
                                 9, 'c', '.', ' ', 'S', 'e', 'm', 'n', 'a', 'l', ' ', 't', 'r', 'i', 'u', 'n', 'g', 'h', 'i', '.', 13, 10,
                                 9, 'd', '.', ' ', 'S', 'e', 'm', 'n', 'a', 'l', ' ', 'r', 'a', 'm', 'p', 'a', '.', 13, 10,
                                 9, 'e', '.', ' ', 'S', 'e', 'm', 'n', 'a', 'l', ' ', 'P', 'W', 'M', '.', 13, 10,
                                 9, 'f', '.', ' ', 'S', 'e', 'm', 'n', 'a', 'l', ' ', 't', 'r', 'a', 'p', 'e', 'z', '.', 13, 10,
                                 9, 'g', '.', ' ', 'S', 'e', 'm', 'n', 'a', 'l', ' ', 'd', 'i', 'n', 't', 'e', ' ', 'd', 'e', ' ', 'f', 'i', 'e', 'r', 'a', 's', 't', 'r', 'a', 'u', '.', 13, 10,
                                 9, 'h', '.', ' ', 'A', 'r', 'c', ' ', 'd', 'e', ' ', 's', 'i', 'n', 'u', 's', ' ', 'p', 'o', 'z', 'i', 't', 'i', 'v', '.', 13, 10,
                                 9, 'i', '.', ' ', 'A', 'r', 'c', ' ', 'd', 'e', ' ', 's', 'i', 'n', 'u', 's', ' ', 'n', 'e', 'g', 'a', 't', 'i', 'v', '.', 13, 10,
                                 13, 10, 'A', 'p', 'a', 's', 'a', ' ', 't', 'a', 's', 't', 'a', ' ', '\'', 's', '\'', ' ', 'p', 'e', 'n', 't', 'r', 'u', ' ', 'a',
                                 ' ', 's', 'c', 'h', 'i', 'm', 'b', 'a', ' ', 'n', 'u', 'm', 'a', 'r', 'u', 'l', ' ', 'd', 'e', ' ', 'e', 's', 'a', 'n', 't', 'i', 'o', 'a', 'n', 'e',
                                 '(', 'i', 'm', 'p', 'l', 'i', 'c', 'i', 't', ' ', 'e', 's', 't', 'e', ' ', '1', '0', '0', ')', 13, 10};

volatile unsigned char errorMessage[] = {13, 10, 'E', 'R', 'R', 'O', 'R', '-', '>', 'I', 'n', 't', 'r', 'o', 'd', 'u', 'c', 'e', 't', 'i',
                                         ' ', 'o', ' ', 'v', 'a', 'l', 'o', 'a', 'r', 'e', ' ', 'c', 'o', 'r', 'e', 'c', 't', 'a', ':',
                                         '.', 13, 10};

volatile unsigned char messageMode1[] = {13, 10, 'C', 'e', ' ', 'v', 'a', 'l', 'o', 'a', 'r', 'e', ' ', 'v', 'r', 'e', 't', 'i', ' ', 's','a',
                                         ' ', 's', 'c', 'r', 'i', 'e', 't', 'i', ' ', 'i', 'n', ' ', 'S', 'O', 'C', '0', 'D', 'A','T',
                                         ':', ' ', '(', 'M', 'a', 'x', '.', ' ', '4', '0', '9', '5', ')', 13, 10};

volatile unsigned char infoMessage[] = {'P', 'o', 't', 'i', ' ', 's', 'a', ' ', 'v', 'e', 'z', 'i', ' ', 's', 'e', 'm', 'n', 'a', 'l',
                                         'u', 'l', ' ', 'l', 'a', ' ', 'p', 'i', 'n', 'u', 'l', ' ', 'P', '1', '.', '1', 13, 10};

volatile unsigned char questionAboutDutyCicle[] = {13 , 10, 'C', 'a', 't', ' ', 'v', 'r', 'e', 'i', ' ', 's', 'a', ' ', 'f', 'i', 'e', ' ',
                                                   'f', 'a', 'c', 't', 'o', 'r', 'u', 'l', ' ', 'd', 'e', ' ', 'u', 'm', 'p', 'l', 'e', 'r', 'e', '?',
                                                   13, 10, 9, '0', '.', ' ', '0', '%', 13, 10, 9, '1', '.', ' ', '1', '0', '%',
                                                   13, 10, 9, '2', '.', ' ', '2', '0', '%', 13, 10, 9, '3', '.', ' ', '3', '0', '%',
                                                   13, 10, 9, '4', '.', ' ', '4', '0', '%', 13, 10, 9, '5', '.', ' ', '5', '0', '%',
                                                   13, 10, 9, '6', '.', ' ', '6', '0', '%', 13, 10, 9, '7', '.', ' ', '7', '0', '%',
                                                   13, 10, 9, '8', '.', ' ', '8', '0', '%', 13, 10, 9, '9', '.', ' ', '9', '0', '%', 13, 10};

volatile unsigned char chooseSamples[] = {13, 10, 9, 'l', '.', ' ', '5', '0', '0',
                                          13, 10, 9, 'm', '.', ' ', '1', '0', '0', '0',
                                          13, 10, 9, 'n', '.', ' ', '1', '5', '0', '0',
                                          13, 10, 9, 'o', '.', ' ', '2', '0', '0', '0',
                                          13, 10, 9, 'p', '.', ' ', '2', '5', '0', '0',
                                          13, 10, 9, 'q', '.', ' ', '3', '0', '0', '0',
                                          13, 10, 9, 'r', '.', ' ', '5', '0', '0', '0', 13, 10};

volatile unsigned char messageDutyCicleSet[] = {13, 10, 'F', 'a', 'c', 't', 'o', 'r', 'u', 'l', ' ', 'd', 'e', ' ', 'u', 'm', 'p', 'l', 'e', 'r', 'e',
                                         ' ', 'a', ' ', 'f', 'o', 's', 't', ' ', 's', 'e', 't', 'a', 't', 13, 10};

volatile unsigned char messageFreqModify[] = {'C', 'u', ' ', 'b', 'u', 't', 'o', 'n', 'u', 'l', ' ', 'P', '2', '.', '3', ' ', 'p', 'o','t', 'i',
                                              ' ', 'm', 'o', 'd', 'i', 'f', 'i', 'c', 'a', ' ', 'f', 'r', 'e', 'c', 'v', 'e', 'n','t', 'a',
                                              ' ', 's', 'e', 'm', 'n', 'a', 'l', 'u', 'l', 'u', 'i', 13, 10};

volatile unsigned char messageSamplesModified[] = {'N', 'u', 'm', 'a', 'r', 'u', 'l', ' ', 'd', 'e', ' ', 'e', 's', 'a', 'n', 't', 'i', 'o', 'n', 'e', ' ', 'a', ' ', 'f', 'o', 's','t',
                                                   ' ', 'c', 'o', 'n', 'f', 'i', 'g', 'u', 'r', 'a', 't', '.', 13, 10};

volatile unsigned char infoMenu[] = {'A', 'p', 'a', 's', 'a', ' ', 'p', 'e', ' ', 'b', 'u', 't', 'o', 'n', 'u', 'l', ' ', 'P', '4', '.', '1', ' ', 'c', 'a',
                                     ' ', 's', 'a', ' ', 'v', 'e', 'z', 'i', ' ', 'm', 'e', 'n', 'i', 'u', 'l', 13, 10};

volatile unsigned int menuSize = sizeof(menu) / sizeof(menu[0]);
volatile unsigned int infoMenuSize = sizeof(infoMenu) / sizeof(infoMenu[0]);
volatile unsigned int errorMessageSize = sizeof(errorMessage) / sizeof(errorMessage[0]);
volatile unsigned int messageMode1Size = sizeof(messageMode1) / sizeof(messageMode1[0]);
volatile unsigned int infoMessageSize = sizeof(infoMessage) / sizeof(infoMessage[0]);
volatile unsigned int semnalSinusoidalSize = sizeof(semnalSinusoidal) / sizeof(semnalSinusoidal[0]);
volatile unsigned int questionAboutDutyCicleSize = sizeof(questionAboutDutyCicle) / sizeof(questionAboutDutyCicle[0]);
volatile unsigned int messageDutyCicleSetSize = sizeof(messageDutyCicleSet) / sizeof(messageDutyCicleSet[0]);
volatile unsigned int messageFreqModifySize = sizeof(messageFreqModify) / sizeof(messageFreqModify[0]);
volatile unsigned int chooseSamplesSize = sizeof(chooseSamples) / sizeof(chooseSamples[0]);
volatile unsigned int messageSamplesModifiedSize = sizeof(messageSamplesModified) / sizeof(messageSamplesModified[0]);

volatile char caracter;

//variabilele pentru semnale
int semnalPoints = 100;
const int amplitudine = 4095;
const int halfAmplitudine = 2047;
int value;
float sinusValue;
int changeSideTriunghi = 1;
int changeSideTrapez = 0;
volatile unsigned int select_Freq = 0;

//indexurile pentru semnale
volatile unsigned int indexMessage = 0;
volatile unsigned int indexSemnalTriunghiular = 0;
volatile unsigned int indexSemnalTrapez = 0;
volatile unsigned int indexSemnalSinusoidal = 0;
volatile unsigned int indexSemnalRampa = 0;
volatile unsigned int indexSemnalFierastrau = 99;
volatile unsigned int indexSemnalArcPozitiv = 0;
volatile unsigned int indexSemnalArcNegativ = 0;
volatile unsigned int indexMenu = 0;
volatile unsigned int selectSemnal = 0;
volatile unsigned int infoMenuIndex = 0;

int main(void) {
    //declaram variabilele

    WDTCTL = WDTPW | WDTHOLD;

    //apelam functia pentru initializarea GPIO
    Init_GPIO();

    //apelam functia coresponzatoare configurarii frecventei
    Clock_System();

    //apelam functia pentru pinul P6.6
    Pin66();

    //apelam functia pentru butonul P4.1
    Button_P41();
    Button_P23();

    //apelam functia pentru configurarea pinului pentru a vedea semnalul PWM
    PWM_P50();

    PM5CTL0 &= ~LOCKLPM5;

    //apelam functia pentru modulul UART
    UART();

    //apelam functia pentru modulul DAC
    DAC();

    //InfoMenu_message();
    for(infoMenuIndex = 0; infoMenuIndex < infoMenuSize; infoMenuIndex++)
    {
        while(!(UCA1IFG&UCTXIFG));
        UCA1TXBUF = infoMenu[infoMenuIndex];
    }

    P4IFG &= ~BIT1;
    P2IFG &= ~BIT3;

    __bis_SR_register(GIE);

    return 0;
}

// Port 4 interrupt service routine
#pragma vector=PORT4_VECTOR
__interrupt void Port_4(void)
{

    //trimitem meniu pe iesirea seriala
    for(indexMenu = 0; indexMenu < menuSize; indexMenu++)
    {
        while(!(UCA1IFG&UCTXIFG));
        UCA1TXBUF = menu[indexMenu];
    }

    P4IFG &= ~BIT1;
    //__bic_SR_register_on_exit(LPM3_bits);
}

// Port 2 interrupt service routine
#pragma vector=PORT2_VECTOR
__interrupt void Port_2(void)
{
    P2IFG &= ~BIT3;

    //ex. : CCR0 = f_SMCLK / f_PWM = 6 MHz / 120 kHz = 50
    switch(select_Freq){
        case 0:
            TB2CCR0 = 50 - 1;
            break;

        case 1:
                TB2CCR0 = 100 - 1;
                break;

        case 2:
                TB2CCR0 = 500 - 1;
                break;

        case 3:
                TB2CCR0 = 1000 - 1;
                break;

        case 4:
                TB2CCR0 = 5000 - 1;
                break;

        case 5:
                TB2CCR0 = 10000-1;
                select_Freq=0;
                break;
    }

//    if(select_Freq == 0) { TB2CCR0 = 50 - 1; }
//
//    if(select_Freq == 1) { TB2CCR0 = 100 - 1; }
//
//    if(select_Freq == 2) { TB2CCR0 = 500 - 1; }
//
//    if(select_Freq == 3) { TB2CCR0 = 1000 - 1; }
//
//    if(select_Freq == 4) { TB2CCR0 = 5000 - 1; }
//
//    if(select_Freq==5){
//       select_Freq=0;
//       TB2CCR0 = 10000-1;
//    }

    select_Freq++;

}

// UART A1
#pragma vector=USCI_A1_VECTOR
__interrupt void USCI_A1_ISR(void)

{
  switch(__even_in_range(UCA1IV,USCI_UART_UCTXCPTIFG))
  {
    case USCI_NONE: break;
    case USCI_UART_UCRXIFG:

        while(!(UCA1IFG&UCTXIFG));
        caracter = UCA1RXBUF;

        //Aici mai jos o sa scriu codul util pentru generarea semnalelor
        switch(caracter)
        {
            //Cand se apasa 'a' se genereaza un semnal cu ampl. constanta si cu data aleasa adica ce scriem in SAC0DAT
            case 'a':

                Show_good_carachter();
                Semnal_pin_message();

                P6OUT ^= BIT6;

                selectSemnal = 0;

                break;

            //Cand se apasa 'b' se genereaza un semnal sinusoidal in functie de nr esantione perioade oferite
            case 'b':

                Show_good_carachter();
                Semnal_pin_message();
                Freq_modify_message();

                P6OUT ^= BIT6;
                selectSemnal = 1;

                break;
            //Cand se apasa 'c' se genereaza un semnal triunghi perfect
            case 'c':

                Show_good_carachter();
                Semnal_pin_message();
                Freq_modify_message();

                P6OUT ^= BIT6;
                selectSemnal = 2;

                break;

            //Cand se apasa  'd' se genereaza un semnal rampa cu nr de esantione perioada data
            case 'd':

                Show_good_carachter();
                Semnal_pin_message();
                Freq_modify_message();

                P6OUT ^= BIT6;
                selectSemnal = 3;

                break;

            //Cand se apasa 'e' se genereaza un semnal PWM cu un factor de umplere mentionat
            case 'e':

                Show_good_carachter();
                Question_Duty_Cicle_message();

                P6OUT ^= BIT6;

                break;

            //Cand se apasa  'f' se genereaza un semnal trapezoidal
            case 'f':

                Show_good_carachter();
                Semnal_pin_message();
                Freq_modify_message();

                P6OUT ^= BIT6;
                selectSemnal = 4;

                break;

            //Cand se apasa  'g' se genereaza un semnal dinte de fierestrau
            case 'g':

                Show_good_carachter();
                Semnal_pin_message();
                Freq_modify_message();

                P6OUT ^= BIT6;
                selectSemnal = 5;

                break;

            //Cand se apasa  'h' se genereaza un semnal arc de sinus pozitiv
            case 'h':

                Show_good_carachter();
                Semnal_pin_message();
                Freq_modify_message();

                P6OUT ^= BIT6;
                selectSemnal = 6;

                break;

            //Cand se apasa  'i' se genereaza un semnal arc de sinus negativ
            case 'i':

                Show_good_carachter();
                Semnal_pin_message();
                Freq_modify_message();

                P6OUT ^= BIT6;
                selectSemnal = 7;

                break;

            //cand se apasa pe 's' se va arata meniul prin care selectezi numarul de esantioane pentru un semnal
            case 's':

                Show_good_carachter();
                Choose_samples_message();

                P6OUT ^= BIT6;
                break;

            case 'l':

                semnalPoints = 500;
                Show_good_carachter();
                Samples_modified_message();

                break;

            case 'm':

                semnalPoints = 1000;
                Show_good_carachter();
                Samples_modified_message();

                break;

            case 'n':

                semnalPoints = 1500;
                Show_good_carachter();
                Samples_modified_message();

                break;

            case 'o':

                semnalPoints = 2000;
                Show_good_carachter();
                Samples_modified_message();

                break;

            case 'p':

                semnalPoints = 2500;
                Show_good_carachter();
                Samples_modified_message();

                break;

            case 'q':

                semnalPoints = 3000;
                Show_good_carachter();
                Samples_modified_message();

                break;

            case 'r':

                semnalPoints = 5000;
                Show_good_carachter();
                Samples_modified_message();

                break;

            case '0':
                TB2CCR1 = 0;
                Duty_Cicle_message();
                Semnal_pin_PWM_message();
                Freq_modify_message();
                break;

            case '1':
                TB2CCR1 = TB2CCR0 * 0.1;
                Duty_Cicle_message();
                Semnal_pin_PWM_message();
                Freq_modify_message();
                break;

            case '2':
                TB2CCR1 = TB2CCR0 * 0.2;
                Duty_Cicle_message();
                Semnal_pin_PWM_message();
                Freq_modify_message();
                break;

            case '3':
                TB2CCR1 = TB2CCR0 * 0.3;
                Duty_Cicle_message();
                Semnal_pin_PWM_message();
                Freq_modify_message();
                break;

            case '4':
                TB2CCR1 = TB2CCR0 * 0.4;
                Duty_Cicle_message();
                Semnal_pin_PWM_message();
                Freq_modify_message();
                break;

            case '5':
                TB2CCR1 = TB2CCR0 * 0.5;
                Duty_Cicle_message();
                Semnal_pin_PWM_message();
                Freq_modify_message();
                break;

            case '6':
                TB2CCR1 = TB2CCR0 * 0.6;
                Duty_Cicle_message();
                Semnal_pin_PWM_message();
                Freq_modify_message();
                break;

            case '7':
                TB2CCR1 = TB2CCR0 * 0.7;
                Duty_Cicle_message();
                Semnal_pin_PWM_message();
                Freq_modify_message();
                break;

            case '8':
                TB2CCR1 = TB2CCR0 * 0.8;
                Duty_Cicle_message();
                Semnal_pin_PWM_message();
                Freq_modify_message();
                break;

            case '9':
                TB2CCR1 = TB2CCR0 * 0.9;
                Duty_Cicle_message();
                Semnal_pin_PWM_message();
                Freq_modify_message();
                break;

            default:

                //se trimite inapoi carcaterul introdus
                while(!(UCA1IFG&UCTXIFG));
                UCA1TXBUF = UCA1RXBUF;

                //afisam mesajul de eroare in cazul in care nu se introduce un carcater corect
                Error_message();

                //by default selectSemnal este 0
                selectSemnal = 0;

                //by default Duty Cicle este 50%
                TB2CCR1 = TB2CCR0 * 0.5;
                break;
        }

        break;
    case USCI_UART_UCTXIFG: break;
    case USCI_UART_UCSTTIFG: break;
    case USCI_UART_UCTXCPTIFG: break;
    default: break;
  }
}


// SAC0 DAC service routine
#pragma vector = SAC0_SAC2_VECTOR
__interrupt void SAC0_ISR(void)
{
  switch(__even_in_range(SAC0IV,SACIV_4))
  {
    case SACIV_0: break;
    case SACIV_2: break;
    case SACIV_4:

        switch(selectSemnal)
        {
            //genereaza semnal cu amplitudine constanta
            case 0:
                SAC0DAT = 2000;
                //Vout = REFVSEL_2 * SOC0DAT / 4095 = 2.5 V * 2000 / 4095 = 1.22 V
                break;

            //afiseaza semnal sinusoidal
            case 1:

                if(indexSemnalSinusoidal == semnalPoints) { indexSemnalSinusoidal = 0; }

                sinusValue = sin((float)indexSemnalSinusoidal / semnalPoints * 2 * M_PI);
                sinusValue = sinusValue * (amplitudine / 2);
                sinusValue = sinusValue + (amplitudine / 2);
                SAC0DAT = sinusValue;

                //SAC0DAT = semnalSinusoidal[indexSemnalSinusoidal];  //asta o folosesc in cazul in care vreau ca semnalul sinusoidal sa se genereze mai repede
                indexSemnalSinusoidal++;
                break;

            //genereaza semnal triungiular
            case 2:
                //asta este rampa pozitiva
                if(changeSideTriunghi == 1)
                {
                    if(indexSemnalTriunghiular == (semnalPoints / 2) - 1)
                    {
                        changeSideTriunghi = 0;
                    }

                    value = amplitudine / (semnalPoints / 2);
                    value = value * indexSemnalTriunghiular;
                    SAC0DAT = value;
                    indexSemnalTriunghiular++;
                }
                //asta este rampa negativa
                else
                {
                    if(indexSemnalTriunghiular == 1)
                    {
                        changeSideTriunghi = 1;
                    }

                    value = amplitudine / (semnalPoints / 2);
                    value = value * indexSemnalTriunghiular;
                    SAC0DAT = value;
                    indexSemnalTriunghiular--;
                }

                break;

            //genereaza semnal rampa
            case 3:

                if(indexSemnalRampa == semnalPoints) { indexSemnalRampa = 0; }

                value = amplitudine / semnalPoints;
                value = value * indexSemnalRampa;
                SAC0DAT = value;
                indexSemnalRampa++;

                break;

            //genereaza semnal trapez
            case 4:
                //asta este partea de jos continua la trapez
                if(changeSideTrapez == 0)
                {
                    if(indexSemnalTrapez == (semnalPoints / 2))
                    {
                        changeSideTrapez = 1;
                        indexSemnalTrapez = 0;
                    }
                    indexSemnalTrapez++;

                }
                //asta este partea ce urca la trapez
                else if(changeSideTrapez == 1)
                {
                    if(indexSemnalTrapez == (semnalPoints / 2) - 1)
                    {
                        changeSideTrapez = 2;
                    }

                    value = amplitudine / (semnalPoints / 2);
                    value = value * indexSemnalTrapez;
                    SAC0DAT = value;
                    indexSemnalTrapez++;
                }
                //asta este partea de sus la trapez
                else if(changeSideTrapez == 2)
                {
                    if(indexSemnalTrapez == (semnalPoints / 2) + (semnalPoints / 2))
                    {
                        changeSideTrapez = 3;
                        indexSemnalTrapez = (semnalPoints / 2) - 2;
                    }
                    indexSemnalTrapez++;
                }
                //asta este partea ce coboara la trapez
                else
                {
                    if(indexSemnalTrapez == 1)
                    {
                        changeSideTrapez = 0;
                    }

                    value = amplitudine / (semnalPoints / 2);
                    value = value * indexSemnalTrapez;
                    SAC0DAT = value;
                    indexSemnalTrapez--;
                }
                break;

            //genereaza semnal dinte de fierastrau
            case 5:

                if(indexSemnalFierastrau == 0) { indexSemnalFierastrau = 0; }

                value = amplitudine / semnalPoints;
                value = value * indexSemnalFierastrau;
                SAC0DAT = value;
                indexSemnalFierastrau--;

                break;

            //genereaza un semnal arc de sinus pozitiv
            case 6:

                if(indexSemnalArcPozitiv == semnalSinusoidalSize) { indexSemnalArcPozitiv = 0; }

                if(indexSemnalArcPozitiv < 51)
                {
                    SAC0DAT = semnalSinusoidal[indexSemnalArcPozitiv];
                }

                if(indexSemnalArcPozitiv > 50)
                {
                    SAC0DAT = halfAmplitudine;
                }

                indexSemnalArcPozitiv++;

                break;

            //genereaza un semnal arc de sinus negativ
            case 7:

                if(indexSemnalArcNegativ == semnalSinusoidalSize) { indexSemnalArcNegativ = 0; }

                if(indexSemnalArcNegativ < 50)
                {
                    SAC0DAT = halfAmplitudine;
                }

                if(indexSemnalArcNegativ > 49)
                {
                    SAC0DAT = semnalSinusoidal[indexSemnalArcNegativ];
                }

                indexSemnalArcNegativ++;

                break;

            default:
                SAC0DAT = 1000;
                break;
        }


        break;
    default: break;
  }
}


void Pin66()
{
    //Configuram P6.6 ca iesire
    P6DIR |=BIT6;
    P6OUT |=BIT6;
}


void Button_P41()
{
    //Configuram butonul P4.1
    P4OUT |= BIT1;
    P4REN |= BIT1;
    P4IES |= BIT1;
    P4IE |= BIT1;
}


void Button_P23()
{
    //Configuram butonul P2.3
    P2OUT |= BIT3;
    P2REN |= BIT3;
    P2IES |= BIT3;
    P2IE |= BIT3;
}


void PWM_P50()
{
    P5DIR |= BIT0;
    P5SEL0 |= BIT0;
    P5SEL1 &= ~BIT0;
}


void UART()
{
    // Configure UART pins
    P1SEL0 |= BIT6 | BIT7;                  // set 2-UART pin as second function

    //P4.2 ->  RxD      P4.3 -> TxD
    P4SEL0 = BIT2 | BIT3;

    // Configure UART
    UCA1CTLW0 |= UCSWRST;
    UCA1CTLW0 |= UCSSEL_2;                   // set MSCLK as BRCLK = 6 MHz

    UCA1BR0 = 78;                          // INT(6 MHz/4800)
    UCA1BR1 = 0x00;
    UCA1MCTLW = 0x0021;

    UCA1CTLW0 &= ~UCSWRST;                    // Initialize eUSCI
    UCA1IE |= UCRXIE;                         // Enable USCI_A0 RX interrupt
}


void DAC()
{

    P1SEL0 |= BIT1;                           // Select P1.1 as OA0O function
    P1SEL1 |= BIT1;                           // OA is used as buffer for DAC

    // Configure reference module
    PMMCTL0_H = PMMPW_H;                      // Unlock the PMM registers
    PMMCTL2 = INTREFEN | REFVSEL_2;           // Enable internal 2.5V reference
    while(!(PMMCTL2 & REFGENRDY));            // Poll till internal reference settles

    SAC0DAC = DACSREF_1 + DACLSEL_2 + DACIE;  // Select int Vref as DAC reference
    //SAC0DAT = semnal[i];                       // Initial DAC data
    SAC0DAC |= DACEN;                         // Enable DAC

    SAC0OA = NMUXEN + PMUXEN + PSEL_1 + NSEL_1;//Select positive and negative pin input
    SAC0OA |= OAPM;                            // Select low speed and low power mode
    SAC0PGA = MSEL_1;                          // Set OA as buffer mode
    SAC0OA |= SACEN + OAEN;                    // Enable SAC and OA

    // Use TB2.1 as DAC hardware trigger
    TB2CCR0 = 50-1;                            // PWM Period/2
    TB2CCTL1 = OUTMOD_6;                       // TBCCR1 toggle/set
    TB2CCR1 = TB2CCR0 * 0.5;                              // TBCCR1 PWM duty cycle
    TB2CTL = TBSSEL__SMCLK  | MC_1 | TBCLR;     // SMCLK, up mode, clear TBR

}


void Clock_System()
{
    //Condiguram DCO

    FRCTL0 = FRCTLPW | NWAITS_2; //asta e pentru frecvente mai mari de 8MHzs

    __bis_SR_register(SCG0);
    CSCTL3 |= SELREF__REFOCLK | FLLREFDIV_0;
    CSCTL0 = 0;
    CSCTL1 = DCOFTRIMEN_1 | DCOFTRIM0 | DCOFTRIM1 | DCORSEL_7;
    //f_mult = f_MCLK / F_REFOCLK = 24.000.000 Hz / 32768 Hz = 732.42
    CSCTL2 = FLLD_0 + 731;
    __delay_cycles(3);
    __bic_SR_register(SCG0);

    Software_Trim();

    CSCTL4 = SELMS__DCOCLKDIV | SELA__REFOCLK;

    CSCTL5 = DIVM_0 | DIVS_2;                   //f_MCLK = 24 MHz, f_SMCLK = 6 MHz

    //Directionam MCLK si SMCLK la doi pini fizici, la P3.0, respectiv P1.0
    //SMCLK 1.0
    P1DIR |= BIT0;
    P1SEL1 |= BIT0;
    P1SEL0 &= ~BIT0;

    //MCLK 3.0
    P3DIR |= BIT0;
    P3SEL1 &= ~BIT0;
    P3SEL0 |= BIT0;
}



void Show_good_carachter()
{
    while(!(UCA1IFG&UCTXIFG));
    UCA1TXBUF = UCA1RXBUF;
    while(!(UCA1IFG&UCTXIFG));
    UCA1TXBUF = 13;
    while(!(UCA1IFG&UCTXIFG));
    UCA1TXBUF = 10;
}

void Semnal_pin_message()
{
    for(indexMessage = 0; indexMessage < infoMessageSize; indexMessage++)
    {
        while(!(UCA1IFG&UCTXIFG));
        UCA1TXBUF = infoMessage[indexMessage];
    }
}


void Samples_modified_message()
{
    for(indexMessage = 0; indexMessage < messageSamplesModifiedSize; indexMessage++)
    {
        while(!(UCA1IFG&UCTXIFG));
        UCA1TXBUF = messageSamplesModified[indexMessage];
    }
}

void Choose_samples_message()
{
    for(indexMessage = 0; indexMessage < chooseSamplesSize; indexMessage++)
    {
        while(!(UCA1IFG&UCTXIFG));
        UCA1TXBUF = chooseSamples[indexMessage];
    }
}

void Semnal_pin_PWM_message()
{
    //afisam mesajul specific pentru acest semnal
    infoMessage[infoMessageSize - 5] = '5';
    infoMessage[infoMessageSize - 3] = '0';
    for(indexMessage = 0; indexMessage < infoMessageSize; indexMessage++)
    {
        while(!(UCA1IFG&UCTXIFG));
        UCA1TXBUF = infoMessage[indexMessage];
    }
    infoMessage[infoMessageSize - 5] = '1';
    infoMessage[infoMessageSize - 3] = '1';
}

void Question_Duty_Cicle_message()
{
    for(indexMenu = 0; indexMenu < questionAboutDutyCicleSize; indexMenu++)
    {
        while(!(UCA1IFG&UCTXIFG));
        UCA1TXBUF = questionAboutDutyCicle[indexMenu];
    }
}


void Duty_Cicle_message()
{
    for(indexMessage = 0; indexMessage < messageDutyCicleSetSize; indexMessage++)
    {
        while(!(UCA1IFG&UCTXIFG));
        UCA1TXBUF = messageDutyCicleSet[indexMessage];
    }
}


void Freq_modify_message()
{
    for(indexMessage = 0; indexMessage < messageFreqModifySize; indexMessage++)
    {
        while(!(UCA1IFG&UCTXIFG));
        UCA1TXBUF = messageFreqModify[indexMessage];
    }
}

void Error_message()
{
    for(indexMessage = 0; indexMessage < errorMessageSize; indexMessage++)
    {
        while(!(UCA1IFG&UCTXIFG));
        UCA1TXBUF = errorMessage[indexMessage];
    }
}

void InfoMenu_message()
{
    for(infoMenuIndex = 0; infoMenuIndex < infoMenuSize; infoMenuIndex++)
    {
        while(!(UCA1IFG&UCTXIFG));
        UCA1TXBUF = infoMenu[infoMenuSize];
    }
}


void Init_GPIO()
{
    P1DIR = 0xFF; P2DIR = 0xFF;
    P1REN = 0xFF; P2REN = 0xFF;
    P1OUT = 0x00; P2OUT = 0x00;
}


void Software_Trim()
{
    unsigned int oldDcoTap = 0xffff;
    unsigned int newDcoTap = 0xffff;
    unsigned int newDcoDelta = 0xffff;
    unsigned int bestDcoDelta = 0xffff;
    unsigned int csCtl0Copy = 0;
    unsigned int csCtl1Copy = 0;
    unsigned int csCtl0Read = 0;
    unsigned int csCtl1Read = 0;
    unsigned int dcoFreqTrim = 3;
    unsigned char endLoop = 0;

    do
    {
        CSCTL0 = 0x100;                         // DCO Tap = 256
        do
        {
            CSCTL7 &= ~DCOFFG;                  // Clear DCO fault flag
        }while (CSCTL7 & DCOFFG);               // Test DCO fault flag

        __delay_cycles((unsigned int)3000 * MCLK_FREQ_MHZ);// Wait FLL lock status (FLLUNLOCK) to be stable
                                                           // Suggest to wait 24 cycles of divided FLL reference clock
        while((CSCTL7 & (FLLUNLOCK0 | FLLUNLOCK1)) && ((CSCTL7 & DCOFFG) == 0));

        csCtl0Read = CSCTL0;                   // Read CSCTL0
        csCtl1Read = CSCTL1;                   // Read CSCTL1

        oldDcoTap = newDcoTap;                 // Record DCOTAP value of last time
        newDcoTap = csCtl0Read & 0x01ff;       // Get DCOTAP value of this time
        dcoFreqTrim = (csCtl1Read & 0x0070)>>4;// Get DCOFTRIM value

        if(newDcoTap < 256)                    // DCOTAP < 256
        {
            newDcoDelta = 256 - newDcoTap;     // Delta value between DCPTAP and 256
            if((oldDcoTap != 0xffff) && (oldDcoTap >= 256)) // DCOTAP cross 256
                endLoop = 1;                   // Stop while loop
            else
            {
                dcoFreqTrim--;
                CSCTL1 = (csCtl1Read & (~DCOFTRIM)) | (dcoFreqTrim<<4);
            }
        }
        else                                   // DCOTAP >= 256
        {
            newDcoDelta = newDcoTap - 256;     // Delta value between DCPTAP and 256
            if(oldDcoTap < 256)                // DCOTAP cross 256
                endLoop = 1;                   // Stop while loop
            else
            {
                dcoFreqTrim++;
                CSCTL1 = (csCtl1Read & (~DCOFTRIM)) | (dcoFreqTrim<<4);
            }
        }

        if(newDcoDelta < bestDcoDelta)         // Record DCOTAP closest to 256
        {
            csCtl0Copy = csCtl0Read;
            csCtl1Copy = csCtl1Read;
            bestDcoDelta = newDcoDelta;
        }

    }while(endLoop == 0);                      // Poll until endLoop == 1

    CSCTL0 = csCtl0Copy;                       // Reload locked DCOTAP
    CSCTL1 = csCtl1Copy;                       // Reload locked DCOFTRIM
    while(CSCTL7 & (FLLUNLOCK0 | FLLUNLOCK1)); // Poll until FLL is locked
}
