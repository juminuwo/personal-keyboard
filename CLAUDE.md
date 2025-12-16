# Personal Keyboard Project

A custom split ergonomic keyboard designed with Ergogen, to be finalized in KiCad.

## Project Status

- [x] Basic layout design (key positions, stagger, thumb clusters)
- [x] Zone definitions (left/right matrix, thumb clusters)
- [x] Switch footprints (Choc hotswap)
- [ ] Outline refinement (currently rough)
- [ ] MCU footprint placement
- [ ] TRRS jack for split communication
- [ ] PCB routing
- [ ] Mounting holes

## Layout Overview

**33-key split layout**

| Side  | Matrix Keys | Thumb Keys | Total |
|-------|-------------|------------|-------|
| Left  | 15 (5x3)    | 2          | 17    |
| Right | 14 (5x3-1)  | 2          | 16    |

Right pinky top key is skipped for a reduced pinky column.

## Key Files

- `keyboard.yaml` - Main Ergogen configuration

## Build Commands

```bash
# Generate outputs with Ergogen
ergogen keyboard.yaml -o output

# Generated files will be in:
# output/points/     - Key position data
# output/outlines/   - DXF/SVG plate files
# output/pcbs/       - KiCad PCB files
```

## Technical Details

### Units
- Key spacing X (kx): 17mm
- Key spacing Y (ky): 16mm
- Key padding: 1.5kx (25.5mm)

### Column Stagger (Left)
- Pinky: 0mm (baseline)
- Ring: +5mm
- Middle: +2.5mm
- Index: -2.5mm
- Inner: -2.5mm

### Thumb Cluster
- Anchored below index finger
- Two keys with splay (-10/-5 deg left, +10/+5 deg right)
- Offset 27mm below matrix

### Switches
- Kailh Choc low-profile
- Hotswap sockets
- Reversible PCB design

### Nets
Left side: L_C0-L_C4 (columns), L_T0-L_T1 (thumbs), L_R0-L_R3 (rows)
Right side: R_C0-R_C4 (columns), R_T0-R_T1 (thumbs), R_R0-R_R3 (rows)

Currently wired as direct-pin (column to GND) - will need diodes for proper matrix scanning.

## TODO

1. **Outline refinement** - Clean up polygon vertices, ensure proper clearances
2. **Add MCU footprint** - Likely Pro Micro or nice!nano compatible
3. **Add TRRS jack** - For split halves communication (or use wireless)
4. **Add diodes** - Convert from direct-pin to proper matrix wiring
5. **Add reset button** - For flashing firmware
6. **Mounting holes** - For case attachment
7. **PCB routing** - Complete traces in KiCad after export
8. **Power switch** - If using wireless/battery

## References

- [Ergogen Documentation](https://docs.ergogen.xyz/)
- [Choc Switch Specs](https://github.com/keyboardio/keyswitch_documentation)
