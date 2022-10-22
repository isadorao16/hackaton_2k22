
int ValorPoten = 0;
int poten = 0;
void setup() {
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(A2, INPUT);
  Serial.begin(9600);

  Serial.print( "Qual é a frequecia minima " );
  Serial.println(" do BPM do coração?" );
  delay(2000);

}

void loop() {
  poten = analogRead(A2) / 4;
  ValorPoten = map (poten, 0, 1023, 0, 255);

  if ( poten >= 60 && poten <= 100) {
    Serial.println ("  CONCLUIDO  ");
    delay(1000);
  }

  else if (poten < 60 || poten > 100) {

    digitalWrite(10, HIGH);
    digitalWrite(9, HIGH);
    delay(ValorPoten);
    digitalWrite(10, LOW);
    digitalWrite(9, LOW);
    delay(ValorPoten);
    Serial.print("Frequência: ");
    Serial.println(poten);
    delay(200);
  }
}
