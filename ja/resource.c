
#include <sys/param.h>
#include "resource.h"
#include "unpack.h"
#include "util.h"

static const int TMP_SIZE = 72728;

static const int BACKGROUND_SIZE = 320 * 200;

static const char *_datapath;

struct resource_t ja_g_res;

void ja_res_init(const char *path, int vga_size) {
	_datapath = path;

	char filepath[MAXPATHLEN];

	static const int FONT_SIZE = 7264;
	ja_g_res.font = (uint8_t *)malloc(FONT_SIZE);
	if (!ja_g_res.font) {
		print_error("Failed to allocate font buffer, %d bytes", FONT_SIZE);
	}
	snprintf(filepath, sizeof(filepath), "%s/font256.eat", _datapath);
	ja_unpack(filepath, ja_g_res.font, FONT_SIZE);

	static const int BOARD_SIZE = 12800;
	ja_g_res.board = (uint8_t *)malloc(BOARD_SIZE);
	if (!ja_g_res.board) {
		print_error("Failed to allocate board buffer, %d bytes", BOARD_SIZE);
	}
	snprintf(filepath, sizeof(filepath), "%s/board.eat", _datapath);
	ja_unpack(filepath, ja_g_res.board, BOARD_SIZE);

	static const int MOTIF_SIZE = 320 * 25 * 9;
	ja_g_res.motif = (uint8_t *)malloc(MOTIF_SIZE);
	if (!ja_g_res.motif) {
		print_error("Failed to allocate motif buffer, %d bytes", MOTIF_SIZE);
	}
	snprintf(filepath, sizeof(filepath), "%s/motif.eat", _datapath);
	ja_unpack(filepath, ja_g_res.motif, MOTIF_SIZE);

	static const int SPRITES_SIZE = 108044;
	ja_g_res.sprites = (uint8_t *)malloc(SPRITES_SIZE);
	if (!ja_g_res.sprites) {
		print_error("Failed to allocate sprites buffer, %d bytes", SPRITES_SIZE);
	}
	snprintf(filepath, sizeof(filepath), "%s/sprites.eat", _datapath);
	ja_unpack(filepath, ja_g_res.sprites, SPRITES_SIZE);

	static const int SAMPLES_SIZE = 49398;
	ja_g_res.samples = (uint8_t *)malloc(SAMPLES_SIZE);
	if (!ja_g_res.samples) {
		print_error("Failed to allocate samples buffer, %d bytes", SAMPLES_SIZE);
	}
	snprintf(filepath, sizeof(filepath), "%s/samples.eat", _datapath);
	ja_unpack(filepath, ja_g_res.samples, SAMPLES_SIZE);

	ja_g_res.tmp = (uint8_t *)malloc(TMP_SIZE);
	if (!ja_g_res.tmp) {
		print_error("Failed to allocate tmp buffer, %d bytes", TMP_SIZE);
	}

	ja_g_res.background = (uint8_t *)malloc(BACKGROUND_SIZE);
	if (!ja_g_res.background) {
		print_error("Failed to allocate tmp buffer, %d bytes", BACKGROUND_SIZE);
	}

	ja_g_res.vga = (uint8_t *)malloc(vga_size);
	if (!ja_g_res.vga) {
		print_error("Failed to allocate vga buffer, %d bytes", vga_size);
	}
}

void ja_res_fini() {
	free(ja_g_res.font);
	ja_g_res.font = 0;
	free(ja_g_res.board);
	ja_g_res.board = 0;
	free(ja_g_res.motif);
	ja_g_res.motif = 0;
	free(ja_g_res.sprites);
	ja_g_res.sprites = 0;
	free(ja_g_res.tmp);
	ja_g_res.tmp = 0;
	free(ja_g_res.background);
	ja_g_res.background = 0;
	free(ja_g_res.vga);
	ja_g_res.vga = 0;
}

int ja_load_file(const char *filename) {
	char filepath[MAXPATHLEN];
	snprintf(filepath, sizeof(filepath), "%s/%s", _datapath, filename);
	print_debug(DBG_RESOURCE, "load_file '%s'", filepath);
	return ja_unpack(filepath, ja_g_res.tmp, TMP_SIZE);
}
