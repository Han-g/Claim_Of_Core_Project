import unreal

MATERIAL_PATH = "/InterchangeAssets/Materials/FBXLegacyPhongSurfaceMaterial"
USAGE = unreal.MaterialUsage.MATUSAGE_NIAGARA_MESH_PARTICLES

material = unreal.EditorAssetLibrary.load_asset(MATERIAL_PATH)
if material is None:
    raise RuntimeError(f"Failed to load material: {MATERIAL_PATH}")

unreal.log(f"Loaded {material.get_path_name()}: {material.get_class().get_name()}")
changed = unreal.MaterialEditingLibrary.set_material_usage(material, USAGE)
unreal.log(f"set_material_usage({USAGE}) returned: {changed}")

saved = unreal.EditorAssetLibrary.save_loaded_asset(material, only_if_is_dirty=False)
unreal.log(f"Saved {material.get_path_name()}: {saved}")

if not saved:
    raise RuntimeError(f"Failed to save material: {MATERIAL_PATH}")
