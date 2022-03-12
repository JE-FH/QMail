add_executable(QMail
	"main.cpp"
)

target_link_libraries(QMail PUBLIC TerminalInterface_static)

target_compile_features(QMail PUBLIC cxx_std_20)
