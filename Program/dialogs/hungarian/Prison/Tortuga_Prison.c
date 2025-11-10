// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
 	switch(Dialog.CurrentNode)
	{
        case "quests":
            dialog.text = "Beszélj, hallgatlak.";
			link.l1 = "Tévedtem. Viszontlátásra.";
			link.l1.go = "Exit";
		break;
		
		case "tonzag_bail":
			NextDiag.TempNode = "First_officer";
		
			dialog.text = "Mi a célja a Tortugán tett látogatásának, kapitány?";
			link.l1 = "Könyörgöm! Segítsen a bajtársamnak, és én válaszolok minden kérdésére!";
			link.l1.go = "tonzag_bail_a";
			link.l2 = "Maga egy ilyen fontos személy, és ôrség nélkül jött ide, rögtön azután, hogy az egész börtön lövést hallott?!";
			link.l2.go = "tonzag_bail_b";
		break;
		
		case "tonzag_bail_a":
			dialog.text = "Amíg késlekedik a válasszal, addig ô elvérzik. Megismétlem a kérdést.";
			link.l1 = "";
			link.l1.go = "tonzag_bail_1";
		break;
		
		case "tonzag_bail_b":
			dialog.text = "Eleget tudok a történtekrôl. Megismétlem a kérdést.";
			link.l1 = "";
			link.l1.go = "tonzag_bail_1";
		break;
		
		case "tonzag_bail_1":
			dialog.text = "Utolsó esély, kapitány.";
			link.l1 = "Végrehajtom a fôkormányzó által rám bízott feladatot!";
			link.l1.go = "tonzag_bail_truth";
			link.l2 = "Nagyon jól tudja, hogy én a saját hajóm kapitánya vagyok, és szerzôdés szerint dolgozom. És évente néhányszor meglátogatom az önök gyönyörû szigetét!";
			link.l2.go = "tonzag_bail_lies";
		break;
		
		case "tonzag_bail_truth":
			dialog.text = "Gyanakodtam, de nem voltam benne teljesen biztos. Szerencséje van, hogy néhány nappal ezelôtt fontos találkozóra került sor Capsterville-ben. Néhány nagyon befolyásos embernek sikerült megállapodnia. Így már nem vagy az ellenségem.";
			link.l1 = "Segítesz nekünk?";
			link.l1.go = "tonzag_bail_truth_1";
			
			AddDialogExitQuestFunction("Tonzag_GetOut");
		break;
		
		case "tonzag_bail_truth_1":
			dialog.text = "Azonnal elengedlek. A bajtársát átszállítjuk a hajóra, és ellátásban részesül.";
			link.l1 = "Köszönöm...";
			link.l1.go = "tonzag_bail_truth_2";
		break;
		
		case "tonzag_bail_truth_2":
			dialog.text = "Majdnem zátonyra futottál, Charles! Menjen el, és legalább egy hónapig ne térjen vissza Tortugára. Hagyja, hogy a por leülepedjen, és a fejek lehûljenek.";
			link.l1 = "Megteszem. Viszlát!";
			link.l1.go = "exit";
			link.l2 = "Egyáltalán nem magyarázol meg semmit? Még egy kicsit sem? ...";
			link.l2.go = "tonzag_bail_truth_3";
		break;
		
		case "tonzag_bail_truth_3":
			dialog.text = "Valaki jelentette magát. Állítólag egy fanatikus katolikus vagy, aki azért érkezett gyönyörû szigetünkre, hogy rosszindulatúan megölje a tiszteletreméltó kormányzót.";
			link.l1 = "Nem vagyok fanatikus!";
			link.l1.go = "tonzag_bail_truth_4";
		break;
		
		case "tonzag_bail_truth_4":
			dialog.text = "Ez ügyesen van megírva, higgye el nekem. Jól értek az ilyesmihez - a legjobb rágalmak azok, amelyekben legalább egy szemernyi igazság van.";
			link.l1 = "Ki írta a jelentést?";
			link.l1.go = "tonzag_bail_truth_a";
			link.l2 = "Ki engedte be a gyilkost a börtönbe?";
			link.l2.go = "tonzag_bail_truth_b";
		break;
		
		case "tonzag_bail_truth_a":
			dialog.text = "Valaki, aki azt akarta, hogy néhány napra a börtönbe zárjanak, ahelyett, hogy azonnal a hugenották kínzóasztalára küldték volna a La Roche pincéjében.\nElég volt, Charles. Menjetek el. Foglalkozz elôbb azzal, ami elôtted van, és utána... nos, értesz engem!";
			link.l1 = "Igen. Megértem. Viszlát, parancsnok.";
			link.l1.go = "exit";
		break;
		
		case "tonzag_bail_truth_b":
			dialog.text = "Hoztam.";
			link.l1 = "Jobb lenne, ha küldene egy másikat, mielôtt elmegyek innen.";
			link.l1.go = "tonzag_bail_truth_b_threat";
			link.l2 = "Csupa fül vagyok, parancsnok.";
			link.l2.go = "tonzag_bail_truth_b_charm";
		break;
		
		case "tonzag_bail_truth_b_threat":
			AddComplexSelfExpToScill(100, 100, 100, 100);
		
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 60) {
				dialog.text = "Nem vagyok köteles semmit sem megmagyarázni neked, Charles. Örüljön, hogy az én kezembe került, és nem a közvetlen felettesem kezébe. És örülj, hogy a fônököd lesz az, aki engem fog kárpótolni ezekért a zavarokért, és nem téged.";
				link.l1 = "Riiiiiiiiiii rendben... Maga nem ismeri úgy a fônökömet, mint én. Viszlát, parancsnok.";
				link.l1.go = "exit";
				
				Notification_Skill(false, 60, SKILL_LEADERSHIP);
				AddQuestRecord("Tonzag", "3.1");
			} else {
				dialog.text = "Tudja mit? Azt hiszem, elmondom. Nagylelkû, adómentes adományt tettek a különleges helyôrségi nyugdíjalapba. Hálából az adományozó hozzájárulhatott egy hírhedt bûnözô gyors és törvényes kivégzéséhez!";
				link.l1 = "Az én tisztemet?";
				link.l1.go = "tonzag_bail_truth_b_1";
				link.l2 = "A barátom?";
				link.l2.go = "tonzag_bail_truth_b_1";
				
				Notification_Skill(true, 60, SKILL_LEADERSHIP);
			}
		break;
		
		case "tonzag_bail_truth_b_charm":
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 60) {
				dialog.text = "Nem vagyok köteles semmit sem megmagyarázni neked, Charles. Örüljön, hogy az én kezembe került, és nem a közvetlen felettesem kezébe. És örülj, hogy a fônököd lesz az, aki engem fog kárpótolni ezekért a zavarokért, és nem téged.";
				link.l1 = "Riiiiiiiiiii rendben... Maga nem ismeri úgy a fônökömet, mint én. Viszlát, parancsnok.";
				link.l1.go = "exit";
				
				Notification_Skill(false, 60, SKILL_LEADERSHIP);
				AddQuestRecord("Tonzag", "3.1");
			} else {
				dialog.text = "Tudja mit? Azt hiszem, elmondom. Nagylelkû, adómentes adományt tettek a különleges helyôrségi nyugdíjalapba. Hálából az adományozó hozzájárulhatott egy hírhedt bûnözô gyors és törvényes kivégzéséhez!";
				link.l1 = "Az én tisztemet?";
				link.l1.go = "tonzag_bail_truth_b_1";
				link.l2 = "A barátom?";
				link.l2.go = "tonzag_bail_truth_b_1";
				
				Notification_Skill(true, 60, SKILL_LEADERSHIP);
			}
		break;
		
		case "tonzag_bail_truth_b_1":
			dialog.text = "Távozzon, Charles. És vigye magával ezt a söpredéket. A társaid kiválasztása... kiábrándító.";
			link.l1 = "Legalább azt mondd meg, hol találom a... jótevôd?";
			link.l1.go = "tonzag_bail_truth_b_2";
		break;
		
		case "tonzag_bail_truth_b_2":
			dialog.text = "A szárazföldön. Viszlát, Charles.";
			link.l1 = "";
			link.l1.go = "exit";
			
			pchar.questTemp.TonzagQuest.KnowMain = true;
			AddQuestRecord("Tonzag", "3.2");
		break;
		
		case "tonzag_bail_lies":
			dialog.text = "Feljelentést tettek ellened. Egy nagyon csúnyát. Kapitány, nyilvánvalóan felültették, de... Teljesen jogomban áll még néhány hétig itt tartani, és hagyni a barátját meghalni. Hacsak...";
			link.l1 = "Mennyibe kerül?";
			link.l1.go = "tonzag_bail_lies_a";
			link.l2 = "Ki ültetett fel? Maga engedte be a gyilkost a börtönbe?";
			link.l2.go = "tonzag_bail_lies_b";
			
			AddDialogExitQuestFunction("Tonzag_Bailed");
		break;
		
		case "tonzag_bail_lies_a":
			pchar.questTemp.TonzagQuest.Bail = 500;
			dialog.text = "Kérem, fizessen be ötszáz dublont a tortugai helyôrség nyugdíjalapjába a helyi pénzkölcsönzônél.";
			if (CheckAttribute(pchar, "questTemp.FMQT") && pchar.questTemp.FMQT == "end") {
				pchar.questTemp.TonzagQuest.Bail = 600;
				dialog.text = dialog.text + " És tegyünk hozzá még száz dublont a régi bajokért, amelyeket azzal kavarsz, hogy egy magas rangú hölggyel keveredtél össze ezen a szigeten.";
			}
			link.l1 = "Nyisd már ki ezt az átkozott ajtót!";
			link.l1.go = "exit";
			
			AddQuestRecord("Tonzag", "3.3");
		break;
		
		case "tonzag_bail_lies_b":
			pchar.questTemp.TonzagQuest.Bail = 500;
			dialog.text = "Már így is túl sok idômet raboltad el. Menj az uzsoráshoz, és fizess be ötszáz dublont a Tortuga helyôrség nyugdíjalapjába.";
			if (CheckAttribute(pchar, "questTemp.FMQT") && pchar.questTemp.FMQT == "end") {
				pchar.questTemp.TonzagQuest.Bail = 600;
				dialog.text = dialog.text + " És tegyünk hozzá még száz dublont a régi bajokért, amelyeket azzal kavarsz, hogy egy magas rangú hölggyel keveredtél össze ezen a szigeten.";
			}
			link.l1 = "Nyisd már ki ezt az átkozott ajtót!";
			link.l1.go = "exit";
			
			AddQuestRecord("Tonzag", "3.3");
		break;
		
		case "tonzag_bailed":
			dialog.text = "";
			link.l1 = "A pénzt letétbe helyeztük. Hol van Hercule?";
			link.l1.go = "tonzag_bailed_1";
		break;
		
		case "tonzag_bailed_1":
			dialog.text = "Elsôsegélyben részesítettük, és elküldtük a hajójára. A gazember szívós, valószínûleg túléli. Viszlát, kapitány, és egy darabig ne engedje, hogy a szigetünkön érjem utol!";
			link.l1 = "Nos, egy ilyen fogadtatás után, jó messze maradok innen! Viszlát, parancsnok.";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "First time";
			AddDialogExitQuestFunction("Tonzag_GetOut");
		break;
		
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
