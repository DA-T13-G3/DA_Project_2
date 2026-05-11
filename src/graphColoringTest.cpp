//
// Created by gustavobastos on 28/04/26.
//
//
// Created by gustavobastos on 27/04/26.
//
#include "graph.h"
#include "graphColoring.h"
#include <cstdio>

void test1() {
    // 1. Grafo Bipartido / Estrela (Esperado: 2 cores)
    Graph<int> g;
    for(int i = 0; i < 5; i++) {
        g.addVertex(i);
    }
    for(int i = 1; i < 5; i++) {
        g.addEdge(0, i, 0);
        g.addEdge(i, 0, 0);
    }
    int expected = 2;
    int result = graphColoring(&g);
    printf("%-30s - Esperado: %d | Resultado: %-2d   [%s]\n", "Test  1 (Estrela/Bipartido)", expected, result, result == expected ? "TEST PASSED" : "TEST FAILED");
}

void test2() {
    // 2. Grafo Ciclo Ímpar (Esperado: 3 cores)
    Graph<int> g;
    for(int i = 0; i < 5; i++) {
        g.addVertex(i);
    }
    g.addEdge(0, 1, 0); g.addEdge(1, 0, 0);
    g.addEdge(1, 2, 0); g.addEdge(2, 1, 0);
    g.addEdge(2, 3, 0); g.addEdge(3, 2, 0);
    g.addEdge(3, 4, 0); g.addEdge(4, 3, 0);
    g.addEdge(4, 0, 0); g.addEdge(0, 4, 0);
    int expected = 3;
    int result = graphColoring(&g);
    printf("%-30s - Esperado: %d | Resultado: %-2d   [%s]\n", "Test  2 (Ciclo Impar)", expected, result, result == expected ? "TEST PASSED" : "TEST FAILED");
}

void test3() {
    // 3. Grafo Totalmente Desconexo (Esperado: 1 cor)
    Graph<int> g;
    for(int i = 0; i < 6; i++) {
        g.addVertex(i);
    }
    // Nenhuma aresta adicionada
    int expected = 1;
    int result = graphColoring(&g);
    printf("%-30s - Esperado: %d | Resultado: %-2d   [%s]\n", "Test  3 (Totalmente Solto)", expected, result, result == expected ? "TEST PASSED" : "TEST FAILED");
}

void test4() {
    // 4. Grafo com Componentes Separados (Esperado: 2 cores)
    Graph<int> g;
    for(int i = 0; i < 4; i++) {
        g.addVertex(i);
    }
    // Componente 1
    g.addEdge(0, 1, 0); g.addEdge(1, 0, 0);
    // Componente 2
    g.addEdge(2, 3, 0); g.addEdge(3, 2, 0);
    int expected = 2;
    int result = graphColoring(&g);
    printf("%-30s - Esperado: %d | Resultado: %-2d   [%s]\n", "Test  4 (Comp. Separados)", expected, result, result == expected ? "TEST PASSED" : "TEST FAILED");
}

void test5() {
    // 5. Grafo Completo (Esperado: 4 cores para 4 vértices)
    Graph<int> g;
    int num_vertices = 4;
    for(int i = 0; i < num_vertices; i++) {
        g.addVertex(i);
    }
    for(int i = 0; i < num_vertices; i++) {
        for(int j = 0; j < num_vertices; j++) {
            if(i != j) {
                g.addEdge(i, j, 0);
            }
        }
    }
    int expected = 4;
    int result = graphColoring(&g);
    printf("%-30s - Esperado: %d | Resultado: %-2d   [%s]\n", "Test  5 (Grafo Completo)", expected, result, result == expected ? "TEST PASSED" : "TEST FAILED");
}

void test6() {
    // 6. Grafo Ciclo Par (Esperado: 2 cores)
    Graph<int> g;
    for(int i = 0; i < 4; i++) g.addVertex(i);

    g.addEdge(0, 1, 0); g.addEdge(1, 0, 0);
    g.addEdge(1, 2, 0); g.addEdge(2, 1, 0);
    g.addEdge(2, 3, 0); g.addEdge(3, 2, 0);
    g.addEdge(3, 0, 0); g.addEdge(0, 3, 0);

    int expected = 2;
    int result = graphColoring(&g);
    printf("%-30s - Esperado: %d | Resultado: %-2d   [%s]\n", "Test  6 (Ciclo Par)", expected, result, result == expected ? "TEST PASSED" : "TEST FAILED");
}

