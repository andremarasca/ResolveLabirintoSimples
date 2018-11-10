clear all;
clc;
n = 4;
formato = '.gif';
entrada = sprintf('Labirinto%d%s', n, formato);
saida = sprintf('PGM/Entrada/Labirinto%d%s', n, '.pgm');
imshow(imread(entrada));
imwrite(imread(entrada), saida);%,'Encoding','ASCII');

%%

solucao = sprintf('PGM/Saida/Labirinto%d%s', n, '.pgm');
resolvido = sprintf('Labirinto%ds%s', n, '.png');
imwrite(imread(saida), resolvido);