#pragma once

struct LevelCollectibleInfo {
    std::string levelName;
    std::vector<std::pair<std::string, std::string>> steves;
    std::vector<std::pair<std::string, std::string>> berries;
    std::vector<std::pair<std::string, std::string>> bilbies;
    std::vector<std::pair<std::string, std::string>> orbs;
    std::vector<std::pair<std::string, std::string>> pictureFrames;
    std::vector<std::pair<std::string, std::string>> stones;

    LevelCollectibleInfo(
        const std::string& levelName,
        const std::vector<std::pair<std::string, std::string>>& steves,
        const std::vector<std::pair<std::string, std::string>>& berries,
        const std::vector<std::pair<std::string, std::string>>& bilbies,
        const std::vector<std::pair<std::string, std::string>>& orbs,
        const std::vector<std::pair<std::string, std::string>>& pictureFrames,
        const std::vector<std::pair<std::string, std::string>>& stones
    )
        : levelName(levelName),
        steves(steves),
        berries(berries),
        bilbies(bilbies),
        orbs(orbs),
        pictureFrames(pictureFrames),
        stones(stones)
    {
    }
};

const LevelCollectibleInfo NBInfo(
    "New Burramudgee",
    {
        {"Steve 1", "Inside the waterfall cave"},
    },
    {
        {"Gooboo Berry 5", "Northeast corner ledge"},
    },
    {
        {"Bilby 1", "Small ledge above Naomi's shop"},
        {"Bilby 2", "Top of tower in southwest section"},
        {"Bilby 23", "Small ledge beneath laundry"},
    },
    {
        {"Kromium Orb 8", "Behind the rock wall by the waterfall"},
        {"Kromium Orb 9", "Highest cliff"},
    },
    {
        {"Picture Frame 98", "Upper level back ledge of house across from rang shop"},
        {"Picture Frame 99", "Small ledge near see-saw"},
        {"Picture Frame 100", "Behind rock pillar near see-saw"},
        {"Picture Frame 101", "In the big tree"},
        {"Picture Frame 102", "In the thin tree near see-saw"},
        {"Picture Frame 103", "Under the large rock overhang"},
        {"Picture Frame 104", "Crate in the tree on the highest cliff"},
        {"Picture Frame 105", "Corner behind rang shop"},
        {"Picture Frame 106", "Beneath laundry"},
        {"Picture Frame 107", "On top of Gate"},
    },
    {
        {"Bunyip Stone 28", "Fire stone in rock wall by tree"},
        {"Bunyip Stone 29", "Multi stone on ledge above trailer"},
        {"Bunyip Stone 30", "Water stone in tree"},
    }
);

const LevelCollectibleInfo CCInfo(
    "Cinder Canyon",
    {
        {"Steve 1", "Inside the waterfall cave"},
    },
    {
        {"Gooboo Berry 1", "End of rail parkour"},
    },
    {
        {"Bilby 3", "Behind spiderwebs in north-center section"},
        {"Bilby 4", "Bushes by warp crystal in west section"},
        {"Bilby 34", "Bushes on upper ledge behind metal bridges"},
    },
    {
        {"Kromium Orb 1", "Spy Egg platforms"},
        {"Kromium Orb 2", "Invisible crate above the houses"},
        {"Kromium Orb 3", "Rock wall near metal bridges"},
        {"Kromium Orb 27", "Fan platforms near first uber frills"},
    },
    {
        {"Picture Frame 67", "Pillars in northwest section"},
        {"Picture Frame 68", "Ledge to the left of the entrance"},
        {"Picture Frame 69", "Fan platforms in west section"},
        {"Picture Frame 70", "Behind rock wall in southwest section"},
        {"Picture Frame 71", "Behind rock wall in southwest section"},
        {"Picture Frame 72", "Behind rock wall in southwest section"},
        {"Picture Frame 73", "Behind rock wall in southwest section"},
        {"Picture Frame 74", "Behind rock wall in southwest section"},
        {"Picture Frame 75", "Near crashed helicopter"},
        {"Picture Frame 76", "Beneath first rotating rock platform in Duke Escort"},
    },
    {
        {"Bunyip Stone 38", "Water stone from turkey"},
        {"Bunyip Stone 39", "Fire stone on ledge after houses"},
        {"Bunyip Stone 40", "Fire stone in rock wall at top of elevators"},
    }
);

