project('finite-automata', 'cpp',
  version : '0.1',
  default_options : ['warning_level=3', 'cpp_std=c++17'])
boost_dep = dependency('boost')

executable('finite-automata',
           'main.cpp',
           install : true, dependencies: [boost_dep])
