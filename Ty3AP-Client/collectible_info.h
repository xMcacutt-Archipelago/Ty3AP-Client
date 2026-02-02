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
        {"Steve", "Inside the waterfall cave"},
    },
    {
        {"Gooboo Berry", "Northeast corner ledge"},
    },
    {
        {"Bilby 1", "Small ledge above Naomi's shop"},
        {"Bilby 2", "Top of tower in southwest section"},
        {"Bilby 3", "Small ledge beneath laundry"},
    },
    {
        {"Kromium Orb 1", "Behind the rock wall by the waterfall"},
        {"Kromium Orb 2", "Highest cliff"},
    },
    {
        {"Picture Frame 1", "Upper level back ledge of house across from rang shop"},
        {"Picture Frame 2", "Small ledge near see-saw"},
        {"Picture Frame 3", "Behind rock pillar near see-saw"},
        {"Picture Frame 4", "In the big tree"},
        {"Picture Frame 5", "In the thin tree near see-saw"},
        {"Picture Frame 6", "Under the large rock overhang"},
        {"Picture Frame 7", "Crate in the tree on the highest cliff"},
        {"Picture Frame 8", "Corner behind rang shop"},
        {"Picture Frame 9", "Beneath laundry"},
        {"Picture Frame 10", "On top of Gate"},
    },
    {
        {"Bunyip Stone 1", "Fire stone in rock wall by tree"},
        {"Bunyip Stone 2", "Multi stone on ledge above trailer"},
        {"Bunyip Stone 3", "Water stone in tree"},
    }
);

const LevelCollectibleInfo CCInfo(
    "Cinder Canyon",
    {
        {"Steve", "Inside the waterfall cave"},
    },
    {
        {"Gooboo Berry", "End of rail parkour"},
    },
    {
        {"Bilby 1", "Behind spiderwebs in north-center section"},
        {"Bilby 2", "Bushes by warp crystal in west section"},
        {"Bilby 3", "Bushes on upper ledge behind metal bridges"},
    },
    {
        {"Kromium Orb 1", "Spy Egg platforms"},
        {"Kromium Orb 2", "Invisible crate above the houses"},
        {"Kromium Orb 3", "Rock wall near metal bridges"},
        {"Kromium Orb 4", "Fan platforms near first uber frills"},
    },
    {
        {"Picture Frame 1", "Pillars in northwest section"},
        {"Picture Frame 2", "Ledge to the left of the entrance"},
        {"Picture Frame 3", "Fan platforms in west section"},
        {"Picture Frame 4", "Behind rock wall in southwest section"},
        {"Picture Frame 5", "Behind rock wall in southwest section"},
        {"Picture Frame 6", "Behind rock wall in southwest section"},
        {"Picture Frame 7", "Behind rock wall in southwest section"},
        {"Picture Frame 8", "Behind rock wall in southwest section"},
        {"Picture Frame 9", "Near crashed helicopter"},
        {"Picture Frame 10", "Beneath first rotating rock platform in Duke Escort"},
    },
    {
        {"Bunyip Stone 1", "Water stone from turkey"},
        {"Bunyip Stone 2", "Fire stone on ledge after houses"},
        {"Bunyip Stone 3", "Fire stone in rock wall at top of elevators"},
    }
);