void test7() {
    // 7. Grafo Arvore Binaria (Esperado: 2 cores)
    Graph<int> g;
    for(int i = 0; i < 7; i++) g.addVertex(i);

    // Raiz (0) liga aos filhos (1 e 2)
    g.addEdge(0, 1, 0); g.addEdge(1, 0, 0);
    g.addEdge(0, 2, 0); g.addEdge(2, 0, 0);
    // Filho 1 liga a 3 e 4
    g.addEdge(1, 3, 0); g.addEdge(3, 1, 0);
    g.addEdge(1, 4, 0); g.addEdge(4, 1, 0);
    // Filho 2 liga a 5 e 6
    g.addEdge(2, 5, 0); g.addEdge(5, 2, 0);
    g.addEdge(2, 6, 0); g.addEdge(6, 2, 0);

    int expected = 2;
    int result = graphColoring(&g);
    printf("%-30s - Esperado: %d | Resultado: %-2d   [%s]\n", "Test  7 (Arvore)", expected, result, result == expected ? "TEST PASSED" : "TEST FAILED");
}

void test8() {
    // 8. Grafo Roda c/ ciclo impar (Esperado: 4 cores)
    Graph<int> g;
    for(int i = 0; i < 6; i++) g.addVertex(i);

    // Centro liga a todos
    for(int i = 1; i <= 5; i++) {
        g.addEdge(0, i, 0); g.addEdge(i, 0, 0);
    }
    // Ciclo externo
    g.addEdge(1, 2, 0); g.addEdge(2, 1, 0);
    g.addEdge(2, 3, 0); g.addEdge(3, 2, 0);
    g.addEdge(3, 4, 0); g.addEdge(4, 3, 0);
    g.addEdge(4, 5, 0); g.addEdge(5, 4, 0);
    g.addEdge(5, 1, 0); g.addEdge(1, 5, 0);

    int expected = 4;
    int result = graphColoring(&g);
    printf("%-30s - Esperado: %d | Resultado: %-2d   [%s]\n", "Test  8 (Grafo Roda)", expected, result, result == expected ? "TEST PASSED" : "TEST FAILED");
}

void test9() {
    // 9. Grafo Grelha 3x3 (Esperado: 2 cores)
    Graph<int> g;
    for(int i = 0; i < 9; i++) g.addVertex(i);

    // Conexoes Horizontais
    g.addEdge(0, 1, 0); g.addEdge(1, 0, 0); g.addEdge(1, 2, 0); g.addEdge(2, 1, 0);
    g.addEdge(3, 4, 0); g.addEdge(4, 3, 0); g.addEdge(4, 5, 0); g.addEdge(5, 4, 0);
    g.addEdge(6, 7, 0); g.addEdge(7, 6, 0); g.addEdge(7, 8, 0); g.addEdge(8, 7, 0);
    // Conexoes Verticais
    g.addEdge(0, 3, 0); g.addEdge(3, 0, 0); g.addEdge(3, 6, 0); g.addEdge(6, 3, 0);
    g.addEdge(1, 4, 0); g.addEdge(4, 1, 0); g.addEdge(4, 7, 0); g.addEdge(7, 4, 0);
    g.addEdge(2, 5, 0); g.addEdge(5, 2, 0); g.addEdge(5, 8, 0); g.addEdge(8, 5, 0);

    int expected = 2;
    int result = graphColoring(&g);
    printf("%-30s - Esperado: %d | Resultado: %-2d   [%s]\n", "Test  9 (Grelha 3x3)", expected, result, result == expected ? "TEST PASSED" : "TEST FAILED");
}

void test10() {
    // 10. Grafo Caminho / Linha (Esperado: 2 cores)
    Graph<int> g;
    for(int i = 0; i < 5; i++) g.addVertex(i);

    for(int i = 0; i < 4; i++) {
        g.addEdge(i, i+1, 0);
        g.addEdge(i+1, i, 0);
    }

    int expected = 2;
    int result = graphColoring(&g);
    printf("%-30s - Esperado: %d | Resultado: %-2d   [%s]\n", "Test 10 (Caminho/Linha)", expected, result, result == expected ? "TEST PASSED" : "TEST FAILED");
}