const LevelCollectibleInfo SRDInfo(
    "Southern Rivers - Desert",
    {
        {"Steve 3", "Behind spiderwebs in Razorback Stream"},
    },
    {
        {"Gooboo Berry 2", "Behind crabs at All Your Base plane"},
    },
    {
        {"Bilby 24", "Lash Parkour in southwest corner"},
        {"Bilby 29", "On-foot parkour in central section"},
        {"Bilby 36", "Warp crystal behind houses in Razorback Stream"},
        {"Bilby 38", "Southeast corner in building with truck"},
    },
    {
        {"Kromium Orb 28", "Top of the loop south of New Burramudgee entrance"},
        {"Kromium Orb 29", "Floating fan platforms in Razorback Stream"},
        {"Kromium Orb 30", "Crab Parkour in east section"},
    },
    {},
    {
        {"Bunyip Stone 1", "Fire Stone from platforming in Rescue Julius arena"},
        {"Bunyip Stone 2", "Water Stone reward from Rescue Julius mission"},
        {"Bunyip Stone 14", "Fire Stone in Battle Arena Zeta parkour behind wall"},
        {"Bunyip Stone 14", "Shadow Stone reward for Battle Arena Zeta"},
        {"Bunyip Stone 19", "Ultra Stone reward for The Big Race mission"},
        {"Bunyip Stone 20", "Fire Stone reward for Experi Mental Cart mission"},
        {"Bunyip Stone 21", "Ultra Stone reward for Respect Effect mission"},
        {"Bunyip Stone 22", "Fire Stone reward for All Your Base mission"},
        {"Bunyip Stone 23", "Zoom Stone reward for Forest Firepower mission"},
        {"Bunyip Stone 27", "Shadow Stone reward for Dennis Dilemma mission"},
        {"Bunyip Stone 31", "Fire Stone given by Steve 3 in Razorback Stream"},
        {"Bunyip Stone 53", "Water Stone in rock pillar near All Your Base"},
        {"Bunyip Stone 54", "Water Stone on floating purple platform crab parkour near All Your Base"},
        {"Bunyip Stone 55", "Fire Stone on invisible platforms near Maurie in Razorback Stream"},
        {"Bunyip Stone 56", "Multi Stone at end of grind rail in Razorback Stream"},
    }
);

const LevelCollectibleInfo BBInfo(
    "Backwood Blizzard",
    {},
    {},
    {
        {"Bilby 6", "In a tree behind breakable wall in south-central section"},
        {"Bilby 7", "In a hole under the ice in northeast section"},
        {"Bilby 31", "On a rock in east section"},
        {"Bilby 32", "Lava platform in northwest section"},
    },
    {},
    {
        {"Picture Frame 77", "Metal crate under tree in center section"},
        {"Picture Frame 78", "Below Bilby 31"},
        {"Picture Frame 79", "Metal crate in northwest corner"},
        {"Picture Frame 80", "Metal crate in southeast section"},
        {"Picture Frame 81", "Metal crate in hole under ice in east gray area of map"},
        {"Picture Frame 82", "Metal crate under Bilby 6"},
    },
    {
        {"Bunyip Stone 17", "Fire Stone at end of lava platform timed parkour"},
        {"Bunyip Stone 18", "Water Stone from timed platforming"},
        {"Bunyip Stone 52", "Fire Stone top of fan platforms in southwest section"},
    }
);

