#include <stddef.h>
#include "main.h"
#define _USE_MATH_DEFINES
#include "math.h"
#include "string.h"

#define Nsmall 1e-14

unsigned basicOp(CplxNum* x, CplxNum y, const char* cmd, const char* outputmode) {
    

}

unsigned complexsub(CplxNum* c1, CplxNum c2) {
   

}

unsigned complexdvs(CplxNum* c1, CplxNum c2) {
   

}

unsigned polarinvertion(Pol* w, Pol p) { 
    // Normaliza o ângulo de p
    //  A norma de p será sempre positiva e 
    //  o ângulo será sempre entre -M_PI < p.g <= M_PI
    normalizeangle(&p);
    // Se a norma é zero, então o angulo também é zero
    if (fabs(p.r - 0.0) < Nsmall)
        p.g = 0;
    // Não modifique o código acima
    // Implemente seu código abaixo


}

unsigned negativecartesian(Cart* x, Cart y) {
   

}

unsigned somacartesiana(Cart* x, Cart y) {

    x->a = x->a + y.a;
    x->b = x->b + y.b;

    return 0;
}

unsigned cartesian2polar(Pol* w, Cart x) {

    w->r = sqrt(x.a * x.a + x.b * x.b);
    w->g = atan2(x.b, x.a);

    return 0;
}

unsigned multiplypolar(Pol* w, Pol p) {

    // Testa para uma ou outra entrada zero
    if (!(w->r != 0.0) || !(p.r != 0)) {
        w->g = 0.0;
        w->r = 0.0;
        return 0;
    }

    // Soma os ângulos
    w->g = w->g + p.g;
    normalizeangle(w);

    // Testa para uma ou outra entrada infinita
    if (w->r >= INFINITY || p.r >= INFINITY) {
        w->r = INFINITY;
        return 2;
    }

    // Testa se as duas entradas tem números gigantescos
    if (w->r >= _HUGE_ENUF && p.r >= _HUGE_ENUF) {
        w->r = INFINITY;
        return 2;
    }

    // Multiplica as normas
    w->r = w->r * p.r;

    return 0;
}

// Normaliza o ângulo no intervalo PI > ângulo >= PI
unsigned normalizeangle(Pol* w) {
    long double angle, n_angle, frac;
    long long int integ;

    n_angle = w->g / (2 * M_PI); // Quantidade de 2PI existem em w->g
    integ = (long long int) n_angle; // Quantidades inteiras de 2PI existem em n_angle
    frac = (n_angle - (long double)integ); // Separa a fração de 2PI existe em n_angle
    angle = frac * 2 * M_PI; // 0 <= |angle| < 2*PI
    if (angle >= 0) {
        if (angle > M_PI) {
            w->g = -(2 * M_PI - angle);
        }
        else {
            w->g = angle;
        }
    }
    else {
        angle = -angle;
        if (angle > M_PI) {
            w->g = (2 * M_PI - angle);
        }
        else {
            w->g = -angle;
        }
    }
    // Marretada numérica
    // Se o ângulo estiver na vizinhança de PI, então é PI
    if ((M_PI - fabsl(w->g)) < Nsmall) {
        w->g = M_PI;
    }
    
    // Se a norma de w for menor que zero,
    //  subtrai PI (180o) do angulo de w
    //  inverte o sinal da norma de w
    //  renormaliza
    if (w->r < 0) {
        w->g = w->g - M_PI;
        w->r = -w->r;

        // Renormaliza
        angle = w->g;
        if (angle >= 0) {
            if (angle > M_PI) {
                w->g = -(2 * M_PI - angle);
            }
            else {
                w->g = angle;
            }
        }
        else {
            angle = -angle;
            if (angle > M_PI) {
                w->g = (2 * M_PI - angle);
            }
            else {
                w->g = -angle;
            }
        }
        // Marretada numérica
        // Se o ângulo estiver na vizinhança de PI, então é PI
        if ((M_PI - fabsl(w->g)) < Nsmall) {
            w->g = M_PI;
        }
    }

    return 0;
}

unsigned polar2cartesian(Cart* x, Pol w) {

    if (w.r == 0.0) {
        x->a = 0.0;
        x->b = 0.0;
        return 0;
    }

    if (w.r >= INFINITY) {
        x->a = INFINITY;
        x->b = INFINITY;
        return 2;
    }

    if (w.g >= INFINITY) {
        x->a = INFINITY;
        x->b = INFINITY;
        return 2;
    }

    // normalizeangle(&w);

    x->a = w.r * cos(w.g);
    x->b = w.r * sin(w.g);

    return 0;
}