const LevelCollectibleInfo SRDInfo(
    "Southern Rivers - Desert",
    {
        {"Steve", "Behind spiderwebs in Razorback Stream"},
    },
    {
        {"Gooboo Berry", "Behind crabs at All Your Base plane"},
    },
    {
        {"Bilby 1", "Lash Parkour in southwest corner"},
        {"Bilby 2", "On-foot parkour in central section"},
        {"Bilby 3", "Warp crystal behind houses in Razorback Stream"},
        {"Bilby 4", "Southeast corner in building with truck"},
    },
    {
        {"Kromium Orb 1", "Top of the loop south of New Burramudgee entrance"},
        {"Kromium Orb 2", "Floating fan platforms in Razorback Stream"},
        {"Kromium Orb 3", "Crab Parkour in east section"},
    },
    {},
    {
        {"Bunyip Stone 1", "Fire Stone from platforming in Rescue Julius arena"},
        {"Bunyip Stone 2", "Water Stone reward from Rescue Julius mission"},
        {"Bunyip Stone 3", "Fire Stone in Battle Arena Zeta parkour behind wall"},
        {"Bunyip Stone 4", "Shadow Stone reward for Battle Arena Zeta"},
        {"Bunyip Stone 5", "Ultra Stone reward for The Big Race mission"},
        {"Bunyip Stone 6", "Fire Stone reward for Experi Mental Cart mission"},
        {"Bunyip Stone 7", "Ultra Stone reward for Respect Effect mission"},
        {"Bunyip Stone 8", "Fire Stone reward for All Your Base mission"},
        {"Bunyip Stone 9", "Zoom Stone reward for Forest Firepower mission"},
        {"Bunyip Stone 10", "Shadow Stone reward for Dennis Dilemma mission"},
        {"Bunyip Stone 11", "Fire Stone given by Steve 3 in Razorback Stream"},
        {"Bunyip Stone 12", "Water Stone in rock pillar near All Your Base"},
        {"Bunyip Stone 13", "Water Stone on floating purple platform crab parkour near All Your Base"},
        {"Bunyip Stone 14", "Fire Stone on invisible platforms near Maurie in Razorback Stream"},
        {"Bunyip Stone 15", "Multi Stone at end of grind rail in Razorback Stream"},
    }
);

const LevelCollectibleInfo BBInfo(
    "Backwood Blizzard",
    {},
    {},
    {
        {"Bilby 1", "In a tree behind breakable wall in south-central section"},
        {"Bilby 2", "In a hole under the ice in northeast section"},
        {"Bilby 3", "On a rock in east section"},
        {"Bilby 4", "Lava platform in northwest section"},
    },
    {},
    {
        {"Picture Frame 1", "Metal crate under tree in center section"},
        {"Picture Frame 2", "Below Bilby 31"},
        {"Picture Frame 3", "Metal crate in northwest corner"},
        {"Picture Frame 4", "Metal crate in southeast section"},
        {"Picture Frame 5", "Metal crate in hole under ice in east gray area of map"},
        {"Picture Frame 6", "Metal crate under Bilby 6"},
    },
    {
        {"Bunyip Stone 1", "Fire Stone at end of lava platform timed parkour"},
        {"Bunyip Stone 2", "Water Stone from timed platforming"},
        {"Bunyip Stone 3", "Fire Stone top of fan platforms in southwest section"},
    }
);

const LevelCollectibleInfo DDMInfo(
    "Dead Dingo Marsh",
    {
        {"Steve", "West of Fluffy's fight pit"},
    },
    {
        {"Gooboo Berry", "End of lash parkour above river"},
    },
    {
        {"Bilby 1", "Hanging in a bush in southeast section"},
        {"Bilby 2", "Hanging in a tree above ladders on east side of river"},
        {"Bilby 3", "Hanging in a tree beneath invisible platform above river"},
    },
    {
        {"Kromium Orb 1", "Fenced-in area on east side of the river"},
        {"Kromium Orb 2", "On a platform in southeast corner"},
        {"Kromium Orb 3", "Rock ledges before bridge"},
        {"Kromium Orb 4", "Grind rails above broken down trucks"},
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
        {"Picture Frame 18", "Invisible crate near Fluffy's fight pit"},
        {"Picture Frame 19", "Invisible crate near Fluffy's fight pit"},
        {"Picture Frame 20", "Invisible crate near Fluffy's fight pit"},
        {"Picture Frame 21", "Invisible crate at the top of the ladders on east side of river"},
        {"Picture Frame 22", "Invisible crate at the top of the ladders on east side of river"},
    },
    {
        {"Bunyip Stone 1", "Earth Stone at end of lash/invisible platform parkour"},
        {"Bunyip Stone 2", "Water Stone given by Steve 5"},
        {"Bunyip Stone 3", "Mega Stone on moving invisible platforms before bridge"},
        {"Bunyip Stone 4", "Water Stone reward for catching the turkey"},
    }
);

