%.o: %.cc
	$(COMPILE.cc) -MT $@ -MMD -MP -o $@ $<
