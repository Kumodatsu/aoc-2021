cd src
javac -classpath . com/github/kumodatsu/*.java
jar -cmvf META-INF/MANIFEST.mf ../out/Main.jar com/github/kumodatsu/*.class
cd ..
