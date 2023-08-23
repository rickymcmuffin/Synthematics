cmake_minimum_required(VERSION 3.27.3)

project(MathSynth)


add_executable(MathSynth main.cpp ast.cpp equationException.cpp lexer.cpp parser.cpp token.cpp unparseMath.cpp unparser.cpp)