Design de Funcionamento
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


Hardware
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

- **Microcontrolador ESP 32**

  O ESP 32 é um microcontrolador multifuncional e eficiente em termos de custo e energia, com suporte a Wi-Fi, o que o torna ideal para projetos de automação e sistemas conectados. 
Com isso em mente, esse microcontrolador foi escolhido por seu preço, disponibilidade e propriedades de conectividade Wi-Fi, que serão utilizadas para captar e transmitir as informações recebidas pelos controles na página Web para o carrinho. 

  ![EspImage](https://github.com/user-attachments/assets/4fd17249-a83c-44d2-b61b-db54e8352292)

  **Fonte: Byteflop (2024).**

- **Placa de Interface**

  De forma a usar o microcontrolador ESP 32 com o carrinho precisamos de uma placa de interface. Visto que o carrinho possui instruções em software baseadas em Arduino, a placa de interface fica responsável por traduzir as chamadas do software compatíveis com
o Arduino para um formato que o esp32 seja capaz de executar.

  ![PlacadeInterfaceImage2](https://github.com/user-attachments/assets/75446d12-d3c9-4056-aed6-f27858e13b1e)

  **Fonte: Abreu (2024, p.54).**

Software
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
- Página web
  
  A pagina web consiste nos controles do carrinho e na opção para armazenar os comandos anteriores , que podem vir a ser executados posteriormente.

![PaginaWeb](https://github.com/user-attachments/assets/add8dadb-006c-4441-8cb5-9e02a48d5318)
**Fonte: Elaboração própria (2024).**

  A opção de armazenamento dos controles é realizada através de cookies criados usando a linguagem javascript, inserida no html da página, e permitem a função de salvar inputs do usuário. 

Esquemático
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


Referências
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

LUSCASOS. GitHub - luscasos/PI3-carro. Disponível em: <https://github.com/luscasos/PI3-carro?tab=readme-ov-file>. Acesso em: 15 nov. 2024. 

XTARKE. GitHub - xtarke/automated_buggy. Disponível em: <https://github.com/xtarke/automated_buggy>. Acesso em: 15 nov. 2024. 

ABREU, N. ESTUDO E DESENVOLVIMENTO DE PROGRAMAÇÕES LOW-CODE E NO-CODE PARA UM SISTEMA EMBARCADO. Disponível em: <https://sigaa.ifsc.edu.br/sigaa/verProducao?idProducao=2955250&key=bfcebe3e4ac7408faaafce6f45a562f1>. Acesso em: nov. 15DC. 

Módulo WiFi ESP32 Bluetooth. Disponível em: <https://www.byteflop.com.br/modulo-wifi-esp32-bluetooth>. 