// Trabalho de Manutencao - triagem do pronto socorro
// versão refatorada (limpa)
#include <stdio.h>

enum Cor { VERMELHO, LARANJA, AMARELO, VERDE, AZUL };

// Pontos de cada sinal vital
const int PONTOS_NORMAL = 0;
const int PONTOS_ALTERADO = 1;
const int PONTOS_CRITICO = 3;

int pontuar_frequencia_cardiaca(int frequencia_cardiaca) {
  const int FREQUENCIA_NORMAL_MINIMA = 51;
  const int FREQUENCIA_NORMAL_MAXIMA = 90;
  const int FREQUENCIA_ALTERADA_MINIMA = 41;
  const int FREQUENCIA_ALTERADA_MAXIMA = 130;

  if (frequencia_cardiaca >= FREQUENCIA_NORMAL_MINIMA &&
      frequencia_cardiaca <= FREQUENCIA_NORMAL_MAXIMA)
    return PONTOS_NORMAL;
  if (frequencia_cardiaca >= FREQUENCIA_ALTERADA_MINIMA &&
      frequencia_cardiaca <= FREQUENCIA_ALTERADA_MAXIMA)
    return PONTOS_ALTERADO;
  return PONTOS_CRITICO;
}

int pontuar_saturacao(double saturacao) {
  const double SATURACAO_NORMAL_MINIMA = 96;
  const double SATURACAO_ALTERADA_MINIMA = 92;

  if (saturacao >= SATURACAO_NORMAL_MINIMA) return PONTOS_NORMAL;
  if (saturacao >= SATURACAO_ALTERADA_MINIMA) return PONTOS_ALTERADO;
  return PONTOS_CRITICO;
}

int pontuar_temperatura(double temperatura) {
  const double TEMPERATURA_NORMAL_MINIMA = 36.1;
  const double TEMPERATURA_NORMAL_MAXIMA = 38.0;
  const double TEMPERATURA_ALTERADA_MINIMA = 35.1;
  const double TEMPERATURA_ALTERADA_MAXIMA = 39.0;

  if (temperatura >= TEMPERATURA_NORMAL_MINIMA &&
      temperatura <= TEMPERATURA_NORMAL_MAXIMA)
    return PONTOS_NORMAL;
  if (temperatura >= TEMPERATURA_ALTERADA_MINIMA &&
      temperatura <= TEMPERATURA_ALTERADA_MAXIMA)
    return PONTOS_ALTERADO;
  return PONTOS_CRITICO;
}

int calcular_pontuacao(int frequencia_cardiaca, double saturacao,
                       double temperatura) {
  return pontuar_frequencia_cardiaca(frequencia_cardiaca) +
         pontuar_saturacao(saturacao) + pontuar_temperatura(temperatura);
}

Cor classificar_risco(int pontuacao, bool esta_consciente) {
  const int PONTUACAO_MINIMA_VERMELHO = 6;
  const int PONTUACAO_MINIMA_LARANJA = 4;
  const int PONTUACAO_MINIMA_AMARELO = 2;
  const int PONTUACAO_MINIMA_VERDE = 1;

  // Paciente inconsciente e sempre emergencia, qualquer que seja a pontuacao
  if (!esta_consciente) return VERMELHO;
  if (pontuacao >= PONTUACAO_MINIMA_VERMELHO) return VERMELHO;
  if (pontuacao >= PONTUACAO_MINIMA_LARANJA) return LARANJA;
  if (pontuacao >= PONTUACAO_MINIMA_AMARELO) return AMARELO;
  if (pontuacao >= PONTUACAO_MINIMA_VERDE) return VERDE;
  return AZUL;
}

void mostrar_resultado(const char nome_paciente[], Cor cor, int pontuacao) {
  printf("Paciente: %s\n", nome_paciente);
  if (cor == VERMELHO)
    printf("Cor: VERMELHO - emergencia - atendimento imediato");
  else if (cor == LARANJA)
    printf("Cor: LARANJA - muito urgente - esperar no maximo 10 min");
  else if (cor == AMARELO)
    printf("Cor: AMARELO - urgente - esperar no maximo 60 min");
  else if (cor == VERDE)
    printf("Cor: VERDE - pouco urgente - esperar no maximo 120 min");
  else
    printf("Cor: AZUL - nao urgente - esperar no maximo 240 min");
  printf(" (pontuacao: %d)\n", pontuacao);
}

void validar_dados_do_paciente(int frequencia_cardiaca, double saturacao,
                               double temperatura, char resposta_consciente) {
  const int FREQUENCIA_MAXIMA_POSSIVEL = 300;
  const double SATURACAO_MAXIMA_POSSIVEL = 100;
  const double TEMPERATURA_MINIMA_POSSIVEL = 25;
  const double TEMPERATURA_MAXIMA_POSSIVEL = 45;

  if (!(frequencia_cardiaca > 0 &&
        frequencia_cardiaca <= FREQUENCIA_MAXIMA_POSSIVEL))
    throw "frequencia cardiaca invalida";
  if (!(saturacao > 0 && saturacao <= SATURACAO_MAXIMA_POSSIVEL))
    throw "saturacao invalida";
  if (!(temperatura >= TEMPERATURA_MINIMA_POSSIVEL &&
        temperatura <= TEMPERATURA_MAXIMA_POSSIVEL))
    throw "temperatura invalida";
  if (!(resposta_consciente == 's' || resposta_consciente == 'S' ||
        resposta_consciente == 'n' || resposta_consciente == 'N'))
    throw "consciencia invalida";
}

// Descarta o que sobrou da linha digitada (por exemplo, letras onde era numero)
void limpar_resto_da_linha() {
  int caractere = getchar();
  while (caractere != '\n' && caractere != EOF) caractere = getchar();
}

int main() {
  int continuar = 1;
  int frequencia_cardiaca;
  int pontuacao;
  char resposta_consciente;
  char nome_paciente[50];
  double saturacao, temperatura;
  Cor cor;

  while (continuar == 1) {
    printf("\n===== TRIAGEM =====\n");
    try {
      printf("Nome do paciente: ");
      if (scanf(" %49[^\n]", nome_paciente) != 1) throw "nome invalido";
      printf("Frequencia cardiaca (bpm): ");
      if (scanf("%d", &frequencia_cardiaca) != 1)
        throw "frequencia cardiaca invalida";
      printf("Saturacao (%%): ");
      if (scanf("%lf", &saturacao) != 1) throw "saturacao invalida";
      printf("Temperatura (C): ");
      if (scanf("%lf", &temperatura) != 1) throw "temperatura invalida";
      printf("Paciente consciente? (s/n): ");
      if (scanf(" %c", &resposta_consciente) != 1) throw "consciencia invalida";

      validar_dados_do_paciente(frequencia_cardiaca, saturacao, temperatura,
                                resposta_consciente);
      pontuacao =
          calcular_pontuacao(frequencia_cardiaca, saturacao, temperatura);
      bool esta_consciente =
          resposta_consciente == 's' || resposta_consciente == 'S';
      cor = classificar_risco(pontuacao, esta_consciente);
      mostrar_resultado(nome_paciente, cor, pontuacao);
    } catch (const char* erro) {
      printf("Erro: %s\n", erro);
      limpar_resto_da_linha();
    }

    printf("\nClassificar outro paciente? (1 - sim / 0 - nao): ");
    if (scanf("%d", &continuar) != 1) continuar = 0;
  }
  printf("Fim do programa\n");
  return 0;
}
