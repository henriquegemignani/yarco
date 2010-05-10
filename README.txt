MAC0211 - Laboratorio de Programacao I
Projeto de Jogo
Nomes:
Andre Mesquita Pereira              nUSP: 6879530
Henrique Gemignani Passos Lima      nUSP: 6879634
Renan Teruo Carneiro                nUSP: 6514157



1) O programa

O programa, no momento chamado "Yarco" por motivos desconhecidos, atualmente apenas imprime os
passageiros na tela conforme eles esariam a cada segundo. # representa um passageiro enquanto
! representa dois ou mais passageiros, muito provavelmente colidindo. Ele pode ser configurado
atrav�s de diversos par�metros da linha de comando.
Para mais informa��es, execute-o com a op�ao -h ou --help.

� poss�vel criar tamb�m um execut�vel de testes, com algumas op��es pr�-definidas. N�o tivemos
tempo de fazer algo completamente customiz�vel, embora isso possivelmente se de pelo fato de essa
ideia sequer ter sido discutida. Ele aceita os mesmos pa�metros que o execut�vel principal, embora
algumas das op��es possam ignorar o valor fornecido pelo usu�rio.


2) Gerando o programa e outros comandos do Makefile

Para gerar o programa execut�vel principal, basta um simples "make", ou "make yarco" caso queira
ser criterioso. O arquivo de testes pode ser gerado a partir do comando "make yarco.test".

Existem os comando "make clean", "make moreclean" e "make realclean". O comando "make clean" remove
todos os .o e os execut�veis, e qualquer outro arquivo infeliz cujo nome comece com yarco. "make
moreclean" tamb�m remove quaisquer arquivos de backup presentes. Finalmente, "make realclean" remove
tamb�m a pasta publish, criada pelos comando "make publish" e "make publish-source", caso ela exista.

Os comandos "make publish" e "make publish-source" servem para criar automaticamente pacotes prontos
para a distribui��o desse programa. "make publish" gera um pacote com o execut�vel pronto para
execu��o, enquanto "make publish-source" gera o pacote com o c�digo fonte do programa, al�m deste 
Readme. (o pacote entregue foi gerado com esse comando)

"make TODO" � algo para os desenvolvedores saberem o que tem que fazer sem olhar arquivo por arquivo.
Voc� pode tentar, mas n�o deve fazer muita coisa. Al�m de criar um autoTODO.txt vazio. Eu espero.

Nesse pacote deve estar incluso o Makefile. Se n�o estiver, culpe o Haruki. Sim, ele � de outro
grupo, mas isso � um pequeno detalhe.

"make nuke" ainda n�o existe, est� em processo de enriquecimento de ur�nio. Logo estar� pronto.
Ainda n�o temos suporte ao preparo de sandu�ches nem ao faz-de-conta. Tamb�m n�o foi implementado
os poderes de vaca.
