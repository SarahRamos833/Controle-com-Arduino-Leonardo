/* Código por Sarah Ramos -> @sarah.ramos18

Esse código foi feito para um controle com 3 botões e um módulo joystick e feito para usar em jogos de PC. Só funciona com ARDUINO LEONARDO
Os botões apertam botões do teclado do PC, depedendo do jogo é só mudar as configurações ou o próprio código.
Enquanto o botão 1 estiver pressionado o mouse do PC é controlado pelo joystick, enquanto estiver solto o joystick pressiona os botões ASDW que fazem o personagem andar
também da pra alterar as funções dos botões 2 e 3 ao pressionar o botão 1
ou seja, da pra fazer varia funções no jogo usando as combinações dos botões

comentei todo o código para maior compreenção e ficar fácil de ser adaptado para outras funções.

E o mais importante: SE DIVIRTA CRIANDO! :)

*/

#include <Keyboard.h> //biblioteca que controla o Teclado
#include <Mouse.h> //biblioteca que controla o Mouse

int horzPin = A0;  // Pino horizontal
int vertPin = A1;  // pino vertical
int PinBT = 9;  // pino botão joystick
int PinBT1 = 8; //pino botão 1
int PinBT2 = 7; // pino botão 2
int PinBT3 = 6; // pino botão 3

int i = 1; //variável usada em algumas funções

int vertZero, horzZero;  // Armazena o valor inicial de cada eixo, geralmente em torno de 512
int vertValor, horzValor;  // Armazena a saída analógica atual de cada eixo
const int sensibilidade = 80;  // Maior valor de sensibilidade = mouse mais lento, deve ser <= cerca de 500 -> teste o melhor pra voce
int mouseClickFlag = 0;
   
//int invertMouse = -1;        //Inverta o joystick com base na orientação -> use de acordo com a posição do seu joystick
int invertMouse = 1;         // se seu joystick tiver fazendo o contrário do que voce quer é só mudar aqui

void setup()
{
  pinMode(PinBT1, INPUT);//botões
  pinMode(PinBT2, INPUT_PULLUP);
  pinMode(PinBT3, INPUT_PULLUP);
  
  pinMode(horzPin, INPUT);  
  pinMode(vertPin, INPUT);
  pinMode(PinBT, INPUT);  
  digitalWrite(PinBT, HIGH);  
  delay(1000);  // pequeno atraso para deixar as saídas estabilizarem
  vertZero = analogRead(vertPin);  
  horzZero = analogRead(horzPin);  

  Keyboard.begin(); // incia controle do teclado
  Mouse.begin(); //inicia controle do mouse
  Serial.begin(9600); //inicia comunicação seria -> da pra usar para testes
}

void loop()
{
  int valorVRx = analogRead(horzPin); //valor do eixo X
  int valorVRy = analogRead(vertPin); // valor do eixo Y
  int estadoBT1 = digitalRead(PinBT1);
  bool estadoBT2 = digitalRead(PinBT2);
  bool estadoBT3 = digitalRead(PinBT3);


  if (estadoBT1 == HIGH)
{
  ////////////////////////////////////////////////////////se o botao 1 tiver pressionado//////////////////////////////////////////////////////////////
    if (estadoBT2 == 0){  //botão 2 aperta a tecla l
     Keyboard.press ('l');
  }else{
    Keyboard.release ('l');
  }

int a = i; //variavel para usar para controlar o inventario no minecraft (se tiver fazendo para outro jogo só apagar essa parte)
if(estadoBT3 == 0)
{
  i = i+1;
  delay(100);
}
if(i == 10)
{
  i = 1;
}
if (a != i)
{
   if(i==1)
   {
    Keyboard.press ('1');
    delay(10);
    Keyboard.release ('1');
   }
   if(i==2)
   {
    Keyboard.press ('2');
    delay(10);
    Keyboard.release ('2');
   }
   if(i==3)
   {
    Keyboard.press ('3');
    delay(10);
    Keyboard.release ('3');
   }
   if(i==4)
   {
    Keyboard.press ('4');
    delay(10);
    Keyboard.release ('4');
   }
   if(i==5)
   {
    Keyboard.press ('5');
    delay(10);
    Keyboard.release ('5');
   }
   if(i==6)
   {
    Keyboard.press ('6');
    delay(10);
    Keyboard.release ('6');
   }
   if(i==7)
   {
    Keyboard.press ('7');
    delay(10);
    Keyboard.release ('7');
   }
   if(i==8)
   {
    Keyboard.press ('8');
    delay(10);
    Keyboard.release ('8');
   }
   if(i==9)
   {
    Keyboard.press ('9');
    delay(10);
    Keyboard.release ('9');
   }
} // termina de controlar o inventario

  //joystick controla mouse
  vertValor = analogRead(vertPin) - vertZero;  // ler deslocamento vertical
  horzValor = analogRead(horzPin) - horzZero;  // ler deslocamento horizontal
  if (vertValor != 0)
    Mouse.move(0, (invertMouse * (vertValor / sensibilidade)), 0); //move o mouse no eixo y
  if (horzValor != 0)
    Mouse.move((invertMouse * (horzValor / sensibilidade)), 0, 0); // move o mouse do eixo x

// se o botão do joystick for apertado clique os botões do mouse
  if ((digitalRead(PinBT) == 0) && (!mouseClickFlag))  // se o botão do Joystick for pressionado
  {
    mouseClickFlag = 1;
    Mouse.press(MOUSE_RIGHT);  // clique com o botão esquerdo do mouse
  }
  else if ((digitalRead(PinBT)) && (mouseClickFlag)) //se o botão do joystick não for pressionado
  {
    mouseClickFlag = 0;
    Mouse.release(MOUSE_RIGHT);  // solte o botão esquerdo RIGHT - DIREITO / LEFT - ESQUERDO
  }
  

 //////////////////////////////////////////////////////////////////se o botão 1 não tiver pressionado////////////////////////////////////////////////////////
  }else if (estadoBT1 == LOW){ 
    //joystick pressiona ASDW para movimentar o personagem do jogo
    if(valorVRx == 0)
    {
      Keyboard.press ('a');
    }else{
      Keyboard.release ('a');
    }
    if(valorVRx == 1023)
    {
     Keyboard.press ('d');
    }else{
      Keyboard.release ('d');
    }
    if(valorVRy == 0)
    {
    Keyboard.press ('w');
    }else{
      Keyboard.release ('w');
    }
    if(valorVRy == 1023)
    {
     Keyboard.press ('s');
    }else{
      Keyboard.release ('s');
    }
    
  if ((digitalRead(PinBT) == 0) && (!mouseClickFlag))  // se o botão do Joystick for pressionado
  {
    mouseClickFlag = 1;
    Mouse.press(MOUSE_LEFT);  // clique com o botão esquerdo do mouse
  }else if ((digitalRead(PinBT)) && (mouseClickFlag)) //se o botão do joystick não for pressionado
  {
    mouseClickFlag = 0;
    Mouse.release(MOUSE_LEFT); // solte o botão esquerdo RIGHT - DIREITO / LEFT - ESQUERDO
  }
  
  if (estadoBT2 == 0){ //o botão 2 pressiona a letra g -> configurada no meu jogo para fazer o Steve pular
  Keyboard.press ('g');
  }else{
    Keyboard.release ('g');
  }
  if (estadoBT3 == 0){ //o botão 3 pressiona a letra e -> configurada no meu jogo para abrir o inventário
  Keyboard.press ('e');
  }else{
   Keyboard.release ('e');
  }
  }

  delay(10);  // espera esse tempinho só pros botões se estabilizarem
} 
