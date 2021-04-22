#pragma once
#ifndef MAIN_H
#define MAIN_H

const char polar[] = { "polar" };
const char cartesian[] = { "cartesian" };

const char add[] = "add";
const char sub[] = "sub";
const char mul[] = "mul";
const char dvs[] = "dvs";

typedef struct {
	const char* face; // define pointer face   
	const char* suit; // define pointer suit
	unsigned int face_number; // Define o número da face da carta
	unsigned int suit_number; // Define o número do naipe
	char* mode;
} Card; // end struct card    

typedef struct {
	double a;
	double b;
} Cart;

typedef struct {
	double r;
	double g;
} Pol;

typedef union {
	Cart	cart;
	Pol		pol;
} Cplx;

typedef struct {
	Cplx s;
	char* mode;
} CplxNum;

unsigned basicOp(CplxNum* x, CplxNum y, const char* cmd, const char* outputmode);
unsigned polarinvertion(Pol* w, Pol p);
unsigned negativecartesian(Cart* x, Cart y);
unsigned somacartesiana(Cart* x, Cart y);
unsigned cartesian2polar(Pol* w, Cart x);
unsigned multiplypolar(Pol* w, Pol p);
unsigned normalizeangle(Pol* w);
unsigned polar2cartesian(Cart* x, Pol w);
unsigned complexsum(CplxNum* c1, CplxNum c2);
unsigned complexmultiply(CplxNum* c1, CplxNum c2);
unsigned complexsub(CplxNum* c1, CplxNum c2);
unsigned complexdvs(CplxNum* c1, CplxNum c2);

#endif // MAIN_H


// Descrição do Assignment

