# Backend do Dailyhub (WIP)

- Servidor feito em C++ com CrownCpp.
- PostgreSQL como banco de dados.
- Docker para subir as aplicações, configuradas pelo Docker-Compose.
- Build feita pelo CMake.

## Features

### Core

- [x] Conexão com PostgreSQL.
- [x] Servidor CrownCpp.
- [x] Request cURL.
- [x] Criação do banco de dados usando PostgreSQL, com as Tabelas users/finance/kanban/blog/news.
- [x] Automação usando Pipeline (CI/CD) Github Actions.

### Feature

- [ ] Sistema de usuarios
  - Login / Registro

- [ ] Sistema do kanban
  - criação de tarefas
  - deletar tarefas
  - atualizar tarefas.

- [ ] Sistema de finanças
  - conversor de moedas
  - adcionar cobrança/ganho
  - editar cobrança/ganho
  - deletar cobrança/ganho
  - filtrar por data cobrança/ganho

- [ ] Sistema de Jornal
  - Temperatura Atual
  - Ultimas Noticias
  - Messagem boa/insentivo
  - Horoscopo

- [ ] Sistema blog
  - Criar post
  - Ver últimos posts

O servidor do Dailyhub está em Desenvolvimento.
