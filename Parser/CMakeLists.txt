# Uncomment when debugging Parser
cmake_minimum_required(VERSION 3.15)
project(Parser VERSION 1.0)
add_executable(Parser 		ast.cpp
					 	equationException.cpp 
						lexer.cpp 
						main.cpp
						parser.cpp 
						token.cpp 
						unparseMath.cpp
						unparser.cpp)

# add_library(Parser STATIC 	ast.cpp
# 						eqast.cpp
# 					 	equationException.cpp 
# 						lexer.cpp 
# 						parser.cpp 
# 						token.cpp 
# 						unparseMath.cpp
# 						unparser.cpp)		