const LevelCollectibleInfo DDMInfo(
    "Dead Dingo Marsh",
    {
        {"Steve 5", "West of Fluffy's fight pit"},
    },
    {
        {"Gooboo Berry 3", "End of lash parkour above river"},
    },
    {
        {"Bilby 9", "Hanging in a bush in southeast section"},
        {"Bilby 10", "Hanging in a tree above ladders on east side of river"},
        {"Bilby 13", "Hanging in a tree beneath invisible platform above river"},
    },
    {
        {"Kromium Orb 5", "Fenced-in area on east side of the river"},
        {"Kromium Orb 6", "On a platform in southeast corner"},
        {"Kromium Orb 7", "Rock ledges before bridge"},
        {"Kromium Orb 10", "Grind rails above broken down trucks"},
    },
    {
        {"Picture Frame 1", "Platform in middle of frogs after broken down trucks"},
        {"Picture Frame 2", "Metal crate before Bunyip Stone 3"},
        {"Picture Frame 3", "Metal crate before Bunyip Stone 3"},
        {"Picture Frame 4", "Metal crate before Bunyip Stone 3"},
        {"Picture Frame 5", "Metal crate before Bunyip Stone 3"},
        {"Picture Frame 6", "Metal crate before Bunyip Stone 3"},
        {"Picture Frame 7", "Underwater in center of river"},
        {"Picture Frame 8", "Pillar in center of river"},
        {"Picture Frame 9", "On top of invisible platform above the river"},
        {"Picture Frame 10", "On a rock in the river"},
        {"Picture Frame 11", "Beneath top ladder in Fluffy's fight pit"},
        {"Picture Frame 14", "Atop the pillars in the southwest section"},
        {"Picture Frame 15", "Floating fan platform near Fluffy's fight pit"},
        {"Picture Frame 16", "Middle of the lash parkour in southeast area"},
        {"Picture Frame 17", "On a platform in southeast corner"},
        {"Picture Frame 116", "Invisible crate near Fluffy's fight pit"},
        {"Picture Frame 117", "Invisible crate near Fluffy's fight pit"},
        {"Picture Frame 118", "Invisible crate near Fluffy's fight pit"},
        {"Picture Frame 119", "Invisible crate at the top of the ladders on east side of river"},
        {"Picture Frame 120", "Invisible crate at the top of the ladders on east side of river"},
    },
    {
        {"Bunyip Stone 3", "Earth Stone at end of lash/invisible platform parkour"},
        {"Bunyip Stone 4", "Water Stone given by Steve 5"},
        {"Bunyip Stone 5", "Mega Stone on moving invisible platforms before bridge"},
        {"Bunyip Stone 57", "Water Stone reward for catching the turkey"},
    }
);

const LevelCollectibleInfo SRSInfo(
    "Southern Rivers Swamp",
    {
        {"Steve 6", "Center island in Pippy Beach"},
    },
    {
        {"Gooboo Berry 7", "Behind breakable wood past Dead Dingo Marsh"},
        {"Gooboo Berry 8", "On top of Parrotbeard's shop in Pippy Beach"},
    },
    {
        {"Bilby 25", "Hanging off the edge of the cliff near Parrotbeard's shop in Pippy Beach"},
        {"Bilby 26", "In the trees on west Pippy Beach raised area"},
        {"Bilby 27", "On top of the east plane in Pippy Beach"},
        {"Bilby 37", "Hanging from tree by airship in southwest corner"},
    },
    {
        {"Kromium Orb 18", "Tiny island in northeast corner of Pippy Beach"},
        {"Kromium Orb 19", "Underwater in Platypus Cove"},
        {"Kromium Orb 20", "On top of plane in northeast corner of Pippy Beach"},
    },
    {
        {"Picture Frame 83", "In bushes south of Pippy Beach entrance"},
        {"Picture Frame 84", "In a bush by the bridge at first river crossing"},
        {"Picture Frame 85", "In bushes to the left at first river crossing"},
        {"Picture Frame 86", "Beneath land bridge in west side of Pippy Beach"},
        {"Picture Frame 87", "Wooden maze at first river crossing"},
        {"Picture Frame 88", "Right landmass after first water section in Pippy Beach"},
        {"Picture Frame 89", "On top of first land bridge in Pippy Beach"},
        {"Picture Frame 90", "Pillar to the right of first water section in Pippy Beach"},
        {"Picture Frame 91", "Bushes on west side of Platypus Cove"},
        {"Picture Frame 92", "Bushes in southeast corner"},
        {"Picture Frame 93", "In bushes beside Cassopolis entrance"},
        {"Picture Frame 94", "Bushes in southeast corner"},
        {"Picture Frame 95", "bushes in Pippy Beach"},
        {"Picture Frame 96", "Top of west side ship in Pippy Beach"},
        {"Picture Frame 97", "Top of dropship in far east section"},
    },
    {
        {"Bunyip Stone 9", "Water Stone at end of platforming in Battle Arena Gamma"},
        {"Bunyip Stone 10", "Air Stone reward for Battle Arena Gamma mission"},
        {"Bunyip Stone 24", "Earth Stone reward for Demolition Derby mission"},
        {"Bunyip Stone 25", "Earth Stone reward for Redback Stash mission"},
        {"Bunyip Stone 26", "Ultra Stone reward for Aero Coast Guard"},
        {"Bunyip Stone 32", "Zoom Stone given by Steve 6"},
        {"Bunyip Stone 33", "Air Stone in southwest corner behind breakable walls"},
        {"Bunyip Stone 34", "Warp Stone in wooden maze at first river crossing"},
        {"Bunyip Stone 35", "Magnet Stone at end of Platypus Cove crab parkour"},
        {"Bunyip Stone 36", "Chrono Stone at end of southeast section crab parkour"},
        {"Bunyip Stone 37", "Multi Stone underwater in river outside Cassopolis"},
    }
);

