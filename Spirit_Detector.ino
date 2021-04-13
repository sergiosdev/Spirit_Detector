/*
                                    
   # Developers: Sérgio Ferreira & Wagner Annunciato
                                      Em: 01/02/2021
                                        
   # Detecção da Variação de Tensão de porta analógica 
   por indução.                
   
   # Utilizar um laço indutivo conectado à porta A0 (Analógica) do seu Arduíno
   # Utilizar um Led (+resistor 220ohms no anôdo) na porta 02 (Digital) de seu Arduíno.
*/

// --- Variáveis Globais ---
#define ledPin 2     
#define antenaPin A0 
int     valSerial = 0;        
float   voltagem =0; 
float   sensibilidadeVoltagem=0.70; // Parâmetro a ser alterado de acordo com a sua antena, deve ser ajustado
                                    // ...para que se obtenha o melhor resultado, com maior distância nas 
                                    // ...captações sem fio.        

// --- Função ---
void ligaDesligaLED()
{
  digitalWrite(ledPin,HIGH); //led ligado
  delay(1000);
  digitalWrite(ledPin,LOW); //led desligado
}

// --- Configurações Iniciais ---
void setup() {
  Serial.begin(9600);           
  
  while (!Serial) { /* Espera a porta serial conectar, usado apenas quando coloca-se o cabo USB */ }
  
  pinMode(antenaPin, INPUT);  // Configura antena
  pinMode(ledPin,OUTPUT);     // Configura o pino do LED como saída
  
  ligaDesligaLED();           // Piscar o led para testar
}

// --- Loop Infinito ---
void loop() {
  valSerial = analogRead(antenaPin);  // Lê o pino de entrada  
  voltagem = valSerial * (5.0 / 1024.0);

  Serial.println(F(" "));          
  Serial.print(F(" Serial: ")); Serial.println(valSerial);            // Imprime o valor da leitura na porta serial  
  Serial.print(F(" Volts: ")); Serial.println(voltagem);           // imprime o valor da voltagem da porta serial
  

   /* Se a voltagem cair ou o valSerialor da porta serial chegar a zero então detecta-se uma presença. */
  if(valSerial == 0  || voltagem <= sensibilidadeVoltagem) { 
    Serial.println(F(""));
    Serial.println(F("[Alguém foi Detectado!]")); 
    Serial.println(F(""));
    
    ligaDesligaLED();
  }
  
  delay(100);  
}
