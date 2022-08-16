# Sonar com Arduino
## Introdução
O sonar é uma técnica que usa a propagação sonora com o intuito de navegação, comunicação ou detecção de objetos na água, como outras embarcações ou grandes animais. Como é algo relativamente caro nossa ideia é criar um sonar usando componentes de fácil obtenção e programa-lo, usando o Arduino. [1][2]

## Objetivo
Desenvolver um sonar simples, que localize objetos próximos a um raio de 40 cm, usando como sensor de eco localização o HC-SR04 e mostrando em um LCD colorido a localização do objeto

## Material
O dispositivo utilizado como processador é o Arduino Mega 2560. O programa envia informações para um servo motor e 
recebe informações do sensor HC-SR04, que fica sob este. Um LCD TFT de 2.4" mostra o gráfico dos objetos aproximadamente. [3]

## Resultado
A montagem do sonar com Arduino trouxe alguns pontos positivos tais como: baixo custo e de fácil utilização.

## Conclusão
O projeto funcionou adequadamente, com um custo menor que US$50 menor quando comparado com sonares que realizam a mesma função. Futuramente deseja-se aprimorar o sonar fazendo-o funcionar em 360 graus e mostrar a distância numérica do objeto, deseja-se ainda utilizar dois sonares um oposto ao outro para mostrar o objeto em 2D.

## Referências
- [1]https://www.infoescola.com/tecnologia/sonar/, Acessado: 24/11/2018.
- [2]https://mundoeducacao.bol.uol.com.br/fisica/sonar.htm, Acessado:24/11/2018.
- [3]NEVES, A. A., SILVA, M. A., “Radar de Objetos”, SENAI/SC, 2017