/*
Este assignment é uma continuação do anterior e contém todas
as suas funções implementadas.

Como sabemos, a soma e a subtração de números complexos é mais
fácil e direta quando os operandos estão na base cartesiana.
Analogamente, é preferível realizar a multiplicação e a
divisão na base polar.
Assim, este projeto utiliza desta estratégia, transformando a
base dos operandos quando necessário para realizar as operações,
mas transformando o resultado na base desejada.


Sua tarefa é construir a função basicOp e fazer com que seu código
passe nos testes unitários especificados neste projeto do VS.
Além disso, você deve implementar as funções polarinversion,
negativecartesian, complexsub e complexdvs, necessárias para
realizar as operações de divisão e subtração de complexos.


A função negativecartesian deve produzir o (-1) de um número complexo
na base cartesiana. Sua entrada é Cart y e a saída é Cart *x. A
função retorna zero se tudo correu bem.
Esta função permite realizar a subtração, utilizando-a em conjunto com
a função complexsum. A subtração nada mais é que a soma de dois
números com o segundo número multiplicado por (-1).
A função sempre retorna zero.


A função polarinversion produz o (1/n) de um número complexo n na
base polar. Sua entrada é Polar p e a saída é Polar* w.
Esta função permite que seja realizada a divisão, usando-a em conjunto
com a função complexmultiply. A divisão nada mais é que a
multiplicação de dois números, com o segundo número invertido (1/n).

A função, antes de realizar qualquer operação, normaliza o ângulo
do número complexo de entrada verifica se o módulo deste é zero. Se
for, zera também seu ângulo.
Não existe ângulo para um vetor com norma zero! Então, por definição,
o ângulo deste vetor é zero.
Esta parte do código já é fornecida.

A função polarinversion retorna zero se tudo correu bem. Ela retorna 2
caso o módulo do número entrado seja menor ou igual a 1/_HUGE_ENUF.
Neste caso, a função devolde INFINITY como módulo de sua variável de
saída.
A função polarinversion também retorna zero se o módulo da entrada
for maior ou igual a _HUGE_ENUF. Neste caso, o módulo da saída será
zero e, por consequência, seu ângulo também será zero.


A função normalizeangle foi modificada. Agora, se o número entrado
tiver norma negativa, a saída terá norma positiva com o ângulo
subtraído de PI radianos. O ângulo de saída estará, como na
versão anterior, entre -PI < ang <= PI.
O código com estas modificações está dado.


A função complexsub realiza a subtração de dois números, quaisquer
que sejam as suas bases. Esta função deve usar as funções complexsum,
negativecartesian e quaisquer outras necessárias para implementar a
subtração.
A função complexsub realiza a seguinte operação com seus operandos:
c1 = c1 - c2. O operando c1 também é o operando de saída e a base do
resultado será a base deste operando.
Esta função retorna zero se a operação for bem sucedida e retorna 2
caso ocorram problemas numéricos.


A função complexdvs realiza a divisão de dois números complexos,
quaisquer que sejam suas bases. Esta função deve usar as funções
complexmultiply, polarinversion e quaisquer outras que sejam
necessárias para implementar a divisão.
A função complexdvs realiza a seguinte operação com seus operandos:
c1 = c1/c2. O operando c1 também é o operando de saída e a base do
resultado será a mesma deste operando.
Esta função retorna zero se a operação for bem sucedida e retorna 2
caso ocorram problemas numéricos.


A função basicOp realiza as quatro operações básica sobre seus
operandos x e y, de forma que x = x op y, onde op pode ser uma
operação de soma, subtração, multiplicação ou divisão.
Os operandos x e y são números complexos cujas partes real e
imaginária são representadas em ponto flutuante com dupla precisão
(double). Estes operandos podem ser representados tanto em
coordenadas cartesianas (a + bj) quanto e coordenadas polares
(r*(exp(jg)), onde a e b representam as porções real e imaginária
e r e g representam o módulo e o ângulo do vetor no plano s
(imaginário).
Os campos ClpxNum *x e y são as variáveis passadas para a função.
O campo cmd define qual operação será realizada por basicOp. A
função aceita apenas as strings: "add", "sub", "mul" e "dvs" para
realizar a operação de soma, subtração, multiplicação ou divisão
sobre os operandos, respectivamente.
O campo outputmode define em qual sistema de coordenadas será
escrito o resultado da operação, desta forma pode apenas receber o
endereço de uma das duas strings "cart" ou "pol" ou NULL. Neste
último a função mantém a base original do operador de saída, sem
necessidade de realizar uma conversão de base ao final.
A função retorna zero se a operação for bem sucedida, retorna 1
caso algum operando ou campo da função aponte para strings não
definidas e retorna 2 caso ocorra uma divisão por zero ou outro
erro numérico.
Para implementar as funções você DEVE utilizar as funções básicas
fornecidas e implementadas, sempre que for possível. Na avaliação do
seu programa isso tem grande peso.

*/


// Descrição do Assignment anterior (SEM10)

