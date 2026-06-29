import unreal

ASSET_PATH = "/Game/Game/Map/Background/Jungle/Mesh/Vine/VineLeaf_B"
USAGE = unreal.MaterialUsage.MATUSAGE_NIAGARA_MESH_PARTICLES

asset = unreal.EditorAssetLibrary.load_asset(ASSET_PATH)
if asset is None:
    raise RuntimeError(f"Failed to load asset: {ASSET_PATH}")

unreal.log(f"Loaded {ASSET_PATH}: {asset.get_class().get_name()}")

changed = False
try:
    changed = unreal.MaterialEditingLibrary.set_material_usage(asset, USAGE)
    unreal.log(f"set_material_usage returned: {changed}")
except Exception as exc:
    unreal.log_error(f"set_material_usage failed: {exc}")
    raise

asset.mark_package_dirty()
saved = unreal.EditorAssetLibrary.save_loaded_asset(asset, only_if_is_dirty=False)
unreal.log(f"Saved {ASSET_PATH}: {saved}")

if not saved:
    raise RuntimeError(f"Failed to save asset: {ASSET_PATH}")
