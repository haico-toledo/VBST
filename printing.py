import pygame
import sys

# Configurações do Pygame
LARGURA, ALTURA = 1000, 700
COR_FUNDO = (30, 30, 30)
COR_NO = (70, 130, 180)
COR_TEXTO = (255, 255, 255)
COR_LINHA = (200, 200, 200)

class NoArvore:
    def __init__(self, valor, esq=None, dir=None):
        self.valor = valor
        self.esq = esq
        self.dir = dir

def parse_bst_string(s):
    if not s:
        return None

    tokens = []
    i = 0
    while i < len(s):
        if s[i] in '()':
            tokens.append(s[i])
            i += 1
        elif s[i].isspace():
            i += 1
        else:
            j = i
            while j < len(s) and not s[j].isspace() and s[j] not in '()':
                j += 1
            tokens.append(s[i:j])
            i = j

    def parse_tokens(index):
        if index >= len(tokens):
            return None, index

        if tokens[index] == '(':
            index += 1
            if index < len(tokens) and tokens[index] == ')':
                return None, index + 1

            valor = tokens[index]
            index += 1

            esq, index = parse_tokens(index)
            dir, index = parse_tokens(index)

            if index < len(tokens) and tokens[index] == ')':
                index += 1

            return NoArvore(valor, esq, dir), index

        return None, index

    raiz, _ = parse_tokens(0)
    return raiz

def calcular_altura(no):
    if no is None:
        return 0
    return 1 + max(calcular_altura(no.esq), calcular_altura(no.dir))

def desenhar_arvore(surface, no, x, y, dx, dy, fonte, escala):
    if no is None or no.valor == "" or no.valor == "()":
        return

    raio_no = int(20 * escala)
    largura_linha = max(1, int(2 * escala))

    # Desenha a subárvore esquerda
    if no.esq and no.esq.valor not in ("", "()"):
        prox_x = x - dx
        prox_y = y + dy
        pygame.draw.line(surface, COR_LINHA, (x, y), (prox_x, prox_y), largura_linha)
        desenhar_arvore(surface, no.esq, prox_x, prox_y, dx * 0.55, dy, fonte, escala)

    # Desenha a subárvore direita
    if no.dir and no.dir.valor not in ("", "()"):
        prox_x = x + dx
        prox_y = y + dy
        pygame.draw.line(surface, COR_LINHA, (x, y), (prox_x, prox_y), largura_linha)
        desenhar_arvore(surface, no.dir, prox_x, prox_y, dx * 0.55, dy, fonte, escala)

    # Desenha o nó atual
    pygame.draw.circle(surface, COR_NO, (int(x), int(y)), raio_no)
    
    # Redimensiona a fonte com base no zoom
    tamanho_fonte = max(10, int(16 * escala))
    fonte_zoom = pygame.font.SysFont("Arial", tamanho_fonte, bold=True)
    texto_surface = fonte_zoom.render(str(no.valor), True, COR_TEXTO)
    texto_rect = texto_surface.get_rect(center=(int(x), int(y)))
    surface.blit(texto_surface, texto_rect)

def main():
    pygame.init()
    tela = pygame.display.set_mode((LARGURA, ALTURA))
    pygame.display.set_caption("Visualizador de BST - (Scroll para Zoom | Botão Esquerdo para Mover)")
    fonte = pygame.font.SysFont("Arial", 16, bold=True)

    try:
        with open("outputVBST", "r", encoding="utf-8") as arquivo:
            string_arvore = arquivo.read()
    except FileNotFoundError:
        print("Erro: Arquivo 'outputVBST' não encontrado.")
        sys.exit(1)

    raiz = parse_bst_string(string_arvore)
    altura = calcular_altura(raiz)

    # Variáveis para Controle de Câmera (Pan & Zoom)
    offset_x = LARGURA // 2
    offset_y = 60
    escala = 1.0
    arrastando = False
    inicio_drag = (0, 0)

    # Ajusta o espaçamento inicial de acordo com a altura
    dx_inicial = min(LARGURA // 3, 40 * (2 ** (min(altura, 5) - 1)))
    dy_inicial = min(80, (ALTURA - 100) // max(altura, 1))

    rodando = True
    while rodando:
        for evento in pygame.event.get():
            if evento.type == pygame.QUIT:
                rodando = False

            # Zoom com a roda do mouse
            elif evento.type == pygame.MOUSEBUTTONDOWN:
                if evento.button == 4:  # Scroll Up
                    escala = min(escala * 1.1, 3.0)
                elif evento.button == 5:  # Scroll Down
                    escala = max(escala / 1.1, 0.3)
                elif evento.button == 1:  # Botão Esquerdo (Drag)
                    arrastando = True
                    inicio_drag = evento.pos

            elif evento.type == pygame.MOUSEBUTTONUP:
                if evento.button == 1:
                    arrastando = False

            elif evento.type == pygame.MOUSEMOTION:
                if arrastando:
                    dx_mouse = evento.pos[0] - inicio_drag[0]
                    dy_mouse = evento.pos[1] - inicio_drag[1]
                    offset_x += dx_mouse
                    offset_y += dy_mouse
                    inicio_drag = evento.pos

        tela.fill(COR_FUNDO)
        if raiz:
            desenhar_arvore(
                tela, 
                raiz, 
                offset_x, 
                offset_y, 
                dx_inicial * escala, 
                dy_inicial * escala, 
                fonte, 
                escala
            )
        
        pygame.display.flip()

    pygame.quit()

if __name__ == "__main__":
    main()