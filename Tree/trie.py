class TrieNo:

    def __init__(self):
        self.filhos = {}
        self.final_da_palavra = False

    
class Trie:

    def __init__(self):
        self.raiz = TrieNo()

    def eh_caracter_valido(self, l):
        return 32 <= ord(l) <= 126

    def inserir(self, palavra):
        no = self.raiz

        for l in palavra:
            if not self.eh_caracter_valido(l):
                continue
            if l not in no.filhos:
                no.filhos[l] = TrieNo()
            no = no.filhos[l]

        no.final_da_palavra = True

    def busca(self, palavra):
        no = self.raiz

        for l in palavra:
            if not self.eh_caracter_valido(l):
                raise ValueError("Caractere inválido")
            if l not in no.filhos:
                return False
            no = no.filhos[l]
        return no.final_da_palavra

    def busca_com_prefixo(self, prefixo):
        no = self.raiz

        for l in prefixo:
            if not self.eh_caracter_valido(l):
                raise ValueError("Caractere inválido")
            if l not in no.filhos:
                return False
            no = no.filhos[l]
        return True
    
    def listar_com_prefixo(self, prefixo):
        def dfs(no, prefixo_atual, resultado):
            if no.final_da_palavra:
                resultado.append(prefixo_atual)  # Adiciona a palavra completa à lista
            for char, proximo_no in no.filhos.items():
                dfs(proximo_no, prefixo_atual + char, resultado)

        no = self.raiz
        resultado = []

        # Navega pela árvore até o final do prefixo
        for l in prefixo:
            if not self.eh_caracter_valido(l):
                raise ValueError(f"Caractere inválido '{l}' no prefixo.")
            if l not in no.filhos:
                return "Nenhuma senha encontrada com esse prefixo."  
            no = no.filhos[l]

        # Realiza uma busca em profundidade (DFS) para encontrar todas as palavras
        dfs(no, prefixo, resultado)

        return resultado

def carregar_senhas(trie, arquivo):
    try:
        with open(arquivo, 'r') as f:
            for linha in f:
                senha = linha.strip()  # Remove espaços em branco e quebras de linha
                if senha:
                    trie.inserir(senha)
        print("Todas as senhas foram inseridas na árvore Trie.")
    except Exception as e:
        print(f"Ocorreu um erro: {e}")



if __name__ == "__main__":

    trie = Trie()
    carregar_senhas(trie, 'rockyou-menor.txt')

    prefixo1 = input("")
    prefixo2 = input("")
    prefixo3 = input("")
    
    s1 = trie.listar_com_prefixo(prefixo1)
    s2 = trie.listar_com_prefixo(prefixo2)
    s3 = trie.listar_com_prefixo(prefixo3)

    for senha in s1:
        print(senha)
    for senha in s2:
        print(senha)
    for senha in s3:
        print(senha)

