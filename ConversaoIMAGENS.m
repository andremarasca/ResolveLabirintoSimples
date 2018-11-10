clear all;
close all;
clc;

%% Converte imagem em matriz

n = 1;
formato = '.png';
entrada = sprintf('Labirinto%d%s', n, formato);
saida = sprintf('Entrada/Labirinto%d%s', n, '.txt');
A = imread(entrada);
A = A(:, :, 1);
[M, N] = size(A);
fileID = fopen(saida, 'w+');
fprintf(fileID, "%d %d\r\n", M, N);
for i = 1 : M
    for j = 1 : N
        fprintf(fileID, "%d ", A(i,j));
    end
    fprintf(fileID, "\r\n");
end

%% chama o C

system('ResolveLabirinto.exe <Entrada/Labirinto1.txt >Saida/Labirinto1.txt ');

%% Pega labirinto em txt e gera imagem

resolvido = sprintf('Saida/Labirinto%d%s', n, '.txt');

fileID = fopen(resolvido, 'r');
A = fscanf(fileID, '%d');
M = A(1);
N = A(2);
A = vec2mat(A(3:end),N);
imwrite(uint8(A), ['Resolvido', entrada]);