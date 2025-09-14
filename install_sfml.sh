echo "Installing SFML 2.6"
echo "Run this script in SFML-2.6.2/ directory"

sudo cp -R share/doc/SFML/ /usr/share/doc/SFML/
sudo cp lib/* /usr/lib/
sudo cp lib/pkgconfig/* /usr/lib/pkgconfig/
sudo cp -R lib/cmake/SFML/ /usr/lib/cmake/SFML/
sudo cp -R include/SFML/ /usr/include/SFML/

echo "Finished"
