MAC0211 - Laboratorio de Programacao I
Projeto de Jogo
Nomes:
Andre Mesquita Pereira              nUSP: 6879530
Henrique Gemignani Passos Lima      nUSP: 6879634
Renan Teruo Carneiro                nUSP: 6514157



1) O programa

Bem vindo à segunda segunda iteração do projeto! Nessa etapa, o ainda misteriosamente nomeado Yarco
é capaz de algo próximo de uma simulação do oceano. Assim como na iteração anterior, o programa po-
de ser configurado da maneira que mais lhe agradar via parâmetors da linha de comando. Consulte a 
opção -h para mais informações. 

Quanto ao funcionamento do programa, agora temos botes, passageiros, corais e a R.M.S. Asimov. Cada
objeto é representado por uma forma geométrica simples. A seguir, mais detalhes sobre cada um deles:

1.1 - Os passageiros
Passageiros são representados por simpáticas bolinhas de cores aleatórias que flutuam a esmo no
oceano. Ao saírem da tela, eles aparecem em outra borda, e ao colidirem com qualquer coisa que não
seja um bote, eles simplesmente quicam. Numa colisão com um bote, eles são alegremente exter- digo,
resgatados e saem do jogo.

1.2 - Os corais
Corais são o obstáculo básico, atrapalhando a vida de todos os botes bem-intencionados. São repre-
sentados por quadrados de cores e tamanho aleatórios, e, na parte jogável, provavelmente sempre es-
tarão no meio do caminho, mesmo sendo absolutamente imóveis.

1.3 - A R.M.S. Asimov
Enquanto estiver rodando a simulação física, procure por um grande retângulo cinza. Esse é o glori-
oso navio, a R.M.S. Asimov. Por enquanto, ela só fica parada e não faz nada além de agir como uma
parede, mas será mais importante no futuro.

1.4 - Os botes
Os nossos queridos botes são representados por triangulozinhos, um vermelho e um azul. Eles surgem
nas bordas da tela e são capazes de acelerar para frente e para trás, em relação à direção na qual
estão apontando, e podem virar quase livremente. Eles simplesmente quicam quando batem nas bordas
da tela ou na R.M.S. Asimov, e geralmente, simplesmente quicam nos corais. Exceto pela terceira co-
lisão. Nesse caso, eles ficam encalhados por um tempo, até ressurgirem numa das bordas da tela, in-
tactos, como se nada tivesse acontecido.


2) Gerando o programa e outros comandos do Makefile

Como de sempre, para gerar o programa usualmente, um simples make basta. Make clean é para aqueles
que se cansaram de ver as coisas boiando e querem se livrar de todos os .o e de qualquer coisa cujo
nome comece com yarco na pasta corrente. Make moreclean remove também todos os arquivos de backup,
e make realclean remove, além desses, também qualquer cosia que estivesse pronta a ser publicada.

O make nuke foi abortado, uma vez que rm -rf ./ pode ser perigoso nas mãos erradas. E além disso,
não queríamos ser acusados de terrorismo nuclear.

Make publish é útil para aqueles que quiserem, por algum motivo, redistribuir o executável, enquan-
to make publish-source gera um pacote com tudo necessário para compilar, editar e redistribuir esse
programa. Bom, exceto o allegro e o gcc, mas esses são utilitários mais facilmente acessíveis.

E, só pra reafirmar, não fazemos sanduíches nem bolos.
