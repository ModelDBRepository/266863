"""
os sys and csv glob modules were imported
importing
	numpy			=> *
	numpy.random		=> rnd
	scipy			=> sp
	scipy.fftpack		=> spfft
	scipy.signal		=> spsignal
	matplotlib.pyplot	=> *
	matplotlib.mlab		=> mlab
	matplotlib.image	=> img
	datatoolkit		=> dtk
	multiprocs		=> mps
	subprocess		=> sbp
	cPickle/pickle		=> pkl
"""

import os,sys,csv,glob
from numpy import *
from numpy import random as rnd
import scipy as sp
import scipy.fftpack as spfft
import scipy.signal as spsignal
import matplotlib
matplotlib.rcParams["savefig.directory"] = ""
from matplotlib.pyplot import *
import matplotlib.mlab as mlab
import matplotlib.image as img
#import datatoolkit as dtk
#from multiprocs import multiprocs as mps
import subprocess as sbp
try:
	import cPickle as pkl
except:
	import pickle as pkl

