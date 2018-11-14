# Seeds

Utility to generate the seeds.txt list that is compiled into the client
(see [src/chainparamsseeds.h](/src/chainparamsseeds.h) and other utilities in [contrib/seeds](/contrib/seeds)).

Be sure to update `PATTERN_AGENT` in `makeseeds.py` to include the current version,
and remove old versions as necessary.

The seeds compiled into the release are created from fuzzbawls' DNS seed data, like this:

    Create seed text files for nodes_main.txt and nodes_test.txt and copy into this folder (ittrium/contrib/seeds)
    python3 generate-seeds.py . > ../../src/chainparamsseeds.h

## Dependencies

Ubuntu:

    sudo apt-get install python3-dnspython
