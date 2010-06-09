MAC0211 - Laboratorio de Programacao I
Projeto de Jogo
Nomes:
Andre Mesquita Pereira              nUSP: 6879530
Henrique Gemignani Passos Lima      nUSP: 6879634
Renan Teruo Carneiro                nUSP: 6514157



1) O programa

Bem vindo � segunda segunda itera��o do projeto! Nessa etapa, o ainda misteriosamente nomeado Yarco
� capaz de algo pr�ximo de uma simula��o do oceano. Assim como na itera��o anterior, o programa po-
de ser configurado da maneira que mais lhe agradar via par�metors da linha de comando. Consulte a 
op��o -h para mais informa��es. 

Quanto ao funcionamento do programa, agora temos botes, passageiros, corais e a R.M.S. Asimov. Cada
objeto � representado por uma forma geom�trica simples. A seguir, mais detalhes sobre cada um deles:

1.1 - Os passageiros
Passageiros s�o representados por simp�ticas bolinhas de cores aleat�rias que flutuam a esmo no
oceano. Ao sa�rem da tela, eles aparecem em outra borda, e ao colidirem com qualquer coisa que n�o
seja um bote, eles simplesmente quicam. Numa colis�o com um bote, eles s�o alegremente exter- digo,
resgatados e saem do jogo.

1.2 - Os corais
Corais s�o o obst�culo b�sico, atrapalhando a vida de todos os botes bem-intencionados. S�o repre-
sentados por quadrados de cores e tamanho aleat�rios, e, na parte jog�vel, provavelmente sempre es-
tar�o no meio do caminho, mesmo sendo absolutamente im�veis.

1.3 - A R.M.S. Asimov
Enquanto estiver rodando a simula��o f�sica, procure por um grande ret�ngulo cinza. Esse � o glori-
oso navio, a R.M.S. Asimov. Por enquanto, ela s� fica parada e n�o faz nada al�m de agir como uma
parede, mas ser� mais importante no futuro.

1.4 - Os botes
Os nossos queridos botes s�o representados por triangulozinhos, um vermelho e um azul. Eles surgem
nas bordas da tela e s�o capazes de acelerar para frente e para tr�s, em rela��o � dire��o na qual
est�o apontando, e podem virar quase livremente. Eles simplesmente quicam quando batem nas bordas
da tela ou na R.M.S. Asimov, e geralmente, simplesmente quicam nos corais. Exceto pela terceira co-
lis�o. Nesse caso, eles ficam encalhados por um tempo, at� ressurgirem numa das bordas da tela, in-
tactos, como se nada tivesse acontecido.


2) Gerando o programa e outros comandos do Makefile

Como de sempre, para gerar o programa usualmente, um simples make basta. Make clean � para aqueles
que se cansaram de ver as coisas boiando e querem se livrar de todos os .o e de qualquer coisa cujo
nome comece com yarco na pasta corrente. Make moreclean remove tamb�m todos os arquivos de backup,
e make realclean remove, al�m desses, tamb�m qualquer cosia que estivesse pronta a ser publicada.

O make nuke foi abortado, uma vez que rm -rf ./ pode ser perigoso nas m�os erradas. E al�m disso,
n�o quer�amos ser acusados de terrorismo nuclear.

Make publish � �til para aqueles que quiserem, por algum motivo, redistribuir o execut�vel, enquan-
to make publish-source gera um pacote com tudo necess�rio para compilar, editar e redistribuir esse
programa. Bom, exceto o allegro e o gcc, mas esses s�o utilit�rios mais facilmente acess�veis.

E, s� pra reafirmar, n�o fazemos sandu�ches nem bolos.
