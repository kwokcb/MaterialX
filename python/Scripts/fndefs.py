# %%
import MaterialX as mx

print("MaterialX version:", mx.getVersionString())

doc : mx.Document = mx.createDocument()

stdlib = mx.createDocument()
libFiles = mx.loadLibraries(mx.getDefaultDataLibraryFolders(), mx.getDefaultDataSearchPath(), stdlib)  

defs = stdlib.getNodeDefs()
print("Number of node definitions loaded:", len(defs))


# %%

test_name = "ND_tiledimage_color3"
imagefloat = stdlib.getNodeDef(test_name)
if imagefloat:
    print(f"Node Definition '{test_name}' found.")
    #print(mx.prettyPrint(imagefloat))

    graph = imagefloat.getImplementation()
    if graph:
        if graph.isA(mx.NodeGraph) :
            #print(mx.prettyPrint(graph))
            newGraph = imagefloat.makeFunctionalDefinition()
        
            if False and not newGraph:
                ngname = graph.getNodeDefString()
                qualname = graph.getQualifiedName(imagefloat.getName())
                print("nodedef string:", ngname)
                print("qualified name:", qualname)
                if ngname == qualname:
                    newGraphName = graph.getName()
                    newGraph = imagefloat.addChildOfCategory("nodegraph", newGraphName)
                    if not newGraph:
                        print("Failed to create new functional node graph:", newGraphName)
                    else:   
                        print("Created new functional node graph:", newGraphName)
                        newGraph.copyContentFrom(graph)
                        newGraph.removeAttribute(mx.InterfaceElement.NODE_DEF_ATTRIBUTE)
                        graph.removeAttribute(mx.InterfaceElement.NODE_DEF_ATTRIBUTE)
                        
                        parent = imagefloat.getParent()
                        tempName = parent.createValidChildName(newGraphName + "_old")
                        graph.setName(tempName)
                        newGraph.setName(newGraphName)
                    

        if newGraph:
            print("New functional node definition name:", newGraph.getName())
            print(mx.prettyPrint(imagefloat))

# %%
stdsurf = stdlib.getNodeDef("ND_standard_surface_surfaceshader")
nodegraph_counts = {}
if stdsurf:
    print(f"got standard surface node def: {stdsurf.getVersionString()}")
    other_stdsurf = stdsurf.getMatchingDefinitions()
    print("number of matching definitions:", len(other_stdsurf))
    for ndstring in other_stdsurf:
        print("matching definition:", ndstring)
        nd = stdlib.getNodeDef(ndstring)
        if nd:
            print("  version:", nd.getVersionString())
            impl = nd.getImplementation()
            nodegraph_string = impl.getAttribute("nodegraph")
            if nodegraph_string:
                impl = stdlib.getNodeGraph(nodegraph_string)
                if nodegraph_string in nodegraph_counts:
                    nodegraph_counts[nodegraph_string] += 1
                else:
                    nodegraph_counts[nodegraph_string] = 1
            if impl and impl.isA(mx.NodeGraph):
                print("  implementation:", impl.getName())

print("*"*80)
print("Node graph usage counts among standard surface definitions:")
for ngname, count in nodegraph_counts.items():
    print(f"  {ngname}: {count}")


