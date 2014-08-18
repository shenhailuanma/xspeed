# according to Scott McPeak's solution (http://scottmcpeak.com/autodepend/autodepend.html)
# -include $(OBJECTS:.o=.d)

# %.o: %.c
# 	@$(CC) -MM $(CPPFLAGS) $< > $*.d; \
# 	mv -f $*.d $*.d.tmp; \
# 	sed -e 's|.*:|$*.o:|' < $*.d.tmp > $*.d; \
# 	sed -e 's/.*://' -e 's/\\$$//' < $*.d.tmp | fmt -1 | \
# 	  sed -e 's/^ *//' -e 's/$$/:/' >> $*.d; \
# 	rm -f $*.d.tmp
# 	$(COMPILE.c) -o $@ $<

-include $(OBJECTS:.o=.d)

%.o: %.c
	$(COMPILE.c) -MT $@ -MMD -MP -o $@ $<
