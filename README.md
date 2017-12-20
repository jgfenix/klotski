<h1><a name="a_pequena_donzela_encarcerada" id="a_pequena_donzela_encarcerada">A Pequena donzela encarcerada</a></h1>

Existe uma antiga lenda japonesa sobre a hakoiri musume, ou seja, a pequena donzela, que não sabe nada sobre o mundo, que está encarcerada numa caixa de ilusões. Seu caminho para a liberdade é impedido por sua mãe, seu pai, irmãos e irmãs…. Enquanto ela não sair desta caixa, não conhecerá a luz da verdade.

Seu trabalho de programação deste semestre é ajudar a pobre hakoiri musume a encontrar seu caminho até a luz! Porém, neste mundo cheio de simbolismos da cultura japonesa, cada personagem será representado no computador por uma figura geométrica que corresponde à inocência do personagem, mais que a forma física. Assim a nossa pobre hakoiri musume é representada pela maior figura do tabuleiro, representando que sua inocência a impede de encontrar o caminho até a saída, enquanto sua família impõe difilculdades neste caminho.

As regras são simples: Você deve levar a donzela até a saída da caixa, deslocando as outras figuras para dar passagem.  Neste nosso tabuleiro matemático, cada peça é representada por um número e as casas vazias são representadas por zero. O tabuleiro tem NxM casas com as posições iniciais das peças. Uma figura só pode ser movimentada se existerem casas livres suficientes para a movimentação e só pode ser movimentada na horizontal ou na vertical, nunca na diagonal. Seu objetivo é levar a donzela até a porta de saída, representada por S.
Por exemplo, a configuração inicial do tipo:
<a href="https://github.com/jgfenix/klotski/blob/master/img/haikoiricometras.png" class="media" title="haikoiricometras.png"><img src="https://github.com/jgfenix/klotski/blob/master/img/haikoiricometras.png" class="media" alt="" /></a>

se
D=Donzela, P=Pai, M=Mãe, I=Irmão, T=Tia, R=iRmã O=Tio, C=Cunhado, N=Cunhada, 
seria representada por:
<p>
DD PPI

DD PIM

RRIIMMS

TTOICNS

TOOICN

</p>

<p>
Uma solução possível para este problema é o da força bruta, procurando todas as possibilidades até colocar a donzela na posição adequada do tabuleiro. Esta busca pode ser computacionalmente muito intensiva e você deve eliminar os caminhos já pecorridos.  Uma forma de diminuir este trabalho seria armazenar cada movimento possível numa árvore (não binária). Assim, a partir da posição inicial, temos 3 possíveis movimentos: da própria donzela, para a direita; do pai, para a esquerda e do irmão, para cima. Se cada possível configuração do tabuleiro possuir uma identificação única, se viocê atingir uma configuração que já se encontra na árvore, você pode continuar a partir deste ponto.
</p>

<h2>Níveis resolvidos</h2>

  <img src="https://github.com/jgfenix/klotski/blob/master/img/niveis_resolvidos.jpeg" align="center"/>
  Basta ir na pasta src, e com o terminal, digitar(por exemplo):
  <br>make nivel_1<br>make nivel_2
  *estão disponíveis os níveis de 1 a 6 + labirinto
  
<h2>Obs:</h2>
Quem fizer para a seguinte configuração, ganha metade dos pontos.

<a href="https://github.com/jgfenix/klotski/blob/master/img/d37cf0507daf80ed379d080f31162772.media.221x259.png" class="media" title="haikoiri1.png"><img src="https://github.com/jgfenix/klotski/blob/master/img/d37cf0507daf80ed379d080f31162772.media.221x259.png" class="medialeft" align="left" alt="" /></a>
