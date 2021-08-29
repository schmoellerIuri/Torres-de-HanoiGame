Iuri Schmoeller 

Descrição da aplicação:
	A aplicação consiste no clássico jogo das torres de Hanói, com o incremento de um novo modo de jogo. O jogo inicialmente vai começar com 3 torres e com a primeira torre (da esquerda para a direita) com discos empilhados, o objetivo do modo de jogo padrão é transportar todos os discos para a terceira torre da esquerda para a direita, com uma regra de que nenhum disco pode ficar acima de 
outro disco de tamanho menor, podendo mover os discos apenas do topo da torre e inserindo-os no topo das outras torres, o jogo acaba quando todos os discos estiverem empilhados do menor para o maior, na terceira torre. 
	O objetivo do modo de jogo "especial" é o mesmo do modo clássico de torres de Hanói, porém a torre inicial começa invertida, com discos de tamanho menor embaixo dos discos maiores(porém é a única situação onde isso pode ocorrer), o disco que pode ser arrastado agora é o disco da base da torre, porém a inserção continua no topo, com a mesma regra de que não se pode inserir um disco em cima de um menor que ele. O jogo acaba quando todos os discos estiverem empilhados do menor para o maior, na terceira torre.
	Além disso, podem ser inseridos e removidos discos pressionando os botões de cima e baixo em uma spinbox abaixo das torres, e também recomeçar o jogo apertando o botão de restart, além dos botões de mudar o modo de jogo no menu carregar, também podendo salvar o jogo atual e carregar um novo jogo com seus respectivos botões no menu.

*Quando um novo jogo é carregado a spinbox não atualiza seu valor para o número total de discos do jogo carregado, porém isso não afeta em nada o funcionamento do jogo e não acarreta em nenhum bug, se a spinbox for pressionada novamente isso volta ao normal.

-Faz-se necessário o uso da plataforma Qt Creator para a aplicação rodar, apenas dando dois cliques no arquivo TORRESDEHANOI.pro em seguida pressionando o botão de run do Qt.