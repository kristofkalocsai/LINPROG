# 3. fejezet
# Megosztott programkönyvtárak

SUBDIRS = statikusan_betoltott dinamikusan_betoltott

.PHONY: subdirs $(SUBDIRS) clean

subdirs: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@

clean:
	for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir clean; \
	done
