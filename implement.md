**Implementação**
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

  A página web roda diretamente no microcontrolador e consiste nos controles do carrinho e na opção para armazenar os comandos anteriores, que podem vir a ser executados posteriormente.

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

  A opção de armazenamento dos controles é realizada através de cookies criados usando a linguagem javascript, inserida no html da página, e permitem a função de salvar inputs do usuário. 
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
  
      A opção de armazenamento dos controles será realizada através de cookies criados usando a linguagem javascript, inserida no html da página, e permitem a função de salvar inputs do usuário.  [...]
