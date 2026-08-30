submodule=""
read -p "Enter submodule name: " submodule

git submodule deinit -f vendor/$submodule

rm -rf .git/modules/vendor/$submodule
rm -rf vendor/$submodule

git submodule update --init vendor/$submodule
