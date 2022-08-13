#pragma once
#include "stdafx.h"
#include "Debugger/PpuTools.h"

class Debugger;
class Emulator;
struct BaseState;
struct LayerConfig;
struct FrameInfo;
struct SnesPpuState;

struct SnesPpuToolsState
{
	uint8_t ScanlineBgMode[239];
	int32_t Mode7StartX[239];
	int32_t Mode7StartY[239];
	int32_t Mode7EndX[239];
	int32_t Mode7EndY[239];
};

class SnesPpuTools final : public PpuTools
{
private:
	SnesPpuToolsState _state = {};

	void GetSpriteInfo(DebugSpriteInfo& sprite, uint16_t spriteIndex, GetSpritePreviewOptions& options, SnesPpuState& state, uint8_t* vram, uint8_t* oamRam, uint32_t* palette);
	
	template<TileFormat format> void RenderMode7Tilemap(uint8_t* vram, uint32_t* outBuffer, uint32_t* palette);
	template<TileFormat format> void RenderTilemap(int rowCount, LayerConfig& layer, int columnCount, uint8_t* vram, int tileHeight, int tileWidth, bool largeTileHeight, bool largeTileWidth, const uint8_t& bpp, uint32_t* outBuffer, FrameInfo& outputSize, uint32_t* palette, const uint16_t& basePaletteOffset);

public:
	SnesPpuTools(Debugger* debugger, Emulator *emu);

	void GetPpuToolsState(BaseState& state) override;
	void SetPpuScanlineState(uint16_t scanline, uint8_t mode, int32_t mode7startX, int32_t mode7startY, int32_t mode7endX, int32_t mode7endY);

	DebugTilemapInfo GetTilemap(GetTilemapOptions options, BaseState& state, uint8_t* vram, uint32_t* palette, uint32_t* outBuffer) override;
	FrameInfo GetTilemapSize(GetTilemapOptions options, BaseState& state) override;
	DebugTilemapTileInfo GetTilemapTileInfo(uint32_t x, uint32_t y, uint8_t* vram, GetTilemapOptions options, BaseState& baseState) override;

	void GetSpritePreview(GetSpritePreviewOptions options, BaseState& state, uint8_t* vram, uint8_t* oamRam, uint32_t* palette, uint32_t* outBuffer) override;
	void GetSpriteList(GetSpritePreviewOptions options, BaseState& baseState, uint8_t* vram, uint8_t* oamRam, uint32_t* palette, DebugSpriteInfo outBuffer[]) override;
	DebugSpritePreviewInfo GetSpritePreviewInfo(GetSpritePreviewOptions options, BaseState& state) override;

	DebugPaletteInfo GetPaletteInfo(GetPaletteInfoOptions options) override;
	void SetPaletteColor(int32_t colorIndex, uint32_t color) override;
};