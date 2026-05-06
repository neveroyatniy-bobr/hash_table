import pandas as pd
import matplotlib.pyplot as plt
import glob
import os

def plot_hashes():
    # Ищем все csv файлы в папке data/
    csv_files = glob.glob('data/*.csv')
    
    if not csv_files:
        print("CSV файлы не найдены в папке data/. Сначала запусти C++ программу.")
        return

    # Настраиваем сетку графиков (например, 4 строки на 2 колонки)
    num_files = len(csv_files)
    cols = 2
    rows = (num_files + 1) // cols

    fig, axes = plt.subplots(rows, cols, figsize=(15, 5 * rows))
    axes = axes.flatten()

    for i, file_path in enumerate(sorted(csv_files)):
        # Читаем данные
        df = pd.read_csv(file_path)
        
        # Название функции из имени файла
        func_name = os.path.basename(file_path).replace('stats_', '').replace('.csv', '').upper()
        
        # Рисуем гистограмму
        axes[i].bar(df['BucketIndex'], df['Count'], color='skyblue', edgecolor='navy')
        
        # Добавляем инфо: среднее кол-во элементов в бакете
        avg = df['Count'].mean()
        axes[i].set_title(f"Hash: {func_name} (Avg: {avg:.2f})")
        axes[i].set_xlabel("Bucket Index")
        axes[i].set_ylabel("Words Count")
        axes[i].grid(axis='y', linestyle='--', alpha=0.7)

    # Убираем пустые графики, если файлов меньше, чем ячеек в сетке
    for j in range(i + 1, len(axes)):
        fig.delaxes(axes[j])

    plt.tight_layout()
    plt.savefig('hash_comparison.png')
    plt.show()
    print("График сохранен в файл hash_comparison.png")

if __name__ == "__main__":
    plot_hashes()
