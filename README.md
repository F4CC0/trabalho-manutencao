# Trabalho de Manutenção de Software

**Disciplina:** Manutenção de Software
**Professor:** Rodrigo Funabashi
**Aluno:** Guilherme Facco Silva

Aplicação das seis premissas do Capítulo 2 (Código Limpo) do livro
[*Fundamentos de Manutenção de Software*](https://manutencaosoftware.org/) em um programa de
**classificação de risco de pacientes** (triagem de pronto-socorro), escrito em C/C++.

## O programa

O programa lê o nome do paciente, a frequência cardíaca, a saturação, a temperatura e se ele
está consciente. Cada sinal vital vale 0 (normal), 1 (alterado) ou 3 (crítico) pontos, e a
soma define a cor da classificação:

| Pontuação | Cor | Tempo máximo de espera |
|---|---|---|
| 6 ou mais, ou paciente inconsciente | VERMELHO (emergência) | atendimento imediato |
| 4 a 5 | LARANJA (muito urgente) | 10 min |
| 2 a 3 | AMARELO (urgente) | 60 min |
| 1 | VERDE (pouco urgente) | 120 min |
| 0 | AZUL (não urgente) | 240 min |

As faixas são uma simplificação para fins acadêmicos e não devem ser usadas em atendimento
real.

## Estrutura

| Pasta | Conteúdo |
|---|---|
| `antes/` | Código original, escrito com problemas de legibilidade de propósito. |
| `depois/` | O mesmo programa refatorado segundo as seis premissas, com o `.clang-format` (guia de estilo) e o `entradas.txt` (entradas de teste). |

A versão `antes` foi gerada com IA. A versão `depois` foi
refatorada pelo aluno, com orientação baseada no capítulo do livro.

## O que foi feito em cada premissa

| Premissa | Antes | Depois |
|---|---|---|
| **1. Verificadores de estilo e formatadores** | Indentação misturada, vários comandos por linha, includes sem uso e `using namespace std`. | Guia de estilo C++ do Google aplicado com o `clang-format`, e o compilador com `-Wall -Wextra` usado como verificador. |
| **2. Nomes legíveis** | `x`, `p`, `calc(a, b, c, d)`, `fc`, `sat`, `temp`, `op`, `r`. | `pontuacao`, `nome_paciente`, `frequencia_cardiaca`, `temperatura`, `continuar`, `cor`, e o booleano `esta_consciente`. |
| **3. Números mágicos** | 51, 90, 130, 96, 36.1, os cortes 6/4/2/1 e as cores representadas por 1 a 5. | Constantes `const` declaradas perto de onde são usadas e o `enum Cor { VERMELHO, ... }`. |
| **4. Linguagem ubíqua** | "doente", "pessoa" e "paciente" para a mesma coisa; "cor", "nível" e "risco" também. | Um termo só para cada conceito: paciente, sinais vitais, pontos, pontuação e cor. |
| **5. Funções coesas e desacopladas** | `calc` pontuava, classificava e alterava uma variável global; o `main` fazia tudo; havia `if` aninhado em 4 níveis e o mesmo `printf` repetido 5 vezes. | `pontuar_*`, `calcular_pontuacao`, `classificar_risco` (com retornos antecipados) e `mostrar_resultado`, sem nenhuma variável global. |
| **6. Separação dos fluxos de execução** | Uma escada de 4 `if` aninhados com os erros nos `else`, e o retorno do `scanf` ignorado. | `validar_dados_do_paciente` lança o erro com `throw`, e o `main` tem o caminho feliz no `try` e um único `catch`. |

### Resultados

| Verificação | Antes | Depois |
|---|---|---|
| Avisos de estilo (`clang-format`, estilo Google) | 263 | 0 |
| Avisos do compilador (`g++ -Wall -Wextra -O2`) | 6 | 0 |
| Variáveis globais | 2 | 0 |

- O comportamento foi preservado: com o mesmo `entradas.txt`, as duas versões classificam
  todos os pacientes igual. As únicas diferenças na saída são as mensagens alteradas de
  propósito na premissa 4.

## Como compilar e executar

```bash
g++ -Wall -Wextra antes/triagem.cpp -o triagem_antes
./triagem_antes
```

```bash
g++ -Wall -Wextra depois/triagem.cpp -o triagem_depois
./triagem_depois
```

Para comparar as duas versões com as entradas de teste (dentro de `depois/`):

```bash
g++ ../antes/triagem.cpp -o antes_bin && ./antes_bin < entradas.txt > saida_antes.txt
g++ triagem.cpp -o triagem && ./triagem < entradas.txt > saida_depois.txt
diff saida_antes.txt saida_depois.txt
```

Para verificar o estilo (dentro de `depois/`):

```bash
clang-format --dry-run --style=Google ../antes/triagem.cpp
clang-format --dry-run triagem.cpp
```
