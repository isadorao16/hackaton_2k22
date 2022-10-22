

// Define os pinos de saída

#define PIN_LED_1 8
#define PIN_LED_2 9
#define PIN_LED_3 10
#define PIN_LED_4 11

// Controla os tempos do piscar
#define REPOUSE_TIME    400// 
#define FAST_PULSE_TIME 1000// 
#define SLOW_PULSE_TIME 1000//
#define WAITING_TIME    1000//
#define SPACE_DELAY     1000//

// Macro de DEBUG
#define DEBUG




char text[50] = ""; // String da entrada
String morse = "";  // Código morse



void setup()
{
  // Comunicação serial
  Serial.begin (9600);

  // Pinos de saída
  pinMode (PIN_LED_1, OUTPUT);
  pinMode (PIN_LED_2, OUTPUT);
  pinMode (PIN_LED_3, OUTPUT);
  pinMode (PIN_LED_4, OUTPUT);

  // Zera as saídas
  digitalWrite (PIN_LED_1, LOW);
  digitalWrite (PIN_LED_2, LOW);
  digitalWrite (PIN_LED_3, LOW);
  digitalWrite (PIN_LED_4,LOW);
}


void loop()
{
  if (Serial.available() > 0)               // Se tiver alguma coisa para escrever
  {
    read_text();

    #ifdef DEBUG
    Serial.println(text);                 // Verifica se o texto de entrada está correto
    #endif

    int tmp = 0;
    while (text[tmp] != '\0')
    {
      char_to_morse(text[tmp]);         // Converte o caractere atual para morse
      tmp++;

      #ifdef DEBUG
      Serial.println(morse);            // Verifica se o código morse está correto
      #endif

      int tmp0 = 0;
      while (morse[tmp0] != '\0')       // Apresenta o cógigo morse
      {
        if (morse[tmp0] == '.')
          pulse (FAST_PULSE_TIME);  // Pulso rápido

        else if (morse[tmp0] == '-')
          pulse (SLOW_PULSE_TIME);  // Pulso lento

        else if (morse[tmp0] == ' ')
          delay (SPACE_DELAY);      // Esperar

        else
         Serial.println("Foi traduzido um caractere irregular!");

        tmp0++;
      }
      delay(WAITING_TIME);
    }
  }
}



// Funções

/*
 * Lee o texto de entrada e corrige ele. Se For usado um caractere irregular, ele avisa
 */
void read_text()
{
  int tmp = 0;
  char ch = ' ';

  while (Serial.available() > 0)                                       // Se tiver alguma coisa para escrever
  {
    ch = Serial.read();                                              // Lee o próximo caractere

    #ifdef DEBUG
    Serial.println((int) ch);
    #endif

    if (ch > 96) ch -= 32;                                           // converte letras maiúsculas em minúsculas

    if ( (ch > 64 && ch < 91) || (ch > 47 && ch < 58) || ch == 32 )  // Se for letra, número ou espaço
    {
      text[tmp] = ch;
      tmp++;

      delay(1);                                                    // Delay para dar tempo de receber o caractere da comunicação serial
    }
    else                                                             // Se não for letra ou número
      Serial.println("Foi usado um caractere irregular!");
  }

  text[tmp] = '\0';
}


/*
 * Converte um caractere para código morse
 */
void char_to_morse(char ch)
{
  // Macro que define os códigos morses para caca caractere válido
  #define SET_MORSE(CHAR, VALUE) \
  case CHAR : \
    morse = VALUE ; \
    break;

  switch (ch) // Define o código morse equivalente para cada caractere válido
  {
    // Letras
    SET_MORSE('A', ".-"   );
    SET_MORSE('B', "-..." );
    SET_MORSE('C', "-.-." );
    SET_MORSE('D', "-.."  );
    SET_MORSE('E', "."    );
    SET_MORSE('F', "..-." );
    SET_MORSE('G', "--."  );
    SET_MORSE('H', "...." );
    SET_MORSE('I', ".."   );
    SET_MORSE('J', ".---" );
    SET_MORSE('K', "-.-"  );
    SET_MORSE('L', ".-.." );
    SET_MORSE('M', "--"   );
    SET_MORSE('N', "-."   );
    SET_MORSE('O', "---"  );
    SET_MORSE('P', ".--." );
    SET_MORSE('Q', "--.-" );
    SET_MORSE('R', ".-."  );
    SET_MORSE('S', "..."  );
    SET_MORSE('T', "-"    );
    SET_MORSE('U', "..-"  );
    SET_MORSE('V', "...-" );
    SET_MORSE('W', ".--"  );
    SET_MORSE('X', "-..-" );
    SET_MORSE('Y', "-.--" );
    SET_MORSE('Z', "--.." );

    // Números
    SET_MORSE('0', ".----");
    SET_MORSE('1', "..---");
    SET_MORSE('2', "...--");
    SET_MORSE('3', "....-");
    SET_MORSE('4', ".....");
    SET_MORSE('5', "-....");
    SET_MORSE('6', "--...");
    SET_MORSE('7', "---..");
    SET_MORSE('8', "----.");
    SET_MORSE('9', "-----");

    // Pontuação
    SET_MORSE(',', "..-.." );
    SET_MORSE('.', ".-.-.-");
    SET_MORSE('?', "..--..");
    SET_MORSE(';', "-.-.-" );
    SET_MORSE(':', "---...");
    SET_MORSE('/', "-..-." );
    SET_MORSE('+', ".-.-." );
    SET_MORSE('-', "-....-");
    SET_MORSE('=', "-...-" );

    // Espaço
    SET_MORSE(' ', " ");
  }

  #undef SET_MORSE
}


/*
 * Executa um pulso no led com o tempo definido pelo parâmetro "period"
 */
void pulse(unsigned long period)
{
  // Leds aceso
  digitalWrite (PIN_LED_1, HIGH);
  digitalWrite (PIN_LED_2, HIGH);
  digitalWrite (PIN_LED_3, HIGH);
  digitalWrite(PIN_LED_4, HIGH);

  //#ifdef HAS_BUZZER // Buzzer ativado
  //digitalWrite (PIN_BUZZER, HIGH);
//  #endif
//
  //delay (period);


  // Leds apagado
  digitalWrite (PIN_LED_1, LOW);
  digitalWrite (PIN_LED_2, LOW);
  digitalWrite (PIN_LED_3, LOW);
  digitalWrite (PIN_LED_4, LOW);
  

  #ifdef HAS_BUZZER // Buzzer desativado
  digitalWrite (PIN_BUZZER, LOW);
  #endif

  delay (REPOUSE_TIME);
}