const LevelCollectibleInfo SRSInfo(
    "Southern Rivers Swamp",
    {
        {"Steve", "Center island in Pippy Beach"},
    },
    {
        {"Gooboo Berry 1", "Behind breakable wood past Dead Dingo Marsh"},
        {"Gooboo Berry 2", "On top of Parrotbeard's shop in Pippy Beach"},
    },
    {
        {"Bilby 1", "Hanging off the edge of the cliff near Parrotbeard's shop in Pippy Beach"},
        {"Bilby 2", "In the trees on west Pippy Beach raised area"},
        {"Bilby 3", "On top of the east plane in Pippy Beach"},
        {"Bilby 4", "Hanging from tree by airship in southwest corner"},
    },
    {
        {"Kromium Orb 1", "Tiny island in northeast corner of Pippy Beach"},
        {"Kromium Orb 2", "Underwater in Platypus Cove"},
        {"Kromium Orb 3", "On top of plane in northeast corner of Pippy Beach"},
    },
    {
        {"Picture Frame 1", "In bushes south of Pippy Beach entrance"},
        {"Picture Frame 2", "In a bush by the bridge at first river crossing"},
        {"Picture Frame 3", "In bushes to the left at first river crossing"},
        {"Picture Frame 4", "Beneath land bridge in west side of Pippy Beach"},
        {"Picture Frame 5", "Wooden maze at first river crossing"},
        {"Picture Frame 6", "Right landmass after first water section in Pippy Beach"},
        {"Picture Frame 7", "On top of first land bridge in Pippy Beach"},
        {"Picture Frame 8", "Pillar to the right of first water section in Pippy Beach"},
        {"Picture Frame 9", "Bushes on west side of Platypus Cove"},
        {"Picture Frame 10", "Bushes in southeast corner"},
        {"Picture Frame 11", "In bushes beside Cassopolis entrance"},
        {"Picture Frame 12", "Bushes in southeast corner"},
        {"Picture Frame 13", "bushes in Pippy Beach"},
        {"Picture Frame 14", "Top of west side ship in Pippy Beach"},
        {"Picture Frame 15", "Top of dropship in far east section"},
    },
    {
        {"Bunyip Stone 1", "Water Stone at end of platforming in Battle Arena Gamma"},
        {"Bunyip Stone 2", "Air Stone reward for Battle Arena Gamma mission"},
        {"Bunyip Stone 3", "Earth Stone reward for Demolition Derby mission"},
        {"Bunyip Stone 4", "Earth Stone reward for Redback Stash mission"},
        {"Bunyip Stone 5", "Ultra Stone reward for Aero Coast Guard"},
        {"Bunyip Stone 6", "Zoom Stone given by Steve 6"},
        {"Bunyip Stone 7", "Air Stone in southwest corner behind breakable walls"},
        {"Bunyip Stone 8", "Warp Stone in wooden maze at first river crossing"},
        {"Bunyip Stone 9", "Magnet Stone at end of Platypus Cove crab parkour"},
        {"Bunyip Stone 10", "Chrono Stone at end of southeast section crab parkour"},
        {"Bunyip Stone 11", "Multi Stone underwater in river outside Cassopolis"},
    }
);

const LevelCollectibleInfo CassInfo(
    "Cassopolis",
    {},
    {
        {"Gooboo Berry", "Above the entrance to Cass' throne"},
    },
    {
        {"Bilby 1", "Hanging under concrete in front of rang shop"},
        {"Bilby 2", "Middle of timed parkour"},
        {"Bilby 3", "Behind crates above grandpa"},
    },
    {
        {"Kromium Orb 1", "Boost panel trampoline chain"},
        {"Kromium Orb 2", "Platforms opened by hitting all 5 red buttons"},
    },
    {
        {"Picture Frame 1", "Metal crate under Kromium Orb 11"},
        {"Picture Frame 2", "Metal crate by bilby 33"},
        {"Picture Frame 3", "Metal crate in front of rang shop"},
        {"Picture Frame 4", "Metal crate at rang shop entrance"},
        {"Picture Frame 5", "Metal crate behind shipping containers"},
        {"Picture Frame 6", "Metal crate at end of timed parkour"},
        {"Picture Frame 7", "Metal crate near dinosuar costume guy"},
        {"Picture Frame 8", "Middle of timed parkour"},
        {"Picture Frame 9", "Metal crate at top of the ladder on the right in Cy's room"},
        {"Picture Frame 10", "Metal crate on back wall at top of ladders in Cy's room"},
    },
    {
        {"Bunyip Stone 1", "Water Stone at end of lash into portal parkour"},
        {"Bunyip Stone 2", "Ultra Stone at top of platforming above grandpa"},
        {"Bunyip Stone 3", "Warp Stone at end of timed parkour"},
    }
);