// Neste assigment você deve continuar o desenvolvimento das
// funções que compõe uma pequena biblioteca que implementa
// as operações aritméticas básicas para números complexos
// na base cartesiana ou na base polar.
// 
// Nesta nova parte do projeto, utilizaremos as funções que
// você implementou no assignment da Semana 9.
// Assim, você deve copiar o código construído para as funções 
// do projeto da Semana 9 e colar neste novo projeto
//
// As especificações das funções implementadas no Assignment
// semana 9 continuam, em grande parte, as mesmas e seguem logo
// abaixo desta nova descrição.
// No entanto, as funções normalizeangle e multiplypolar 
// tiveram seus requisitos alterados de forma a melhorar seu 
// desempenho e para atender os requisitos das novas funções
// que serão implementadas.
// Sendo assim, testes adicionais para estas funções foram 
// implementados.
//
// A função normalizeangle recebe como parâmetro de entrada 
// um tipo Pol* cujo argumento do ângulo pode ter qualquer 
// amplitude em radianos, incluindo valores positivos e 
// negativos.
// A função agora normaliza o valor deste argumento de forma 
// que este esteja entre -PI < ângulo <= PI. Note que o 
// intervalo foi ligeiramente modificado.
// Outra modificação fornecida, que deve ser incorporada ao 
// final do seu código na função, trata da descontinuidade 
// e da imprecisão ou erros inerentes aos valores em 
// long double em torno do PI radianos.
// Imagine um ângulo calculado cujo valor deveria ser exatos 
// PI radianos. Este ângulo raramente terá este valor, devido 
// às aproximações do processamento em ponto flutuante. Na 
// realidade, este ângulo irá oscilar com um erro E entre 
// -PI+E e PI-E. Onde E é o erro de aproximação inserido pelas
// operações em ponto flutuante.
// Isso produz resultados inesperados e em grande parte
// errados quando o ângulo do número normalizado estiver
// nesta região.
// Assim, sempre que o valor calculado estiver dentro desta
// região de erro, o código irá aproximar automaticamente
// o resultado para PI, conforme pode ser visto no trecho 
// de código disponibilizado.
//
// A função cartesian2polar agora deve retornar valores de
// ângulo no intervalo entre -PI < ângulo <= PI.
//
// A nova versão da função multiplypolar deve retornar o 
// valor do ângulo calculado normalizado entre 
// -PI < ângulo <= PI. Para isso, você deve obrigatoriamente
// usar a função normalizeangle, chamando-a dentro da
// função multiplypolar.
//
// A função polar2cartesian recebe um valor Pol w em 
// coordenadas polares e o converte para cartesiano, 
// retornando-o na variável do tipo Cart apontada por x.
// Esta função deve verificar se o valor do módulo do
// número complexo de entrada é zero, então deve retornar
// um vetor com coordenadas cartesianas zero.
// Adicionalmente a função testa se os valores do módulo ou 
// do ângulo do número entrado são INFINITY. Caso sejam, a
// função deve retornar um par de coordenadas INFINITY.
//
// Para implementar as funções complexsum e complexmultiply 
// é preciso entender como é aplicado o tipo ComplexNum, o  
// qual é definido em main.h
// ComplexNum é definido por uma struct que contém dois 
// campos, um do tipo Clpx e outro do tipo char*. O primeiro 
// contém um valor complexo s, que pode conter em um certo
// momento um valor na base cartesiana ou um valor na base
// polar. O segundo (mode) é um ponteiro para a string cujo 
// conteúdo define qual a base do número complexo armazenado 
// em s.
// Nas linhas 5 e 6 de main.h estão definidas as strings 
// polar e cartesian. Estas são as strings para qual o 
// campo mode de uma variável do tipo ClpxNum deve apontar,
// dependendo, como já dito, da base do número complexo
// armazenado no campo s desta mesma variável.
// O campo s é do tipo Clpx, que é uma Union das structs 
// Cart e Pol. Isto permite que o campo s possa conter valores
// do tipo Cart ou do tipo Pol, ou seja, s pode representar
// tanto um número complexo na base cartesiana quanto um
// número complexo na base polar.
// Por exemplo, se uma variável do tipo ClpxNum contiver
// um número complexo cartesiano, então, seu campo mode irá 
// apontar para a string cartesian. Desta forma, o campo s
// conterá valores das coordenadas cartesianas do número.
// Da mesma forma, se o campo s contiver um número complexo 
// polar, o campo mode irá apontar para a string polar. 
// Consequentemente o campo s terá conterá sub-campos com as
// coordenadas polares do número.
// 
// A função complexsum soma dois números complexos c1 e c2, 
// encapsulados com o tipo ClpxNum.
// Nossa biblioteca conseque apenas somar números na base
// cartesiana. A biblioteca também possui funções para 
// converter números da base cartesiana para a base polar e
// vice-versa.
// A função complexsum pode somar dois números complexos, os 
// quais podem estar em qualquer base. A função realiza a 
// seguinte operação: c1 = c1 + c2.
// Se necessário, a função converte uma cópia dos números
// a serem somados para a base cartesiana, soma os mesmos,
// converte o resultado para a base original de c1 e 
// retorna o resultado para c1.
// A função retorna zero se não houver erros. Eventualmente
// caso alguma função de conversão retorne um código de erro
// (deferente de zero), então a função complexsum pára sua
// execução e retorna o erro.
//
// A função complexmultiply opera de análoga à função 
// complexsum. Nossa biblioteca somente consegue multiplicar
// números na base polar.
//
// Para a implementação das funções deste assignment é
// mandatório que as funções básicas construídas sejam
// utilizadas dentro das funções de mais alto nível
// quando necessário. O uso de código redundante irá 
// tornar seu exercício errado, mesmo que esteja funcional.
//


