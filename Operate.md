Documentação de uso do Buggy AWD
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

O carrinho é controlado através de uma ESP32-Wroom32. Para carregar o software no carrinho é necessário ter o arduino IDE v2 instalado, o programa se conecta à placa, compila e grava o firmware.

Para se conectar com sucesso, a porta USB deve ter as permissões de leitura e gravação.
No Windows essas permissões devem estar ativas por padrão,nos sistemas baseados em Linux elas podem ser alteradas momentaneamente ou permanentemente. Para liberar momentaneamente a porta basta inserir no terminal o comando:

`sudo chown *seu usuário* /dev/ttyUSBx`

Em que “x” é o número da unidade USB correspondente à conectada ao Carrinho com a ESP (geralmente 0). Conecte o carrinho a esp32 com um cabo USB<->microUSB, selecione a placa ESP32 Wrover kit, e selecione a opção upload.

O software configura a ESP como AP(Access point). Ele gera uma rede Wi-Fi em que é possível se conectar. Por padrão as credenciais de rede são:

Nome da Rede: Buggy AWD
Senha: abc42069

O ESP32 no modo AP tem o IP 192.168.4.1, a menos que seja configurado de outra forma. Após se conectar você deve entrar na barra de endereços do seu navegador o IP do carrinho, 192.168.4.1 por padrão. Ao se conectar você será recebido nesta página:

![Screenshot_20250216_224251](https://github.com/user-attachments/assets/3bb8da15-02ff-4dd2-ab4b-cb9875cd9663)
(Fonte: Elaboração própria)

Esta é a página inicial do carrinho.

A página possui botões para acionar os comandos do carrinho e indicações de status dos motores responsáveis por cada movimento.

Os comandos ‘UP’, ‘DOWN’, ‘LEFT’, e ‘RIGHT‘ acionam os movimentos do carrinho, para frente, para trás, para girar à direita e para girar à esquerda. Cada comando só pode ser acionado individualmente. Os comandos ‘LEFT’ e ‘RIGHT’ fazem com que o carrinho gire sobre o seu próprio eixo, já que o carrinho não possui eixo para esterçamento, suas rodas são fixas.

É importante lembrar que página usa o método GET como gatilho para os comandos do carrinho, e cada comando é uma página, isso significa que o botão voltar do navegador funciona como um atalho para o comando anterior.

O botão ‘RESET’ cessa todos os movimentos do carrinho e retorna a página ao seu estado inicial.

Ao pressionar qualquer comando, o carrinho passará a se mover e haverá uma atualização dos status presentes na página, tanto da atividade dos motores quanto a tensão das baterias. esse status será atualizado toda vez que um novo comando for acionado.

Quando um botão é pressionado ele fica verde, e é indicativo que os motores estão acionados naquela direção.

Na página web, é mostrada a tensão sendo aplicada pelas baterias do Buggy AWD. Esse dado está presente acima do botão RESET, ao final da página, ele somente atualizará caso a página seja recarregada (ou algum botão for apertado ou solto).

