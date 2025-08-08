# RitmosUrbanos-IoT-Data-Science
Projeto com um Microcontrolador ESP32 coletando dados da rua como luminosidade, temperatura, prressão atmosférica, umidade, movvimento e som, para poder cruzar essas informações da via urbana.

Desenvolvimento do projeto Ritmos Urbanos

Relatório do "Dia 1" 05/08/2025:

•	Validação da Ideia: Comecei com a ideia de usar os dois sensores de movimento PIR para detectar a direção do tráfego de pedestres.

•	Integração e Código do ESP32: Testado com sucesso todos os sensores:
   o	BH1750 (Luminosidade): Testada a leitura inicial.
   o	BME280 (Pressão, Temperatura e Umidade): Adicionada a leitura de dados ambientais.
   o	MAX4466 (Microfone): Integrado o sensor de ruído.
   o	HC-SR505 (PIRs): Implementada a lógica para detectar a direção do movimento com dois sensores.
   
•	Resolução de Problemas: Solucionado um erro de upload ao identificar que a fonte de alimentação do ESP32 estava sobrecarregada pois estava utilizando a porta USB-c para alimentar todo o projeto. A solução de usar uma fonte externa foi perfeita resolvendo o problema.

•	Conexão com a Nuvem: Configurado o ESP32 para se conectar à rede Wi-Fi.

•	Backend e Armazenamento (Etapa 1): Foi criada uma API com o Google Apps Script e uma planilha no Google Sheets para receber os dados, validando o sistema de ponta a ponta.

•	Análise sobre Bancos de Dados: Pesquisada a importância de usar um banco de dados de verdade, como o PostgreSQL com a extensão TimescaleDB, em vez da planilha, e tomei a decisão estratégica de usar a nuvem para hospedar o servidor, o que tornará o portfólio muito mais robusto e profissional.

Relatório do “Dia 2” 07/08/2025: 

1. Configuração da Infraestrutura na Nuvem (Google Cloud Platform - GCP)
   •	Criação da Máquina Virtual (VM): Iniciado o projeto com a criação de uma instância de máquina virtual na GCP.
   •	Configuração de Rede: Configuradas as regras de firewall para permitir o tráfego de entrada nas portas 80 (HTTP), 443 (HTTPS) e, mais importante, na porta 5000 para a API, garantindo que o ESP32 pudesse se comunicar com o servidor.
   •	Sistema Operacional: A VM foi provisionada com o sistema operacional Ubuntu 24.04 LTS, uma base robusta para o servidor.

2. Configuração do Banco de Dados PostgreSQL e TimescaleDB
   •	Instalação do PostgreSQL: No terminal do servidor, foi instalado o banco de dados PostgreSQL.
   •	Criação do Banco de Dados: Criado o banco de dados chamado monitoramento_iot e um usuário específico (iot_user) com uma senha para a API se conectar.
   •	TimescaleDB: Adicionamos o plugin TimescaleDB para otimizar o banco de dados para séries temporais, o que é ideal para dados de sensores.
   •	Criação da Tabela: Criada a tabela dados_sensores com colunas para timestamp e os dados de todos os seus sensores.

3. Desenvolvimento e Ajustes da API Python
   •	Ambiente Virtual: Criado e ativado um ambiente virtual em Python (venv) para gerenciar as dependências do projeto de forma organizada.
   •	API Flask: Desenvolvida a API em Flask com uma rota /data que recebe os dados do ESP32 via método POST e os insere no banco de dados.
   •	Solução de Problemas (Troubleshooting): Enfrentados e resolvidos vários desafios, incluindo:
      o	Erros de sintaxe no arquivo app.py.
      o	Erros de conexão entre a API e o banco de dados, corrigindo o host de IP externo para localhost.
      o	Garantia que a API rodasse em segundo plano com o tmux para não ser interrompida.
4. Verificação e Validação Final
   •	Conectividade do ESP32: Verificado que o ESP32 estava se conectando ao Wi-Fi e à API, exibindo mensagens de sucesso (HTTP Response code: 200) no Monitor Serial.
   •	Dados no Banco de Dados: Confirmado, através de uma consulta SQL, que os dados dos sensores estavam sendo inseridos com sucesso na tabela dados_sensores.
   •	Ajuste do Horário: Ajustado o comando de consulta para exibir o timestamp no fuso horário local de Mesquita, RJ, resolvendo a defasagem de 3 horas para futuras análises de dados.

Este relatório completo demonstra que o projeto está funcionando perfeitamente, com uma arquitetura de ponta a ponta robusta e bem configurada, desde o hardware até o banco de dados na nuvem.
Montagem do ESP32 na garagem. Os sensores de movimento e som, foram colocados no muro externo para captar a passagem das pessoas e os sons da rua. O sensor de luminosidade está na garagem perto da telha apontado para a rua de forma que capte a luminosidade. O sensor de temperatura, umidade e pressão está posicionado perto do telhado de forma a coletar esses dados.

Relatório do “Dia 3” 08/08/2025:

Transformado o projeto de um sistema de coleta de dados em uma plataforma completa de visualização.
Dashboard Web
1.	Objetivo do Dia: O principal objetivo foi criar uma dashboard web, acessível pelo navegador, para visualizar os dados dos sensores em tempo real, agregando um valor significativo ao projeto.
2.	Desenvolvimento do Frontend:
   o	Criação da Estrutura: Criada uma pasta templates no seu servidor para hospedar as páginas web.
   o	Código da Dashboard: Foi criada uma página HTML completa (index.html) com CSS para o estilo e JavaScript para a lógica de atualização.
3.	Expansão da API Python:
   o	Novos Endpoints: Modificado o arquivo app.py para criar dois novos endpoints:
      	Uma rota principal (/) que serve a página index.html para os visitantes.
      	Uma rota /latest que consulta o banco de dados e retorna os dados mais recentes em formato JSON, permitindo que a página se atualize em tempo real.
4.	Integração e Teste Final:
   o	Reinicialização da API: Reiniciada a API Flask para que ela pudesse carregar o novo código.
   o	Verificação Final: Acessado o IP do seu servidor no navegador e confirmamos que a dashboard estava funcionando perfeitamente, exibindo os dados em tempo real e se atualizando a cada 5 segundos.

Tempo do projeto até a implantação: 3 dias

Custo do projeto na data de 08/08/2025

Esp32 Dev Kit – R$ 34,00

Placa de desenvolvimento ESP32 – R$  18,35

Semsor Bme280 5V Pressão, Temperatura e Umidade – R$ 42,00

Módulo Sensor de Luz Luminosidade Bh1750 – R$ 21,04

Mini Sensor de Movimento Presença PIR HC-sr505 – R$ 26,31

Módulo Microfone Max4466 Ganho Ajustável – R$ 22,00

Mangueira Crista para proteção de sensores – R$ 4,50

Total: R$ 168,20 (valor aproximado, sem incluir cabos, fixação e mão de obra)


