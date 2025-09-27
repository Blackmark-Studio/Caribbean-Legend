// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Milyen kérdések, "+ GetSexPhrase("fiam","lányom") +"?", "Kérdezz csak, hallgatlak..."), "Figyelek, beszélj most, "+ GetSexPhrase("fiam","lányom") +"...", "Harmadszorra, "+ GetSexPhrase("fiam","lányom") +", kérd, amire szükséged van.",
                          "Egy lelkésznek rengeteg munkája van, és te eltereled a figyelmemet, "+ GetSexPhrase("fiam","lányom") +"...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Meggondoltam magam...", "Most nem, atyám..."), "Nincs mit mondanom, elnézést kérek.",
                      "Megkérdezem, de késôbb. Bocsásson meg, atyám.", "Bocsásson meg, szent atyám...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			// калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "havana")
			{
				ref sld = characterFromId("Villemstad_Priest");
				link.l1 = "Üdvözlöm atyám. A willemstadi templom elöljárója "+sld.name+" küldött. Elmondta neki, hogy furcsa észleléseket tett egy kubai barlangban.";
				link.l1.go = "caleuche";
				DelLandQuestMark(npchar);
			}
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "havana1")
			{
				link.l1 = "Meglátogattam a barlangot a dzsungelben, atyám.";
				link.l1.go = "caleuche_4";
				DelLandQuestMark(npchar);
			}
		break;
		
		case "caleuche":
			dialog.text = "Hála Istennek, hogy odafigyelt rá! Miután az élôholtakról szóló pletykák eljutottak a fülemhez, azonnal értesítettem Ôfôméltóságát, Vincento atyát, Santiago inkvizítorát. Megígérte, hogy utánajár a dolognak, de eddig nem történt semmilyen intézkedés! Attól tartok, Ôméltóságának fontosabb dolgai is vannak...";
			link.l1 = "Majd én magam utánanézek. Különben is, ezek a pletykák nem mások, mint részeg vadászok zagyvaságai - ezért az inkvizíció nem vette ôket komolyan. Elmegyek a dzsungelbe, hogy a saját szememmel gyôzôdjek meg róla.";
			link.l1.go = "caleuche_1";
		break;
		
		case "caleuche_1":
			dialog.text = "Biztosíthatlak, fiam, hogy ez döntô fontosságú. Az emberre, aki mesélt nekem a két lábon járó holtakról, az életemet is rábízom.";
			link.l1 = "Rendben, akkor felkészülök a csatára. Ha a szentségtelen lények valóban gyökeret eresztettek a barlangban, ki fogom ôket irtani ebbôl a világból.";
			link.l1.go = "caleuche_2";
		break;
		
		case "caleuche_2":
			dialog.text = "Menj az Úr áldásával, fiam! Tessék, fogd ezt a megszentelt amulettet. Segíteni fog a feladatodban. Menj most, pusztítsd el a gonoszság ivadékait!";
			link.l1 = "Addig is, atyám "+npchar.name+". Ha végeztem, azonnal visszatérek hozzád.";
			link.l1.go = "caleuche_3";
		break;
		
		case "caleuche_3":
			DialogExit();
			AddQuestRecord("Caleuche", "27");
			pchar.questTemp.Caleuche = "cave";
			Log_Info("Kaptál egy templomi amulettet");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "amulet_7"); 
			if (GetCharacterIndex("cavehunter") != -1)
			{
				sld = characterFromId("cavehunter");
				sld.dialog.currentnode = "cavehunter_5";
				LAi_SetGuardianType(sld);
				sld.protector = true;
				LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
				AddLandQuestMark(sld, "questmarkmain");
			}
			LocatorReloadEnterDisable("Cuba_Jungle_07", "reload2_back", false);
			pchar.quest.Caleuche_cuba_caveentrance.win_condition.l1 = "location";
			pchar.quest.Caleuche_cuba_caveentrance.win_condition.l1.location = "Cuba_CaveEntrance";
			pchar.quest.Caleuche_cuba_caveentrance.function = "Caleuche_CubaCaveEntrance";
		break;
		
		case "caleuche_4":
			dialog.text = "Mit láttál, fiam? Alaptalan volt a félelmünk?";
			link.l1 = "Attól tartok, nem, atyám "+npchar.name+". A barlangban hemzsegtek az élôholtak, de Isten segítségével gyôztesen jöttem ki. Nem fognak többé senkit sem zavarni.";
			link.l1.go = "caleuche_5";
		break;
		
		case "caleuche_5":
			dialog.text = "Dicsértessék az Úr! Te valóban az Ô fenyítô kardja vagy, fiam! Engedd meg, hogy az egész havannai egyházközség nevében kifejezzem legmélyebb hálámat. Kérlek, fogadd el hálád jeléül ezeket a megszentelt amuletteket. Bizonyára hasznosnak találjátok majd ôket veszedelmes utatokon.";
			link.l1 = "Köszönöm, atyám "+npchar.name+".";
			link.l1.go = "caleuche_6";
		break;
		
		case "caleuche_6":
			Log_Info("Egyházi amulettet kaptál");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "amulet_3"); 
			GiveItem2Character(pchar, "amulet_9"); 
			GiveItem2Character(pchar, "obereg_7"); 
			GiveItem2Character(pchar, "obereg_11"); 
			dialog.text = "Ezen kívül gondoskodom róla, hogy mind a köznép, mind a nemesek tudomást szerezzenek hôstettedrôl, és fáradhatatlanul imádkozni fogok érted éjjel-nappal.";
			link.l1 = "Köszönöm, atyám. Még egy kérdést szeretnék feltenni.";
			link.l1.go = "caleuche_7";
		break;
		
		case "caleuche_7":
			dialog.text = "Kérdezz, fiam.";
			link.l1 = "Mondja, atyám "+npchar.name+", érkezett nemrég egy Joachim Merriman nevû férfi a városába? Középkorú senor, egy portugál, bajusszal, császárszakállal és szúrós szemekkel?";
			link.l1.go = "caleuche_8";
		break;
		
		case "caleuche_8":
			sld = characterFromId("Villemstad_Priest");
			dialog.text = "Sajnálom, de sem a neve, sem a leírása nem ismerôs. Ki ez a férfi?";
			link.l1 = "Merriman egy varázsló. Az inkvizíció már nagyon régóta vadászik rá. Atya "+sld.name+" és gyanítom, hogy az élôholtak megjelenése Kubában az ô mûve. Nemrég még Willemstadban élt, aztán hirtelen eltûnt. Nem sokkal késôbb az ôt szállásoló nôbôl két lábon járó csontváz lett.";
			link.l1.go = "caleuche_9";
		break;
		
		case "caleuche_9":
			dialog.text = "Micsoda rémálom! Azonnal értesítem az inkvizítorokat, magát Vincento atyát! Tudnia kell, hogy mi történik itt! Mondd, fiam, mit gondolsz, azok az emberek, akik eltûntek a dzsungelben...?";
			link.l1 = "Valóban, szinte biztos vagyok benne, hogy azok a barlangban élô halottak a te egykori polgáraid voltak. Meg akarom keresni ezt a portugált Kubában, és a sarkamra akarom állítani! Annak a gazembernek sikerült megszereznie egy régi pogány ereklyét - Yum Cimil jáde koponyáját. Attól tartok, hogy az ereklyével és az indián boszorkánysággal Merriman még több bajt fog okozni, ha senki sem állítja meg egyhamar.";
			link.l1.go = "caleuche_10";
		break;
		
		case "caleuche_10":
			dialog.text = "Gondolod, hogy az élôhalottak újra feltámadnak?";
			link.l1 = "Majdnem biztos. Nem tudom, mi hajtja, de az biztos, hogy a törekvései távolról sem erényesek.";
			link.l1.go = "caleuche_11";
		break;
		
		case "caleuche_11":
			dialog.text = "A Mindenható legyen irgalmas hozzánk! Keresd meg ôt, fiam! Engedélyezem, hogy Szent Egyházunk nevében bármilyen intézkedést megtegyél ellene! Azonnal küldök egy hírnököt Santiagóba, aki jelentést tesz Vincento atyának.";
			link.l1 = "Tegye azt. Isten veled, atyám "+npchar.name+".";
			link.l1.go = "caleuche_12";
		break;
		
		case "caleuche_12":
			DialogExit();
			AddQuestRecord("Caleuche", "29");
			pchar.questTemp.Caleuche = "graveyard";
			AddCharacterMaxHealth(pchar, 3);
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
			ChangeCharacterComplexReputation(pchar, "authority", 2);
			ChangeCharacterComplexReputation(pchar, "fame", 3);
			ChangeCharacterNationReputation(pchar, SPAIN, 10);
			AddCharacterExpToSkill(pchar, "Leadership", 500);
			AddLandQuestMark(characterFromId("Havana_CemeteryMan"), "questmarkmain");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
