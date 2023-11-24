# Aunimal-SYS
### Status: ✅ Concluído
Sistema de gerenciamento de reservas de um hotel Pet usando linguagem C. Neste sistema é possível alterar, inserir e listas reservas do dia ou todas. A compilação é feita separadamente formando três executáveis com funções próprias.

<h4>Tecnologia utilizada:</h4>
<ul>
 <li>C</li>
</ul>

<h4>Passos para executar a aplicação:</h4>
<ol>
  <li>Abrir o terminal na pasta da aplicação</li>
  <li>No terminal digite: gcc -c -o lista.o lista.c</li>
  <li>Digite: gcc -o Gerador gerador.c lista.o</li>
  <li>Digite: gcc -o Exportador exportador.c lista.o</li>
  <li>Digite: gcc -o Editor editor.c lista.o</li>
  <li>Digite: gcc -o Gerador gerador.c lista.o</li>
  <li>Até aqui foram compilados/ligados os códigos e criados os três programas executáveis</li>
  <li>Digite no terminal para executar o Gerador e criar o binário: ./Gerador dados.txt binario.bin</li>
  <li>Digite no terminal para executar o Editor (manipular dados): ./Editor binario.bin</li>
  <li>Digite no terminal para executar o Exportador e criar o arquivo de texto: ./Gerador relatorio.txt binario.bin</li>
</ol>
