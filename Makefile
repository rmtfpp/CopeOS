.PHONY: kernel run clean format

kernel:
	@$(MAKE) -C src/kernel build-iso

run:
	@$(MAKE) -C src/kernel run

clean:
	@$(MAKE) -C src/kernel clean

format:
	find src/kernel/ -type f \( -name "*.c" -o -name "*.h" \) | xargs clang-format -style="{BasedOnStyle: Microsoft, IndentWidth: 8, PointerAlignment: Left, AlignConsecutiveAssignments: true, AlignConsecutiveDeclarations: true, AlignConsecutiveMacros: true, UseTab: Always, TabWidth: 8, AlignAfterOpenBracket: true}" -i