// Descrição do Assignment anterior (SEM9)

/*
Sua tarefa é ímplementar as funções acima prototipadas
Estas funções usam as structs, unions e typedefs definidos em
main.h. Estas definições permitem a manipulação de números
complexos no sistema de coordenadas cartesiano (a+bj) ou no
sistema polar (r*exp(jg)) (r=módulo, g=ângulo).

O objetivo é criar funções básicas para serem utilizadas na
construção de funções mais elaboradas, que permitirão lidar
com os problemas inerentes aos números complexos de maneira
transparente ao usuário.

Estas funções básicas, apesar de implementarem operações
matemáticas elementares, lidam com alguns problemas numéricos
importantes. Assim, os testes criados em test.cpp verificam
a implementação de cada uma destas quatro funções iniciais.
Os testes estão agrupados em tópicos referentes a cada uma
das funções a serem testadas, como pode ser visto no Test
Explorer.

A função somacartesiana recebe dois parâmetros do tipo Cart
e realiza a seguinte operação vetorial sobre estes:
x = x + y,
onde dois números complexos (x, y) que estão na forma
cartesiana, são somados.
Nesta versão, esta função sempre deve retornar zero.

A função cartesian2polar converte um número na forma
cartesiana (x) em número na forma polar (w), onde x e w
são os parâmetros de entrada e de saída da função,
respectivamente.
Esta função converte vetores cartesianos nos quatro
quadrantes. A função utiliza como unidade angular o radiano.
Na saída, o ângulo (g) estará entre -PI <= g < PI (rad).
A implementação de algumas das funções trigonométricas
tradicionais em math.h possuem problemas em diferentes
quadrantes e nos seus limites. Sua tarefa é pesquisar e
encontrar a solução.
Nesta versão, esta função sempre deve retornar zero.

A função multiplypolar realiza a seguinte operação sobre
números na forma polar:
w = w * p
Como a função poderá ser utilizada para a divisão de dois
números, esta testa para alguns problemas númericos comums.
Caso o módulo de qualquer um dos operadores for zero, então
o resultado retornado será o vetor polar (0,0), pois não há
definição de ângulo para vetor com comprimento zero.
Nas bibliotecas utilizadas existe a constante INFINITY, que
define um número o qual valores acima deste são considerados
números infinitos. Assim, caso algum dos módulos dos parâmetros
fornecidos para a função forem iguais ou maiores que INFINITY,
então a saída terá módulo INFINITY. O ângulo não é afetado.
Nas bibliotecas também é definido a constante _HUGE_ENUF. Caso
ambos os parâmetros de entrada forem maiores que _HUGE_ENUF,
então a função deve retornar INFINITY. O ângulo não é afetado.
Verifique como é definida a constante INFINITY e entenda o
porquê desta regra.
A função retorna zero normalmente e retorna 2 caso o módulo do
resultado retornado seja INFINITY.

A função normalizeangle normaliza o ângulo de um número
complexo (w) na forma polar. O número entrado pode ter um ângulo
qualquer expresso em radianos, inclusive com valor negativo.
A função deve converter o ângulo entrado para o intervalo
positivo entre -PI <= g < PI (rad).
A norma do vetor não é processada, permanecendo inalterada.
Esta função sempre deve retornar zero.

*/
