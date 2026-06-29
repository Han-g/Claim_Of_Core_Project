import unreal

SOURCE_MATERIAL = "/InterchangeAssets/Materials/FBXLegacyPhongSurfaceMaterial"
LOCAL_MATERIAL = "/Game/Game/Map/Background/Jungle/Mesh/Vine/M_FBXLegacyPhongSurfaceMaterial_Niagara"
INSTANCE_PATH = "/Game/Game/Map/Background/Jungle/Mesh/Vine/VineLeaf_B"
USAGE = unreal.MaterialUsage.MATUSAGE_NIAGARA_MESH_PARTICLES

source = unreal.EditorAssetLibrary.load_asset(SOURCE_MATERIAL)
if source is None:
    raise RuntimeError(f"Failed to load source material: {SOURCE_MATERIAL}")

local = unreal.EditorAssetLibrary.load_asset(LOCAL_MATERIAL)
if local is None:
    local = unreal.EditorAssetLibrary.duplicate_asset(SOURCE_MATERIAL, LOCAL_MATERIAL)
    if local is None:
        raise RuntimeError(f"Failed to duplicate {SOURCE_MATERIAL} to {LOCAL_MATERIAL}")
    unreal.log(f"Duplicated local material: {LOCAL_MATERIAL}")
else:
    unreal.log(f"Using existing local material: {LOCAL_MATERIAL}")

changed = unreal.MaterialEditingLibrary.set_material_usage(local, USAGE)
unreal.log(f"set_material_usage({USAGE}) on local material returned: {changed}")

instance = unreal.EditorAssetLibrary.load_asset(INSTANCE_PATH)
if instance is None:
    raise RuntimeError(f"Failed to load material instance: {INSTANCE_PATH}")

instance.set_editor_property("parent", local)
unreal.log(f"Set parent of {INSTANCE_PATH} to {LOCAL_MATERIAL}")

saved_local = unreal.EditorAssetLibrary.save_loaded_asset(local, only_if_is_dirty=False)
saved_instance = unreal.EditorAssetLibrary.save_loaded_asset(instance, only_if_is_dirty=False)
unreal.log(f"Saved local material: {saved_local}")
unreal.log(f"Saved material instance: {saved_instance}")

if not saved_local or not saved_instance:
    raise RuntimeError("Failed to save one or more assets")