const LevelCollectibleInfo CassInfo(
    "Cassopolis",
    {},
    {
        {"Gooboo Berry 9", "Above the entrance to Cass' throne"},
    },
    {
        {"Bilby 14", "Hanging under concrete in front of rang shop"},
        {"Bilby 15", "Middle of timed parkour"},
        {"Bilby 33", "Behind crates above grandpa"},
    },
    {
        {"Kromium Orb 11", "Boost panel trampoline chain"},
        {"Kromium Orb 12", "Platforms opened by hitting all 5 red buttons"},
    },
    {
        {"Picture Frame 12", "Metal crate under Kromium Orb 11"},
        {"Picture Frame 13", "Metal crate by bilby 33"},
        {"Picture Frame 108", "Metal crate in front of rang shop"},
        {"Picture Frame 109", "Metal crate at rang shop entrance"},
        {"Picture Frame 110", "Metal crate behind shipping containers"},
        {"Picture Frame 111", "Metal crate at end of timed parkour"},
        {"Picture Frame 112", "Metal crate near dinosuar costume guy"},
        {"Picture Frame 113", "Middle of timed parkour"},
        {"Picture Frame 114", "Metal crate at top of the ladder on the right in Cy's room"},
        {"Picture Frame 115", "Metal crate on back wall at top of ladders in Cy's room"},
    },
    {
        {"Bunyip Stone 49", "Water Stone at end of lash into portal parkour"},
        {"Bunyip Stone 50", "Ultra Stone at top of platforming above grandpa"},
        {"Bunyip Stone 51", "Warp Stone at end of timed parkour"},
    }
);

const LevelCollectibleInfo WWInfo(
    "Winter Woods",
    {},
    {},
    {
        {"Bilby 5", "Hanging from root above lava platform in center of map"},
        {"Bilby 8", "Branch on top of ice blocks behind large ice wall"},
        {"Bilby 19", "North lava patch platform"},
        {"Bilby 40", "Under ice bridge on southwest section behind large ice wall"},
    },
    {},
    {
        {"Picture Frame 33", "North lava patch purple platforms"},
        {"Picture Frame 34", "Center lava tube"},
        {"Picture Frame 35", "Center lava tube"},
        {"Picture Frame 36", "Center lava tube"},
        {"Picture Frame 37", "South lava tube"},
        {"Picture Frame 38", "South lava tube"},
        {"Picture Frame 39", "South lava tube"},
        {"Picture Frame 40", "First collapsible bridge in southeast corner"},
        {"Picture Frame 41", "Second collapsible bridge in southeast corner"},
        {"Picture Frame 42", "North lava patch purple platforms"},
    },
    {
        {"Bunyip Stone 46", "Earth Stone in center lava tube"},
        {"Bunyip Stone 47", "Mega Stone under ice blocks behind large ice wall"},
        {"Bunyip Stone 48", "Zoom Stone in south lava tube"},
    }
);

const LevelCollectibleInfo KBIInfo(
    "Kaka Boom Island",
    {
        {"Steve 2", "Behind rock wall at start"},
    },
    {
        {"Gooboo Berry 6", "Behind rock wall at start"},
    },
    {
        {"Bilby 20", "Hanging from tree above invisible crate behind the start"},
        {"Bilby 21", "Treading water in northeast corner"},
        {"Bilby 22", "Behind rock wall at start"},
    },
    {
        {"Kromium Orb 16", "Underwater on south shore"},
        {"Kromium Orb 17", "Underwater in south corner of end area"},
        {"Kromium Orb 21", "Waterfall pool"},
        {"Kromium Orb 22", "Invisible platform at start"},
    },
    {
        {"Picture Frame 18", "Underwater in the corner behind start"},
        {"Picture Frame 19", "Sitting on an island near lava in end area"},
        {"Picture Frame 20", "Bushes north of center volcano"},
        {"Picture Frame 21", "Bushes in southwest corner of end area"},
        {"Picture Frame 22", "Middle of lava in end area"},
        {"Picture Frame 23", "Underwater in sunken plane in end area"},
        {"Picture Frame 24", "By dunny before spiky roller traps"},
        {"Picture Frame 25", "Underwater straight from start"},
        {"Picture Frame 26", "Underwater in southwest corner"},
        {"Picture Frame 27", "Underwater in northwest corner of end area"},
        {"Picture Frame 28", "Invisible crate behind start"},
        {"Picture Frame 29", "Invisible crate behind start"},
        {"Picture Frame 30", "Invisible crate behind start"},
        {"Picture Frame 31", "Invisible crate behind start"},
        {"Picture Frame 32", "Invisible crate behind start"},
    },
    {
        {"Bunyip Stone 6", "Air Stone at end area floating in the air"},
        {"Bunyip Stone 7", "Magnet Stone underwater on south shore"},
        {"Bunyip Stone 8", "Earth Stone at end area floating above lava"},
    }
);

