
//Light up the correct segments to display the given digit
void displayDigit(int digit)
{
  String digits = (String)digit;
  for(int i=0;i<digits.length();i++)
  {
    if(i>1)
      break;
    int digi = 0;
    digi = digits.substring(i,i+1).toInt();
    digitalWrite(displayDigits[i], HIGH); 
    switch(digi)
    {
      case 0:
        for(int i=0;i<6;i++)
          digitalWrite(segments[i], HIGH);
          break;
      case 1:
        digitalWrite(segments[5], HIGH);
        digitalWrite(segments[4], HIGH);
        break;
      case 2:
        for(int i=0;i<7;i++)
          if(i != 2 && i != 5)
            digitalWrite(segments[i], HIGH);
        break;
      case 3:
        for(int i=0;i<7;i++)
          if(i != 4 && i != 5)
            digitalWrite(segments[i], HIGH);
        break;
      case 4:
        for(int i=0;i<7;i++)
          if(i != 0 && i != 3 && i != 4)
            digitalWrite(segments[i], HIGH);
        break;
      case 5:
        for(int i=0;i<7;i++)
          if(i != 1 && i != 4)
            digitalWrite(segments[i], HIGH);
        break;
      case 6:
        for(int i=0;i<7;i++)
          if(i != 1)
            digitalWrite(segments[i], HIGH);
        break;
      case 7:
        for(int i=0;i<3;i++)
            digitalWrite(segments[i], HIGH);
        break;
      case 8:
        for(int i=0;i<7;i++)
            digitalWrite(segments[i], HIGH);
        break;
      case 9:
        for(int i=0;i<7;i++)
          if(i != 3 && i != 4)
            digitalWrite(segments[i], HIGH);
        break;
      default:
        break;
    }
    delay(5);
    for(int i=0;i<7;i++)
      digitalWrite(segments[i], LOW);
    digitalWrite(displayDigits[i], LOW);
  }
  
  
}

