
CFLAGS=$(shell pkg-config gtkmm-3.0 --cflags) -MMD -I ./
LDFLAGS=$(shell pkg-config gtkmm-3.0 --libs)
CXX=g++
OUT=out
SRC = HMI/homeScreen.cpp          \
      HMI/AddMemberScreen.cpp     \
      HMI/ScreenManager.cpp       \
      HMI/RemoveMemberScreen.cpp  \
      HMI/AddBookScreen.cpp       \
      HMI/RemoveBookScreen.cpp    \
      HMI/IssueBookScreen.cpp     \
      App/main.cpp

$(foreach directory , $(sort $(dir $(SRC))) , $(shell mkdir -p $(OUT)/$(directory)))
CFLAGS +=$(foreach directory , $(sort $(dir $(SRC))) ,-I$(directory) )

all : $(OUT)/Library

$(OUT)/Library : $(patsubst %.cpp,$(OUT)/%.o,$(SRC))
	@echo Linking Library...
	@$(CXX) -o $(OUT)/Library $(addprefix $(OUT)/,$(addsuffix .o,$(basename $(SRC)))) $(LDFLAGS)
	
.PHONY : clean
clean :
	@echo Cleaning Out Folder
	rm -r out

define BUILD_RULES=
   $$(OUT)/$(1)%.o:$(1)%.cpp
	@echo Compiling $$(notdir $$<) ...   
	@$$(CXX) -c $$< $$(CFLAGS) -o $$@
endef   

$(foreach directory , $(sort $(dir $(SRC))) ,$(eval $(call BUILD_RULES ,$(directory)) ))
include $(foreach directory , $(sort $(dir $(SRC))),$(wildcard $(OUT)/$(directory)/*.d))

