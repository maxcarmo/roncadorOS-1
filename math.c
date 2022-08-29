#include "types.h"
#include "defs.h"
#include "math.h"

/*
* @param divisor: O divisor
* @param dividend: O dividendo
* @return divisor % dividend para números de ponto flutuante
*/
double fremainder(double divisor, double dividend);

double min(double x, double y){
    if (x < y) return x;
    return y;
}

double max(double x, double y){
    if (x > y) return x;
    return y;
}



int ceil(double x){
    //se tem algo depois da virgula q seja
    //maior que zero, entao arredonda pra cima
    if ((x - (int)x) > 0){
        x+=1;
    }
    return (int) x;
}



double pow(double base, int power){
    double ac = base;
    if (power == 0) return 1; //qualquer numero elevado a 0 é 0
    int iterator = power - 1; //é preciso iterar power -1 vezes,
    // pois vao ser feitas power -1 multiplicacoes ex: b^3 = b*b*b, ao todo 2 multiplicacoes
    if (power < 0) iterator = (power * -1) -1; //se power é negativo entao conserto o iterator
    for (int i = 0; i < iterator; i++){
        ac *= base;
    }
    //nesse momento tenho meu numero acumulado em ac
    if (power > 0) return ac; //se nao é negativo, retorno normalmente
    return 1/ac; //se for negativo entao temos o inverso do numero

}


double fremainder(double divisor, double dividend){
    //extrai o resto de forma flutuante
    //ex: 5/2 = 2.5, entao
    //floating = 0.5
    double floating = ((divisor/dividend) - ((int)(divisor/dividend)));
    //entao retorna 0.5 * 2 = 1
    //ou seja, 5%2 da 1
    //é uma formula geral que vale tanto para inteiros quanto para flutuantes
    return floating * dividend;
}



uint64 factorial(int n){
    if (n <= 1) return 1;
    return n * factorial(n-1);
}

double cosine(double x){
    //1 - ((x^2)/2!) + ((x^4)/4!) - ((x^6)/6!) ...
    //como o radiano so varia de 0 a 2PI
    //entao pego o resto -> x%(2*PI)
    double new_x = fremainder(x, 2*PI);
    //numeros maiores que PI nao estavam com uma
    //boa precisao, entao reduzi de 0 a PI
    
    //para guardar o sinal do resultado
    int cos_sign = 1;

    if (new_x >= PI){
        cos_sign = -1;
        new_x -= PI;
    }
    //o resultado do cosseno é a soma da serie
    //entao acumulo o resultado nessa variavel
    double soma = 1;
    //para guardar o sinal da operacao atual
    int sign = -1;
    //precisao de 8 termos
    //eh uma precisao muito boa, mas requer um custo computacional um pouco alto
    for (int i = 1; i< 8; i++){
        soma += (sign * (pow(new_x,i*2)) / factorial(i*2));
        sign *= -1;
    }
    return soma * cos_sign;
}



double sine(double x){
    return cosine(PI/2 - x);
}


double root(double n){
  // Max and min are used to take into account numbers less than 1
  double lo = min(1, n), hi = max(1, n), mid;

  // Update the bounds to be off the target by a factor of 10
  while(100 * lo * lo < n) lo *= 10;
  while(0.01 * hi * hi > n) hi *= 0.1;

  for(int i = 0 ; i < 100 ; i++){
      mid = (lo+hi)/2;
      if(mid*mid == n) return mid;
      if(mid*mid > n) hi = mid;
      else lo = mid;
  }
  return mid;
}




double distance_points(int x1, int y1, int x2, int y2){
    int diffx, diffy;
    diffx = x1 - x2;
    diffy = y1 - y2;
    return root(
        pow(diffx,2) + pow(diffy,2)
    );
}