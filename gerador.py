import random

# PEDRO HENRIQUE DE SOUZA SILVESTRE -- ESTRUTURA DE DADOS 1 -- CIENCIA DA COMPUTAÇÃO - UEL 
# TESTE VSCODE GITHUB

"""
  > referencias: 
    - https://algs4.cs.princeton.edu/43mst/
    - Felipe Pierotti ( Ciência da Computação - UFSC)
"""

class Grafo: 
  def __init__(self, vertices):
    self.vertices = vertices
    self.arestas = []

  def adicionar_aresta(self, u, v):
    self.arestas.append((u, v))

  def encontrar_pai(self, pai, i):
    if pai[i] == i:
      return i
    return self.encontrar_pai(pai, pai[i])

  def uniao(self, pai, nivel, x, y):
    raiz_x = self.encontrar_pai(pai, x)
    raiz_y = self.encontrar_pai(pai, y)
    if nivel[raiz_x] < nivel[raiz_y]:
      pai[raiz_x] = raiz_y
    elif nivel[raiz_x] > nivel[raiz_y]:
      pai[raiz_y] = raiz_x
    else:
      pai[raiz_y] = raiz_x
      nivel[raiz_x] += 1

  def kruskal(self):
    arvore_minima_geradora = set()
    pai = {}
    nivel = {}

    for v in self.vertices:
      pai[v] = v
      nivel[v] = 0

    primeira = self.arestas[0]
    ultima = self.arestas[-1]
    arvore_minima_geradora.add(primeira)
    arvore_minima_geradora.add(ultima)
    self.uniao(pai, nivel, primeira[0], primeira[1])
    self.uniao(pai, nivel, ultima[0], ultima[1])

    random.shuffle(self.arestas) 
    for aresta in self.arestas:
      u, v = aresta
      raiz_u = self.encontrar_pai(pai, u)
      raiz_v = self.encontrar_pai(pai, v)
      if raiz_u != raiz_v: 
        arvore_minima_geradora.add(aresta)
        self.uniao(pai, nivel, raiz_u, raiz_v)
    return arvore_minima_geradora

tamanho = random.randint(4,10)
largura = tamanho
altura = tamanho


vertices = [(x, y) for x in range(largura) 
                  for y in range(altura)]

g = Grafo(vertices)

for v in vertices:
  if v[0] < tamanho-1:
    g.adicionar_aresta(v, (v[0]+1, v[1]))
  if v[1] < tamanho-1:
    g.adicionar_aresta(v, (v[0], v[1]+1))

arvore_minima_geradora = g.kruskal()

matriz = [[1 for _ in range((tamanho*2)+1)] for _ in range((tamanho*2)+1)]

for aresta in arvore_minima_geradora:
  u, v = aresta

  xu = u[0]*2 + 1
  yu = u[1]*2 + 1

  xv = v[0]*2 + 1
  yv = v[1]*2 + 1

  if u[0] == v[0]:
    matriz[xu][yu] = 0
    matriz[xu][yu + 1] = 0
    matriz[xv][yv] = 0
  else:
    matriz[xu][yu] = 0
    matriz[xu + 1][yu] = 0
    matriz[xv][yv] = 0


coordenadas_internas = [(x, y) for x in range(1, tamanho * 2, 2) for y in range(1, tamanho * 2, 2)]
coordenada_inicio = random.choice(coordenadas_internas)
coordenadas_internas.remove(coordenada_inicio)
coordenada_destino = random.choice(coordenadas_internas)

matriz[coordenada_inicio[0]][coordenada_inicio[1]] = 2  
matriz[coordenada_destino[0]][coordenada_destino[1]] = 3


for i in range((tamanho*2)+1):
  for j in range((tamanho*2)+1):
    print(matriz[i][j], end=" ")
  print()

  
with open("labirinto.txt", "w") as arquivo:
    tam_matriz = str(len(matriz))
    arquivo.write(tam_matriz + "\n")
    for linha in matriz:
        linha_texto = "".join(map(str, linha)) 
        arquivo.write(linha_texto + "\n") 