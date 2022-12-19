
rm -R build/
sphinx-build -b html -d build/doctrees  ./ build/html
touch ./build/html/.nojekyll