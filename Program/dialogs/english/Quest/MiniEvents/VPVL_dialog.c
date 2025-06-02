
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		////// Леа Карно //////
		
		case "Exit":
			DialogExit();
		break;
		
		case "First Time":
			dialog.text = ""+GetSexPhrase("Monsieur","Mademoiselle")+"! Pardon me, are you a sail"+GetSexPhrase("or","oress")+"?";
			link.l1 = "I am Captain "+GetFullName(pchar)+", at your service.";
			link.l1.go = "Lea First Talk";
			DelLandQuestMark(npchar);
		break;

		case "Lea First Talk":
			dialog.text = "I am Lea. Lea Carno... "+GetSexPhrase("Monsieur","Mademoiselle")+" Captain, did you arrive recently? You haven't seen a fishing boat called the 'Cormorant' out at sea, have you? You see, my husband... my husband Pierre... he set sail two days ago and hasn’t returned.";
			link.l1 = "The 'Cormorant'? No, I haven’t come across any such vessel. That name I would’ve remembered. I’m sorry to hear this, Madame. I hope your husband is well and simply delayed along his route.";
			link.l1.go = "Lea First Talk Rep Plus";
			link.l2 = "The 'Cormorant'? Ha! Is that the boat’s name or a nickname for its owner? Either way, I’ve seen neither.";
			link.l2.go = "Lea First Talk Rep Minus";
		break;

		case "Lea First Talk Rep Plus":
			dialog.text = "I don’t know what to think... He’s never been gone this long. He always returned by noon, without fail. Now... something’s happened. I feel it.";
			link.l1 = "Go to the authorities. They can send a patrol ship to comb the coastal waters.";
			link.l1.go = "Lea First Talk1";
			ChangeCharacterComplexReputation(pchar,"nobility", 3);
		break;

		case "Lea First Talk Rep Minus":
			dialog.text = "I don’t know what to think... He’s never been gone this long. He always returned by noon, without fail. Now... something’s happened. I feel it.";
			link.l1 = "Go to the authorities. They can send a patrol ship to comb the coastal waters.";
			link.l1.go = "Lea First Talk1";
			ChangeCharacterComplexReputation(pchar,"nobility", -3);
		break;

		case "Lea First Talk1":
			dialog.text = "Oh, "+GetSexPhrase("Monsieur","Mademoiselle")+" Captain, of course I already spoke to the commandant. But what good did it do? He just shrugged... Said he had no ships free to search for my husband.\nAnd me? All I can do is stand here, stare at the horizon, wait... and hope.";
			link.l1 = "Now now, Madame Lea. Don’t despair just yet. I think I can spare a day to help you search.";
			link.l1.go = "Agree To Help";
			link.l2 = "Why worry so much? Maybe the morning breeze carried him into the arms of some charming lady. He’ll take a stroll, breathe the fresh air, and come back.";
			link.l2.go = "bad joke";
			link.l3 = "Want a bit of advice? Stop straining your eyes on the horizon. Head to the tavern in Le François and search for your dear husband there. Don’t take offense, but most likely he just needed a break from domestic worries, and you're turning it into a tragedy. Best of luck.";
			link.l3.go = "Rejection";
		break;

		case "Agree To Help":
			dialog.text = ""+GetSexPhrase("Monsieur","Mademoiselle")+" Captain, I... I don’t even know how to thank you... You... you have no idea what this means to me! Everyone just shrugs... But you... you’re willing to help. Thank you!";
			link.l1 = "No need to thank me yet. Just tell me—where did your husband usually fish? Did he have a regular spot, or did he like to roam?";
			link.l1.go = "Go To Help";
		break;
		
		case "bad joke":
			dialog.text = "A charming lady?! You truly think this is the right moment for jests? I know he's in trouble... and you laugh at my sorrow! (weeps) Everything in the world is against me right now. No one wants to help... No one understands how heavy my heart is.";
			link.l1 = "Madame Lea, for heaven’s sake, forgive my thoughtlessness. I meant no offense! I swear, I’ll search for your husband. Just tell me where to begin.";
			link.l1.go = "bad joke1";
		break;

		case "bad joke1":
			dialog.text = "You...? You really mean to help me?";
			link.l1 = "Of course. It's the least I can do to atone for my inexcusable and ill-timed joke.";
			link.l1.go = "bad joke2";
		break;

		case "bad joke2":
			dialog.text = "Thank you, "+GetSexPhrase("Monsieur","Mademoiselle")+" Captain. Thank you... Truly, you’ve caught me off guard—I don’t know what to say...";
			link.l1 = "No need for thanks just yet. Tell me instead—where does your husband usually fish? Does he have a regular spot, or does he move about?";
			link.l1.go = "Go To Help";
		break;

		case "Go To Help":
			dialog.text = "Well... Pierre... He rarely told me exactly where he fished. Called it 'his secret'. But if it helps find him... Maybe... I don’t know... You really do mean to help, don’t you, "+GetSexPhrase("Monsieur","Mademoiselle")+" Captain? Truly?";
			link.l1 = "You wonder whether to share your husband’s secret fishing spot? I assure you, your family’s secret stays with me—I give you my word as a captain. I must know the place to begin the search.";
			link.l1.go = "Go To Help1";
		break;

		case "Go To Help1":
			dialog.text = "You're right, "+GetSexPhrase("Monsieur","Mademoiselle")+" Captain... Forgive me. That place meant so much to Pierre. He always said it was his one true secret, his little treasure.\nBut I know where it is. If it will help bring him home... He fished near Le Marin Bay. It’s along the southern coast, not too far from the town. Please, I beg you—find him!";
			link.l1 = "Don’t worry, Lea. I’ll do everything in my power. Did he have any enemies? Had anyone threatened him recently?";
			link.l1.go = "Go To Help2";
		break;

		case "Go To Help2":
			dialog.text = "Enemies? Pierre? He’s the kindest soul alive! He wouldn’t harm a fly... He’s just a simple fisherman. Who could he have possibly wronged? I just don’t understand what could’ve happened... It’s all so strange... and terrifying...";
			link.l1 = "Do not fear, Madame Lea. I’ll set out immediately. I’m sure your husband is safe. I’ll bring him back into your loving arms. Stay strong.";
			link.l1.go = "Return Lea Exit";
		break;

		case "Return back to Lea":
			dialog.text = ""+GetSexPhrase("Monsieur","Mademoiselle")+" Captain, please—do you have any news? Have you learned anything? Anything at all?";
			link.l1 = "Not yet, I’m afraid. But I’m still searching, Lea!";
			link.l1.go = "Exit";
		break;
		
		case "Return Lea Exit":
			DialogExit();
			npchar.dialog.currentnode = "Return back to Lea";
			AddQuestRecord("VPVL", "2"); 
			DoQuestCheckDelay("VPVL_Start", 0.1);
		break;
		
		case "Rejection":
			DialogExit();
			npchar.dialog.currentnode = "Rejection1";
			SetTimerCondition("VPVL_ClearLea", 0, 0, 2, false);  // Удаляем Леа через 2 дня
			CloseQuestHeader("VPVL");
		break;
		
		case "Rejection1":
			dialog.text = "What more do you want? Haven’t you had enough fun mocking a poor woman?";
			link.l1 = "...";
			link.l1.go = "Exit";
		break;

		case "Lea second talk":
			dialog.text = ""+GetSexPhrase("Monsieur","Mademoiselle")+" Captain! Pierre! Oh, how glad I am to see you! You found him!";
			link.l1 = "Madame Lea, may I present Pierre Carno, in the flesh. I can't say he's come through unscathed, but I’ve no doubt your care will mend him in short order.";
			link.l1.go = "Lea second talk1";
			locCameraFromToPos(-7.58, 3.1, 82.5, false, -10, -15, 0);
		break;

		case "Lea second talk1":
			dialog.text = "Pierre! Blessed Virgin Mary! I worried myself sick over you! Where have you been? There's no color in your face... you're so pale... Oh! And what is this?! These terrible wounds?! Cuts... and burns...";
			link.l1 = "Hush now, my heart's treasure. Mere scratches, they'll fade in time. To see your face again... that's all I wished for. Had it not been for the Captain... I owe "+GetSexPhrase("him","her")+" my very life.";
			link.l1.go = "Lea second talk2";
			CharacterTurnByChr(npchar, CharacterFromID("VPVL_Pier_carno"));
			sld = CharacterFromID("VPVL_Pier_carno");
			CharacterTurnByChr(sld, CharacterFromID("VPVL_Lea_girl"));
			locCameraFromToPos(-7.62, 3.1, 83.26, false, 30, -15, 0);
		break;

		case "Lea second talk2":
			dialog.text = ""+GetSexPhrase("Monsieur","Mademoiselle")+" Captain... I... I don’t even know how to thank you... you found him! You saved my Pierre! Thank you... thank you for everything! May the Lord watch over you, "+GetSexPhrase("Monsieur","Mademoiselle")+" Captain!";
			link.l1 = "Now, now, that’s enough of that. What Pierre truly needs is a hot meal and some proper rest.";
			link.l1.go = "Exit";
			CharacterTurnByChr(npchar, CharacterFromID("Blaze"));
			locCameraFromToPos(-7.58, 3.1, 82.5, false, -10, -15, 0);
			AddDialogExitQuest("VPVL_PierTalkOnThePirs");
		break;
		
		//////   Контры   //////
		
		case "Kontr Le Maren":
			dialog.text = "Blast it all! Finally you show yourself, "+GetSexPhrase("you mangy cur","you wretched wench")+"! Where the devil have you been? We've been roasting on this blasted beach for three days! Where’s our cargo?!";
			link.l1 = "Seems the revelry can't commence without me, eh, gentlemen? Well, I may be a touch late—but better to arrive with the tide than not at all!";
			link.l1.go = "Exit_Sneak";
			link.l2 = "Addressing me, are you? Perhaps learn some manners before barking questions like bilge rats!";
			link.l2.go = "Exit_Lucky";
			//locCameraFromToPos(-3.35, 2.23, 6.93, false, 20, -1, 10);
			locCameraFromToPos(-5.73, 2.45, 5.75, true, -0.53, 0.40, 7.17);
			DeleteAttribute(pchar, "questTemp.VPVL_Contr_V_Lemaren");
		break;
		
		case "Exit_Sneak":
			DialogExit();
			sld = CharacterFromID("VPVL_contr_1");
			sld.dialog.filename = "Quest\MiniEvents\VPVL_dialog.c";
			sld.dialog.currentnode = "Kontr Le Maren0";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			AddCharacterExpToSkill(pchar, "Sneak", 50);
			notification("Experience gained", SKILL_SNEAK);
		break;
		
		case "Exit_Lucky":
			DialogExit();
			sld = CharacterFromID("VPVL_contr_1");
			sld.dialog.filename = "Quest\MiniEvents\VPVL_dialog.c";
			sld.dialog.currentnode = "Kontr Le Maren0";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			AddCharacterExpToSkill(pchar, "Fortune", 50);
			notification("Experience gained", SKILL_FORTUNE);
		break;

		case "Kontr Le Maren0":
			sld = CharacterFromID("VPVL_contr_2");
			dialog.text = ""+sld.name+", you addled barnacle! Open your deadlights, you daft fool—this ain't our contact at all!";
			link.l1 = "Argh... Another of the governor's lapdogs! Sure as the tide! Since "+GetSexPhrase("this blackguard","this foolish girl")+" dragged "+GetSexPhrase("himself","herself")+" here, let’s haul "+GetSexPhrase("him","her")+" to the cave with the other rat. We'll show "+GetSexPhrase("him","her")+" how we get secrets out—quick enough they'll spill every filthy plan their master ever dreamt!";
			link.l1.go = "Kontr Le Maren1";
			locCameraFromToPos(-3.40, 2.38, 5.79, true, -0.49, 0.5, 7.59);
			CharacterTurnByChr(sld, CharacterFromID("VPVL_contr_1"));
			
			sld = CharacterFromID("VPVL_contr_1");
			CharacterTurnByChr(sld, CharacterFromID("VPVL_contr_2"));
		break;
		
		case "Kontr Le Maren1":
			dialog.text = "What foul fantasies be festering in your head, you salt-soaked beast? Stow your drooling! Better we sell her to... you know who. He’ll part with a chest of coin for such a fine lass, and we’ll be drinking and wenching for a month of Sundays!";
			if (pchar.sex == "man")
			{
				dialog.text = "What in Davy Jones' locker do we need another swab cluttering our brig for? Bear down harder on his mate—he’ll sing like a gull at sunrise. As for this one, let’s gut him here and now, save us the trouble of looking at his face!";
			}
			link.l1 = "A thousand hungry sharks gnaw your guts, Simon! You be the slyest smuggler in the whole archipelago!";
			link.l1.go = "Kontr Le Maren2";
		break;

		case "Kontr Le Maren2":
			dialog.text = "...";
			if (GetSummonSkillFromName(pchar, SKILL_PISTOL) >= 20)
			{
				if(GetCharacterEquipByGroup(pchar, GUN_ITEM_TYPE) == "") {
					notification("No pistol equipped", "NONE");
					link.l2 = "If that barnacle-brain’s your sharpest cutlass, I dread to think what addled nonsense rattles in the heads of the rest!";
					link.l2.go = "Kontr Le Maren3";
					CharacterTurnByChr(npchar, CharacterFromID("Blaze"));
					//locCameraFromToPos(-3.35, 2.23, 6.93, false, 20, -1, 10);
					sld = CharacterFromID("VPVL_contr_1");
					CharacterTurnByChr(sld, CharacterFromID("Blaze"));
				}
				else
				{
					link.l1 = "(To myself)(Pistols) While these sea rats prattle on with their worthless gab, I've a chance to strike quick and true, like lightning from a clear sky.";
					link.l1.go = "murder";
					notification("Check passed", SKILL_PISTOL);
					locCameraFromToPos(-5.73, 2.45, 5.75, true, -0.53, 0.40, 7.17);
				}
			}
			if (GetSummonSkillFromName(pchar, SKILL_PISTOL) < 20)
			{
				notification("Skill too low (20)", SKILL_PISTOL);
				CharacterTurnByChr(npchar, CharacterFromID("Blaze"));
				sld = CharacterFromID("VPVL_contr_2");
				CharacterTurnByChr(sld, CharacterFromID("Blaze"));
				locCameraFromToPos(-5.73, 2.45, 5.75, true, -0.53, 0.40, 7.17);
			}
			link.l2 = "If that barnacle-brain’s your sharpest cutlass, I dread to think what addled nonsense rattles in the heads of the rest!";
			link.l2.go = "Kontr Le Maren3";
		break;
		
		case "Kontr Le Maren3":
			dialog.text = "I'll carve that wagging tongue from your head, you impudent cur"+GetSexPhrase("","—filthy strumpet")+ ", and feed it to the gulls so you'll never speak another word!";
			link.l1 = "Carve it out, will you? Come then, if you've the nerve to dance with the devil.";
			link.l1.go = "Kontr Le Maren Fight";
			CharacterTurnByChr(pchar, CharacterFromID("VPVL_contr_1"));
		break;
		
		case "Kontr Le Maren Fight":
			DialogExit();
			AddDialogExitQuest("VPVL_EveryoneFight");
			LAi_LocationFightDisable(&Locations[FindLocation("Shore39")], false);
			EndQuestMovie();
		break;
		
		case "murder":
			DialogExit();
			AddDialogExitQuest("VPVL_Pistol_Murder");
			locCameraFromToPos(-5.04, 2.62, 8.65, false, 20, -6, -15);
		break;
		
		/////////////   Пьер Карно   /////////////
		
		case "PierFirstTalk":
			dialog.text = ""+GetSexPhrase("Monsieur","Mademoiselle")+"... Forgive me... My wits are scattered... Have you come to finish what they started?";
			link.l1 = "Are you Pierre Carno?";
			link.l1.go = "Pier_1";
			DelLandQuestMark(npchar);
			DeleteAttribute(pchar, "questTemp.VPVL_SetFlagLeMaren");
		break;

		case "Pier_1":
			dialog.text = "Ayou, that's me. You know my name?";
			link.l1 = "Of course. Otherwise, what would I be doing here?";
			link.l1.go = "Pier_2";
		break;

		case "Pier_2":
			dialog.text = "Forgive me, I don't understand anything... Pain and hunger have robbed me of my senses... Why have you come?";
			link.l1 = "It's simple. Since your disappearance, your faithful wife has kept vigil at the quay, her eyes ever searching for the Cormorant’s sail. Her sorrow pierced me so deeply I could not sail past unmoved—I resolved to search for you.";
			link.l1.go = "Pier_3";
		break;

		case "Pier_3":
			dialog.text = "My wife... my dear Léa... I was certain I'd never see her again...";
			link.l1 = "That tide has passed. She's waiting for you at the dock, still clinging to hope. Let’s get out of here. Take my arm.";
			link.l1.go = "Pier_4";
		break;

		case "Pier_4":
			dialog.text = "Mercy... "+GetSexPhrase("Monsieur","Mademoiselle")+"... I need a moment... my legs are like driftwood... Thank you, truly. If not for you... it feels like the Almighty Himself sent you... You've not told me your name. How should I address my savior?";
			link.l1 = "Captain "+GetFullName(pchar)+". While you gather your strength, tell me how you ended up in this place. Were you doing business with these... men?";
			link.l1.go = "Pier_5";
			LAi_Fade("VPVL_PierStay", "");
		break;

		case "Pier_5":
			dialog.text = "Heavens no, Captain. I'm just a humble fisherman. The day started off so well. I was fishing along the western shore—the catch was incredible.\nI was eager to barrel the fish and cast my nets again, but didn’t notice the current pulling my boat toward the reef. The hull was thin as an eggshell—one strike was enough to let the sea in. The Cormorant, heavy with the morning’s catch, sank quickly.";
			link.l1 = "Then you made it ashore, only for smugglers to mistake you for one of the governor’s spies?";
			link.l1.go = "Pier_6";
		break;

		case "Pier_6":
			dialog.text = "Exactly. I barely reached the shore, battered by the cursed waves. I just needed to dry off and rest before heading to town. Then, those devils appeared out of nowhere.\nThey took one look and decided I was a spy. I couldn't say a word before they bound me and dragged me here. They starved me and tortured me for two days, trying to get me to confess to things I know nothing about—agents, plans... but I knew nothing!";
			link.l1 = "Brains were in short supply among that lot—that’s why they’re now feeding the crabs. But that’s all behind you now. You’re free. Time to reunite with your wife—she’s surely at her wits’ end.";
			link.l1.go = "Pier_7";
		break;

		case "Pier_7":
			dialog.text = "All I want is to hold her again. I think... I think I can walk now.";
			link.l1 = "Then let’s not waste another moment.";
			link.l1.go = "exit_grot";
		break;
		
		case "exit_grot":
			DialogExit();  
			AddQuestRecord("VPVL", "4");
			AddDialogExitQuest("VPVL_PierFollow");
		break;
		
		case "PierInThePirs":
			dialog.text = "Captain, I beg you—come to the tavern tomorrow evening at six bells. My conscience would never rest if I failed to thank you properly. Right now... I cannot find the words to express what’s in my heart. Please, come. It would mean a great deal to me.";
			link.l1 = "Very well, Pierre. Don’t worry—I’ll be there.";
			link.l1.go = "GoHome";
			locCameraFromToPos(-8.28, 3.1, 82.93, false, 40, -15, 0);
		break;

		case "GoHome":
			DialogExit();
			AddQuestRecord("VPVL", "5");
			AddDialogExitQuest("VPVL_KarnoGoHome");
		break;

		case "PierTalkTavern":
			dialog.text = "Capitaine! You’ve come! Please, join me!";
			link.l1 = "With pleasure!";
			link.l1.go = "PierTalkTavern1";
			LAi_Fade("VPVL_SitOnTheTable", "");
			FreeSitLocator("FortFrance_Tavern", "sit6");  // Just in case
			DeleteAttribute(pchar, "questTemp.VPVL_Magor_Dialogue");
			pchar.questTemp.VPVL_DontSpawnSmugglersShipPier = true;
			DelLandQuestMark(npchar);
			AddDialogExitQuest("VPVL_KillCapitanOfSmuggler");
			locCameraFromToPos(-2.87, 1.37, -1.09, false, 0, -0.8, -0.90);
		break;

		case "PierTalkTavern1":
			dialog.text = "Let us hoist our tankards to your continued good fortune and health!";
			link.l1 = "Not just to mine, Pierre—but to yours as well. You're looking far better than when I found you in that wretched cave. Cheers!";
			link.l1.go = "PierTalkTavern2";
		break;

		case "PierTalkTavern2":
			dialog.text = "Capitaine, I can’t begin to express my endless gratitude! You didn’t pass me by, you didn’t turn away—you helped a complete stranger, a humble fisherman. Such nobility deserves a worthy reward, and I wish to give you all I have.\nHere—twenty pieces of sun-gold amber and five rare blue stones, salvaged from a sunken wreck. They’re yours now.\nAlso, I want you to have my navigational instruments and tackle. I’ve no ship left, so they serve me no purpose.";
			link.l1 = "Thank you, Pierre. These will certainly be of use. But most importantly, you're home again—and your wife need not live in fear any longer. Things will turn around for you both.";
			link.l1.go = "PierTakeGift";
			link.l2 = "Pierre, I appreciate the gesture, but you should keep them. You'll need every coin to repair your boat, buy tackle, nets, barrels... Your thanks—and seeing you and your wife reunited—that's reward enough. Take care of each other.";
			link.l2.go = "PierWontGift1";
		break;
		
		case "PierTakeGift":
			dialog.text = "I still can’t believe all of this truly happened... Let us drink to a new chapter in my family’s life—and to your noble heart, Capitaine!";
			link.l1 = "And to good fortune, Pierre. We could all use a touch of it!";
			link.l1.go = "ZastavkaVPVL";
			AddItems(PChar, "jewelry8", 20);
			AddItems(PChar, "jewelry7", 5);
			AddItems(PChar, "A_map_martiniqua", 1);
			AddItems(PChar, "spyglass3", 1);
			AddItems(PChar, "obereg_7", 1);
		break;

		case "PierWontGift1":
			dialog.text = "Capitaine, I cannot let things rest like this... You saved my life, and I owe you everything. Since you refuse the amber and other gifts, allow me at least to teach your crew how to fish the shallows. It will keep them fed and lighten your purse when it comes to provisions. What do you say?";
			link.l1 = "Now that’s a fine idea! As the old saying goes—teach a soul to cast a net, and they’ll never go hungry.";
			link.l1.go = "PierWontGift2";
			pchar.questTemp.VPVL_Food = true;
		break;

		case "PierWontGift2":
			dialog.text = "Wisely spoken, Capitaine! I’m glad to be of use. Now—shall we share another cup?";
			link.l1 = "To your health and prosperity, Pierre!";
			link.l1.go = "ZastavkaVPVL";
		break;
		
		case "ZastavkaVPVL":
			DialogExit();
			SetLaunchFrameFormParam("Four hours have passed...", "VPVL_SitOnTheTable", 2, 2);
			LaunchFrameForm();
			locCameraFromToPos(-2.87, 1.37, -1.09, false, 0, -0.8, -0.90);
			sld = CharacterFromID("VPVL_Pier_carno");
			sld.dialog.currentnode = "PierTalkTavern3";
			LAi_SetActorType(pchar);
			LAi_ActorDialog(pchar, sld, "", -1, 0);
		break;
		
		case "PierTalkTavern3":
			if(CheckAttribute(pchar, "questTemp.VPVL_Food"))
			{
			int foodDays = CalculateShipFood(&pchar);
			dialog.text = "By Neptune's beard! That's potent grog! Another swig or two, and I'll... hic... I'll be belting out a shanty fit to wake the kraken! Every soul from here to the harbor will hear my voice!";
			link.l1 = "Stow that shanty for calmer waters, Pierre. Save your voice for... hic... our next port of call. Should you start caterwauling, I'll be joining the chorus before long. And I've... er... pressing matters demanding my attention. The tide waits for no one... hic... even with the wind in their cups! Keep yourself in fair weather... hic... and that good woman of yours too!";
			link.l1.go = "PierTalkTavern4";
			WaitDate("", 0, 0, 0, 4, 10);
			LAi_AlcoholSetDrunk(pchar, 71, 5600);
			notification("Ship's provisions consumption reduced by 15%", "None");
			}
			else
			{
			dialog.text = "By Neptune's beard! That's potent grog! Another swig or two, and I'll... hic... I'll be belting out a shanty fit to wake the kraken! Every soul from here to the harbor will hear my voice!";
			link.l1 = "Stow that shanty for calmer waters, Pierre. Save your voice for... hic... our next port of call. Should you start caterwauling, I'll be joining the chorus before long. And I've... er... pressing matters demanding my attention. The tide waits for no one... hic... even with the wind in their cups! Keep yourself in fair weather... hic... and that good woman of yours too!";
			link.l1.go = "PierTalkTavern4";
			WaitDate("", 0, 0, 0, 4, 10);
			LAi_AlcoholSetDrunk(pchar, 71, 5600);
			}
		break;

		case "PierTalkTavern4":
			dialog.text = "Arr, Capitaine... you've the heart of a... hic... true mariner, you have! My debt to you can never be squared, d'you hear? Should your anchor drop in our harbor again... our hearth... our hearth be yours as if you were born of the same... same mother! On my soul and honor! We'll splice the mainbrace together again when Fortuna guides you back to these shores!";
			link.l1 = "Steady as she goes, Pierre! I'd best... hic... weigh anchor before my sea legs turn to jelly and I find myself adrift on this tavern floor! May fair winds fill your sails!";
			npchar.dialog.currentnode = "RepeatTavern";
			link.l1.go = "Exit2";
			CloseQuestHeader("VPVL");
		break;

		case "Exit2":
			DialogExit();
			LAi_Fade("VPVL_ExitFromTableVPVL", "VPVL_PierLivingTavern");
			DeleteAttribute(pchar, "questTemp.VPVL_Delete_Ship_RemoveFlag");
		break;

		case "RepeatTavern":
			dialog.text = "Too-o-o, the deep blue se-e-ea, and the trade winds fair... hic... to the fishin' grounds we sa-a-ail at first light!.. Blast and damn these rum-soaked wits! The verses escape me! Captain!.. Still anchored here, are you? Tavernkeeper! Bring forth... hic... the finest West Indies spirit in your cellar!";
			link.l1 = "I'm casting off, Pierre! Hic... while I can still navigate the treacherous path back to my vessel without foundering on the shoals!";
			link.l1.go = "Exit";
		break;

		case "MeetingInTneCity":
			dialog.text = ""+pchar.name+"! A sight for these salt-stained eyous! What say you to a measure of the Caribbean's finest spirit? To commemorate our crossing paths on life's vast ocean!";
			link.l1 = "Your weathered face brings joy to my heart as well, Pierre. Alas, duty commands my sobriety this day. My course is charted through treacherous waters that demand a clear mind and steady hand. Perhaps when next our stars align?";
			link.l1.go = "MeetingInTneCity1";
		break;

		case "MeetingInTneCity1":
			dialog.text = "Ayou, ayou, Capitaine! A ship must be sailed before she can dock. The ledger before the leisure, as merchants say. But when Fortune spins her wheel our way again, we shall raise a toast that would make old Blackbeard himself proud!";
			link.l1 = "Mark it in the ship's log, Pierre. Until the tides bring us together once more!";
			link.l1.go = "Exit";
			npchar.dialog.currentnode = "ExitRepeat";
		break;

		case "ExitRepeat":
			dialog.text = "Capitaine! Has your ship found safe harbor from the storm of obligations?";
			link.l1 = "The tide of commerce still pulls at my anchor, Pierre. My duties keep me lashed to the wheel yout awhile.";
			link.l1.go = "Exit";
		break;
	}
}   