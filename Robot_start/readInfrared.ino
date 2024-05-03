void readInfrared() {
  int IRvalue1 = digitalRead(IR_1);
  int IRvalue2 = digitalRead(IR_2);
  int IRvalue3 = digitalRead(IR_3);
  int IRvalue4 = digitalRead(IR_4);

  Serial.print("IR_1: ");
  Serial.print(IRvalue1);
  Serial.print(" , IR_2: ");
  Serial.print(IRvalue2);
  Serial.print(" , IR_3: ");
  Serial.print(IRvalue3);
  Serial.print(" , IR_4: ");
  Serial.print(IRvalue4);
}