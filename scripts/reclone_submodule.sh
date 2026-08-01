submodule=""
read -p "Enter submodule name: " submodule

git submodule deinit -f engine/vendor/$submodule

rm -rf .git/modules/engine/vendor/$submodule
rm -rf engine/vendor/$submodule

git submodule update --init engine/vendor/$submodule
