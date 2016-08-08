dirs := attr mod/hello mod_invoke/A_func mod_invoke/B_func
all:
	$(foreach N,$(dirs),make -C $(N);)
clean:
	$(foreach N,$(dirs),make -C $(N) clean;)
