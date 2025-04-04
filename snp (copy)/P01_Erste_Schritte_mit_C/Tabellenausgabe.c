#include <stdio.h>

#define NUM_ROWS 8 // Definiere das Makro NUM_ROWS

int main(void) {
  double conversionRate;

  // Eingabe des Umrechnungsfaktors
  printf("Enter conversion rate (1.00 BTC -> CHF): ");
  scanf("%lf", &conversionRate);

  // Tabellenausgabe mit Schleife
  for (int i = 1; i <= NUM_ROWS; i++) {
    int chfAmount = i * 200;
    double btcAmount = (double)chfAmount / conversionRate; // Umrechnung von CHF zu BTC

    // Formatierte Ausgabe mit printf
    printf("  %4d CHF\t<-->\t %9.5f BTC\n", chfAmount, btcAmount);
  }

  return 0;
}
