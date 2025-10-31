// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Milyen kérdései vannak?", "Miben segíthetek?"), "Nemrég próbálta ezt a kérdést feltenni nekem...", "Igen, hadd találjam ki... Már megint körbe-körbe jársz?",
                          "Figyelj, én itt a pénzügyekkel foglalkozom, nem válaszolok kérdésekre...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Meggondoltam magam...", "Jelenleg nincs mirôl beszélnem."), "Umph, hová tûnt a memóriám...",
                      "Kitaláltad, sajnálom...", "Megértem...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			// --> Sinistra Длинные тени старых грехов	
			if (CheckAttribute(pchar, "questTemp.DTSG_KnippelDolg"))
			{
				link.l1 = "Szeretnék beszélni önnel az egyik adósáról.";
				link.l1.go = "DTSG_KnippelDolg";
			}
			// <-- Длинные тени старых грехов
		break;
		
		// --> Sinistra Длинные тени старых грехов	
		case "DTSG_KnippelDolg":
			DeleteAttribute(pchar, "questTemp.DTSG_KnippelDolg");
			dialog.text = "Melyik?";
			if (sti(pchar.reputation.nobility) > 50)
			{
				link.l1 = "(Becsület) Ez az a bizonyos Charlie Knippel.";
				link.l1.go = "DTSG_KnippelDolg_VD_2";
			}
			else
			{
				link.l2 = "(Becsület) Van képed ilyen nyugodtan beszélni velem. Fejvadászokat küldtél az emberem után.";
				link.l2.go = "DTSG_KnippelDolg_2";
			}
		break;
		
		case "DTSG_KnippelDolg_VD_2":
			dialog.text = "Charlie? De ô már nem az adósom. Az adósságát már régen kifizették, uram.";
			link.l1 = "Az adósságát már régen kiegyenlítette, uram. Ki, ha nem titok?";
			link.l1.go = "DTSG_KnippelDolg_VD_3";
		break;
		
		case "DTSG_KnippelDolg_VD_3":
			dialog.text = "Nem az. A kapitánya, Richard Fleetwood. Igazi úriember, mindenkinek kellene, hogy legyenek ilyen barátai.";
			link.l1 = "Tudja, most már én vagyok Charlie kapitánya. Mr. Fleetwood... áthelyezte ôt az én szolgálatomba. Jó tudni, hogy betartotta az ígéretét, és fizetett magának.";
			link.l1.go = "DTSG_KnippelDolg_VD_4";
		break;
		
		case "DTSG_KnippelDolg_VD_4":
			dialog.text = "Szóval ezért kérdezi.";
			link.l1 = "Nem csak ezért. Jól ismeri Charlie-t, igaz? Letartóztatták, és korábbi zsoldosokat küldtek utána. Van ötleted, hogy miért? Elvégre önnek nagyon... változatos emberekkel van dolga.";
			link.l1.go = "DTSG_KnippelDolg_VD_5";
		break;
		
		case "DTSG_KnippelDolg_VD_5":
			dialog.text = "Charlie-t letartóztatták? Meglepett, uram, nem tudtam róla semmit. Sem az... ellenségeirôl. Egy ilyen jó, istenfélô ember, mint ô...";
			link.l1 = "Ezzel nem lehet vitatkozni. Nos, azért köszönöm. Remélem, a parancsnok úr elfogadja az óvadékot.";
			link.l1.go = "DTSG_KnippelDolg_VD_6";
		break;
		
		case "DTSG_KnippelDolg_VD_6":
			dialog.text = "Ne habozzon, keressen meg újra, ha szüksége van pénzre az óvadék biztosításához - jó feltételeket fogok adni.";
			link.l1 = "Ha-ha, ez most komoly? Egy uzsorás mindig uzsorás marad. Az óvadékot magam is meg tudom fizetni. Viszontlátásra.";
			link.l1.go = "DTSG_KnippelDolg_VD_7";
		break;
		
		case "DTSG_KnippelDolg_VD_7":
			DialogExit();
			
			LAi_LocationFightDisable(&Locations[FindLocation("SentJons_town")], false);
			//LAi_LocationDisableOfficersGen("SentJons_town", false);
			LAi_LocationDisableOfficersGen("SentJons_bank", false);
			AddQuestRecord("DTSG", "11");
			pchar.questTemp.DTSG_AntiguaZalog = true;
			AddLandQuestMarkToPhantom("SentJons_prison", "SentJonsJailOff");
		break;
		
		case "DTSG_KnippelDolg_2":
			dialog.text = "Fejvadászok? Az embered után? Mirôl beszélsz?";
			link.l1 = "Ne is tagadd. Jobb, ha bevallod, és úriember módjára elintézzük a dolgot. De ha hülyét csinálsz magadból, akkor a nehezebb utat kell járnom veled.";
			link.l1.go = "DTSG_KnippelDolg_3";
		break;
		
		case "DTSG_KnippelDolg_3":
			dialog.text = "Tévedsz!... Ôrség!!! Azzal fenyeget, hogy megöl!";
			link.l1 = "Ó, a kurva életbe...";
			link.l1.go = "DTSG_KnippelDolg_4";
		break;
		
		case "DTSG_KnippelDolg_4":
			DialogExit();
			
			sld = GetCharacter(NPC_GenerateCharacter("DTSG_AntiguaStrazhBank_1", "sold_eng_"+(rand(7)+1), "man", "man", 10, ENGLAND, 0, false, "soldier"));
			GiveItem2Character(sld, "blade_10");
			EquipCharacterByItem(sld, "blade_10");
			GiveItem2Character(sld, "pistol1");
			EquipCharacterByItem(sld, "pistol1");
			ChangeCharacterAddressGroup(sld, "SentJons_bank", "reload", "reload1");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_AntiguaStrazhBank";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
			LAi_SetHP(sld, 140+MOD_SKILL_ENEMY_RATE*10, 140+MOD_SKILL_ENEMY_RATE*10);
			AddLandQuestMarkToPhantom("SentJons_prison", "SentJonsJailOff");
		break;
		// <-- Длинные тени старых грехов
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
