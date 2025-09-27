// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Mit akarsz?", "Mit szeretnél tudni?"), "Mire van szüksége, " + GetAddress_Form(NPChar) + "?", "Már harmadszor próbálod megkérdezni...", "Elegem van belôled, tûnj el!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Sajnálom, meggondoltam magam.", "Semmiség, elnézést."), "Elfelejtettem, elnézést kérek...",
                      "Harmadszorra sikerül, mi? Elnézést...", "Bocsánat, bocsánat! Akkor majd én kikísérem magam...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.Guardoftruth.Trinidad") && pchar.questTemp.Guardoftruth.Trinidad == "begin")
			{
				link.l1 = "Figyelj, egy fregatt Miguel Dichoso parancsnoksága alatt 1654 áprilisában járt errefelé, akkor tûnt el. Tudna többet mondani a hajójáról? Talán látta, mi történt vele, vagy hová tûnt? Emlékszik valamire?";
				link.l1.go = "guardoftruth";
			}
		break;
		
		case "guardoftruth":
			dialog.text = "Oh-ho... Igen, Senor, ez egy látvány volt, amit látni lehetett! Az ilyen dolgokat nem felejted el, ha!";
			link.l1 = "El tudod mondani, mi történt?";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "Senior Dichoso fregattja horgonyt vetett San José kikötôjében. Jó kilátásom volt, hogy mindent lássak, igen. Mondom nektek, ez egy kiváló fregatt volt, egy remekmû, esküszöm a vérzô' szívemre! A legénység a sebességével dicsekedett, akár tizenhat csomóval is tudott száguldani!\nEgy napot töltöttek itt, aztán egyenesen Tobago szigete felé vették az irányt. Aztán, nem is hinnéd, furcsa dolgok történtek az idôjárással, amint eltûntek a horizont mögött. Az idôjárás akkor már napok óta jó volt, egyetlen felhô sem volt!\nÉs mégis a semmibôl jött ez a szörnyû vihar. Úgy nézett ki, mintha maga a Neptunusz látogatott volna meg minket, tényleg! Felmentem a világítótorony tetejére, hogy meggyújtsam, de akkor megláttam ôt... Santa Quiteria! Hatalmas hullámokon száguldott egy óriási tornádó kíséretében!\nA fregatt szikraként repült a világítótornyom mellett, majd a vihar északnyugatra sodorta! Azóta senki sem látta Santa Quiteria-t. Alig egy órával késôbb a szél, az esô és a felhôk elvonultak, a nap sütött, a viharnak nyoma sem volt! Soha nem láttam még ilyet! Bár aznap rengeteg borostyánt gyûjtöttem az öbölben...";
			link.l1 = "Tehát a vihar visszahajtotta a fregattot a Karib-tengerre?";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "Így van! Messze odaát, Martinique-on. Kétlem, hogy Dichoso 'av túlélte volna azt a vihart, bár mindent megtett, ami tôle telik! A fregatt nem süllyedt el, de a Santa Quiteria már biztosan a tenger fenekén van a korallok között... Tulajdonképpen nem te vagy az elsô, aki Dichoso és a fregattjáról kérdezett.";
			link.l1 = "Tényleg? Ki más érdeklôdött még Miguel iránt?";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "A spanyol flotta valami daliás kapitányáról, nem is akármilyenrôl! Úgy mutatkozott be, mint... ó... már el is felejtettem... Á! Senor Diego. A neve Diego, de a vezetékneve... de Montagna vagy de Montoya. Valami ilyesmi. Meghallgatott engem, ahogyan te is, megköszönte és elment. Azóta nem láttam.";
			if (sti(Pchar.money) >= 5000)
			{
				link.l1 = "Értem. Köszönöm szépen a történeted, sokat segítettél nekem. Hálámat érmékben fejezem ki. Viszontlátásra.";
				AddMoneyToCharacter(pchar, -5000);
				AddCharacterExpToSkill(pchar, "Leadership", 250);
			}
			else
			{
				link.l1 = "Értem. Köszönöm szépen a történeted, sokat segítettél nekem. Viszlát.";
			}
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			DialogExit();
			AddQuestRecord("Guardoftruth", "41");
			pchar.questTemp.Guardoftruth.Trinidad = "mayak";
			pchar.quest.GuardOT_setDiego.win_condition.l1 = "ExitFromLocation";
			pchar.quest.GuardOT_setDiego.win_condition.l1.location = pchar.location;
			pchar.quest.GuardOT_setDiego.function = "GuardOT_SetDiegoOnMayak";
		break;
	}
	UnloadSegment(NPChar.FileDialog2); 
}
