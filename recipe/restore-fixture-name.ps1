$ErrorActionPreference = 'Stop'
# Windows archive extraction can decode this UTF-8 tar member as CP437.
# Restore only the known filename; keep upstream fixture bytes unchanged.
$directory = Join-Path $env:SRC_DIR 'tests/resources'
$name = [string][char]0x00C5 + ' ' + [char]0x00C9 + 'xample.txt'
$expected = Join-Path $directory $name
if (-not (Test-Path -LiteralPath $expected)) {
    $misdecoded = [string][char]0x251C + [char]0x00E0 + ' ' + [char]0x251C + [char]0x00EB + 'xample.txt'
    $source = Join-Path $directory $misdecoded
    if (-not (Test-Path -LiteralPath $source)) { throw 'Missing upstream Unicode filename fixture' }
    Move-Item -LiteralPath $source -Destination $expected
}
