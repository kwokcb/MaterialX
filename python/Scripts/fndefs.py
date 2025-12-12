# %%
import MaterialX as mx

print("MaterialX version:", mx.getVersionString())

def createTestDoc():
    doc : mx.Document = mx.createDocument()

    stdlib = mx.createDocument()
    libFiles = mx.loadLibraries(mx.getDefaultDataLibraryFolders(), mx.getDefaultDataSearchPath(), stdlib)  

    defs = stdlib.getNodeDefs()
    print("Number of node definitions loaded:", len(defs))
    return doc, stdlib

doc, stdlib = createTestDoc()

# %%



def test_make_functional_definition(test_name):
    test_def = stdlib.getNodeDef(test_name)
    if test_def:
        print(f"Node Definition '{test_name}' found.")
        #print(mx.prettyPrint(test_def))

        graph = test_def.getImplementation()
        if graph:
            if graph.isA(mx.NodeGraph) :
                #print(mx.prettyPrint(graph))
                newGraph = test_def.makeFunctionalDefinition()
            
                if False and not newGraph:
                    # This is the C++ code in Python form
                    ngname = graph.getNodeDefString()
                    qualname = graph.getQualifiedName(test_def.getName())
                    print("nodedef string:", ngname)
                    print("qualified name:", qualname)
                    if ngname == qualname:
                        newGraphName = graph.getName()
                        newGraph = test_def.addChildOfCategory("nodegraph", newGraphName)
                        if not newGraph:
                            print("Failed to create new functional node graph:", newGraphName)
                        else:   
                            print("Created new functional node graph:", newGraphName)
                            newGraph.copyContentFrom(graph)
                            newGraph.removeAttribute(mx.InterfaceElement.NODE_DEF_ATTRIBUTE)
                            
                            parent = test_def.getParent()
                            graph.removeAttribute(mx.InterfaceElement.NODE_DEF_ATTRIBUTE)
                            #tempName = parent.createValidChildName(newGraphName + "_old")
                            #graph.setName(tempName)
                        

                if newGraph:
                    print("New functional node definition name:", newGraph.getName())
                    print(mx.prettyPrint(test_def))

test_name = "ND_tiledimage_color3"
test_make_functional_definition(test_name)

test_name = "ND_tiledimage_color4"
test_make_functional_definition(test_name)

# %%

def get_matching_definitions(def_name):
    check_nodedef = stdlib.getNodeDef(def_name)
    nodegraph_counts = {}  # Will store {nodegraph: count}
    nodegraph_nodedefs = {}  # Will store {nodegraph: set(nodedefs)}
    mapped_other_check_nodedef = None
    if check_nodedef:
        print(f"got node def: {check_nodedef.getVersionString()}")

        # Traverse inheritance to find all matching definitions
        other_check_nodedef = check_nodedef.getMatchingDefinitions()
        print("* number of matching definitions:", len(other_check_nodedef))
        for ndstring in other_check_nodedef:
            print("matching definition:", ndstring)
            nd = stdlib.getNodeDef(ndstring)
            if nd:
                # See if there are any indirect mappings
                mapped_other_check_nodedef = stdlib.getMatchingIndirectImplementations(ndstring)
                print("number of mapped implementations:", len(mapped_other_check_nodedef))
                for impl in mapped_other_check_nodedef:
                    print("- mapping implementations:", impl.getName())
                    #print(mx.prettyPrint(impl))

                print("  version:", nd.getVersionString(), " inherits from:", nd.getInheritString())
                impl = nd.getImplementation()
                if impl.isA(mx.NodeGraph):
                    print("  nodegraph implementation:", impl.getName()) 

                    # Check if there is an indirect mapping to get to this nodegraph
                    #
                    if mapped_other_check_nodedef:
                        for other in mapped_other_check_nodedef:
                            if other.getAttribute("nodegraph") == impl.getName():
                                print(f"   (nodegraph acessed via {other.getName()} implementation redirection !)") 
                else: 
                    # >>> Code to handle regression (not required anymore after new cache change)          
                    nodegraph_name = None
                    nodegraph_string = impl.getAttribute("nodegraph")
                    if nodegraph_string:
                        impl = stdlib.getNodeGraph(nodegraph_string)
                        nodegraph_name = nodegraph_string
                    if nodegraph_name:
                        # Count usage of each nodegraph
                        if nodegraph_name in nodegraph_counts:
                            nodegraph_counts[nodegraph_name] += 1
                        else:
                            nodegraph_counts[nodegraph_name] = 1
                        # Track which nodedefs use this nodegraph
                        if nodegraph_name not in nodegraph_nodedefs:
                            nodegraph_nodedefs[nodegraph_name] = set()
                        nodegraph_nodedefs[nodegraph_name].add(ndstring)
                    if impl and impl.isA(mx.NodeGraph):
                        print("  mapped implementation:", impl.getName())

        impls = stdlib.getImplementations()
        print("*"*80)
        print("Mapped Node graph usage counts:")
        for ngname, count in nodegraph_counts.items():
            ndefs = nodegraph_nodedefs[ngname]
            for ndef in ndefs:
                print(f"  nodedef: {ndef}, nodegraph: {ngname}, count: {count}")

        print("-"*80 + "\n")


get_matching_definitions("ND_UsdUVTexture")
get_matching_definitions("ND_standard_surface_surfaceshader")


# %%
indirect_mapped_nodedefs = {}
direct_mapped_nodefs = {}

for ndef in stdlib.getNodeDefs():
    impl = ndef.getImplementation()
    if impl:
        if impl.isA(mx.NodeGraph) :
            direct_mapped_nodefs[ndef.getName()] = impl
            continue
        elif impl.hasAttribute("nodegraph"):
            indirect_mapped_nodedefs[ndef.getName()] = impl    

print("Directly mapped nodedefs count:", len(direct_mapped_nodefs))
print("Indirectly mapped nodedefs count:", len(indirect_mapped_nodedefs))
if len(indirect_mapped_nodedefs) > 0:
    print("Indirectly mapped nodedefs:")
    for ndef_name, impl in indirect_mapped_nodedefs.items():
        print(f"- nodedef: {ndef_name} -> implementation: {impl.getNamePath()}")

def getUnmappedImplementation(find_nodedef_name, indirect_mapped_nodedefs):
    if find_nodedef_name in indirect_mapped_nodedefs:
        return indirect_mapped_nodedefs[find_nodedef_name]
    return None

impls = stdlib.getImplementations()
for ndef in stdlib.getNodeDefs():
    ndef_name = ndef.getName()
    unmapped_impl = getUnmappedImplementation(ndef_name, indirect_mapped_nodedefs)
    if unmapped_impl:
        print(f"- found unmapped implementation {unmapped_impl.getNamePath()} for nodedef: {ndef_name}")


