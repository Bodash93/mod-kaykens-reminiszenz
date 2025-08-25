-- Kayken's Reminiszenz - Immersive Story-Driven Gossip System
-- Complete narrative experience replacing development menus

-- =============================================
-- NPC TEXT ENTRIES - Kayken's Tragic Story
-- =============================================

-- Main Menu (60000) - Kayken's Troubled State
DELETE FROM `npc_text` WHERE `ID` = 60000;
INSERT INTO `npc_text` (`ID`, `text0_0`, `text0_1`, `BroadcastTextID0`, `lang0`, `Probability0`, `em0_0`, `em0_1`, `em0_2`, `em0_3`, `em0_4`, `em0_5`, `VerifiedBuild`) VALUES
(60000, 'Ah, ein Besucher... $N, nicht wahr? Verzeiht, aber ich bin... nicht ganz bei mir. Diese Träume, sie werden immer lebendiger, immer quälender.$B$BIch sehe ihn noch immer vor mir - Punscho, meinen treuen Gefährten. Er starb durch meine Schuld in den Tiefen des Schwarzfels. Und nun... nun kehren die Erinnerungen zurück, als lebendige Alpträume.', 'Die Dunkelheit in den Schwarzfelstiefen hat mich für immer gezeichnet, $N. Was Ihr in meinen Augen seht, ist nicht nur Trauer - es ist die Last der Schuld, die mich jeden Tag verfolgt.$B$BPunscho... mein bester Freund... wäre er doch nie mit mir gegangen.', 0, 0, 1, 1, 6, 25, 0, 0, 0, 12340);

-- Visions Menu (60001) - Dark Dreams and Memories
DELETE FROM `npc_text` WHERE `ID` = 60001;  
INSERT INTO `npc_text` (`ID`, `text0_0`, `text0_1`, `BroadcastTextID0`, `lang0`, `Probability0`, `em0_0`, `em0_1`, `em0_2`, `em0_3`, `em0_4`, `em0_5`, `VerifiedBuild`) VALUES
(60001, 'Die Träume... sie sind nicht nur Erinnerungen, $N. Sie sind lebendige Echos einer zerbrochenen Realität. Ich sehe Polydeuces, den alten Drachen, wie er in seinen Flammen erwacht. Gorleax, das korrumpierte Konstrukt, beginnt seine tödlichen Reinigungsprotokolle.$B$BJede Nacht erlebe ich unsere letzte Expedition erneut. Immer und immer wieder sehe ich Punschos entsetzten Gesichtsausdruck, bevor die Dunkelheit ihn verschlang.', 'Die Schwarzfelstiefen haben meine Seele gezeichnet, $N. Was als wissenschaftliche Expedition begann, wurde zu einem Albtraum aus Verrat, Schuld und Tod.$B$BDiese Träume sind keine normalen Visionen - sie sind ein Portal zu dem Ort, wo alles begann. Wo alles endete.', 0, 0, 1, 25, 274, 1, 18, 0, 0, 12340);

-- Punscho Menu (60002) - The Tragic Tale of a Lost Friend  
DELETE FROM `npc_text` WHERE `ID` = 60002;
INSERT INTO `npc_text` (`ID`, `text0_0`, `text0_1`, `BroadcastTextID0`, `lang0`, `Probability0`, `em0_0`, `em0_1`, `em0_2`, `em0_3`, `em0_4`, `em0_5`, `VerifiedBuild`) VALUES
(60002, 'Punscho war mehr als nur mein Forschungspartner - er war der Bruder, den ich nie hatte. Gemeinsam erforschten wir die arkanen Geheimnisse der Schwarzfelstiefen. Er vertraute mir bedingungslos.$B$BAber meine Gier nach Wissen wurde ihm zum Verhängnis. Als wir tiefer vordrangen als je zuvor, öffnete ich versehentlich ein Portal zu den Schattenlanden. Punscho opferte sich, um mich zu retten... und ich konnte ihn nicht zurückhalten.$B$BSein letzter Blick... voller Enttäuschung und Vergebung zugleich... er verfolgt mich bis heute.', 'Er sagte zu mir: "Kayken, manchmal muss man wissen, wann man aufhören sollte." Aber ich hörte nicht auf ihn. Mein Ehrgeiz kostete ihm das Leben.$B$BNun erscheint er mir in Träumen, nicht als Vorwurf, sondern als Warnung. Die Dunkelheit, die wir damals erweckten, sie ist noch immer dort. Sie wartet.', 0, 0, 1, 18, 274, 6, 25, 0, 0, 12340);

-- Mission Menu (60003) - The Call to Action
DELETE FROM `npc_text` WHERE `ID` = 60003;
INSERT INTO `npc_text` (`ID`, `text0_0`, `text0_1`, `BroadcastTextID0`, `lang0`, `Probability0`, `em0_0`, `em0_1`, `em0_2`, `em0_3`, `em0_4`, `em0_5`, `VerifiedBuild`) VALUES
(60003, 'Ihr wollt mir wirklich helfen, $N? Dann hört gut zu: Diese "Reminiszenz" ist kein gewöhnlicher Ort. Es ist eine Manifestation meiner Schuld, ein psychisches Echo jener verhängnisvollen Expedition.$B$BDort werdet Ihr auf die Schatten meiner Vergangenheit treffen - Polydeuces, den schlafenden Drachen, der durch Punschos Tod erwachte. Gorleax, das Konstrukt, das unsere Anwesenheit als "Verunreinigung" erkannte. Und die Horde des Schwarzfels, Echos der Krieger, die durch meine Torheit fielen.$B$BWenn Ihr bereit seid, diese Dämonen zu konfrontieren... dann kann ich vielleicht endlich Frieden finden.', 'Die Reminiszenz ist gefährlich, $N. Dort sind meine dunkelsten Erinnerungen lebendig geworden. Aber vielleicht... vielleicht ist es an der Zeit, sich ihnen zu stellen.$B$BPunscho würde wollen, dass ich weitermache. Dass ich lerne, mit dieser Schuld zu leben, ohne daran zu zerbrechen.', 0, 0, 1, 1, 25, 274, 0, 0, 0, 12340);

-- =============================================
-- GOSSIP MENU ENTRIES - Link Text IDs to Menus
-- =============================================

-- Main Menu
DELETE FROM `gossip_menu` WHERE `MenuID` = 60000;
INSERT INTO `gossip_menu` (`MenuID`, `TextID`) VALUES (60000, 60000);

-- Visions Menu  
DELETE FROM `gossip_menu` WHERE `MenuID` = 60001;
INSERT INTO `gossip_menu` (`MenuID`, `TextID`) VALUES (60001, 60001);

-- Punscho Menu
DELETE FROM `gossip_menu` WHERE `MenuID` = 60002;
INSERT INTO `gossip_menu` (`MenuID`, `TextID`) VALUES (60002, 60002);

-- Mission Menu
DELETE FROM `gossip_menu` WHERE `MenuID` = 60003;
INSERT INTO `gossip_menu` (`MenuID`, `TextID`) VALUES (60003, 60003);

-- =============================================
-- CLEANUP - Remove old unused gossip menus
-- =============================================

-- Remove old development menus and obsolete entries
DELETE FROM `gossip_menu` WHERE `MenuID` IN (59999, 59998, 59997);
DELETE FROM `npc_text` WHERE `ID` IN (59999, 59998, 59997);

-- Note: The new gossip system is entirely code-driven through npc_kayken.cpp
-- These text entries provide the immersive narrative experience for Kayken the Dreamer
-- Players will experience a complete emotional journey before entering the Reminiszenz instance