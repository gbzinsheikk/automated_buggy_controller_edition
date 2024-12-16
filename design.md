Design de Funcionamento
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Continuação de: https://github.com/gbzinsheikk/automated_buggy_controller_edition/blob/master/readme.md

Hardware
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

- **Microcontrolador ESP 32**

  O ESP 32 é um microcontrolador multifuncional e eficiente em termos de custo e energia, com suporte a Wi-Fi, o que o torna ideal para projetos de automação e sistemas conectados. 
Com isso em mente, esse microcontrolador foi escolhido por seu preço, disponibilidade e propriedades de conectividade Wi-Fi, que serão utilizadas para captar e transmitir as informações recebidas pelos controles na página Web para o carrinho. 

  ![EspImage](https://github.com/user-attachments/assets/4fd17249-a83c-44d2-b61b-db54e8352292)

  **Fonte: Byteflop (2024).**

- **Placa de Interface**

  De forma a usar o microcontrolador ESP32 com o carrinho precisamos de uma placa de interface. Essa placa fica responsável por transferir a pinagem do ESP para o carrinho, que originalmente não é compatível.
  
  ![PlacadeInterfaceImage2](https://github.com/user-attachments/assets/75446d12-d3c9-4056-aed6-f27858e13b1e)

  **Fonte: Abreu (2022, p.54).**

Software
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
- **Página Web**

  - Access Point
 
    Para o usuário poder realizar os comandos de movimento e controlar o Buggy, foi-se desenvolvido um código o qual transforma a ESP 32 em um access point. Esse access point age como uma estação de Wi-fi, onde o usuário através de qualquer dispositivo que tenha conectividade Wi-fi, possa entrar como cliente na rede criada pela ESP e assim, acesse uma página web que transmite os comandos em tempo real ao carrinho. 

  ![image](https://github.com/user-attachments/assets/7ce56df1-1cf7-4520-8c41-4f411e862c8d)
 
  **Fonte: Rui Santos (2024).**
  
    Baseado no [modelo](https://randomnerdtutorials.com/esp32-access-point-ap-web-server/) desenvolvido pelo Rui Santos. Para criar um web server através da ESP 32, foi-se preciso, primeiramente definir as credencias da rede a ser criada.  
    
      // Biblioteca Wi-Fi
      #include <WiFi.h>
      // Set web server port number to 80
      WiFiServer server(80);
      // Credenciais da network
      const char* ssid     = "BuggyAWD-AP";
      const char* password = "abc42069";

    Após isso, é necessário obter o IP do access point usando o softAPIP() e imprimir no monitor serial.

      // Conecta ao Wi-Fi com o SSID e senha
      Serial.print("Setting AP (Access Point)…");
      WiFi.softAP(ssid, password);
  
      IPAddress IP = WiFi.softAPIP();
      Serial.print("AP IP address: ");
      Serial.println(IP);
    
      server.begin();

    Implementado esse código, ao ligar a ESP 32 e nos conectar na rede provida por ela, devemos acessar a página web ao digitar no navegador o endereço de IP padrão do gerenciador de Wi-fi da ESP 32: **192.168.4.1**.

   - Interface
   
   Para a interface da página web, foi tido em mente um design simples e prático. Onde o usuário tenha dinamicidade ao controlar os comandos do Buggy, e claridade visual de quais botões e pinos estão ligados/desligados e qual movimentação está, ou não, está sendo realizada. Portanto foi escolhido um design semelhante a um controle de video game, os botões foram postos em uma posição de cruz em suas posições respectivas e também foi implementado um tracker de estado para cada um dos botões, onde ele mostra os pinos associados a cada botão e se estão ligados ou desligados. Por fim, temos o seguinte design:

  ![pagWeb_screenshot](https://github.com/user-attachments/assets/59af1dba-c623-459c-8fea-79207d46fc6d)

  **Fonte: Elaboração própria (2024).**

  O Buggy AWD possui 4 motores, **M1**(Direito, para frente), **M1N**(Direito, para trás), **M2**(Esquerdo, para frente), **M2N**(Esquerdo, para trás). Cada botão foi associado aos pinos da ESP correspondentes à movimentação requerida. Os motores e pinos escolhidos para cada movimento são demonstrados pela tabela abaixo:

  | Direção   | Motores   | ESP 32 Pins  |
  | --------- | --------- | ------------ |
  | UP        | M1 e M2   | D21 e D18    |
  | DOWN      | M1N e M2N | D19 e D22    |
  | LEFT      | M1 e M2N  | D21 e D19    |
  | RIGHT     | M2 e M1N  | D18 e D22    |

  **Fonte: Elaboração própria (2024).**

  Nota-se que, para as movimentações LEFT e RIGHT, além de alimentar o motor dianteiro necessário para virar, foi alimentado também um motor traseiro que auxilia no movimento do giro. Fazendo com que o carrinho gire em seu próprio eixo e mais rapidamente na direção requisitada. 
  
  Os botões da página servem como switches, alternando seu estado de ON para OFF dependendo do clique do usuário. Ao serem apertados, é primeiro verificado se o botão já não está ligado, se não estiver os terminais específicos daquele botão seram ligados, e seu display de estado na página web será atualizado. Caso o botão já esteja apertado, ele é retornado ao estado OFF. Abaixo está um exemplo do código implementado ao botão **DOWN**:

        // DOWN
            else if (header.indexOf("GET /down/on") >= 0) {
              // Liga DOWN
              Serial.println("DOWN pressed - GPIO 19 & GPIO 22 on");
              turnOffAllOutputs();
              output19State = "on";
              output22State = "on";
              digitalWrite(output19, HIGH);
              digitalWrite(output22, HIGH);
            } else if (header.indexOf("GET /down/off") >= 0) {
              // Desliga DOWN
              Serial.println("DOWN released - GPIO 19 & GPIO 22 off");
              output19State = "off";
              output22State = "off";
              digitalWrite(output19, LOW);
              digitalWrite(output22, LOW);

  Note também que, há uma função chamada "turnOffAllOutputs()" inicializando antes de ligar qualquer dos pinos daquele botão. Essa função foi implementada tendo em mente uma particularidade da placa do Buggy, onde caso os motores M1 e M1N ou M2 e M2N sejam ligados simultaneamente isso causará um curto circuito na placa, queimando-a. Para evitar isso, essa função desligará todos os inputs ligados anteriormente (se houver) antes de ligar o botão pedido.

  - Tracker de Bateria
 
  [...]

  - Sensores de Distância

  [...]

  - Armazenamento de inputs

  [...]
  A opção de armazenamento dos controles será realizada através de cookies criados usando a linguagem javascript, inserida no html da página, e permitem a função de salvar inputs do usuário. 

Esquemático
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

O esquema de funcionamento do carrinho, de forma simplificada, pode ser visualizado da seguinte forma:

  ![buggy 3 drawio](https://github.com/user-attachments/assets/e01c69c3-2861-4bb0-a179-4fc3eb880ccf)

  **Fonte: Elaboração própria (2024).**

- Conexões do ESP

  Usando a placa shield, podemos conectar o ESP ao carrinho e usá-lo como substituto ao arduino. Segue abaixo o esquemático da placa shield:

  ![image](https://github.com/user-attachments/assets/0776919d-c4cd-43e0-8e31-d755baa2ed92)

   **Fonte: Abreu (2022, p.51).**

  Os pinos da placa de interface em relação ao ESP32 seguem a seguinte relação:

  ### Pinos analógicos

  | ESP32 pin | Analog input | Signal |
  | --------- | ------------ | ------ |
  | D32       | ADC0         | Bat0   |
  | D33       | ADC1         | Bat1   |
  | X         | ADC2         | Ampop1 |
  | X         | ADC3         | Ampop2 |
  
  ### Sensor ultrassônico
  
  | ESP32 Pin | Signal |
  | --------- | ------ |
  | D13       | Echo0  |
  | D12       | Trig0  |
  | D14       | Echo1  |
  | D27       | Trig1  |
  
  ### Motores
  
  | ESP32 Pin | Signal |
  | --------- | ------ |
  | D21       | PWM1   |
  | D22       | PWM1N  |
  | D18       | PWM2   |
  | D19       | PWM2N  |
  
  ### Encoder de velocidade
  
  | ESP32 Pin | Signal |
  | --------- | ------ |
  | D15       | D0     |
  | D4        | D1     |
  
  ### Sensor ótico
  
  | ESP32 Pin | Signal |
  | --------- | ------ |
  | D26       | R_TCRT |
  | D25       | L_TCRT |
  
  ### UART
  
  | ESP32 Pin | Signal |
  | --------- | ------ |
  | TX        | TX     |
  | RX        | RX     |
  ___

  **Fonte: Nycolas Abreu (2022).**

  Note-se que inputs sem um fio associado são fios que não tem uma conexão direta ao sistema, pois não são necessários.

Pista
----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Esse projeto também desenvolverá uma pista com um traçado pré definido, para que o carrinho possa executar seu trajeto de forma autônoma, preservando a sua funcionalidade anterior, junto com a funcionalidade de controle adicionada. Serão utilizados materiais de fácil acesso, como madeira, e uma fita para delimitar seus limites.


Referências
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

LUSCASOS. GitHub - luscasos/PI3-carro. Disponível em: <https://github.com/luscasos/PI3-carro?tab=readme-ov-file>. Acesso em: 15 nov. 2024. 

XTARKE. GitHub - xtarke/automated_buggy. Disponível em: <https://github.com/xtarke/automated_buggy>. Acesso em: 15 nov. 2024. 

ABREU, N. ESTUDO E DESENVOLVIMENTO DE PROGRAMAÇÕES LOW-CODE E NO-CODE PARA UM SISTEMA EMBARCADO. Disponível em: <https://sigaa.ifsc.edu.br/sigaa/verProducao?idProducao=2955250&key=bfcebe3e4ac7408faaafce6f45a562f1>. Acesso em: nov. 15DC. 

NYCOLASABREU. GitHub - NycolasAbreu/Buggy_TCC: Repositório para armazenar o projeto de tcc. Disponível em: <https://github.com/NycolasAbreu/Buggy_TCC>. Acesso em: 18 nov. 2024. 

RUISANTOS. How to Set an ESP32 Access Point (AP) for Web Server. Disponível em: https://randomnerdtutorials.com/esp32-access-point-ap-web-server/. Acesso em: 11 dez. 2024. 

