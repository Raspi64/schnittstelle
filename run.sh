if ! test -d ./cmake-build-debug; then
  ./build.sh
else
  (cd cmake-build-debug && make)
fi

(cd cmake-build-debug && ./schnittstelle)