void test11() {
    // 11. Grafo de Petersen (Esperado: 3 cores)
    Graph<int> g;
    for(int i = 0; i < 10; i++) g.addVertex(i);

    // Pentagono exterior (0 a 4)
    g.addEdge(0, 1, 0); g.addEdge(1, 0, 0); g.addEdge(1, 2, 0); g.addEdge(2, 1, 0);
    g.addEdge(2, 3, 0); g.addEdge(3, 2, 0); g.addEdge(3, 4, 0); g.addEdge(4, 3, 0);
    g.addEdge(4, 0, 0); g.addEdge(0, 4, 0);
    // Estrela interior (5 a 9)
    g.addEdge(5, 7, 0); g.addEdge(7, 5, 0); g.addEdge(7, 9, 0); g.addEdge(9, 7, 0);
    g.addEdge(9, 6, 0); g.addEdge(6, 9, 0); g.addEdge(6, 8, 0); g.addEdge(8, 6, 0);
    g.addEdge(8, 5, 0); g.addEdge(5, 8, 0);
    // Ligar exterior ao interior
    g.addEdge(0, 5, 0); g.addEdge(5, 0, 0); g.addEdge(1, 6, 0); g.addEdge(6, 1, 0);
    g.addEdge(2, 7, 0); g.addEdge(7, 2, 0); g.addEdge(3, 8, 0); g.addEdge(8, 3, 0);
    g.addEdge(4, 9, 0); g.addEdge(9, 4, 0);

    int expected = 3;
    int result = graphColoring(&g);
    printf("%-30s - Esperado: %d | Resultado: %-2d   [%s]\n", "Test 11 (Grafo Petersen)", expected, result, result == expected ? "TEST PASSED" : "TEST FAILED");
}

void test12() {
    // 12. Caso Extremo: Apenas 1 vertice (Esperado: 1 cor)
    Graph<int> g;
    g.addVertex(0);

    int expected = 1;
    int result = graphColoring(&g);
    printf("%-30s - Esperado: %d | Resultado: %-2d   [%s]\n", "Test 12 (So 1 Vertice)", expected, result, result == expected ? "TEST PASSED" : "TEST FAILED");
}

void test13() {
    // 13. Grafo Bipartido Completo K_3,3 (Esperado: 2 cores)
    Graph<int> g;
    for(int i = 0; i < 6; i++) g.addVertex(i);
    for(int i = 0; i < 3; i++) {
        for(int j = 3; j < 6; j++) {
            g.addEdge(i, j, 0); g.addEdge(j, i, 0);
        }
    }
    int expected = 2;
    int result = graphColoring(&g);
    printf("%-30s - Esperado: %d | Resultado: %-2d   [%s]\n", "Test 13 (Bipartido K_3,3)", expected, result, result == expected ? "TEST PASSED" : "TEST FAILED");
}

void test14() {
    // 14. Grafo Prisma Triangular (Esperado: 3 cores)
    Graph<int> g;
    for(int i = 0; i < 6; i++) g.addVertex(i);
    // Triangulo 1 (0, 1, 2)
    g.addEdge(0, 1, 0); g.addEdge(1, 0, 0);
    g.addEdge(1, 2, 0); g.addEdge(2, 1, 0);
    g.addEdge(2, 0, 0); g.addEdge(0, 2, 0);
    // Triangulo 2 (3, 4, 5)
    g.addEdge(3, 4, 0); g.addEdge(4, 3, 0);
    g.addEdge(4, 5, 0); g.addEdge(5, 4, 0);
    g.addEdge(5, 3, 0); g.addEdge(3, 5, 0);
    // Ligacoes entre triangulos
    g.addEdge(0, 3, 0); g.addEdge(3, 0, 0);
    g.addEdge(1, 4, 0); g.addEdge(4, 1, 0);
    g.addEdge(2, 5, 0); g.addEdge(5, 2, 0);

    int expected = 3;
    int result = graphColoring(&g);
    printf("%-30s - Esperado: %d | Resultado: %-2d   [%s]\n", "Test 14 (Prisma Triangular)", expected, result, result == expected ? "TEST PASSED" : "TEST FAILED");
}

void test15() {
    // 15. Grafo Coroa / Crown Graph S_4^0 (Esperado: 2 cores)
    Graph<int> g;
    for(int i = 0; i < 8; i++) g.addVertex(i);
    for(int i = 0; i < 4; i++) {
        for(int j = 4; j < 8; j++) {
            if(j != i + 4) {
                g.addEdge(i, j, 0); g.addEdge(j, i, 0);
            }
        }
    }
    int expected = 2;
    int result = graphColoring(&g);
    printf("%-30s - Esperado: %d | Resultado: %-2d   [%s]\n", "Test 15 (Grafo Coroa)", expected, result, result == expected ? "TEST PASSED" : "TEST FAILED");
}

void test16() {
    // 16. Grafo de Grotzsch (Esperado: 4 cores)
    Graph<int> g;
    for(int i = 0; i < 11; i++) g.addVertex(i);

    for(int i = 0; i < 5; i++) {
        g.addEdge(i, (i+1)%5, 0); g.addEdge((i+1)%5, i, 0);
    }
    for(int i = 0; i < 5; i++) {
        int u = i + 5;
        int v_prev = (i + 4) % 5;
        int v_next = (i + 1) % 5;
        g.addEdge(u, v_prev, 0); g.addEdge(v_prev, u, 0);
        g.addEdge(u, v_next, 0); g.addEdge(v_next, u, 0);
    }
    for(int i = 5; i <= 9; i++) {
        g.addEdge(10, i, 0); g.addEdge(i, 10, 0);
    }
    int expected = 4;
    int result = graphColoring(&g);
    printf("%-30s - Esperado: %d | Resultado: %-2d   [%s]\n", "Test 16 (Grafo Grotzsch)", expected, result, result == expected ? "TEST PASSED" : "TEST FAILED");
}