const LevelCollectibleInfo WWInfo(
    "Winter Woods",
    {},
    {},
    {
        {"Bilby 1", "Hanging from root above lava platform in center of map"},
        {"Bilby 2", "Branch on top of ice blocks behind large ice wall"},
        {"Bilby 3", "North lava patch platform"},
        {"Bilby 4", "Under ice bridge on southwest section behind large ice wall"},
    },
    {},
    {
        {"Picture Frame 1", "North lava patch purple platforms"},
        {"Picture Frame 2", "Center lava tube"},
        {"Picture Frame 3", "Center lava tube"},
        {"Picture Frame 4", "Center lava tube"},
        {"Picture Frame 5", "South lava tube"},
        {"Picture Frame 6", "South lava tube"},
        {"Picture Frame 7", "South lava tube"},
        {"Picture Frame 8", "First collapsible bridge in southeast corner"},
        {"Picture Frame 9", "Second collapsible bridge in southeast corner"},
        {"Picture Frame 10", "North lava patch purple platforms"},
    },
    {
        {"Bunyip Stone 1", "Earth Stone in center lava tube"},
        {"Bunyip Stone 2", "Mega Stone under ice blocks behind large ice wall"},
        {"Bunyip Stone 3", "Zoom Stone in south lava tube"},
    }
);

const LevelCollectibleInfo KBIInfo(
    "Kaka Boom Island",
    {
        {"Steve", "Behind rock wall at start"},
    },
    {
        {"Gooboo Berry", "Behind rock wall at start"},
    },
    {
        {"Bilby 1", "Hanging from tree above invisible crate behind the start"},
        {"Bilby 2", "Treading water in northeast corner"},
        {"Bilby 3", "Behind rock wall at start"},
    },
    {
        {"Kromium Orb 1", "Underwater on south shore"},
        {"Kromium Orb 2", "Underwater in south corner of end area"},
        {"Kromium Orb 3", "Waterfall pool"},
        {"Kromium Orb 4", "Invisible platform at start"},
    },
    {
        {"Picture Frame 1", "Underwater in the corner behind start"},
        {"Picture Frame 2", "Sitting on an island near lava in end area"},
        {"Picture Frame 3", "Bushes north of center volcano"},
        {"Picture Frame 4", "Bushes in southwest corner of end area"},
        {"Picture Frame 5", "Middle of lava in end area"},
        {"Picture Frame 6", "Underwater in sunken plane in end area"},
        {"Picture Frame 7", "By dunny before spiky roller traps"},
        {"Picture Frame 8", "Underwater straight from start"},
        {"Picture Frame 9", "Underwater in southwest corner"},
        {"Picture Frame 10", "Underwater in northwest corner of end area"},
        {"Picture Frame 11", "Invisible crate behind start"},
        {"Picture Frame 12", "Invisible crate behind start"},
        {"Picture Frame 13", "Invisible crate behind start"},
        {"Picture Frame 14", "Invisible crate behind start"},
        {"Picture Frame 15", "Invisible crate behind start"},
    },
    {
        {"Bunyip Stone 1", "Air Stone at end area floating in the air"},
        {"Bunyip Stone 2", "Magnet Stone underwater on south shore"},
        {"Bunyip Stone 3", "Earth Stone at end area floating above lava"},
    }
);