const LevelCollectibleInfo GGInfo(
    "Gooboo Gully",
    {},
    {
        {"Gooboo Berry 10", "End of twisting platform parkour above river"},
    },
    {
        {"Bilby 28", "Crevice in west side"},
        {"Bilby 29", "Under log at turn leading to bridge"},
        {"Bilby 30", "Hanging from branch near falling boulders"},
    },
    {
        {"Kromium Orb 23", "On top of Steve's House"},
        {"Kromium Orb 24", "Behind twisty block south at first turn"},
        {"Kromium Orb 25", "Fenced area after lash slide"},
        {"Kromium Orb 26", "Invisible crate outside fence where Kromium Orb 25 is"},
    },
    {
        {"Picture Frame 43", "End of falling boulders section"},
        {"Picture Frame 44", "Second crevice in falling boulders section"},
        {"Picture Frame 45", "Underwater crate near Kromium Orb 25"},
        {"Picture Frame 46", "Underwater crate near Kromium Orb 25"},
        {"Picture Frame 47", "Moving platform over river"},
        {"Picture Frame 48", "Moving platform over river"},
        {"Picture Frame 49", "Platform above Frames 47 and 48"},
        {"Picture Frame 50", "First crevice in falling boulders section"},
        {"Picture Frame 51", "Third crevice in falling boulders section"},
    },
    {
        {"Bunyip Stone 11", "Fire Stone behind Kromium Orb 24"},
        {"Bunyip Stone 12", "Ultra Stone behind timed gate at end"},
        {"Bunyip Stone 13", "Zoom Stone behind timed gate at end"},
    }
);

const LevelCollectibleInfo MBBInfo(
    "Mount Boom Basin",
    {
        {"Steve 4", "Southeast lava area"},
    },
    {
        {"Gooboo Berry 4", "Behind spiderwebs before 3rd turret"},
    },
    {
        {"Bilby 16", "Bounce shrooms to platform"},
        {"Bilby 17", "Behind first turret"},
        {"Bilby 18", "Bushes behind plane at start"},
    },
    {
        {"Kromium Orb 4", "Frog arena behind spiderwebs"},
        {"Kromium Orb 13", "Moving platforms in first lavaquin area"},
        {"Kromium Orb 14", "Behind rock wall after second turret"},
        {"Kromium Orb 15", "In southeast lava area"},
    },
    {
        {"Picture Frame 52", "Metal crates near start"},
        {"Picture Frame 53", "Metal crates near start"},
        {"Picture Frame 54", "Metal crates near start"},
        {"Picture Frame 55", "Metal crates near start"},
        {"Picture Frame 56", "Invisible crate after 2nd turret"},
        {"Picture Frame 57", "Invisible crate after 2nd turret"},
        {"Picture Frame 58", "Invisible crate after 3rd turret"},
        {"Picture Frame 59", "Invisible crate after 3rd turret"},
        {"Picture Frame 60", "Invisible crate in first lavaquin area"},
        {"Picture Frame 61", "Invisible crate in first lavaquin area"},
    },
    {
        {"Bunyip Stone 41", "Warp Stone given by Steve 4"},
        {"Bunyip Stone 42", "Chrono Stone behind spiderwebs"},
        {"Bunyip Stone 43", "Fire Stone across lava at end"},
    }
);

const LevelCollectibleInfo FFInfo(
    "Frozen Forests",
    {},
    {},
    {
        {"Bilby 11", "West platform in main area"},
        {"Bilby 12", "East side Grav Grenade platform to cliff"},
        {"Bilby 35", "North lava river platforms"},
    },
    {},
    {
        {"Picture Frame 62", "West lava area"},
        {"Picture Frame 63", "West lava area"},
        {"Picture Frame 64", "West lava area"},
        {"Picture Frame 65", "West lava area"},
        {"Picture Frame 66", "West lava area"},
    },
    {
        {"Bunyip Stone 16", "Shadow Stone reward from Ranger Endanger mission"},
        {"Bunyip Stone 44", "Magnet Stone above ice block tower"},
        {"Bunyip Stone 45", "Water Stone on central platform"},
    }
);