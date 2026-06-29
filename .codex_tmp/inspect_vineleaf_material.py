import unreal

asset_path = "/Game/Game/Map/Background/Jungle/Mesh/Vine/VineLeaf_B"
asset = unreal.EditorAssetLibrary.load_asset(asset_path)
if not asset:
    raise RuntimeError(f"Failed to load {asset_path}")

unreal.log(f"asset={asset.get_path_name()} class={asset.get_class().get_name()}")

current = asset
for depth in range(10):
    cls = current.get_class().get_name()
    unreal.log(f"chain[{depth}] {current.get_path_name()} class={cls}")
    if hasattr(current, "get_editor_property"):
        try:
            parent = current.get_editor_property("parent")
        except Exception:
            parent = None
        if parent:
            current = parent
            continue
    break

for prop in dir(asset):
    if "niagara" in prop.lower() or "usage" in prop.lower() or "parent" in prop.lower():
        unreal.log(f"asset attr: {prop}")