unsigned complexsum(CplxNum* c1, CplxNum c2) {

    Cart c1_cart, c2_cart;
    unsigned ret;

    if (strcmp(c1->mode, cartesian) == 0) {
        if (strcmp(c2.mode, polar) == 0) {
            // Transforma c2 para cartesiano em c2_cart
            ret = polar2cartesian(&c2_cart, c2.s.pol);
            if (ret != 0) {
                return ret;
            }
            // Soma c1 e c2_cart
            ret = somacartesiana(&c1->s.cart, c2_cart);
            if (ret != 0) {
                return ret;
            }
        }
        else {
            // Soma c1 e c2
            ret = somacartesiana(&c1->s.cart, c2.s.cart);
            if (ret != 0) {
                return ret;
            }
        }
    }
    else {
        if (strcmp(c2.mode, polar) == 0) {
            // transforma c1 e c2 para cartesiano em c1_cart e em c2_cart
            ret = polar2cartesian(&c1_cart, c1->s.pol);
            if (ret != 0) {
                return ret;
            }
            ret = polar2cartesian(&c2_cart, c2.s.pol);
            if (ret != 0) {
                return ret;
            }
            // soma c1_cart e c2_cart
            ret = somacartesiana(&c1_cart, c2_cart);
            if (ret != 0) {
                return ret;
            }
            // transforma c1_cart para polar em c1
            ret = cartesian2polar(&c1->s.pol, c1_cart);
            if (ret != 0) {
                return ret;
            }
        }
        else {
            // transforma c1 para cartesiano em c1_cart
            ret = polar2cartesian(&c1_cart, c1->s.pol);
            if (ret != 0) {
                return ret;
            }
            // soma c1_cart e c2
            ret = somacartesiana(&c1_cart, c2.s.cart);
            if (ret != 0) {
                return ret;
            }
            // transforma c1_cart para polar em c1
            ret = cartesian2polar(&c1->s.pol, c1_cart);
            if (ret != 0) {
                return ret;
            }
        }
    }

    return 0;
}

unsigned complexmultiply(CplxNum* c1, CplxNum c2) {
    Pol c1_pol, c2_pol;
    unsigned ret;

    if (strcmp(c1->mode, cartesian) == 0) {
        if (strcmp(c2.mode, polar) == 0) {
            // transforma c1 para polar em c1_pol
            ret = cartesian2polar(&c1_pol, c1->s.cart);
            if (ret != 0) {
                return 2;
            }
            // multiplica c1_pol por c2
            ret = multiplypolar(&c1_pol, c2.s.pol);
            if (ret != 0) {
                return 2;
            }
            // transforma c1_pol para cartesiano em c1
            ret = polar2cartesian(&c1->s.cart, c1_pol);
            if (ret != 0) {
                return 2;
            }
        }
        else {
            // transforma c1 para polar em c1_pol
            ret = cartesian2polar(&c1_pol, c1->s.cart);
            if (ret != 0) {
                return 2;
            }
            // transforma c2 para polar em c2_pol
            ret = cartesian2polar(&c2_pol, c2.s.cart);
            if (ret != 0) {
                return 2;
            }
            // multiplica c1_pol por c2_pol
            ret = multiplypolar(&c1_pol, c2_pol);
            if (ret != 0) {
                return 2;
            }
            // transforma c1_pol para cartesiano em c1
            ret = polar2cartesian(&c1->s.cart, c1_pol);
            if (ret != 0) {
                return 2;
            }
        }
    }
    else {
        if (strcmp(c2.mode, polar) == 0) {
            // multiplica c1 por c2
            ret = multiplypolar(&c1->s.pol, c2.s.pol);
            if (ret != 0) {
                return 2;
            }
        }
        else {
            // transforma c2 para polar em c2_pol
            ret = cartesian2polar(&c2_pol, c2.s.cart);
            if (ret != 0) {
                return 2;
            }
            // multiplica c1 por c2_pol
            ret = multiplypolar(&c1->s.pol, c2_pol);
            if (ret != 0) {
                return 2;
            }
        }
    }

    return 0;
}

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
