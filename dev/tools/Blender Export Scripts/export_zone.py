import bpy
import mathutils

outputFile = open('export_zone_output.txt', 'w')

#for mesh in bpy.data.meshes:
mesh = bpy.context.active_object.to_mesh(bpy.context.scene, True, 'PREVIEW')

numOfFaces = len(mesh.polygons)

for faceIndex in range(0, numOfFaces):
    v1 = (  mesh.vertices[mesh.polygons[faceIndex].vertices[0]].co.x * 10, 
            mesh.vertices[mesh.polygons[faceIndex].vertices[0]].co.y * 10, 
            mesh.vertices[mesh.polygons[faceIndex].vertices[0]].co.z * 10 )
            
    v2 = (  mesh.vertices[mesh.polygons[faceIndex].vertices[1]].co.x * 10, 
            mesh.vertices[mesh.polygons[faceIndex].vertices[1]].co.y * 10, 
            mesh.vertices[mesh.polygons[faceIndex].vertices[1]].co.z * 10 )
            
    v3 = (  mesh.vertices[mesh.polygons[faceIndex].vertices[2]].co.x * 10, 
            mesh.vertices[mesh.polygons[faceIndex].vertices[2]].co.y * 10, 
            mesh.vertices[mesh.polygons[faceIndex].vertices[2]].co.z * 10 )
    
    normal = ( mesh.polygons[faceIndex].normal.x, mesh.polygons[faceIndex].normal.y, mesh.polygons[faceIndex].normal.z )
    
    uv1 = mesh.tessface_uv_textures.active.data[faceIndex].uv1
    uv2 = mesh.tessface_uv_textures.active.data[faceIndex].uv2
    uv3 = mesh.tessface_uv_textures.active.data[faceIndex].uv3

    texName = mesh.tessface_uv_textures.active.data[faceIndex].image.filepath

    print( v1, v2, v3, normal, uv1, uv2, uv3, texName )
    
    outputFile.write( "\t\ttexTriangle\n" )
    outputFile.write( "\t\t\tvert0\t\t" + str( round(v1[0], 4) ) + " " + str( round(v1[1], 4) ) + " " + str( round(v1[2], 4) ) + '\n')
    outputFile.write( "\t\t\tvert0Tex\t" + str( round(uv1[0], 4) ) + " " + str( round(uv1[1], 4) ) + '\n')
    outputFile.write( "\t\t\tvert1\t\t" + str( round(v2[0], 4) ) + " " + str( round(v2[1], 4) ) + " " + str( round(v2[2], 4) ) + '\n')
    outputFile.write( "\t\t\tvert1Tex\t" + str( round(uv2[0], 4) ) + " " + str( round(uv2[1], 4) ) + '\n')
    outputFile.write( "\t\t\tvert2\t\t" + str( round(v3[0], 4) ) + " " + str( round(v3[1], 4) ) + " " + str( round(v3[2], 4) ) + '\n')
    outputFile.write( "\t\t\tvert2Tex\t" + str( round(uv3[0], 4) ) + " " + str( round(uv3[1], 4) ) + '\n')
    outputFile.write( "\t\t\tnormal\t\t" + str( round(normal[0], 4) ) + " " + str( round(normal[1], 4) ) + " " + str( round(normal[2], 4) ) + '\n')
    outputFile.write( "\t\t/texTriangle\n" )

outputFile.close()
#for poly in mesh.polygons:
#    for vi in poly.vertices:
#        vc = mesh.vertices[vi].co
#        print( "CO:", vc.x, vc.y, vc.z )
#    break
#
#uv1 = mesh.tessface_uv_textures.active.data[0].uv1
#uv2 = mesh.tessface_uv_textures.active.data[0].uv2
#uv3 = mesh.tessface_uv_textures.active.data[0].uv3
#print (uv1, uv2, uv3 )