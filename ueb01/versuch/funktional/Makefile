
sim.data: sim
	@./$<

sim: sim.cpp datatypes.hpp EquationSolver.hpp EquationSolverTest.hpp EquationSolverTop.hpp
	g++ sim.cpp -lsystemc -o $@

plot: compare.plot sim.data golden.data
	@gnuplot -persist $<

check: sim.data golden.data
	@if diff -w sim.data golden.data > results.diff ; then \
        	echo "Simulation PASSED"; \
        else \
        	echo "Simulation FAILED (see results.diff)"; \
        fi;

clean:
	rm -rf sim sim.data results.diff
