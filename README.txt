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
através de diversos parâmetros da linha de comando.
Para mais informações, execute-o com a opçao -h ou --help.

É possivel criar também um executável de testes, com algumas opções pré-definidas. Não tivemos
tempo de fazer algo completamente customizável, embora isso possivelmente se de pelo fato de essa
ideia sequer ter sido discutida. Ele aceita os mesmos paâmetros que o executável principal, embora
algumas das opções possam ignorar o valor fornecido pelo usuário.


2) Gerando o programa e outros comandos do Makefile

Para gerar o programa executável principal, basta um simples "make", ou "make yarco" caso queira
ser criterioso. O arquivo de testes pode ser gerado a partir do comando "make yarco.test".

Existem os comando "make clean", "make moreclean" e "make realclean". O comando "make clean" remove
todos os .o e os executaveis, e qualquer outro arquivo infeliz cujo nome comece com yarco. "make
moreclean" também remove quaisquer arquivos de backup presentes. Finalmente, "make realclean" remove
também a pasta publish, criada pelos comando "make publish" e "make publish-source", caso ela exista.

Os comandos "make publish" e "make publish-source" servem para criar automaticamente pacotes prontos
para a distribuição desse programa. "make publish" gera um pacote com o executavel pronto para
execução, enquanto "make publish-source" gera o pacote com o código fonte do programa, além deste 
Readme. (o pacote que entregue foi gerado com esse comando)

"make TODO" é algo para os desenvolvedors saberem o que tem que fazer sem olhar arquivo por arquivo.
Você pode tentar, mas não deve fazer muita coisa. Além de criar um autoTODO.txt vazio. Eu espero.

Nesse pacote deve estar incluso o Makefile. Se não estiver, culpe o Haruki. Sim, ele é de outro
grupo, mas isso é um pequeno detalhe.

"make nuke" ainda nao existe, esta em processo de enriquecimento de uranio. Logo estara pronto.
Ainda não temos suporte ao preparo de sanduíches nem ao faz-de-conta. Tambem nao foi implementado
ainda poderes de vaca.
