set -e

if [[ "${DEBUG}" == "1" ]]; then
	set -x
fi

EXTRACTOR_NAME="ext-dump-ins"

INSTALL_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
PINTOOL_INSTALL_PATH="${INSTALL_DIR}/../../dependencies/pin-3.5-97503-gac534ca30-msvc-windows"
# FIXME: This is hardcoded 64bit dll...
PIN_PATH="${INSTALL_DIR}/obj-intel64/a${EXTRACTOR_NAME}.dll"

function clean() {
	
	if [[ "$1" == "all" ]]; then
		rm *.out
	fi

	make clean
	
	rm *.pdb *.ilk *.exe *.obj
}

function dotest() {
	python -m unittest discover --pattern=*.py	
}

function build() {
	cl traceme.c /DEBUG /Zi

	if [[ $(is64) -eq 1 ]]; then
		make all TARGET=intel64
	else
		make all TARGET=ia32
	fi
}

function pin_proc() {
	local targetExe=$1
	local pin=$2

	$(get_pin_path) -t ${pin} -- ${targetExe}
}

function pin_pid() {
	local pid=$1
	local pin=$2

	$(get_pin_path) -pid ${pid} -t ${pin}
}

function get_pin_path() {
	if [[ $(is64) -eq 0 ]]; then
		echo "${PINTOOL_INSTALL_PATH}/pin.exe"
	else
		echo "${PINTOOL_INSTALL_PATH}/intel64/bin/pin.exe"
	fi
}

function is64() {
	# Visual studio vcvars.bat sets this...
	if [[ "${VSCMD_ARG_TGT_ARCH}" == "x64" ]]; then
		echo 1
	else
		echo 0
	fi
}

function main() {
	clean all 2>/dev/null | true
	dotest
	build
	
	pin_proc "./traceme.exe" $(cygpath -w "${PIN_PATH}")

	time python "f${EXTRACTOR_NAME}.py" > ${EXTRACTOR_NAME}.out
	head ${EXTRACTOR_NAME}.out
	wc -l *.out
	clean 2>/dev/null | true
}

if [[ "${BASH_SOURCE[0]}" == "${0}" ]]; then
    main "$@"
fi