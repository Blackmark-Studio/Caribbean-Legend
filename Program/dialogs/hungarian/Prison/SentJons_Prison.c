// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
 	switch(Dialog.CurrentNode)
	{
        case "quests":
            dialog.text = "Beszélj, hallgatlak.";
			link.l1 = "Tévedtem. Viszontlátásra.";
			link.l1.go = "Exit";
			
			// --> Sinistra Длинные тени старых грехов
			if(CheckAttribute(pchar,"questTemp.DTSG_AntiguaZalog"))
			{
				link.l1 = "Nemrég a város egyik katonája letartóztatta és ôrizetbe vette Charlie Knippelt. Még mindig itt van?"; 
				link.l1.go = "DTSG_AntiguaZalog_2";
			}
			// <-- Длинные тени старых грехов
		break;
		
		// --> Sinistra Длинные тени старых грехов
		case "DTSG_AntiguaZalog_2":
			dialog.text = "Így van, de miért kérdezi?";
			link.l1 = "Az a helyzet, hogy Charlie az egyik tisztem. Szeretném tudni, hogy mivel vádolják. A katonák, akik elvitték, nem mondtak nekem semmit."; 
			link.l1.go = "DTSG_AntiguaZalog_3";
			DelLandQuestMark(npchar);
		break;
		
		case "DTSG_AntiguaZalog_3":
			dialog.text = "Nem mondtak semmit. Ez nem közismert. Sajnos, még neked sem. Ez államtitok, uram.";
			link.l1 = "Szóval, ha jól értem, az óvadék nem jöhet szóba?"; 
			link.l1.go = "DTSG_AntiguaZalog_4";
		break;
		
		case "DTSG_AntiguaZalog_4":
			dialog.text = "Pontosan. Megértem, hogy kellemetlen elveszíteni egy értékes legénységi tagot, de sem ön, sem én nem tehetünk ellene semmit. Nagyon sajnálom, kapitány.";
			link.l1 = "Nincs óvadék, értem. Akkor mit szólna... kártérítéshez? Hozzátenném, hogy nagylelkû. Magának és az összes emberének, hogy senki se maradjon ki."; 
			link.l1.go = "DTSG_AntiguaZalog_5";
		break;
		
		case "DTSG_AntiguaZalog_5":
			dialog.text = "Megvesztegetés? Bátor dolog, kapitány, de semmi pénz nem ment meg minket azok haragjától, akik rájönnek, hogy elengedtük Charlie-t.";
			link.l1 = "Talán... De legalább beszélhetek vele?"; 
			link.l1.go = "DTSG_AntiguaZalog_6";
		break;
		
		case "DTSG_AntiguaZalog_6":
			dialog.text = "Miért ne? Nem tehet semmit, hogy megmentse vagy segítsen neki megszökni, szóval... csak rajta. Az egyik cellában van.";
			link.l1 = "Ha, és ha elmondja, hogy mivel vádolják, és felfedi azt az államtitkot, ami miatt annyira aggódik, tiszt úr?"; 
			link.l1.go = "DTSG_AntiguaZalog_7";
		break;
		
		case "DTSG_AntiguaZalog_7":
			dialog.text = "Nem aggódom emiatt. Meg fogja érteni, miért. Menjen, beszéljen a volt tisztjével, mielôtt meggondolom magam.";
			link.l1 = "Köszönöm."; 
			link.l1.go = "DTSG_AntiguaZalog_8";
		break;
		
		case "DTSG_AntiguaZalog_8":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.DTSG_AntiguaZalog");
			pchar.questTemp.jailCanMove = true;
			
			sld = CharacterFromID("Knippel");
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "SentJons_prison", "goto", "goto9");
			
			sld = GetCharacter(NPC_GenerateCharacter("DTSG_Killer", "sold_eng_10", "man", "man", sti(pchar.rank), PIRATE, -1, false, "quest"));
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Killer";
			LAi_SetStayType(sld);
			sld.talker = 5;
			GiveItem2Character(sld, "blade_14");
			EquipCharacterbyItem(sld, "blade_14");
			GiveItem2Character(sld, "pistol4");
			EquipCharacterbyItem(sld, "pistol4");
			AddItems(sld, "purse2", 1);
			sld.SaveItemsForDead = true;
			sld.DontClearDead = true;
			ChangeCharacterAddressGroup(sld, "SentJons_prison", "reload", "reload12");
			sld.rank = 30;
			SetSelfSkill(sld, 80, 80, 80, 80, 80);
			LAi_SetHP(sld, 200+MOD_SKILL_ENEMY_RATE*20, 200+MOD_SKILL_ENEMY_RATE*20);
			LAi_SetImmortal(sld, true);
		break;
		
		case "DTSG_AntiguaTrevoga_2":
			dialog.text = "Nincs rá szükség, kapitány. Ahogy mondtam, egy cellába került volna azzal a bolond Charlie-val. De egyrészt a kormányzó értékelte, hogy nem álltál ellen a letartóztatásnak, másrészt nem volt elégedett az uzsorás legutóbbi látogatásával, akinek sikolyai majdnem betörték a palota ablakait...";
			link.l1 = "Ô kérte a letartóztatásomat?"; 
			link.l1.go = "DTSG_AntiguaTrevoga_3";
			DelLandQuestMark(npchar);
		break;
		
		case "DTSG_AntiguaTrevoga_3":
			dialog.text = "Nem kérte - követelte. És Ôexcellenciája nem szereti, ha bármit is követelnek tôle. Ezért az uzsorásnak ajtót mutattak.";
			link.l1 = "Fergeteges. Nos..."; 
			link.l1.go = "DTSG_AntiguaTrevoga_4";
		break;
		
		case "DTSG_AntiguaTrevoga_4":
			dialog.text = "Javaslom, hogy ön is tegye ugyanezt, de Maure kapitány. És ne tegyen fel olyan kérdéseket, amikre nem kap választ.";
			link.l1 = "Nem megyek el innen Charlie Knippel nélkül."; 
			link.l1.go = "DTSG_AntiguaTrevoga_H1";
			link.l2 = "Kérem, uram, hadd beszéljek Charlie Knippel-lel. Vagy legalább megtudhatná, hogy..."; 
			link.l2.go = "DTSG_AntiguaTrevoga_Ch1";
		break;
		
		case "DTSG_AntiguaTrevoga_H1":
			dialog.text = "Ebben az esetben, csatlakozzon hozzá. Nem egy cellában, hanem a túlvilágon.";
			link.l1 = "Szóval, meghalt..."; 
			link.l1.go = "DTSG_AntiguaTrevoga_H2";
			ChangeCharacterComplexReputation(pchar, "authority", 1);
		break;
		
		case "DTSG_AntiguaTrevoga_H2":
			dialog.text = "Átkozottul éleslátó, kapitány. És remélem, tisztában van vele, hogy nem mondom el, ki tette és miért.";
			link.l1 = "Tényleg?"; 
			link.l1.go = "DTSG_AntiguaTrevoga_H3";
		break;
		
		case "DTSG_AntiguaTrevoga_H3":
			dialog.text = "Nem tudom, hogy ki tette. És most ne tegye próbára a türelmemet - mielôtt elrendelem, hogy zárkába vessék egy angol katona megöléséért.";
			link.l1 = "Tekintve, hogy nem sokan jutnak ki a cellájukból, nem szeretném ott végezni. Nem kívánok jó napot."; 
			link.l1.go = "DTSG_AntiguaTrevoga_5";
		break;
		
		case "DTSG_AntiguaTrevoga_Ch1":
			dialog.text = "Charlie Knippel nem beszél senkivel. Kivéve talán a Teremtôvel...";
			link.l1 = "Meghalt?"; 
			link.l1.go = "DTSG_AntiguaTrevoga_Ch2";
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;
		
		case "DTSG_AntiguaTrevoga_Ch2":
			dialog.text = "Az ítéletet végrehajtották. Nem mondhatok részleteket. És remélem, nem ragaszkodik hozzá - rosszul végzôdhet a dolog. Nem csak egy cellával. Világos, de Mor kapitány?";
			link.l1 = "Több mint világos. Viszontlátásra."; 
			link.l1.go = "DTSG_AntiguaTrevoga_5";
		break;
		
		case "DTSG_AntiguaTrevoga_5":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.DTSG_AntiguaTrevoga");
			AddQuestRecord("DTSG", "10");
			CloseQuestHeader("DTSG");
			ChangeCharacterComplexReputation(pchar, "authority", -10);
			AddCrewMorale(Pchar, -30);
		break;
		// <-- Длинные тени старых грехов
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
