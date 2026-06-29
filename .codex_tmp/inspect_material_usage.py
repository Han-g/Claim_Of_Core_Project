import unreal

print("MaterialUsage enum values:")
for name in dir(unreal.MaterialUsage):
    if "NIAGARA" in name.upper() or "MESH" in name.upper():
        print(name, getattr(unreal.MaterialUsage, name))
