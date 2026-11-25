import pandas as pd
import matplotlib.pyplot as plt
import matplotlib.ticker as ticker

# Estilo limpo para relatório técnico/acadêmico
plt.rcParams.update({
    'font.size': 11,
    'axes.titlesize': 12,
    'axes.titleweight': 'bold',
    'axes.labelsize': 11,
    'legend.fontsize': 10,
    'axes.grid': True,
    'grid.linestyle': '--',
    'grid.alpha': 0.5
})

df = pd.read_csv('resultados.csv')

metricas = [
    {
        'col_avl': 'Comp_Constr_AVL',
        'col_rb': 'Comp_Constr_RB',
        'titulo': 'Comparações na Construção (AVL vs. Rubro-Negra)',
        'ylabel': 'Número de Comparações',
        'arquivo': 'grafico_1_comp_construcao.png',
        'escala_milhoes': True
    },
    {
        'col_avl': 'Tempo_Constr_AVL_ms',
        'col_rb': 'Tempo_Constr_RB_ms',
        'titulo': 'Tempo de Construção (AVL vs. Rubro-Negra)',
        'ylabel': 'Tempo (ms)',
        'arquivo': 'grafico_2_tempo_construcao.png',
        'escala_milhoes': False
    },
    {
        'col_avl': 'Comp_Consul_AVL',
        'col_rb': 'Comp_Consul_RB',
        'titulo': 'Comparações na Consulta (AVL vs. Rubro-Negra)',
        'ylabel': 'Número de Comparações',
        'arquivo': 'grafico_3_comp_consulta.png',
        'escala_milhoes': True
    },
    {
        'col_avl': 'Tempo_Consul_AVL_ms',
        'col_rb': 'Tempo_Consul_RB_ms',
        'titulo': 'Tempo de Consulta (AVL vs. Rubro-Negra)',
        'ylabel': 'Tempo (ms)',
        'arquivo': 'grafico_4_tempo_consulta.png',
        'escala_milhoes': False
    }
]

def formatar_eixos(ax, escala_milhoes=False, log_scale=False):
    if log_scale:
        ax.set_xscale('log')
        ax.set_yscale('log')
        return
    ax.xaxis.set_major_formatter(
        ticker.FuncFormatter(lambda x, _: f'{int(x):,}'.replace(',', '.'))
    )
    if escala_milhoes:
        ax.yaxis.set_major_formatter(
            ticker.FuncFormatter(
                lambda y, _: f'{y/1e6:.1f}M' if y >= 1e6 else f'{int(y):,}'.replace(',', '.')
            )
        )

# 1. Exportar os 4 gráficos individuais (300 DPI)
for m in metricas:
    fig, ax = plt.subplots(figsize=(7.5, 4.8))
    ax.plot(df['Tamanho'], df[m['col_avl']], marker='o', markersize=4.5,
            linewidth=2, color='#1f77b4', label='Árvore AVL')
    ax.plot(df['Tamanho'], df[m['col_rb']], marker='s', markersize=4.5,
            linewidth=2, linestyle='--', color='#d62728', label='Árvore Rubro-Negra (RB)')

    ax.set_title(m['titulo'])
    ax.set_xlabel('Tamanho da Entrada (N)')
    ax.set_ylabel(m['ylabel'])
    ax.legend(loc='upper left', frameon=True)
    formatar_eixos(ax, escala_milhoes=m['escala_milhoes'], log_scale=False)

    plt.tight_layout()
    plt.savefig(m['arquivo'], dpi=300, bbox_inches='tight')
    plt.close(fig)

# 2. Exportar painel consolidado 2x2
fig, axes = plt.subplots(2, 2, figsize=(13, 9.5))
for ax, m in zip(axes.flatten(), metricas):
    ax.plot(df['Tamanho'], df[m['col_avl']], marker='o', markersize=4,
            linewidth=1.8, color='#1f77b4', label='Árvore AVL')
    ax.plot(df['Tamanho'], df[m['col_rb']], marker='s', markersize=4,
            linewidth=1.8, linestyle='--', color='#d62728', label='Árvore Rubro-Negra (RB)')

    ax.set_title(m['titulo'])
    ax.set_xlabel('Tamanho da Entrada (N)')
    ax.set_ylabel(m['ylabel'])
    ax.legend(loc='upper left', frameon=True)
    formatar_eixos(ax, escala_milhoes=m['escala_milhoes'], log_scale=False)

plt.tight_layout(pad=2.0)
plt.savefig('painel_geral_avl_rb.png', dpi=300, bbox_inches='tight')
plt.close(fig)
print("Gráficos salvos com sucesso.")