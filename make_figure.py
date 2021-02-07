#!/bin/python3
import matplotlib.pyplot as plot
from matplotlib import cm
import numpy
import pandas
from scipy.interpolate import griddata
from sys import argv
from pprint import pprint

if __name__ == "__main__":
        if len(argv) < 2:
            print("Provide a file name")

        file = argv[1]
        df = pandas.read_csv(file, skipinitialspace=True)

        print(df['unnu'])

        # x1 = numpy.linspace(df['n'].min(),   df['n'].max(),   len(df['n'].unique()))
        # y1 = numpy.linspace(df['max'].min(), df['max'].max(), len(df['max'].unique()))
        # x2, y2 = numpy.meshgrid(x1, y1)
        # z2 = griddata((df['n'], df['max']), df['unnu'], (x2, y2), method='cubic')

        # pprint(x2)
        # pprint(y2)
        # pprint(z2)

        # figure = plot.figure()
        # ax = plot.axes(projection='3d')
        # # ax.plot_surface(df['n'].tolist(), df['max'].tolist(), df['unnu'].tolist(), rstride=1, cstride=1, cmap='viridis', edgecolor='none')
        # ax.plot_surface(x2, y2, z2, rstride=1, cstride=1, cmap='viridis', edgecolor='none')
        # ax.set_title('unnu');

        fig = plot.figure()
        ax = fig.gca(projection='3d')

        surf = ax.plot_trisurf(df['n'], df['max'], df['unnu'], cmap=cm.jet, linewidth=0.1)
        fig.colorbar(surf, shrink=0.5, aspect=5)
        plot.show()

