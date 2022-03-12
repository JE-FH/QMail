add_executable(QMail
	"main.cpp"
	"TITerminalWindow.cpp"
	"ITerminalWindow.hpp"
	"TITerminalWindow.hpp"
)

target_link_libraries(QMail PUBLIC TerminalInterface_static)

target_compile_features(QMail PUBLIC cxx_std_20)
