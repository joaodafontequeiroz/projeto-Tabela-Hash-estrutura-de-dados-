# HashGuard System: Tabela Hash com Sondagem Linear

Este é um projeto acadêmico em C que implementa um sistema simples de cadastro e login de usuários. O objetivo principal é demonstrar o funcionamento de uma **Tabela Hash com Endereçamento Aberto**, utilizando a técnica de **Sondagem Linear** para o tratamento de colisões.

---

## 🚀 Conceito Implementado

A estrutura de dados central é uma Tabela Hash que armazena `Usuarios`.

* **Endereçamento Aberto (Sondagem Linear):** Diferente de implementações com listas ligadas (encadeamento separado), este projeto resolve colisões procurando o próximo "espaço aberto" (`index + 1`, `index + 2`, ...) no próprio array da tabela.
* **Marcador de Remoção (`ITEM_REMOVIDO`):** Para que a busca não falhe após a remoção de um item, um ponteiro global especial (`ITEM_REMOVIDO`) é usado para "tapar o buraco". Isso sinaliza para a função `buscaHash` que ela deve continuar procurando, e para a `insereHash` que ela pode ocupar aquele espaço.
* **Hashing de Senhas:** As senhas não são armazenadas em texto puro. Elas são convertidas em um `unsigned long` usando a função de hash `djb2` (`funcaoValorString`) e apenas este hash é armazenado na estrutura.

---

## ⚙️ Funcionalidades

O programa `main.c` fornece uma interface de console interativa com as seguintes opções:

1.  **Cadastrar:** Permite inserir um novo usuário e senha. O sistema verifica se o `username` (chave) já existe para evitar duplicatas.
2.  **Login:** Verifica se o `username` existe e, em caso afirmativo, se o hash da senha digitada corresponde ao hash armazenado.
3.  **Remover:** Remove um usuário da tabela, marcando seu local com `ITEM_REMOVIDO`.
4.  **Ver Tabela:** Imprime o estado atual completo da tabela hash no console, mostrando quais índices estão `LIVRE`, `X (REMOVIDO)` ou `Ocupados`.
5.  **Sair:** Encerra o programa e libera toda a memória alocada (`free`) pela tabela e seus elementos.

---

## 🗂️ Estrutura de Arquivos

* `tabelaHash.h`: Arquivo de cabeçalho (header) que define as estruturas (`Usuario`, `Hash`) e os protótipos de todas as funções.
* `tabelaHash.c`: Arquivo de implementação que contém a lógica de todas as funções da tabela hash (criar, liberar, inserir, buscar, remover, etc.).
* `main.c`: O programa principal que fornece a interface de menu para o usuário e testa a tabela hash.

---

## 🔧 Como Compilar e Executar

Este código pode ser compilado usando `gcc` (ou qualquer compilador C padrão).

1.  Abra seu terminal na pasta onde os arquivos estão localizados.
2.  Execute o comando de compilação:

    ```bash
    gcc main.c tabelaHash.c -o hash_system
    ```

3.  Execute o programa compilado:

    * No Linux/macOS:
        ```bash
        ./hash_system
        ```
    * No Windows:
        ```bash
        hash_system.exe
        ```

---

## 🎓 Integrantes

* Marcelo Caldas
* Heitor Meira
* Joao da Fonte Queiroz
