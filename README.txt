** Building **

python setup.py build

or for py3k

python3 setup.py build


** Module setup **

OpenVG:
       VG:
           Functions:
               get_error
                   -- vgGetError
               get_string
                   -- vgGetString
               hardware_query
                   -- vgHardwareQuery

           Classes:
               VGContext:
                   Attributes:
                       [VGParamType]
                           -- vgGet{i,f,v}(VGParamType)
                              vgSet{i,f,v}(value, VGParamType)
                       paint_fill
                           -- vgGetPaint(VG_FILL_PATH)
                              vgSetPaint(VGPaint, VG_FILL_PATH)
                       paint_stroke
                           -- vgGetPaint(VG_FILL_STROKE)
                              vgSetPaint(VGPaint, VG_FILL_STROKE)
                   Functions:
                       clear
                           -- vgClear
                       copy_pixels
                           -- vgCopyPixels
                       finish
                           -- vgFinish
                       flush
                           -- vgFlush
                       get_matrix
                           -- vgGetMatrix
                       get_pixels
                           -- vgGetPixels
                       load_identity
                           -- vgLoadIdentity
                       load_matrix
                           -- vgLoadMatrix
                       mask
                           -- vgMask
                       mult_matrix
                           -- vgMultMatrix
                       read_pixels
                           -- vgReadPixels
                       resize
                           -- vgResize
                       rotate
                           -- vgRotate
                       scale
                           -- vgScale
                       set_pixels
                           -- vgSetPixels
                       shear
                           -- vgShear
                       translate
                           -- vgTranslate
                       write_pixels
                           -- vgWritePixels

               VGImage:
                   Attributes:
                       [VGImageParamType]
                           -- vgGetParameter{i,f,v}(VGImageParamType)
                              vgSetParameter{i,f,v}(value, VGImageParamType)
                   Functions:
                       child
                           -- vgChildImage
                       clear
                           -- vgClearImage
                       color_matrix
                           -- vgColorMatrix
                       convolve
                           -- vgConvolve
                       copy
                           -- vgCopyImage
                       draw
                           -- vgDrawImage
                       gaussian_blur
                           -- vgGaussianBlur
                       get_sub_data
                           -- vgGetImageSubData
                       lookup
                           -- vgLookup
                       lookup_single
                           -- vgLookupSingle
                       parent
                           -- vgGetParent
                       separable_convolve
                           -- vgSeparableConvolve
                       set_sub_data
                           -- vgImageSubData

               VGPaint:
                   Attributes:
                       [VGPaintParamType]
                           -- vgGetParameter{i,f,v}(VGPaintParamType)
                              vgSetParameter{i,f,v}(value, VGPaintParamType)
                       color
                           -- vgGetColor
                              vgSetColor
                   Functions:
                       pattern
                           -- vgPaintPattern

               VGPath:
                   Attributes:
                       [VGPathParamType]
                           -- vgGetParameter{i,f,v}(VGPathParamType)
                              vgSetParameter{i,f,v}(value, VGPathParamType)
                   Functions:
                       append
                           -- vgAppendPath
                       append_data
                           -- vgAppendPathData
                       bounds
                           -- vgPathBounds
                       capabilities
                           -- vgGetPathCapabilities
                       capabilities_remove
                           -- vgRemovePathCapabilities
                       clear
                           -- vgClearPath
                       draw
                           -- vgDrawPath
                       interpolate
                           -- vgInterpolatePath
                       length
                           -- vgPathLength
                       modify_coords
                           -- vgModifyPathCoords
                       point_along_path
                           -- vgPointAlongPath
                       transform
                           -- vgTransformPath
                       transformed_bounds
                           -- vgPathTransformedBounds

           Enumerations:
               VGBlendMode
               VGCapStyle
               VGColorRampSpreadMode
               VGErrorCode
               VGFillRule
               VGHardwareQueryResult
               VGHardwareQueryType
               VGImageChannel
               VGImageFormat
               VGImageMode
               VGImageParamType
               VGImageQuality
               VGJoinStyle
               VGMaskOperation
               VGMatrixMode
               VGPaintMode
               VGPaintParamType
               VGPaintType
               VGParamType
               VGPathAbsRel
               VGPathCapabilities
               VGPathCommand
               VGPathDatatype
               VGPathParamType
               VGPathSegment
               VGPixelLayout
               VGRenderingQuality
               VGStringID
               VGTilingMode

       VGU:
           Functions:
               arc
                   -- vguArc
               compute_warp_quad_to_quad
                   -- vguComputeWarpQuadToQuad
               compute_warp_quad_to_sphere
                   -- vguComputeWarpQuadToSquare
               compute_warp_square_to_quad
                   -- vguComputeWarpSquareToQuad
               ellipse
                   -- vguEllipse
               line
                   -- vguLine
               polygon
                   -- vguPolygon
               rect
                   -- vguRect
               round_rect
                   -- vguRoundRect