void test17() {
    // 17. Escada de Mobius de 8 vertices (Esperado: 3 cores)
    Graph<int> g;
    for(int i = 0; i < 8; i++) g.addVertex(i);
    for(int i = 0; i < 8; i++) {
        g.addEdge(i, (i+1)%8, 0); g.addEdge((i+1)%8, i, 0);
    }
    for(int i = 0; i < 4; i++) {
        g.addEdge(i, i+4, 0); g.addEdge(i+4, i, 0);
    }
    int expected = 3;
    int result = graphColoring(&g);
    printf("%-30s - Esperado: %d | Resultado: %-2d   [%s]\n", "Test 17 (Escada Mobius)", expected, result, result == expected ? "TEST PASSED" : "TEST FAILED");
}

void test18() {
    // 18. Grafo Engrenagem (Esperado: 2 cores)
    Graph<int> g;
    for(int i = 0; i < 9; i++) g.addVertex(i);

    for(int i = 1; i <= 7; i+=2) {
        g.addEdge(0, i, 0); g.addEdge(i, 0, 0);
    }
    for(int i = 1; i <= 8; i++) {
        int next = (i % 8) + 1;
        g.addEdge(i, next, 0); g.addEdge(next, i, 0);
    }
    int expected = 2;
    int result = graphColoring(&g);
    printf("%-30s - Esperado: %d | Resultado: %-2d   [%s]\n", "Test 18 (Engrenagem)", expected, result, result == expected ? "TEST PASSED" : "TEST FAILED");
}

void test19() {
    // 19. Grafo de Turan T(10,3) (Esperado: 3 cores)
    Graph<int> g;
    for(int i = 0; i < 10; i++) g.addVertex(i);

    for(int i = 0; i < 10; i++) {
        for(int j = i + 1; j < 10; j++) {
            int group_i = (i < 4) ? 0 : ((i < 7) ? 1 : 2);
            int group_j = (j < 4) ? 0 : ((j < 7) ? 1 : 2);

            if(group_i != group_j) {
                g.addEdge(i, j, 0); g.addEdge(j, i, 0);
            }
        }
    }
    int expected = 3;
    int result = graphColoring(&g);
    printf("%-30s - Esperado: %d | Resultado: %-2d   [%s]\n", "Test 19 (Turan T(10,3))", expected, result, result == expected ? "TEST PASSED" : "TEST FAILED");
}

void test20() {
    // 20. Multicomponente Complexo (Esperado: 4 cores)
    Graph<int> g;
    for(int i = 0; i < 14; i++) g.addVertex(i);

    // Componente 1: Grafo Completo K_4 (0 a 3)
    for(int i = 0; i < 4; i++) {
        for(int j = i + 1; j < 4; j++) {
            g.addEdge(i, j, 0); g.addEdge(j, i, 0);
        }
    }
    // Componente 2: Ciclo Impar C_5 (4 a 8)
    g.addEdge(4, 5, 0); g.addEdge(5, 4, 0);
    g.addEdge(5, 6, 0); g.addEdge(6, 5, 0);
    g.addEdge(6, 7, 0); g.addEdge(7, 6, 0);
    g.addEdge(7, 8, 0); g.addEdge(8, 7, 0);
    g.addEdge(8, 4, 0); g.addEdge(4, 8, 0);
    // Componente 3: Estrela (9 no centro, 10 a 13 pontas)
    for(int i = 10; i <= 13; i++) {
        g.addEdge(9, i, 0); g.addEdge(i, 9, 0);
    }

    int expected = 4;
    int result = graphColoring(&g);
    printf("%-30s - Esperado: %d | Resultado: %-2d   [%s]\n", "Test 20 (Multicomponente)", expected, result, result == expected ? "TEST PASSED" : "TEST FAILED");
}

int graphColoringTestSuite() {
    printf("--- A iniciar a suite de testes de Coloracao de Grafos ---\n\n");

    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    test7();
    test8();
    test9();
    test10();
    test11();
    test12();
    test13();
    test14();
    test15();
    test16();
    test17();
    test18();
    test19();
    test20();

    printf("\n--- Testes concluidos ---\n");
    return 0;
}


int main() {
    graphColoringTestSuite();
    return 0;
}