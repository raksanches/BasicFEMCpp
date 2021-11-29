# Introdução
Código básico para simulações de elementos finitos otimizadas em C++

[![Run Unit Tests](https://github.com/raksanches/BasicFEMCpp/actions/workflows/run_unittests.yml/badge.svg)](https://github.com/raksanches/BasicFEMCpp/actions/workflows/run_unittests.yml)

# Desenvolvedores:
Rodolfo Sanches

Jeferson Fernandes

Wesley Wutzow

# Requisitos
A utilização desse código necessita das seguintes bibliotecas externas:

MPICH

PETSc

METIS

CMake

```bash
sudo apt-get install cmake-curses-gui
```

# Utilização
Para instalação das bibliotecas externas, siga o tutorial disponível em: (https://github.com/giavancini/UnifiedFSI)

Tendo as bibliotecas necessárias instaladas, os passos para compilação deste programa são:

1- Criar um diretório onde os arquivos de compilação serão armazenados e acessá-lo:
```bash
mkdir build
cd build
```

2- Criar a "build" desejada (Debug ou Release):
```bash
ccmake ..
```
- Pressione "C";
- Insira a "build" desejada em CMAKE_BUILD_TYPE: Debug ou Release
- Em PETSC_DIR adicione o caminho para a pasta onde as diferentes builds do PETSc estão instaladas.
- Pressione "C" novamente;
- Confira se o campo PETSC-ARCH está correto, caso contrário corrija-o;
- Pressione "C" novamente;
- Pressione "G";

3- Feitos os passos 1 e 2, os makefiles do código já terão sido criados, assim a compilação pode ser feita diretamente no VSCode (Ctrl+Shift+B) ou pelo terminal:
```bash
make -j8
```

4- Após isso, será criado um executável para cada arquivo do tipo "main". Para executá-lo, pressione F5 no VSCode.
