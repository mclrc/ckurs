build:
	find -name "*_Aufgaben" -exec make -C {} build \;

test: build
	find -name "*_Aufgaben" -exec make -C {} test \;
