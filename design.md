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

  **Fonte: Abreu (2024, p.54).**
  **Fonte: Abreu (2022, p.54).**

Software
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
- Página Web

  A página web roda diretamente no microcontrolador e consiste nos controles do carrinho e na opção para armazenar os comandos anteriores, que podem vir a ser executados posteriormente.

![PaginaWeb](https://github.com/user-attachments/assets/add8dadb-006c-4441-8cb5-9e02a48d5318)
  **Fonte: Elaboração própria (2024).**

  A opção de armazenamento dos controles é realizada através de cookies criados usando a linguagem javascript, inserida no html da página, e permitem a função de salvar inputs do usuário. 

Esquemático
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

O esquema de funcionamento do carrinho, de forma simplificada, pode ser visualizado da seguinte forma:

  ![buggy 3 drawio](https://github.com/user-attachments/assets/e01c69c3-2861-4bb0-a179-4fc3eb880ccf)

  **Fonte: Elaboração própria (2024).**

- Conexões do ESP

  Usando a placa shield, podemos conectar o ESP ao carrinho e usá-lo como substituto ao arduino. Segue abaixo o esquemático da placa shield:

  ![image](https://github.com/user-attachments/assets/0776919d-c4cd-43e0-8e31-d755baa2ed92)

   **Fonte: Abreu (2024, p.51).**

  ### Pinos analógicos

  **Fonte: Elaboração própria (2024).**
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

Módulo WiFi ESP32 Bluetooth. Disponível em: <https://www.byteflop.com.br/modulo-wifi-esp32-bluetooth>. 
NYCOLASABREU. GitHub - NycolasAbreu/Buggy_TCC: Repositório para armazenar o projeto de tcc. Disponível em: <https://github.com/NycolasAbreu/Buggy_TCC>. Acesso em: 18 nov. 2024. 
