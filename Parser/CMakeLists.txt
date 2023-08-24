add_library(Parser SHARED 	ast.cpp
					 	equationException.cpp 
						lexer.cpp 
						parser.cpp 
						token.cpp 
						unparseMath.cpp
						unparser.cpp)		