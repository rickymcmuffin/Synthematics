# Uncomment when debugging Parser
add_executable(Parser 		ast.cpp
					 	equationException.cpp 
						lexer.cpp 
						main.cpp
						parser.cpp 
						token.cpp 
						unparseMath.cpp
						unparser.cpp)

add_library(Parser STATIC 	ast.cpp
					 	equationException.cpp 
						lexer.cpp 
						parser.cpp 
						token.cpp 
						unparseMath.cpp
						unparser.cpp)		
