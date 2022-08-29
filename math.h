
#ifndef MATH_H
#define MATH_H



#define PI 3.141592653589793



/*
* Funcao basica de exponenciacao
* @return base elevado a power
*/
double pow(double base, int power);
double root(double n);
/*
*Funcao recursiva para calcular o fatorial
* @return fatorial de n
*/
uint64 factorial(int n);

/*
* Funcao cosseno implementada por aproximação
* @return cosseno(x)
*/
double cosine(double x);
/*
* Funcao seno implementada por aproximação
* Esta usa o calculo da função cosseno com um pequeno ajuste
* @return seno(x)
*/
double sine(double x);

/*
* Dado P1 e P2, esta funcao calcula a distancia entre os pontos
* @param x1: P1.x
* @param y1: P1.y
* @param x2: P2.x
* @param y2: P2.y
* @return distancia entre P1 e P2
*/
double distance_points(int x1, int y1, int x2, int y2);

/*
* @return x arrendodado para cima
*/
int ceil(double x);

#endif