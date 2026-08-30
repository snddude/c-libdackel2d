# Reclones a git submodule and properly initializes it.
# Use in case of a faulty clone or a pull that was
# done without recursing the repositories submodules.

submodule=""
read -p "Enter submodule name: " submodule

git submodule deinit -f vendor/$submodule

rm -rf .git/modules/vendor/$submodule
rm -rf vendor/$submodule

git submodule update --init vendor/$submodule
