EIDE_UNIFY_BUILDER := 1
CFLAGS := --std-c99 -c -mmcs51 --opt-code-speed --iram-size 256 --xram-size 0 --code-size 8192 -I.\src -I.\inc
CXXFLAGS := -c -mmcs51 --opt-code-speed --iram-size 256 --xram-size 0 --code-size 8192 -I.\src -I.\inc
ASMFLAGS := -l -o -s -I.\src -I.\inc
LDFLAGS := --out-fmt-ihx -mmcs51 --iram-size 256 --xram-size 0 --code-size 8192
LDLIBS := 
