from setuptools import setup, Extension, find_packages

arrays_module = Extension('matropy.arrays', sources = ['matropy/src/arrays/array_py.c', 'matropy/src/arrays/array.c'])
rand_module = Extension('matropy.rand', sources = ['matropy/src/rand/rand_py.c', 'matropy/src/rand/rand.c'])

setup(
    name = "matropy",
    version = "0.0.0",
    description = 'The new C Optimized Numerical Library',
    author = 'Somiparno Chattopadhyay',
    ext_modules = [arrays_module, rand_module],
    packages = ['matropy']
)
