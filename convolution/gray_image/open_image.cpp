#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;

int main(int argc, char** argv) {
  // Verificação de parâmetros e instrução de uso.
  if( argc < 2 ) { // Fornece instrução de uso se não houver pelo menos um parâmetro de entrada (nome da imagem).
    cout << "Usage: " << argv[0] << " <image_file_name>" << endl;
    return(0);
  }

  // Leitura de uma entrada do arquivo no formato de tons de cinza (monocrimático).
  cv::Mat image = cv::imread(argv[1], cv::IMREAD_GRAYSCALE);

  // Mostrando imagem lida do arquivo no display. Aguarda por qualquer tecla ser pressionada para fechar a janela.
  cv::imshow("my image", image);
  cv::waitKey(0);
  cv::destroyAllWindows();

  // Utilização de estrutura de dados adicional para facilitar e acelerar o acesso aos dados da imagem.
  uint8_t *myData = image.data;

  // Leitura das informações da imagem: número de colunas e linhas e tamanho de uma linha.
  int width = image.cols;
  int height = image.rows;
  int stride = image.step;
  cout << "Columns: " << width << ". Lines: " << height << ". Stride: " << stride << endl; 

  // Preparando variáveis para encontrar as coordenadas e o valor máximo de cada canal de cor da imagem.
  uint8_t max_val = 0;
  int line_stride = 0;
  /* Laço do código para percorrer toda a imagem e buscar pelos pixels de maior valor de cada canal. Nesta implementação,
     andamos com saltos de coluna em coluna no laço interno e de linha em linha no laço externo. Para isso, é utilizada
     a variável auxiliar line_stride para que o código tenho um desempenho melhor. Evitamos usar multiplicações para
     que o código seja mais eficiente.
  */
  for(int y = 0; y < height; ++y) {
    line_stride += stride;
    for(int x = 0; x < width; ++x) {
      uint8_t val = myData[x + line_stride];
      if(max_val < val)
 	max_val = val;
    }
  }

  // Aqui imprimimos o valor máximo encontrado.
  cout << "max value: " << static_cast<int>(max_val) << endl;

  // Liberando a imagem da memória.
  image.release();

  return(0);
}
