# -*- coding: utf-8 -*-
'''
	visualize your social network of renren.
'''

import urllib
import urllib2
import cookielib
import re
import cPickle as p
import networkx as nx
import matplotlib.pyplot as plt

username = 'None'
password = 'None'

## Control Graphs, Edit for better graphs as you need
label_flag = True # Whether shows labels.NOTE: configure your matplotlibrc for Chinese characters.
remove_isolated = True # Whether remove isolated nodes(less than iso_level connects)
different_size = True # Nodes for different size, bigger means more shared friends
iso_level = 10
node_size = 40 # Default node size


if __name__ == "__main__":
    G = draw_graph(username, password)