const LevelCollectibleInfo GGInfo(
    "Gooboo Gully",
    {},
    {
        {"Gooboo Berry", "End of twisting platform parkour above river"},
    },
    {
        {"Bilby 1", "Crevice in west side"},
        {"Bilby 2", "Under log at turn leading to bridge"},
        {"Bilby 3", "Hanging from branch near falling boulders"},
    },
    {
        {"Kromium Orb 1", "On top of Steve's House"},
        {"Kromium Orb 2", "Behind twisty block south at first turn"},
        {"Kromium Orb 3", "Fenced area after lash slide"},
        {"Kromium Orb 4", "Invisible crate outside fence where Kromium Orb 25 is"},
    },
    {
        {"Picture Frame 1", "End of falling boulders section"},
        {"Picture Frame 2", "Second crevice in falling boulders section"},
        {"Picture Frame 3", "Underwater crate near Kromium Orb 25"},
        {"Picture Frame 4", "Underwater crate near Kromium Orb 25"},
        {"Picture Frame 5", "Moving platform over river"},
        {"Picture Frame 6", "Moving platform over river"},
        {"Picture Frame 7", "Platform above Frames 47 and 48"},
        {"Picture Frame 8", "First crevice in falling boulders section"},
        {"Picture Frame 9", "Third crevice in falling boulders section"},
    },
    {
        {"Bunyip Stone 1", "Fire Stone behind Kromium Orb 24"},
        {"Bunyip Stone 2", "Ultra Stone behind timed gate at end"},
        {"Bunyip Stone 3", "Zoom Stone behind timed gate at end"},
    }
);

const LevelCollectibleInfo MBBInfo(
    "Mount Boom Basin",
    {
        {"Steve", "Southeast lava area"},
    },
    {
        {"Gooboo Berry", "Behind spiderwebs before 3rd turret"},
    },
    {
        {"Bilby 1", "Bounce shrooms to platform"},
        {"Bilby 2", "Behind first turret"},
        {"Bilby 3", "Bushes behind plane at start"},
    },
    {
        {"Kromium Orb 1", "Frog arena behind spiderwebs"},
        {"Kromium Orb 2", "Moving platforms in first lavaquin area"},
        {"Kromium Orb 3", "Behind rock wall after second turret"},
        {"Kromium Orb 4", "In southeast lava area"},
    },
    {
        {"Picture Frame 1", "Metal crates near start"},
        {"Picture Frame 2", "Metal crates near start"},
        {"Picture Frame 3", "Metal crates near start"},
        {"Picture Frame 4", "Metal crates near start"},
        {"Picture Frame 5", "Invisible crate after 2nd turret"},
        {"Picture Frame 6", "Invisible crate after 2nd turret"},
        {"Picture Frame 7", "Invisible crate after 3rd turret"},
        {"Picture Frame 8", "Invisible crate after 3rd turret"},
        {"Picture Frame 9", "Invisible crate in first lavaquin area"},
        {"Picture Frame 10", "Invisible crate in first lavaquin area"},
    },
    {
        {"Bunyip Stone 1", "Warp Stone given by Steve 4"},
        {"Bunyip Stone 2", "Chrono Stone behind spiderwebs"},
        {"Bunyip Stone 3", "Fire Stone across lava at end"},
    }
);

const LevelCollectibleInfo FFInfo(
    "Frozen Forests",
    {},
    {},
    {
        {"Bilby 1", "West platform in main area"},
        {"Bilby 2", "East side Grav Grenade platform to cliff"},
        {"Bilby 3", "North lava river platforms"},
    },
    {},
    {
        {"Picture Frame 1", "West lava area"},
        {"Picture Frame 2", "West lava area"},
        {"Picture Frame 3", "West lava area"},
        {"Picture Frame 4", "West lava area"},
        {"Picture Frame 5", "West lava area"},
    },
    {
        {"Bunyip Stone 1", "Shadow Stone reward from Ranger Endanger mission"},
        {"Bunyip Stone 2", "Magnet Stone above ice block tower"},
        {"Bunyip Stone 3", "Water Stone on central platform"},
    }
);