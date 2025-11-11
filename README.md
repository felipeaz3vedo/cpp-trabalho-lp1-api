# CPP Trabalho LP1 – REST API para Restaurante

Este projeto é uma API REST escrita em **C++ (C++17)** usando o framework **[Drogon](https://github.com/drogonframework/drogon)**.  
O domínio é um sistema simples de restaurante, com:

- **Users**
  - Funcionários (`Employee`) – com cargos (`EmployeeRole`) e desconto especial
  - Clientes (`Customer`) – com pontos de fidelidade
- **Mesas** (`Table`)
- **Reservas** (`Reservation`)
- **Cardápio** (`MenuItem`)
- **Pedidos** (`Order`)
  - Itens do pedido (`OrderMenuItem`)
  - Cálculo de subtotal, desconto do usuário, taxa de pagamento e total
- **Pagamentos** (`PaymentMethod`, `CashPayment`, `CardPayment`)

Os dados são mantidos em **memória** (repositórios estáticos), sem banco de dados, para focar em orientação a objetos, regras de negócio e arquitetura em camadas:

- `controllers/` – controllers HTTP (Drogon)
- `services/` – regras de negócio
- `repositories/` – “persistência” em memória
- `models/` – entidades de domínio
- `shared/` – DTOs, helpers, enums e exceptions

## Requisitos

Para rodar usando Docker (recomendado):

- [Docker](https://www.docker.com/) instalado

Para rodar manualmente (sem Docker):

- Compilador C++17 (g++ / clang++)
- CMake ≥ 3.15
- Drogon e dependências instaladas (via `vcpkg` ou sistema)

## Como rodar o projeto com Docker

### 1. Clonar o repositório

```bash
git clone https://github.com/felipeaz3vedo/cpp-trabalho-lp1-api.git
```

### 2. Entrar no diretório do projeto

```bash
cd cpp-trabalho-lp1-api
```

### 3. Build da imagem

```bash
docker build -t cpp-trabalho-lp1-api .
```

### 4. Criar/rodar o container

```bash
docker run --rm -d -p 8080:8080 --name api cpp-trabalho-lp1-api
```

A API deve ficar acessível em: http://localhost:8080

## Como rodar o projeto localmente (sem Docker)

### 1. Clonar o repositório

```bash
git clone https://github.com/felipeaz3vedo/cpp-trabalho-lp1-api.git
```

### 2. Entrar no diretório do projeto

```bash
cd cpp-trabalho-lp1-api
```

### 3. Gerar build com CMake

```bash
mkdir -p build
cd build
cmake ..
cmake --build .
```

### 4. Rodar o binário

```bash
./cpp_trabalho_lp1_api
```
